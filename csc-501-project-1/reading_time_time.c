#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

/* Code from linux manual */
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

/* code by us */

int main(int argc, char* argv[])
{
	struct timeval t;
    time_t start_time;
    time_t final_time;
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");
    

    char buffer[100000];
    FILE* inpfp;
    inpfp = fopen("sampleFile.txt", "r");

    gettimeofday(&t, NULL);
    start_time = t.tv_usec;

    fgets(buffer, 100000, (FILE*)inpfp);
    
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;
    
    fprintf(fp, "%d\n", (final_time-start_time));
    fclose(fp);

    fclose(inpfp);

    // printf("%" PRIu64 "\n", (f-i));
}