#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "matrix.h"


void Matrix::copy(Matrix * dest,const Matrix * ori)
{
	for(int i =0;i<dest->n;i++)
	{
		for(int j=0;j<dest->m;j++)
		{
			dest->matrix[i][j]=ori->matrix[i][j];
		}
	}
}


void Matrix::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
					printf(" %lf ",matrix[i][j]);
		
		}
					printf("\n");
	}
}

void Matrix::printInt()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
					printf(" %0.lf ",matrix[i][j]);
		
		}
					printf("\n");
	}
}

Matrix& Matrix::mult(Matrix & a, Matrix & b)
{
	//printf("oi\n");
			Matrix * c;		
	if(a.m != b.n)
	{
		printf("não é possivel multiplicar\n");
		return *c;

	}
	double aux;
	c= new Matrix(a.n,b.m);
	printf("%d \n",a.n );
	for (int i = 0; i < a.n; i++)
	{
		//printf("oi\n");
		for(int j = 0; j< b.m; j++)
		{
			c->matrix[i][j]=0;
			aux=0;
			for(int k =0; k < a.m; k++)
			{
				printf("i %d j  %d = a[%d][%d]*b[%d][%d] \n",i,j,i,k,k,j);
				aux += a.matrix[i][k]* b.matrix[k][j];
			}
			c->matrix[i][j]=aux;

		}
	}
	return *c;
}

void Matrix::min(int *a, int *b)
{
	double min = this->matrix[0][0];
	double mini=0,minj=0;
	for(int i =0;i<this->n;i++)
	{
		for(int j =0;j<this->m;j++)
		{
			if(this->matrix[i][j]<min)
			{
				min= this->matrix[i][j];
				mini=i;
				minj=j;
			}
		}
	}
	(*a)=mini;
	(*b)=minj;
}


void Matrix::updateMatrixSeparation(Matrix *d,Matrix* q,double * u, int a)
{
	double aux1=0,aux2=0;
	for(int i=0;i<d->n;i++)
	{

		for(int j=0;j<d->n;j++)
		{	aux1=aux2=0;
			if(i!=j)
			{
				for(int k =0;k<d->n;k++)
				{
					aux1 += d->matrix[i][k];
					aux2 += d->matrix[j][k]; 
				}
				q->matrix[i][j] = (n-2)*(d->matrix[i][j]) - aux1 - aux2;
			}
			else
			{
				q->matrix[i][j]=0;
			}
		}

	}

}
void Matrix::updateMatrixQ(Matrix *d,Matrix* q, int a)
{
	double aux1=0, aux2 = 0;
	// a= i
	//k=j
	//int i = a;.
	d->n--;

	for(int j =0;j<q->n;j++)
	{
		aux1 = 0;
		aux2 = 0;
		for(int k =0;k<q->n;k++)
			{
					//printf("%lf\n",q->matrix[i][j]);
				aux1 += d->matrix[a][k];
				aux2 += d->matrix[j][k]; 
			}
			q->matrix[a][j] = (n-2)*(d->matrix[a][j]) - aux1 - aux2;
			q->matrix[j][a] = q->matrix[a][j];
	}
	q->matrix[a][a]=0;

	q->n=q->m=d->n;

}
/* Soma todas a posições da matriz */
double Matrix::sum()
{
	//printf("somando a matrix:\n");
//	printInt();
	double s=0;
	for (int i = 0; i < n;i++)
	{
		for(int j=0;j<m;j++)
		{
			s+=matrix[i][j];
		}
	}
	return s;
}


int Matrix::updateDistanceMatrix(int a,int b, int nD)
{
	double * distNewNode = new double[n];
	bool aisn = false;
		if(a==n-1)
		{
			a=b;
			aisn =true;
		}
		double ab = matrix[a][b];
		for(int i =0;i<n;i++)
		{
			
				matrix[a][i]=fabs(0.5*(matrix[a][i]+matrix[b][i]-ab));
				matrix[i][a]= matrix[a][i];	
		}
		// tirando os 2 nós unidos da matriz de distancia e colocando o novo :
		if(!aisn)
		{
			for(int i =0; i< n; i++)
			{
				matrix[i][b] = matrix[i][n-1];
				matrix[b][i] = matrix[n-1][i];
			}
			matrix[b][b]=0;
		}
		if (!aisn)
		{
			label[b] = label[n-1];
		}
		if(aisn)
		{
			label[a] =label[n-1];
		}
	//n--;
	m=n;
	return a;
}



// devolve um vetor de dois elementos com as distancias [0]-> distancia de a->u [1]-> distancia de  b->u
double* Matrix::newDistance(Matrix * m,int f, int g)
{	
	double dfu;
	double dgu;
	double aux1,aux2;
	aux1=aux2=0;
	for(int i=0;i<this->n;i++)
	{
		aux1+=m->matrix[f][i];
		aux2+=m->matrix[g][i];
	}
	dfu =abs(floor(0.5*m->matrix[f][g]+(1/(2*(n-2)))*(aux1-aux2)));
	dgu= m->matrix[f][g]-dfu;
	double *v = new double[2];
	//printf("no método %lf %lf\n",dfu,dgu);
	v[0]=dfu;
	v[1]=dgu;
	return v;
}

Matrix* Matrix::matrixQ(Matrix *d,int n)
{	
	Matrix * q = new Matrix(n,n);
	double aux1=0,aux2=0;
	for(int i=0;i<d->n;i++)
	{

		for(int j=0;j<d->n;j++)
		{	aux1=aux2=0;
			if(i!=j)
			{
				for(int k =0;k<d->n;k++)
				{
					aux1 += d->matrix[i][k];
					aux2 += d->matrix[j][k]; 
				}
				q->matrix[i][j] = (n-2)*(d->matrix[i][j]) - aux1 - aux2;
			}
			else
			{
				q->matrix[i][j]=0;
			}
		}

	}
	return q;
}
