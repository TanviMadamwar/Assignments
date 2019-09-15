//Assignment 6
//Dinning Philosopher problem demonstrated using thread mutex

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define N 5

sem_t c[N];
pthread_mutex_t m;

enum en{THINKING,HUNGRY,EATING};
enum en state[5];

//Function to test if any philosopher is not eating  
void test(int i)
{
    
    if( state[i%1]!=EATING && state[i%4]!=EATING && state[i]==HUNGRY )
    {
        printf("\n\nPhilosopher %d takes fork %d and %d",i+1,((i+4)%N)+1,i+1);
        printf("\nPhilosopher %d is eating\n",i+1);
        state[i] = EATING;
        sleep(rand()%7);
        sem_post(&c[i]);
    }
    
}

//Function to grab force when phiosopher is hungry
void grab_fork(int i)
{
    pthread_mutex_lock(&m);
    printf("\nPhilospher %d is hungry ",i+1);
    state[i] = HUNGRY;
    test(i);
    pthread_mutex_unlock(&m);
    sem_wait(&c[i]);
}


//Function to put fork when phiosopher has done eating
void put_fork(int i)
{
    pthread_mutex_lock(&m);
    state[i] = THINKING;
    test((i+1)%N);
    test((i+4)%N);
    pthread_mutex_unlock(&m);
}

//Function of philosopher
void * philpsopher(void *arg)
{
    int i = *(int *)arg;
    while(1)
    {
        printf("\nPhilospher %d is thinking ",i+1);
        grab_fork(i);
        put_fork(i);
    }
} 

//Main Function
int main()
{
    pthread_t phil[N];
    int i,err;
    
    //Initializating state and semaphore
    for(i=0;i<N;i++)
    {
        state[i] = THINKING;
        sem_init(&c[i],0,0);
    }
    
    //Initializing mutex
    pthread_mutex_init(&m,NULL);
    
    //Creating thread
    for(i=0;i<N;i++)
    {
           void *args = &i;
           err = pthread_create(&phil[i],NULL,philpsopher,args);
           if(err!=0)
            exit(1);
    }
    
    //Joining Thread
    for(i=0;i<N;i++)
    {
        err = pthread_join(phil[i],NULL);
        if(err!=0)
            exit(1);   
    }
    return 0;
}
