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

void print_versions(ClassFile* cf, FILE* arq) {
    fprintf(arq, "-- MINOR VERSION: %d\n", cf->minor_version);
    char *version_jdk =  look_version(cf->major_version);
    fprintf(arq, "MAJOR VERSION: %d - %s\n", cf->major_version, version_jdk);
    free(version_jdk);

    fprintf(arq, "-- CONSTANT POOL COUNT: %d\n", cf->constant_pool_count);

    fprintf(arq, "-- ACCESS_FLAGS: %x ", cf->access_flags);
    print_flags(cf->access_flags, arq);
    fprintf(arq, "\n");
    fprintf(arq, "-- THIS_CLASS: %d\n", cf->this_class);
    fprintf(arq, "-- SUPER_CLASS: %d\n", cf->super_class);

    fprintf(arq, "-- INTERFACES_COUNT: %d\n", cf->interfaces_count);
    fprintf(arq, "-- FIELDS_COUNT: %d\n", cf->fields_count);
    fprintf(arq, "-- METHODS_COUNT: %d\n", cf->methods_count);
    fprintf(arq, "-- ATTRIBUTES_COUNT: %d\n\n", cf->attributes_count);

}

char* look_version(int code) {

    char* version_jdk;
    switch (code) {
        case 45:
            version_jdk = (char*) malloc(sizeof(char) * 8);
            strcpy(version_jdk, "JDK 1.1");
            break;
        case 46:
            version_jdk = (char*) malloc(sizeof(char) * 8);
            strcpy(version_jdk, "JDK 1.2");
            break;
        case 47:
            version_jdk = (char*) malloc(sizeof(char) * 8);
            strcpy(version_jdk, "JDK 1.3");
            break;
        case 48:
            version_jdk = (char*) malloc(sizeof(char) * 8);
            strcpy(version_jdk, "JDK 1.4");
            break;
        case 49:
            version_jdk = (char*) malloc(sizeof(char) * 12);
            strcpy(version_jdk, "Java SE 5.0");
            break;
        case 50:
            version_jdk = (char*) malloc(sizeof(char) * 12);
            strcpy(version_jdk, "Java SE 6.0");
            break;
        case 51:
            version_jdk = (char*) malloc(sizeof(char) * 10);
            strcpy(version_jdk, "Java SE 7");
            break;
        case 52:
            version_jdk = (char*) malloc(sizeof(char) * 10);
            strcpy(version_jdk, "Java SE 8");
            break;
        case 53:
            version_jdk = (char*) malloc(sizeof(char) * 10);
            strcpy(version_jdk, "Java SE 9");
            break;
        case 54:
            version_jdk = (char*) malloc(sizeof(char) * 10);
            strcpy(version_jdk, "Java SE 10");
            break;
        default:
            version_jdk = (char*) malloc(sizeof(char) * 21);
            strcpy(version_jdk, "Java desconhecido");
            break;
    }
    return version_jdk;
}