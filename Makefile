CC=gcc
CFLAGS=-g -lm

compile:
	$(CC) $(CFLAGS) potd.c -o arrispotd
