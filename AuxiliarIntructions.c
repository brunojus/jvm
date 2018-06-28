/*
 Universidade de Brasilia  - UnB
 Departamento de Ciencia da Computacao  - CIC
 Disciplina:  Software Basico
 Professor:  Marcelo Ladera
 Turma: A
 Alunos:
       Tomaz Aguiar 090040121
       Lucas Braga 090009746
       Lucas Lo Ami 090009886
       Leonardo de Sousa Melo 0834220
       Artur de Azevedo 0990001
*/


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
