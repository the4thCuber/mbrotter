#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//palette defines
#define rshift 2.71828172846
#define gshift 3.14159265359
#define bshift 1.61803398874
//other defines
#define bailout 4000
#define maxperiod 70
double iterscaling(double i, int f) {return pow(i, .416-1/(double)f+.51*(450/(double)f)*sin((double)f/69));}
//misc (e.g. computation) defines
#define l log(2)
