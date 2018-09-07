
Constants
~~~~~~~~~

This section describes contstants such as options and the error codes.

Errors
^^^^^^

.. c:macro:: LIBIRC_ERR_OK

(0): No error


.. c:macro:: LIBIRC_ERR_INVAL

(1): An invalid value was given for one of the arguments to a function. For example, supplying the NULL value as a channel argument of :c:func:`irc_cmd_join` produces this error.


.. c:macro:: LIBIRC_ERR_RESOLV

(2): The host name supplied for :c:func:`irc_connect` function could not be resolved into valid IP address.
 

.. c:macro:: LIBIRC_ERR_SOCKET

(3): The new socket could not be created or made non-blocking. Usually means that the server is out of resources, or (hopefully not) a bug in libircclient. See also :ref:`faq_err_socket`

.. c:macro:: LIBIRC_ERR_CONNECT

(4): The socket could not connect to the IRC server, or to the destination DCC part. Usually means that either the IRC server is down or its address is invalid. 
For DCC the reason usually is the firewall on your or destination computer, which refuses DCC transfer.

.. c:macro:: LIBIRC_ERR_CLOSED

(5): The IRC connection was closed by the IRC server (which could mean that an IRC operator just have banned you from the server - test your client before connecting to a public server), or the DCC connection
was closed by remote peer - for example, the other side just terminates the IRC application.  Usually it is not an error.


.. c:macro:: LIBIRC_ERR_NOMEM

(6): There are two possible reasons for this error. First is that memory could not be allocated for libircclient internal use, and this error is usually fatal.
Second reason is that the command buffer (which queues the commands ready to be sent to the IRC server) is full, and could not accept more commands yet. 
In the last case you should just wait, and repeat the command later.


.. c:macro:: LIBIRC_ERR_ACCEPT

(7): A DCC chat/send connection from the remote peer could not be accepted. Either the connection was just terminated before it is accepted, or there is a bug in libircclient.
 

.. c:macro:: LIBIRC_ERR_NODCCSEND

(9):  A filename supplied to :c:func:`irc_dcc_sendfile` could not be sent. Either is is not a regular file (a directory or a socket, for example), or it could not be read. See also :c:macro:`LIBIRC_ERR_OPENFILE`


.. c:macro:: LIBIRC_ERR_READ

(10): Either a DCC file could not be read (for example, was truncated during sending), or a DCC socket returns a read error, which usually means that the network connection is terminated.

.. c:macro:: LIBIRC_ERR_WRITE

(11):  Either a DCC file could not be written (for example, there is no free space on disk), or a DCC socket returns a write error, which usually means that the network connection is terminated.

.. c:macro:: LIBIRC_ERR_STATE

(12):  The function is called when it is not allowed to be called. For example, :c:func:`irc_cmd_join` was called before the connection to IRC server succeed, and :c:member:`event_connect` is called.

.. c:macro:: LIBIRC_ERR_TIMEOUT

(13):  The DCC request is timed out. There is a timer for each DCC request, which tracks connecting, accepting  and non-accepted/declined DCC requests. For every request this timer 
is currently set to 60 seconds. If the DCC request was not connected, accepted or declined during this time, it will be terminated with this error.

.. c:macro:: LIBIRC_ERR_OPENFILE

(14): The file specified in :c:func:`irc_dcc_sendfile` could not be opened.

.. c:macro:: LIBIRC_ERR_TERMINATED

(15): The connection to the IRC server was terminated.

.. c:macro:: LIBIRC_ERR_NOIPV6

(16): The function which requires IPv6 support was called, but the IPv6 support was not compiled into the application

.. c:macro:: LIBIRC_ERR_SSL_NOT_SUPPORTED

(17): The SSL connection was required but the library was not compiled with SSL support

.. c:macro:: LIBIRC_ERR_SSL_INIT_FAILED

(18): The SSL library could not be initialized.

.. c:macro:: LIBIRC_ERR_CONNECT_SSL_FAILED

(19): SSL handshare failed when attempting to connect to the server. Typically this means you're trying to use SSL but attempting to connect to a non-SSL port.

.. c:macro:: LIBIRC_ERR_SSL_CERT_VERIFY_FAILED

(20): The server is using an invalid or the self-signed certificate. Use :c:macro:`LIBIRC_OPTION_SSL_NO_VERIFY` option to connect to it.


.. _api_options:

Options
^^^^^^^

.. c:macro:: LIBIRC_OPTION_DEBUG

If set, enables additional debug output which goes to STDOUT.

.. c:macro:: LIBIRC_OPTION_STRIPNICKS

If set, strips the event origins automatically. Every event has an origin (i.e. who originated the event). The origin usually looks like *nick!host@ircserver*, 
i.e. like *tim!home@irc.server.net*. Such origins can not be used in IRC commands, and need to be stripped (i.e. host and server part should be cut off) before using. 
This can be done either manually by calling :c:func:`irc_target_get_nick`, or automatically for all the events if this option is set.


.. c:macro:: LIBIRC_OPTION_SSL_NO_VERIFY

By default the SSL connection is authenticated by verifying that the certificate presented by the server is signed by a known trusted certificate authority. 
Since those typically cost money, some IRC servers use the self-signed certificates. They provide the benefits of the SSL connection but since they are 
not signed by the Certificate Authority, their authencity cannot be verified. This option, if set, disables the certificate verification - the library 
will accept any certificate presented by the server.

This option must be set before the :c:macro:`irc_connect` function is called.
