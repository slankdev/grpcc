
LIB_PATH := ../../libgrpcc
CFLAGS += -I$(LIB_PATH) -g -O0
LDFLAGS += -L$(LIB_PATH) -lgrpcc -lstdc++
LDFLAGS += -lprotobuf -pthread -lpthread -lgrpc++ -lgrpc

all: pre
	$(CC) $(CFLAGS) main.c $(LDFLAGS)

pre:
	make -C $(LIB_PATH)

clean:
	rm -f a.out
