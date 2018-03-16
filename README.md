# grpcxx
C++ misc for gRPC

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
