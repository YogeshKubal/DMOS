#include"q.h"
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

extern TCB_t * Q;

void start_thread(void (*function)(void))
{
	int stack_size = 8192;
	void *stack = malloc(stack_size);
	TCB_t *tcb = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(tcb,function,stack,stack_size);
	AddQueue(Q,tcb);
}


void run()
{  
    ucontext_t parent;     
    getcontext(&parent);   
    swapcontext(&parent, &(Q->next->context));
}


void yield() 
{
	ucontext_t parent;     
	getcontext(&parent);
	Q->next->context = parent;
	RotateQueue(Q);
	swapcontext(&parent, &(Q->next->context));
}
