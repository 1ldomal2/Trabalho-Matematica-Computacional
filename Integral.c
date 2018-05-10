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
#include "Integral.h"
#include "R_to_C.h"


//Ponteiro para função que tem como argumento um numero flutuante
//float (*F)(float);
//F=Horner();

float Funcao(float Min,float Max,int NumeroTrapezios){

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
	//	Area=(float) ( ( Horner(Ponto1) + Horner(Ponto2) ) * Altura) / 2 ) );   // (B+b)*H/2
		Ponto1+=Range;
		Ponto2+=Range;
		AreaTotal+=Area;
	}
	return AreaTotal;
}

int Interpolacao(char Url[],ARQUIVO *File){
	FILE *Arquivo;
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
		
		//Verifica se a linha é um comentario
		if(Buff == '#'){
			fscanf(Arquivo,"%[^\n]s",String);
			//Pula o /n
			getc(Arquivo);
			continue;
		}
	printf("%c\n",Buff);

		switch (Buff){
			case 'n':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&File->n);//Le o Tamanho
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'x':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				for(int i = 1;i <= File->n;i++)
				{
					fscanf(Arquivo,"%f",&valor);
					getc(Arquivo);
					printf("%f\t",valor); 	
					File->x=(float*)realloc(File->x,i * sizeof(float));
					File->x[i] = valor;
				}
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'y':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				for(int i = 1;i <= File->n;i++)
				{
					fscanf(Arquivo,"%f",&valor);
					getc(Arquivo); 	
					printf("%f\t",valor); 
					File->y=(float*)realloc(File->y,i * sizeof(float));
					File->y[i] = valor;
				}
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'a':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				getc(Arquivo); 	
				File->a = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'b':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				getc(Arquivo); 	
				File->b = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'i':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				fscanf(Arquivo,"%f",&valor);
				getc(Arquivo); 	
				File->i = valor;
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 'p':
				fscanf(Arquivo,"%c",&Buff);//Pula o espaço
				for(int i = 1;i <= File->i;i++)
				{
					fscanf(Arquivo,"%f",&valor);
					getc(Arquivo); 	
					File->p=(float*)realloc(File->p,i * sizeof(float));
					File->p[i] = valor;
				}
				fscanf(Arquivo,"%c",&Buff);//Pula o \n
				break;
			case 't':
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
			printf("%c",Buff);
				printf("Erro ao ler");
				return -2;
				break;
		}
	}
	return 0;
}
