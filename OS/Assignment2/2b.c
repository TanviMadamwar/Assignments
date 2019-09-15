#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char *argv[])
{
    
    int arr[20],i,n,m,c=0,l,u,mid;
    i=0;
    char k;
    printf("\nIn p2");
    n = strlen(argv[1]);
    for(i=0;i<n;i++)
    {
      
        arr[i]= argv[1][i] - '0';

    }
    printf("\n\nThe Received Array is : \n");
    for(i=0;i<n;i++)
    printf("\n%d ",arr[i]);
    
    printf("\n\nEnter the number to be searched  :  ");
    scanf("%d",&m);
     
    	
	
       	l=0,u=i-1;
    	while(l<=u)
	    {
        	mid=(l+u)/2;
        	if(m==arr[mid])
		    {
             		c=1;
             		break;
         	}
         	else if(m<arr[mid])
	 	    {
         		u=mid-1;
         	}
         	else
	 	{
             		l=mid+1;
	 	}
    	}
    	if(c==0)
        	printf("\n\nThe number %d is not found.\n\n",m);
    	else
         	printf("\n\nThe number %d is found at %d Position.\n\n",m,mid+1);

    return 0;
} 
