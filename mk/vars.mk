
ifeq ($(GRPCXX_PROTO),)
$(error "Please define GRPCXX_PROTO environment variable")
endif
ifeq ($(GRPCXX_PROTO_PATH),)
$(error "Please define GRPCXX_PROTO_PATH environment variable")
endif

GRPCXX_OBJ = $(GRPCXX_PROTO).grpc.pb.o $(GRPCXX_PROTO).pb.o
GRPCXX_CXXFLAGS += -std=c++11
GRPCXX_CXXFLAGS += `pkg-config --cflags protobuf grpc++ grpc`
GRPCXX_LDFLAGS  += `pkg-config --libs protobuf grpc++ grpc`
GRPCXX_LDFLAGS  += -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl

