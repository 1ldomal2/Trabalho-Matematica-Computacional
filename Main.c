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


Gauls(File.n,Matriz_Interpolacao.MatrizA,Matriz_Interpolacao.VetorB);

	
	
	SubsRetro(File.n, Matriz_Interpolacao.MatrizA, Matriz_Interpolacao.VetorB,Matriz_Interpolacao.VetorX);
				printf("\n");
			
	for(int j = 0;j < File.n;j++){
			printf("%f \t",Matriz_Interpolacao.VetorX[j]);
		}
		printf("\n");
	
	
	return 0;
}