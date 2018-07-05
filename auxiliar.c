#include <errno.h>
#include "leitor.h"

/*
* Lê 1 byte do arquivo de entrada .class
*/
u1 u1Read(FILE* fd) {
    return getc(fd);
}

/*
* Lê 2 bytes do arquivo de entrada .class
* Par isso, a função primeiro lê 1 byte,
faz um SHIFT de 8 bits para a esquerda
e depois faz um OR com o próximo byte.
Ela basicamente concatena os bytes
em uma váriavel e a retorna.
*/
u2 u2Read(FILE* fd) {
    u2 toReturn = getc(fd);
    toReturn = (toReturn << 8)|(getc(fd));
    return toReturn;
}

/*
* Lê 4 bytes do arquivo de entrada .class
* Par isso, a função primeiro lê 2 bytes,
faz um SHIFT de 16 bits para a esquerda
e depois faz um OR com os próximos bytes.
Ela basicamente concatena os bytes
em uma váriavel e a retorna.
*/
u4 u4Read(FILE* fd) {
    u4 toReturn = u2Read(fd) << 16;
    toReturn |= u2Read(fd);
    return toReturn;
}

/*Verifica o conteúdo da string e retorna qual é o seu tipo*/
int return_type(char* type) {
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
void free_constpool(ClassFile *cf) {
    cp_info *cp;
    for(cp = cf->constant_pool;cp<cf->constant_pool+cf->constant_pool_count-1;++cp) {
       if (cp->tag == UTF8)
         free(cp->info.Utf8_info.bytes);
    }
    free(cf->constant_pool);
}

/*Função responsável por desalocar memória e finalizar a gravação no arquivo*/
void finish_record(FILE *fd, FILE *arq, ClassFile* cf) {
    if (!cf)
      return;
    free_constpool(cf);
    if (cf->fields)
      free(cf->fields);
    if (cf->interfaces)
      free(cf->interfaces);
    free(cf->methods);
    free(cf);

    fclose(arq);
    fclose(fd);
    printf("Finish!\n");
}

/*
* Abre o arquivo com nome guardado em namefile.
* Retorna o ponteiro para o arquivo caso consiga abrir.
* Retorna NULL caso não consiga.
* rb -> Abre arquivo binário apenas para leitura.
*/
FILE* open_arq(char *namefile) {
    FILE* fp = fopen(namefile, "rb");
    if (!fp) {
        printf("Erro: Arquivo não encontrado.\n");
        return NULL;
    } else {
        return fp;
    }
}
/*
* Função que inicializa os arquivos passados como argumentos no terminal.
* Se argc == 1, não foi passado nenhum argumento. Por isso, a função
pede o nome do arquivo class a ser lido e define o arquivo de saída como
"output.txt"
* Se argc == 3, foram passados tanto o nome do arquivo de saída quanto
o arquivo de entrada.
* Se argc tiver algum valor diferente de 1 ou de 3, o programa é fechado.
Uma mensagem de como rodar o programa é impressa antes de fechar.
* Se tudo ocorrer como esperado na abertura do arquivo de entrada, a função
procede para abrir o arquivo de saída. Caso consiga abrir, a função acaba.
Caso contrário, imprime na tela o código do erro e fecha o programa.
*/
FILE * handlerio(int argc, char *argv[], char *namefile, FILE **arq)
{
  FILE *fd = NULL;
  char saidaarquivo[1024] = "output.txt";

  if (argc == 1) {

    do
    {
      printf("Digite o nome do arquivo: ");
      scanf("%s", namefile);
      fflush(stdin);
      fd = open_arq(namefile);
    } while (!fd);

  }
  else if (argc == 3)
  {
    strcpy(namefile, argv[1]);
    fd = open_arq(namefile);
    strcpy(saidaarquivo, argv[2]);
  }
  else
  {
    printf("Uso do programa: ./leitorexibidor [nome-do-class nome-da-saída]\n");
    exit(0);
  }

  if (!(*arq = fopen(saidaarquivo, "w+"))) {
    fprintf(stderr, "Erro %d na abertura do arquivo de saida\n", errno);
    exit(0);
  }

  return fd;
}
