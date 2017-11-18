#include <malloc.h> 
#include "threads.h"


typedef struct semaphore{
     TCB_t *queue;
     int count;
} semaphore_t;

extern TCB_t * Q;

void init_sem(semaphore_t *s, int i)
{  
	s->count = i;
	InitQueue(&s->queue);
}


/*
 * The P routine decrements the semaphore, and if the value is less than
 * zero then blocks the process 
 */
void P(semaphore_t *sem)
{    
	sem->count--;
	if (sem->count < 0) 
	{
		TCB_t *p=DelQueue(Q);
		AddQueue(sem->queue,p);
		swapcontext(&(p->context),&(Q->next->context));
	}
}


/*
 * The V routine increments the semaphore, and if the value is 0 or
 * negative, wakes up a process and yields
 */

void V(semaphore_t *sem)
{    
	sem->count++;
	if (sem->count <= 0)
	{
			TCB_t *temp = DelQueue(sem->queue);
			AddQueue(Q,temp);
	}
	yield();
}


