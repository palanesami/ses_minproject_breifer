#CC=gcc
CC=aarch64-rpi3-linux-gnu-gcc
CFLAGS=-I/opt/palanesami/x-tools/aarch64-rpi3-linux-gnu/aarch64-rpi3-linux-gnu/sysroot/usr/include/
SRC=$(wildcard *.c)

briefer: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^  $(LIBS)