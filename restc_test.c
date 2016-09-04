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
	unsigned eax, ebx, ecx, edx;
	eax = 1; /* processor info and feature bits */
  	uint64_t i, f;
    
    __cpuid(1, eax, ebx, ecx, edx);
    i = rdtsc();
    
    sleep(10);
    
    __cpuid(1, eax, ebx, ecx, edx);
  	f = rdtsc();
    
    printf("%" PRIu64 "\n", (f-i));
}
