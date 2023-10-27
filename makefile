CC = gcc
CFLAGS = -Wall -Werror

all: mbrotter

mbrotter: mandelbrot.o cores.o output.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
mandelbrot.o: mandelbrot.c cores.c cores.h
	$(CC) $(CFLAGS) -c $<
cores.o: cores.c cores.h config.h output.c output.h
	$(CC) $(CFLAGS) -c $<
output.o: output.c output.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o mbrotter
