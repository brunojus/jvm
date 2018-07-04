#include "exibidor.h"


void print_func_magic(ClassFile* cf, FILE* arq) {
    fprintf(arq, "-- MAGIC: %x\n", cf->magic);
}