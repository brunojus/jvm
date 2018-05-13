#include "leitor.h"
#include "exibidor.h"
#include "helper.h"


int main(int argc, char* argv[]) {
    char namefile[1024];
    FILE* arq = NULL;

    FILE *fd = io_handler(argc, argv, namefile, &arq);

    ClassFile* cf = readClass(fd);
    print_class(cf, namefile, arq);
    shutdown(fd, arq, cf);
    return 0;
}