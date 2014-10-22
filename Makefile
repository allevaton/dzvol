# Makefile
#

CC = gcc

CFLAGS = -g -std=c99
LDFLAGS = $(shell pkg-config --libs x11 alsa) -lm

OUT = dzvol

all: main.o

main.o: main.c
	$(CC) -o $(OUT) $(CFLAGS) $(LDFLAGS) $^

clean:
	rm -rf *.o $(OUT)

install:
	cp  $(OUT) /usr/bin
	chmod +x /usr/bin/$(OUT)

.PHONY: clean
