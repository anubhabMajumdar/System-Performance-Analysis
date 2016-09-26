#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

int size = 1024*1024;
int step = 5;

int main(int argc, char* argv[])
{
    struct timeval t;
    time_t start_time;
    time_t final_time;

    int a[size],j,i;
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    // Following code is for write Bandwidth
    for(i=0;i<size;i = i+step){
        gettimeofday(&t, NULL);
        start_time = t.tv_usec;
        for( j=0; j<step;j++){
            srand(time(NULL));
            a[i+j] = rand()+5;
        }
        gettimeofday(&t, NULL);
        final_time = t.tv_usec;

        fprintf(fp, "%d\n", (final_time-start_time));
    }
    fprintf(fp, "\n Write BW Ends here \n Read BW Starts here \n");
    
    // Following code is for Read Bandwidth
    int b;
    for(i=0;i<size;i = i+step){
        gettimeofday(&t, NULL);
        start_time = t.tv_usec;
        for( j=0; j<step;j++){
            b = a[i+j] + 10;    
        }
        
        gettimeofday(&t, NULL);
        final_time = t.tv_usec;

        fprintf(fp, "%d\n", (final_time-start_time));

    }
    fclose(fp); 
}
