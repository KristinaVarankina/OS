#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define mfence asm volatile ("mfence" : : : "memory")

volatile int *Number, *Entering;
int n;
int k=0;
int count=0;

int max (volatile int* arr ) {
    int i, max = 0;
    for ( i = 0; i < n ; i++ ){
        if ( Number[ i ] > max )
			{max = Number[ i ];}
			mfence;}
	return Number[ i ];
}
static void* T1 ( void* args ) {
    pthread_detach( pthread_self() ); 
    int i = k, j;
    while ( 1 ) {
        Entering[ i ] = 1;
			mfence;
        Number[ i ] = 1 + max( Number );
			Entering[ i ] = 0;
		mfence;
        for ( j = 0 ; j < n ; j++ ) {
            while ( Entering[ j ] ) {}
            while ( Number[ j ] != 0 && ( Number[ j ] <  Number[ i ] || ( Number[ j ] == Number[ i ] && j < i ) ) ) {}
        }
		 /* Critical section. */
        printf( "Thread ID: %d start\n", i );
        for ( j = 0 ; j < 0xFFFFFF ; j++ ) {mfence;}
        printf( "Thread ID: %d end\n", i );
		 /* End of critical section. */
        Number[ i ] = 0;
			mfence;
    }
    return NULL;
}
//static void* T2 ( void* args ) {
//    pthread_detach( pthread_self() ); 
 //   int i = 1, j;
 //   while ( 1 ) {
 //       Entering[ i ] = 1;
 //       Number[ i ] = 1 + max( Number );
 //       Entering[ i ] = 0;
  //      for ( j = 0 ; j < n ; j++ ) {
  //          while ( Entering[ j ] ) {}
  //          while ( Number[ j ] != 0 && ( Number[ j ] <  Number[ i ] || ( Number[ j ] == Number[ i ] && j < i ) ) ) {}
   //     }
   //     printf( "Thread ID: %d start\n", i );
    //    for ( j = 0 ; j < 0xFFFFFF ; j++ ) {}
    //    printf( "Thread ID: %d end\n", i );
    //    Number[ i ] = 0;
   // }
   // return NULL;
//}		
int main (int argc,char **argv) {
	if(argc != 2)
        puts("please enter number of processes");
	n=atoi(argv[1]);
    Number = (int *)malloc(n*sizeof(int));
    Entering = (int *)malloc(n*sizeof(int));	
    int i = 0;
    pthread_t t1;

    for ( i = 0 ; i < n ; i++ )
        Number[ i ] = Entering[ i ] = 0;	
	while (count<n){
   if ( pthread_create( &t1, NULL, T1, NULL ) )
     exit( -1 );
	 k+=1;
	 mfence;
	 count++;}
 // if ( pthread_create( &t1, NULL, T2, NULL ) )
 //    exit( -1 );

    while ( 1 ) {}
    return EXIT_SUCCESS;
}