/*
7th August, 2017

Lab 2: Invariant Property

Allocating and relieving memory as per request with unique user ID:

-> Implented using arrays

-> Allocated and free list printed in the end

*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int alloclist[MAX_SIZE][3];											// 3 columns each for UID, first index, memory allocated
int freelist[MAX_SIZE][2];
int totalfree = MAX_SIZE;

int uid = 0;														//user ID; unique for every user
int count = 0;														//number of users occupying memory space

void request(int);
void garbageCollection();
void release(int);


void garbageCollection()
{
	int i, j;
	
	freelist[0][0] = 0;
	freelist[0][1] = totalfree-1;									//pushing all free memory to top slot
	
	for(i=1; i<MAX_SIZE; i++)
		for(j=0; j<2; j++)
		{
			freelist[i][j] = -1;									//flagging rest of the array
		}
	
	alloclist[0][1] = freelist[0][1]+1;

	for(i=1; i<count; i++)
		alloclist[i][1] = alloclist[i-1][1] + alloclist[i-1][2];	//redeclaring values in allocated list
	
}


void request(int mem)
{
	int i, flag = -1;
	
	//if(mem > totalfree)											//checking for net memory
	//return -1;
		
	for(i=0; freelist[i][0] != -1; i++)
	{
		if(freelist[i][1]-freelist[i][0]+1 >= mem )
		{
			alloclist[count][0] = uid;

			alloclist[count][1] = freelist[i][0];
			alloclist[count][2] = mem;
			
			freelist[i][0] += mem;
			uid++;

			flag = 1;
		}
	}
	
	if( flag != 1)
	{
		garbageCollection();
		request(mem);
	}
}


void release(int index)
{
	int i, j;

	for(i=0; i<count; i++)											//finding match for requested user ID
		if(index == alloclist[i][0])
		{
			break;
		}

	for(j=0; j<MAX_SIZE; j++)										//finding end of free list
		if(freelist[j][0] == -1)
		{
			j--;
			break;
		}
	

	for(; j>=0; j--)												//inserting new element in free list using Insertion Sort
		if(alloclist[i][1] < freelist[j][0])
		{
			freelist[j+1][0] = freelist[j][0];
			freelist[j+1][1] = freelist[j][1];
		}
		else
		{
			break;
		}
	
	freelist[j+1][0] = alloclist[i][1];
	freelist[j+1][1] = alloclist[i][1] + alloclist[i][2] - 1;		//now the sort is maintained in the free list
		

	

	totalfree += alloclist[i][2];									//incrementing net free memory

	for(j=0; j<3; j++)												//exchanging value of last value of alloc with requested index
	{
		alloclist[i][j] = alloclist[count-1][j];
		alloclist[count-1][j] = -1;
	}
}


int main()
{
int i, j;

for(i=1; i<MAX_SIZE; i++)											//initialsing free list
	for(j=0; j<2; j++)
	{
		freelist[i][j] = -1;
	}

freelist[0][0] = 0;
freelist[0][1] = MAX_SIZE-1;

int n;
int x, flag = 0;

scanf("%d", &n);													//number of operations

while(n--)
{

	scanf("%d %d", &flag, &x);

	if(flag == 1)													//deciding course of action as per request
	{
		totalfree -= x;
		request(x);

		count++;
	}
	else
	{
		release(x);
		count--;
	}
}


printf("allocated list:\n");										//printing alloc and free list

for(i=0; i<count; i++)
	printf("%d %d %d\n", i, alloclist[i][1], alloclist[i][2]);

printf("free list:\n");

for(i=0; freelist[i][0] != -1; i++)
	printf("%d %d %d\n", i, freelist[i][0], freelist[i][1]);

return 0;
}