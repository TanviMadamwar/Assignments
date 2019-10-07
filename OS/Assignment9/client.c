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

int main()
{
	int shm_id;
	SHARED_REGION *shm_ptr;
	int i,j,ret_val;
	int client_data[SZ];
    key_t mykey;
    mykey = ftok("," , 'A');
     
     //Geting Shared Memory
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
      printf("client : shared region is attached at : %x\n", shm_ptr);
      while(shm_ptr ->status == DATA_NOT_FILLED_BY_SERVER)
      {
        ;
      }
      
      //Fetching data from Shared Memory
      printf("Data Ready");
      for(i=0;i<SZ;i++)
      {
        client_data[i] = shm_ptr->data[i];
      }
      printf("\nData is : \n");
      for(i=0; i<SZ ; i++)
     {
		printf("data[%d] = %d\n", i , client_data[i]);
	 }
      
   
    return 0;	
}
