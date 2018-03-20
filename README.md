
# libgrpcxx

Tiny build scripts and wrapper for using grpc in C

## Setup

install grpc
```
$ sudo apt install build-essential autoconf libtool pkg-config libgflags-dev libgtest-dev clang libc++-dev
$ git clone https://github.com/grpc/grpc && cd grpc
$ git submodule update --init
$ make && sudo make install
```

install proto-buf
```
$ cd grpc/third_party/protobuf
$ sudo make install
```

clone and build libgrpcxx
```
$ git clone https://github.com/slankdev/grpcxx && cd grpcxx/libgrpcxx
$
```

## Usage

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgrpcxx.h>

int main(int argc, char** argv)
{
}
```

```
CFLAGS += -I../
LDFLAGS += -L../ -lgrpcxx -lstdc++

all:
	$(CC) $(CFLAGS) main.c $(LDFLAGS)
```
