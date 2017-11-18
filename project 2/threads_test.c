#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "threads.h"

int global =0;

void func1()
{
	int local1=0;
	printf("Function 1 is running\n");
	while(1)
	{		
		global++;
		local1++;
		printf("Function 1 Global : %d Local : %d\n",global,local1);		
		sleep(1);
		yield();
	}
}

void func2()
{
	int local2=0;
	printf("Function 2 is running\n");
	while(1)
	{
		global++;
		local2++;
		printf("Function 2 Global : %d Local : %d\n",global,local2);
		sleep(1);
		yield();
	}
}


void func3()
{
	int local3=0;
	printf("Function 3 is running\n");
	while(1)
	{
		global++;
		local3++;
		printf("Function 3 Global : %d Local : %d\n",global,local3);
		sleep(1);
		yield();
	}
}

int main(int argc, char *argv)
{
	start_thread(func1);
	start_thread(func2);
	start_thread(func3);
	run();

}
