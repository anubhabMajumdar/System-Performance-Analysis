#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

/* code by us */

int main(int argc, char* argv[])
{
	int k;  // for loop
    struct timeval t;
    time_t start_time;
    time_t final_time;
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    int *buffer = (int*)malloc(10000*sizeof(int));
    buffer[0] = 0;

    gettimeofday(&t, NULL);
    start_time = t.tv_usec;

    for (k=1;k<=10000;k++)
    {
        // buffer[k-1] = 0;
    }
    
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;

    fprintf(fp, "%d\n", (final_time-start_time));
    fclose(fp);

    // printf("%d\n", (final_time));
    // printf("%d\n", (start_time));
}