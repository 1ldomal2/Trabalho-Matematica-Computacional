//###########################################
/*
	Recebe uma função, 2 valores referente ao intervalo [Min,Max], e 
	o numero de trapézios
	
	Retorna a Area sobre a curva no intervalo [Min,Max],
	por intermedio do somatorio da area de diversos trapézios 
*/
//###########################################

//Ponteiro para função que tem como argumento um numero flutuante
//float (*F)(float);

float Funcao(float Min,float Max,int NumeroTrapezios){

	//Descobre o Tamanho da altura ( que é o mesmo tamanho para todos)
	float Range=Max-Min;
	float Altura=(float)Range/NumeroTrapezios;

	//Somatorio das areas do trapeziozio;
	float Ponto1=Min;//F(Min)
	float Ponto2=Min+Range;//F(Min+Range)
	float AreaTotal=0;
	for (int i = 1; i <=NumeroTrapezios; ++i)
	{
		Area=(float) ( ( F(Ponto1) + F(Ponto2) ) * Altura) / 2      // (B+b)*H/2
		Ponto1+=Range;
		Ponto2+=Range;
		AreaTotal+=Area
	}
	return AreaTotal;
}




}
