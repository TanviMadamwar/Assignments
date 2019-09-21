#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 50
#define READ 0
#define WRITE 1

// Main Method
int main()
{
    int file_d1[2],file_d2[2],i=0;          //File discriptors
    char st[20], file_data[SIZE];
    pid_t pid;                          
    char buffer[SIZE];
    memset(buffer,'\0',SIZE);               
    FILE *fp;                          //File Pointer 
    
    printf("\nEnter filename ");
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
            read(file_d1[READ],buffer,SIZE);
            close(file_d1[READ]);
         
            sleep(2);
            
            
            //Readinf from file
            fp = fopen(buffer,"r");
            if(fp==NULL)
            {
                printf("\nUnable to oprn file");
                return 1;
            }  
            
            file_data[i] = getc(fp);
            while(file_data[i]!=EOF) 
            {
                file_data[i] = getc(fp);
                i++;
            }  
            
            //Writing file contents to Pipe 2
            write(file_d2[WRITE],file_data,SIZE);              
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
            read(file_d2[READ],buffer,SIZE);
            printf("%s",buffer);
            close(file_d2[READ]);
        }
        
    
    exit(EXIT_SUCCESS);
}
