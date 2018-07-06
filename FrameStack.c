#include <stdlib.h>
#include "FrameStack.h"

/*FRAME STACK*/


void push_frame (cp_info* cp, StaticAtrib* sa, method_info *mf, FrameStack* fs){
    frame *f = (frame *) malloc (sizeof(frame));
    f->cPoolRunTime = cp;    /*ponteiro para o constant pool run time*/
    f->pStaticAtrib = sa;    /*ponteiro para o vetor de variaveis estaticas*/
    f->LocalVariables = (u4 *) malloc(mf->attributes->data.Code_attribute.max_locals*sizeof(u4));/*Alocacao de espaco para vetor de variaveis locais*/
    f->pointers = (void **) malloc((mf->attributes->data.Code_attribute.max_locals+mf->attributes->data.Code_attribute.max_stack)*sizeof(void *));
    f->countpoint=0;
    f->pc=0;    /*PC inicial*/
    f->method = mf; /*ponteiro para as informacoes do metodo*/
    f->opStack.top=NULL;    /*Inicializa a pilha de operandos*/
    f->next=NULL;    /*Inicializa a pilha de Frames*/
    if (fs->top==NULL){
        fs->top=f;
    }
    else{
        f->next=fs->top;
        fs->top=f;
    }

}

void pop_frame (FrameStack* fs){
    frame* aux;
    aux =fs->top;
    /*Libera a pilha de operandos*/
    free_operand_stack(&(fs->top->opStack));
    fs->top =fs->top->next;/*Recebe o frame que estava no topo*/
   if (aux->LocalVariables!=NULL)
        free(aux->LocalVariables);
    /*Libera o frame*/
    free(aux);

}


/*OPERAND STACK*/

void push_operand (u4 data, operand_stack *opstack){    
    stack* new_operand = (stack *) malloc(sizeof(stack));/*Alocacao do novo operando*/
    if (opstack->top!=NULL){    /*Se nao for o primeiro da pilha de operandos*/
        new_operand->next = opstack->top;
        new_operand->data = data;
        opstack->top=new_operand;
        
    }else{
        new_operand->data = data;    
        new_operand->next = NULL;    
        opstack->top=new_operand;
    }        
}

/*Funcao que desempilha toda a pilha de operandos*/
void free_operand_stack (operand_stack *opstack){
    while (opstack->top!=NULL)
        pop_operand(opstack);

}

u4  pop_operand (operand_stack *opstack){    
    u4  Return;
    stack *temp;    
    if (opstack->top!=NULL){
        Return = opstack->top->data;
        temp = opstack->top;
        if (opstack->top->next !=NULL)
            opstack->top = opstack->top->next;
        else
            opstack->top = NULL;
        free(temp);/*depois de pegar o operador libera a memória*/
        return Return;
    }else{
        exit(1);
    }
}
