/*
CS2710: Programming & Data Structures Lab
LAB 6: Partial e-building Trees

Operations of Insert, Delete, Search & Level Order Traversal implemented
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include "partial_tree.h"

int main()
{
	srand(time(NULL));
	clock_t start, end;

	//number of points, ie number of instances
	int NUM_POINTS = 8;
	double xvals[NUM_POINTS], yvals[NUM_POINTS];

	int cnt = 0, i;
	int dirn;

	//maintaing count of inserted and deleted nodes
	int cnt_ins = 0, cnt_del = 0;
	int n, gen;

	BSTnode* root;

	for(n=1024; cnt < NUM_POINTS; n*=2)
	{
		//code executed for n queries
		xvals[cnt] = n;
		cnt_ins = cnt_del = 0;

		start = clock();

		for(i=0; i<n; i++)
		{
			root = NULL;
			BSTnode* mark = NULL;

			// randomly choosing the operation
			dirn = rand()%3;

			// number taken %n to increase probability of deletion
			// otherwise, delete will mainly act as only search
			gen = rand()%(n);
			switch(dirn)
			{
				case 0:
					cnt_ins++;

					root = Insert(root, gen);
					break;

				case 1:
					mark = Search(root, gen);
					break;

				case 2:
					mark = Search(root, gen);

					if(mark)
						cnt_del++;
					else
						break;
					// don't delete a node, rather mark it
					mark->markdel = true;

					// rebuild if more than half the nodes are deleted
					if(cnt_del >= cnt_ins/2)
					{
						root = Delete(root, cnt_del);
						cnt_del = 0;
						cnt_ins -= cnt_del;
					}
					break;

				default: break;
			}
		}

		end = clock();

		yvals[cnt++] = (end - start);

	}

	// commands to create .temp file to store data array used for plotting graph
	char* commandsForGnuplot[] = {"set title \"PLOT_LAB_6\" ", "plot 'DataLab6.temp'"};
	FILE* temp = fopen("DataLab6.temp", "w");

	for(i=0; i<NUM_POINTS; i++)
		fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]);

	LevelOrder(root);

	return 0;
}