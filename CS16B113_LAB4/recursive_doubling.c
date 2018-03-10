/*
CS 2710 : Programming and Data Structures Lab
Lab 4 - Prefix sum linked list

Implement prefix sum linked list for a given linked list using recursive doubling.

Attempted By:
Raghav Nauhria
CS16B113
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
    
int main()
{
	linkedlist* head = NULL;

	int x, length, i, jump=1;
	char input;

	//scanf("%c", &input);
	while(input != 10)
	{
		scanf("%d", &x);
		AddOnTop(&head, x);
	
		length++;

		scanf("%c", &input);
	}

	AddOnTop(&head, 0);								//adding dummy value 0 to ease the addition process
	length++;

	Reverse(&head);									//reversing the whole list as it was created by pushing on top.

	linkedlist* ptr[length];						//array of pointers

	ptr[0] = head;
	for(i=1; i<length; i++)							//assigning a pointer to each element
	{
		ptr[i] = ptr[i-1]->next;
	}

	for(jump=1; jump < length; jump*=2)				//recursive doubling
	{
		i=0;
		while(i+jump<length)						//check for length
		{
			ptr[i]->val += ptr[i+jump]->val;
			i++;
		}
	}
	PrintList(head);

	return 0;
}