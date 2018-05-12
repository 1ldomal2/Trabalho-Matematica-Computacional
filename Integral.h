#ifndef _Integral_
#define _Integral_
typedef struct arquivo{
	float *x;
	float *y;
	int n;
	float a;
	float b;
	float i;
	float *p;
	float t;
}ARQUIVO;
typedef struct Matrizes{
	float **MatrizA;
	float *VetorB;
	float *VetorX;
}MATRIZ;
typedef int bool;
float Funcao(float Min,float Max,int NumeroTrapezios,ARQUIVO *Lidos);
int Interpolacao(char Url[],ARQUIVO *File);
void Seta_Valores_Structs_Verifica_0(ARQUIVO *Verifica);
bool Verifica_Arquivo_Valido(ARQUIVO Verifica);
void Prepara_Matriz(ARQUIVO *Lida,MATRIZ *matriz);
#endif 