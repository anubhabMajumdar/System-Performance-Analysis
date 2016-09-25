#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdlib.h>
#include <sys/time.h>

int size = 1000;
/* Code from linux manual */
uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

typedef struct node{
    int val;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//insert link at the first location
void insertFirst(int val)
{
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->val = val;
   
   //point it to old first node
   link->next = head;

   //point first to new first node
   head = link;
}

//display the list
void printList()
{
   struct node *ptr = head;
   
   //start from the beginning
   while(ptr != NULL)
	{        
      //printf("(%d,%d) ",ptr->val); //We dont need this right now as we are just going to traverse through the list
      ptr = ptr->next;
   }
}

int main(int argc, char* argv[])
{
	unsigned eax, ebx, ecx, edx, level;
	eax = 1; /* processor info and feature bits */
	level = 1;
    uint64_t i, f;
    struct node *p = (struct node *) malloc( sizeof(struct node) );

    // for inserting elements into the linked list
    for(int i=0;i<size;i++){
        srand(time(NULL));
        int r = rand();    //returns a pseudo-random integer between 0 and RAND_MAX
        insertFirst(r);  
    }

    FILE* fp;
    fp = fopen("loop_overhead.txt", "a");
    
    p = head;
    while( p->next ){
        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            
            i = rdtsc();
            p = p->next;  

        __cpuid(level, eax, ebx, ecx, edx); // for serializing the instructions
            f = rdtsc();

        fprintf(fp, "%d\n", (f-i));
              
    }
    fclose(fp); 
}
