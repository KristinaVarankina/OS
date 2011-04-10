#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define x 2500
#define y 100

int main()
{
	int x = y = 500;
	int matr[x][y];
	int rep=1000;
	int i,j,k,tmp;
	clock_t time1,time2,time3;
	time1 = clock();
	for(k=0; k<rep; k++)
		for(i=0; i<x; i++)
			for(j=0; j<y; j++)
				tmp+=matr[i][j];
	time2 = clock();
	for(k=0; k<rep; k++)
		for(i=0; i<x; i++)
			for(j=0; j<y; j++)
				tmp+=matr[j][i];
	time3 = clock();
	printf("summarize by rows: %d clock ticks\n summarize by columns: %d clock ticks\n", (int)(time2-time1), (int)(time3-time2));
	return 0;
}