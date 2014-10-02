# Matthew Fritze
# 1360555
# CMPUT 379
# Assignment 1

CFLAGS = -m32 -g -Wall
OBJS = lander.o init.o input.o graphics.o player.o 
PROG = lander

memchunk: memchunk.o testprogram.o
	gcc $(CFLAGS) testprogram.o memchunk.o -o memchunk

testprogram.o: testprogram.c memchunk.h
	gcc $(CFLAGS) -c testprogram.c -o testprogram.o

memchunk.o: memchunk.c memchunk.h
	gcc $(CFLAGS) -c memchunk.c -o memchunk.o

run:
	./memchunk

clean:
	rm -rf *.o memchunk

