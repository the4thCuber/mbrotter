#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "cores.h"
#include "output.h"

#define CLOCK_SPEED 1500000;

int main(int argc, char* argv[]) {
    if (argc!=9) {
	printf("incorrect number of arguments\n");
        printf("use ./mbrotter width height xcenter ycenter zoom_i zoom_f frames max_loop\n");
	exit(EXIT_FAILURE);
   }
    //massively disorganized variable initializations
    int width=atoi(argv[1]);
    int height=atoi(argv[2]);
    double xcenter=atof(argv[3]);
    double ycenter=atof(argv[4]);
    double zoom_i=atof(argv[5]);
    double zoom_f=atof(argv[6]);
    int frames=atoi(argv[7]);
    double deltazoom=(zoom_f-zoom_i)/frames;
    double max_loop=atoi(argv[8]);
    double zoom=zoom_i;
    char filename[30];
    double x0 = rand()/1000000000;
    double y0 = rand()/1000000000;
    char cmd[99]; //make sure has enough chars for the ffmpeg cmd
    clock_t start, end;
    double cpu_time, cpu_total=0.0;
    printf("Rendering frame 1");
    for (int z = 0; z <= frames; z++) {
	start = clock();
	sprintf(filename, "images/%04d.ppm", z);
	//draw frame and perform post-processing
	mndl(width, height, xcenter, ycenter, x0, y0, pow(10, zoom), max_loop, filename);
	sprintf(cmd, "ffmpeg -loglevel 0 -i images/%04d.ppm images/%04d.png; rm images/%04d.ppm", z, z, z);
	int status = system(cmd);
	if (status == -1) {
	    perror("exiting, ffmpeg failure");
	    exit(EXIT_FAILURE);
	}
	printf("\r");
	//update arguments and output
	end = clock();
	cpu_time = ((double)(end-start))/CLOCK_SPEED;
	cpu_total = cpu_total+cpu_time;
	printProgress(z+1, frames, 100, cpu_time, cpu_total);
	zoom+=deltazoom;
    }
    return 0;
}
