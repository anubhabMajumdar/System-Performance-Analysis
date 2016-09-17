#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main()
{
	unsigned eax, ebx, ecx, edx, level;
	eax = 1; /* processor info and feature bits */
	level = 1;
  	uint64_t i, f;
    int k;  // for loop

    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    i = rdtsc();
    
    //for (k=1;k<=100;k++);
    
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
  	f = rdtsc();
    
    printf("%" PRIu64 "\n", (f-i));
}