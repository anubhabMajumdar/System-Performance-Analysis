#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

int size = 1000;

int main(int argc, char* argv[])
{
    struct timeval t;
    time_t start_time;
    time_t final_time;

    int a[size];
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    // Following code is for write Bandwidth
    for(int i=0;i<size;i = i+5){
        gettimeofday(&t, NULL);
        start_time = t.tv_usec;

        srand(time(NULL));
        a[i] = rand()+5;   
        a[i+1] = rand();
        a[i+2] = rand();
        a[i+3] = rand();
        a[i+4] = rand();

        gettimeofday(&t, NULL);
        final_time = t.tv_usec;

        fprintf(fp, "%d\n", (final_time-start_time));
    }
    fprintf("\n Write BW Ends here \n Read BW Starts here \n");
    
    // Following code is for Read Bandwidth
    int b,c,d,e,f;
    for(int i=0;i<size;i = i+5){
        gettimeofday(&t, NULL);
        start_time = t.tv_usec;
        
        b = a[i] + 5;
        c = a[i+1] + 10 ;
        d = a[i+2];
        e = a[i+3];  
        f = a[i+4];      

        gettimeofday(&t, NULL);
        final_time = t.tv_usec;

        fprintf(fp, "%d\n", (final_time-start_time));

    }
    fclose(fp); 
}
