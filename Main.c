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




int main(int argc, char const *argv[])
{
	float MatrizA[3][3] = {1,2,1,4,2,1,2,0,2};
	
	float VetorB[3] = {56,131,64};
	float VetorX[3];
	Gauls(3,MatrizA,VetorB);
	//SubsRetro(3,&VetorB,VetorX,MatrizA);
	for(int i = 0;i < 3;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			printf("%f\t",MatrizA[i][j]);	
		}
		printf("\n");
	}
	Gauls(3,MatrizA,VetorB);
	printf("\n");

	
	return 0;
}