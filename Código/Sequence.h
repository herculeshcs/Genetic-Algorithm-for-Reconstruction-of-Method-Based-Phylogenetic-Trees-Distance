#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __SEQ_H
#define __SEQ_H

class Sequence{
public:
	Sequence(int n)
	{
		s = new char[n];
		this->n = n;
	}
	Sequence (char * s)
	{
			int n = strcmp(s);
			this->s = new char[n+1];
			strcpy(this->s,s);
			this->n = n;
	}
	// retorna o valor do alinhamento otimo entre duas sequencias
	int aling ( Sequence *, Sequence *);
	char * s;
	int n;
	// valores para medir os alinhamentos
	static int gap;
	static int match;
	static int missmatch;
	private:
		// métodos para realizar o alinhamento
		int max(int,int,int);
		int f(char, char);

};
inline int Sequence ::max(int a,int b, int c)
{
	int max = a;
	if(b>max)
		max = b;
	if(c>max)
		max = c;
	return max;

}
inline int Sequence::f(char a,char b)
{
	if(a==b)
	{
		return match;
	}
	else
	{
		return missmatch;
	}
}
// Depois fazer com espaço linear : D.
inline int  Sequence::aling ( Sequence *S1, Sequence *S2)
{
	 int **matrix = new int*[s1->n];
	 int n,m,i,j;
	 char *a,*b;
	 a = S1->s;
	 b= S2->s;
	 n= s1->n;
	 m= s2->n;
	  for(int i =0 ; i < s1->n;i++)
	  {
	  	matrix[i] = new int[s2->n];
	  }

	  for(i=0;i<n;i++)
	{
		matrix[i][0]= gap*i;

	}
	for(i=0;i<m;i++)
	{
		matrix[0][i]= gap*i;

	}
	for(i=1;i<n;i++)
	{
		for(j=1;j<m;j++)
		{
			matrix[i][j]= max(matrix[i-1][j-1]+f(a[i],b[j]),matrix[i][j-1]+gap,matrix[i-1][j]+gap);

		}
	}
	 
	return M[i][j];
}


#endif