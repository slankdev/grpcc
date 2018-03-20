
# libgrpcxx

Tiny build scripts and wrapper for using grpc in C

## Setup and Usage

```
// install grpc
$ sudo apt install build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev
$ git clone https://github.com/grpc/grpc && cd grpc
$ git submodule update --init
$ make && sudo make install

// install proto-buf
$ cd grpc/third_party/protobuf
$ sudo make install

// clone and build libgrpcxx
$ git clone https://github.com/slankdev/grpcxx
$ cd grpcxx/libgrpcxx
$ make grpcbuild
$ make

// Best Sample for using this library is ``examples/grpc_manager``.
// running sample script (grpc_manager)
// install openconfigd before following
$ cd examples/grpc_manager
$ make
$ openconfigd &
$ ./a.out &
$ cli
```

