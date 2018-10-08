
Callbacks
~~~~~~~~~

This section describes the callbacks supported by the library.

irc_event_callback_t
^^^^^^^^^^^^^^^^^^^^

**Prototype:**

.. c:type:: typedef void (*irc_event_callback_t) (irc_session_t * session, const char * event, const char * origin, const char ** params, unsigned int count)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *session*   | The IRC session, which generated the event                                                                                                      |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *event*     | The text name of the event. Useful in case a single event handler is used to handle multiple events                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *origin*    | The originator of the event. Depends on the event.                                                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *params*    | Extra parameters, if any, for this event. The number of extra parameters depends on the event, and may be zero.                                 |
|             | Each parameter is a NULL-terminated text string. None of the params can be NULL, but the *params* pointer itself could be NULL for some events. |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *count*     | The number of entries in the *params* argument supplied.                                                                                        |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

Every IRC event generates a callback. This type of callback is universal and is used by almost all IRC events. Depending on the event nature, it can have zero or more parameters. 
For each type of event, the number of provided parameters is fixed, and their meaning is described in the :c:type:`irc_callbacks_t` structure.

Every event has an origin (i.e. who originated the event). In some cases the *origin* variable may be NULL, which indicates that event origin is unknown. The origin usually looks like *nick!host@ircserver*, 
i.e. like *tim!home@irc.server.net*. Such origins can not be used in IRC commands, and need to be stripped (i.e. host and server part should be cut off) before using. This can be done either manually, by 
calling :c:func:`irc_target_get_nick`, or automatically for all the events - by setting the :c:macro:`LIBIRC_OPTION_STRIPNICKS` option with :c:func:`irc_option_set`.



irc_event_dcc_chat_t
^^^^^^^^^^^^^^^^^^^^

**Prototype:**

.. c:type:: typedef void (*irc_event_dcc_chat_t) (irc_session_t * session, const char * nick, const char * addr, irc_dcc_t dccid)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *session*   | IRC session, which generates an event (the one returned by irc_create_session)                                                                  |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *nick*      | User who requested the chat                                                                                                                     |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *addr*      | IP address of the person such as 189.12.34.56                                                                                                   |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | Identifier associated with this request which should be passed to the :c:func:`irc_dcc_accept` / :c:func:`irc_dcc_decline` functions            |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

This callback is called when someone requests DCC CHAT with you. DCC CHAT is the type of chat which goes directly between the clients, instead of going through the IRC server. Since the TCP connection must be
established for it to happen, typically the initiator must either have the public IP or special software on the firewall which handles the necessary port forwarding.

You must respond to the chat request either by calling :c:func:`irc_dcc_accept` to accept it, or by calling :c:func:`irc_dcc_decline` to decline it.
 

irc_event_dcc_send_t
^^^^^^^^^^^^^^^^^^^^

**Prototype:**

.. c:type:: typedef void (*irc_event_dcc_send_t) (irc_session_t * session, const char * nick, const char * addr, const char * filename, unsigned long size, irc_dcc_t dccid)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *session*   | The IRC session, which generates an event (the one returned by irc_create_session)                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *nick*      | The user who requested the chat                                                                                                                 |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *addr*      | The IP address of the person such as 189.12.34.56                                                                                               |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *filename*  | The name of the file the user is trying to send you                                                                                             |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *size*      | The size of the file                                                                                                                            |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *dccid*     | Identifier associated with this request which should be passed to the :c:func:`irc_dcc_accept` / :c:func:`irc_dcc_decline` functions            |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

This callback is called when someone wants to send you a file by using DCC SEND. DCC SEND goes directly between the clients, and requires the TCP connection to be established
established for it to happen. Therefore the initiator must either have the public IP or special software on the firewall which handles the necessary port forwarding.

You must respond to the chat request either by calling :c:func:`irc_dcc_accept` to accept it, or by calling :c:func:`irc_dcc_decline` to decline it.



irc_dcc_callback_t
^^^^^^^^^^^^^^^^^^

**Prototype:**

.. c:type:: typedef void (*irc_dcc_callback_t) (irc_session_t * session, irc_dcc_t id, int status, void * ctx, const char * data, unsigned int length)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *session*   | The IRC session, which generates an event (the one returned by irc_create_session)                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *id*        | The DCC session id                                                                                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *status*    | The DCC connection status. 0 means there is no error, otherwise contains an error code                                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *ctx*       | The user-provided context                                                                                                                       |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *data*      | Data received (if available), otherwise NULL                                                                                                    |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *length*    | Size of the data received if any data                                                                                                           |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

This callback is called for all DCC functions when state change occurs.

For DCC CHAT, the callback is called as following:
  * *status* is :c:macro:`LIBIRC_ERR_CLOSED`: connection is closed by remote peer. After returning from the callback, the DCC session is automatically destroyed
  * *status* is nonzero but not :c:macro:`LIBIRC_ERR_CLOSED`: socket I/O error  (connect error, accept error, recv error, send error). After returning from the callback, the DCC session is automatically destroyed
  * *status* is zero and *length* is zero: the remote side accepted the chat request
  * *status* is zero and *length* is nonzero: new chat message received, *data* contains the message (a null-terminated string), *length* contains the string length without null terminator
  

For DCC SEND, while file is being sent, the callback is called as following:
  * *status* is nonzero: socket I/O error (connect error, accept error, recv error, send error). After returning from the callback, the DCC session is automatically destroyed
  * *status* is zero: another data packet has been sent, *length* contains the total amount of data sent so far, *data* is NULL
  
For DCC RECV, while file is being sending, callback called as following:
  * *status* is nonzero: socket I/O error (connect error, accept error, recv error, send error). After returning from the callback, the DCC session is automatically destroyed.
  * *status* is zero, and *data* is NULL: the file has been received successfully. After returning from the callback, the DCC session is automatically destroyed.
  * *status* is zero, and *data* is not NULL: new data received, *data* contains the data received, *length* contains the amount of data received.
 

irc_eventcode_callback_t
^^^^^^^^^^^^^^^^^^^^^^^^

**Prototype:**

.. c:type:: typedef void (*irc_eventcode_callback_t) (irc_session_t * session, unsigned int event, const char * origin, const char ** params, unsigned int count)

**Parameters:**

+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *session*   | The IRC session, which generates an event (the one returned by irc_create_session)                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *event*     | The numeric code of the event. Useful in case a single event handler is used to handle multiple events                                          |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *origin*    | The originator of the event. Depends on the event.                                                                                              |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *params*    | Extra parameters, if any, for this event. The number of extra parameters depends on the event, and may be zero.                                 |
|             | Each parameter is a NULL-terminated text string. None of the params can be NULL, but the *params* pointer itself could be NULL for some events. |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+
| *count*     | The number of entries in the *params* argument supplied.                                                                                        |
+-------------+-------------------------------------------------------------------------------------------------------------------------------------------------+

**Description:**

This is an advanced callback for those who want to handle events deeper. Most times the IRC server replies to your actions with numeric events. 
Most of those events are error codes, and some are list-start and list-stop markers. Every code has its own set of params; for details you can either experiment, or read RFC 1459 
(don't expect servers to follow it closely though).

Every event has an origin (i.e. who originated the event). In some cases the *origin* variable may be NULL, which indicates that event origin is unknown. The origin usually looks like *nick!host@ircserver*, 
i.e. like *tim!home@irc.server.net*. Such origins can not be used in IRC commands, and need to be stripped (i.e. host and server part should be cut off) before using. This can be done either manually, by 
calling :c:func:`irc_target_get_nick`, or automatically for all the events - by setting the :c:macro:`LIBIRC_OPTION_STRIPNICKS` option with :c:func:`irc_option_set`.
