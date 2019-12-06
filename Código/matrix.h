#include <stdio.h>
#include <stdlib.h>
#ifndef __MATRIX_H
#define __MATRIX_H
#include <cmath>
#include <iostream>


class Matrix
{
public:
  double **matrix;
  int * label;
	int n,m;

	Matrix(int n, int m)
	{
	  this->n = m;
	  this->m = n;
	  Realm = m;
	  Realn = n;
	  matrix = new double*[n];
	  label = new int [n];
	  for(int i =0 ; i < m;i++)
	  {
	  	label[i]=i;
	  	matrix[i] = new double[m];
	  }
	}
	
	Matrix(int n)
	{
	  this->n = n;
	  this->m = n;
	  matrix = new double*[n];

 	}

	~Matrix()
	{
		for(int i =0;i<Realn;i++)
		{
			delete [] matrix[i];
		}
		delete[] matrix;
		delete[] label;
	}
	
	void copy(Matrix*,const Matrix*);
	void print();
	void printInt();
	Matrix & mult(Matrix&, Matrix&);
	void min (int*, int*);
	void updateMatrixSeparation(Matrix*, Matrix*, double * u, int );
	void updateMatrixQ(Matrix*,Matrix*, int);
	double sum();
	int updateDistanceMatrix(int,int, int);
	double* newDistance(Matrix*,int, int);
	Matrix* matrixQ(Matrix*,int);
private:
	int Realm,Realn;
};

#endif