#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

/* code by us */

int main(int argc, char* argv[])
{
	int id=-1;
    struct timeval t;
    time_t start_time;
    time_t final_time;
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    gettimeofday(&t, NULL);
    start_time = t.tv_usec;

    id = fork();

    gettimeofday(&t, NULL);
    final_time = t.tv_usec;

    if (id==0)
    {
        exit(0);
    }
    
    fprintf(fp, "%d\n", (final_time-start_time));
    fclose(fp);

    // printf("%d\n", (final_time-start_time));
    // printf("%d\n", (start_time));
}