CFLAGS=-m64 -fPIC -g -I../../heclib/headers -I../../heclib/grid
CPPFLAGS= -std=c++11 -m64 -fPIC -g -I../../heclib/headers -I../../heclib/grid

CPP_SRCS:=$(wildcard *.cpp)
CPP_OBJS=$(CPP_SRCS:.cpp=*.o)

C_SRCS:=$(wildcard *.c)
C_OBJS=$(C_SRCS:.c=.o)
LIBS=../../heclib/Output/heclib.a ../../heclib/grid/grid.a -lz -lrt -lgfortran -lm 

all: chainsaw

chainsaw: $(CPP_OBJS) $(C_OBJS)
	$(CXX)  $(CPPFLAGS) -o $@ $(CPP_OBJS) $(C_OBJS) $(LIBS)

.cpp.o:
	$(CXX) $(CPPFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm  $(CPP_OBJS) $(C_OBJS) chainsaw