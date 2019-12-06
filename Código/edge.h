#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <iostream>
#ifndef __EDGE_H
#define __EDGE_H
using namespace std;

/* 
 * Classe Edge representa as arestas do grafo.
 * Os vértices são representados pelos inteiros a e b. E a variável v representa o valor da aresta entre os vértices a e b.
*/

class  Edge
{
public:
	int a,b;
	double v;
	bool copy;/*falso se eu já copiei*/
	
	Edge(int a, int b, double v)
	{
		this->a= a;
		this->b= b;
		this->v= v;
		copy =true;
	}
	
	/* Método que imprime os vértices a e b, que tem uma aresta entre eles e o peso desta aresta */
	void print()
	{
		cout<<a<<"-"<<b<<" "<<v<<"\n";
	}
};


#endif