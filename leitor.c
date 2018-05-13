#include "leitor.h"
#include "helper.h"

void load_magic(ClassFile* cf, FILE* fd) {
    cf->magic = u4Read(fd);
    /*if (cf->magic != 0xcafebabe)
        EXIT; //arquivo não eh .class
    */
}

void load_versions(ClassFile* cf, FILE* fd) {
    cf->minor_version = u2Read(fd);
    cf->major_version = u2Read(fd);
}

void load_constantpool(ClassFile* cf, FILE* fd) {
    cf->constant_pool_count = u2Read(fd);
    if (cf->constant_pool_count <= 1) {
        cf->constant_pool = NULL;
        return;
    }
    cf->constant_pool = (cp_info*) calloc((cf->constant_pool_count - 1), sizeof(cp_info));
    cp_info *cp;
    for (cp = cf->constant_pool; cp < cf->constant_pool + cf->constant_pool_count - 1; ++cp) {
        cp->tag = u1Read(fd);
        switch (cp->tag) {
        case CLASS:
            cp->info.Class_info.name_index = u2Read(fd);
            break;
        case FIELDREF:
            cp->info.Fieldref_info.class_index = u2Read(fd);
            cp->info.Fieldref_info.name_and_type_index = u2Read(fd);
            break;
        case METHOD:
            cp->info.Method_info.class_index = u2Read(fd);
            cp->info.Method_info.name_and_type_index = u2Read(fd);
            break;
        case INTERFACE:
            cp->info.Interface_info.class_index = u2Read(fd);
            cp->info.Interface_info.name_and_type_index = u2Read(fd);
            break;
        case NAMEANDTYPE:
            cp->info.NameAndType_info.name_index = u2Read(fd);
            cp->info.NameAndType_info.descriptor_index = u2Read(fd);
            break;
        case UTF8:
            cp->info.Utf8_info.length = u2Read(fd);
            cp->info.Utf8_info.bytes = (u1*)calloc(cp->info.Utf8_info.length+1, sizeof(u1)); //length diz o numero de bytes UTF8 desse cp_info
            u1* b;
            for (b = cp->info.Utf8_info.bytes ; b < cp->info.Utf8_info.bytes + cp->info.Utf8_info.length ; ++b) { //laco para leitura desses bytes
                *b = u1Read(fd);
            }
            break;
        case STRING:
            cp->info.String_info.string_index = u2Read(fd);
            break;
        case INTEGER:
            cp->info.Integer_info.bytes = u4Read(fd);
            break;
        case FLOAT:
            cp->info.Float_info.bytes = u4Read(fd);
            break;
        case LONG:
            cp->info.Long_info.high_bytes = u4Read(fd); //estrutura de 64 bytes
            cp->info.Long_info.low_bytes = u4Read(fd);
            break;
        case DOUBLE:
            cp->info.Double_info.high_bytes = u4Read(fd); //estrutura de 64 bytes
            cp->info.Double_info.low_bytes = u4Read(fd);
            break;
        }
        if (cp->tag == LONG || cp->tag == DOUBLE) {
            ++cp;
            cp->tag = -1;
        }
    }
}

void load_classdata(ClassFile* cf, FILE* fd) {
    cf->access_flags = u2Read(fd);
    cf->this_class = u2Read(fd);
    cf->super_class = u2Read(fd);
}

void load_interfaces(ClassFile* cf, FILE* fd) {
    cf->interfaces_count = u2Read(fd);
    if (cf->interfaces_count == 0) {
        cf->interfaces = NULL;
        return;
    }
    cf->interfaces = (u2*) calloc(cf->interfaces_count, sizeof(u2));
    u2* bytes;
    for (bytes = cf->interfaces; bytes < cf->interfaces + cf->interfaces_count; ++bytes) {
        *bytes = u2Read(fd);
    }
}

void load_constantvalue_attr(attribute_info* att, FILE* fd) {
    att->type.ConstantValue.constantvalue_index = u2Read(fd);
}

void load_code_attr(attribute_info* att, ClassFile* cf, FILE* fd) {
    att->type.Code_attribute.max_stack = u2Read(fd);
    att->type.Code_attribute.max_locals = u2Read(fd);
    att->type.Code_attribute.code_length = u4Read(fd);
    if (att->type.Code_attribute.code_length == 0) {
        att->type.Code_attribute.code = NULL;
    } else {
        att->type.Code_attribute.code = (u1*)calloc(att->type.Code_attribute.code_length, sizeof(u1));
        u1* byte;
        for (byte = att->type.Code_attribute.code; byte < att->type.Code_attribute.code + att->type.Code_attribute.code_length; ++byte) {
            *byte = u1Read(fd);
        }
    }
    att->type.Code_attribute.exception_table_length = u2Read(fd);
    if (att->type.Code_attribute.exception_table_length == 0) {
        att->type.Code_attribute.exception_table = NULL;
    } else {
        att->type.Code_attribute.exception_table = (exception_table_info*)calloc(att->type.Code_attribute.exception_table_length,sizeof(exception_table_info));
        exception_table_info* exp_aux;
        for (exp_aux = att->type.Code_attribute.exception_table; exp_aux < att->type.Code_attribute.exception_table + att->type.Code_attribute.exception_table_length; ++exp_aux) {
            exp_aux->start_pc = u2Read(fd);
            exp_aux->end_pc = u2Read(fd);
            exp_aux->handler_pc = u2Read(fd);
            exp_aux->catch_type = u2Read(fd);
        }
    }
    att->type.Code_attribute.attributes_count = u2Read(fd);
    if (att->type.Code_attribute.attributes_count == 0) {
        att->type.Code_attribute.attributes = NULL;
    } else {
        att->type.Code_attribute.attributes = (attribute_info*)calloc(att->type.Code_attribute.attributes_count,sizeof(attribute_info));
        attribute_info* att_aux;
        for (att_aux = att->type.Code_attribute.attributes; att_aux < att->type.Code_attribute.attributes + att->type.Code_attribute.attributes_count; ++att_aux) {
            load_attribute(att_aux, cf, fd);
        }
    }
}

void load_exceptions_attr(attribute_info* att, FILE* fd) {
    att->type.Exceptions.number_of_exceptions = u2Read(fd);
    if (att->type.Exceptions.number_of_exceptions == 0) {
        att->type.Exceptions.exception_index_table = NULL;
    } else {
        att->type.Exceptions.exception_index_table = (u2*) calloc(att->type.Exceptions.number_of_exceptions,sizeof(u2));
        u2* bytes;
        for (bytes = att->type.Exceptions.exception_index_table; bytes < att->type.Exceptions.exception_index_table + att->type.Exceptions.number_of_exceptions; ++bytes) {
            *bytes = u2Read(fd);
        }
    }
}

void load_innerclasses_attr(attribute_info* att, FILE* fd) {
    att->type.InnerClasses.number_of_classes = u2Read(fd);
    if (att->type.InnerClasses.number_of_classes == 0) {
        att->type.InnerClasses.classes = NULL;
        return;
    }
    att->type.InnerClasses.classes = (classtype_info*) calloc(att->type.InnerClasses.number_of_classes,sizeof(classtype_info));
    classtype_info* classtype_aux;
    for (classtype_aux = att->type.InnerClasses.classes; classtype_aux < att->type.InnerClasses.classes + att->type.InnerClasses.number_of_classes; ++classtype_aux) {
        classtype_aux->inner_class_info_index = u2Read(fd);
        classtype_aux->outer_class_info_index = u2Read(fd);
        classtype_aux->inner_name_index = u2Read(fd);
        classtype_aux->inner_class_access_flags = u2Read(fd);
    }
}

void load_other_attr(attribute_info* att, FILE* fd) {
    if (att->attribute_length == 0) {
        att->type.Other.bytes = NULL;
        return;
    }
    att->type.Other.bytes = (u1*) calloc(att->attribute_length,sizeof(u1));
    u1* bytes;
    for (bytes = att->type.Other.bytes; bytes < att->type.Other.bytes + att->attribute_length; ++bytes) {
        *bytes = u1Read(fd);
    }
}

void load_attribute(attribute_info* att, ClassFile* cf, FILE* fd) {
    char* type;
    att->attribute_name_index = u2Read(fd);
    att->attribute_length = u4Read(fd);
    type = (char*)calloc(cf->constant_pool[att->attribute_name_index - 1].info.Utf8_info.length+1,sizeof(char));
      strcpy(type, (char*)cf->constant_pool[att->attribute_name_index - 1].info.Utf8_info.bytes);
      int i = findtype(type);
      switch (i) {
      case CONSTANTVALUE:
          load_constantvalue_attr(att, fd);
          break;
      case CODE:
          load_code_attr(att, cf, fd);
          break;
      case EXCEPTIONS:
          load_exceptions_attr(att, fd);
          break;
      case INNERCLASSES:
          load_innerclasses_attr(att, fd);
          break;
      case OTHER:
          load_other_attr(att, fd);
          break;
      }
      free(type);
  }

  void load_fields(ClassFile* cf, FILE* fd) {
// carrega os fields. Dois campos na mesma classe não podem ter o mesmo nome.
    
      cf->fields_count = u2Read(fd);

      if (cf->fields_count == 0) {
          cf->fields = NULL;
          return;
      }
      cf->fields = (field_info*)calloc(cf->fields_count,sizeof(field_info));
      field_info* aux_field;
      for (aux_field = cf->fields; aux_field < cf->fields + cf->fields_count; ++aux_field) {
          aux_field->access_flags = u2Read(fd);
          aux_field->name_index = u2Read(fd);
          aux_field->descriptor_index = u2Read(fd);
          aux_field->attributes_count = u2Read(fd);
          aux_field->attributes = calloc(aux_field->attributes_count,sizeof(attribute_info));
          attribute_info* aux_attribute;
          for (aux_attribute = aux_field->attributes; aux_attribute < aux_field->attributes + aux_field->attributes_count; ++aux_attribute) {
              load_attribute(aux_attribute, cf, fd);
          }
      }
  }

  void load_methods(ClassFile* cf, FILE* fd) {
    // carrega os métodos
      cf->method_count = u2Read(fd);
      if (cf->method_count == 0) {
          cf->methods = NULL;
          return;
      }
      cf->methods = (method_info*) calloc(cf->method_count, sizeof(method_info));
      method_info* aux_method;
      for (aux_method = cf->methods; aux_method < cf->methods + cf->method_count; ++aux_method) {
          aux_method->access_flags = u2Read(fd);
          aux_method->name_index = u2Read(fd);
          aux_method->descriptor_index = u2Read(fd);
          aux_method->attributes_count = u2Read(fd);
          aux_method->attributes = (attribute_info*) calloc(aux_method->attributes_count, sizeof(attribute_info));
          attribute_info* att_aux;
          for (att_aux = aux_method->attributes; att_aux < aux_method->attributes + aux_method->attributes_count; ++att_aux) {
              load_attribute(att_aux, cf, fd);
          }
      }
  }

  void load_attributes(ClassFile* cf, FILE* fd) {
      cf->attributes_count = u2Read(fd);
      if (cf->attributes_count == 0) {
          cf->attributes = NULL;
          return;
      }
      cf->attributes = (attribute_info*) calloc(cf->attributes_count, sizeof(attribute_info));
      attribute_info* att_aux;
      for (att_aux = cf->attributes; att_aux < cf->attributes + cf->attributes_count; ++att_aux) {
          load_attribute(att_aux, cf, fd);
      }
  }

  ClassFile* readClass(FILE* fd) {
      ClassFile* cf = (ClassFile*) calloc(1,sizeof(ClassFile));
      load_magic(cf, fd);
      load_versions(cf, fd);
      load_constantpool(cf, fd);
      load_classdata(cf, fd);
      load_interfaces(cf, fd);
      load_fields(cf, fd);
      load_methods(cf, fd);
      load_attributes(cf, fd);
      return cf;
}
