#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct{
	int * st;
	int n;
}SegTree;

int min(int a, int b);
int max(int a, int b);
int soma(int a, int b);

int constroiStMin(SegTree *st, int v[], int p, int b, int e);
void constroiMin(SegTree *st, int v[], int n);
int queryMinSt(SegTree *st, int p, int i, int j, int b, int e);
int queryMin(SegTree *st, int b, int e);
int atualizaMinSt(SegTree *st, int p, int i, int j, int pos, int val);
void atualizaMin(SegTree *st, int pos, int val);

int constroiStMax(SegTree *st, int v[], int p, int b, int e);
void constroiMax(SegTree *st, int v[], int n);
int queryMaxSt(SegTree *st, int p, int i, int j, int b, int e);
int queryMax(SegTree *st, int b, int e);
int atualizaMaxSt(SegTree *st, int p, int i, int j, int pos, int val);
void atualizaMax(SegTree *st, int pos, int val);

int constroiStSoma(SegTree *st, int v[], int p, int b, int e);
void constroiSoma(SegTree *st, int v[], int n);
int querySomaSt(SegTree *st, int p, int i, int j, int b, int e);
int querySoma(SegTree *st, int b, int e);
int atualizaSomaSt(SegTree *st, int p, int i, int j, int pos, int val);
void atualizaSoma(SegTree *st, int pos, int val);

void atualizaArvoreAdd(SegTree *stMin, SegTree *stSum, SegTree *stMax, int i, int j, int *v);
void atualizaArvoreSub(SegTree *stMin, SegTree *stSum, SegTree *stMax, int i, int j, int *v);

void leituraArquivo();
