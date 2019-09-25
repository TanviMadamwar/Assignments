/*
PROBLEM  STATEMENT : FIFOs: Full duplex communication between two independent processes. First process accepts sentences and writes on one pipe to be read by second process and second process counts number of characters, number of words and number of lines in accepted sentences, writes this output in a text file and writes the contents of the file on second pipe to be read by first process
and displays on standard output.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#define MAX_BUF 1024



int main()
{
    int fd1, fd2,c=0,i,words=0,lines=0,chars=0;
    pid_t pid;
    char buffer[MAX_BUF];   
    char *fifo1="fifo1";                                        
    char *fifo2="fifo2", str[MAX_BUF],ch;
      
    mkfifo(fifo1,0777);                        // FIFO pipe     
    mkfifo(fifo2,0777);                        // FIFO pipe                 
    
    fd1 = open(fifo1,O_RDWR);                  // Opening pipe fd1                 
    fd2 = open(fifo2,O_RDWR);                  // Opening pipe fd2     
    
    pid = fork();                              // Forking 
    
    if(pid < 0)
    {
        perror("Fork failure");
    }
    else if(pid ==0)                          // Child Process
    {
          
          
           //Reading from fifo1
          read(fd1,buffer,sizeof(buffer));
          
           i =0;
           //Calculating no. of words,chars and lines
           
           while(buffer[i]!='\0')
           {
             if(buffer[i]==' '||buffer[i]=='\n')
                 {words++;}
             else
                 {chars++;}
             if(buffer[i]=='\n')
                 { lines++;}
              i++;
          }
           
           sprintf(str, "\nNumber of words : %d\nNumber of characters : %d\nNumber of lines : %d\n",words,chars,++lines);
           
           //Writing senetnece to fifo2
            write(fd2,str,sizeof(str));
    }
    else                                       // Parent Process 
    {
           printf("\nEnter some senetence \n\n");
           while((ch = getchar())!='#')
           buffer[c++] = ch;
           buffer[c]='\0';
           
           //Writing senetnece to fifo1
           write(fd1,buffer,sizeof(buffer));           
           sleep(2);
           
           //Reading from fifo2
           read(fd2,str,sizeof(str));
           printf("\n!!----Sentence Details----!!");
           printf("%s",str);   
    }
    
    //Closing both pipes
    close(fd1);
    close(fd2);
    return 0;
}
