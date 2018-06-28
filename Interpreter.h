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



#include "MethodArea.h"
#include "FrameStack.h"
#include "Opcodes.h"
#include "Instructions.h"

#ifndef __INTERPRETER_H_
#define __INTERPRETER_H_

/*
Funcao e reposnsavel por empilhar um novo frame e passar os prametros para funcao que foi chamada, e executa esta funcao
 method O ponteiro para o nome da funcao
 descriptor ponteiro para o descritor
 class_name ponteiro para o nome da class
 nargs numero de argumentos da funcao
 fr ponteiro para a pilha de frame
 param  especial flag que indica se a funcao alem dos argumentos tambem passar um ponteiro para um objeto
*/
void executar(char* method, char* descriptor, char* class_name,int nargs, FrameStack* fr, int especial);

/*
Funcao e reposnsavel contar o numero de argumentos de um funcao a partir do descritor funcao que foi chamada, e executa esta funcao
 descriptor ponteiro para o descripto
 length tamanho do descritor
 toReturn numero de argumentos
*/

int Nargs(char *descriptor, int length); /*nargs e o numero de argumentos*/

/*
Funcao e responsavel por imprimir na tela a saida do programa java
 fr  ponteiro para a pilha de frame
 descriptor ponteiro para o descriptor
 length tamanho do descritor
*/


void executarPrintln(FrameStack* fr, char* descriptor, int length);

/*
Funcao e responsavel por decodificar um intrucao e chamar a funcao correta
 opcode byte que correponde ao opcode de uma instrucao valida
 fr ponteiro para a pilha de frame
*/

void executarInstrucao(unsigned char opcode,FrameStack* fr);

/*
Funcao responsavel executar a funcao clinit para inicializar as variaveis estaticas e a segunda executa o contrutor de uma classe
 fr ponteiro para a pilha de frame
*/
void executarClinit(FrameStack* fr);


void executarInstrucao(unsigned char opcode,FrameStack* fr);

#endif /*__INTERPRETER_H_*/
