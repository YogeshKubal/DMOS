#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"

TCB_t* NewItem()
{
	TCB_t* item = malloc(sizeof(TCB_t));
	item->next = NULL;
	item->prev = NULL;
	return item;
}

TCB_t* newQueue()
{
	TCB_t *head = malloc(sizeof(TCB_t));
	head->prev = head;
	head->next = head; 
	return head;
}

void AddQueue(TCB_t* head, TCB_t* item)
{
	if((head->prev == head) && (head->next == head))
	{
		head->next = item;
		head->prev = item;
		item->next = head;
		item->prev = head;
	}
	else
	{
		head->prev->next = item;
		head->prev = item;
		item->next = head;
		item->prev = head->prev;
	}
}

TCB_t * DelQueue(TCB_t* head)
{	
	TCB_t *temp = NULL;
	if((head->prev == head) && (head->next == head) && (head == NULL))
	{
		printf("Queue is empty !\n");
		return temp;
	}else
	{
		temp = head->next;
		head->next = temp->next;
		temp->next->prev = head;		
	}
	return temp;	
}





