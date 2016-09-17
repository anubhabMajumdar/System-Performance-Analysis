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
    struct timeval t;
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");
    char buffer[100000];

    FILE* inpfp;
    inpfp = fopen("sampleFile.txt", "r");

    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    i = rdtsc();
    
    fgets(buffer, 100000, (FILE*)inpfp);
    
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
  	f = rdtsc();
    
    fprintf(fp, "%d\n", (f-i));
    fclose(fp);

    fclose(inpfp);

    // printf("%" PRIu64 "\n", (f-i));
}