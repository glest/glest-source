
Functions
~~~~~~~~~

This section describes the functions defined in the library which are grouped by the purpose.


Library initialization and shutdown
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


irc_create_session
******************

**Prototype:**

.. c:function:: irc_session_t * irc_create_session( irc_callbacks_t * callbacks )

**Parameters:**

+---------------------------------------------------------------------------------------------------------------------------------------+
| *callbacks* | Event callbacks structure, which defines several callbacks, which will be called on appropriate events. Cannot be NULL. |
+---------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

Creates and initiates a new IRC session. Every session represents a single user connection to a single IRC server, and possibly to one or more users via DCC. 
Almost every library function requires this object to be passed to, and therefore this function should be called first. 
Multiple sessions could be allocated to support multiple connections.

When it is not needed anymore, the session must be destroyed by calling the :c:func:`irc_destroy_session` function.

**Return value:**

An :c:type:`irc_session_t` object, or 0 if creation failed. Usually, failure is caused by out of memory error.

**Thread safety:**

This function can be called simultaneously from multiple threads. Same callback structure may be reused by multiple threads.


irc_destroy_session
*******************

**Prototype:**

.. c:function:: void irc_destroy_session (irc_session_t * session)

**Parameters:**

+---------------------------------------------------------------------------------------------------------------------------------------+
| *session* | The IRC session handle                                                                                                    |
+---------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function destroys an IRC session, closes the connection to the IRC server, and frees all the used resources. After calling this function you should not use this session object anymore.

**Thread safety:**

This function can be called simultaneously from multiple threads.




Connecting, disconnecting and running the main event loop
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

irc_connect6
************

**Prototype:**

.. c:function:: int irc_connect6 (irc_session_t * session, const char * server, unsigned short port, const char * password, const char * nick, const char * username, const char * realname)

irc_connect
***********

**Prototype:**

.. c:function:: int irc_connect (irc_session_t * session, const char * server, unsigned short port, const char * password, const char * nick, const char * username, const char * realname)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *server*    | IP address or the host name of the server. If prefixed with #, the library will try to establish the SSL connection     |
|             | IPv4 address should be in numeric form such as 154.23.112.33; IPv6 address should be in IPv6 form                       |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *port*      | Port number to connect to, usually 6667                                                                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *password*  | IRC server password, if the server requires it. May be NULL, in this case password will not be send to the IRC          |
|             | server. Vast majority of IRC servers do not require passwords. This is NOT NickServ/ChanServ password                   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Nick which will be used to log into the IRC server. Cannot be NULL                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *username*  | Username of the Unix account which is used to connect to the IRC server. This is for information only, will be shown in |
|             | "user properties" dialogs and returned by /whois request. Can be NULL in which case "nobody" would be used              |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *realname*  | A real name of the person, who connects to the IRC. In reality nobody uses this field for that. Instead this field is   |
|             | used as user self-description, advertising, or other purposes. This information also will be shown in "user properties" |
|             | dialogs and returned by /whois request. May be NULL, in this case "noname" will be used                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function initiates the connection to the IPv4 (irc_connect) or IPv6 (irc_connect6) IRC server. The server could be specified either by an IP address or by the DNS name. 
The irc_connect6 works only if the library was built with the IPv6 support.

If the library was built with the OpenSSL support, and the IP address or the host name is prefixed by a hash, such as ``"#irc.example.com"``, the library attempts to establish the SSL connection.

The connection is established asynchronously, and the :c:member:`event_connect` is called once the connection is established.

A single IRC session object can only be connected to a single IRC server and only with a single nick, meaning it is not possible to have multiple nicks sharing a single connection.

**Return value:**

Returns 0 if the connection is initiated successfully. This doesn't mean the connection is established - the :c:member:`event_connect` is called when it happens. If the connection cannot be established, 
either :c:func:`irc_run` or :c:func:`irc_process_select_descriptors` will return an error.

**Thread safety:**

This function can be called simultaneously from multiple threads, but not using the same session object.



irc_disconnect
**************

**Prototype:**

.. c:function:: void irc_disconnect (irc_session_t * session)

**Parameters:**

+---------------------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+---------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function closes the IRC connection. After that connection is closed, if the libirc was looped in the :c:func:`irc_run` loop, it automatically leaves the loop and :c:func:`irc_run` returns.


**Thread safety:**

This function can be called simultaneously from multiple threads, but not using the same session object.



irc_is_connected
****************

**Prototype:**

.. c:function:: int irc_is_connected (irc_session_t * session)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Return value:**

This function returns 1 if the connection to the IRC server is established or 0 if it is not.


**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_run
*******

**Prototype:**

.. c:function:: int irc_run (irc_session_t * session)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function enters into forever loop, processing the IRC events, and calling the relevant callbacks. This function will not return 
until the server connection is terminated - either by server, or by calling :c:type:`irc_cmd_quit`. This function should only be used 
if you use a single IRC session and don't need asynchronous request processing (i.e. your bot just reacts on the events, and doesn't 
generate it asynchronously). Even in last case, you still can call this function and start the asynchronous thread in :c:member:`event_connect` handler.
See the examples.

**Return value:**

This function returns a nonzero value if the connection to the IRC server could not be established, or was terminated.

**Thread safety:**

This function cannot be called from multiple threads. Use :c:func:`irc_add_select_descriptors` and :c:func:`irc_process_select_descriptors` instead.


irc_add_select_descriptors
**************************

**Prototype:**

.. c:function:: int irc_add_select_descriptors (irc_session_t * session, fd_set *in_set, fd_set *out_set, int * maxfd)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *in_set*    | fd_set input descriptor set for select()                                                                                |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *out_set*   | fd_set output descriptor set for select()                                                                               |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *maxfd*     | Largest descriptor already in all the sets. Will be updated if libirc adds larger number to the FD_SET array            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function should be used after you called :c:func:`irc_connect`. It is useful when you have your own select-based event processing loop. To use it 
you should put your own descriptors into the sets, call this function to add the library descriptor(s) into the set, and then call select(). 
When it returns, you should call :c:func:`irc_process_select_descriptors` which will handle the events and calls your callbacks(!). Then you can process 
your sockets events from set. See the example.

What if you use epoll? :ref:`See the FAQ <faq_epoll>`
 
**Return value:**

This function returns a nonzero value if the :c:func:`irc_connect` was not called before calling this function.

**Thread safety:**

This function can be called simultaneously from multiple threads, but it rarely makes sense.



irc_process_select_descriptors 
******************************

**Prototype:**

.. c:function:: int irc_process_select_descriptors (irc_session_t * session, fd_set *in_set, fd_set *out_set)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *in_set*    | fd_set input descriptor set for select()                                                                                |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *out_set*   | fd_set output descriptor set for select()                                                                               |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function should be used in pair with :c:func:`irc_add_select_descriptors` function, which documentation describes how they work together.

Note that while processing the events this function calls your callbacks and it will not return until all your callbacks return. Keep that in mind
if you pop up a dialog in your application, such as a DCC CHAT or DCC SEND confirmation dialog.

**Return value:**

Return code 0 means success. Other value means error, the error code may be obtained through irc_errno().

**Thread safety:**

This function can be called simultaneously from multiple threads for different IRC session objects only.



Managing the IRC channels: joining, leaving, inviting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

irc_cmd_join
************

**Prototype:**

.. c:function:: int irc_cmd_join (irc_session_t * session, const char * channel, const char * key)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | Channel name to join. Cannot be NULL.                                                                                   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *key*       | Secret key for the channel. Can be NULL if not needed                                                                   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

Use this function to join the new IRC channel. If the channel does not exist, it will be automatically created by the IRC server. 
Note that to JOIN the password-protected channel, you must know the password, and specify it in the key argument.
If join is successful, the :c:member:`event_join` will be called (with your nick as the origin), then typically the :c:member:`event_topic` is be called and then you 
receive the list of users who are on the channel (by using LIBIRC_RFC_RPL_NAMREPLY), which will include the user who just joined.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_BANNEDFROMCHAN
 - LIBIRC_RFC_ERR_INVITEONLYCHAN
 - LIBIRC_RFC_ERR_BADCHANNELKEY
 - LIBIRC_RFC_ERR_CHANNELISFULL
 - LIBIRC_RFC_ERR_BADCHANMASK
 - LIBIRC_RFC_ERR_NOSUCHCHANNEL
 - LIBIRC_RFC_ERR_TOOMANYCHANNELS
 
**Thread safety:**

This function can be called simultaneously from multiple threads.



irc_cmd_part
************

**Prototype:**

.. c:function:: int irc_cmd_part (irc_session_t * session, const char * channel)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | Channel name to leave. Cannot be NULL.                                                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

Use this function to leave the IRC channel you've already joined to. An attempt to leave the channel you aren't in results a LIBIRC_RFC_ERR_NOTONCHANNEL server error.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NOSUCHCHANNEL
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 
**Thread safety:**

This function can be called simultaneously from multiple threads.



irc_cmd_invite
**************

**Prototype:**

.. c:function:: int irc_cmd_invite (irc_session_t * session, const char * nick, const char * channel)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Nick name of the user to invite                                                                                         |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | Channel name to join. Cannot be NULL                                                                                    |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to invite someone to invite-only channel. "Invite-only" is a channel mode, which restricts anyone, except invided, to join this channel. 
After invitation, the user could join this channel. The user, who is invited, will receive the :c:member:`event_invite` event. Note that you must be a channel operator to invite the users.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

On success one of the following replies returned:
 - LIBIRC_RFC_RPL_INVITING
 - LIBIRC_RFC_RPL_AWAY

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NEEDMOREPARAMS
 - LIBIRC_RFC_ERR_NOSUCHNICK
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_ERR_USERONCHANNEL
 - LIBIRC_RFC_ERR_ERR_CHANOPRIVSNEEDED

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_names
*************

**Prototype:**

.. c:function:: int irc_cmd_names (irc_session_t * session, const char * channel);

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | A channel name(s) to obtain user list. Multiple channel names must be separated by a comma                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to to ask the IRC server for the list of the users who are joined the specified channel. You can list all nicknames 
that are visible to you on any channel that you can see. The list of users will be returned using LIBIRC_RFC_RPL_NAMREPLY and LIBIRC_RFC_RPL_ENDOFNAMES numeric codes.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

The channel names are returned by :c:member:`event_numeric` event using the following reply codes:
 - LIBIRC_RFC_RPL_NAMREPLY
 - LIBIRC_RFC_RPL_ENDOFNAMES

**Thread safety:**

This function can be called simultaneously from multiple threads.



irc_cmd_list
************

**Prototype:**

.. c:function:: int irc_cmd_list (irc_session_t * session, const char * channel)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | A channel name(s) to list. Multiple channel names must be separated by a comma. If NULL, all channels are listed        |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to ask the IRC server for the active (existing) channels list. The list will be returned using the LIBIRC_RFC_RPL_LISTSTART, 
multiple LIBIRC_RFC_RPL_LIST, and LIBIRC_RFC_RPL_LISTEND event sequence. Note that "private" channels are listed (without their topics) as channel
"Prv" unless the client generating the LIST query is actually on that channel. Likewise, secret channels are not listed at all unless the client 
is active at the channel in question.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

The list of channels is returned by :c:member:`event_numeric` event using the following reply codes:
 - LIBIRC_RFC_RPL_LISTSTART
 - LIBIRC_RFC_RPL_LISTEND
 - LIBIRC_RFC_RPL_LIST

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_topic
*************

**Prototype:**

.. c:function:: int irc_cmd_topic (irc_session_t * session, const char * channel, const char * topic)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | A channel name                                                                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *topic*     | A new channel topic. If NULL, the old topic would be returned and nothing would change. To set the empty topic use ""   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to change or view the topic (title) of a channel. Note that depending on *+t* channel mode, you may be required to be 
a channel operator to change the channel topic.

If the command succeeds, the IRC server will generate a LIBIRC_RFC_RPL_NOTOPIC or LIBIRC_RFC_RPL_TOPIC message, containing either the old 
or changed topic. Also the IRC server can (but does not have to) generate the non-RFC LIBIRC_RFC_RPL_TOPIC_EXTRA message, containing the 
nick of person who changed the topic, and the date/time of the last change.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

The topic information is returned using one of following reply codes:
 - LIBIRC_RFC_RPL_NOTOPIC
 - LIBIRC_RFC_RPL_TOPIC
 
If the topic change was requested and it was successfully changed, the :c:member:`event_topic` is generated as well.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NEEDMOREPARAMS
 - LIBIRC_RFC_ERR_CHANOPRIVSNEEDED
 - LIBIRC_RFC_ERR_NOTONCHANNEL

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_channel_mode
********************

**Prototype:**

.. c:function:: int irc_cmd_channel_mode (irc_session_t * session, const char * channel, const char * mode)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | A channel name                                                                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *mode*      | A mode to change. If NULL, the channel mode is not changed but the old mode is returned                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to is used to change or view the channel modes. Note that only the channel operators can change the channel mode.

Channel mode is represended by the multiple letters combination. Every letter has its own meaning in channel modes. Most channel mode letters 
are boolean (i.e. could only be set or reset), but a few channel mode letters accept a parameter. All channel options are set by adding a 
plus sign before the letter, and reset by adding a minus sign before the letter.

Here is the list of 'standard' channel modes:

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| o nickname  | gives (+o nickname) to, or takes (-o nickname) the channel operator privileges from a *nickname*. This mode affects     |
|             | the users in channel, not the channel itself. Examples: "+o tim", "-o watson"                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| p           | sets (+p) or resets (-p) private channel flag. Private channels are shown in channel list as 'Prv', without the topic   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| s           | sets (+s) or resets (-s) secret channel flag. Secret channels aren't shown in channel list at all                       |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| i           | sets (+i) or resets (-i) invite-only channel flag. When the flag is set, only the people who are invited by the         |
|             | :c:func:`irc_cmd_invite` can join this channel                                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| t           | allows (+t) or denies (-t) changing the topic by the non-channel operator users. When the flag is set, only the channel |
|             | operators can change the channel topic                                                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| n           | sets (+n) or resets (-n) the protection from the users who did not join the channel. When the +n mode is set, only the  |
|             | users who have joined the channel can send the messages to the channel                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+ 
| m           | sets (+m) or resets (-m) the moderation of the channel. When the moderation mode is set, only channel operators and the |
|             | users who have +v user mode can speak in the channel                                                                    |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| v nickname  | gives (+v nick) or takes (-v nick) from user the ability to speak on a moderated channel. Examples: "+v bob", "-v joy"  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| l number    | sets (+l 20) or removes (-l) the restriction of maximum number of users allowed in channel. When the restriction is set |
|             | and there is a number of users in the channel, no one can join the channel anymore                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| k key       | sets (+k password) or removes (-k) the password from the channel. When the restriction is set, any user joining the     |
|             | channel required to provide a channel key                                                                               |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| b mask      | sets (+b *!*@*.mil) or removes (-b *!*@*.mil) the ban mask on a user to keep him out of channel. Note that to remove the|
|             | ban you must specify the ban mask to remove, not just "-b".                                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

Note that the actual list of channel modes depends on the IRC server, and can be bigger. If you know the popular channel modes which aren't listed here - please contact me

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

The old mode information is returned by using following numeric codes:
 - LIBIRC_RFC_RPL_CHANNELMODEIS
 - LIBIRC_RFC_RPL_BANLIST
 - LIBIRC_RFC_RPL_ENDOFBANLIST

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NEEDMOREPARAMS
 - LIBIRC_RFC_ERR_CHANOPRIVSNEEDED
 - LIBIRC_RFC_ERR_NOSUCHNICK
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_KEYSET
 - LIBIRC_RFC_ERR_UNKNOWNMODE
 - LIBIRC_RFC_ERR_NOSUCHCHANNEL

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_user_mode
*****************

**Prototype:**

.. c:function:: int irc_cmd_user_mode (irc_session_t * session, const char * mode)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *mode*      | A mode to change. If NULL, the user mode is not changed but the old mode is returned                                    |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to change or view the user modes. Note that, unlike channel modes, some user modes cannot be changed at all.

User mode is represended by the letters combination. All the user mode letters are boolean (i.e. could only be set or reset), they are set 
by adding a plus sign before the letter, and reset by adding a minus sign before the letter.

Here is the list of 'standard' user modes:

+---+-----------------------------------------------------------------------------------------------------------------------------------+
| o | represents an IRC operator status. Could not be set directly (but can be reset though), to set it use the IRC \a OPER command     |
+---+-----------------------------------------------------------------------------------------------------------------------------------+
| i | if set, marks a user as 'invisible' - that is, not seen by lookups if the user is not in a channel                                |
+---+-----------------------------------------------------------------------------------------------------------------------------------+
| w | if set, marks a user as 'receiving wallops' - special messages generated by IRC operators using WALLOPS command                   |
+---+-----------------------------------------------------------------------------------------------------------------------------------+
| s | if set, marks a user for receipt of server notices                                                                                |
+---+-----------------------------------------------------------------------------------------------------------------------------------+
| r | NON-STANDARD MODE. If set, user has been authenticated with the NickServ IRC service                                              |
+---+-----------------------------------------------------------------------------------------------------------------------------------+
| x | NON-STANDARD MODE. If set, user's real IP is masked by the IRC server                                                             |
+---+-----------------------------------------------------------------------------------------------------------------------------------+

Note that the actual list of user modes depends on the IRC server, and can be bigger. If you know the popular user modes, which aren't mentioned here - please contact me.


**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

The old mode information is returned by using the numeric code LIBIRC_RFC_RPL_UMODEIS:

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NEEDMOREPARAMS
 - LIBIRC_RFC_ERR_NOSUCHNICK
 - LIBIRC_RFC_ERR_UNKNOWNMODE
 - LIBIRC_RFC_ERR_USERSDONTMATCH
 - LIBIRC_RFC_ERR_UMODEUNKNOWNFLAG

**Thread safety:**

This function can be called simultaneously from multiple threads.

irc_cmd_kick
************

**Prototype:**

.. c:function:: int irc_cmd_kick (irc_session_t * session, const char * nick, const char * channel, const char * reason);

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | The nick to kick                                                                                                        |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *channel*   | The channel to kick the nick from                                                                                       |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | If not NULL, the reason to kick the user                                                                                |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to kick a person out of channel. Note that you must be a channel operator to kick anyone from a channel.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

If the command succeed, the :c:member:`event_kick` will be generated.

If the command failed, one of the following :c:member:`event_numeric` responses will be generated:
 - LIBIRC_RFC_ERR_NEEDMOREPARAMS
 - LIBIRC_RFC_ERR_BADCHANMASK
 - LIBIRC_RFC_ERR_NOSUCHCHANNEL
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_CHANOPRIVSNEEDED

**Thread safety:**

This function can be called simultaneously from multiple threads.


Sending the messages, notices, /me messages and working with CTCP
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

irc_cmd_msg
***********

**Prototype:**

.. c:function:: int irc_cmd_msg (irc_session_t * session, const char * nch, const char * text)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nch*       | Target nick or target channel                                                                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *text*      | Message text                                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to send the message to the channel or privately to another nick. "Privately" here means the message is not posted to the public,
but the message still goes through the IRC server and could be seen by the IRC netwrk operators. The message target is determined by the *nch* argument: 
if it is a nick, this will be a private message, but if it is a channel name it will be posted into the channel. 

The protocol does not require you to join the channel to post the message into it, but most channels set the channel mode preventing you from posting into a channel unless you join it.
 
**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed. You need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

If the command succeed, no event is typically generated except the possibility of LIBIRC_RFC_RPL_AWAY. 

However if the command failed, one of the following numeric events may be generated:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK
 
**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_me
**********

**Prototype:**

.. c:function:: int irc_cmd_me (irc_session_t * session, const char * nch, const char * text) 

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nch*       | Target nick or target channel                                                                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *text*      | Message text                                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+


**Description:**

This function is used to send the /me message (CTCP ACTION) to the channel or privately to another nick. "Privately" here means the message is not posted to the public,
but the message still goes through the IRC server and could be seen by the IRC netwrk operators. The message target is determined by the *nch* argument: 
if it is a nick, this will be a private message, but if it is a channel name it will be posted into the channel. 

The protocol does not require you to join the channel to post the message into it, but most channels set the channel mode preventing you from posting into a channel unless you join it.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed. You need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

If the command succeed, no event is typically generated except the possibility of LIBIRC_RFC_RPL_AWAY. 

However if the command failed, one of the following numeric events may be generated:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK
 
**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_notice
**************

**Prototype:**

.. c:function:: int irc_cmd_notice (irc_session_t * session, const char * nch, const char * text)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nch*       | Target nick or target channel                                                                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *text*      | Message text                                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to send the notice to the channel or privately to another nick. "Privately" here means the message is not posted to the public,
but the message still goes through the IRC server and could be seen by the IRC netwrk operators. The message target is determined by the *nch* argument: 
if it is a nick, this will be a private message, but if it is a channel name it will be posted into the channel. 

The protocol does not require you to join the channel to post the notice into it, but most channels set the channel mode preventing you from posting into a channel unless you join it.

The only difference between a message and a notice is that the RFC explicitly says the automatic bots must not reply to NOTICE automatically.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

If the command succeed, no event is typically generated except the possibility of LIBIRC_RFC_RPL_AWAY. 

However if the command failed, one of the following numeric events may be generated:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_ctcp_request
********************

**Prototype:**

.. c:function:: int irc_cmd_ctcp_request (irc_session_t * session, const char * nick, const char * request)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Target nick                                                                                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *request*   | CTCP request tex                                                                                                        |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to send a CTCP request. There are four CTCP requests supported by most IRC clients:
 
 * VERSION - get the client software name and version
 * FINGER  - get the client username, host and real name.
 * PING    - get the client delay.
 * TIME    - get the client local time.

Some clients may support other requests. The RFC does not list the requests and does not mandate any CTCP support.

If you send the CTCP request, make sure you define the handler for the :c:member:`event_ctcp_rep` to process the reply;

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_ctcp_reply
******************

**Prototype:**

.. c:function:: int irc_cmd_ctcp_reply (irc_session_t * session, const char * nick, const char * reply)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Target nick                                                                                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *reply*     | CTCP reply                                                                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to send a reply to the CTCP request received from :c:member:`event_ctcp_req` event. Note that you will not receive this event
unless you specify your own handler during the IRC session initialization.
 
**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK

**Thread safety:**

This function can be called simultaneously from multiple threads.



Miscellaneous: library version, raw data, changing nick, quitting
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

irc_cmd_nick
************

**Prototype:**

.. c:function:: int irc_cmd_nick (irc_session_t * session, const char * newnick)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | New nick                                                                                                                |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to change your current nick to another nick. Note that such a change is not always possible; for example 
you cannot change nick to the existing nick, or (on some servers) to the registered nick.
 
**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

If the operation succeed, the server will send the :c:member:`event_nick` event. If not, it will send a numeric error. Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NONICKNAMEGIVEN
 - LIBIRC_RFC_ERR_ERRONEUSNICKNAME
 - LIBIRC_RFC_ERR_NICKNAMEINUSE
 - LIBIRC_RFC_ERR_NICKCOLLISION

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_whois
*************

**Prototype:**

.. c:function:: int irc_cmd_whois (irc_session_t * session, const char * nick)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Nick or comma-separated list of nicks to query the information about                                                    |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function queries various information about the nick. The amount of information depends on the IRC server but typically includes username, 
real name (as defined by the client at login), the IRC server used, the channels user is in, idle time, away mode and so on.


**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate :c:member:`event_numeric` event.

If the request succeed, the information is returned through the following numeric codes which return the information:
 - LIBIRC_RFC_RPL_WHOISUSER
 - LIBIRC_RFC_RPL_WHOISCHANNELS
 - LIBIRC_RFC_RPL_WHOISSERVER
 - LIBIRC_RFC_RPL_AWAY
 - LIBIRC_RFC_RPL_WHOISOPERATOR
 - LIBIRC_RFC_RPL_WHOISIDLE
 - LIBIRC_RFC_RPL_ENDOFWHOIS - this event terminates the WHOIS information

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NOSUCHSERVER
 - LIBIRC_RFC_ERR_NOSUCHNICK
 - LIBIRC_RFC_ERR_NONICKNAMEGIVEN
 
**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_cmd_quit
************

**Prototype:**

.. c:function:: int irc_cmd_quit (irc_session_t * session, const char * reason)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *reason*    | If not NULL, the reason to quit                                                                                         |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**
This function sends the QUIT command to the IRC server. This command forces the IRC server to close the IRC connection, and terminate the session.

The difference between this command and calling the irc_disconnect is that this command allows to specify the reason to quit which will be shown 
to all the users in the channels you joined. Also it would make it clear that you left the IRC channels by purpose, and not merely got disconnected.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_send_raw
************

**Prototype:**

.. c:function:: int irc_send_raw (irc_session_t * session, const char * format, ...);

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *format*    | printf-type formatting string followed by the format arguments                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function sends the raw data as-is to the IRC server. Use it to generate a server command, which is not (yet) provided by libircclient directly.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_target_get_nick
*******************

**Prototype:**

.. c:function:: void irc_target_get_nick (const char * origin, char *nick, size_t size)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *origin*    | Nick in the common IRC server format such as tim!root\@mycomain.com                                                     |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Buffer to retrieve the parsed nick name                                                                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *size*      | Size of the *nick* buffer. If the parsed nick is larger than the buffer size it will be truncated                       |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

For most events IRC server returns 'origin' (i.e. the person, who generated this event) in so-called "common" form, like nick!host@domain.
However, all the irc_cmd_* functions require just a nick. This function parses this origin, and retrieves the nick, storing it into the user-provided buffer.

A buffer of size 128 should be enough for most nicks.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_target_get_host
*******************

**Prototype:**

.. c:function:: void irc_target_get_host (const char * target, char *host, size_t size)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *origin*    | Nick in the common IRC server format such as tim!root\@mycomain.com                                                     |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *host*      | Buffer to retrieve the parsed hostname                                                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *size*      | Size of the *host* buffer. If the parsed nick is larger than the buffer size it will be truncated                       |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

For most events IRC server returns 'origin' (i.e. the person, who generated this event) in so-called "common" form, like nick!host\@domain.
This function parses this origin, and retrieves the host, storing it into the user-provided buffer.

**Thread safety:**

This function can be called simultaneously from multiple threads.



DCC initiating and accepting chat sessions, sending and receiving files
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

irc_dcc_chat
************

**Prototype:**

.. c:function:: int irc_dcc_chat(irc_session_t * session, void * ctx, const char * nick, irc_dcc_callback_t callback, irc_dcc_t * dccid)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *ctx*       | User-defined context which will be passed to the callback. May be NULL                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Target nick                                                                                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *callback*  | DCC callback which will be used for DCC and chat events                                                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | If this function succeeds, the DCC session identifier is stored in this field                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function requests a DCC CHAT between you and other IRC user. DCC CHAT is like private chat, but it goes directly between two users, 
and bypasses the IRC server. DCC CHAT request must be accepted by other side before you can send anything.

When the chat is accepted, declined, terminated, or some data is received, the *callback* function is called. To be specific, 
the callback will be called when:

 * The chat request is accepted;
 * The chat request is denied;
 * The new chat message is received;
 * The chat is terminated by the remote party;

See the details in :c:type:`irc_dcc_callback_t` declaration.

**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_dcc_msg
***********

**Prototype:**

.. c:function:: int irc_dcc_msg (irc_session_t * session, irc_dcc_t dccid, const char * text)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | DCC session identifier for the DCC CHAT session which is active                                                         |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *text*      | NULL-terminated message to send                                                                                         |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function is used to send the DCC CHAT message to an active DCC CHAT. To be active, DCC CHAT request must be initiated by one side and accepted by another side.

**Return value:**

Return code 0 means success. Other value means error, the error code may be obtained through irc_errno().

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_dcc_accept
**************

**Prototype:**

.. c:function:: int irc_dcc_accept (irc_session_t * session, irc_dcc_t dccid, void * ctx, irc_dcc_callback_t callback)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | DCC session identifier returned by the callback                                                                         |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *ctx*       | User-defined context which will be passed to the callback. May be NULL                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *callback*  | DCC callback which will be used for DCC and chat events                                                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function accepts a remote DCC chat or file transfer request. After the request is accepted the *callback* will be called for the further DCC events,
including the termination of the DCC session. See the :c:type:`DCC callback information <irc_dcc_callback_t>`.

This function should be called only after either :c:member:`event_dcc_chat_req` or :c:member:`event_dcc_send_req` events are received. You don't have to call irc_dcc_accept()
or irc_dcc_decline() immediately in the event processing function - you may just store the *dccid* and return, and call those functions later. However to
prevent memory leaks you must call either irc_dcc_decline() or irc_dcc_accept() for any incoming DCC request within 60 seconds after receiving it.

**Return value:**

Return code 0 means success. Other value means error, the error code may be obtained through :c:func:`irc_errno`.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_dcc_decline
***************

**Prototype:**

.. c:function:: int irc_dcc_decline (irc_session_t * session, irc_dcc_t dccid)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | DCC session identifier returned by the callback                                                                         |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function declines a remote DCC chat or file transfer request.

This function should be called only after either :c:member:`event_dcc_chat_req` or :c:member:`event_dcc_send_req` events are received. You don't have to call irc_dcc_accept()
or irc_dcc_decline() immediately in the event processing function - you may just store the *dccid* and return, and call those functions later. However to
prevent memory leaks you must call either irc_dcc_decline() or irc_dcc_accept() for any incoming DCC request within 60 seconds after receiving it.

Do not use this function to forecefully close the previously accepted or initiated DCC session. Use :c:func:`irc_dcc_destroy` instead.

**Return value:**

Return code 0 means success. Other value means error, the error code may be obtained through :c:func:`irc_errno`.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_dcc_sendfile
****************

**Prototype:**

.. c:function:: int irc_dcc_sendfile (irc_session_t * session, void * ctx, const char * nick, const char * filename, irc_dcc_callback_t callback, irc_dcc_t * dccid)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *ctx*       | User-defined context which will be passed to the callback. May be NULL                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *nick*      | Target nick                                                                                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *filename*  | Full path to the file which will be sent. Must be an existing file                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *callback*  | DCC callback which will be used for DCC and chat events                                                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | If this function succeeds, the DCC session identifier is stored in this field                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function generates a DCC SEND request to send the file. When it is accepted, the file is sent to the remote party, and the DCC session is
closed. The send operation progress and result can be checked in the callback. See the :c:type:`DCC callback information <irc_dcc_callback_t>`.
 
**Return value:**

Return code 0 means the command was sent to the IRC server successfully. This does not mean the operation succeed, and you need to wait 
for the appropriate event or for the error code via :c:member:`event_numeric` event.

Possible error responces for this command from the RFC1459:
 - LIBIRC_RFC_ERR_NORECIPIENT
 - LIBIRC_RFC_ERR_NOTEXTTOSEND
 - LIBIRC_RFC_ERR_CANNOTSENDTOCHAN
 - LIBIRC_RFC_ERR_NOTONCHANNEL
 - LIBIRC_RFC_ERR_NOTOPLEVEL
 - LIBIRC_RFC_ERR_WILDTOPLEVEL
 - LIBIRC_RFC_ERR_TOOMANYTARGETS
 - LIBIRC_RFC_ERR_NOSUCHNICK

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_dcc_destroy
***************

**Prototype:**

.. c:function:: int irc_dcc_destroy (irc_session_t * session, irc_dcc_t dccid)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | DCC session identifier of a session to destroy                                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function closes the DCC connection (if available), and destroys the DCC session, freeing the used resources. It can be called anytime, even from callbacks or from different threads.

Note that when DCC session is finished (either with success or failure), you should not destroy it - it will be destroyed automatically.

**Return value:**

Return code 0 means success. Other value means error, the error code may be obtained through :c:func:`irc_errno`.

**Thread safety:**

This function can be called simultaneously from multiple threads.



Handling the colored messages
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


irc_color_strip_from_mirc
*************************

**Prototype:**

.. c:function:: char * irc_color_strip_from_mirc (const char * message)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *message*   | Original message with colors                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function strips all the ANSI color codes from the message, and returns a new message with no color information. Useful for the bots which react to strings,
to make sure the bot is not confused if the string uses colors.

This function does not modify the message which doesn't use colors.

**Return value:**

Returns a new message with stripped color codes. Note that the memory for the new message is allocated using malloc(), so you should free 
it using free() when it is not used anymore. If memory allocation failed, returns 0.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_color_convert_from_mirc
***************************

**Prototype:**

.. c:function:: char * irc_color_convert_from_mirc (const char * message)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *message*   | Original message with colors                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function converts all the color codes and format options to libircclient internal colors.

**Return value:**

Returns a pointer to the new message with converted ANSI color codes and format options. See the irc_color_convert_to_mirc_ help for details.
 
Note that the memory for the new message is allocated using malloc(), so you should free it using free() when it is not used anymore. 
If memory allocation failed, returns 0.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_color_convert_to_mirc
*************************

**Prototype:**

.. c:function:: char * irc_color_convert_to_mirc (const char * message)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *message*   | Original message with colors                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function converts all the color codes and format options from internal libircclient colors to ANSI used by mIRC and other IRC clients.

**Return value:**

Returns a new message with converted color codes and format options, or 0 if memory could not be allocated. Note that the memory for the 
new message is allocated using malloc(), so you should free it using free() when it is not used anymore.

**Thread safety:**

This function can be called simultaneously from multiple threads.

The color system of libircclient is designed to be easy to use, and portable between different IRC clients. Every color or format option 
is described using plain text commands written between square brackets. 

The possible codes are:
 - [B] ... [/B] - bold format mode. Everything between [B] and [/B] is written in **bold**.
 - [I] ... [/I] - italic/reverse format mode. Everything between [I] and [/I] is written in *italic*, or reversed (however, because some clients are incapable of rendering italic text, most clients display this as normal text with the background and foreground colors swapped).
 - [U] ... [/U] - underline format mode. Everything between [U] and [/U] is written underlined.
 - [COLOR=RED] ... [/COLOR] - write the text using specified foreground color. The color is set by using the COLOR keyword, and equal sign followed by text color code (see below).
 - [COLOR=RED/BLUE] ... [/COLOR] - write the text using specified foreground and background color. The color is set by using the COLOR keyword, an equal sign followed by text foreground color code, a dash and a text background color code.

The following colors are supported:
 - WHITE
 - BLACK
 - DARKBLUE
 - DARKGREEN
 - RED
 - BROWN
 - PURPLE
 - OLIVE
 - YELLOW
 - GREEN
 - TEAL
 - CYAN
 - BLUE
 - MAGENTA
 - DARKGRAY
 - LIGHTGRAY

Examples of color sequences:
::

 Hello, [B]Tim[/B]. 
 [U]Arsenal[/U] got a [COLOR=RED]red card[/COLOR]
 The tree[U]s[/U] are [COLOR=GREEN/BLACK]green[/COLOR]



Changing the library options
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

irc_get_version
***************

**Prototype:**

.. c:function:: void irc_get_version (unsigned int * high, unsigned int * low)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *high*      | Stores the high version number                                                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *low*       | Stores the low version number                                                                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function returns the libircclient version. You can use the version either to check whether required options are available, or to output the version.
The preferred printf-like format string to output the version is:

``printf ("Version: %d.%02d", high, low);``
 
**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_set_ctx
***********

**Prototype:**

.. c:function:: void irc_set_ctx (irc_session_t * session, void * ctx)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *ctx*       | User-defined context                                                                                                    |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function sets the user-defined context for this IRC session. This context is not used by libircclient. Its purpose is to store session-specific
user data, which may be obtained later by calling irc_get_ctx_. Note that libircclient just carries out this pointer. If you allocate some memory, 
and store its address in ctx (most common usage), it is your responsibility to free it before calling :c:func:`irc_destroy_session`.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_get_ctx
***********

**Prototype:**

.. c:function:: void * irc_get_ctx (irc_session_t * session)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function returns the IRC session context, which was set by irc_set_ctx_. 

**Return value:**

If no context was set, this function returns NULL.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_option_set
**************

**Prototype:**

.. c:function:: void irc_option_set (irc_session_t * session, unsigned int option)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *option*    | One of the :ref:`Libirc options <api_options>` to set                                                                   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function sets the libircclient option, changing libircclient behavior. See the :ref:`options <api_options>` list for the meaning for every option.

**Thread safety:**

This function can be called simultaneously from multiple threads.


irc_option_reset
****************

**Prototype:**

.. c:function:: void irc_option_reset (irc_session_t * session, unsigned int option)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *option*    | One of the :ref:`Libirc options <api_options>` to set                                                                   |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function resets the libircclient option, changing libircclient behavior. See the :ref:`options <api_options>` list for the meaning for every option.

**Thread safety:**

This function can be called simultaneously from multiple threads.


Handling the errors
^^^^^^^^^^^^^^^^^^^

irc_errno
*********

**Prototype:**

.. c:function:: int irc_errno (irc_session_t * session)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session handle                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function returns the last error code associated with last operation of this IRC session. Possible error codes are defined in libirc_errors.h

As usual, typical errno rules apply:

 - irc_errno() should be called ONLY if the called function fails;
 - irc_errno() doesn't return 0 if function succeed; actually, the return value will be undefined.
 - you should call irc_errno() IMMEDIATELY after function fails, before calling any other libircclient function.
 
**Return value:**

The error code.

**Thread safety:**

This function can be called simultaneously from multiple threads. Local error code is per IRC context, not per thread.


irc_strerror
************

**Prototype:**

.. c:function:: const char * irc_strerror (int ircerrno)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------+
| *ircerrno*  | IRC error code returned by :c:func:`irc_errno`                                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------+

**Description:**

This function returns the text representation of the given error code.

**Return value:**

Returns an internal English string with a short description of the error code.

**Thread safety:**

This function can be called simultaneously from multiple threads.
