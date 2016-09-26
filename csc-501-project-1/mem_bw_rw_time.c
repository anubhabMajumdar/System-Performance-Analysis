#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

uint64_t size = 1024 * 1024; // (8 * 1024 * 1024) is the size of the array created (in bytes)
int step = 1; // Loop unrolling is not implemented in the program

int main(int argc, char* argv[])
{
    struct timeval t;
    time_t start_time;
    time_t final_time;
    uint64_t time_diff;
    int a[size],j,i;
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");
    
    gettimeofday(&t, NULL);
    start_time = t.tv_usec;
    // Following code is for write Bandwidth
    for(i=0;i<size;i = i++){
            a[i] = 10;
        }
    }
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;

    time_diff = (final_time-start_time);
    fprintf(fp,"\nWrite time for entire array (2MB) is %d\n",time_diff );
    
    fprintf(fp, "\n Write BW Ends here \n Read BW Starts here \n");
    
    // Following code is for Read Bandwidth
    int b;
    gettimeofday(&t, NULL);
    start_time = t.tv_usec;
    for(i=0;i<size;i = i++){
            b = a[i] + 10;    
    }
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;  
    fprintf(fp, " \nRead time for (2MB) is %d micro seconds \n", (final_time-start_time));
    printf(" \n Read BW in total in per sec : TBF\n" );	
    			
    fclose(fp); 
}
