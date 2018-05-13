#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "leitor.h"

int is_true(int code, int id);
void print_permissions(int code,FILE* arq);
void print_magic(ClassFile* cf,FILE* arq);
void print_versions(ClassFile* cf,FILE* arq);
void print_constantpool(ClassFile* cf,FILE* arq);
void print_classdata(ClassFile* cf,FILE* arq);
void print_interfaces(ClassFile* cf,FILE* arq);
void print_attribute(ClassFile* cf, attribute_info* att,FILE* arq);
void print_fields(ClassFile* cf,FILE* arq);
void print_methods(ClassFile* cf,FILE* arq);
void print_attributes(ClassFile* cf,FILE* arq);
void print_class(ClassFile* cf,char* namefile,FILE* arq);
char* show_version(int code);