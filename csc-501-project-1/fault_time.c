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

int size = 4096;

int main(int argc, char* argv[])
{
    struct timeval t;
    time_t start_time;
    time_t final_time;

    int fd = -1;
    char *p;
    FILE* fp;    
    fp = fopen("loop_overhead.txt", "a");
    // fd = open("",O_RDWR,);    
            
    gettimeofday(&t, NULL);
    start_time = t.tv_usec;
    
    p = (char*)mmap((caddr_t)0, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, fd, 0);

    gettimeofday(&t, NULL);
    final_time = t.tv_usec;

    fprintf(fp, "%d\n", (final_time-start_time));
    printf(" \n Time for accessing a byte is ( Page size is 4096B) %f\n",((final_time-start_time)/4096));          
    fclose(fp); 
}
