#include "leitor.h"

u1 u1Read(FILE* fd);
u2 u2Read(FILE* fd);
u4 u4Read(FILE* fd);
void finish_record(FILE *fd, FILE *arq, ClassFile* cf);
int return_type(char* type);
FILE* open_arq(char *namefile);
FILE * handlerio(int argc, char *argv[], char *namefile, FILE **arq);