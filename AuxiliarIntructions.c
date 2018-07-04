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

/*Verifica o conteúdo da string e retorna qual é o seu tipo*/
int return_type(char* type) {
    if (!strcmp(type, "ConstantValue")) {
        return CONSTANTVALUE;
    } else if (!strcmp(type, "Code")) {
        return CODE;
    } else if (!strcmp(type, "Exceptions")) {
        return EXCEPTIONS;
    } else if (!strcmp(type, "InnerClasses")) {
        return INNERCLASSES;
    } else {
        return OTHER;
    }
}
