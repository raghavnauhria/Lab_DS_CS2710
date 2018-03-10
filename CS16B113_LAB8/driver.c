/*
Lab 8: Disjoint Sets

Disjoint set data structure implemented with support for the following operations

1. Make_set(x) - To create a new set with element x

2. Find_set(x) - Find the set to which x belongs

3. Union(x,6) - Union of two sets containing elements x and y

*/
#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set.h"

int main()
{
	char c;
	int x, y;

	// Enter :
	// 1. "m" to add element "x".
	// 2. "u" to do union of sets containing "x" & "y".
	// 3. "f" to find leader of set containing "x".
	// 4. "q" to exit.
	printf("Enter:\n1. \"m\" to add element \"x\".\n2. \"u\" to do union of sets containing \"x\" & \"y\".\n3. \"f\" to find leader of set containing \"x\".\n4. \"q\" to exit.\n");

	printf("Select operation\n>> ");
	scanf("%c", &c);

	// operation runs until exit value is entered
	while(c != 'q' && c != 'Q')
	{
		printf("Enter the value(s)\n>> ");

		if( c == 'm' )
		{
			scanf("%d", &x);
			Make_set(x);

			printf("New Set has been created.\n\n");
		}
		
		if( c == 'u' )
		{
			scanf("%d %d", &x, &y);
			Union(x, y);

			printf("Union has been done.\n\n");
		}

		if( c == 'f' )
		{
			scanf("%d", &x);
			printf("Leader of set containing x : %d\n\n", Find_set(x));
		}

		printf("Select operation\n>> ");
		scanf("\n%c", &c);
	}

	printf("\nSee you again!!\n");

	return 0;
}