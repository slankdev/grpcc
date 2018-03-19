
GRPCXX := $(HOME)/grpcxx
include $(GRPCXX)/mk/grpc.vars.mk

CXXFLAGS += $(GRPC_CXXFLAGS)
LDFLAGS += $(GRPC_LDFLAGS)

TARGET = libgrpcxx_wrapper.a
SRC = wrapper.cc
OBJ = $(SRC:.cc=.o)

all: $(OBJ)
	rm -f $(TARGET)
	ar -r $(TARGET) $(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

include $(GRPCXX)/mk/grpc.rules.mk
