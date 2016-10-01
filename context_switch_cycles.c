#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

/* Code from linux manual */
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

/* Our code */

int main()
{
	int   fd[2], nbytes;
    // int   childpid=1;
    // int i;
    char    string[] = "Hello World\n";
    char    readbuffer[80];
    unsigned eax, ebx, ecx, edx, level;
    eax = 1; /* processor info and feature bits */
    level = 1;
    uint64_t i, f;
    int* rec;
    pipe(fd);
    
    if (fork() == 0)
    {
        
        /* Child process closes up input side of pipe */
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        i = rdtsc();
        
        write(fd[1], &i, sizeof(i));
        
        // fprintf(fp1, "%d\n", i);
        // fclose(fp1);

        return 0;
    }
        close(fd[1]);   // close up output side of pipe
        
        nbytes = read(fd[0], rec, sizeof(rec));

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        f = rdtsc();

        FILE* fp;
        fp = fopen("loop_overhead.txt", "a");
        
        fprintf(fp, "%d\n", (f-(*rec)));
        fclose(fp);
        //printf("Received string: %s", readbuffer);
    return 0;

}

