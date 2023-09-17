#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"

void mndl(int WIDTH, int HEIGHT, double XCENTER, double YCENTER, double X0, double Y0, double DELTAPIX, double m, char* filename) {
    double cx,cy,x,y,x2,y2,i,px,py,pc;
    FILE *fp;
    fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int yy = 0; yy < HEIGHT; yy++) {
        cy = YCENTER + ((yy - HEIGHT / 2) * DELTAPIX);
	for (int xx = 0; xx < WIDTH; xx++) {
            cx = XCENTER + ((xx - WIDTH / 2) * DELTAPIX);
            x = X0;
            y = Y0;
            x2 = 0;
	    y2 = 0;
            i = 1;
	    px=x;
	    py=y;
	    pc=1;
            while (i < m && x2 + y2 <= bailout) {
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
		x2 = x * x;
		y2 = y * y;
                i++;
		pc++;
		if (pc>=maxperiod) {
		    pc=0;
		    if (px==x && py==y) {i=m;}
		    else {px=x;py=y;}
		}
            }
            if (i == m) {
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
