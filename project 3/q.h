#include"TCB.h"
#include<stdio.h>
#include<stdlib.h>

void InitQueue(TCB_t ** head)
{
        *head=(TCB_t *)malloc(1*sizeof(TCB_t));
        (*head)->next = *head; (*head)-> prev = *head;
}

void AddQueue( TCB_t * head,TCB_t * tcb)
{
	TCB_t *cur = head;
	while(cur->next!=head)
		cur=cur->next;
	cur -> next = tcb;
	tcb-> prev = cur;
	tcb->next = head;
	head-> prev = tcb;
}

TCB_t * DelQueue( TCB_t * head)
{
	TCB_t *cur = head-> next;
	TCB_t *cur_next = cur->next;
	head->next = cur_next;
	cur_next->prev=head;
	return cur;
}

void RotateQueue( TCB_t * head)
{
	if(head->next->next !=head && head->next !=head){
		TCB_t * cur = head->next;
		while(cur->next != head){
			cur = cur->next;
		}
		TCB_t * ret = DelQueue(head);
		cur->next = ret;
		ret->prev = cur;
		ret->next = head;
		head->prev = ret;
	}
}

