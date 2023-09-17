#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cores.h"

//switches, items that are testing
#define zoom_while_changing_x0 true

//ffmpeg command to postprocess ppm image into .png
#define ffmpeg "ffmpeg images/%04d.ppm images/%04d.png"

int main(int argc, char* argv[]) {
    if (argc!=9) {
	printf("argc is not 9\n");
        printf("use ./mandelbrot width height xcenter ycenter zoom_i zoom_f frames max_loop");
	exit(EXIT_FAILURE);
   }
    int WIDTH=atoi(argv[1]);
    int HEIGHT=atoi(argv[2]);
    double XCENTER=atof(argv[3]);
    double YCENTER=atof(argv[4]);
    double ZOOM_I=atof(argv[5]);
    double ZOOM_F=atof(argv[6]);
    int frames=atoi(argv[7]);
    double DELTAZOOM=(ZOOM_F-ZOOM_I)/frames;
    double m=atoi(argv[8]);
    double zoom=ZOOM_I;
    char filename[30];
    double X0 = rand()/1000000000;
    double Y0 = rand()/1000000000;
    char cmd[99]; //make sure has the right num of chars for the ffmpeg cmd
    for (int z = 0; z <= frames; z++) {
        sprintf(filename, "images/%04d.ppm", z);
        printf("%04d\n", z);
	mndl(WIDTH, HEIGHT, XCENTER, YCENTER, X0, Y0, pow(10, zoom), m, filename);
	zoom+=DELTAZOOM;
	sprintf(cmd, "ffmpeg -loglevel 0 -i images/%04d.ppm images/%04d.png; rm images/%04d.ppm", z, z, z);
	int status = system(cmd);
	if (status == -1) {
	    perror("exiting, ffmpeg failure");
	    exit(EXIT_FAILURE);
	}
    }
    return 0;
}
