#include "AuxiliarInstructions.h"

double fmod(double f1, double f2){
	long long el1, el2;
	el1 = (long long)f1;
	el2 = (long long)f2;
	return(double) (el1 % el2);
	
}

float quociente(float f1,float f2){
	int saida = (int) f1/f2;
	return (float)saida;
}
