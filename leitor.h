#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#ifndef LEITOR_H
#define LEITOR_H

#define CONTINUED 0
#define CLASS 7
#define FIELDREF 9
#define METHOD 10
#define INTERFACE 11
#define NAMEANDTYPE 12
#define UTF8 1
#define STRING 8
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define CONSTANTVALUE 5
#define CODE 1
#define EXCEPTIONS 2
#define INNERCLASSES 3
#define OTHER 4

typedef uint8_t     u1;
typedef uint16_t    u2;
typedef uint32_t    u4;

union {
    u4 U4;
    float Float;
} u4tofloat;

union {
    long Long;
    double Double;
} longtodouble;



typedef struct {
    u2  inner_class_info_index;
    u2  outer_class_info_index;
    u2  inner_name_index;
    u2  inner_class_access_flags;
} classtype_info;


typedef struct {
    u2  start_pc;
    u2  end_pc;
    u2  handler_pc;
    u2  catch_type;
}   exception_table_info;


typedef struct _attribute_info {
    u2  attribute_name_index;
    u4  attribute_length;
    union {
        struct {
            u2 constantvalue_index;
        }   ConstantValue;
        struct {
            u2                      max_stack;
            u2                      max_locals;
            u4                      code_length;
            u1*                     code;
            u2                      exception_table_length;
            exception_table_info*   exception_table;
            u2  attributes_count;
            struct _attribute_info* attributes;
        }   Code_attribute;
        struct {
            u2  number_of_exceptions;
            u2* exception_index_table;
        }   Exceptions;
        struct {
            u2              number_of_classes;
            classtype_info* classes;
        }   InnerClasses;
        struct {
            u1* bytes;
        } Other;
    }   type;
}   attribute_info;



typedef struct {
    u2              access_flags;
    u2              name_index;
    u2              descriptor_index;
    u2              attributes_count;
    attribute_info* attributes;
}   field_info, method_info;


typedef struct {
    u1  tag;
    union {
        struct {
            u2  name_index;
        }   Class_info;
        struct {
            u2  class_index;
            u2  name_and_type_index;
        }   Fieldref_info, Method_info,   Interface_info;
        struct {
            u2  name_index;
            u2  descriptor_index;
        }   NameAndType_info;
        struct {
            u2  length;
            u1* bytes;
        }   Utf8_info;
        struct {
            u2  string_index;
        }   String_info;
        struct {
            u4  bytes;
        }   Integer_info;
        struct {
            u4  bytes;
        }   Float_info;
        struct {
            u4  high_bytes;
            u4  low_bytes;
        }   Long_info, Double_info;
    }   info;
}   cp_info;



typedef struct {
    u4              magic;
    u2              minor_version;
    u2              major_version;
    u2              constant_pool_count;
    cp_info*        constant_pool;
    u2              access_flags;
    u2              this_class;
    u2              super_class;
    u2              interfaces_count;
    u2*             interfaces;
    u2              fields_count;
    field_info*     fields;
    u2              method_count;
    method_info*    methods;
    u2              attributes_count;
    attribute_info* attributes;
}   ClassFile;

void load_magic(ClassFile* cf,FILE* fd);
void load_versions(ClassFile* cf,FILE* fd);
void load_constantpool(ClassFile* cf,FILE* fd);
void load_classdata(ClassFile* cf,FILE* fd);
void load_interfaces(ClassFile* cf,FILE* fd);
void load_constantvalue_attr(attribute_info* att, FILE* fd);
void load_code_attr(attribute_info* att, ClassFile* cf,FILE* fd);
void load_exceptions_attr(attribute_info* att,FILE* fd);
void load_innerclasses_attr(attribute_info* att,FILE* fd);
void load_other_attr(attribute_info* att, FILE* fd);
void load_fields(ClassFile* cf,FILE* fd);
void load_attributes(ClassFile* cf, FILE* fd);
void load_methods(ClassFile* cf,FILE* fd);
void load_attribute(attribute_info* att,ClassFile* cf,FILE* fd);
ClassFile* readClass(FILE* fd);
#endif
