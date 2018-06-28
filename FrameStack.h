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
#include "ClassLoader.h"

#ifndef __FRAME_STACK__
#define __FRAME_STACK__



/*OPERAND STACK*/

/*
*  \brief Estrutura principal dos operandos para a pilha
*/
typedef struct operand{
    u4 data;
    struct operand *next;
}stack;
/**
*  \brief Estrutura da pilha propriamente dita
*/
typedef struct operand_stack{
    struct operand *top;
}operand_stack;

/**
*  \brief Função que coloca um operando na pilha
*  \param data O operando a ser empilhado
*  \param *stack ponteiro para a pilha
*/
void push_operand (u4 data, operand_stack *stack);
/**
*  \brief Função que desempilha um operando da pilha
*  \param *stack ponteiro para a pilha
*  \return O operando desimpilhado
*/
u4 pop_operand (operand_stack *stack);

/**
*  \brief Função que libera a pilha da memória
*  \param *opstack ponteiro para a pilha
*/
void free_operand_stack (operand_stack *opstack);



/*FRAME STACK*/

/**
*  \brief Estrutura dos elementos da pilha de frames
*/
typedef struct frame{
    operand_stack opStack;/*pilha de operandos*/
    cp_info* cPoolRunTime; /*Ponteiro para a pilha de operandos*/
    StaticAtrib* pStaticAtrib; /*Ponteiro para o vetor de variáveis estáticas*/
    u4* LocalVariables;    /*Vetor de variáveis locais*/
    void ** pointers;    /*vetor de ponteiros para qualquer alocação dinâmicas*/
    u4 countpoint;    /*aponta para o "topo" do vetor pointers*/
    void *tempMultArray; /*Vetor para guardar o array multidimencional*/
    method_info *method; /*Ponteiro para a informações do metodo*/
    u4 pc;            /*Program counter*/
    struct frame *next;  /*Ponteiro para a próxima entrada do frame*/
}frame;
/**
*  \brief Estrutura da pilha de frames
*/
typedef struct FrameStack{
    struct frame *top;/*Ponteiro para o topo*/
}FrameStack;
/**
*  \brief Função que adiciona um frame
*  \param *cp Ponteiro para o constant pool
*  \param *mf Ponteiro para as informações do método
*  \param *fs Ponteiro para a pilha de frames
*/
void push_frame (cp_info* cp, StaticAtrib* sa, method_info *mf, FrameStack* fs);

/*
*  \brief Função que retira um frame da pilha
*  \param *fs Ponteiro para a pilha de frames
*/
void pop_frame (FrameStack* sf);

#endif
