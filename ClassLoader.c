#include "ClassLoader.h"

u1 u1Read(FILE *fd) {
  u1 toReturn = getc(fd);

  return toReturn;
}

u2 u2Read(FILE *fd) {
  u2 toReturn = getc(fd);

  toReturn = (toReturn << 8) | (getc(fd));
  return toReturn;
}

u4 u4Read(FILE *fd) {
  u4 toReturn = getc(fd);
  toReturn = (toReturn << 8) | (getc(fd));
  toReturn = (toReturn << 8) | (getc(fd));
  toReturn = (toReturn << 8) | (getc(fd));
  return toReturn;
}
/**
*   Funcao que le as informacoes dos atributos no bytecode
*   count Numero de atributos
*   *cp Ponteiro para o constant pool
*   *ptrClass Ponteiro para o arquivo
*   ptrAttributes ponteiro para vetor de atributos
*/
attribute_info* read_attributes_info ( u2 count, cp_info *cp,  FILE *ptrClass){
    int i,j;
    u1 *lixo;    /*Nao usamos(E liberado)*/
    attribute_info * ptrAttributes = (attribute_info *) malloc(count*sizeof(attribute_info));
    for (i=0;i<count;i++){
        ptrAttributes[i].attribute_name_index = u2Read(ptrClass);
        ptrAttributes[i].attribute_length = u4Read(ptrClass);

        if (strcmp((char *)cp[ptrAttributes[i].attribute_name_index].data.Utf8.bytes,"ConstantValue")==0){

            ptrAttributes[i].data.ConstantValue_attribute.constantvalue_index = u2Read(ptrClass);
        }else if (strcmp((char *)cp[ptrAttributes[i].attribute_name_index].data.Utf8.bytes,"Code")==0){

            ptrAttributes[i].data.Code_attribute.max_stack = u2Read(ptrClass);
            ptrAttributes[i].data.Code_attribute.max_locals = u2Read(ptrClass);
            ptrAttributes[i].data.Code_attribute.code_length = u4Read(ptrClass);

            ptrAttributes[i].data.Code_attribute.code = (u1 *)malloc(ptrAttributes[i].data.Code_attribute.code_length*sizeof(u1));
            fread(ptrAttributes[i].data.Code_attribute.code,sizeof(u1),ptrAttributes[i].data.Code_attribute.code_length,ptrClass);
            ptrAttributes[i].data.Code_attribute.exception_table_length = u2Read(ptrClass);
            ptrAttributes[i].data.Code_attribute.exception_table =
		(struct exception_table*)malloc(ptrAttributes[i].data.Code_attribute.exception_table_length* sizeof(struct exception_table));

            for (j=0;j<ptrAttributes[i].data.Code_attribute.exception_table_length;j++){

            /*esta JVM nao implementa excessoes*/
		      u2Read(ptrClass);
		      u2Read(ptrClass);
              u2Read(ptrClass);
		      u2Read(ptrClass);
            }
            ptrAttributes[i].data.Code_attribute.attributes_count = u2Read(ptrClass);
            ptrAttributes[i].data.Code_attribute.attributes = read_attributes_info(ptrAttributes[i].data.Code_attribute.attributes_count, cp, ptrClass);
        }else if (strcmp((char *)cp[ptrAttributes[i].attribute_name_index].data.Utf8.bytes,"Exceptions")==0){

            ptrAttributes[i].data.Exceptions_attribute.number_of_exceptions = u2Read(ptrClass);
            ptrAttributes[i].data.Exceptions_attribute.exception_index_table = (u2 *)
                malloc(ptrAttributes[i].data.Exceptions_attribute.number_of_exceptions*sizeof(u2));
        }else{
              /*Nao usamos, por isso tem free*/
            lixo = (u1 *)malloc((ptrAttributes[i].attribute_length+1)*sizeof(u1));
            fread(lixo,sizeof(u1),ptrAttributes[i].attribute_length,ptrClass);
	    lixo[ptrAttributes[i].attribute_length]='\0';
	    if (lixo!=NULL)
		free(lixo);
        }
    }
    return ptrAttributes;

}

ClassFile *read_class(char *filename){

    FILE *ptrClass;
    int i;
    int length = strlen(filename);
    int length_dir;
    char pclass[7] = ".class";
    ClassFile *cf;
    char* size_dir = strrchr(filename,'/');
    if (size_dir){
	memcpy(dir_base,filename,(size_dir-filename)+1);
	dir_base[(size_dir-filename)+2]='\0';
	strcat(filename,pclass);
    	ptrClass = fopen (filename,"rb");
    	filename[length]='\0';
    }else {
	length_dir= strlen(dir_base);
	strcat(dir_base,filename);
	strcat(dir_base,pclass);
	ptrClass = fopen (dir_base,"rb");
	dir_base[length_dir]='\0';

    }

    if (ptrClass == NULL){
        printf("Nao foi possivel abrir o arquivo: %s!\n\n", filename);
        return NULL;
    }
    cf = (ClassFile *) malloc(sizeof(ClassFile));
    cf->magic = u4Read(ptrClass);
    if(cf->magic != 0xCAFEBABE){
	printf("Arquivo .class fornecido nao e arquivo .class JAVA.\n");
	exit(1);
	return NULL;
    }
    cf->minor_version = u2Read(ptrClass);
    cf->major_version = u2Read(ptrClass);
    cf->constant_pool_count = u2Read(ptrClass);
    cf->constant_pool = (cp_info *) malloc((cf->constant_pool_count)*sizeof(cp_info));
    for (i=1; i < cf->constant_pool_count ; i++) {
        cf->constant_pool[i].tag = u1Read(ptrClass);
        switch (cf->constant_pool[i].tag) {
             case CLASS_INDEX:
                cf->constant_pool[i].data.Class.name_index = u2Read(ptrClass);
                break;
             case FIELDREF:
                cf->constant_pool[i].data.Fieldref.class_index = u2Read(ptrClass);
                cf->constant_pool[i].data.Fieldref.name_and_type_index = u2Read(ptrClass);
                break;
            case METHODREF:
                cf->constant_pool[i].data.Methodref.class_index = u2Read(ptrClass);
                cf->constant_pool[i].data.Methodref.name_and_type_index = u2Read(ptrClass);
                break;
            case INTERFACEMETHODREF:
                cf->constant_pool[i].data.InterfaceMethodref.class_index = u2Read(ptrClass);
                cf->constant_pool[i].data.InterfaceMethodref.name_and_type_index = u2Read(ptrClass);
                break;
            case STRING:
                cf->constant_pool[i].data.String.string_index = u2Read(ptrClass);
                break;
            case INTEGER:
                cf->constant_pool[i].data.Integer.bytes = u4Read(ptrClass);
                break;
            case FLOAT:
                cf->constant_pool[i].data.Float.bytes = u4Read(ptrClass);
                break;
            case LONG:
                cf->constant_pool[i].data.Long.high_bytes = u4Read(ptrClass);
                cf->constant_pool[i].data.Long.low_bytes = u4Read(ptrClass);
                i++;    /*Por long long ser de categoria 2 o proximo indice do const poll e invalido*/
                break;
            case DOUBLE:
                cf->constant_pool[i].data.Double.high_bytes = u4Read(ptrClass);
                cf->constant_pool[i].data.Double.low_bytes = u4Read(ptrClass);
                i++;    /*Por double ser de categoria 2 o proximo indice do const poll e invalido*/
                break;
            case NAMEANDTYPE:
                cf->constant_pool[i].data.NameAndType.name_index = u2Read(ptrClass);
                cf->constant_pool[i].data.NameAndType.descriptor_index = u2Read(ptrClass);
                break;
            case UTF8:
                cf->constant_pool[i].data.Utf8.length = u2Read(ptrClass);
                cf->constant_pool[i].data.Utf8.bytes = (u1 *) malloc((cf->constant_pool[i].data.Utf8.length+1)* sizeof(u1));
                fread (cf->constant_pool[i].data.Utf8.bytes, sizeof(u1),cf->constant_pool[i].data.Utf8.length,ptrClass);
                cf->constant_pool[i].data.Utf8.bytes[cf->constant_pool[i].data.Utf8.length]='\0';
                break;
        }
    }
    cf->access_flags = u2Read(ptrClass);
    cf->this_class = u2Read(ptrClass);
    cf->super_class = u2Read(ptrClass);
    cf->interfaces_count = u2Read(ptrClass);

/*Parte das interfaces*/
    if (cf->interfaces_count>0){
        cf->interfaces = (u2 *) malloc(cf->interfaces_count*sizeof(u2));
        for (i=0; i<cf->interfaces_count; i++){
            cf->interfaces[i] = u2Read(ptrClass);
        }
    }
    cf->fields_count = u2Read(ptrClass);

/*Parte dos campos*/
    if (cf->fields_count>0){
        cf->fields = (field_info *) malloc (cf->fields_count*sizeof(field_info));
        for (i=0;i<cf->fields_count; i++){
            cf->fields[i].access_flags = u2Read(ptrClass);
                 cf->fields[i].name_index = u2Read(ptrClass);
            cf->fields[i].descriptor_index = u2Read(ptrClass);
            cf->fields[i].attributes_count = u2Read(ptrClass);
            cf->fields[i].attributes = read_attributes_info ( cf->fields[i].attributes_count,cf->constant_pool, ptrClass);
        }
    }
    cf->methods_count = u2Read(ptrClass);

/*Parte dos metodos*/
    cf->methods = (method_info *) malloc (cf->methods_count*sizeof(method_info));
    for (i=0;i<cf->methods_count;i++){
        cf->methods[i].access_flags = u2Read(ptrClass);
        cf->methods[i].name_index =u2Read(ptrClass);
        cf->methods[i].descriptor_index = u2Read(ptrClass);
        cf->methods[i].attributes_count = u2Read(ptrClass);
        cf->methods[i].attributes = read_attributes_info(cf->methods[i].attributes_count,cf->constant_pool, ptrClass);

    }
    cf->attributes_count = u2Read(ptrClass);
    cf->attributes = read_attributes_info(cf->attributes_count,cf->constant_pool, ptrClass);

    return cf;
}

