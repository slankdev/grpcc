
TARGET = libgrpcxx.a
SUB_TARGETS = \
	 grpc_wrapper/libgrpcxx_wrapper.a \
	 openconfigd/libgrpc_openconfig.a \
	 helloworld/libgrpc_helloworld.a

all: sub $(TARGET)

$(TARGET): $(SUB_TARGETS)
	$(RM) $@
	$(AR) cqT $@ $^
	echo "create $@\naddlib $@\nsave\nend" | ar -M

clean: subclean
	rm -f $(TARGET)

sub:
	make -C grpc_wrapper
	make -C helloworld
	make -C openconfigd

subclean:
	make -C grpc_wrapper clean
	make -C helloworld clean
	make -C openconfigd clean

test:
	make -C ../test clean
	make -C ../test
	../test/a.out

