#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h> 
#include <err.h>
#include <fcntl.h>

// $ getconf PAGESIZE    Use this to get the pagesize

int size = getpagesize();
/* Code from linux manual */
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(int argc, char* argv[])
{
	unsigned eax, ebx, ecx, edx, level;
	eax = 1; /* processor info and feature bits */
	level = 1;
    uint64_t i, f;

    int fd = -1;
    char *p;
    FILE* fp;    
    fp = fopen("loop_overhead.txt", "a");
    // fd = open("",O_RDWR,);
    
    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions         
    i = rdtsc();
  
    p = (char*)mmap((caddr_t)0, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, fd, 0);

    __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
    f = rdtsc();

    fprintf(fp, "%d\n", (f-i));
    munmap(p,size);
    fclose(fp); 
}