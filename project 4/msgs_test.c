// Project 4
//Submitted by Yogesh Kubal (1209536364) and Aman Karnik (1209536091)

#include "msgs.h"

int A[10]={0,5,10,15,20,25,30,35,40,45},B[10]={100,200,300,400,500,600,700,800,900,1000}, sPort=99, lPort = 0;

void incrementGlobalA()
{
	int i;
	for(i=0;i<10;i++)
	{
		A[i] = A[i] + 1;
	}
}
void incrementGlobalB()
{
	int j;
	for(j=0;j<10;j++)
	{
		B[j] = B[j] + 1;
	}
}
void printGlobalA()
{
	int i;
	for(i=0;i<10;i++)
	{
		printf("%d,",A[i]);
	}
	printf("\n");
}
void printGlobalB()
{
	int j;
	for(j=0;j<10;j++)
	{
		printf("%d,",B[j]);
	}
	printf("\n");
}

void client1()
{
	printf("In CLIENT 1\n");
	while(1)
	{	
		sleep(1);
		incrementGlobalA();
		printf("Client 1: Local port is %d and sending message to server on port %d\n",lPort,sPort);
		send(sPort,A);
		receive(lPort,B);
		printf("Client 1 received the reply from Server on local port %d and the message is:\n",lPort);
		printGlobalB();
		sleep(1);			
	}
}

void client2()
{
	printf("In CLIENT 2\n");
	while(1)
	{	
		sleep(1);
		incrementGlobalA();
		printf("Client 2: Local port is %d and sending message to server on port %d\n",lPort,sPort);
		send(sPort,A);
		receive(lPort,B);
		printf("Client 2 received the reply from Server on local port %d and the message is:\n",lPort);
		printGlobalB();
		sleep(1);			
	}
}

void client3()
{
	printf("In CLIENT 3\n");
	while(1)
	{	
		sleep(1);
		incrementGlobalA();
		printf("Client 3: Local port is %d and sending message to server on port %d\n",lPort,sPort);
		send(sPort,A);
		receive(lPort,B);
		printf("Client 3 received the reply from Server on local port %d and the message is:\n",lPort);
		printGlobalB();
		sleep(1);			
	}
}

void server()
{
	printf("In SERVER\n");
	while(1)
	{
		sleep(1);
		//printf("  SERVER!! Waiting to receive message from client on server port %d\n",sPort);		
		receive(sPort,A);
		printf("Received message is:\n");
		printGlobalA();
		printf("Server replying to client on local port %d\n",lPort);
		incrementGlobalB();
		send(lPort,B);
		lPort++;
		sleep(1);
	}
	//sleep(1);
}



int main() 
{
	ReadyQ=newQueue();
	InitSem();
	start_thread(&(server));
	start_thread(&(client1));
	start_thread(&(client2));
	start_thread(&(client3));
	run();
}


