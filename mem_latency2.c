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
// int mm = (1024*1024)/sizeof(int);

int granularity = 1000;

int main(int argc, char* argv[])
{
	unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t in, f;

	int i,j;
    int *arr;

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    int total = (l1+l2+l3);

    arr = malloc(total*sizeof(int));

    // put array elements in cache
    for(i=0;i<total;i++)
        arr[i] = i;

    // access cache elements

    for(i=0;i<l1;i+=1024)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            in = rdtsc();

            arr[i] = arr[i] + 1;

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            f = rdtsc();

        fprintf(fp, "%d\t%d\n", i ,(f-in));
    }

    for(i=l1;i<l2;i+=1024)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            in = rdtsc();

            arr[i] = arr[i] + 1;

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            f = rdtsc();

        fprintf(fp, "%d\t%d\n", i ,(f-in));
    }

    for(i=l2;i<l3;i+=1024)
    {
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            in = rdtsc();

            arr[i] = arr[i] + 1;

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            f = rdtsc();

        fprintf(fp, "%d\t%d\n", i ,(f-in));
    }

fclose(fp);
}

