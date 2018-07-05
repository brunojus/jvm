#include "leitor.h"
#include "exibidor.h"
#include "auxiliar.h"

int main(int argc, char* argv[]) {
    char namefile[1024]; // Variável para guardar o nome do arquivo de entrada
    FILE* arq = NULL;

    // Vai abrir tanto o arquivo de entrada .class quanto o de saída
    // Se tudo acontecer dentro do esperado, fd será o ponteiro para o arquivo de entrada
    // A variável arq será modificada por referência e será o ponteiro para o arquivo de saída
    FILE *fd = handlerio(argc, argv, namefile, &arq);

    // Recebe apenas o ponteiro do arquivo de entrada .class
    // Tal ponteiro de entrada é modificado por referência enquanto o arquivo .class é lido
    // Ao final dessa função, se espera um ponteiro para a struct ClassFile corretamente carregada
    ClassFile* cf = readClass(fd);

    // Recebe a estrutura ClassFile carregada, o nome do arquivo .class de entrada e  ponteiro para o arquivo de saida
    // Ao final da função, se expera um "output.txt" corretamente preenchido de acordo com os valores da estrutura
    print_class(cf, namefile, arq);

    // Desaloca todas as estruturas do programa, juntamente com os poteiros de arquivo
    // Ao final dessa função, é esperado total liberação do espaço usado. 
    finish_record(fd, arq, cf);
    return 0;
}

/* ClassFile está definido no arquivo leitor.h
*  Ele inclui 16 variáveis, incluindo ponteiros para outras estruturas do mesmo arquivo.
*/
