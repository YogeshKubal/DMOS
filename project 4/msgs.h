#include "sem.h"

# define PORTS 100
# define N 10

struct port {
	Semaphore_t *produce, *consume, *mutex;
	int input, output;
	int message[N][10];
};
struct port Port_set[PORTS];

void InitSem() {
	int i;
	for(i = 0; i < PORTS; i++) {
		Port_set[i].produce = CreateSem(N);
		Port_set[i].consume = CreateSem(0);
		Port_set[i].mutex = CreateSem(1);
		Port_set[i].input = 0;
		Port_set[i].output = 0;
	}
}

void send(int port, int var[]) {
	int j;
	P(Port_set[port].produce);
	P(Port_set[port].mutex);
	for(j = 0; j < 10; j++) {
		Port_set[port].message[Port_set[port].input][j] = var[j];
	}
	Port_set[port].input = (Port_set[port].input + 1) % N;
	V(Port_set[port].mutex);
	V(Port_set[port].consume);
}

void receive(int port, int var[]) {
	int j;
	P(Port_set[port].consume);
	P(Port_set[port].mutex);
	for(j = 0; j < 10; j++) {
		var[j] = Port_set[port].message[Port_set[port].output][j];
	}
	Port_set[port].output = (Port_set[port].output + 1) % N;
	V(Port_set[port].mutex);
	V(Port_set[port].produce);
}





