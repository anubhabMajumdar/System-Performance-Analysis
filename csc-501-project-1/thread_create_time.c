#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

/* our code */

void* threadWork(void* arg)
{
	//printf("Thread created\n");
	
}


int main()
{
	struct timeval t;
    time_t start_time;
    time_t final_time;
    
    int id=-1;
    pthread_t thread_id;

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    gettimeofday(&t, NULL);
    start_time = t.tv_usec;

    id = pthread_create(&thread_id, NULL, &threadWork, NULL);
    
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;

  	fprintf(fp, "%d\n", (final_time-start_time));
    fclose(fp);

    // printf("%d\n", (final_time-start_time));
}