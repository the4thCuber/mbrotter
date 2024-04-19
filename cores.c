#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"
#include "output.h"

double iter(double cx, double cy, double max_loop) {
	    double y2 = cy*cy;
	    double q = pow((cx-.25),2) + y2;
	    if (q*(q+(cx-.25)) <= .25*y2) {return max_loop;}
            if (pow((cx+1),2) + y2 <= .0625) {return max_loop;}
	    double x2 = cx*cx;
	    double y = cy;
	    double x = cx;
	    double i = 1;
	    double px=x;
	    double py=y;
	    int pc=1;
            while (i < max_loop && x2 + y2 <= bailout) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
		x2 = x * x;
		y2 = y * y;
                i++;
		pc++;
		if (pc>=maxperiod) {
		    pc=0;
		    if (px==x && py==y) {return max_loop;}
		    else {px=x;py=y;}
		}
            }
	    double logz=log(x2+y2)/2;
	    double n=log((logz/l))/l;
	    return i+1-n;
}


void mndl(int width, int height, double xcenter, double ycenter, double deltapix, double max_loop, int f, char* filename) {
    double cx,cy;
    FILE *fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (int yy = 0; yy < height; yy++) {
        cy = ycenter + ((yy - height / 2) * deltapix);
	printProgressBar(yy, height, 100);
	for (int xx = 0; xx < width; xx++) {
            cx = xcenter + ((xx - width / 2) * deltapix);
	    double i = .25*(iter(cx, cy, max_loop)+iter(cx+.5*deltapix,cy,max_loop)+iter(cx,cy+.5*deltapix,max_loop)+iter(cx+.5*deltapix,cy+.5*deltapix,max_loop));
	    if (i >= max_loop) {
                fputc(0, fp);
                fputc(0, fp);
                fputc(0, fp);
            } else {
		i = iterscaling(i, f);
		fputc((char)128*(1+sin(rshift*i)), fp);
                fputc((char)128*(1+sin(gshift*i)), fp);
                fputc((char)128*(1+sin(bshift*i)), fp);
            }
        }
    }
    fclose(fp);
}
