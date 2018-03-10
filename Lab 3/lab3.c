/*
14/08/2017

CS2710	Lab 3

TASK: Implementing dynamic array.

Array should support 2 operations - 
i) Addition
ii) Deletion.
These operations dynamically expand and contract the size of array as and when needed.

a) Output time taken for N queries

b) Plot the graph for increasing values of i (2^10 to 2^15) v/s time taken.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double cpu_time_used = 0;

int* a;
int* temp;

int len = 1;
int count = 0;												// to keep a track of the number of elements

void add(int x)
{
	int i;

	if(len-count <= 1)
	{
		len *= 2;
		temp = (int*)malloc(sizeof(int)*len);				// assigning temp pointer to a new array of double size

		for(i=0; i<count; i++)								// copying elements from previous array to new one
			temp[i] = a[i];

		free(a);											// freeing the memory of the previous array

		a = temp;											// assigning the main array pointer to this new array
	}
	
	a[count] = x;
}


void del()
{
	int i;

	if(count <= len/4)
	{
		len /= 2;
		temp = (int*)malloc(sizeof(int)*len);				// repeating same steps as in add(x); except halving the length

		for(i=0; i<count; i++)
			temp[i] = a[i];

		free(a);

		a = temp;
	}
}

int iteration(int N)
{
	int coin, x;

	cpu_time_used = 0;

	for(int i=0; i<N; i++)
	{
		start = clock();
		coin = rand() % 100 + 1;							// simulating coin throw
  	
		if(coin <= 40 && count > 0)							// cap of 40 to have 40% deletions
		{
			del();
			count--;
		}
		else
		{
			x = rand();
			add(x);
			count++;
		}
	
		end = clock();
	
		cpu_time_used += ((double) (end - start));			// summing time for all queries. CLOCKS_PER_SEC not used as time too less
	}

	return cpu_time_used;
}

int main()
{
srand(time(NULL));

int N;

a = (int*)malloc(sizeof(int)*1);

scanf("%d", &N);

double answer = 0;

answer = iteration(N);										// time taken for N queries

printf("%lf\n", answer);

int NUM_POINTS = 6;
double xvals[NUM_POINTS], yvals[NUM_POINTS];

int i, j=0;

for(i=1024; i<= 32768; i*=2)								// loop from 2^10 to 2^15 queries
{
	answer = iteration( i );

	xvals[j] = i;
	yvals[j++] = (float) answer;							// storing these in an array for graph plotting
}


char* commandsForGnuplot[] = {"set title \"PLOT_LAB_3\"", "plot 'DataLab3.temp'"};
   
FILE * temp = fopen("DataLab3.temp", "w");

for (i=0; i < NUM_POINTS; i++)
	fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);		//Write the data to a temporary file

return 0;
}