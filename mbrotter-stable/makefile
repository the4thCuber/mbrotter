CC = gcc
CFLAGS = -Wall -Werror

all: mbrotter

mbrotter: mandelbrot.o cores.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
mandelbrot.o: mandelbrot.c cores.h
	$(CC) $(CFLAGS) -c $<
cores.o: cores.c cores.h config.h
	$(CC) $(CFLAGS) -c $<

#Dependencies
check_ffmpeg:
	@if ! [ -x /usr/bin/ffmpeg ]; then \
		echo "ffmpeg is not found in /usr/bin. Please install it."; \
		exit 1; \
	fi
run: check_ffmpeg
	echo "checks complete"

clean:
	rm -f *.o mbrotter
