#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

#define MAX_SIZE 1000

void gera_instancia(int m[MAX_SIZE][MAX_SIZE], int size, int varying_range);
void show_instancia(int m[MAX_SIZE][MAX_SIZE], int size);
void escreve_instancia(int m[MAX_SIZE][MAX_SIZE], int size, FILE* f);

int main(void){
	int m[MAX_SIZE][MAX_SIZE];
	const int sizes[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
	const int values_range[] = { 10, 100, 1000 };
	// Para cada configuração (size, value_range) faça 10 amostragens
	const int nAmostras = 10;
	//gera_instancia(m, sizes[0], values_range[0]);
	//show_instancia(m, sizes[0]);
	//cout << "Tams : " << sizeof(sizes)/sizeof(int) << ", " << sizeof(values_range)/sizeof(int) << endl;
	const int nSizes = sizeof(sizes)/sizeof(int);
	const int nVaryingValues = sizeof(values_range)/sizeof(int);
	for(int i = 0; i < nSizes; i++){
		for(int j = 0; j < nVaryingValues; j++){
			for(int k = 0; k < nAmostras; k++){
				char name_file[200];
				snprintf(name_file, 200, "./instancias/tamanho%d_variando%d_amostra%d.txt", sizes[i], values_range[j], k+1);
				FILE *f = fopen(name_file, "w");
				if (f == NULL)
				{
				    printf("Error opening file!\n");
				    exit(1);
				}
				printf("Gerando amostra %d para: (Tamanho %d, Variando Valores %d):\n", k+1, sizes[i], values_range[j]);
				gera_instancia(m, sizes[i], values_range[j]);
				//show_instancia(m, sizes[i]);
				escreve_instancia(m, sizes[i], f);
				fclose(f);
			}
		}
	}
}

void gera_instancia(int m[MAX_SIZE][MAX_SIZE], int size, int varying_range)
{
	for(int i = 0; i < size; i++){
		for(int j = i; j < size; j++){
			if(i == j)
				m[i][j] = 0;
			else
				m[i][j] = m[j][i] = 1 + (rand() % varying_range);
		}
	}
	return;
}

void show_instancia(int m[MAX_SIZE][MAX_SIZE], int size)
{
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

void escreve_instancia(int m[MAX_SIZE][MAX_SIZE], int size, FILE* f)
{
	fprintf(f, "%d\n", size);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			fprintf(f, "%d ", m[i][j]);
		}
		fprintf(f, "\n");
	}
}