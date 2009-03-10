#
# Makefile for glslKernel library
#

CC = gcc
CXX = g++

CFLAGS = -Wall
CXXFLAGS = -Wall -Wno-deprecated

#--------------------------------------------

libglslKernel.a: GLee.o glslKernel.o
	ar -rs libglslKernel.a GLee.o glslKernel.o

GLee.o: GLee.c
	$(CC) -c $(CFLAGS) GLee.c

glslKernel.o: glslKernel.cc glslKernel.h
	$(CXX) -o glslKernel.o -c $(CXXFLAGS) glslKernel.cc

clean:
	rm -f *.a *.o *~
