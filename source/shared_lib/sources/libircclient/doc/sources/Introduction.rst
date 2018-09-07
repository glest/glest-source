=====================
Introduction
=====================

Overview
~~~~~~~~

Libircclient is a small but extremely powerful library which implements the client IRC protocol. It is designed to be small, fast, portable and compatible 
with the RFC standards as well as non-standard but popular features. It is perfect for building the IRC clients and bots.


Features
~~~~~~~~
 - Comprehensive C API;
 - Full coverage of the IRC protocol using providing functions;
 - Supports multiple simultaneous connection to different IRC servers or even to the same server;
 - Supports both plain and SSL connections to the IRC servers with the optional certificate check;
 - Full multi-threading support, the library is thread-safe;
 - All the processing could be handled by a single thread even if multiple connections are used;
 - Non-blocking, asynchronous event-based interface implemented with callbacks;
 - Extra support for the socket-based applications, which use select();
 - CTCP support with optional build-in reply code;
 - Supports CTCP PING necessary to pass the “spoof check” implemented by most IRC servers;
 - Flexible DCC support, including both DCC chat, and DCC file transfer;
 - Can both initiate and react to initiated DCC;
 - Can accept or decline DCC sessions asynchronously;
 - Written in plain C, very small binary size (around 30K depending on platform);
 - Compatible all tested IRC clients;
 - Free software licensed under the LGPLv3 license;
 - Supports Linux as well as any POSIX-compliant Unix, Mac OS X and Microsoft Windows;
 - Supports 32/64bit architectures as well as non-x86 architectures;
 - IPv6 support (optional, must be compiled in);
 - OpenSSL support (optional, must be compiled in);
 - Cocoa interface by Nathan Ollerenshaw;
 - Comprehensive documentation, examples and the FAQ;


Known issues
~~~~~~~~~~~~

Even though possible by using multiple sessions, the library is not suitable to connect to a large number of IRC servers simultaneously. If you still want to use it, you'd have to overcome the following:

 - You cannot use the main loop in :c:func:`irc_run` because it only supports one session. You would have to use :c:func:`irc_add_select_descriptors`
 - You'd have to handle reconnections separately by processing the relevant :c:func:`irc_process_select_descriptors` return values
 - If you wish to use poll/epoll() instead of select() you'd have to write more logic as it is not directly supported. See the :ref:`FAQ <faq_epoll>`.
 - The library is not optimized to have a low per-connection memory footprint, each non-SSL connection uses at least 4K, with around 32K per connection for SSL.


Author
~~~~~~

This library is created by George Yunaev, copyright 2004-2016. Please see http://www.ulduzsoft.com/linux/libircclient


License
~~~~~~~

Libircclient is licensed under Lesser General Public License version 3 or higher. The complete license text is provided in the Appendix.
