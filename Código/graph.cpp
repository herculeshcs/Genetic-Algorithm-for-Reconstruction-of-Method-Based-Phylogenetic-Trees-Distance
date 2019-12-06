#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <queue>
#include "node.h"
#include "edge.h"
//#include "matrix.h"
#include <time.h>
#include <stdlib.h>
#include "graph.h"

using namespace std;


/* Procura o nó com id = a (isto é, nó A) na lista de nós */
Node* Graph::find(int a)
{
	for(auto node = listOfNodes->begin(),endNode = listOfNodes->end(); node != endNode;node++)
	{
		if((*node)->id==a)
		{
			return 	*node;
		}
	}
	return 0;
}


/* Adiciona uma aresta entre os vértices a e b com o peso v */
void Graph::addAdj(int a, int  b, double v)
{
	Node* aux;
	Node* nodeInList = find(a);
	Edge* newEdge = new Edge(a,b,v);
	if(nodeInList ==0)
	{
		aux = new Node(a);
		aux->addEdge(newEdge);
		listOfNodes->push_back(aux);
	}
	else
	{
		nodeInList->addEdge(newEdge);
	}
	nodeInList = find(b);
	if(nodeInList==0)
	{
		aux= new Node(b);
		aux->addEdge(newEdge);
		listOfNodes->push_back(aux);
	}
	else
	{
		nodeInList->addEdge(newEdge);
	}
}

/* Gera uma arvore qualquer */
Graph * Graph::randonKruskal()
{

    list<Edge *> * listOfEdges= graphToListOfEdge();
	Graph * g = new Graph();
	int * v  = new int[listOfNodes->size()];
	for(int i =0;i<listOfNodes->size();i++)
	{
		v[i]=i;
	}
	listOfEdges->sort(this->randonCompare);
	//printf("oi eu estou no Kruskal\n");
	for(auto i=listOfEdges->begin(), e= listOfEdges->end();i!=e;i++)
	{
		if(v[(*i)->a]!=v[(*i)->b])
		{
			g->addAdj((*i)->a,(*i)->b,(*i)->v);
			update(v,listOfNodes->size(),v[(*i)->b],v[(*i)->a]);
		}
	}
	delete[] v;
	return g;

}

/* Gera a árvore geradora mínima */
Graph* Graph::kruskal()
{
	list<Edge *> * listOfEdges= graphToListOfEdge();
	Graph * g = new Graph();
	int * v  = new int[listOfNodes->size()];
	for(int i =0;i<listOfNodes->size();i++)
	{
		v[i]=i;
	}
	listOfEdges->sort(this->compare);
	//printf("oi eu estou no Kruskal\n");
	for(auto i=listOfEdges->begin(), e= listOfEdges->end();i!=e;i++)
	{
		if(v[(*i)->a]!=v[(*i)->b])
		{
			g->addAdj((*i)->a,(*i)->b,(*i)->v);
			update(v,listOfNodes->size(),v[(*i)->b],v[(*i)->a]);
		}
	}
	delete[]v;
	return g;
}


void Graph::update(int* v, int n, int atual, int novo)
{
	for(int i =0;i<n;i++)
	{
		if(v[i]==atual)
		{
			v[i]=novo;
		}
	}
}


/* Transforma a lista de nós em uma lista de arestas para ser usada pelo Kruskal */
list<Edge*>* Graph::graphToListOfEdge()
{
	list<Edge*> *l = new list<Edge*>;
		for(auto i=listOfNodes->begin(),e=listOfNodes->end();i!=e;i++)
		{
			for(auto it = (*i)->listOfAdj->begin(),ed = (*i)->listOfAdj->end(); it!=ed;it++)
			{
				l->push_back((*it));
			}
		}
		return l;
}




/* Método que faz uma busca em largura no grafo a partir de root e devolve um vetor de distancia de todos os vértices para root */
void Graph::bfs(Node * root, double* distances, bool * visitados)
{
	//double * distances = new double [listOfNodes->size()+1]; 
	//bool * visitados = new bool [listOfNodes->size()];
	for(int i =0;i<listOfNodes->size();i++)
	{
		visitados[i]=false;
	}
	int vis =0;
	queue<Node *> * fila = new queue <Node *> ();
	Node * aux;
	Node * currentNode;
	int aux2;
	/* Coloca visinhança do primeiro nó para o bfs. */
	for(auto i = root->listOfAdj->begin(), e=root->listOfAdj->end();i!=e;i++)
	{
			if((*i)->a != root->id)
			{
				aux = find((*i)->a);
				aux2 = (*i)->a;
			}
			else if((*i)->b != root->id)
			{
				aux = find((*i)->b);
				aux2 = (*i)->b;
			}
			fila->push(aux);
			distances[aux2]= (*i)->v;
			visitados[aux2]=true;
			vis++;
	}
	/* Coloca primeiro nó no vetor de visitados */
	visitados[root->id]= true;
	vis++;
	/* Laço principal do bfs enquanto a fila não for vazia */
	while(!fila->empty())
	{
		currentNode = fila->front();
		fila->pop();
		for(auto i =currentNode->listOfAdj->begin(), e= currentNode->listOfAdj->end();i!=e;i++)
		{	
				/* Vetifica que lado da aresta é o correto */
				if((*i)->a != currentNode->id)
				{
					aux = find((*i)->a);
					aux2 = (*i)->a;
				}
				else if((*i)->b != currentNode->id)
				{
					aux = find((*i)->b);
					aux2 = (*i)->b;
				}
				/* Verifica se visitados tem aux2, ou seja, se o nó esta na lista de visitados. */
				if(!visitados[aux2])
				{
					fila->push(aux);
					distances[aux2]= distances[currentNode->id]+(*i)->v;
					visitados[aux2]= true;
					vis++;
				}
		}
	}
	delete fila;
	//delete []visitados;
	//return distances;
}


/* Procura o valor a no vetor v de tamanho de n */
bool Graph::intFind(int* v, int n, int a)
{
	for(int i=0; i<n; i++)
	{
		if(v[i]==a)
		{
			return true;
		}
	}
	return false;
}



Graph* Graph::randonValidTree(const Matrix *distances)
{
	int i,j;
	int n = distances->n;
	int nD =0;
	Matrix * m = new Matrix(n,n);
	m->copy(m,distances);
	Graph * tree = new Graph();
	for(int j = 0;j<n;j++)
	{
		tree->addNode(j);
	}
	double * newDistances;
	int newNodei;
	while(m->n>2)
	{	
		i = rand()%m->n;
		j = rand()%m->n;
		if(i==j)
		{
			if(i< m->n-1)
			{
				j++;
			}
			else
			{
				j--;
			}
		}
		newDistances = m->newDistance(m,i,j);
		if(m->label[i]>=n && m->label[j]>=n)
		{
			tree->addAdj(m->label[i],m->label[j],m->matrix[i][j]);
		}	
		else
		{
			tree->addAdj(m->label[i],n+nD,newDistances[0]);
			tree->addAdj(m->label[j],n+nD,newDistances[1]);
		}
		newNodei=m->updateDistanceMatrix(i,j,n+nD);
		nD++;
		delete [] newDistances;
		m->n--;
		m->m=m->n;
		
	}
	i=0;
	j=1;
	tree->addAdj(m->label[i],m->label[j],m->matrix[i][j]);
	delete m;
	//m->printInt();
	//tree->print();
	return tree;
}


Graph* Graph::NJ(const Matrix *distances)
{
	int i,j;
	int n = distances->n;
	int nD =0;
	Matrix * m = new Matrix(n,n);
	m->copy(m,distances);
	Graph * tree = new Graph();
	Matrix * q=m->matrixQ(m,n);
	int newNodei;
	double * newDistances;
	while(m->n > 2 )
	{
		q->min(&i,&j);
		newDistances = q-> newDistance(m,i,j);
	/*	printf("%d %d\n",m->label[i],m->label[j]);
		for(int k =0;k<m->n;k++)
		{
			printf(" %d",m->label[k]);
		}
		printf("\n");*/
		if(m->label[i]>=n && m->label[j]>=n)
		{
			tree->addAdj(m->label[i],m->label[j],m->matrix[i][j]);
		}
		else
		{
			tree->addAdj(m->label[i],n+nD,newDistances[0]);
			tree->addAdj(m->label[j],n+nD,newDistances[1]);
		}
		newNodei=m->updateDistanceMatrix(i,j,n+nD);
		m->updateMatrixQ(m,q,newNodei);
		nD++;
		delete [] newDistances;
	}
	q->min(&i,&j);
	tree->addAdj(m->label[i],m->label[j],m->matrix[i][j]);
	delete q;
	delete m;
	return tree;
}


double Graph::treeSumOfAllPath(Graph * tree, int n)
{
	//Matrix * distance = new Matrix(n);
	double d;
	double * v = new double[tree->listOfNodes->size()];
	bool * visitados = new bool[tree->listOfNodes->size()];
	d=0;
	for(auto it= tree->listOfNodes->begin(), et = tree->listOfNodes->end();et!=it;it++)
	{
			if((*it)->id<n)
			{
				tree->bfs(*it,v,visitados);
				//distance->matrix[(*it)->id]=d;
				for(int i=0;i<n;i++ )
				{
					d+=v[i];
				}
			}
	}
	delete []v;
	delete []visitados; 
	return d;
}



/* Imprime o grafo */
void Graph::print()
{
	listOfNodes->sort(this->compareNode);
	for(auto i = listOfNodes->begin(), e = listOfNodes->end();i!=e;i++)
	{
		(*i)->print();
	}
}
