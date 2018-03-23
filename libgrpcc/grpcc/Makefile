


CXXFLAGS += -std=c++11
CXXFLAGS += `pkg-config --cflags protobuf grpc grpc++`
LDFLAGS += `pkg-config --libs protobuf grpc grpc++`

TARGET = libgrpcc_grpcc.a
SRC = grpcc.cc
OBJ = $(SRC:.cc=.o)

all: $(OBJ)
	rm -f $(TARGET)
	ar -r $(TARGET) $(OBJ) $(GRPCXX_OBJ)

clean:
	rm -f $(TARGET) $(OBJ)

# include $(GRPCXX_ROOT)/mk/rules.mk

