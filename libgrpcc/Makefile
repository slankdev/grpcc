
TARGET = libgrpcc.a
SUB_LIBS = \
	 grpcc/libgrpcc_grpcc.a \
	 openconfigd/libgrpcc_openconfig.a \
	 helloworld/libgrpcc_helloworld.a \
	 gobgp/libgrpcc_gobgp.a

all:
	rm -f $(TARGET)
	make -C grpcc
	make -C helloworld
	make -C gobgp
	make -C openconfigd
	ar cqT $(TARGET) $(SUB_LIBS)
	echo "create $(TARGET)\naddlib $(TARGET)\nsave\nend" | ar -M

clean:
	rm -f $(TARGET)
	make -C grpcc clean
	make -C gobgp clean
	make -C helloworld clean
	make -C openconfigd clean

grpcbuild:
	make -C gobgp grpcbuild
	make -C helloworld grpcbuild
	make -C openconfigd grpcbuild

grpcclean:
	make -C gobgp grpcclean
	make -C helloworld grpcclean
	make -C openconfigd grpcclean

