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

int size = (64*1024*1024)/sizeof(int);
int stride = 16;

int main()
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

    int i, j;
	int *arr = malloc(size*sizeof(int));
	memset(arr, 0, size*sizeof(int));	// this should fill L1, L2 and L3 cache
	
	for(i=0;i<size;i+=stride)
	{
		__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    	in = rdtsc();

    	j = arr[i];
    	// memset(&arr[i], 1, stride*sizeof(int));

    	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    	f = rdtsc();

    	printf("%d\n", (f-in));
    }

}