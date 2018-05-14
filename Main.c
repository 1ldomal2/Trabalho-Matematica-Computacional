///////////////////////////////////////////////////////////////////////////
//						//
//Lucas Mateus Fernandes 	0035411	//
//Leandro					//
//						//
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "R_to_C.h"
#include "Integral.h"
#define DEBUG printf("\nLinha = %d Arquivo = %s\n",__LINE__,__FILE__);





int main(int argc, char const *argv[])
{
	ARQUIVO File;
	MATRIZ Matriz_Interpolacao;
	

	
Interpolacao("Input",&File);
	
Prepara_Matriz(&File,&Matriz_Interpolacao);

for(int i = 0;i < File.n;i++)
{
	for(int j = 0;j < File.n;j++)
{
	printf("%f\t ",Matriz_Interpolacao.MatrizA[i][j]);
}
printf("\n");
}
Gauls(File.n,Matriz_Interpolacao.MatrizA,Matriz_Interpolacao.VetorB);
printf("\n");

printf("\n");

for(int i = 0;i < File.n;i++)
{
	for(int j = 0;j < File.n;j++)
{
	printf("%f\t ",Matriz_Interpolacao.MatrizA[i][j]);
}
printf("\n");
}
printf("\n");
printf("\n");
printf("\n");	
printf("\n");
	
	for(int i = 0;i < File.n;i++)
{
	printf("%f\n ",Matriz_Interpolacao.VetorB[i]);
}
printf("\n");

	SubsRetro(File.n, Matriz_Interpolacao.MatrizA, Matriz_Interpolacao.VetorB,
	Matriz_Interpolacao.VetorX);
		
	return 0;
}