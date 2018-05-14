#include "leitor.h"
#include "exibidor.h"
#include "auxiliar.h"

int main(int argc, char* argv[]) {
    char namefile[1024];
    FILE* arq = NULL;
    FILE *fd = handlerio(argc, argv, namefile, &arq);
    ClassFile* cf = readClass(fd);
    print_class(cf, namefile, arq);
    finish_record(fd, arq, cf);
    return 0;
}