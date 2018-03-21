
GRPCXX_ROOT := ../../
GRPCXX_PROTO = gobgp
GRPCXX_PROTO_PATH = .
include $(GRPCXX_ROOT)/mk/vars.mk

CXXFLAGS += $(GRPCXX_CXXFLAGS) -g
LDFLAGS += $(GRPCXX_LDFLAGS)

# for debug
LIBSLANKDEV := $(HOME)/git/libslankdev
CXXFLAGS += -I$(LIBSLANKDEV) -std=c++11

TARGET = libgrpcxx_$(GRPCXX_PROTO).a
SRC = gobgp.cc
OBJ = $(SRC:.cc=.o)

all: $(OBJ)
	rm -f $(TARGET)
	ar -r $(TARGET) $(OBJ) $(GRPCXX_OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

include $(GRPCXX_ROOT)/mk/rules.mk

