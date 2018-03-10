/*
31/07/2017
CS2710	Lab 1
TASK:
Write a program that will search for a given quey element in a UNSORTED array -

a) Assume elements are double and fill array with random double.

b) Simulate tossing of an unbiased coin. If heads, query is a random double, else query is the double stored in random index k ( 0 <= k <= n-1 ).

c) Plot the graph for increasing values of n and time taken.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char* argv[])
{
srand(time(NULL));

clock_t start, end;
double cpu_time_used = 0;
   
int i, j=100, q, coin, k, ans;

int NUM_POINTS = 100; //(int) pow(2, 16) - (int) pow(2, 10);		//fixing range for "n"
int NUM_COMMANDS = 2;
   
   
double xvals[NUM_POINTS], yvals[NUM_POINTS];
    
int n, x, y;
double g, h, qu;
   
while(j--)
{
	x = rand() % (int)pow(2,16);
	y = rand();
	
	if( x < (int)pow(2,10) )
		x+= (int) pow(2,10);
	g = x;
	h = y;
	while( h > 1)
		h = (double) h/10;
	n = g+h;
			
	xvals[j] = n;

	int a[n];

	for( i = 0; i<n; i++ )						//initialising a[n] array with random numbers
		a[i] = rand();
	
	q = 10000;						//number of queries processed for each n

	cpu_time_used = 0;
   
	while(q--)
	{
		start = clock();
		coin = rand()%2;				// simulating coin throw
   	
		if(coin)					//getting query
		{
			x = rand();
			y = rand();

			g = x;
			h = y;
			while(h > 1)
				h = (double) h/10;
				
			qu = g+h;
		}
		else
		{
			k = rand() % n;
			qu = a[k];
		}

		ans = -1;
		
		for(i=0; i<n; i++)			//finding index of query using linear search
			if( qu == a[i] )
			{
				ans = i;
				break;
			}

		end = clock();
		cpu_time_used += ((double) (end - start)) / CLOCKS_PER_SEC;		//summing time for all queries
	}
   
	yvals[j] = (float) cpu_time_used / 10000;		//averaging time for a "n"


	n++;
}
   
char * commandsForGnuplot[] = {"set title \"PLOT_LAB_1_a\"", "plot 'data1.temp'"};
   
FILE * temp = fopen("data1.temp", "w");
/*Opens an interface that one can use to send commands as if they were typing into the gnuplot command line. "The -persistent" keeps the plot open even after the C program terminates.
*/
//FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

for (i=0; i < NUM_POINTS; i++)
	fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);		//Write the data to a temporary file

//for (i=0; i < NUM_COMMANDS; i++)	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); 	//Send commands to gnuplot one by one

return 0;
}
