
GRPCXX := $(HOME)/grpcxx
CFLAGS += -I$(GRPCXX)/libgrpcxx -g -O0
LDFLAGS += -L$(GRPCXX)/libgrpcxx -lgrpcxx -lstdc++
LDFLAGS += -lprotobuf -pthread -lpthread -lgrpc++ -lgrpc

all: pre
	$(CC) $(CFLAGS) main.c $(LDFLAGS)

pre:
	make -C ../libgrpcxx

clean:
	rm -f a.out
