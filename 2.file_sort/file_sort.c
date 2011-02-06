#include <stdio.h>
#include <stdlib.h>
void print_err(char *mes,char *file)
{
	if(file)
	{
		printf("%s",mes);
		printf("%s",file);
	}
	else
		printf("%s",mes);
	exit(1);
}
int cmp(const void *a, const void *b)
{
     return *(int*)a - *(int*)b;
 }
int main(int argc, char *argv[])
{
	FILE *in;
	FILE *out;
	int *numbers=NULL;
	int start=1;
	int count=0;
	int input;
	int *more_numbers;
	int i=0;
	if(argc<3)
		print_err("Wrong parametrs format","");
	while(start<argc-1)
	{
		in=fopen(argv[start],"r");
		if(!in)
			print_err("Couldn't open input file: ",argv[start]);
		while(!feof(in))
		{
			int read=fscanf(in,"%d",&input);
			if(!read)
			{
				if(numbers!=NULL)
					free (numbers);
				fclose(in);
				print_err("Wrong input type in file: ",argv[start]);
			}
			count++;
			more_numbers = (int*) realloc (numbers, count * sizeof(int));
			if (more_numbers) 
			{
				numbers=more_numbers;
				numbers[count-1]=input;
			}
			else
			{
				free (numbers);
				fclose(in);
				print_err("Error (re)allocating memory","");
			}
		}
		start++;
	}
	qsort(numbers, count, sizeof(int),cmp);
	out=fopen(argv[argc-1],"w");
	if(!out)
        print_err("Couldn't create output file: ",argv[argc-1]);
	for(;i<count;i++) 
	{
		int write=fprintf (out,"%d\n",numbers[i]);
		if(!write)
		{
			fclose(out);
			print_err("Couldn't write number to output file","");
		}
	}
	free (numbers);
	return 0;
}