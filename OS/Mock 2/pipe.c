#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define READ 0 			//Value for READ
#define WRITE 1			//Value for WRITE
#define SIZE 1000

int main()
{

	int file_d1[2],file_d2[2];
	char buffer[SIZE] ,filename[10],read_f[10],file_data[300];
	int pid,i=0;
	
	if(pipe(file_d1)==-1) 					//Creating Pipe 1
	{
		perror("Pipe not created");
		exit(1);
	}
	
	if(pipe(file_d2)==-1)				//Creating Pipe 2
	{
		perror("Pipe not created");
		exit(1);
	}
	
	pid = fork();					//Creating Parent and child
	
	if(pid < 0)						//Error in creating fork
	{
		perror("Process not created");
		exit(1);
	}
	else if(pid==0)					//Child Process
	{
		close(file_d1[WRITE]);
		read(file_d1[READ],read_f,sizeof(read_f) );
		close(file_d1[READ]);
		sleep(2);
		
		FILE *fp;
		fp = fopen(read_f,"r");
		if(fp==NULL)
		{
			printf("\nFile not present");
			exit(0);
		}
		else
		{
			file_data[i] = getc(fp);
			while(file_data[i]!=EOF)
			{
				file_data[++i] = getc(fp);
			}
			
			write(file_d2[WRITE],file_data,sizeof(file_data));
			close(file_d2[WRITE]);		
		}
	}	
	else 							//Parent Process
	{
		printf("\nEnter file name : ");
		scanf("%s",filename);
		
		close(file_d1[READ]);
		write(file_d1[WRITE],filename,sizeof(filename));
		close(file_d1[WRITE]);
		sleep(2);
		
		read(file_d2[READ],buffer,sizeof(buffer));
		printf("\nFile contents are : \n");
		printf("%s",buffer);
		
		close(file_d2[READ]);
	}
	
	return 0;
}
