#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	srand(time(NULL));
	clock_t start, end;

	// number of elements in the array
	int NUM_POINTS = 7;
	double xvals[NUM_POINTS], yvals[NUM_POINTS];
	
	int x;

	for(x=0; x<NUM_POINTS; x++)
	{
		int i, j;
		int k = rand()%16;
		int n = pow(2, k);
		int * a = (int*) malloc(n*sizeof(int));

		xvals[x] = n;

		// random initialisation of array
		for(i=0; i<n; i++)
			a[i] = rand()%n;
	
		int * heap = (int*)malloc((2*n-1)*sizeof(int));
		int count = 2*n-1;

		for(i=0; i<n; i++)
			heap[i+n-1] = a[i];

		// building heap from bottom-up

		// k levels
		for(i=1; i<=k && count > 1; i++)
		{
			// each level allows 2^(k-i) computations
			for(j=1; j<= pow(2, k-i) && count > 1; j++)
			{
				heap[(count-2)/2] = heap[count-2] + heap[count-1];
				count -= 2;
			}
		}

		start = clock();
		int coin, t, p;

		for(i=0; i<n; i++)
		{
			// selecting operation
			coin = rand()%2;

			// select index to operate on
			t = rand()%n;

			// select value to be added (if)
			p = rand();

			if(coin)
			{
				
			}
			else
			{
				int temp = t+n-1;

				// increase in last level of heap i.e. effectively in the array
				heap[temp] += p;

				// recursively increase along the levels of the heap
				while(temp)
				{
					heap[(temp-1)/2] += p;
					temp = (temp-1)/2;
				}
			}
		}

		end = clock();

		yvals[x] = end-start ;
	}


	char* commandsForGnuplot[] = {"set title \"DataLab7\" ", "plot 'DataLab7.temp'"};
	FILE* temp = fopen("DataLab7.temp", "w");

	for(x=0; x<NUM_POINTS; x++)
		fprintf(temp, "%lf %lf \n", xvals[x], yvals[x]);

	return 0;
}