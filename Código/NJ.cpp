//#include "Sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "graph.h"
using namespace std;

int main ()
{
	Matrix * m;// matriz de distancias
	Matrix * q;// matriz Q
	int nD =1;
	Graph * tree = new Graph();
	double * newDistances;
	int res;
	int n;
	int i,j;
	double a;
	FILE * file = fopen("Resultado_NJ","a+");
	res=scanf(" %d",&n);
	m = new Matrix(n,n);
	for(int i =0;i<n;i++)
	{
		// criando arvore estrela pra o inicio do algoritmo : D
		tree->addNode(i);
		for(int j=0;j<n;j++)
		{
		    res=scanf(" %lf",&a);
			m->matrix[i][j]=a;
		}
	}

	tree = tree->NJ(m);
	//printf("%lf %lf\n",tree->treeSumOfAllPath(tree,n),m->sum());
	//tree->print();
	fprintf(file,"%d %lf\n",n,fabs(tree->treeSumOfAllPath(tree,n)-m->sum()));
	 printf("%d %lf\n",n,fabs(tree->treeSumOfAllPath(tree,n)-m->sum()));
}
    


