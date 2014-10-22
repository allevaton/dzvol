# Makefile
#

CC = gcc

CFLAGS = -g -std=c99
LDFLAGS = $(shell pkg-config --libs x11 alsa) -lm

OUT = dzvol

all: main.o

main.o: main.c
	$(CC) -o dzvol $(CFLAGS) $(LDFLAGS) $^

clean:
	rm -rf *.o $(OUT)

.PHONY: clean
