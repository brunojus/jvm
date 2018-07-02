#include "MethodArea.h"

Class *list = NULL;    /*variavel global para a LISTA DE CLASSES*/

void insertClass(Class *newClass){
    newClass->nextClass = NULL;
    if(list == NULL){
        list = newClass;
    }else{
        Class *aux = list;
        while(aux->nextClass!=NULL){
            aux = aux->nextClass;
        }
        aux->nextClass = newClass;
    }
}

void destroyClassList(){
	Class *aux;
	int i,j;
	while(list!=NULL){
		aux = list;
		list = list->nextClass;/*salva a referencia para os free's*/
		for(i=0;i<aux->classFl->constant_pool_count;i++){/*libera todo vetor Utf8 dentro do constant pool*/
			free(aux->classFl->constant_pool[i].data.Utf8.bytes);
		}
		free(aux->classFl->constant_pool);/*para so ai liberar o constant pool*/
		free(aux->classFl->interfaces);
		for(i=0;i<aux->classFl->fields_count;i++){/*libera todos os atributos de cada campo*/
			for(j=0;j<aux->classFl->fields[i].attributes_count;j++){/*liberando 1 o codigo ou exception_index_tabel*/
				free(aux->classFl->fields[i].attributes[j].data.Code_attribute.code);
				free(aux->classFl->fields[i].attributes[j].data.Exceptions_attribute.exception_index_table);
			}
			free(aux->classFl->fields[i].attributes);/*para so assim liberar o atributo*/
		}
		free(aux->classFl->fields);/*e o campo*/
		for(i=0;i<aux->classFl->methods_count;i++){/*mesma coisa para os metodos*/
			for(j=0;j<aux->classFl->methods[i].attributes_count;j++){
				free(aux->classFl->methods[i].attributes[j].data.Code_attribute.code);
				free(aux->classFl->methods[i].attributes[j].data.Exceptions_attribute.exception_index_table);
			}
			free(aux->classFl->methods[i].attributes);
		}
		free(aux->classFl->methods);
		for(j=0;j<aux->classFl->attributes_count;j++){/*mesma coisa para os atributos da classe*/
			free(aux->classFl->attributes[j].data.Code_attribute.code);
			free(aux->classFl->attributes[j].data.Exceptions_attribute.exception_index_table);
		}
		free(aux->classFl->attributes);
		free(aux->classFl);/*libera a classe*/
		free(aux->atribs);/*libera os atributos staticos*/
		free(aux);/*libera o elemento da lista*/
	}
}

Class *searchClass(char *className){
    u2 idx;
    Class *aux = list;
    ClassFile *newClassFile;
    while(aux!=NULL){    /*verifica se a classe solicitada nao esta carregada*/
        idx=aux->classFl->constant_pool[aux->classFl->this_class].data.Class.name_index;
        if(!strcmp(className, (char *) aux->classFl->constant_pool[idx].data.Utf8.bytes)){
            return aux;
        }else{
            aux = aux->nextClass;
        }
    }/*se nao estiver a carrega*/
    newClassFile = read_class(className);
    if(newClassFile == NULL){
	//printf("\n%s",className);
        //printf(" Classe não encontrada\n\n");
        exit(0);
    }else{/*Se for encontrada ajusta seus atributos*/
        Class *newClass = (Class*) malloc (sizeof(Class));
        newClass->classFl = newClassFile;
        newClass->nAtribStatic = CountStaticAtrib(newClassFile);
        newClass->atribs = staticLoad(newClassFile);
        insertClass(newClass);/*Insere na lista*/
        return newClass;
    }
}

cp_info* cpSearch(char *className){
    Class *classInfo = searchClass(className);/*Procura a classe*/
    return classInfo->classFl->constant_pool;/*e retorna o ponteiro para o constant pool*/
}

int CountStaticAtrib(ClassFile *ptClass){
    unsigned int flagsAcesso,numAtributos,i;
    int contador = 0;
    numAtributos = ptClass->fields_count;
    for(i=0;i<numAtributos;i++){
	
        flagsAcesso = ptClass->fields[i].access_flags;
        /*Teste flags de acesso de atributo estatico*/
        if((flagsAcesso == 0x000a) || (flagsAcesso == 0x0010) || (flagsAcesso==0x0008)){
            contador++;
        }
    }
    return contador;
}

int CountAtrib(ClassFile *ptClass){
    unsigned int flagsAcesso,numAtributos,i;
    int contador = 0;
    numAtributos = ptClass->fields_count;
    for(i=0;i<numAtributos;i++){
	
        flagsAcesso = ptClass->fields[i].access_flags;
        /*Teste flags de acesso de atributo dinamico*/
        if((flagsAcesso != 0x000a) && (flagsAcesso != 0x0010) && (flagsAcesso!=0x0008)){
            contador++;
        }
    }
    if (strcmp((char *)ptClass->constant_pool[ptClass->constant_pool[ptClass->super_class].data.Class.name_index].data.Utf8.bytes,"java/lang/Object")){
		return contador + CountAtrib(searchClass(((char *)ptClass->constant_pool[ptClass->constant_pool[ptClass->super_class].data.Class.name_index].data.Utf8.bytes))->classFl);
	}
    return contador;
}

int TypeDescriptor (char *descriptor){
    if (!strcmp("I",descriptor))
        return INTEGER;
    else if (!strcmp("Ljava/lang/String;",descriptor))
        return STRING;
    else if (!strcmp("D",descriptor))
        return DOUBLE;
    else if (!strcmp("J",descriptor))
        return LONG;
    else if (!strcmp("F",descriptor))
        return FLOAT;
    else if (strstr(descriptor,"[I"))    
        return REFERENCE_INTEGER;
    else if (strstr(descriptor,"[Ljava/lang/String;"))
        return REFERENCE_STRING;
    else if (strstr(descriptor,"[F"))
        return REFERENCE_FLOAT;
    else if (strstr(descriptor,"[J"))
        return REFERENCE_LONG;
    else if (strstr(descriptor,"[D"))
        return REFERENCE_DOUBLE;
    else if (strstr(descriptor,"[C"))
        return REFERENCE_CHAR;
    else if (strstr(descriptor,"[S"))
        return REFERENCE_SHORT;
    else if (strstr(descriptor,"[Z"))
        return REFERENCE_BOOLEAN;
    else if (strstr(descriptor,"[B"))
        return REFERENCE_BYTE;
    else if (strstr(descriptor,"[L"))
        return REFERENCE_REFERENCE;
    return 0;
    
}

StaticAtrib * staticLoad(ClassFile * cf){
    StaticAtrib * Toreturn;/*Ponteiro para a lista de atributos*/
    int nAtrib;
    int i,j;
    nAtrib = CountStaticAtrib(cf);
    Toreturn = (StaticAtrib *) malloc (nAtrib * sizeof(StaticAtrib));
    j=0;    
    for (i=0;i<cf->fields_count;i++){
        if ((cf->fields[i].access_flags==0x000a) || (cf->fields[i].access_flags==0x0010)||(cf->fields[i].access_flags==0x0008)){
            /*Adiciona o nome e descritor*/
            Toreturn[j].name_index= cf->fields[i].name_index;
            Toreturn[j].type = TypeDescriptor((char *)cf->constant_pool[cf->fields[i].descriptor_index].data.Utf8.bytes);
            switch (Toreturn[j].type){
                case (STRING):
                    Toreturn[j].data.staticString.staticString_bytes = NULL;
                    break;
                case (INTEGER):
                    Toreturn[j].data.staticInt = 0;
                    break;
                case (FLOAT):
                    Toreturn[j].data.staticFloat = 0;
                    break;
                case (DOUBLE):
                    Toreturn[j].data.staticDouble.staticLowDouble = 0;
                    Toreturn[j].data.staticDouble.staticHighDouble = 0;
                    break;
                case (LONG):
                    Toreturn[j].data.staticLong.staticLowLong = 0;
                    Toreturn[j].data.staticLong.staticHighLong = 0;
                    break;
            }
            j++;
        }
    }
    return Toreturn;


}

Object * createObject(ClassFile * cf){
    Object * Toreturn;
    int nAtrib;
    int i,j,k,super=1;
    nAtrib = CountAtrib(cf);
    Toreturn = (Object *) malloc (nAtrib * sizeof(Object));
    j=0;    
    k=0;
    while(super){
	    for (i=k;i<k+cf->fields_count;i++){
		if ((cf->fields[i].access_flags!=0x000a) || (cf->fields[i].access_flags!=0x0010) || (cf->fields[i].access_flags!=0x0008)){
		    
		    Toreturn[j].name_index= cf->fields[i].name_index;
		    Toreturn[j].type = TypeDescriptor((char *)cf->constant_pool[cf->fields[i].descriptor_index].data.Utf8.bytes);
		
		    switch (Toreturn[j].type){
		        case (STRING):
		            Toreturn[j].data.String.String_bytes = NULL;
		            break;
		        case (INTEGER):
		            Toreturn[j].data.Int = 0;
		            break;
		        case (FLOAT):
		            Toreturn[j].data.Float = 0;
		            break;
		        case (DOUBLE):
		            Toreturn[j].data.Double.LowDouble = 0;
		            Toreturn[j].data.Double.HighDouble = 0;
		            break;
		        case (LONG):
		            Toreturn[j].data.Long.LowLong = 0;
		            Toreturn[j].data.Long.HighLong = 0;
		            break;
		    }
		    j++;
		}
	    }
	k=i;
	if (!strcmp((char*)(cf->constant_pool[cf->constant_pool[cf->super_class].data.Class.name_index].data.Utf8.bytes),"java/lang/Object"))
		super =0;
		else
		 cf = searchClass((char*)cf->constant_pool[cf->constant_pool[cf->super_class].data.Class.name_index].data.Utf8.bytes)->classFl;
	}	
    return Toreturn;
}

method_info *getMethod(char* name, char* class_name, char* descriptor ){
    int i=0, idx;
    Class *c = searchClass(class_name);
    if (c!=NULL){/*Testa se a classe existe*/
        for (i=0;i<c->classFl->methods_count;i++){
            idx=c->classFl->methods[i].name_index;
            if (!strcmp((char *)c->classFl->constant_pool[idx].data.Utf8.bytes,name) && !strcmp((char *)c->classFl->constant_pool[c->classFl->methods[i].descriptor_index].data.Utf8.bytes, descriptor))
                
                return &(c->classFl->methods[i]);
	}
	if (strcmp((char *)c->classFl->constant_pool[c->classFl->constant_pool[c->classFl->super_class].data.Class.name_index].data.Utf8.bytes,"java/lang/Object")){
		return getMethod(name,(char *)c->classFl->constant_pool[c->classFl->constant_pool[c->classFl->super_class].data.Class.name_index].data.Utf8.bytes,descriptor);
		}
    }	 		
    return NULL;

}
cp_info *getCpSuper(char* name, char* class_name, char* descriptor ){
    int i=0, idx;
    Class *c = searchClass(class_name);
    if (c!=NULL){/*Testa se a classe existe*/
        for (i=0;i<c->classFl->methods_count;i++){
            idx=c->classFl->methods[i].name_index;
            if (!strcmp((char *)c->classFl->constant_pool[idx].data.Utf8.bytes,name) && !strcmp((char *)c->classFl->constant_pool[c->classFl->methods[i].descriptor_index].data.Utf8.bytes, descriptor))
                
                return c->classFl->constant_pool;
	}
	if (strcmp((char *)c->classFl->constant_pool[c->classFl->constant_pool[c->classFl->super_class].data.Class.name_index].data.Utf8.bytes,"java/lang/Object")){
		return getCpSuper(name,(char *)c->classFl->constant_pool[c->classFl->constant_pool[c->classFl->super_class].data.Class.name_index].data.Utf8.bytes,descriptor);
		}
    }	 		
    return NULL;

}
StaticAtrib * getstaticAtrib(char *class_name){
    Class* c = searchClass(class_name);/*Procura a classe*/
    return c->atribs;            /*E retorna o ponteiro para seus atributos*/

}

long getNAtribStatic (char *class_name){
    Class* c = searchClass(class_name);/*Procura a classe*/
    return c->nAtribStatic;        /*E retorna o ponteiro com o numero de atributos estaticos*/
}
