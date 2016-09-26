#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int l1 = (64*1024)/sizeof(int);
int l2 = (128*1024)/sizeof(int);
int l3 = (768*1024)/sizeof(int);


int granularity = 1000;

int main(int argc, char* argv[])
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

	struct timeval t;
    time_t start_time;
    time_t final_time;
    int i,j;
    char *arr;

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    
    for (j=start; j<=end; j+=granularity)
    {
	    arr = (char *)malloc(j*sizeof(char));
	    // printf("%d\n", sizeof(double));

	    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
	        in = rdtsc();

	    for (i=0;i<j;i++)
	    {
	    	
	    	arr[i] = 'a';
	    	// arr[i]++;

		}	
	    
	    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
	        f = rdtsc();

	    fprintf(fp, "%d\t%d\n", j ,(f-in)/j);
	    free(arr);
	    // printf("%lf\t%d\n", log2(j) ,(f-in)/j);
	}    
    // for (i=0;i<(size-granularity);i+=granularity)
    // {
    // 	gettimeofday(&t, NULL);
    // 	start_time = t.tv_usec;
    	
    // 	for (j=i; j<(i+granularity); j++)
    // 		arr[j] = 0;
    // 		arr[j]++;

    // 	gettimeofday(&t, NULL);
    // 	final_time = t.tv_usec;

    // 	fprintf(fp, "%d\n", (final_time-start_time));
    	
    // }	
    fclose(fp);
}