#!/bin/bash
set -x

rm -f *.o pch.h.gch a.out

CFLAGS=-I../../heclib/heclib/headers
#g++ -c  pch.h -I../../heclib/heclib/headers


gcc -c chainsaw.cpp  ${CFLAGS}
gcc -c DssDatabase.cpp ${CFLAGS}
gcc -c DssTest.cpp ${CFLAGS}
gcc -c pch.cpp ${CFLAGS}
gcc -c TestingCenter.cpp ${CFLAGS}
gcc -c ts_write_irregular.c ${CFLAGS}
gcc -c SampleText1.cpp ${CFLAGS}
gcc  *.o  ../../build/heclib/heclib/Output/heclib.a  -lstdc++ -lm -lgfortran

