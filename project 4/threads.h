#include "q.h"

TCB_t *ReadyQ;                      
TCB_t *Curr_Thread;		    
int t_id=0;


void start_thread(void (*function)(void))
{
	int stack_size = 8192;
	void *stackP = malloc(stack_size);
	TCB_t *tcb = newItem();
	init_TCB(tcb, function, stackP, stack_size);
	
	t_id++;
	tcb->thread_id=t_id;
	AddQueue(ReadyQ,tcb);
}

void run()
{   
    Curr_Thread = DelQueue(ReadyQ);
       ucontext_t parent;     
    getcontext(&parent);   
    swapcontext(&parent,&Curr_Thread->context);  
}

void yield() 
{  TCB_t *Prev_Thread;
   AddQueue(ReadyQ, Curr_Thread); 
   Prev_Thread = Curr_Thread;
   Curr_Thread = DelQueue(ReadyQ);
   swapcontext(&Prev_Thread->context, &Curr_Thread->context);
}

void print_tid(TCB_t * tcb){
    printf("%d",tcb->thread_id);
    return;   
}
