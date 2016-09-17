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
int tp0()
{
    return 0;
}

int tp1(int a)
{
    return 0;
}

int tp2(int a, int b)
{
    return 0;
}

int tp3(int a, int b, int c)
{
    return 0;
}

int tp4(int a, int b, int c, int d)
{
    return 0;
}

int tp5(int a, int b, int c, int d, int e)
{
    return 0;
}

int tp6(int a, int b, int c, int d, int e, int f)
{
    return 0;
}

int tp7(int a, int b, int c, int d, int e, int f, int g)
{
    return 0;
}


int main(int argc, char* argv[])
{
	unsigned eax, ebx, ecx, edx, level;
	eax = 1; /* processor info and feature bits */
	level = 1;
  	uint64_t i, f;
    int result;
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    i = rdtsc();
    
    /*-----------------------------------------------------------------------*/

    // result = tp0();
    // result = tp1(1);
    // result = tp2(1,2);
    // result = tp3(1,2,3);
    // result = tp4(1,2,3,4);
    // result = tp5(1,2,3,4,5);
    // result = tp6(1,2,3,4,5,6);
    result = tp7(1,2,3,4,5,6,7);
    

    /*-----------------------------------------------------------------------*/
    
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
  	f = rdtsc();
    
    fprintf(fp, "%d\n", (f-i));
    fclose(fp);

    printf("%" PRIu64 "\n", (f-i));
}