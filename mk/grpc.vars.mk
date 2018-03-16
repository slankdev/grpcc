

GRPC_OBJ = $(GRPCXX_PROTO).grpc.pb.o $(GRPCXX_PROTO).pb.o
GRPC_CXXFLAGS += -std=c++11
GRPC_CXXFLAGS += `pkg-config --cflags protobuf grpc++ grpc`
GRPC_LDFLAGS  += `pkg-config --libs protobuf grpc++ grpc`
GRPC_LDFLAGS  += -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl

