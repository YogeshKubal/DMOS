#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "q.h"

TCB_t *ReadyQ;
TCB_t *Curr_Thread;
int count = 1;

void start_thread(void (*function)(void))
{
	
	stack_t *stack = malloc(8192*sizeof(stack_t));
	TCB_t *tcb = (TCB_t *)malloc(sizeof(TCB_t));
	init_TCB(tcb,function,stack,8192*sizeof(stack_t));
	tcb->thread_id = count;
	count++;
	if(ReadyQ == NULL)
	{
		ReadyQ = newQueue();
	}
	AddQueue(ReadyQ,tcb);
}

void run()
{
	Curr_Thread = DelQueue(ReadyQ);
	ucontext_t parent;     
    	getcontext(&parent);   
    	swapcontext(&parent, &(Curr_Thread->context));  
}

void yield()
{
	TCB_t *Prev_Thread = (TCB_t *)malloc(sizeof(TCB_t));
	AddQueue(ReadyQ, Curr_Thread);
	Prev_Thread = Curr_Thread;
	Curr_Thread = DelQueue(ReadyQ);
	swapcontext(&(Prev_Thread->context),&(Curr_Thread->context));

}


