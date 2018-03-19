
GRPCXX := $(HOME)/grpcxx
CFLAGS += -I$(GRPCXX)/libgrpcxx -g -O0
LDFLAGS += -L$(GRPCXX)/libgrpcxx -lgrpcxx -lstdc++
LDFLAGS += -lprotobuf -pthread -lpthread -lgrpc++ -lgrpc

all:
	$(CC) $(CFLAGS) main.c $(LDFLAGS)

clean:
	rm -f a.out
