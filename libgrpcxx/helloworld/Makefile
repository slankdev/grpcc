
GRPCXX := $(HOME)/grpcxx
GRPCXX_PROTO = helloworld
GRPCXX_PROTO_PATH = .
include $(GRPCXX)/mk/grpc.vars.mk

CXXFLAGS += $(GRPC_CXXFLAGS)
LDFLAGS += $(GRPC_LDFLAGS)

TARGET = libgrpc_helloworld.a
SRC = helloworld.cc
OBJ = $(SRC:.cc=.o)

all: $(OBJ)
	rm -f $(TARGET)
	ar -r $(TARGET) $(OBJ) $(GRPC_OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

include $(GRPCXX)/mk/grpc.rules.mk
