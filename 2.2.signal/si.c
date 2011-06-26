#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int piparray[2];
int gi=0;

void function(int i, siginfo_t * info,void * vinfo)
{
	gi=i;
	int x=getpid();
	if(write(piparray[1],&x,sizeof(int))==-1)
	{
//		char *str="error i";
		write(1,"error i",7);
//		puts("error i");
	}
	x=getpgid(x);
	if(write(piparray[1],&x,sizeof(int))==-1)
	{
//		char *str="info error";
		write(1,"info error",10);
//		puts("info error");
	}	
}
int main()
{
	struct sigaction sag;
	if (pipe(piparray) == -1) 
	{
		printf("create of pipe error");
        exit(0);
    }
	sag.sa_sigaction = function;
	sag.sa_flags=SA_SIGINFO; 
	int num;
	for (num=1;num<=31;num++)
		if(num != 9 && num != 19 && sigaction(num, &sag, NULL))
		printf("error: %d\n",num);

	int pid=0, er, gpid=0;

	while(gi!=20)
	{	
		er=read(piparray[0],&pid,sizeof(int));
		if(er==-1 && errno!=EINTR)
		puts("read error");
		else if(er>0)
		{	
			printf ("pid %d\n", getpid());
			read(piparray[0],&gpid,sizeof(int));
			printf ("group pid %d\n", getgid());
		}
	}	
	close(piparray[1]);
	close(piparray[0]);

	return 0;}