#include<stdio.h>
#include<stdlib.h>

typedef struct list
{
	int val;
	struct list* next;
} linkedlist;

void AddOnTop(linkedlist** head, int x);

void Reverse(linkedlist** head);

void PrintList(linkedlist *head);