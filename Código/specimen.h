#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include "edge.h"
#include "graph.h"
#include "matrix.h"
#ifndef __SPECIMEN_H
#define __SPECIMEN_H

using namespace std;

class Specimen
{
public:
	Graph * genotype;
	double fenotype;
	
	Specimen(){}
	Specimen(Matrix*, double);
	Specimen(Matrix*, double, bool);
	Specimen(Graph*);
	Specimen* crossOver(Specimen*, Specimen*);
	void print()
	{
	  genotype->print();
	}
};

#endif