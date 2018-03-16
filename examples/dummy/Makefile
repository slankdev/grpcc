
# for grpcxx
GRPCXX := $(HOME)/grpcxx
GRPCXX_PROTO = helloworld
GRPCXX_PROTO_PATH = .
include $(GRPCXX)/mk/grpc.vars.mk

CXXFLAGS += $(GRPC_CXXFLAGS)
LDFLAGS += $(GRPC_LDFLAGS)

all: server client

server:
	$(CXX) $(CXXFLAGS) server.cc -o server.out $(GRPC_OBJ) $(LDFLAGS)

client:
	$(CXX) $(CXXFLAGS) client.cc -o client.out $(GRPC_OBJ) $(LDFLAGS)

clean:
	rm -f server.out client.out

# for grpcxx
include $(GRPCXX)/mk/grpc.rules.mk
# include $(HOME)/git/libslankdev/mk/rules.mk
