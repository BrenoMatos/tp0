#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "arvore.h"

const int inf = 100000000;

//funcoes que retornam, respectivamente, as comparacoes entre minimo,maximo e a soma entre dois numeros a e b
int min(int a, int b){
	return a <= b ? a : b;
}

int max(int a, int b){
	return a <= b ? b : a;
}

int soma(int a, int b){
	return a+b;
}
//////////////////////////////////////////////////////////////////////////////////////////
//MINIMOS
//funcoes que constroem a arvore e buscam e atualizam valores nela
int constroiStMin(SegTree *st, int v[], int p, int b, int e){
	if(b == e) return st->st[p] = v[b];
	int m = (b+e)/2;
	return st->st[p] = min(constroiStMin(st, v, p+p, b, m), constroiStMin(st, v, p+p+1, m+1, e));
}

void constroiMin(SegTree *st, int v[], int n){
	st->st = (int *)malloc(4*(n-1)*sizeof(int));
	st->n = n-1;
	constroiStMin(st, v, 1, 0, n-1);
}

int queryMinSt(SegTree *st, int p, int i, int j, int b, int e){
	if(i > e || j < b) return inf;
	if(i >= b && j <= e) return st->st[p];
	int m = (i+j)/2;
	return min(queryMinSt(st, p+p, i, m, b, e), queryMinSt(st, p+p+1, m+1, j, b, e));
}

int queryMin(SegTree *st, int b, int e){//funcao para encontrar o valor minimo em um intervalo dado
	return queryMinSt(st, 1, 0, st->n, b, e);
}

int atualizaMinSt(SegTree *st, int p, int i, int j, int pos, int val){
	if(i > pos || j < pos) return st->st[p];
	if(i == pos && j == pos) return st->st[p] = val;
	int m = (i+j)/2;
	return st->st[p] = min(atualizaMinSt(st, p+p, i, m, pos, val), atualizaMinSt(st, p+p+1, m+1, j, pos, val));
}

void atualizaMin(SegTree *st, int pos, int val){
	atualizaMinSt(st, 1, 0, st->n, pos, val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAXIMOS
//funcoes que constroem a arvore e buscam e atualizam valores nela
int constroiStMax(SegTree *st, int v[], int p, int b, int e){
	if(b == e) return st->st[p] = v[b];
	int m = (b+e)/2;
	return st->st[p] = max(constroiStMax(st, v, p+p, b, m), constroiStMax(st, v, p+p+1, m+1, e));
}

void constroiMax(SegTree *st, int v[], int n){
	st->st = (int *)malloc(4*(n-1)*sizeof(int));
	st->n = n-1;
	constroiStMax(st, v, 1, 0, n-1);
}

int queryMaxSt(SegTree *st, int p, int i, int j, int b, int e){
	if(i > e || j < b) return 0;
	if(i >= b && j <= e) return st->st[p];
	int m = (i+j)/2;
	return max(queryMaxSt(st, p+p, i, m, b, e), queryMaxSt(st, p+p+1, m+1, j, b, e));
}

int queryMax(SegTree *st, int b, int e){
	return queryMaxSt(st, 1, 0, st->n, b, e);
}

int atualizaMaxSt(SegTree *st, int p, int i, int j, int pos, int val){
	if(i > pos || j < pos) return st->st[p];
	if(i == pos && j == pos) return st->st[p] = val;
	int m = (i+j)/2;
	return st->st[p] = max(atualizaMaxSt(st, p+p, i, m, pos, val), atualizaMaxSt(st, p+p+1, m+1, j, pos, val));
}

void atualizaMax(SegTree *st, int pos, int val){
	atualizaMaxSt(st, 1, 0, st->n, pos, val);
}
///////////////////////////////////////////////////////////////////////////////////////////
//SOMAS
//funcoes que constroem a arvore e buscam e atualizam valores nela
int constroiStSoma(SegTree *st, int v[], int p, int b, int e){//constroi a arvore de forma recursiva
	if(b == e) return st->st[p] = v[b];
	int m = (b+e)/2;
	return st->st[p] = soma(constroiStSoma(st, v, p+p, b, m), constroiStSoma(st, v, p+p+1, m+1, e));
}

void constroiSoma(SegTree *st, int v[], int n){
	st->st = (int *)malloc(4*(n-1)*sizeof(int));
	st->n = n-1;
	constroiStSoma(st, v, 1, 0, n-1);
}

int querySomaSt(SegTree *st, int p, int i, int j, int b, int e){
	if(i > e || j < b) return 0;
	if(i >= b && j <= e) return st->st[p];
	int m = (i+j)/2;
	return soma(querySomaSt(st, p+p, i, m, b, e), querySomaSt(st, p+p+1, m+1, j, b, e));
}

int querySoma(SegTree *st, int b, int e){
	return querySomaSt(st, 1, 0, st->n, b, e);
}

int atualizaSomaSt(SegTree *st, int p, int i, int j, int pos, int val){
	if(i > pos || j < pos) return st->st[p];
	if(i == pos && j == pos) return st->st[p] = val;
	int m = (i+j)/2;
	return st->st[p] = soma(atualizaSomaSt(st, p+p, i, m, pos, val), atualizaSomaSt(st, p+p+1, m+1, j, pos, val));
}

void atualizaSoma(SegTree *st, int pos, int val){
	atualizaSomaSt(st, 1, 0, st->n, pos, val);
}

///////////////////////////////////////////////////////////////////////////////////////

void atualizaArvoreAdd(SegTree *stMin, SegTree *stSum, SegTree *stMax, int i, int j, int *v){
	int max,min,k,l;

	if (i < j)
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}

	for (k = min; k <= max; k++) {
		v[k]++;
	}

	for (l = min; l <= max; l++)
	{
		atualizaSoma(stSum,l,v[l]);
		atualizaMin(stMin,l,v[l]);
		atualizaMax(stMax,l,v[l]);
	}

}


void atualizaArvoreSub(SegTree *stMin, SegTree *stSum, SegTree *stMax, int i, int j, int *v){
	int max,min,k,l;

	if (i < j)
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}

	for (k = min; k <= max; k++) {
		v[k]--;
	}

	for (l = min; l <= max; l++)
	{
		atualizaSoma(stSum,l,v[l]);
		atualizaMin(stMin,l,v[l]);
		atualizaMax(stMax,l,v[l]);
	}
}
//////////////////////////////////////////////////////////////////////////////////////
void leituraArquivo(){
	int n,i,consultas,n1,n2;
	char operacao[4];
	SegTree stMin,stMax,stSum;

	if (scanf("%d %d",&n,&consultas)==-1) {
		printf("ERRO" );
	}

	int *v = (int *) malloc(sizeof(int)*n);//aloca o vetor que ira receber todos os valores

	for ( i = 0; i < n; i++)//leitura do vetor de entrada
	{
		if (scanf("%d",v+i)==-1) {
			printf("ERRO");
		}
	}

	constroiMin(&stMin, v, n);//inicia cada uma das tres arvores
	constroiMax(&stMax, v, n);
	constroiSoma(&stSum, v, n);

	while(consultas--){
		if(scanf("%s %d %d",operacao,&n1,&n2)==-1){
			printf("ERRO");
		}
		if (strcmp(operacao,"Sum")==0)
		{
			printf("%d", querySoma(&stSum, n1-1, n2-1) );
			if (consultas != 1)
		{
			printf("\n");
		}
		}
		else if (strcmp(operacao,"Min")==0)
		{
			printf( "%d", queryMin(&stMin, n1-1, n2-1));
			if (consultas != 1)
		{
			printf("\n");
		}
		}
		else if (strcmp(operacao,"Max")==0)
		{
			printf( "%d", queryMax(&stMax, n1-1, n2-1));
			if (consultas != 1)
		{
			printf("\n");
		}
		}
		else if (strcmp(operacao,"Add")==0)
		{
			atualizaArvoreAdd(&stMin,&stSum,&stMax,n1-1,n2-1,v);
		}
		else if (strcmp(operacao,"Sub")==0)
		{
			atualizaArvoreSub(&stMin,&stSum,&stMax,n1-1,n2-1,v);
		}
		else printf("ERRO\n");

	}

}
/////////////////////////////////////////////////////////////////////////////////////
int main(){

	leituraArquivo();

	return 0;
}
