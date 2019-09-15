//Assiginment 5
//Program to demonstrate Reader-Writer Problem , where reader is priority

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define SIZE 5

//Global Variables
int nr,nw,buffer[SIZE];
int readcnt;
pthread_mutex_t mutex,wrt;
int item;
int wid=0,rid=0;

//Function  of writer
void * writer(void *arg)
{
     
    int err;
    int i = *(int *)arg;
    while(1)
    {
         item=rand()%13;
         sleep(item);
         if(item == 0)
            item = 2;
         
         pthread_mutex_lock(&wrt);
             printf("\nWriter %d Written %d",i+1,item);
             buffer[wid] = item;
             wid = (wid+1)%SIZE;  
             
             printf("\n Buffer Contents: ");
             printf("\n[");
             for(int c=0;c<SIZE;c++)
             {
                printf("%3d",buffer[c]);
             }
             printf("]\n");
         pthread_mutex_unlock(&wrt);
        
    }
  
}


//Function  of reader
void * reader(void *arg)
{
    int i = *(int *)arg;
    int con,err;
    while(1)
    {
        int temp = rand()%15;

        sleep(temp);
        if(temp == 0)
            temp =2;
        
        pthread_mutex_lock(&mutex);
             
             readcnt++;
             if(readcnt == 1)
                pthread_mutex_lock(&wrt);

        pthread_mutex_unlock(&mutex);
       

        item = buffer[rid];
        buffer[rid] = 0; 
        printf("\nReader %d Read %d ",i+1,item);
        rid = (rid+1)%SIZE;

        pthread_mutex_lock(&mutex);
             
             readcnt--;
             if(readcnt == 0)
                pthread_mutex_unlock(&wrt);
            
        pthread_mutex_unlock(&mutex);

    }
   
}

//Main Function
void main()
{    
    int i,res;
    pthread_t read[10],write[10];
    
    
    //Initializing Buffer
    for(i=0;i<SIZE;i++)
        buffer[i]=0;
        
    printf("\nEnter number of Readers : ");
    scanf("%d",&nr);
    printf("\nEnter number of Writers : ");
    scanf("%d",&nw);
    
    
    readcnt = 0;
    
    //Initializing thread mutex
    pthread_mutex_init( &wrt, NULL);
    pthread_mutex_init( &mutex, NULL);
    

    //Creating thread   
    for(i=0;i<nw;i++)
    {
        void * args = &i;
        res = pthread_create(&write[i],NULL, *writer,args);
        
        if(res!=0)
        {
            printf("\nError in Writer thread creation");
            exit(1);
        }
    }
    
    for(i=0;i<nr;i++)
    {
        void * args = &i;
        res = pthread_create(&read[i],NULL, *reader, args);
        
        if(res!=0)
        {
            printf("\nError in Reader thread creartion");
            exit(1);
        }
    }
    
    //Joining thread
    for(i=0;i<nw;i++)
        res = pthread_join(write[i],NULL);
    for(i=0;i<nr;i++)
        res = pthread_join(read[i],NULL);   
}
