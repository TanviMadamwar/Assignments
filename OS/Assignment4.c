//Assignment 4
//Program to demonstrate Producer-Consumer Problem using semaphore and mutex

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define SIZE 5

//GOLOBAL VARIABLES
int np,nc, buffer[SIZE],in,out;
sem_t empty,full;
pthread_mutex_t mutex;
int item ,con;

//FUNCTION OF PRODUCER
void * producer(void *arg)
{
     
    int err;
    int i = *(int *)arg;
    while(1)
    {
    	 item=rand()%10;
         sleep(rand()%10);
         
         sem_wait(&empty);
         pthread_mutex_lock(&mutex);
             printf("\nProducer %d produced %d",i+1,item);
             buffer[in] = item;
             in = (in+1)%SIZE;
             printf("\n Buffer Contents: ");
             printf("\n[");
             for(int c=0;c<SIZE;c++)
             {
             	printf("%3d",buffer[c]);	
             }
             printf("]\n");
         pthread_mutex_unlock(&mutex);
         sem_post(&full);
    }
  
}


//FUNCTION OF CUNSUMER
void * consumer(void *arg)
{
    int i = *(int *)arg;
    int con,err;
    while(1)
    {
        sleep(rand()%10);
        sem_wait(&full);
        
        pthread_mutex_lock(&mutex);
             con = buffer[out];
             buffer[out] = 0;
             out = (out+1)%SIZE;
             printf("\nConsumer %d consumed %d",i+1,con);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
   
}

//Main Block
void main()
{    
    int i,res;
    pthread_t pid[10],cid[10];
    in=out=0;
    
    //Initializing buffer
    for(i=0;i<SIZE;i++)
        buffer[i]=0;
        
    printf("\nEnter number of producers : ");
    scanf("%d",&np);
    printf("\nEnter number of consumers : ");
    scanf("%d",&nc);
    
    //Initilizing semaphores
    sem_init(&full,0,0);
    sem_init(&empty,0,SIZE);
    
    //Creating thread
    for(i=0;i<np;i++)
    {
        void * args = &i;
        res = pthread_create(&pid[i],NULL, *producer, (void *)args);
        
        if(res!=0)
        {
            printf("\nError in producer thread creation");
            exit(1);
        }
    }
    
    for(i=0;i<nc;i++)
    {
        void * args = &i;
        res = pthread_create(&cid[i],NULL, *consumer, (void *) args);
        
        if(res!=0)
        {
            printf("\nError in consumer thread creartion");
            exit(1);
        }
    }
    
    //Joining thread
    for(i=0;i<np;i++)
    {
        res = pthread_join(pid[i],NULL);
    }
    
    for(i=0;i<nc;i++)
    {
        res = pthread_join(cid[i],NULL);
    }
}
