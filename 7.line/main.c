#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile long long array[100];

void error(char* error_message, int exit_code)
{	printf("%s", error_message);
	exit(exit_code);
}
static void *counter(void *args)
{
	int id = (int)args;
	for(array[id]=0; array[id]<100000000; array[id]++);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	cpu_set_t cpu1, cpu2;
	CPU_ZERO(&cpu1);
	CPU_SET(0, &cpu1);
	CPU_ZERO(&cpu2);
	CPU_SET(1, &cpu2);
	pthread_t thread1;
	pthread_t thread2;
	int distance;

if (argc != 2)
{
	error("Incorrect input parameters\n", 1);
}
distance = strtol(argv[1], NULL, 10);
if (pthread_create(&thread1, NULL, counter, (void*)0))
{
	error("can't create thread\n", 10);
}
if (pthread_create(&thread2, NULL, counter, (void*)distance))
{
   error("can't create thread\n", 20);
}
if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu1))
{
    error("can't set affinity\n", 11);
}
if (pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpu2))
{
    error("can't set affinity\n", 21);
}
if (pthread_join(thread1, NULL))
{
    error("can't join thread\n", 13);
}
if (pthread_join(thread2, NULL))
{
    error("can't join thread\n", 23);
}
	return 0;
}
