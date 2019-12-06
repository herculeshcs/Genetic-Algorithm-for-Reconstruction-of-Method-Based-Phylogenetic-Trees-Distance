#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include "edge.h"
#ifndef __NODE_H
#define __NODE_H
using namespace std;

/**
 * Classe que representa um nó do grafo.
**/

class Node
{
public:
	/* A lista listOfAdj é uma lista encadeada que contém ponteiros para as arestas do grafo */
	list<Edge*> * listOfAdj;
	/* A variável id é um identificador do nó (o nome do nó). */
	int id;
	
	
	Node()
	{
		listOfAdj = new list<Edge*>;
	}
	
	Node(int id)
	{
		listOfAdj = new list<Edge*>;
		this->id = id;
	}
	
	~Node();
	
	void addEdge(Edge*);
	int numberOfAdj();
	void print();
	bool contains(Edge*);
};


/* Métodos da classe Node */

/* Método que insere uma aresta na lista de adjacencias do vértice */
inline
void Node::addEdge(Edge* a)
{
	/* push_back insere a aresta a no fim da lista listOfAdj. Isso quer dizer que a aresta a é adjacente a esse vértice */
	listOfAdj->push_back(a);
}

/* Método que devolve o número de arestas que são adjacentes a esse vértice */
inline
int Node::numberOfAdj()
{
	return listOfAdj->size();
}

/* Método que imprime um nó e a sua lista de arestas adjacentes */
inline
void Node::print()
{
	cout<<"Nó"<<this->id<<": \n";
	for(auto i=listOfAdj->begin(),e=listOfAdj->end(); i!=e; i++)
	{
		(*i)->print();
	}
}

/* Método que verifica se a aresta está contida na lista de adjacencias */
inline
bool Node::contains(Edge* aresta)
{
	for(auto i=listOfAdj->begin(),e = listOfAdj->end(); i!=e; i++)
	{
		if((*i)->a == aresta->a && (*i)->b == aresta->b)
		{
			return true;
		}
	}
	return false;
}

#endif