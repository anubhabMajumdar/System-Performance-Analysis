#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>

int main()
{
	int i;
	FILE* inpfp;
    inpfp = fopen("sampleFile.txt", "a");

    for (i=1;i<=100000;i++)
    	fprintf(inpfp, "%c", 'a');

    fclose(inpfp);
}