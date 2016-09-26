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

int size = (1024*1024*1024)/sizeof(int);
int stride = 1024;
int granularity = 1024*1024;

int main()
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    int i, j;
	int *arr;

	for(i=512;i<=size;i+=granularity)
	{
		arr = malloc(i*sizeof(int));

		__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    	in = rdtsc();

		for (int j = 0; j < i; j+=stride)
		{
			arr[j] = 1;
		}

		__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    	f = rdtsc();

    	fprintf(fp, "%lf\t%d\n", log2(i), (f-in-i));
    	free(arr);
	}
	fclose(fp);
}
