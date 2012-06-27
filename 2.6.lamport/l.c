#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

volatile int *Number, *Entering;
int n;
int k=0;
volatile int res = 0 ;

int max (volatile int* arr ) {
int i, max = arr[ 0 ];
for ( i = 1 ; i < n ; i++ )
if ( Number[ i ] > max )
return Number[ i ];
return Number[ 0 ];
}
static void* T1 ( void* args ) 
{
pthread_detach( pthread_self() ); 
int i = (intptr_t)args, j;
for(int z=0;z<10000000;z++) 
{
Entering[ i ] = 1;
Number[ i ] = 1 + max( Number );
Entering[ i ] = 0;
for ( j = 0 ; j < n ; j++ ) {
while ( Entering[ j ] ) {}
while ( Number[ j ] != 0 && ( Number[ j ] < Number[ i ] || ( Number[ j ] == Number[ i ] && j < i ) ) ) {}
}
printf( "Thread ID: %d start\n", i );

res++;

printf( "Thread ID: %d end\n", i );
fprintf (stdout, "%s %d\n","resource=", res);
Number[ i ] = 0;
}
return NULL;
}

int main (int argc,char **argv) {
if(argc != 2)
{
puts("please enter number of processes");
exit( -1 );
}
n=atoi(argv[1]);
Number = (int *)malloc(n*sizeof(int));
Entering = (int *)malloc(n*sizeof(int)); 
int i = 0;
pthread_t *threads = (pthread_t *)malloc(n*sizeof(pthread_t));

for ( i = 0 ; i < n ; i++ )
Number[ i ] = Entering[ i ] = 0; 
for (k=0;k<n;k++)
{
if ( pthread_create( &threads[k], NULL, T1, (void*)(k)) )
exit( -1 ); 
}

for(int j=n-1; j>=0 ; j--)
{
if (pthread_join(threads[j], NULL))
exit( -1 );
}


return EXIT_SUCCESS;
}
