/*
Problem Statement:
Application to demonstrate: Client and Server Programs in which server process creates a shared memory segment and write the message to the shared memory segment.Client process reads the message from the shared memory segment and displays it to the screen.
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>

#define SZ 3                            //data size
#define DATA_NOT_FILLED_BY_SERVER -1    //if the data area has not yet filled
#define DATA_FILLED_BY_SERVER 0         //if server has filled the data
#define DATA_TAKEN_BY_CLIENT 1

typedef struct mem
{
    int status;
    int data[3];
}SHARED_REGION;

int main(int argc,char *argv[])
{
    int shm_id;
    SHARED_REGION *shm_ptr;
    int i,j,ret_val;
    key_t mykey;
    mykey = ftok("," , 'A');
    
    //Taking values from command line
    if(argc!=4)
    {   
        printf("\nNo. arguments are not correct");;
        exit(-1);
    }
    
    //Getting Shared Memory
    shm_id = shmget(mykey,sizeof(SHARED_REGION), IPC_CREAT | 066);
    if(shm_id < 0)
    {
        printf("shmget error");
        exit(-1);
    }
    
    //Shared Memory Attachment
     shm_ptr = (SHARED_REGION*)shmat(shm_id,NULL,0);
     if((int)shm_ptr == -1)
     {
        printf("\nshmat error");
        exit(-1);
     }
     
     //Transferring data to Shared Memory
      printf("server : shared region is attached at : %x\n", shm_ptr);
      shm_ptr->status = DATA_NOT_FILLED_BY_SERVER;
      j=1;
      for(i=0; i< SZ;i++)
      {
        shm_ptr->data[i] = atoi(argv[j]);
        ++j;
      }  
      
      shm_ptr->status = DATA_FILLED_BY_SERVER;
      
      while(shm_ptr->status!=DATA_TAKEN_BY_CLIENT)
      {
        sleep(1);
        printf("\nServer Waiting");
      }
      printf("\nClient has received Data");
      
      //Shared Memory Detachment
      ret_val= shmdt((void*)shm_ptr);
      if(ret_val <0)
      {
        printf("\nDetach error");
        exit(-1);
      }
      return 0;
}
