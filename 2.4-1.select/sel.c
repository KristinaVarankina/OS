#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int i = 1,max = 0;
int main (int argc, char**argv)
{
int *arg = (int *)malloc((argc-1)*sizeof(int));
//int arg[argc];
fd_set set;
fd_set tmp;
int res;
FD_ZERO(&set);

for (i = 0; i< argc-1; ++i)
	{
	arg[i] = (int)(strtol(argv[i+1],NULL,10));
//	arg[i]=atoi(argv[i]);
	FD_SET(arg[i],&set);
	if(arg[i] > max)
		max=arg[i];
	}
	max++;
char buf[20];
for (tmp=set;1;set=tmp)
	{
	if(select(max,&set, NULL, NULL, NULL) == -1)
		{printf("Error");	
		exit(0);}
	for(i = 0; i< argc-1; ++i)
			{
			if (select(max,&set, NULL, NULL, NULL) > 0)
				{
				if (FD_ISSET(arg[i],&set)!=0)
					{
					res=read(arg[i], buf, 20);
					if (res < 0)
						{printf("Error");	
						exit(0);}
					else
						write(1, buf, res);
					}
				}else if (select(max,&set, NULL, NULL, NULL) < 0)
				printf("error on select(): %d\n", strerror(errno));
			}
	}
free(arg);
return 0;
}