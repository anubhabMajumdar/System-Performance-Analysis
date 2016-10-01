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

int size = (3*1024*1024)/sizeof(int);

int l0 = (1024)/sizeof(int);
int l1 = (8*1024)/sizeof(int);
int l2 = (128*1024)/sizeof(int);
int l3 = (768*1024)/sizeof(int);
int l4 = (1024*1024)/sizeof(int);

int stride = 1;
int granularity = 1024;

int main()
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    int i, j, cycles, temp;
	int *arr;

	// for(i=(8/sizeof(int));i<=size;i+=granularity)
	for(i=l0;i<l4;i+=granularity)
	{
		arr = malloc(i*sizeof(int));
		cycles = 0;

		// Bring array to cache and stop page fault
		for (int j = 0; j < i; j+=stride)
		{
			arr[j] = j;
		}		

		for (int j = (i-1); j > (i-l0); j+=stride)
		{
			__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    		in = rdtsc();

			temp = arr[j];

			__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    		f = rdtsc();

    		cycles+=f-in-1;
		}

    	fprintf(fp, "%lf\t%d\n", log2(i), cycles);
    	free(arr);
	}
	fclose(fp);
}
