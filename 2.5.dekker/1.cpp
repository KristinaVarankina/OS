#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define A 100000000

volatile int turn;
volatile int sch = 0;
volatile int threads[2];
void  critical_function(int thread_id)
{
	++sch;
}

void* dekker(void* id)
{
	int thread_id=*((int*)id);
    while (sch < A)
    {	
		threads[thread_id] = 1;
        while (threads[1-thread_id])
        {
            if (turn != thread_id)
            {
                threads[thread_id]=0;
                while (turn != thread_id)
				{}
                threads[thread_id]=1;
            }
        }
        if (sch < A) 
        {
		critical_function(thread_id);
		}
        turn=1-thread_id;
        threads[thread_id]=0;
    }
}

int main()
 {
	pthread_t thread_1;
	pthread_t thread_2;
	int id[] = {0,1};
	int stat=pthread_create(&thread_1, NULL, dekker,(void*)&id[0]);
	if (stat)
	{
		printf("can't create 1st thread \n");
		return 1;
	}
	stat=pthread_create(&thread_2, NULL,dekker,(void*)&id[1]);
	if (stat)
	{
		printf("can't create 2st thread \n");
		return 1;
	}
	pthread_join(thread_1,NULL);
	pthread_join(thread_2,NULL);
	printf("%i\n", sch);
	return 0;
}