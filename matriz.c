#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "matriz.h"

int Min(int i,int j,int *v){
	int auxMin, k,max,min;

	if (i < j)//para ter certeza que os valores passados a funcao foram minimo e maximo, respextivamente
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}

	auxMin = v[min];//para realizar as comparações
	for (k = min; k <= max; k++)//percorre o vetor e checa, sequencialmente, qual o menor valor naquele intervalo
	{
		if (auxMin > v[k])
		{
			auxMin = v[k];
		}
	}
	return auxMin;//valor eh retornado
}

int Max(int i,int j,int *v){
	int auxMax, k,max,min;

	if (i < j)
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}

	auxMax = v[min];//para realizar as comparações
	for (k = min; k <= max; k++)//percorre o vetor e checa, sequencialmente, qual o menor valor naquele intervalo
	{
		if (auxMax < v[k])
		{
			auxMax = v[k];
		}
	}
	return auxMax;//valor eh retornado
}

int Soma(int i,int j,int *v){
	int auxSoma = 0,k,max,min;

	if (i < j)
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}
	for (k = min; k <= max ; k++)//percorre o vetor sequencialmente e soma os valores daquele dado intervalo
	{
		auxSoma+=v[k];
	}
	printf("MIN %d MAX %d\n",i,j );
	for ( i = 0; i < 8; i++) {
		printf("%d ", v[i]);
	}
	return auxSoma;//valor entao eh retornado
}

void atualiza(int min,int n,celula **m,int *v){//atualizar tudo, pq a matriz é imbecil
	int i,j;
	for (i = min; i < n; i++)
	{
		for (j = min; j < n; j++)
		{
			m[i][j].min = Min(i,j,v);//atualiza a matriz APENAS nas celulas que serao alteradas por Sub ou Add
			m[i][j].max = Max(i,j,v);
			m[i][j].sum = Soma(i,j,v);
			//printf("INDICES I e J:%d %d  Min %d Max %d Sum %d\n",i,j,m[i][j].min,m[i][j].max,m[i][j].sum );
		}
	}
}
void Add(int i,int j,int *v,celula **m,int n){//adiciona um a todos os elementos no intervalo [i,j]
	int max,min;

	if (i < j)
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}

	for (int k = min; k <= max; k++) {
		v[k]++;
	}

	atualiza(min,n ,m,v);

}

void Sub(int i,int j, int *v,celula **m,int n){
	int max,min;

	if (i < j)
	{
		max = j;
		min = i;
	}else {
		max = i;
		min = j;
	}

	for (int l = min; l <= max; l++) {
		v[l]--;
	}

	atualiza(min,n ,m,v);//aqui estava n - 1
}


void libera(int *v,celula **m,int n){
	int i;
	for ( i = 0; i < n; i++)//libera a matriz
	{
		free(m[i]);
	}
	free(m);

	free(v);
}

void imprime(celula **m,int n){//funcao que imprime a matriz, nao eh utilizada de fato para o TP, mas resolvi deixar, caso os monitores queiram realizar algum teste
	int i,j;
	printf("SOMAS:\n\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ",m[i][j].sum );
		}
		printf("\n");
	}
}

void leituraArquivo(){
	int n,i,j,consultas,n1,n2;
	char operacao[4];

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

	celula **m = (celula**) malloc(sizeof(celula *)*n);
	for (i = 0; i < n; i++)
	{
		m[i] = (celula*) malloc(sizeof(celula)*n);
	}
//CRIACAO DA MATRIZ
//para cada posicao da matriz, cada valor (min,max,soma) da struct celula sao preenchidos
//com seus respectivos valores, sendo o interavalo de pesquisa igual ao intervalo [i,j] dos contadores
//que percorrem a matriz
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			m[i][j].min = Min(i,j,v);
			m[i][j].max = Max(i,j,v);
			m[i][j].sum = Soma(i,j,v);
		}
	}

	while(consultas--){
		if(scanf("%s %d %d",operacao,&n1,&n2)==-1){
			printf("ERRO");
		}
		if (strcmp(operacao,"Sum")==0)
		{
			printf("%d\n", m[n1-1][n2-1].sum );
			//imprime(m,n);

		}
		else if (strcmp(operacao,"Min")==0)
		{
			printf( "%d\n", m[n1-1][n2-1].min);

		}
		else if (strcmp(operacao,"Max")==0)
		{
			printf( "%d\n", m[n1-1][n2-1].max);


		}
		else if (strcmp(operacao,"Add")==0)
		{
			//printf("add %d %d\n", n1-1,n2-1);
			Add(n1-1,n2-1,v,m,n);
		}
		else if (strcmp(operacao,"Sub")==0)
		{
			//printf("sub %d %d\n", n1-1,n2-1);
			Sub(n1-1,n2-1,v,m,n);
		}
		else printf("ERRO\n");

	}

	//libera as alocações feitas
	libera(v,m,n);
}

int main()
{

	leituraArquivo();

	return 0;
}
