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


/* Our code */

int main()
{
	int   fd[2], nbytes;
    // int   childpid=1;
    // int i;
    struct timeval t;
    uint64_t start_time;
    uint64_t final_time;
    int* rec;


    pipe(fd);
    
    if (fork() == 0)
    {
        
        /* Child process closes up input side of pipe */
        close(fd[0]);
        /* Send "string" through the output side of pipe */
        
        gettimeofday(&t, NULL);
        start_time = t.tv_usec;
        
        write(fd[1], &(start_time), sizeof(start_time));
        // printf("%d\n", start_time);
        // fprintf(fp1, "%d\n", i);
        // fclose(fp1);

        return 0;
    }
        close(fd[1]);   // close up output side of pipe
        
        nbytes = read(fd[0], rec, sizeof(rec));
        // printf("%d\n", *rec);
        
        gettimeofday(&t, NULL);
        final_time = t.tv_usec;

        FILE* fp;
        fp = fopen("loop_overhead.txt", "a");
        
        
        fprintf(fp, "%d\n", (final_time-(*rec)));
        // fprintf(fp, "%d\n", (f-i));
        fclose(fp);
        //printf("Received string: %s", readbuffer);
    return 0;

}

