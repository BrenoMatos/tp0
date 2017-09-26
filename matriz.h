#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct celula{
	int min,max,sum;
} celula;

int Min(int i,int j,int *v);
int Max(int i,int j,int *v);
int Soma(int i,int j,int *v);
void atualiza(int n,celula **m,int *v);
void Add(int i,int j,int *v,celula **m,int n);
void Sub(int i,int j, int *v,celula **m,int n);
void libera(int *v,celula **m,int n);
void imprime(celula **m,int n);
void leituraArquivo();
