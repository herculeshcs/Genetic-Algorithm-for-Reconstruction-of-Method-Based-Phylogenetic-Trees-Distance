#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <queue>
#include "node.h"
#include "edge.h"
#ifndef __MATRIX_H
#include "matrix.h"
#endif
#include <time.h>
#include <stdlib.h>
#ifndef __GRAPH_H
#define __GRAPH_H
using namespace std;

/*
 * Classe que representa o grafo. 
 */

class Graph
{
public:
	/* listOfNodes é uma lista encadeada que contém ponteiros para os vértices */
	list<Node*> * listOfNodes;
	
	Graph()
	{
		listOfNodes = new list<Node*>;
	}

	~Graph();
	
	
	static bool compare(const Edge* a, const Edge * b)
	{
		if(a->v < b->v)
			return true;
		else
				return false;
	}
	static bool randonCompare(const Edge *a,const Edge *b)
	{
		if(rand()%2)
			return true;
		else
			return false;
	}
	static bool compareNode(const Node* a, const Node * b)
	{
		if(a->id < b->id)
			return true;
		else
				return false;
	}
	void copy(Graph * graphA)
	{

		listOfNodes->clear();
		listOfNodes = new list<Node*>;
		for(auto i=graphA->listOfNodes->begin(), e= graphA->listOfNodes->end();i!=e;i++)
		{
			for(auto it = (*i)->listOfAdj->begin(),ed = (*i)->listOfAdj->end(); it!=ed;it++)
			{
				if((*it)->copy)
				{
					this->addAdj((*it)->a, (*it)->b, (*it)->v);
					(*it)->copy=false;
				}
			}
		}
		/*libera copia das arestas*/
		for(auto i=graphA->listOfNodes->begin(), e= graphA->listOfNodes->end();i!=e;i++)
		{
			for(auto it = (*i)->listOfAdj->begin(),ed = (*i)->listOfAdj->end(); it!=ed;it++)
			{
				(*it)->copy=true;
			}
		}
	}
	void addNode(int);
	bool intFind(int*,int,int);
	Node* find(int);
	void addAdj(int, int, double);
	Graph* kruskal();
	Graph* randonKruskal();

	void update(int*, int, int, int);
	list<Edge*>* graphToListOfEdge();
	void print();
	void bfs(Node*,double*,bool*);
	Graph* randonValidTree(const Matrix*);
	Graph* NJ(const Matrix*);
	double treeSumOfAllPath(Graph*, int);
	
};


/* Método que insere um vértice no grafo */
inline
void Graph::addNode(int n)
{
	Node* node = new Node(n);
	/* Insere o vértice no final da lista de nós */
	listOfNodes->push_back(node);
}






#endif