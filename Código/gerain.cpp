#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main (void)
{
	
	srand(time(NULL));
	int n;

	n=10;
	int d;
	int m[30][30];
	printf("%d\n",n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			d=1+(rand()%1000);
			m[j][i]=m[i][j]=d;
		}
		//printf("\n");
	}
		for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(m[i][j]==m[j][i])
			{
				printf("%d ",m[i][j]);
			}
		}
		printf("\n");
	}
	
	return 0;	
}