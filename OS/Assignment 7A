/*
PROBLEM STATEMENT : Pipes: Full duplex communication between parent and child processes. Parent process writes a pathname of a fil (the contents of the file are desired) on one pipe to be read by child process and child process writes the contents of the file on second pipe to be read by parent process and displays on standard output.
*/

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 500
#define READ 0
#define WRITE 1

// Main Method
int main()
{
    int file_d1[2],file_d2[2],i=0;          //File discriptors
    char st[20], file_data[SIZE];
    pid_t pid;                          
    char buffer[SIZE],fname[10];
    memset(buffer,'\0',SIZE);
    memset(fname,'\0',10);               
    FILE *fp;                          //File Pointer 
    
    printf("\nEnter filename : ");
    scanf("%s",st);
         
    //Pipe Creation        
    if(pipe(file_d1) == -1)             
    {
        printf("\nUnable to create file discriptor 1");
        exit(0);
    }
    
    if(pipe(file_d1) == -1)
    {
        printf("\nUnable to create file discriptor 2");
        exit(0);
    }
    
    //Forking
    pid = fork();
        
        if(pid < 0)
        {
            fprintf(stderr, "fork failure");
            return 1;
        }
        else if(pid == 0)                       //Child Process
        {
            
            close(file_d1[WRITE]);          
            
            //Reading filename from Pipe1
            read(file_d1[READ],st,strlen(st));
            close(file_d1[READ]);
         
            sleep(2);
            
            
            //Readinf from file
            fp = fopen(st,"r");
            if(fp==NULL)
            {
                printf("\nUnable to open file");
                return 1;
            }  
            
            file_data[i] = getc(fp);
            while(file_data[i]!=EOF) 
            {
                i++;
                file_data[i] = getc(fp);
                
            }  
            i++;
            file_data[i] = '\0';
            
            //Writing file contents to Pipe 2
            write(file_d2[WRITE],file_data,strlen(file_data));              
            close(file_d2[WRITE]);
        }
        else            //Parent Process    
        {
            
            close(file_d2[WRITE]);
            
            //Writing file to Pipe 1
            write(file_d1[WRITE],st,strlen(st));       
            close(file_d1[WRITE]);
            sleep(2);
            
            //Reading pipe contents through Pipe2
            read(file_d2[READ],buffer,1000);
            printf("%s",buffer);
            close(file_d2[READ]);
        }
        
    
    exit(EXIT_SUCCESS);
}
