
LIB_PATH := $(HOME)/grpcxx/libgrpcxx
CFLAGS += -I$(LIB_PATH) -g -O0
LDFLAGS += -L$(LIB_PATH) -lgrpcxx -lstdc++
LDFLAGS += -lprotobuf -pthread -lpthread -lgrpc++ -lgrpc

all: pre
	$(CC) $(CFLAGS) main.c $(LDFLAGS)

pre:
	make -C ../libgrpcxx

clean:
	rm -f a.out
