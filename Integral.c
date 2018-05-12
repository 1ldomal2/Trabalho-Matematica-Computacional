//###########################################
/*
	Recebe uma função, 2 valores referente ao intervalo [Min,Max], e 
	o numero de trapézios
	
	Retorna a Area sobre a curva no intervalo [Min,Max],
	por intermedio do somatorio da area de diversos trapézios 
*/
//###########################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Integral.h"
#include "R_to_C.h"
#define DEBUG printf("\nLinha = %d Arquivo = %s\n",__LINE__,__FILE__);
#define true 1
#define false 0

//Ponteiro para função que tem como argumento um numero flutuante
//float (*F)(float);
//F=Horner();

float Funcao(float Min,float Max,int NumeroTrapezios,ARQUIVO *Lido){
	//Descobre o Tamanho da altura ( que é o mesmo tamanho para todos)
	float Range=Max-Min;
	float Altura=(float)Range/NumeroTrapezios;
	//Somatorio das areas do trapeziozio;
	float Ponto1=Min;//F(Min)
	float Ponto2=Min+Range;//F(Min+Range)
	float AreaTotal=0;
	float Area;
	for (int i = 1; i <=NumeroTrapezios; ++i)
	{
	//Area=(float) ( ( Horner(Ponto1) + Horner(Ponto2) ) * Altura) / 2 ) );   // (B+b)*H/2
	//Horner(float Coeficiente[],int Tamanho,float DominioX);

		Ponto1+=Range;
		Ponto2+=Range;
		AreaTotal+=Area;
	}
	return AreaTotal;
}

void Prepara_Matriz(ARQUIVO *Lida,MATRIZ *matriz){
	matriz->MatrizA = (float**)malloc(Lida->n * sizeof(float*));
	for(int i = 0;i < Lida->n;i++){
		matriz->MatrizA[i] = (float*)malloc(Lida->n * sizeof(float));
	}
	//preenche a MatrizA
	for(int i = 0;i < Lida->n;i++){//linha
		for(int j = 0;j < Lida->n;j++){//coluna
			if(j == 0){
				matriz->MatrizA[i][j] = 1; // x⁰ = 1
			}else if(j ==1){
				matriz->MatrizA[i][j] = Lida->x[i];// x¹ = x
			}else{
				matriz->MatrizA[i][j] = matriz->MatrizA[i][j - 1] * matriz->MatrizA[i][1]; 
				// x^n = x^(n-1) * x
				// Mais eficiente que POW
			}
		}
	}
	// Preenche Vetor B
	matriz->VetorB = (float*)malloc(Lida->n * sizeof(float));
	for(int j = 0;j < Lida->n;j++){//coluna
		matriz->VetorB[j] = Lida->y[j];
	}
	matriz->VetorX = (float*)malloc(Lida->n * sizeof(float));
	for(int j = 0;j < Lida->n;j++){//coluna
		matriz->VetorX[j] = 0;
	}
}

void Seta_Valores_Structs_Verifica_0(ARQUIVO *Verifica){
//Funcao responsavel por setar todos os valores como False indicando que ainda nao foram lidos corretamente 
	Verifica->x=(float*)malloc(sizeof(float));
	Verifica->y=(float*)malloc(sizeof(float));
	Verifica->p=(float*)malloc(sizeof(float));
	Verifica->x[0] = false;
	Verifica->y[0] = false;
	Verifica->n = false;
	Verifica->a = false;
	Verifica->b = false;
	Verifica->i = false;
	Verifica->p[0] = false;
	Verifica->t = false;
}
bool Verifica_Arquivo_Valido(ARQUIVO Verifica){
	//Verifica se todos campos da struct esta como true indicando que arquivo tem parametros corretos
	if(Verifica.x[0] == true){
		if(Verifica.y[0] == true){
			if(Verifica.n == true){
				if(Verifica.a == true){
					if(Verifica.b == true){
						if(Verifica.i == true){
							if(Verifica.p[0] == true){
								if(Verifica.t == true){
									return true;//retorna true indicando que foi corretamente
								}else{
									printf("No t");
								}
							}else{
								printf("No p");
							}
						}else{
							printf("No i");
						}
					}else{
						printf("No b");
					}
				}else{
					printf("No a");
				}
			}else{
				printf("No n");
			}
		}else{
			printf("No y");
		}
	}else{
		printf("No x");
	}
	return false;//retorna false indicando que nao foi corretamente
}


int Interpolacao(char Url[],ARQUIVO *File){
	FILE *Arquivo;
	ARQUIVO Verifica;
	Seta_Valores_Structs_Verifica_0(&Verifica);
	Arquivo=fopen(Url,"r");
	char Buff;
	float valor;
	char String[999];
	//Verifica se o arquivo existe
	if(Arquivo == NULL ){
		printf("O arquivo não foi aberto\n");
		return -1;
	}
	
	//Le o Arquivo
		while(!feof(Arquivo)){
		fscanf(Arquivo,"%c",&Buff);
			if(feof(Arquivo)){//Caso chegue no fim do arquivo sai do LOOP
			break;
		}
		//Verifica se a linha é um comentario
			if(Buff == '#'){
			fscanf(Arquivo,"%[^\n]s",String);
			//Pula o /n
			getc(Arquivo);
			continue;
		}

			switch (Buff){
			case 'n':
				Verifica.n = true;
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%d",&File->n);//Le o Tamanho
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'x':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				File->x=(float*)malloc(sizeof(float));
					for(int i = 1;i <= File->n;i++){
						fscanf(Arquivo,"%f",&valor);
						getc(Arquivo);//Pula
						File->x=(float*)realloc(File->x,i * sizeof(float));
						File->x[i-1] = valor;
						if(i == File->n ){
							Verifica.x[0] = true;
						}
					}
				break;
			case 'y':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
					File->y=(float*)malloc(sizeof(float));
					for(int i = 1;i <= File->n;i++){
					fscanf(Arquivo,"%f",&valor);
					if(valor == '-'){
						getc(Arquivo);
						fscanf(Arquivo,"%f",&valor);
						valor = valor * -1;
					}
					getc(Arquivo);	
					File->y=(float*)realloc(File->y,i * sizeof(float));
					File->y[i-1] = valor;
					if(i == File->n ){
						Verifica.y[0] = true;
					}
				}
				break;
			case 'a':
				Verifica.a = true;
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				File->a = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'b':
				Verifica.b = true;
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				File->b = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'i':
				Verifica.i = true;
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				File->i = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'p':
				File->p=(float*)malloc(sizeof(float));
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
					for(int i = 1;i <= File->i;i++){
						fscanf(Arquivo,"%f",&valor);
						getc(Arquivo); 	
						File->p=(float*)realloc(File->p,i * sizeof(float));
						File->p[i-1] = valor;
						if(i == File->i ){
							Verifica.p[0] = true;
						}
					}
				break;
			case 't':
				Verifica.t = true;
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				getc(Arquivo); 	
				File->i = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case '\n':
				break;
			case ' ':
				break;
			default:
				printf("Erro ao ler\n");
				return -2;
				break;
		}
	}
	if(Verifica_Arquivo_Valido(Verifica) == false){
		printf("Erro ao ler arquivo incompleto\n");
		return -3;
	}
	return 0;
}