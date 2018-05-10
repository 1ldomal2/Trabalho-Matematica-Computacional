#ifndef _Integral_
#define _Integral_
typedef struct arquivo{
	float *x;
	float *y;
	float n;
	float a;
	float b;
	float i;
	float *p;
	float t;
}ARQUIVO;
float Funcao(float Min,float Max,int NumeroTrapezios);
int Interpolacao(char Url[],ARQUIVO *File);
#endif 