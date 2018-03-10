/*
CS2710: Programming & Data Structures Lab
LAB 7: Red Black Trees

Operations of Insert, Delete, Search & Level Order Traversal implemented
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include "rb_tree.h"

int main()
{
	srand(time(NULL));
	clock_t start, end;

	//number of points, ie number of instances
	int NUM_POINTS = 7;
	double xvals[NUM_POINTS], yvals[NUM_POINTS];

	int n, i, cnt = 0, gen, dirn;
	RBTnode* root = NULL;

	for(n=1024; cnt < NUM_POINTS; n*=2)
	{
		//code executed for n queries
		xvals[cnt] = n;

		start = clock();

		for(i=0; i<n; i++)
		{
			root = NULL;
			RBTnode* mark = NULL;

			//scanf("%d %d", &dirn, &gen);

			// randomly choosing the operation
			dirn = rand()%3;

			// number taken %n to increase probability of deletion
			// otherwise, delete will mainly act as only search
			gen = rand()%(n);

			switch(dirn)
			{
				case 0:
					root = RB_Insert(root, gen);
					break;

				case 1:
					mark = Search(root, gen);
					break;

				case 2:
					mark = Search(root, gen);

					if(mark)
						RB_Del(root, mark);
					else
						break;
					
				default:
					break;
			}
		}
		
		LevelOrder(root);

		end = clock();

		yvals[cnt++] = (end - start);
	}

	// commands to create .temp file to store data array used for plotting graph
	char* commandsForGnuplot[] = {"set title \"CS16B113_RaghavNauhria\" ", "plot 'CS16B113_RaghavNauhria.temp'"};
	FILE* temp = fopen("CS16B113_RaghavNauhria.temp", "w");

	for(i=0; i<NUM_POINTS; i++)
		fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);

	//LevelOrder(root);

	fclose(temp);
	return 0;
}
