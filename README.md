# grpcxx
C++ misc for gRPC

## Install gRPC

```
$ sudo apt-get install build-essential autoconf libtool pkg-config
$ sudo apt-get install libgflags-dev libgtest-dev
$ sudo apt-get install clang libc++-dev

$ git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
$ cd grpc
$ git submodule update --init
$ make && sudo make install

$ cd grpc/thrid_party/protobuf
$ sudo make install
```

## Usage

```
GRPCXX := /path/to/grpcxx
GRPCXX_PROTO := gobgp.proto
GRPCXX_PROTO_PATH := /path/to/proto
include $(GRPCXX)/mk/grpc.vars.mk
include $(GRPCXX)/mk/grpc.rules.mk
```

```
$ make grpcbuild
$ make grpcclean
```

## License and Author

Hiroki Shirokura (slank.dev [at] gmail.com) <br>
This software is developing under thre MIT License.
