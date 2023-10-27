#include <stdio.h>
#include <unistd.h>
#include <string.h>

void printProgressBar(int progress, int total, int barWidth) {
    float percentage = (float)progress / (float)total;
    int numBars = (int)(percentage * barWidth);

    printf("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < numBars) {
            putchar('#');
        } else {
            putchar(' ');
        }
    }
    printf("] %3.2f%%\r", percentage * 100);
    fflush(stdout);
}

void printProgress(int progress, int total, int barWidth, double cpu_time, double cpu_total) {
    for (int i = 0; i <= 4; i++) {
	printf("\033[A\033[K");
    }
    printProgressBar(progress, total, barWidth);
    printf("\nCompleted %i frames using %f CPU time\n", progress, cpu_total);
    double average_time = cpu_total/progress;
    printf("Time for last frame:%f\nAverage time per frame:%f\n", cpu_time, average_time);
    int remaining = total - progress;
    printf("Estimated time to completion:%f\n", remaining * average_time);
    printf("Rendering frame %d", progress+1);
    fflush(stdout);
}
