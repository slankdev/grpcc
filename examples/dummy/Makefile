
# for grpcxx
GRPCXX := $(HOME)/grpcxx
GRPCXX_PROTO = dummy
GRPCXX_PROTO_PATH = .
include $(GRPCXX)/mk/grpc.vars.mk

CXXFLAGS += $(GRPCXX_CXXFLAGS)
LDFLAGS += $(GRPCXX_LDFLAGS)

all:
	$(CXX) $(CXXFLAGS) main.cc $(LDFLAGS)

# for grpcxx
include $(GRPCXX)/mk/grpc.rules.mk
