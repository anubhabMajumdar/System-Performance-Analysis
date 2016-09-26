#include <stdint.h>
#include <inttypes.h>
#include <cpuid.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int size = 1000000;

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
    struct timeval t;
    time_t start_time;
    time_t final_time;
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

            
            gettimeofday(&t, NULL);
            start_time = t.tv_usec;

            p->val = p->val + 1;
            p = p->next;  

            gettimeofday(&t, NULL);
            final_time = t.tv_usec;

        fprintf(fp, "%d\n", (final_time-start_time));
              
    }
    fclose(fp); 
}
