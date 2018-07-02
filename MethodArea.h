#include <strings.h>
#include "ClassLoader.h"


#ifndef __METHODAREA_H__
#define __METHODAREA_H__

/**
*  \brief Estrutura que gerencia os array multidimensionais
*/
typedef struct arrayMult{
u2 * dimensions;
u2 dimensions_count;
void ** ptr;
void *values;
}arrayMult;


/**
*  \brief Estrutura que gerencia os atributos estáticos para cada tipo
*/

typedef union DataStaticAtrib{
    struct {
        u2 length;
        u1* staticString_bytes;
        u2 index_bytes;    /*ponteiro para a entrada do constant poll*/
    }staticString;

    u4 staticInt;
    arrayMult *staticArray;  /*indice do vetor de ponteiros*/
    struct{
        u4 staticLowLong;
        u4 staticHighLong;
    }staticLong;
    u4 staticFloat;
    struct{
        u4 staticLowDouble;
        u4 staticHighDouble;
    }staticDouble;

}DataStaticAtrib;

/**
*  \brief Estrutura que gerencia os atributos estáticos, mais geral
*/

typedef struct StaticAtrib{
    u2 type;
    u2 name_index;
    DataStaticAtrib data;

}StaticAtrib;

/**
*  \brief Estrutura que gerencia os atributos dinâmicos para cada tipo
*/

typedef union DataAtrib{
    struct {
        u2 length;
        u1* String_bytes;
        u2 index_bytes;
    }String;

    u4 Int;
    void* Array;    /*indice do vetor de ponteiros*/
    struct{
        u4 LowLong;
        u4 HighLong;
    }Long;
    u4 Float;
    struct{
        u4 LowDouble;
        u4 HighDouble;
    }Double;

}DataAtrib;

/**
*  \brief Estrutura que gerencia os atributos dinâmicos, mais geral
*/

typedef struct Object{
    u2 type;
    u2 name_index;
    DataAtrib data;

}Object;

/**
*  \brief Estrutura que gerencia uma classe carregada
*/

typedef struct Class{
    ClassFile *classFl;
    long long nAtribStatic;
    StaticAtrib *atribs;
    struct Class *nextClass;
}Class;

/**
*  \brief Função que insere uma classe na lista de classes
*  \param *newClass Ponteiro para a classe a ser inserida
*/
void insertClass(Class *newClass);
/**
*  \brief Limpa da memória toda a lista de classes
*/
void destroyClassList();
/**
*  \brief Função que extrai todos os parametros estáticos
*  \param *cf Ponteiro para a classe
*  \return Vetor de variáveis estáticas
*/
StaticAtrib * staticLoad(ClassFile * cf);
/**
*  \brief Função que procura e carrega uma classe do HD
*  \param *className Endereço da classe
*  \return Ponteiro para a classe
*/
Class *searchClass(char *className);
/**
*  \brief Função que procura o constant pool
*  \param *className Nome da classe
*  \return Ponteiro para o constant poll
*/
cp_info *cpSearch(char *className);
/**
*  \brief Função que extrai as informações de um dado método
*  \param *name Nome do método
*  \param *class_name Nome da classe que contém esse método
*  \param *descritor Descritor do método
*  \return Ponteiro para a estrutura que guarda as informações do método
*/
method_info *getMethod(char* name, char* class_name, char* descriptor);
/**
*  \brief Função que busca o vetor de variáveis estáticas
*  \param *class_name nome da classe
*  \return Ponteiro para o vetor de variáveis estáticas
*/
StaticAtrib * getstaticAtrib(char* class_name);
/**
*  \brief Função que conta o número de atributos estáticos
*  \param *class_name nome da classe
*  \return Número de atributos estáticos
*/
long getNAtribStatic (char *class_name);
/**
*  \brief Função que conta o número de atributos estáticos
*  \param *ptClass ponteiro para a classe
*  \return Número de atributos estáticos
*/
int CountStaticAtrib(ClassFile *ptClass);
/**
*  \brief Função que conta o número de atributos dinâmicos
*  \param *ptClass ponteiro para a classe
*  \return Número de atributos dinâmicos
*/
int CountAtrib(ClassFile *ptClass);
/**
*  \brief Função que procura o tipo do descritor
*  \param *descritor string do descritor
*  \return Número referente a esse descritor
*/
int TypeDescriptor (char *descriptor);
/**
*  \brief Função que cria um objeto
*  \param *cf Ponteiro para a classe
*  \return Ponteiro para o objeto
*/
Object * createObject(ClassFile * cf);
/**
*  \brief Função que procura um constant pool de um função
*  \param *name Nome do método
*  \param *class_name Nome da classe que contém esse método
*  \param *descritor Descritor do método
*  \return Ponteiro para o constant pool
*/
cp_info *getCpSuper(char* name, char* class_name, char* descriptor );

#endif
