Ubicoin Core
=============

Setup
---------------------
Ubicoin Core is the original Ubicoin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of Litecoin transactions (which is currently more than 7 GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Ubicoin Core, visit [Ubistate.org](https://ubistate.org).

Running
---------------------
The following are some helpful notes on how to run Ubicoin Core on your native platform.

### Unix

Unpack the files into a directory and run:

- `ubicoin-qt` (GUI) or
- `ubicoind` (headless)

### Windows

Unpack the files into a directory, and then run ubicoin-qt.exe.

### Need Help?

* Ask for help on [Ubicoin](http://t.me/ubistate) on Telegram.
* Ask for help on the [Forum Ubicoin](https://forum.ubistate.org/) forums.

Building
---------------------
The following are developer notes on how to build Litecoin Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Linux Build Notes](build-linux.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Ubicoin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
