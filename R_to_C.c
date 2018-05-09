//###########################################
/*
	Mudar linguagem dos Algoritmos de R para C, 
	Algoritmos de Horney,Gauls com pivoteamento
*/
//###########################################

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Resolve uma função Polinomial de maneira mais eficiente
//Recebe Um vetor com os coeficiente o tamanho do vetor e o valor de X
//Retorna f(x) ou seja a imagem no ponto X
float Horner(float Coeficiente[],int Tamanho,float DominioX){
	float ImagemY=Coeficiente[0];
	for (int i = 1; i < Tamanho; ++i)
	{
		ImagemY=ImagemY*DominioX+Coeficiente[i];
	}
	return ImagemY;
}



void Gauls(float **MatrizA,float VetorB[],int Tamanho){

	//Cria Dois vetores para trocar matriz                                                     
	float VetorSwapA[Tamanho];
	float VetorSwapB[Tamanho];

	//Inicializa os Vetores do Swap
	for (int i = 0; i < Tamanho; ++i)
	{
		VetorSwapA[i]=0;
		VetorSwapB[i]=0;
	}

	//Vai da primeira até a penultima linha zerando-as
	for (int Pivo = 0; Pivo < Tamanho-1; ++Pivo)
	{
		int IndiceMaior = Pivo;
		float Maior =MatrizA[Pivo][Pivo];

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

			//Swap B
			VetorSwapB[i]=VetorB[Pivo];
			VetorB[Pivo]=VetorB[IndiceMaior];
			VetorB[IndiceMaior]=VetorSwapB[i];
		}
		

		//Acha o Escalar que ira zerar as linhas
		float Escalar=1;
		for (int LinhaTrabalha = (Pivo+1); LinhaTrabalha < Tamanho; ++LinhaTrabalha)
		{
			Escalar=MatrizA[LinhaTrabalha][Pivo]/MatrizA[Pivo][Pivo];

			for (int Coluna = 0; Coluna < Tamanho; ++Coluna)
			{
				MatrizA[LinhaTrabalha][Coluna]=MatrizA[LinhaTrabalha][Coluna]-(Escalar*MatrizA[Pivo][Coluna]);
			}
			VetorB[LinhaTrabalha]=VetorB[LinhaTrabalha]-(Escalar*VetorB[Pivo]);
		}
	}

	return;
}

void SubsRetro(float **MatrizA,float VetorB[],float VetorX[],int Tamanho){
	float Somatorio = 0;
	//Zera matriz para evitar erros
	for(int i = 0;i < Tamanho;i++)
	{
		VetorX[i] = 0;	
	}
	VetorX[Tamanho] = VetorB[Tamanho] / MatrizA[Tamanho][Tamanho];

	for(int i = (Tamanho -1);i < 0;i--)
	{
		Somatorio = 0;
		for(int j = (i + 1);j < Tamanho;j++)
		{
			Somatorio = Somatorio + MatrizA[i][j] * VetorX[j];
		}
		VetorX[i] = (VetorB[i] - Somatorio) / MatrizA[i][i];
	}
}
int main(int argc, char const *argv[])
{
	float MatrizA[3][3] = {4,4,4,3,1,2,6,3};
	float VetorB[3] = {59,97,66};
	float VetorX[3];
	Gauls(MatrizA,VetorB,3);
	SubsRetro(MatrizA,VetorB,VetorX,3);
	for(int i = 0;i < 3;i++)
	{
		printf("%f",VetorX[i]);	
	}

	
	return 0;

}



