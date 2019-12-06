#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main (int argc,char ** argv) 
{

	int n =atoi(argv[1]);
	double media;
	double r;
	int a;
	int j;
	j=0;
	media=0;
	FILE * file = fopen("medias","a+");
	for(int i=0;i<300;i++)
	{
			scanf("%d %lf",&a,&r);
			j++;
			media+=r;
			if(j==n-1)
			{
				media=media/n;
				fprintf(file,"%d %lf\n",a,media);
				j=0;
				media=0;
			}
	}

}