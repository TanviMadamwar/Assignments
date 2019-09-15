#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pid,arr[20],arr2[20], n,i,j,temp,min_i;
char output[20];

void bubble_sort()
{
    //Bubble Sort
             printf("\nBubble sort");
            for(i=0;i<n-1;i++)
            {   
                for(j=0;j<(n-1-i); j++)
                {
                    if(arr[j] > arr[j+1])
                    {
                        temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp; 
                    }      
                }
            }
            printf("\nAfter sort elements are : ");
            for(i=0;i<n;i++)
            {
                printf("%d ",arr[i]);
                output[i] = arr[i] + '0';
            }  
            output[i]='\0';
            //End of sort and display

}



void input()
{

    printf("\nEnter number of elements : ");
    scanf("%d",&n);
    printf("\nEnter array elements");
    for(i=0;i<n;i++)
    {
        printf("\nEnter element %d : ",i+1);
        scanf("%d",&arr[i]);
       
    }
    
    printf("\nArray elements are : ");
    for(i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }  
    
}

int main(int argc, char **argv)
{
    
    char *args[10];
    input();
    
    pid=fork();
    if(pid==-1)
    {
        printf("\nError");
    }
    else if(pid==0)
    {
        bubble_sort();
         for(i=0;i<n/4;i++)
            {
                printf("%d ",arr[i]);
  
            } 

        args[0]="./p2";
        args[1]=output;
        args[2]=NULL;
        execv("./p2",args);
      
        
     }   
    else if(pid > 0)
    {
  
        
        printf("\nParent process is running\n");
        wait(NULL);
               
    }
}       
