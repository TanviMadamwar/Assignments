#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <stdio.h>

//Function Declaration
void input(int *,int ,int );
void display(int *,int ,int );
void* matrix_m(void *);

//Structure Declaration
struct matrix_arr
{
    int *mat1, *mat2, *res;
    int r1,c1,r2,c2;
};


struct matrix_arr *ar1,ar,*last;

//Function to input matrix
void input(int *a,int m,int n)
{   
    int i,j;
    for(i=0;i<m;i++) 
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",(a+i*n+j));
        }
     }      
}

//Function to display matrix
void display(int *a,int m,int n)
{   
    int i,j;
    for(i=0;i<m;i++) 
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",*(a+i*n+j));
        }
        printf("\n");
     }      
}

//Function for matrix multiplication
void* matrix_m(void *marr)
{
    struct matrix_arr * ar2 = (struct matrix_arr *) marr;
    int i,j,k;
    
    if(ar2->c1 == ar2->r2)
    {   
        for(i=0; i<ar2->r1; i++)
        {   
            for(j=0; j<ar2->c2; j++)
            {
              *(ar2->res+i*ar2->c2+j) = 0;
               
                for(k=0; k<ar2->r1; k++)
                {
                    *(ar2->res+i*ar2->c2+j) += *(ar2->mat1+i * ar2->r1+k) * *(ar2->mat2+k * ar2->c2+j);   
                }
            }
        }
        pthread_exit(ar2);
        
    }
    else
    {
        printf("\nNumber of Columns of 1st Matrix  must be equal to Number of Rows of 2nd Matrix");
        pthread_exit(0);
    }
    
}

//Main Function

int main()
{
    int res;
    pthread_t tid;
    void *tRes;
    ar1 = &ar;
    
    printf("\nEnter number of row and column for Matrix 1 : ");
    scanf("%d%d",&ar1->r1,&ar1->c1);
    ar1->mat1 = malloc((ar1->r1*ar1->c1)*sizeof(int));
    
    printf("\nEnter number of row and column for Matrix 2 : ");
    scanf("%d%d",&ar1->r2,&ar1->c2);
    ar1->mat2 = malloc((ar1->r2*ar1->c2)*sizeof(int));
    ar1->res = malloc((ar1->r1*ar1->c2)*sizeof(int));
    
    printf("\nEnter values of 1st matrix\n");
    input(ar1->mat1,ar1->r1,ar1->c1);
    
    printf("\nEnter values of 2nd matrix\n");
    input(ar1->mat2,ar1->r2,ar1->c2);      
    
    printf("\nMatrix 1\n");
    display(ar1->mat1,ar1->r1,ar1->c1);
    
    printf("\nMatrix 2\n");
    display(ar1->mat2,ar1->r2,ar1->c2);   
    
    res = pthread_create(&tid,NULL,matrix_m,(void *)&ar);
    if(res!=0)
    {
        printf("\nError in thread creation");
        exit(1);
    }
    
    res = pthread_join(tid,&tRes);
    if(res!=0)
    {
        printf("\nError in thread joining");
        exit(1);
    }
    
    if(0==(int)tRes)
    exit(0);
    
    printf("\nMatrix Multiplication is :\n");
    last = (struct matrix_arr * )tRes;
    display(last->res,last->r1,last->c2);  
     
    return 0;
}
