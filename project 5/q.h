#include "TCB.h"

//For returning a pointer to a new q-element
TCB_t * newItem()
{
	TCB_t * item;
	item = (TCB_t*)malloc(sizeof(TCB_t));
	return item;
}





//For creation of an empty queue containing only one dummy element, head
TCB_t * newQueue()
{   TCB_t * head=newItem();
    head->prev=head;
    head->next=head;
    head->thread_id=12;
	return head;
}



void AddQueue(TCB_t *head, TCB_t *item) 
{    
	TCB_t * tail;
	
	if(head->prev==head){
	    
	    head->prev=item;
	    head->next=item;
	    item->next=head;
	    item->prev=head;
	}
	else{
	    tail=head->prev;
	    item->next=tail->next;
	    tail->next=item;
	    item->prev=tail;
	    head->prev=item;
	}
	return ;	
}

TCB_t *DelQueue(TCB_t *head) 
{   TCB_t * temp;
    
    if(head->prev==head){
        printf("\nQueue is empty");
        exit(0);
        return NULL;   
    }
    temp=head->next;
    head->next=temp->next;
    temp->next->prev=head;
    return temp;	
}
