#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

/* code by us */
int tp0()
{
    return 0;
}

int tp1(int a)
{
    return 0;
}

int tp2(int a, int b)
{
    return 0;
}

int tp3(int a, int b, int c)
{
    return 0;
}

int tp4(int a, int b, int c, int d)
{
    return 0;
}

int tp5(int a, int b, int c, int d, int e)
{
    return 0;
}

int tp6(int a, int b, int c, int d, int e, int f)
{
    return 0;
}

int tp7(int a, int b, int c, int d, int e, int f, int g)
{
    return 0;
}


int main(int argc, char* argv[])
{
	int result;
    struct timeval t;
    time_t start_time;
    time_t final_time;
    
    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");

    gettimeofday(&t, NULL);
    start_time = t.tv_usec;
    
    /*-----------------------------------------------------------------------*/

    // result = tp0();
    // result = tp1(1);
    // result = tp2(1,2);
    // result = tp3(1,2,3);
    // result = tp4(1,2,3,4);
    // result = tp5(1,2,3,4,5);
    // result = tp6(1,2,3,4,5,6);
    result = tp7(1,2,3,4,5,6,7);
    

    /*-----------------------------------------------------------------------*/
    
    gettimeofday(&t, NULL);
    final_time = t.tv_usec;
    
    fprintf(fp, "%d\n", (final_time-start_time));
    fclose(fp);

    
}