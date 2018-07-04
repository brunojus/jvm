#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __CLOADER_H__

#define __CLOADER_H__

/*************Constant Pool*******************/
#define CLASS_INDEX 7
#define FIELDREF 9
#define METHODREF 10
#define INTERFACEMETHODREF 11
#define STRING 8
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define NAMEANDTYPE 12
#define UTF8  1
#define CONSTANTVALUE 5



/*******************attributes info******************/
#define CODE 1
#define EXCEPTIONSA 2
#define INNERCLASSES 3
#define OTHER 4


#define EXCEPTIONS "Exceptions"


#define REFERENCE_INTEGER 15
#define REFERENCE_STRING 16
#define REFERENCE_FLOAT 17
#define REFERENCE_LONG 18
#define REFERENCE_DOUBLE 19
#define REFERENCE_BOOLEAN 20
#define REFERENCE_BYTE 21
#define REFERENCE_SHORT 22
#define REFERENCE_CHAR 23
#define REFERENCE_REFERENCE 24

typedef unsigned char u1; /*Mudança de nome para condizer com a especificação java*/
typedef unsigned short u2;
typedef unsigned int u4;

/**
*  \brief Diretório de que contem as classes
*/
char dir_base[100];

/**
*  \brief Estrutura do constant pool
*/
typedef struct cp_info{
        u1 tag;
         union datacp{
        struct  {/*valor 7*/
               u2 name_index;
        }Class;
        struct  {/* valor 9*/
              u2 class_index;
              u2 name_and_type_index;
        }Fieldref ;

        struct {/*valor 12*/
            u2 name_index; 
            u2 descriptor_index;
        }NameAndType;
        struct{/* valor 1*/
            u2 length; 
            u1 *bytes;
        }Utf8;
        struct {/* valor 10*/
            u2 class_index; 
            u2 name_and_type_index;
        }Methodref;
        struct {/* valor 11*/
            u2 class_index; 
            u2 name_and_type_index;
        }InterfaceMethodref;
        struct {/* valor 8*/
            u2 string_index; 
        }String;
        struct {/*valor 3*/
            u4 bytes;
        }Integer;
        struct {/* valor 4*/
            u4 bytes;
        }Float;
        struct {/*valor 5*/
            u4 high_bytes;
            u4 low_bytes;
        }Long;
        struct {/*valor 5*/
            u4 high_bytes;
            u4 low_bytes;
        }Double;
    }data;
    
}cp_info;

typedef struct {
    u2  inner_class_info_index;
    u2  outer_class_info_index;
    u2  inner_name_index;
    u2  inner_class_access_flags;
} classtype_info;

/**
*  \brief Tabela de excesões
*/
typedef struct exception_table{
       u2 start_pc;/*Começo do try*/
          u2 end_pc; /*Fim do try*/
          u2  handler_pc; /*Ponteiro para o tratamento*/
          u2  catch_type;/*Tipo do catch*/
}exception_table;

/**
*  \brief Estrutura das informações dos atributos
*/
typedef struct attribute_info {
   u2 attribute_name_index;    /*Ponteiro para o nome do atributo*/
   u4 attribute_length;    /*Tamanho do atriburo*/
   union dataatt{
    struct ConstantValue_attribute {
            u2 constantvalue_index;
        }ConstantValue_attribute;    /*ponteiro para o constant pool caso seja um atribuo constante*/

    struct  {
            u2 max_stack;    /*Maximo de pilhas*/
            u2 max_locals;/*Maximo de variaveis locais*/
            u4 code_length;    /*Tamanho do codigo*/
            u1 *code;    /*O codigo propriamente dito*/
            u2 exception_table_length;    /*Tamanho da tabela de excesões*/
            struct exception_table *exception_table;    /*Ponteiro para a tabela de excessões*/
            u2 attributes_count;    /*Contagem de atributos*/
            struct attribute_info *attributes; /*Ponteiro para o vetor de variáveis */
          }Code_attribute;    /*Atributo de codigo*/
    struct  {
            u2 number_of_exceptions;    /*Numero de excessões*/
            u2 *exception_index_table;    /*indice da tabela de excessões*/
        }Exceptions_attribute;    /*Atributo de exceção*/

    struct {
            u2 number_of_classes;
            classtype_info* classes;
        }   InnerClasses;
        struct {
            u1* bytes;
        } Other;
   }data;
}attribute_info;

/**
*  \brief Escrutura para gernciar as informações dos campos
*/
typedef struct field_info{      
   u2 access_flags;    /*Flags de controle*/
   u2 name_index;    /*Indice para o nome do campo*/
   u2 descriptor_index;    /*Indice para o descritor*/
   u2 attributes_count;    /*contagem de atributos*/
   attribute_info *attributes;    /*vetor de atributos*/
}field_info;
/**
*  \brief Escrutura para gernciar as informações dos metodos
*/
typedef struct  method_info {      
    u2 access_flags;    /*Flags de controle*/
    u2 name_index;   /*Indice para o nome do campo*/
    u2 descriptor_index;    /*Indice para o descritor*/
    u2 attributes_count;    /*Quantidade de atributos*/
    attribute_info *attributes;    /*Vetor de atributos*/
} method_info ;
/**
*  \brief Escrutura da classe
*/
typedef struct ClassFile { 
    u4 magic;    /*Numero mágico*/
    u2 minor_version;    /*Menor versão aceitável*/
    u2 major_version;    /*Maior versão aceitável*/
    u2 constant_pool_count;    /*quantdade de entradas da constant pool*/
    cp_info *constant_pool;    /*Constant pool*/
    u2 access_flags;    /*Flags de acesso*/
    u2 this_class;    /*Referencia a propria classe*/
    u2 super_class;    /*Referencia a classe pai*/
    u2 interfaces_count;    /*Numero de interfaces*/
    u2 *interfaces;    /*Vetor de interfaces*/
    u2 fields_count;    /*Contagem de campos*/
    field_info *fields;    /*Vetor de campos*/
    u2 methods_count;    /*Contagem de métodos*/
    method_info *methods;    /*Vetor de métodos*/
    u2 attributes_count;    /*Contagem de atributos*/
    attribute_info *attributes;    /*Vetor de atributos*/
}ClassFile;//chamei cfile

/**
*  \brief Função que le um byte do arquivo
*  \param *fd endereço do arquivo
*  \return byte lido
*/
u1 u1Read(FILE *fd);
/**
*  \brief Função que le dois byte do arquivo
*  \param *fd endereço do arquivo
*  \return bytes lidos
*/
u2 u2Read(FILE *fd);
/**
*  \brief Função que le quatro byte do arquivo
*  \param *fd endereço do arquivo
*  \return bytes lidos
*/
u4 u4Read(FILE *fd);
/**
*  \brief Função que le o bytecode java e monta a estrutura da classe
*  \param *filename Endereço do arquivo
*  \return estrutura da classe montada
*/
ClassFile *read_class(char *filename);

#endif
