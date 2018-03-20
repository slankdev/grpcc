

ifeq ($(GRPCXX_PROTO),)
$(error "Please define GRPCXX_PROTO environment variable")
endif
ifeq ($(GRPCXX_PROTO_PATH),)
$(error "Please define GRPCXX_PROTO_PATH environment variable")
endif

grpcbuild:
	protoc -I. --cpp_out=. \
		--proto_path=$(GRPCXX_PROTO_PATH) $(GRPCXX_PROTO).proto
	protoc -I. --grpc_out=. \
		--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
		--proto_path=$(GRPCXX_PROTO_PATH) $(GRPCXX_PROTO).proto
	$(CXX) -g $(GRPCXX_CXXFLAGS) -c -o $(GRPCXX_PROTO).grpc.pb.o $(GRPCXX_PROTO).grpc.pb.cc
	$(CXX) -g $(GRPCXX_CXXFLAGS) -c -o $(GRPCXX_PROTO).pb.o $(GRPCXX_PROTO).pb.cc

grpcclean:
	rm -f \
		$(GRPCXX_PROTO).grpc.pb.cc \
		$(GRPCXX_PROTO).grpc.pb.h  \
		$(GRPCXX_PROTO).grpc.pb.o  \
		$(GRPCXX_PROTO).pb.cc  \
		$(GRPCXX_PROTO).pb.h   \
		$(GRPCXX_PROTO).pb.o


