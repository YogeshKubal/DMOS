#include "sem.h"

# define PORTS 100
# define N 10

// Port definition
typedef struct port {
	Semaphore_t *produce, *consume, *mutex;
	int input, output;
	int message[N][10];
}Port_set;
Port_set p[PORTS];

// Initialize all the semaphore variables. And message buffer in and out pointer
void InitSem() {
	int i;
	for(i = 0; i < PORTS; i++) {
		p[i].produce = CreateSem(N);
		p[i].consume = CreateSem(0);
		p[i].mutex = CreateSem(1);
		p[i].input = 0;
		p[i].output = 0;
	}
}

// Add message to a particular port
void send(Port_set *p1, int var[]) {
	int j;
	P(p1->produce);
	P(p1->mutex);
	for(j = 0; j < 10; j++) {
		p1->message[p1->input][j] = var[j];
	}
	p1->input = (p1->input + 1) % N;
	V(p1->mutex);
	V(p1->consume);
}

// Remove message from the port 
void receive(Port_set *p1, int var[]) {
	int j;
	P(p1->consume);
	P(p1->mutex);
	for(j = 0; j < 10; j++) {
		var[j] = p1->message[p1->output][j];
	}
	p1->output = (p1->output + 1) % N;
	V(p1->mutex);
	V(p1->produce);
}





