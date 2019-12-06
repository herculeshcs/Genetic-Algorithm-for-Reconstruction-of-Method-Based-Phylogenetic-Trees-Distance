#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include "edge.h"
#include "graph.h"
#include "specimen.h"
#ifndef __POPULATION_H
#define __POPULATION_H
using namespace std;
class Population
{
public:
	list<Specimen* > * listOfSpecimen;
	Matrix * reference;
	Population(int size, Matrix *m)
	{
		double referenceValue = m->sum();
		listOfSpecimen = new list<Specimen *>();
		startPopulation(size-1,m,referenceValue);
		listOfSpecimen->push_back(new Specimen(m,referenceValue));
	}
	void startPopulation(int size,Matrix * m, double referenceValue)
	{
	 
	  Specimen * individual;
	  for(int i=0;i<size-1;i++)
	  {	
	  	individual = new Specimen(m,referenceValue);
	  	listOfSpecimen->push_back(individual);
	  }
	  //listOfSpecimen->push_back()
	  individual = new Specimen(m,referenceValue,true);
	  listOfSpecimen->push_back(individual);

	}
	static bool compare(const Specimen *a, const Specimen * b)
	{	
		if(a->fenotype < b->fenotype)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	void selectBestSpecimens(Specimen *l,int numberOfBests, Matrix * m)
	{
		//sort();
		int count=0;
		double sum = m->sum();
		//list<Specimen *> l = new list<Specimen*>();
		for(auto i= listOfSpecimen->begin(), e= listOfSpecimen->end();i!=e;i++)
		{
		 	  (*i)->fenotype =fabs((*i)->genotype->treeSumOfAllPath((*i)->genotype,m->n)-sum);
		}
		sort();
		for(auto i= listOfSpecimen->begin(), e= listOfSpecimen->end();count<numberOfBests && i!=e;count++,i++)
		{
		 	l[count].genotype = (*i)->genotype;
		 	l[count].fenotype = (*i)->fenotype;
		}
	}
	void sort()
	{
		listOfSpecimen->sort(this->compare);
	}
	
};

#endif