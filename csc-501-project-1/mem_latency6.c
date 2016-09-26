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

int l1 = (32*1024)/sizeof(int);
int l2 = (128*1024)/sizeof(int);
int l3 = (768*1024)/sizeof(int);
int l4 = (1024*1024)/sizeof(int);

int main()
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

	int i,j, temp, cycles=0;
    int *arr;

    // FILE* fp;
    // fp = fopen("loop_overhead.txt", "a");

    int *l1arr = malloc(l1*sizeof(int));
	int *l2arr = malloc(l2*sizeof(int));
    int *l3arr = malloc(l3*sizeof(int));
    int *l4arr = malloc(l4*sizeof(int));
    
    // Data in Ll1cache
    for (int j = 0; j < l1; j++)
    {
        l1arr[j] = j;
    }



	// L2
	for (int j = 0; j < l2; j++)
    {
        l2arr[j] = j;
    }



	// L3 cache time
	for (int j = 0; j < l3; j++)
    {
        l3arr[j] = j;
    }



    // RAM time
	for (int j = 0; j < l4; j++)
    {
        l4arr[j] = j;
    }





    /* Accessing L1 again */
    cycles=0;
    for (int j = 0; j < l1; j++)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        in = rdtsc();

        temp = l1arr[j];

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        f = rdtsc();

        cycles+=f-in-1;
    }
    printf("l1arr array access second time = %d\n", cycles);



    /* Accessing L2 again */
    cycles=0;
    for (int j = 0; j < l1; j++)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        in = rdtsc();

        temp = l2arr[j];

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        f = rdtsc();

        cycles+=f-in-1;
    }

    printf("l2arr array access second time = %d\n", cycles);



    /* Accessing L3 again */
    cycles=0;
    for (int j = 0; j < l1; j++)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        in = rdtsc();

        temp = l3arr[j];

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        f = rdtsc();

        cycles+=f-in-1;
    }


    printf("l3arr array access second time = %d\n", cycles);




    // Accessing RAM second time
	cycles=0;
    for (int j = 0; j < l1; j++)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        in = rdtsc();

        temp = l4arr[j];

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        f = rdtsc();

        cycles+=f-in-1;
    }


    printf("l4arr memset time = %d\n", cycles);





}