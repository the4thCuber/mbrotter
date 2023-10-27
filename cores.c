#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"
#include "output.h"

void mndl(int width, int height, double xcenter, double ycenter, double x0, double y0, double deltapix, double max_loop, char* filename) {
    double cx,cy,x,y,x2,y2,i,px,py,pc;
    FILE *fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (int yy = 0; yy < height; yy++) {
        cy = ycenter + ((yy - height / 2) * deltapix);
	printProgressBar(yy, height, 100);
	for (int xx = 0; xx < width; xx++) {
            cx = xcenter + ((xx - width / 2) * deltapix);
            x = x0;
            y = y0;
            x2 = 0;
	    y2 = 0;
            i = 1;
	    px=x;
	    py=y;
	    pc=1;
            while (i < max_loop && x2 + y2 <= bailout) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
		x2 = x * x;
		y2 = y * y;
                i++;
		pc++;
		if (pc>=maxperiod) {
		    pc=0;
		    if (px==x && py==y) {i=max_loop;}
		    else {px=x;py=y;}
		}
            }
            if (i == max_loop) {
                fputc(0, fp);
                fputc(0, fp);
                fputc(0, fp);
            } else {
		double logz=log(x2+y2)/2;
		double n=log((logz/l))/l;
		i=pow(log(i+1-n),iterscaling);
                fputc((char)128*(1+sin(rshift*i)), fp);
                fputc((char)128*(1+sin(gshift*i)), fp);
                fputc((char)128*(1+sin(bshift*i)), fp);
            }
        }
    }
    fclose(fp);
}
