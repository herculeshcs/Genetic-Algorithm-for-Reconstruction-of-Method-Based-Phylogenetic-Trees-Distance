//#include "Sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef __MATRIX_H
#include "matrix.h"
#endif
#include "population.h"
#include "graph.h"
#include "specimen.h"
using namespace std;
int numberOfGenerations;
int numberOfBests;
int main ()
{	
	srand(time(NULL));
	Matrix * m;// matriz de distancias
	FILE * file = fopen("Resultado_gen","a+");
	numberOfGenerations = 100;
	numberOfBests =10;
	int res;
	int nD =1;
	Graph * tree = new Graph();
	double * newDistances;
	int n;
	int i,j;
	double a;
	list<Specimen*> * newPopulation;
	res=scanf(" %d",&n);
	m = new Matrix(n,n);
	for(int i =0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
		res=scanf(" %lf",&a);
			m->matrix[i][j]=a;
		}
	}
	Population * pop = new Population(50,m);
	Specimen * best=pop->listOfSpecimen->front();
	best->fenotype = best->genotype->treeSumOfAllPath(best->genotype,n);
    Specimen *listOfBests= new Specimen[numberOfBests];
    for(int i=0;i<numberOfBests;i++)
    {
    	listOfBests[i].fenotype = best->fenotype;
    }

	for(int generation = 0;generation<numberOfGenerations && best->fenotype != 0;generation++)
	{
		newPopulation =new list<Specimen *>;
		pop->selectBestSpecimens(listOfBests,numberOfBests,m);
		if(best->fenotype > listOfBests[0].fenotype)
		{
			best->genotype->copy(listOfBests[0].genotype);
			best->fenotype=listOfBests[0].fenotype;
		}
		int id;
		for(auto i = pop->listOfSpecimen-> begin(),e = pop->listOfSpecimen->end();i!=e;i++)
		{	
		      newPopulation->push_back((*i)->crossOver((*i),&listOfBests[rand()%numberOfBests]));
		}	
		pop->listOfSpecimen = newPopulation;
	}
	printf("%d %lf\n",n,best->fenotype);
	fprintf(file,"%d %lf\n",n,best->fenotype);


}
    