=====================
Integration
=====================   


Requirements
~~~~~~~~~~~~

Supported operating systems and compilers
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The library has been extensively tested on Linux x86 and x86_64. It has also been tested on Solaris x86, Linux on ARM and Linux on MIPS platforms, on Mac OS X on x86 and on various versions of Microsoft Windows.

Compilation
^^^^^^^^^^^

On Linux, FreeBSD and Mac OS X the library has to be compiled and installed before use unless you use a precompiled package provided by your operating system distribution. If it is provided, you are recommended to use it as it would be updated
from the central repository when the bugs are fixed.

On Microsoft Windows the official library binaries are provided, so you do not have to build it. Unless you have experience building with Cygwin, you're advised not to build from source and use the official binary.

Required libraries
******************

The library depends only on libc (glibc-devel on Linux) and gcc, although the examples require also libstdc++ (libstdc++-devel) and g++. Minimum supported version is glibc 2.2, 
although if IPv6 is requested, at least glibc 2.4 is required.

If the library is built with SSL support, the openssl development package (openssl-devel) needs to be installed.

On Microsoft Windows the Cygwin with necessary development packages must be installed (and openssl-devel as well).

Compiling
*********

The library is configured and built the standard Unix way:

::

  ./configure [--enable-openssl] [--enable-ipv6]
  make
  
Installing
**********

Although no install is necessary to use the libraries, the install target is provided for convenience and could be invoked via ``sudo make install``


Linking
^^^^^^^

Link your application with either libircclient.a or libircclient.so depending on your needs. If you use the system-provided library, please link with libircclient.so.

If you have built the library with SSL support, you will need to link with OpenSSL libraries; add ``-lcrypto -lssl`` to your LDFLAGS

On Microsoft Windows please link with libircclient.lib which implicitly links with libircclient.dll


Coding
~~~~~~

Initialization
^^^^^^^^^^^^^^

Include the headers
*******************

Before using the library you need to include the library header *libircclient.h*. You may also want to include *libirc_rfcnumeric.h* which provides the RFC codes:

.. sourcecode:: c

 #include "libircclient.h"
 #include "libirc_rfcnumeric.h"


Create event handlers
*********************

Unlike most network protocols such as HTTP or SMTP, the IRC protocol is event-based. The events come from server asynchronously. Some events are triggered by your 
action (such as joining the channel or changing your nick), some are triggered by other IRC users (such as sending you a message), and some are triggered by the IRC 
server itself (such as sending operation notes or invoking NickServ services).

Libircclient helps handling those events by providing the :c:type:`event handling structure <irc_callbacks_t>`. It declares the events you can define in your application,
and when such event is received from the server, the appropriate callback will be called. The number of events you need to handle depending on the complexity of your client
and the functionality it supports.

Generally there are only two events you must handle to provide a bare minimum functionality: :c:member:`event_connect` and :c:member:`event_numeric`. However it is recommended
to create an event dump function and use it for all unused events to make sure you do not miss an important event because you expected a wrong one. See function **dump_event** in 
the file examples/irctest.c

Windows-specific initialization
*******************************

If you link with the **static** library on Microsoft Windows, you need to initialize the Winsock2 library before calling the library functions. It could be done by following:

.. sourcecode:: c

  WSADATA wsaData;
 
  if ( WSAStartup ( MAKEWORD (2, 2), &wsaData) != 0 )
      // report an error

However if you link with the **dynamic** library (libircclient.dll) which is default if you use the official build, this is not needed because the DLL initializes it automatically on load.


Create an IRC session
*********************

To use the library at least one :c:type:`IRC session <irc_session_t>` needs to be created. One session could be used to establish a single connection to one IRC server for one nick. 
However more than one session could be created if needed.

To create a session, call the :c:func:`irc_create_session` function:

.. sourcecode:: c

  // The IRC callbacks structure
  irc_callbacks_t callbacks;

  // Init it
  memset ( &callbacks, 0, sizeof(callbacks) );

  // Set up the mandatory events
  callbacks.event_connect = event_connect;
  callbacks.event_numeric = event_numeric;

  // Set up the rest of events

  // Now create the session
  irc_session_t * session = irc_create_session( &callbacks );

  if ( !session )
      // Handle the error

This code could be repeated as many times as needed to create multiple sessions. The same callback structure could be reused for multiple sessions.
      
Set options
***********

Besides debugging there are two options you may need to use. The :c:macro:`LIBIRC_OPTION_STRIPNICKS` enables automatic parsing of nicknames, 
and since it is hard to imagine the case when it should not be enabled, we enable it:

.. sourcecode:: c

  irc_option_set( session, LIBIRC_OPTION_STRIPNICKS );

The second option you may need if you use SSL connections and plan to connect to the servers which use self-signed certificates. See the 
documentation for :c:macro:`LIBIRC_OPTION_SSL_NO_VERIFY`


Connect to the server
*********************

To initiate the connection to the IRC server, call the :c:func:`irc_connect` function:

.. sourcecode:: c

  // Connect to a regular IRC server
  if ( irc_connect (session, "irc.example.com", 6667, 0, "mynick", "myusername", "myrealname" ) )
    // Handle the error: irc_strerror() and irc_errno()

To initiate the connection to the IRC server over SSL, call the :c:func:`irc_connect` function and prefix the host name or IP address with a hash symbol:

.. sourcecode:: c

  // Connect to the SSL server; #192.168.1.1 is also possible
  if ( irc_connect (session, "#irc.example.com", 6669, 0, "mynick", "myusername", "myrealname" ) )
    // Handle the error: irc_strerror() and irc_errno()
   
This function only initiates the connection, so when it successfully returns the connection is only initiated, but not established yet. Then one
of the following happens after you invoke the networking handler:

 - If the connection is established, you will receive the :c:member:`event_connect` - this is why it is important to handle it
 - If the connection failed, the networking handler function will return failure    


Connect to the IPv6 server
**************************

To initiate the connection to the IPv6 server, call the :c:func:`irc_connect6` function:

.. sourcecode:: c

  if ( irc_connect6 (session, "2001:0db8:85a3:0042:1000:8a2e:0370:7334", 6669, 0, "mynick", "myusername", "myrealname" ) )
    // Handle the error: irc_strerror() and irc_errno()

The rest of the details, including the return value and the SSL are the same as with regular connect.
    

Start the networking loop
*************************

To let the library handle the events, there are two scenarios. You can either invoke the built-in networking loop which will handle the networking and
call your events, or you can write your own loop.

Invoking the build-in networking loop is simpler but limited. Since it loops until the connection terminates, it is not an option for a GUI application
(unless you start the loop in a separate thread which you can do). And since this loop only can handle one session, it is impossible to use it if you want
to handle multiple IRC sessions. In those cases the custom networking loop, described below, should be used.

To start the event loop call the :c:func:`irc_run` function:

.. sourcecode:: c

  if ( irc_run (s) )
    // Either the connection to the server could not be established or terminated. See irc_errno()

Remember that irc_run() call **will not return** until the server connection is not active anymore.

    
Use the custom networking loop
******************************

If you use multiple sessions or have your own socket handler, you can use the custom networking loop. In this case your application must be select()-based 
(:ref:`see the FAQ <faq_epoll>` if you want to use other polling methods). And you need to run the following loop:

.. sourcecode:: c

  // Make sure that all the IRC sessions are connected
  if ( !irc_is_connected(session) )
    // reconnect it, or abort
    
  // Create the structures for select()
  struct timeval tv;
  fd_set in_set, out_set;
  int maxfd = 0;

  // Wait 0.25 sec for the events - you can wait longer if you want to, but the library has internal timeouts
  // so it needs to be called periodically even if there are no network events
  tv.tv_usec = 250000;
  tv.tv_sec = 0;

  // Initialize the sets
  FD_ZERO (&in_set);
  FD_ZERO (&out_set);

  // Add your own descriptors you need to wait for, if any
  ...
  
  // Add the IRC session descriptors - call irc_add_select_descriptors() for each active session
  irc_add_select_descriptors( session, &in_set, &out_set, &maxfd );
  
  // Call select()
  if ( select (maxfd + 1, &in_set, &out_set, 0, &tv) < 0 )
     // Error
   
  // You may also check if any descriptor is active, but again the library needs to handle internal timeouts,
  // so you need to call irc_process_select_descriptors() for each session at least once in a few seconds
  ...

  // Call irc_process_select_descriptors() for each session with the descriptor set
  if ( irc_process_select_descriptors (session, &in_set, &out_set) )
      // The connection failed, or the server disconnected. Handle it.

  // Do it again


Channels and users
^^^^^^^^^^^^^^^^^^

Before calling any of those functions make sure you have connected to the server.

Join and leave a channel
************************

To join the channel call the :c:func:`irc_cmd_join` function with the channel name:

.. sourcecode:: c

  // Join the channel #linux
  if ( irc_cmd_join( session, "#linux", 0 ) )
    // most likely connection error

  // Join the channel $science protected by the secret key *superpassword*
  if ( irc_cmd_join( session, "$science", "superpassword" ) )
    // most likely connection error

You can join as many channels as you want, although the serer may restrict the number of channels you can join simultaneously.

If the join was successful you will receive the :c:member:`event_join` event. You need to wait for this event before you can perform any channel operations (such as sending the messages). However you do NOT
have to wait for this event to issue a second JOIN command as shown in the example above.

If the join was not successful, you will receive the error via :c:member:`event_numeric`.

To leave the channel call the :c:func:`irc_cmd_part` function with the channel name:

.. sourcecode:: c

  // Leave the channel #linux
  if ( irc_cmd_part( session, "#linux" ) )
    // most likely connection error

  // Leave the channel $science
  if ( irc_cmd_part( session, "$science" ) )
    // most likely connection error
    

Send a message to a channel or to a user
****************************************

After you have joined the channel, you can send a message to the channel by using the :c:func:`irc_cmd_msg` function with the channel name:

.. sourcecode:: c

  // Say "Hi!" to everyone in the channel #linux
  if ( irc_cmd_msg( session, "#linux", "Hi!" ) )
    // most likely connection error

Technically the protocol does not require one to join the channel to send the messages into the channel. However most servers by default set 
the channel mode which prevents the users who did not join the channel from sending the message into the channel.

Same function is used to send a "private" message to another user. The "private" messages do not go through the channels, but they still go through
the IRC server (sometime multiple servers) and can be seen or even logged by the IRC network operators.

.. sourcecode:: c

  // Say "Hi!" to IRC user john
  if ( irc_cmd_msg( session, "john", "Hi!" ) )
    // most likely connection error

If the message was sent successfully you will not receive any confirmation or event. You will only receive the error via :c:member:`event_numeric` 
if the message was not sent.
    

Receive messages from a channel or from a user
**********************************************

You receive the channel messages by handling the :c:member:`event_channel`. Each time someone says something in the channel this event is called.

You receive the "private" messages from other users by handling the :c:member:`event_privmsg`.

Those event handlers should be created in your application and passed to the library when you `create an IRC session`_


Send an action message
**********************

"Action" messages, also called /me messages, are specially formatted CTCP messages. However the library contains a special function to send 
them, :c:func:`irc_cmd_me`. Actions sent by other people are handled by the :c:member:`event_ctcp_action` event.

Same as with sending messages no confirmation is received on success.


Send a CTCP request
*******************

Other CTCP requests such as PING, VERSION etc should be sent by calling :c:func:`irc_cmd_ctcp_request`. If the CTCP response is received, 
it is handled by the :c:member:`event_ctcp_rep` event.


Handling DCC chat
^^^^^^^^^^^^^^^^^

Implementing the DCC callback
*****************************

No matter whether you plan to initiate DCC chats or respond to them you must implement the :c:type:`DCC callback <irc_dcc_callback_t>`:

.. sourcecode:: c

 void dcc_callback (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length)
 {
    if ( status )
    {
        // If status is LIBIRC_ERR_CLOSED, the chat has been closed by the remote party.
        // Otherwise it is an error; the CHAT either terminated or could not be established. status is the error code; see irc_strerror(status)
    }
    else if ( length == 0 )
    {
        // The remote side has accepted the chat request, send "hello" something to them
        irc_dcc_text( session, id, "Hello!" );
    }
    else
    {
        // We have received the chat message from the remote party
        printf ("Remote party said: %s\n", data );
    }
 }

This callback should be passed to either :c:func:`irc_dcc_chat` function which initiates the request, or to :c:func:`irc_dcc_accept` function
which accepts the DCC CHAT request initiated by another user.
 
 
Initiating the DCC CHAT
***********************

You can initiate the DCC chat with another user by calling :c:func:`irc_dcc_chat`:

.. sourcecode:: c

 // The DCC chat session id will be returned in this variable
 irc_dcc_t dccid;
 
 // Initiate the DCC chat with the IRC user "john"
 if ( irc_dcc_chat( session, 0, "john", dcc_callback, &dccid ) )
   // report error

Now you can proceed with other tasks. When John accepts or declines the chat, the dcc_callback() will be called, and it will be possible 
to use the :c:func:`irc_dcc_text` function to send the chat messages. The callback will also be called each time a new chat message is 
received, or when the chat is finished or terminated because of network error.


Responding to DCC CHAT requests
*******************************

To respond to the DCC CHAT equests your application should implement for the :c:member:`event_dcc_chat_req` event. 
The callback could be implemented as following:

.. sourcecode:: c

 void callback_event_dcc_chat( irc_session_t * session, const char * nick, const char * addr, irc_dcc_t dccid )
 {
     // User 'nick' from the IP address 'addr' tries to initiate the DCC chat with us.
     // Store this information in the application internal queue together with the dccid so the callback can return
     dcc_queue.store( dccid, "CHAT from " + nick + " IP address: " + addr  );
 }

and registered when the IRC session is created.
If your application does not handle DCC at all you can just call the :c:func:`irc_dcc_decline` function inside the callback.
 
If it does, we only store this information in the callback, and return. This is because the event processing will stop 
until the callback returns, so popping up the dialog asking for the user confirmation would stop further events such as 
channel messages from being processed. Even if your application is automatic and doesn't pop up dialogs it is still better to
separate the chat logic from the callback logic.

Somewhere later the application would check the queue in the GUI thread, get this information, and pop up the dialog asking the user
feedback. Then if the chat request was accepted, the application would call the :c:func:`irc_dcc_accept` function, and if it was
declined, the application would call the :c:func:`irc_dcc_decline` function. Both functions will accept the *dccid* which identifies 
this specific request:

.. sourcecode:: c

 // Somewhere in the GUI thread
 if ( !dcc_queue.empty() )
 {
     // Get the DCC information and show the dialog to the user
     irc_dcc_t dccid = dcc_chat_queue.top().dccid;
     
     ...
     
     // React to the user entry
     if ( dialog.isAccepted() )
         irc_dcc_accept( session, dccid, 0, dcc_callback );
     else
         irc_dcc_decline( session, dccid );
 }


Send CHAT messages
******************

Once the chat session is established, you can send the chat messages using :c:func:`irc_dcc_text` function. Note that you need to pass the 
dcc session id instead of nick:

.. sourcecode:: c
  
  irc_dcc_text( session, dccid, "Hello there!" );


Handling DCC file transfer
^^^^^^^^^^^^^^^^^^^^^^^^^^

This section covers handling sending and receiving files via DCC.


Implementing the callback
*************************

No matter whether you plan to send or receive files via dcc you must implement the :c:type:`DCC callback <irc_dcc_callback_t>`. 
While the same callback may be used both for sending and receiving, this is not recommended since the logic is different. Therefore
the suggested implementation would be to use different callbacks as suggested:

.. sourcecode:: c

 // This callback is used when we send a file to the remote party
 void callback_dcc_send_file (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length)
 {
    if ( status )
    {
        // It is an error; the send operation was either terminated or the connection could not be established. status is the error code; see irc_strerror(status)
    }
    else
    {
        // We have sent some data to the remote party, 'length' indicates how much data was sent
        printf ("Sent bytes: %d\n", length );
    }
 }

 // This callback is used when we receive a file from the remote party
 void callback_dcc_recv_file (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length)
 {
    if ( status )
    {
        // It is an error; the send operation was either terminated or the connection could not be established. status is the error code; see irc_strerror(status)
    }
    else if ( data == 0 )
    {
        // File transfer has been finished
        printf ("File has been received successfully\n" );
    }
    else
    {
        // More file content has been received. Store it in memory, write to disk or something
        printf ("Received %d bytes of data\n", length );
    }
 }
 
 
This callback should be passed to either :c:func:`irc_dcc_sendfile` function which initiates the request, or to :c:func:`irc_dcc_accept` function
which accepts the DCC RECVFILE request initiated by another user.
 
 
Sending the file via DCC
************************

You can initiate sending the file via DCC to another user by calling :c:func:`irc_dcc_sendfile`:

.. sourcecode:: c

 // The DCC session id will be returned in this variable
 irc_dcc_t dccid;
 
 // Initiate sending of file "/etc/passwd" via DCC chat to the IRC user "john"
 if ( irc_dcc_sendfile( session, 0, "john", "/etc/passwd", callback_dcc_send_file, &dccid ) )
   // report error

Now you can proceed with other tasks. When John accepts the request, the file will be sent and callback_dcc_send_file() will be called
each time a piece of file is sent. The callback will also be called when the file has been sent, or when sending was terminated 
because of network error.


Receive a file via DCC
**********************

To receive the file via DCC a remote user must initiate the DCC request to send you a file. To receive this request your application 
should implement the :c:member:`event_dcc_send_req` event. The callback could be implemented as following:

.. sourcecode:: c

 void callback_event_dcc_file( irc_session_t * session, const char * nick, const char * addr, const char * filename, unsigned long size, irc_dcc_t dccid )
 {
     // User 'nick' from the IP address 'addr' tries to initiate the DCC chat with us.
     // Store this information in the application internal queue together with the dccid so the callback can return
     dcc_queue.store( dccid, "CHAT from " + nick + " IP address: " + addr + ", filename " + filename  );
 }

If your application does not handle DCC at all you can just call the :c:func:`irc_dcc_decline` function inside the callback.
 
If it does, we only store this information in the callback, and return. This is because the event processing will stop 
until the callback returns, so popping up the dialog asking for the user confirmation would stop further events such as 
channel messages from being processed. Even if your application is automatic and doesn't pop up dialogs it is still better to
separate the chat logic from the callback logic.

Somewhere later the application would check the queue in the GUI thread, get this information, and pop up the dialog asking the user
feedback. Then if the chat request was accepted, the application would call the :c:func:`irc_dcc_accept` function, and if it was
declined, the application would call the :c:func:`irc_dcc_decline` function. Both functions will accept the *dccid* which identifies 
this specific request:

.. sourcecode:: c

 // Somewhere in the GUI thread
 if ( !dcc_queue.empty() )
 {
     // Get the DCC information and show the dialog to the user
     irc_dcc_t dccid = dcc_chat_queue.top().dccid;
     
     ...
     
     // React to the user entry
     if ( dialog.isAccepted() )
         irc_dcc_accept( session, dccid, 0, dcc_callback );
     else
         irc_dcc_decline( session, dccid );
 }

Note that it is not possible to request a remote user to send you a file.

Handling colors
^^^^^^^^^^^^^^^

.. _color_stripping:

Stripping colors from the message
*********************************

If your bot reacts on the text messages, you need to strip down the colors from the text messages before processing them. Otherwise the user sending
the colored message won't get the same reaction as the user who doesn't use colors, and some users use colors by default.

Use the :c:func:`irc_color_strip_from_mirc` function to strip the ANSI colors from the text message. It does not modify the message which doesn't use colors.


Color conversion
****************

The library supports color translation, and can convert colors between the ANSI colors used by the IRC clients and their textual representation.
Colors usage is typically limited to the messages and user specified reasons. You cannot use colors as part of your nick or channel name.

Use the :c:func:`irc_color_convert_from_mirc` function to convert colors from ANSI to the library textual representation, and :c:func:`irc_color_convert_to_mirc`
to convert the library textual representation of colors into ANSI. 

Do not forget to free() the returned pointer once it is not used anymore.

Miscellaneous
^^^^^^^^^^^^^

Tracking user nicks
*******************

If your application maintains some user-specific quotas, it is important to track the nick changes. Since the nick is the only identifier 
available to you, each time the user changes the nick you need to update your quota database. To do so you need to intercept the :c:member:`event_nick`
event. See the examples/censor.c for details.
