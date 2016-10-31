# BBS

This might be some kind of BBS at some point. Currently it supports awful "login" backed by RocksDB and prints a wicked sweet ASCII dragon.

## Motivation

I wanted to explore how one might write a bulletin board system. Turns out that there are a lot of awesome things you can do with telnet and bash escape codes.

## Installation

You'll need Boost ASIO and RocksDB. From there, run:

    $ bfg9000 configure build
    $ cd build
    $ ninja
    $ ./bbs 9999

To connect, open another shell and run:

    $ telnet localhost 9999

## License

[MIT](LICENSE)
