Copyright (c) 2009-2012 Bitcoin Developers
Copyright (c) 2017 BUZZ Developers
Distributed under the MIT/X11 software license, see the accompanying file
license.txt or http://www.opensource.org/licenses/mit-license.php.  This
product includes software developed by the OpenSSL Project for use in the
OpenSSL Toolkit (http://www.openssl.org/).  This product includes cryptographic
software written by Eric Young (eay@cryptsoft.com) and UPnP software written by
Thomas Bernard.

# intro

See qt-build.md for instructions on building BuzzCoin QT, the graphical user interface.

All of the commands should be executed in Terminal.

## lets go!

1.  Clone the github tree to get the source code:

```
git clone https://github.com/buzzcoin-project/BUZZ
```

2.  Download and install Brew and never look at Macports, ever! https://brew.sh

3.  Install dependencies from Brew

```
brew install boost berkeley-db openssl miniupnpc qrencode
```

4.  Now you should be able to build buzzcoind:

```
cd buzzcoin/src
make -f makefile.osx
```

```
  ./buzzcoind --help  # for a list of command-line options.
  ./buzzcoind -daemon # to start the buzzcoin daemon.
  ./buzzcoind help # When the daemon is running, to get a list of RPC commands
```
