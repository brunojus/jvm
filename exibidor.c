#include "exibidor.h"


/**
*  \brief Funcao que realiza o shift a esquerda do bit 0..01 em 'id' posições
*  \code,id int
*  \return o bit com a operação de shift
*
*/

int bit_is_true(int code, int id) {
    return code & (1 << id);
}

/**
*  \brief Funcao que realiza o print das flags
*  \code int arq FILE
*  \return o arquivo de acordo com a tabela em https://docs.oracle.com/javase/specs/jvms/se7/html/jvms-4.html#jvms-4.1-200-E.1
*
*/


void print_flags(int code, FILE* arq) {

    fprintf(arq, "[");

    if (bit_is_true(code, 0)) fprintf(arq, "public ");
    else if (bit_is_true(code, 1)) fprintf(arq, "private ");
    else if (bit_is_true(code, 2)) fprintf(arq, "protected ");
    if (bit_is_true(code, 3)) fprintf(arq, "static ");
    if (bit_is_true(code, 4)) fprintf(arq, "final ");
    if (bit_is_true(code, 5)) fprintf(arq, "super ");
    if (bit_is_true(code, 6)) fprintf(arq, "volatile ");
    if (bit_is_true(code, 7)) fprintf(arq, "transient ");
    if (bit_is_true(code, 8)) fprintf(arq, "native ");
    if (bit_is_true(code, 9)) fprintf(arq, "interface ");
    if (bit_is_true(code, 10)) fprintf(arq, "abstract ");

    fprintf(arq, "]");
}


void print_func_magic(ClassFile* cf, FILE* arq) {
    fprintf(arq, "-- MAGIC: %x\n", cf->magic);
}