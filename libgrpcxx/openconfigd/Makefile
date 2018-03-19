
GRPCXX := $(HOME)/grpcxx
GRPCXX_PROTO = openconfig
GRPCXX_PROTO_PATH = .
include $(GRPCXX)/mk/grpc.vars.mk

CXXFLAGS += $(GRPC_CXXFLAGS) -g
LDFLAGS += $(GRPC_LDFLAGS)

TARGET = libgrpc_$(GRPCXX_PROTO).a
SRC = openconfig.cc
OBJ = $(SRC:.cc=.o)

all: $(OBJ)
	rm -f $(TARGET)
	ar -r $(TARGET) $(OBJ) $(GRPC_OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

include $(GRPCXX)/mk/grpc.rules.mk
