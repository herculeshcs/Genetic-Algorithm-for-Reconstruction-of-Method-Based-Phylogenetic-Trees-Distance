#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include "edge.h"
#include "graph.h"
#include "matrix.h"
#include "specimen.h"

using namespace std;

int SpecimenN;
double SpecimenReferencialValue;


/* Matriz de distancia e  somatorio  de toda a matriz de distancia (para não ter que calcular tudo) */
Specimen:: Specimen(Matrix * m, double referencialValue)
{
	genotype = new Graph();
	genotype= genotype->randonValidTree(m);
	SpecimenN = m->n;
	//fenotype = genotype->treeSumOfAllPath(genotype,m->n);
	//SpecimenReferencialValue = referencialValue; 
}

Specimen:: Specimen(Matrix * m, double referencialValue, bool nj)
{
	genotype = new Graph();
	genotype= genotype->NJ(m);
	SpecimenN = m->n;
	//fenotype = fabs(genotype->treeSumOfAllPath(genotype,m->n) - referencialValue);
	//SpecimenReferencialValue = referencialValue; 
}

Specimen:: Specimen(Graph *a)
{
	genotype = a;
	//double m = genotype->treeSumOfAllPath(genotype,SpecimenN);
	//fenotype = fabs(m - SpecimenReferencialValue);
}

/* Faz cross Over entre dois especimes. */
Specimen* Specimen::crossOver(Specimen * a, Specimen *b)
{
	Graph * graphA = a->genotype;
	Graph * graphB = b->genotype;
	Graph *c= new Graph();

	/* Coloca todos os nós de a em c */
	for(auto i=graphA->listOfNodes->begin(), e= graphA->listOfNodes->end();i!=e;i++)
	{
		for(auto it = (*i)->listOfAdj->begin(),ed = (*i)->listOfAdj->end(); it!=ed;it++)
		{
			c->addAdj((*it)->a, (*it)->b, (*it)->v);
		}
	}
	/* Coloca todos os nós de b em c */
	for(auto i=graphB->listOfNodes->begin(),e=graphB->listOfNodes->end();i!=e;i++)
	{
		for(auto it = (*i)->listOfAdj->begin(),ed = (*i)->listOfAdj->end(); it!=ed;it++)
		{
			c->addAdj((*it)->a, (*it)->b, (*it)->v);
		}
	}
	//c=c->kruskal();
	c=c->randonKruskal();
	return new Specimen(c);
}