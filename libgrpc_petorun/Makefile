
TARGET = libgrpc_kamuee.a
SUB_TARGETS = helloworld/libgrpc_helloworld.a

all: sub
	rm -f $(TARGET)
	ar cqT $(TARGET) $(SUB_TARGETS)
	echo "create $(TARGET) \n addlib $(SUB_TARGETS) \n save \n end" | ar -M
	cp $(TARGET) ../build

clean: subclean
	rm -f $(TARGET)

sub:
	make -C helloworld

subclean:
	make -C helloworld clean

grpcbuild:
	make -C helloworld grpcbuild

grpcclean:
	make -C helloworld grpcclean

