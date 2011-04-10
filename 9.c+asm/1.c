#include <stdio.h>

extern int sum(int,int);
int main()
{
	int a=4;
	int b=5;
	int t;
	t = sum(a, b);
	printf("%d + %d = %d\n", a, b, t);
	return 0;
} 