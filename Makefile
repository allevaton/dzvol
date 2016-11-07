# Makefile
#

CC = gcc

CFLAGS = -std=c99
LDFLAGS = $(shell pkg-config --libs x11 alsa) -lm

INSTALL_PATH = /usr/bin
OUT = dzvol

all: main.o

main.o: main.c
	$(CC) -o $(OUT) $(CFLAGS) $^ $(LDFLAGS)

clean:
	rm -rf *.o $(OUT)

install:
	cp  $(OUT) $(INSTALL_PATH)
	chmod +x $(INSTALL_PATH)/$(OUT)

.PHONY: clean
