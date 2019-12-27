// Program to demonstrate N Queens problem

#include<iostream>
#include <cstdlib> 
using namespace std;
int col[10]; // To store column no. where queen can be placed
			// Index determines row

//Printing matrix
void print(int n)
{
	int i,j,q=1;
				cout<<"\n";
				for(i=1;i<=n;i++)
				{
					for(j=1;j<=n;j++)
					{
						if(j==col[i])
						{
							cout<<" "<<q<<" ";
							q++;
						}
						else
							cout<<" 0 "; 	
					}
					cout<<"\n";
}
}

// k  No. of Row / No. of Queen
// i Column
// checking condition to place a queen 
// checking by columns stored in global array

int place(int k ,int i)
{
	int j;
	for(j=1;j<=(k-1);j++)
	{
		//Column check and diagonal check
		if(col[j]==i || abs(col[j]-i) == abs(j-k) )
			return 0;
	}	
	return 1;
}

//Recursive funtion to place a queen at non attacking position
void NQueens(int k, int n)
{
	int i,j,q=1;
	
	for(i=1;i<=n;i++)
	{
		if(place(k,i))
		{
			col[k]=i;
			if(k==n)
			{
				print(n);
			}
			else
				NQueens(k+1,n);
		}
	}
}

int main()
{
	int n;
	cout<<"\nEnter number of Queens you want to place : ";
	cin>>n;
	cout<<"\nColumns aquired by queens are : \n";
	NQueens(1,n);	
}
