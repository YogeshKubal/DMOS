// CSE-531:Project 5 Submitted by
// Yogesh Kubal(1209536364)
// Aman Karnik(1209536091)


#include <stdio.h>
#include "msgs.h"
#include <string.h>
#include <math.h>



int n;
int clientId = 0;

char *filename[50];



void client()

{	
	int fileType,fileEnd;
	int A[10];
	char ch;
	//char * end_str = ":aa";
	fileEnd = 255;
	printf("In CLIENT\n");
	
	
	clientId++;
	char *fname = strdup(filename[clientId]);
	FILE * fp = fopen(fname,"r");
	fileType = (clientId*10)+0;
	A[0] = fileType;
	int len = strlen(fname);
	int i;
	int j = 1;
	for(i = 0;i<len;i++){
		A[j] = fname[i];
		j++;
		if (j == 10){
			send(&p[99],A);
			j = 1;
			continue;
		}
	}
	A[j] = fileEnd;
	send(&p[99],A);
		
	//printf("Transferred file name");

	
	fileType = (clientId*10)+1;
	
	i = 1;
	while(1){
		A[0] = fileType;
		ch = fgetc(fp);

		if(ch == EOF){
			A[i] = fileEnd;
			send(&p[99],A);
			break;
		}
		A[i] = ch;
		i++;
		
		if(i == 10){
			send(&p[99],A);
			i = 1;
		}
		
	}
	while(1) {yield(); sleep(1);} 
}


void server()
{
	printf("In SERVER\n");
	char* name_array[n];
	int i = 0;
	int fileEnd = 255;
	for(i = 1;i<= n;i++){
		name_array[i] = malloc(sizeof(char)*16);
	}
	int rem;
	int len;
	int quo;
	char ch;
	int A[10];
	while(1)
	{
		sleep(1);
				
		receive(&p[99],A);
		rem=A[0]%10;
		quo=A[0]/10;
		if (rem==0){
			//its a file name
			for(i=1; i<10;i++){
				if(A[i]==255){
					int fname_length=strlen(name_array[quo]);
					char * suffix=".server";
					fname_length+=7;
					char* ser_fname=malloc(sizeof(char)*fname_length);
					strcpy(ser_fname,name_array[quo]);
					strcat(ser_fname,suffix);
					printf("%s", ser_fname);
					name_array[quo]=strdup(ser_fname);
					FILE *fp = fopen(ser_fname, "ab+");
					fclose(fp);
					break;
				}
				len=strlen(name_array[quo]);
				name_array[quo][len]=A[i];
				name_array[quo][len+1]='\0';
			}
		}
		else if(rem==1){
			//its file contents
			FILE *fp = fopen(name_array[quo], "a");
			int flag=0;
			for(i=1;i<10;i++){
				if(A[i]==255){
					fclose(fp);
					flag=1;
					break;
				}
				ch=A[i];
				fputc(ch,fp);

			}
			if (flag==0){
				fclose(fp);
			}
		}		
		sleep(1);
	}
	//sleep(1);
}
int main(int argc, char *argv[]) 
{	
	int i,j=2;
	n= atoi(argv[1]);
	for(i=1;i<=n;i++){
		filename[i]=strdup(argv[j]);
		j++;
	}
	ReadyQ=newQueue();
	InitSem();
	for(i=0;i<n;i++){
		start_thread(&(client));
	}
	start_thread(&(server));

	run();
}


