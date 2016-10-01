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
    time_t tt;

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    gettimeofday(&t, NULL);
    start_time = t.tv_usec;

    time(&tt);
    
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;

    fprintf(fp, "%d\n", (final_time-start_time));
    fclose(fp);

    // printf("%d\n", (final_time));
    // printf("%d\n", (start_time));
}