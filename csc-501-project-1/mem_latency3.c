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
int l4 = (1024*1024)/sizeof(int);

int main()
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

	int i,j;
    int *arr;

    // FILE* fp;
    // fp = fopen("loop_overhead.txt", "a");

    int *l1arr = malloc(l1*sizeof(int));
	int *l2arr = malloc(l2*sizeof(int));
    int *l3arr = malloc(l3*sizeof(int));
    int *l4arr = malloc(l4*sizeof(int));
    
    // L1 cache time
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();
    
    memset(l1arr, 0, l1*sizeof(int));
	
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l1arr memset time = %d\n", (f-in));



	// L2 cache time
	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();
    
    memset(l2arr, 0, l2*sizeof(int));
	
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l2arr memset time = %d\n", (f-in));



	// L3 cache time
	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();
    
    memset(l3arr, 0, l3*sizeof(int));
	
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l3arr memset time = %d\n", (f-in));



    // RAM time
	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();
    
    memset(l4arr, 0, l4*sizeof(int));
	
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l4arr memset time = %d\n", (f-in));





    /* Accessing L1 again */
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();

    memset(l1arr, 0, l1*sizeof(int));

	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l1arr array access second time = %d\n", (f-in));



    /* Accessing L1 again */
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();

    memset(&l2arr[l2/2], 0, l1*sizeof(int));

	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l2arr array access second time = %d\n", (f-in));



    /* Accessing L1 again */
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();

    memset(&l3arr[l3/2], 0, l1*sizeof(int));

	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l3arr array access second time = %d\n", (f-in));





    // Accessing RAM second time
	__cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    in = rdtsc();
    
    memset(&l4arr[l4/2], 0, l1*sizeof(int));
	
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    printf("l4arr memset time = %d\n", (f-in));





}