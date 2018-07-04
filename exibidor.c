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


/*Imprime os valores referente a constant pool, as tags definidas na tabela
foram definidos no exibidor.h */
void print_constantpool(ClassFile* cf, FILE* arq) {
    int i = 1;
    long long Long;
    fprintf(arq, "- CONSTANT POOL COUNT: %d\n", cf->constant_pool_count);
    fprintf(arq, "- CONSTANT_POOL:\n");
    cp_info* cp;
    for (cp = cf->constant_pool; cp < cf->constant_pool + cf->constant_pool_count ; ++cp) {
        fprintf(arq, "[%d]\n", i++);
        switch (cp->tag) {
          case CLASS_INDEX:
              fprintf(arq, " ---CP_INFO: CLASS\n");
              fprintf(arq, " ---NAME_INDEX: %d: %s\n", cp->data.Class.name_index, (char*)cf->constant_pool[cp->data.Class.name_index].data.Utf8.bytes);
              break;
          case FIELDREF:
              fprintf(arq, " ---CP_INFO: FIELDREF\n");
              fprintf(arq, " ---CLASS_INDEX: %d: %s\n", cp->data.Fieldref.class_index, (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.class_index].data.Class.name_index].data.Utf8.bytes);
              fprintf(arq, " ---NAMEANDTYPE_INDEX: %d: %s%s\n", cp->data.Fieldref.name_and_type_index, (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.name_and_type_index].data.NameAndType.name_index].data.Utf8.bytes, (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.name_and_type_index].data.NameAndType.descriptor_index].data.Utf8.bytes);
              break;
          case METHODREF:
              fprintf(arq, " ---CP_INFO: METHOD\n");
              fprintf(arq, " ---CLASS_INDEX: %d: %s\n", cp->data.Methodref.class_index, (char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.class_index].data.Class.name_index].data.Utf8.bytes);
              fprintf(arq, " ---NAMEANDTYPE_INDEX: %d: %s%s\n", cp->data.Methodref.name_and_type_index, (char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.name_and_type_index].data.NameAndType.name_index].data.Utf8.bytes, (char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.name_and_type_index].data.NameAndType.descriptor_index].data.Utf8.bytes);
              break;
          case INTERFACEMETHODREF:
              fprintf(arq, " ---CP_INFO: INTERFACE\n");
              fprintf(arq, " ---CLASS_INDEX: %d: %s\n", cp->data.InterfaceMethodref.class_index, (char*)cf->constant_pool[cf->constant_pool[cp->data.InterfaceMethodref.class_index].data.Class.name_index].data.Utf8.bytes);
              fprintf(arq, " ---NAMEANDTYPE_INDEX: %d: %s%s\n", cp->data.InterfaceMethodref.name_and_type_index, (char*)cf->constant_pool[cf->constant_pool[cp->data.InterfaceMethodref.name_and_type_index].data.NameAndType.name_index].data.Utf8.bytes, (char*)cf->constant_pool[cf->constant_pool[cp->data.InterfaceMethodref.name_and_type_index].data.NameAndType.descriptor_index ].data.Utf8.bytes);
              break;
          case NAMEANDTYPE:
              fprintf(arq, " ---CP_INFO: NAMEANDTYPE\n");
              fprintf(arq, " ---NAME_INDEX: %d: %s\n", cp->data.NameAndType.name_index, (char*)cf->constant_pool[cp->data.NameAndType.name_index].data.Utf8.bytes);
              fprintf(arq, " ---DESCRIPTOR_INDEX: %d: %s\n", cp->data.NameAndType.descriptor_index, (char*)cf->constant_pool[cp->data.NameAndType.descriptor_index].data.Utf8.bytes);
              break;
          case UTF8:
              fprintf(arq, " ---CP_INFO: UTF8\n");
              fprintf(arq, " ---LENGTH: %d\n", cp->data.Utf8.length);
              fprintf(arq, " ---VALUE: %s\n", (char*)cp->data.Utf8.bytes);
              break;
          case STRING:
              fprintf(arq, " ---CP_INFO: STRING\n");
              fprintf(arq, " ---STRING_INDEX: %d: %s\n", cp->data.String.string_index, (char*)cf->constant_pool[cp->data.String.string_index].data.Utf8.bytes);
              break;
          case INTEGER:
              fprintf(arq, " ---CP_INFO: INTEGER\n");
              fprintf(arq, " ---BYTES: %x\n", cp->data.Integer.bytes);
              fprintf(arq, " ---VALUE: %u\n", cp->data.Integer.bytes);
              break;
          case FLOAT:
              fprintf(arq, " ---CP_INFO: FLOAT\n");
              fprintf(arq, " ---BYTES: %x\n", cp->data.Float.bytes);
              u4tofloat.U4 = cp->data.Float.bytes;
              fprintf(arq, " ---VALUE: %f\n", u4tofloat.Float);
              break;
          case LONG:
              fprintf(arq, " ---CP_INFO: LONG\n");
              fprintf(arq, " ---HIGH: %x\n", cp->data.Long.high_bytes);
              fprintf(arq, " ---LOW: %x\n", cp->data.Long.low_bytes);
              Long = ((long long) cp->data.Long.high_bytes << 32) | (cp->data.Long.low_bytes);
              fprintf(arq, " ---VALUE: %lld\n", Long);
              break;
          case DOUBLE:
              fprintf(arq, " ---CP_INFO: DOUBLE\n");
              fprintf(arq, " ---HIGH: %x\n", cp->data.Double.high_bytes);
              fprintf(arq, " ---LOW: %x\n", cp->data.Double.low_bytes);
              Long = ((long long) cp->data.Double.high_bytes << 32) | (cp->data.Double.low_bytes);
              fprintf(arq, " ---VALUE: %lld\n", Long);
              break;
        }
    }

}

void print_interfaces(ClassFile* cf, FILE* arq) {
    fprintf(arq, "INTERFACES_COUNT: %d\n", cf->interfaces_count);
    fprintf(arq, "\n");
    fprintf(arq, "INTERFACES:\n");
    fprintf(arq, "\n");
    u2* interface_aux;
    for (interface_aux = cf->interfaces; interface_aux < cf->interfaces + cf->interfaces_count; ++interface_aux) {
        fprintf(arq, " ---INTERFACE: %d\n\n", *interface_aux);
    }
    if (!cf->interfaces_count) {
        fprintf(arq, "\n");
        return;
    }
}

void print_methodes(ClassFile* cf, FILE* arq) {
    int var1 = 0;
    int var2 = 0;

    fprintf(arq, "METHODS_COUNT: %d\n", cf->methods_count); // número de estruturas na tabela methods
    if (cf->methods_count == 0) {
        fprintf(arq, "\n");
        return;
    }
    fprintf(arq, "METHODS:\n");
    method_info* aux_meth;
    for (aux_meth = cf->methods; aux_meth < cf->methods + cf->methods_count; ++aux_meth) {
        fprintf(arq, "[%d]\n", var1++);
        fprintf(arq, "--- NAME_INDEX: %d: %s\n", aux_meth->name_index, (char*)cf->constant_pool[aux_meth->name_index].data.Utf8.bytes);
        fprintf(arq, "--- DESCRIPTOR_INDEX: %d: %s\n", aux_meth->descriptor_index, (char*)cf->constant_pool[aux_meth->descriptor_index].data.Utf8.bytes);
        fprintf(arq, "--- ACCESS_FLAGS: %x ", aux_meth->access_flags);
        print_flags(aux_meth->access_flags, arq);
        fprintf(arq, "\n");
        fprintf(arq, "--- ATTRIBUTE_COUNT: %d\n", aux_meth->attributes_count);
        attribute_info* aux_att;
        for (aux_att = aux_meth->attributes; aux_att < aux_meth->attributes + aux_meth->attributes_count; ++aux_att) {
            fprintf(arq, "--- [%d] METHOD_ATTRIBUTE:\n", var2++);
            print_atribute(cf, aux_att, arq);
        }
    }
}

void print_atributes(ClassFile* cf, FILE* arq) {
    int att_itera = 0;
    fprintf(arq, "ATTRIBUTES_COUNT: %d\n", cf->attributes_count);
    if (cf->attributes_count == 0) {
        fprintf(arq, "\n");
        return;
    }
    fprintf(arq, "ATTRIBUTES:\n");
    attribute_info* aux_att;
    for (aux_att = cf->attributes; aux_att < cf->attributes + cf->attributes_count; ++aux_att) {
        fprintf(arq, "[%d] ATTRIBUTE:\n", att_itera++);
        print_atribute(cf, aux_att, arq);
    }
}


void print_fields(ClassFile* cf, FILE* arq) {
    int var1 = 0;
    int var2 = 0;

    fprintf(arq, "FIELDS_COUNT: %d\n", cf->fields_count);
    if (cf->fields_count == 0) {
        fprintf(arq, "\n");
        return;
    }
    fprintf(arq, "FIELDS:\n");
    field_info* aux_field;
    for (aux_field = cf->fields; aux_field < cf->fields + cf->fields_count; ++aux_field) {
        fprintf(arq, "\t[%d]\n", var1++);
        fprintf(arq, "\tNAME_INDEX: %d: %s\n", aux_field->name_index, (char*)cf->constant_pool[aux_field->name_index ].data.Utf8.bytes);
        fprintf(arq, "\tDESCRIPTOR_INDEX: %d: %s\n", aux_field->descriptor_index, (char*)cf->constant_pool[aux_field->descriptor_index ].data.Utf8.bytes);
        fprintf(arq, "\tACCESS_FLAGS: %x ", aux_field->access_flags);
        print_flags(aux_field->access_flags, arq);
        fprintf(arq, "\n");
        fprintf(arq, "\tATTRIBUTE_COUNT: %d\n\n", aux_field->attributes_count);
        attribute_info* aux_att;
        for (aux_att = aux_field->attributes; aux_att < aux_field->attributes + aux_field->attributes_count; ++aux_att) {
            fprintf(arq, "[%d] FIELD_ATTRIBUTE:\n", var2++);
            print_atribute(cf, aux_att, arq);
        }
    }
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

void print_atribute(ClassFile* cf, attribute_info* att, FILE* arq) {

//Comeca do 4, https://cs.au.dk/~mis/dOvs/jvmspec/ref-newarray.html
char* newarray_value[] = {NULL, NULL, NULL, NULL, "T_BOOLEAN", "T_CHAR", "T_FLOAT", "T_DOUBLE", "T_BYTE", "T_SHORT","T_INT", "T_LONG"};
//10 instrucoes por linha
char* instruction_name[] = {
    "nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", "iconst_3", "iconst_4", "iconst_5", "lconst_0", //9
    "lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush", "ldc", "ldc_w",
    "ldc2_w", "iload", "lload", "fload","dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3",
    "lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", "dload_0", "dload_1",
    "dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", "iaload", "laload", "faload", "daload",
    "aaload", "baload", "caload", "saload", "istore", "lstore", "fstore", "dstore", "astore", "istore_0",
    "istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2",
    "fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", "astore_2", "astore_3", "iastore",
    "lastore", "fastore", "dastore", "aastore", "bastore", "castore", "sastore", "pop", "pop2", "dup",
    "dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd",
    "isub", "lsub", "fsub", "dsub", "imul", "lmul", "fmul", "dmul", "idiv", "ldiv", //109
    "fdiv", "ddiv", "irem", "lrem", "frem", "drem", "ineg", "lneg", "fneg", "dneg",
    "ishl", "lshl", "ishr", "lshr", "iushr", "lushr", "iand", "land", "ior", "lor",
    "ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", "l2d", "f2i",
    "f2l", "f2d", "d2i", "d2l", "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl",
    "fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt", "ifge","ifgt", "ifle", "if_icmpeq", //159
    "if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeq", "if_acmpne", "goto", "jsr", "ret",
    "tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", "dreturn", "areturn", "return", "getstatic", "putstatic",
    "getfield", "putfield", "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "invokedynamic", "new", "newarray", "anewarray",
    "arraylength", "athrow", "checkcast", "instanceof", "monitorenter", "monitorexit", "wide", "multianewarray", "ifnull", "ifnonnull",
    "goto_w", "jsr_w", "breakpoint", NULL, NULL, NULL, NULL, NULL, NULL, NULL, //209
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, "impdep1", "impdep2" //255
};
//10 instrucoes por linha
enum instrucoes_code {
    nop, aconst_null, iconst_m1, iconst_0, iconst_1, iconst_2, iconst_3, iconst_4, iconst_5, lconst_0, //9
    lconst_1, fconst_0, fconst_1, fconst_2, dconst_0, dconst_1, bipush, sipush, ldc, ldc_w,
    ldc2_w, iload, lload, fload,dload, aload, iload_0, iload_1, iload_2, iload_3,
    lload_0, lload_1, lload_2, lload_3, fload_0, fload_1, fload_2, fload_3, dload_0, dload_1,
    dload_2, dload_3, aload_0, aload_1, aload_2, aload_3, iaload, laload, faload, daload,//59
    aaload, baload, caload, saload, istore, lstore, fstore, dstore, astore, istore_0,
    istore_1, istore_2, istore_3, lstore_0, lstore_1, lstore_2, lstore_3, fstore_0, fstore_1, fstore_2,
    fstore_3, dstore_0, dstore_1, dstore_2, dstore_3, astore_0, astore_1, astore_2, astore_3, iastore,
    lastore, fastore, dastore, aastore, bastore, castore, sastore, pop, pop2, dup,
    dup_x1, dup_x2, dup2, dup2_x1, dup2_x2, swap, iadd, ladd, fadd, dadd,
    isub, lsub, fsub, dsub, imul, lmul, fmul, dmul, idiv, ldiv, //109
    fdiv, ddiv, irem, lrem, frem, drem, ineg, lneg, fneg, dneg,
    ishl, lshl, ishr, lshr, iushr, lushr, iand, land, ior, lor,
    ixor, lxor, iinc, i2l, i2f, i2d, l2i, l2f, l2d, f2i,
    f2l, f2d, d2i, d2l, d2f, i2b, i2c, i2s, lcmp, fcmpl,
    fcmpg, dcmpl, dcmpg, ifeq, ifne, iflt, ifge,ifgt, ifle, if_icmpeq, //150 ao 159
    if_icmpne, if_icmplt, if_icmpge, if_icmpgt, if_icmple, if_acmpeq, if_acmpne, goto2, jsr, ret,
    tableswitch, lookupswitch, ireturn, lreturn, freturn, dreturn, areturn, return2, getstatic, putstatic,
    getfield, putfield, invokevirtual, invokespecial, invokestatic, invokeinterface, invokedynamic, new, newarray, anewarray,
    arraylength, athrow, checkcast, instanceof, monitorenter, monitorexit, wide, multianewarray, ifnull, ifnonnull,
    goto_w, jsr_w, breakpoint,  //200 ao 203
    impdep1 = 254, impdep2 = 255
};

    long long Long;
    char* type;
    type = (char*)malloc(sizeof(char) * cf->constant_pool[att->attribute_name_index ].data.Utf8.length+1);
    strcpy(type, (char*)cf->constant_pool[att->attribute_name_index ].data.Utf8.bytes);
    int i = return_type(type);
    fprintf(arq, "\tATTRIBUTE_NAME_INDEX: %d : %s\n", att->attribute_name_index, (char*)cf->constant_pool[att->attribute_name_index ].data.Utf8.bytes);
    fprintf(arq, "\tATTRIBUTE_LENGTH: %u\n\n", att->attribute_length);
    switch (i) {
    case CONSTANTVALUE:
        fprintf(arq, "\tTYPE: CONSTANT_VALUE\n");
        fprintf(arq, "\tCONSTANTVALUE_INDEX: %d\n\n", att->data.ConstantValue_attribute.constantvalue_index);
        switch (cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].tag) {
        case INTEGER:
            fprintf(arq, "\tCP_INFO: INTEGER\n");
            fprintf(arq, "\tBYTES: %x\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Integer.bytes);
            fprintf(arq, "\tVALUE: %u\n\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Integer.bytes);
            break;
        case FLOAT:
            fprintf(arq, "\tCP_INFO: FLOAT\n");
            fprintf(arq, "\tBYTES: %x\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Float.bytes);
            fprintf(arq, "\tVALUE: %lf\n\n", (float *)cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index].data.Float.bytes);
            break;
        case LONG:
            fprintf(arq, "\tCP_INFO: LONG\n");
            fprintf(arq, "\tHIGH: %x\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Long.high_bytes);
            fprintf(arq, "\tLOW: %x\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Long.low_bytes);
            Long = ((long long) cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index  ].data.Long.high_bytes << 32) | (cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Long.low_bytes);
            fprintf(arq, "\tVALUE: %lld\n\n", Long);
            break;
        case DOUBLE:
            fprintf(arq, "\tCP_INFO: DOUBLE\n");
            fprintf(arq, "\tHIGH: %x\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index  ].data.Double.high_bytes);
            fprintf(arq, "\tLOW: %x\n", cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index  ].data.Double.low_bytes);
            Long = ((long long) cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index  ].data.Double.high_bytes << 32) | (cf->constant_pool[att->data.ConstantValue_attribute.constantvalue_index ].data.Double.low_bytes);
            fprintf(arq, "\tVALUE: %lld\n\n", Long);
            break;
        }
        break;
    case CODE:
        fprintf(arq, "\tTYPE: CODE\n");
        fprintf(arq, "\tMAX_STACK: %d\n", att->data.Code_attribute.max_stack);
        fprintf(arq, "\tMAX_LOCALS: %d\n", att->data.Code_attribute.max_locals);
        fprintf(arq, "\tCODE_LENGTH: %u\n", att->data.Code_attribute.code_length);
        fprintf(arq, "\tCODE:\n");
        u1* code;
        cp_info* cp;
        for (code = att->data.Code_attribute.code; code < att->data.Code_attribute.code + att->data.Code_attribute.code_length; ++code) {
            fprintf(arq, "\t\t%d | ", (int) (code - (att->data.Code_attribute.code))); //printa a instrucao sem o codigo em hexa

            fprintf(arq, "%s ", instruction_name[*code]); //printa a instrucao
            u1 u1_aux;
            u2 u2_aux;
            u4 u4_aux;

            switch (*code) {
                case aload:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case anewarray:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case astore:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case bipush:
                    fprintf(arq, "%d", *(++code)); //byte
                    break;
                case checkcast:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case dload:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case dstore:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case fload:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case fstore:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case getfield:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    cp = cf->constant_pool +  u2_aux ;
                    fprintf(arq, "#%d <%s.%s>", u2_aux,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.class_index ].data.Class.name_index ].data.Utf8.bytes,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.name_and_type_index ].data.NameAndType.name_index ].data.Utf8.bytes);
                    break;
                case getstatic:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case goto2: //REVER - MOSTRANDO VALOR INESPERADO
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case goto_w:
                    u4_aux = *(++code); //byte1 de branch
                    u4_aux = u4_aux << 8; //shift de branch
                    u4_aux += *(++code); //byte2 de branch
                    u4_aux = u4_aux << 8; //shift de branch
                    u4_aux += *(++code); //byte3 de branch
                    u4_aux = u4_aux << 8; //shift de branch
                    u4_aux += *(++code); //byte4 de branch
                    fprintf(arq, "%d", u4_aux); //print branchbyte

                    break;
                case if_acmpeq:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_acmpne:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_icmple:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_icmpgt:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_icmpge:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_icmplt:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_icmpne:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case if_icmpeq:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifeq:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifne:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifgt:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case iflt:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifle:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifge:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifnonnull:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case ifnull:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case iinc:
                    u1_aux = *(++code); //byte de index
                    fprintf(arq, "%d by %d", u1_aux, *(++code)); //print branchbyte
                    break;
                case iload:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case instanceof:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case invokedynamic:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    ++code; //leitura de 0 - caracteristica do invokedynamic
                    ++code; //leitura de 0 - caracteristica do invokedynamic
                    break;
                case invokeinterface:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    fprintf(arq, " count %d", *(++code)); //count
                    ++code; //leitura de 0 - caracteristica do invokedynamic
                    break;
                case invokespecial:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    cp = cf->constant_pool + u2_aux ;
                    fprintf(arq, "#%d <%s.%s>", u2_aux,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.class_index ].data.Class.name_index ].data.Utf8.bytes,
						(char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.name_and_type_index ].data.NameAndType.name_index ].data.Utf8.bytes);
                    break;
                case invokestatic:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case invokevirtual:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    cp = cf->constant_pool + u2_aux ;
                    fprintf(arq, "#%d <%s.%s>", u2_aux,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.class_index ].data.Class.name_index ].data.Utf8.bytes,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Methodref.name_and_type_index ].data.NameAndType.name_index ].data.Utf8.bytes);
                    break;
                case istore:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case jsr:
                    u2_aux = *(++code); //byte1 de branch
                    u2_aux = u2_aux << 8; //shift de branch
                    u2_aux += *(++code); //byte2 de branch
                    fprintf(arq, "%d", u2_aux); //print branchbyte
                    break;
                case jsr_w:
                    u4_aux = *(++code); //byte1 de branch
                    u4_aux = u4_aux << 8; //shift de branch
                    u4_aux += *(++code); //byte2 de branch
                    u4_aux = u4_aux << 8; //shift de branch
                    u4_aux += *(++code); //byte3 de branch
                    u4_aux = u4_aux << 8; //shift de branch
                    u4_aux += *(++code); //byte4 de branch
                    fprintf(arq, "%d", u4_aux); //print branchbyte
                    break;
                case ldc:
                    u1_aux = *(++code); //index
                    cp = cf->constant_pool + u2_aux ;
                    fprintf(arq, "#%d", u2_aux); //CONTEUDO PODE SER STRING, FLOAT...
                    break;
                case ldc_w:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case ldc2_w:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case lload:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case lstore:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case multianewarray:
                    u2_aux = *(++code); //byte1 de index
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    fprintf(arq, " dim %d", *(++code)); //dimensions
                    break;
                case new:
                    u2_aux = *(++code);
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    cp = cf->constant_pool +  u2_aux ;
                    fprintf(arq, "#%d, <%s>", u2_aux, (char*)cf->constant_pool[cp->data.Class.name_index ].data.Utf8.bytes);
                    break;
                case newarray:
                    fprintf(arq, "%s", newarray_value[*(++code)]);
                    break;
                case putfield:
                    u2_aux = *(++code);
                    u2_aux = u2_aux << 8;
                    u2_aux += *(++code);

                    cp = cf->constant_pool +  u2_aux ;
                    fprintf(arq, "#%d <%s.%s>", u2_aux,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.class_index ].data.Class.name_index ].data.Utf8.bytes,
                        (char*)cf->constant_pool[cf->constant_pool[cp->data.Fieldref.name_and_type_index ].data.NameAndType.name_index ].data.Utf8.bytes);
                    break;
                case putstatic:
                    u2_aux = *(++code);
                    u2_aux = u2_aux << 8; //shift de index
                    u2_aux += *(++code); //byte2 de index
                    fprintf(arq, "#%d", u2_aux); //print indexbyte
                    break;
                case ret:
                    fprintf(arq, "#%d", *(++code)); //index
                    break;
                case sipush:
                    u2_aux = *(++code); //byte1
                        u2_aux = u2_aux << 8; //shift
                        u2_aux += *(++code); //byte2
                        fprintf(arq, "%d", u2_aux); //print
                    break;
                case wide:
                    if ((*(++code)) == iinc) { //caso o proximo byte seja iinc
                        u2_aux = *(++code);
                        u2_aux = u2_aux << 8; //shift de index
                        u2_aux += *(++code); //byte2 de index
                        fprintf(arq, "#%d", u2_aux); //print indexbyte

                        u2_aux = *(++code); //byte1 de constante
                        u2_aux = u2_aux << 8; //shift de constante
                        u2_aux += *(++code); //byte2 de constante
                        fprintf(arq, " const %d", u2_aux); //print constante
                    }
                    else {
                        u2_aux = *(++code); //byte1 de index
                        u2_aux = u2_aux << 8; //shift de index
                        u2_aux += *(++code); //byte2 de index
                        fprintf(arq, "#%d", u2_aux); //print indexbyte
                    }
                    break;

                //TODO:
                case lookupswitch:
                    break;
                //TODO:
                case tableswitch: //REVER - ESTUDAR SOBRE
                    break;
            }


            fprintf(arq, "\n");
        }
        fprintf(arq, "--- EXCEPTION_TABLE_LENGTH: %d\n", att->data.Code_attribute.exception_table_length);
        exception_table *exp_aux;
        for (exp_aux = att->data.Code_attribute.exception_table; exp_aux < att->data.Code_attribute.exception_table + att->data.Code_attribute.exception_table_length; ++exp_aux) {
            fprintf(arq, "--- EXCEPTION:\n");
            fprintf(arq, "\t--- START_PC: %d\n", exp_aux->start_pc);
            fprintf(arq, "\t--- END_PC: %d\n", exp_aux->end_pc);
            fprintf(arq, "\t--- HANDLER_PC: %d\n", exp_aux->handler_pc);
            fprintf(arq, "\t--- CATCH_TYPE: %d\n", exp_aux->catch_type);
        }
        fprintf(arq, "--- ATTRIBUTES_COUNT: %d\n", att->data.Code_attribute.attributes_count);
        attribute_info* aux_att;
        for (aux_att = att->data.Code_attribute.attributes; aux_att < att->data.Code_attribute.attributes + att->data.Code_attribute.attributes_count; ++aux_att) {
            print_atribute(cf, aux_att, arq);
        }
        break;
    case EXCEPTIONS:
        fprintf(arq, "--- TYPE: EXCEPTIONS\n");
        fprintf(arq, "--- NUMBER_OF_EXCEPTIONS: %d\n", att->data.Exceptions_attribute.number_of_exceptions);
        u2* expt_aux;
        for (expt_aux = att->data.Exceptions_attribute.exception_index_table; expt_aux < att->data.Exceptions_attribute.exception_index_table + att->data.Exceptions_attribute.number_of_exceptions; ++expt_aux) {
            fprintf(arq, "--- EXCEPTION:\n");
            fprintf(arq, "\t--- CLASS: %d\n", *expt_aux);
        }
        break;
    case INNERCLASSES:
        fprintf(arq, "--- TYPE: INNER CLASSES:\n");
        fprintf(arq, "--- NUMBER_OF_CLASSES: %d\n", att->data.InnerClasses.number_of_classes);
        classtype_info* classtype_aux;
        for (classtype_aux = att->data.InnerClasses.classes; classtype_aux < att->data.InnerClasses.classes + att->data.InnerClasses.number_of_classes; ++classtype_aux) {
            fprintf(arq, "--- INNER CLASS:\n");
            fprintf(arq, "\t--- INNER CLASS: %d\n", classtype_aux->inner_class_info_index);
            fprintf(arq, "\t--- OUTER CLASS: %d\n", classtype_aux->outer_class_info_index);
            fprintf(arq, "\t--- INNER NAME: %d\n", classtype_aux->inner_name_index);
            fprintf(arq, "\t--- INNER CLASS ACCESS FLAGS: %x ", classtype_aux->inner_class_access_flags);
            print_flags(classtype_aux->inner_class_access_flags, arq);
            fprintf(arq, "\n\n");
            fprintf(arq, "\n");
        }
        break;
    case OTHER:
        break;
    }
    free(type);
}
