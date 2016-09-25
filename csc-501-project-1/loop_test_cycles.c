#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>

/* Code from linux manual */
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

/* code by us */

int main(int argc, char* argv[])
{
	unsigned eax, ebx, ecx, edx, level;
	eax = 1; /* processor info and feature bits */
	level = 1;
  	uint64_t i, f;
    int k;  // for loop
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    int *buffer = (int*)malloc(10000*sizeof(int));
    buffer[0] = 0;
    
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    i = rdtsc();
    
    for (k=1;k<=10000;k++)
    {
        // buffer[k-1] = 0;
    }
    
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
  	f = rdtsc();
    
    fprintf(fp, "%d\n", (f-i));
    fclose(fp);

    // printf("%" PRIu64 "\n", (f-i));
}