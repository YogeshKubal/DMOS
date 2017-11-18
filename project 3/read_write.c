/*CSE 531 Distributed and Multiprocessor Operating Systems
Project 3
Submitted by
Yogesh Kubal(1209536364)
Aman Karnik(1209536091)*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sem.h"

TCB_t * Q;
int readwritecount = 0 , writewritecount = 0 , readcount = 0 , writecount = 0, global_ID = 0;

semaphore_t read_sem,write_sem,mutex;

void reader_entry(int ID)
{

	printf("Reader %d is trying to read\n",ID);
	P(&mutex);
	if(writewritecount > 0 || writecount > 0)
	{
		printf("Reader %d is blocked due to writers\n", ID);
		readwritecount++;
		V(&mutex);
		//Sleep on the read semaphore
		P(&read_sem);
		readwritecount--;

	}
	readcount++;
	if( readwritecount > 0 )
		V(&read_sem);
	else{
		V(&mutex);
	}
}

void reader_exit(int ID)
{
	P(&mutex);
	readcount--;
	printf("Reader %d has finished reading\n", ID);
	
	if(readcount == 0 && writewritecount > 0 )
	{
		//We handle the waiting writers
		V(&write_sem);
	}
	else
		V(&mutex);
}

void writer_entry(int ID)
{
	printf("Writer %d is trying to write\n",ID);
	P(&mutex);
	if(readcount > 0 || writecount > 0 )
	{
		printf("Writer %d is blocked due to Readers\n", ID);
		writewritecount++;
		V(&mutex);
		P(&write_sem);
		writewritecount--;
	}
	writewritecount++;
	V(&mutex);
}

void writer_exit(int ID)
{
	P(&mutex);
	writecount--;
	printf("Writer %d has finished writing\n", ID);
	if(readwritecount > 0)
		V(&read_sem);
	else if( writewritecount > 0 )
		V(&write_sem);
	else
		V(&mutex);
}

void reader()
{
	//printf("Entering reader");
	int ID;
	P(&mutex);
	ID = global_ID++;
	 //printf("[reader: %d] changing ID: \n",ID);
	V(&mutex);
	while(1)
	{
		reader_entry(ID);
		printf("Reader %d is reading\n",ID);
		sleep(1);
		reader_exit(ID);
	};

}

void writer()
{
	int ID;
	P(&mutex);
	ID = global_ID++;
	V(&mutex);
	while(1)
	{
		writer_entry(ID);
		printf("Writer %d is writing\n",ID);
		sleep(1);
		writer_exit(ID);
	};
}
int main()
{
	InitQueue(&Q);
	init_sem(&mutex, 1);
	init_sem(&read_sem, 0);
	init_sem(&write_sem, 0);
	
	start_thread(reader);
	start_thread(reader);
	start_thread(writer);
	start_thread(reader);	
	start_thread(writer);
	
	
	run();
}
