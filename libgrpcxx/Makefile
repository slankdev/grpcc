
TARGET = libgrpcxx.a
SUB_LIBS = \
	 openconfigd/libgrpcxx_openconfig.a \
	 helloworld/libgrpcxx_helloworld.a

all:
	rm -f $(TARGET)
	make -C helloworld
	make -C openconfigd
	ar cqT $(TARGET) $(SUB_LIBS)
	echo "create $(TARGET)\naddlib $(TARGET)\nsave\nend" | ar -M

clean:
	rm -f $(TARGET)
	make -C helloworld clean
	make -C openconfigd clean

grpcbuild:
	make -C helloworld grpcbuild
	make -C openconfigd grpcbuild

grpcclean:
	make -C helloworld grpcclean
	make -C openconfigd grpcclean

