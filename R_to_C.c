//###########################################
/*
	Mudar linguagem dos Algoritmos de R para C, 
	Algoritmos de Horney,Gauls com pivoteamento
*/
//###########################################

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "R_to_C.h"
#define  ERRO  0.001
#define DEBUG printf("\nLinha = %d Arquivo = %s\n",__LINE__,__FILE__);

/*
ERRO ao realizar a subs retro, a constante ta dando erro tentamos truncar e nao funcionou 
erro de arrendodamento sera?
*/
//Resolve uma função Polinomial de maneira mais eficiente
//Recebe Um vetor com os coeficiente o tamanho do vetor e o valor de X
//Retorna f(x) ou seja a imagem no ponto X
float Horner(float Coeficiente[],int Tamanho,float DominioX){
	float ImagemY=Coeficiente[0];
		for (int i = 1; i < Tamanho; ++i){
		ImagemY=ImagemY*DominioX+Coeficiente[i];
	}
	return ImagemY;
}

void Gauls(int Tamanho,float **MatrizA,float VetorB[]){
	//Cria Dois vetores para trocar matriz                                                     
	float VetorSwapA[Tamanho];
	float VetorSwapB[Tamanho];
	float Aux = 0;
	//Inicializa os Vetores do Swap
	for (int i = 0; i < Tamanho; ++i)
	{
		 VetorSwapA[i]=0;
		 VetorSwapB[i]=0;
	}

	//Vai da primeira até a penultima linha zerando-as
	for (int Pivo = 0; Pivo < (Tamanho-1); ++Pivo)
	{
		int IndiceMaior = Pivo;
		float Maior = MatrizA[Pivo][Pivo];

		//Faz as trocas da linha Pivo
		for (int SwapIndice = Pivo; SwapIndice < Tamanho; ++SwapIndice)
		{
			if(SwapIndice != Pivo){
				if (fabs(Maior)<fabs(MatrizA[SwapIndice][Pivo]))
				{
					 IndiceMaior = SwapIndice;
					 Maior = MatrizA[SwapIndice][Pivo];
				}
			}
		}

		//Troca
		for (int i = 0; i < Tamanho; ++i)
		{
			//Swap A
			 VetorSwapA[i]=MatrizA[Pivo][i];
			 MatrizA[Pivo][i]=MatrizA[IndiceMaior][i];
			 MatrizA[IndiceMaior][i]=VetorSwapA[i];
		}
		//Swap B
		Aux=VetorB[Pivo];
		VetorB[Pivo]=VetorB[IndiceMaior];
		VetorB[IndiceMaior]=Aux;
		
		

		//Acha o Escalar que ira zerar as linhas
		float Escalar=1;
		float mult = 1;
		for (int LinhaTrabalha = (Pivo+1); LinhaTrabalha < Tamanho; ++LinhaTrabalha)
		{
			 Escalar=MatrizA[LinhaTrabalha][Pivo]/MatrizA[Pivo][Pivo];
		
			//Resolução Começa a Zerar
			for (int Coluna = 0; Coluna < Tamanho; ++Coluna)
			{
				MatrizA[LinhaTrabalha][Coluna]=MatrizA[LinhaTrabalha][Coluna]-(Escalar*MatrizA[Pivo][Coluna]);
				mult = Escalar * MatrizA[Pivo][Coluna];
				if(fabs(MatrizA[LinhaTrabalha][Coluna]) < ERRO){
					MatrizA[LinhaTrabalha][Coluna] = 0;//Ajuste devido a aproximacao de valores 
				}
			}
			 VetorB[LinhaTrabalha]=VetorB[LinhaTrabalha]-(Escalar*VetorB[Pivo]);
		}
	}

	return;
}

void SubsRetro(int Tamanho,float **MatrizA,float VetorB[],float VetorX[]){
	float Somatorio = 0;
	float AuxTruc = 0;
	float Aux = 0, Aux1 = 0;

	//Zera matriz para evitar erros
	for(int i = 0;i < Tamanho;i++)
	{
		VetorX[i] = 0;	
	}
	
	//Acha o primeiro x que é atípico
	VetorX[Tamanho-1] = VetorB[Tamanho-1] / MatrizA[Tamanho-1][Tamanho-1];
	
	//Acha os demais X
	for(int i = (Tamanho-2);i >= 0;i--)
	{
		Somatorio = 0;
		for(int j = i;j < Tamanho;j++)
		{
			//printf("\n %f + ",Somatorio);
			Somatorio = Somatorio + MatrizA[i][j] * VetorX[j];

			//printf("%f * %f = %f" ,MatrizA[i][j] , VetorX[j], Somatorio);
		}
		Aux = 0;
		AuxTruc = 0;
		Aux1 = 0;
		VetorX[i] = (VetorB[i] - Somatorio) / MatrizA[i][i];
		AuxTruc = trunc(VetorX[i]);
		Aux = (VetorX[i]) - (AuxTruc);
		Aux1 = (float) (1 - fabs(Aux));
		//printf("%f\t%f\n",Aux,Aux1);

		printf("%f",VetorX[i]);
		if(fabs(Aux1) <= ERRO){
			if(Aux >= 0){
				VetorX[i] = ceil(VetorX[i]);
			}else{
				VetorX[i] = floor(VetorX[i]);
			}
		}
		if(fabs(Aux) <=ERRO){
			if(Aux < 0){
				VetorX[i] = ceil(VetorX[i]);
			}else{
				VetorX[i] = floor(VetorX[i]);
			}
		}
		if(VetorX[i] == (-0)){
			VetorX[i] = 0;
		}
		printf("\t%f\n",VetorX[i]);
	}
}




