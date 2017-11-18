#include "threads.h"

typedef struct semaphore_t
{
	int counter;
	TCB_t *waitingQ;
}Semaphore_t;

Semaphore_t *CreateSem(int InputValue)
{
	Semaphore_t *sem;
	sem=(Semaphore_t*)malloc(sizeof(Semaphore_t));
	if(sem == NULL)
	{
		exit;
	}
	sem->counter = InputValue;
	sem->waitingQ=newQueue();
	return sem;
}

void P(Semaphore_t *sem)
{
	TCB_t *from = NULL;
	sem->counter = sem->counter - 1;
	if(sem->counter < 0)
	{	
		AddQueue(sem->waitingQ,Curr_Thread);
		from = Curr_Thread;
		Curr_Thread = DelQueue(ReadyQ);
		swapcontext(&from->context,&Curr_Thread->context);
	}
}

void V(Semaphore_t *sem)
{
	TCB_t* curr;
	sem->counter = sem->counter + 1;
	if(sem->counter <= 0)
	{
		curr = DelQueue(sem->waitingQ);
		AddQueue(ReadyQ,curr);
	}
	yield();
}
