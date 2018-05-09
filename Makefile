main:	Main.o	R_to_C.o	Integral.o
	gcc Main.o R_to_C.o Integral.o -o exe
	rm *.o 

main.o:	Main.c
	gcc -c Main.c

R_to_C.o:	R_to_C.c	R_to_C.h
	gcc -c R_to_C.c

Integral.o:	Integral.c	Integral.h
	gcc -c Integral.c

	
	