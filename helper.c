#include <errno.h>
#include "leitor.h"

u1 u1Read(FILE* fd) {
    return getc(fd);
}

u2 u2Read(FILE* fd) {
    u2 toReturn = getc(fd);
    toReturn = (toReturn << 8)|(getc(fd));
    return toReturn;
}

u4 u4Read(FILE* fd) {
    u4 toReturn = u2Read(fd) << 16;
    toReturn |= u2Read(fd);
    return toReturn;
}

/*Verifica o conteúdo da string e retorna qual é o seu tipo*/
int findtype(char* type) {
    if (!strcmp(type, "ConstantValue")) {
        return CONSTANTVALUE;
    } else if (!strcmp(type, "Code")) {
        return CODE;
    } else if (!strcmp(type, "Exceptions")) {
        return EXCEPTIONS;
    } else if (!strcmp(type, "InnerClasses")) {
        return INNERCLASSES;
    } else {
        return OTHER;
    }
}

/*Desaloca a memória da constant pool*/
void free_cte_pool(ClassFile *cf) {
    cp_info *cp;
    for(cp = cf->constant_pool;cp<cf->constant_pool+cf->constant_pool_count-1;++cp) {
       if (cp->tag == UTF8)
         free(cp->info.Utf8_info.bytes);
    }
    free(cf->constant_pool);
}

/*Função responsável por desalocar memória e finalizar a gravação no arquivo*/
void shutdown(FILE *fd, FILE *fout, ClassFile* cf) {
    if (!cf)
      return;
    free_cte_pool(cf);
    if (cf->fields)
      free(cf->fields);
    if (cf->interfaces)
      free(cf->interfaces);
    free(cf->methods);
    free(cf);

    fclose(fout);
    fclose(fd);
    printf("Finalizado!\n");
}


FILE* open_file(char *nomearquivo) {
    FILE* fp = fopen(nomearquivo, "rb");
    if (!fp) {
        printf("Erro: Arquivo não encontrado.\n");
        return NULL;
    } else {
        return fp;
    }
}

FILE * io_handler(int argc, char *argv[], char *nomearquivo, FILE **fout)
{
  FILE *fd = NULL;
  char saidaarquivo[1024] = "output_class.txt";
  if (argc == 1) {
    do {
      printf("Digite o nome do arquivo: ");
      scanf("%s", nomearquivo);
      fflush(stdin);
      fd = open_file(nomearquivo);
    } while (!fd);
  } else if (argc == 3) {
    strcpy(nomearquivo, argv[1]);
    fd = open_file(nomearquivo);
    if (!fd) {
      printf("Arquivo de entrada não encontrado!\n");
      exit(0);
    }
    strcpy(saidaarquivo, argv[2]);

  } else {
    printf("Uso do programa: ./leitorexibidor [nome-do-class nome-da-saída]\n");
    exit(0);
  }
  if (!(*fout = fopen(saidaarquivo, "w+"))) {
    fprintf(stderr, "Erro %d na abertura do arquivo de saida\n", errno);
    exit(0);
  }
  return fd;
}
