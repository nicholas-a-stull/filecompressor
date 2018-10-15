CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g
COMPILE = $(CC) $(CFLAGS)
BINS =  teststack testqueue testhuffman testbv encode decode
PROGRAM = encode decode

.PHONY:
all:	encode decode

# Executable Binaries

encode:	encode.o queue.o huffman.o stack.o stacktwo.o bv.o
	$(COMPILE) encode.o huffman.o queue.o stack.o stacktwo.o bv.o -o encode

decode:	decode.o queue.o huffman.o stack.o stacktwo.o bv.o
	$(COMPILE) decode.o huffman.o queue.o stack.o stacktwo.o bv.o -o decode

teststack: stack.o teststack.o stacktwo.o huffman.o
	$(COMPILE) stack.o stacktwo.o huffman.o teststack.o -o teststack

testhuffman:	testhuffman.o huffman.o
	$(COMPILE) testhuffman.o huffman.o -o testhuffman

testqueue: testqueue.o huffman.o queue.o
	$(COMPILE) testqueue.o queue.o huffman.o -o testqueue

testbv:		testbv.o bv.o
	$(COMPILE) testbv.o bv.o -o testbv

# Object files for executable binares

encode.o:	encode.c
	$(COMPILE) -c encode.c

decode.o:	decode.c
	$(COMPILE) -c decode.c

teststack.o:	teststack.c
	$(COMPILE) -c teststack.c

testhuffman.o:	testhuffman.c
	$(COMPILE) -c testhuffman.c

testqueue.o:	testqueue.c
	$(COMPILE) -c testqueue.c

testbv.o:	testbv.c
	$(COMPILE) -c testbv.c

# Object files for data structures

huffman.o:	huffman.c
	$(COMPILE) -c huffman.c

queue.o::	queue.c
	$(COMPILE) -c queue.c

stack.o:	stack.c
	$(COMPILE) -c stack.c

bv.o:		bv.c
	$(COMPILE) -c bv.c

stacktwo.o:	stacktwo.c
	$(COMPILE) -c stacktwo.c

# Clean

clean:
	rm -f $(BINS) *.o *.gch
