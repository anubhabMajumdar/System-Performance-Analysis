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
    struct timeval t;
    time_t start_time;
    time_t final_time;

    pipe(fd);
    
    if (fork() == 0)
    {
        /* Child process closes up input side of pipe */
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        

        FILE* fp;
        fp = fopen("loop_overhead.txt", "a");
        
        // __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        // i = rdtsc();
        
        gettimeofday(&t, NULL);
        start_time = t.tv_usec;
        
        write(fd[1], string, (strlen(string)+1));
        
        gettimeofday(&t, NULL);
        final_time = t.tv_usec;

        fprintf(fp, "%d\n", (final_time-start_time));
        // fprintf(fp, "%d\n", (f-i));
        fclose(fp);


        return 0;
    }
        wait(NULL);
        close(fd[1]);   // close up output side of pipe
        
        
        nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

        // __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
        // f = rdtsc();

        
        //printf("Received string: %s", readbuffer);
    return 0;

}

