#include "linked_list.h"

void AddOnTop(linkedlist** head, int x)
{
	linkedlist* node = (linkedlist*) malloc(sizeof(linkedlist)*1);

	node->val = x;
	node->next = *head;

	*head = node;
}

void Reverse(linkedlist** head)
{
    linkedlist* past = NULL;
    linkedlist* present = *head;
    linkedlist* future;

    while (present != NULL)
    {
        future = present->next;  
        present->next = past;   
        past = present;
        present = future;
    }
    *head = past;
}

void PrintList(linkedlist *head)
{
    linkedlist *ele = head;
    while(ele->next != NULL)
    {
        printf("%d ", ele->val);    
        ele = ele->next;  
    }
    printf("\n");
}