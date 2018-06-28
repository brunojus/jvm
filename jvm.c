/*
 Universidade de Brasilia  - UnB
 Departamento de Ciencia da Computacao  - CIC
 Disciplina:  Software Basico
 Professor:  Marcelo Ladera
 Turma: A
 Alunos:
       Tomaz Aguiar 090040121
       Lucas Braga 090009746
       Lucas Lo Ami 090009886
       Leonardo de Sousa Melo 0834220
       Artur de Azevedo 0990001
*/



#include <stdio.h>
#include <string.h>
#include "Interpreter.h"





int Nargs(char *descriptor, int length){
    int i, toReturn=0;
    int ref=0;/*flag para indicar que e uma referencia*/
    for (i=0;i<length;i++){
        switch (descriptor[i]){
	    case ('['):
		ref=1;
	    break;
            case ('I'):/*int*/
            case ('B'):/*byte*/
            case ('Z'):/*boolean*/
            case ('S'):/*short*/
            case ('C'):/*char*/
            case ('F'):/*float*/
                toReturn++;
		ref=0;
                break;
            case ('D'):/*double, soma 2 de 32 bits=64bits*/
	    case ('J'): /*igual a double*/
		if (ref){
        	        toReturn++;
			ref=0;
		}else{
                	toReturn++;
	                toReturn++;
		}
                break;
            case ('L'):/*referencia*/
                toReturn++;

                while(descriptor[i]!=';') i++;
                break;
            case (')'):/*fim dos paramentros de entrada*/
                i = length;
                break;
        }
    }
    return toReturn;

}




void executarPrintln(FrameStack* fr, char* descriptor, int length){ /*Verifica qual o tipo para poder imprimir*/
	/*variaveis para fazer cast ou movimentacao de bits para os tipos adequados*/
	float f;
	double d;
	long long l;
	int i;
	unsigned short *pshort;
	u4 idx,aux[2];

	if (!strcmp(descriptor,"()V")) /*Caso que so usa system.output.println*/
		printf("\n");
	if (strstr(descriptor,"Ljava/lang/String;")!=NULL){/*Para o tipo string*/
		idx = pop_operand(&(fr->top->opStack));
		printf("%s\n",fr->top->cPoolRunTime[idx].data.Utf8.bytes);
	}
	if (strstr(descriptor,"(I)")!=NULL){/*Inteiro, short, boolean e byte*/
		idx = pop_operand(&(fr->top->opStack));

		printf("%d\n",(int)idx);                      /*faz o cast, pois na pilha esta unsigned*/
	}

	if (strstr(descriptor,"(F)")!=NULL){/*Float*/
		idx = pop_operand(&(fr->top->opStack));
		memmove(&f,&idx,sizeof(float));              /*Transfere p memoria, pois o interpretador nao pode fazer cast pelo padrao i3e. (unsigned int, tem q passar p float)*/
		printf("%f\n",f);
	}
	if (strstr(descriptor,"(D)")!=NULL){/*Double*/
		aux[1] = pop_operand(&(fr->top->opStack));
		aux[0] = pop_operand(&(fr->top->opStack));
		memmove(&d,&aux,sizeof(double));
		printf("%lf\n",d);
	}

	if (strstr(descriptor,"(J)")!=NULL){/*Long*/
		aux[1] = pop_operand(&(fr->top->opStack));
		aux[0] = pop_operand(&(fr->top->opStack));
		memmove(&l,&aux,sizeof(long long));
		printf("%ld\n",l);
	}
	if (strstr(descriptor,"(C)")!=NULL){/*Char*/
		idx = pop_operand(&(fr->top->opStack));
		printf("%c\n",(char)idx);
	}
	if (strstr(descriptor,"([C)")!=NULL){/*vetor de char*/
		idx = pop_operand(&(fr->top->opStack));              /*aqui ele pegue somente o indice p o vetor de 64 bits(bizu)*/
		pshort =(unsigned short*)fr->top->pointers[idx];    /*aqui ele pegue da pilha de 64 bits(bizu)*/
		i=0;
		while (pshort[i]!=0){
			printf("%c",(char)pshort[i]);
			i++;
		}
		printf("\n");
	}
	if (strstr(descriptor,"(Z)")!=NULL){/*boolean*/
		idx = pop_operand(&(fr->top->opStack));
		if ((char)idx !=0)
			printf("%s\n","true");
		else
			printf("%s\n","false");
	}
}



void executarClinit(FrameStack* fr){ /*execucao do metodo*/


	for (fr->top->pc=0;fr->top->pc<fr->top->method->attributes->data.Code_attribute.code_length;fr->top->pc++){
		executarInstrucao(fr->top->method->attributes->data.Code_attribute.code[fr->top->pc],fr);


	}

}

void executar(char* method, char* descriptor, char* class_name,int nargs, FrameStack* fr, int especial){

	method_info *mi;
	int i=0;
	u4 idx;
	int par;/*indice do vetor de variaveis locais, no qual sera passado um parametro*/
	u4* argumentos;/*vetor de argumentos de uma funcao*/
	int ref=0;/*flag para indicar de um referenci ou um tipo primitivo*/
	u4 temp;/*flag para indicar que eh um referencia*/
	Class* class  = searchClass(class_name);
	mi = getMethod(method,class_name,descriptor);
	cp_info* cp = getCpSuper(method,class_name,descriptor);
		if (mi!=NULL){
			push_frame(cp,class->atribs, mi, fr); /*Cria o frame*/

			if (nargs && !strstr("Ljava/lang",descriptor)){/*Intercepta funcoes da bilioteca java*/

				argumentos = (u4*) malloc(nargs*sizeof(u4));
				/*argumentos estao sendo desempilhados e colocados num vetor
				  pois na especificacao os primeiros parametros vao para os
				  indices mais altos do vetor de variaveis locais
				*/
				for (i=0;i<nargs;i++){
					argumentos[i] = pop_operand(&(fr->top->next->opStack));

				}

				if (!especial){/*funcoes que usam passagem por referencias de objetos*/
					nargs=nargs-1;
				/*Passagem de paramentros
				  para funcoes que nao passa alem dos argumentos referencia de objetos*/
				par=0;/*Inicia por zero pq nao faz referencia a nenhum objeto*/
				for (i=0;i<strlen(descriptor);i++){
					switch (descriptor[i]){
						case ('['):/*Seta a flag de refecia, e pula os '['*/
							ref=1;
							while(descriptor[i]=='[')i++;
							i--;
							break;
						case('L'):/*passa uma referencia*/
							temp = argumentos[nargs];
							fr->top->LocalVariables[par++] = fr->top->countpoint;	/*Variaveis local o indice do vet ponteiros(64 bits)*/
							fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[temp]; /*Tranfere valor do end q esta no vetor de end do frame de baixo*/
							fr->top->countpoint++;
							nargs--;
							ref=0;
							while(descriptor[i]!=';')i++;/*fim do descritor ;*/
							break;
						 case ('I'):/*int*/
						 case ('B'):/*byte*/
						 case ('Z'):/*boolean*/
						 case ('S'):/*short*/
						 case ('C'):/*char*/
						 case ('F'):/*float*/

							if (!ref){
							fr->top->LocalVariables[par++] = argumentos[nargs];
							nargs--;

							}
							else {
								temp = argumentos[nargs];
								fr->top->LocalVariables[par++] =fr->top->countpoint;
								fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[temp];
								fr->top->countpoint++;
								nargs--;
								ref=0;
							}

							break;
						case ('D'):/*Double*/
						case ('J'):/*Long*/

							if (!ref){
							fr->top->LocalVariables[par++] =argumentos[nargs];
							nargs--;
							fr->top->LocalVariables[par++] =argumentos[nargs];
							nargs--;

							}
							else {

								temp = argumentos[nargs];
								fr->top->LocalVariables[par++] = fr->top->countpoint;
								fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[temp];
								fr->top->countpoint++;
								nargs--;
								ref=0;
							}
							break;
						case (')'):/*fim dos parametros*/
						i = strlen(descriptor);
						break;

					}
				}
				}

			}
			if (especial){/*funcoes que alem de argumentos passam uma referencia de objetos q e colocada no vet var locais*/

				par=1;/*O 0 e reservado no vet var locais*/
				for (i=0;i<strlen(descriptor) && nargs>=0;i++){

					switch (descriptor[i]){
						case ('['):/*seta a flag referencia, pula caracteres '['*/
							ref=1;
							while(descriptor[i]=='[')i++;
							i--;
							break;
						case('L'):/*referencia*/
							temp = argumentos[nargs-1];
							fr->top->LocalVariables[par] = fr->top->countpoint;
							fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[temp];
							fr->top->countpoint++;
							nargs--;
							par++;
							ref=0;
							while(descriptor[i]!=';')i++;
							break;
						 case ('I'):/*int*/
						 case ('B'):/*byte*/
						 case ('Z'):/*boolean*/
						 case ('S'):/*short*/
						 case ('C'):/*char*/
						 case ('F'):/*float*/

							if (!ref){
							fr->top->LocalVariables[par] = argumentos[nargs-1];
							nargs--;
							par++;
							}
							else {

								temp = argumentos[nargs-1];
								fr->top->LocalVariables[par] = fr->top->countpoint;
								fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[temp];
								fr->top->countpoint++;
								par++;
								ref=0;
								nargs--;
							}

							break;
						case ('D'):/*Double*/
						case ('J'):/*Long*/

							if (!ref){
							fr->top->LocalVariables[par] =argumentos[nargs-1];
							nargs--;
							par++;
							fr->top->LocalVariables[par] =argumentos[nargs-1];
							nargs--;
							par++;
							}
							else {

								temp = argumentos[nargs-1];
								fr->top->LocalVariables[par] = fr->top->countpoint;
								fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[temp];
								fr->top->countpoint++;
								nargs--;
								par++;
								ref=0;
							}
							break;
						case (')'):/*Caso ) indica fim dos parametros*/
						i = strlen(descriptor);
						break;
					}
				}
				/*vetor var locais indice 0: Passagem da referencia de um objeto*/
				idx = pop_operand(&(fr->top->next->opStack));
				fr->top->pointers[fr->top->countpoint] = fr->top->next->pointers[idx];
				fr->top->LocalVariables[0]=fr->top->countpoint;
				fr->top->countpoint++;
			}

		}else{
			printf("Metodo %s nao encontrado!", method);
			exit(1);
		}
/*Executa funcao chamada*/
	for (fr->top->pc=0;fr->top->pc<fr->top->method->attributes->data.Code_attribute.code_length;fr->top->pc++){
		executarInstrucao(fr->top->method->attributes->data.Code_attribute.code[fr->top->pc],fr);


	}
/*Desempilha o frame*/
	pop_frame(fr);

}

/*Funcao principal reponsavel por receber o nome de uma classe como argumento e chamar o loader para carregar o ponto class  e executar as funcos de inicializacao e a main*/

int main(int argc, char* argv[]){

	method_info *mi;

	if (argc==2){
		FrameStack fr;


		Class* class  = searchClass(argv[1]);

		mi =getMethod("<clinit>",argv[1],"()V");/*Procura a funcao clinit*/
		if (mi!=NULL){
			push_frame(class->classFl->constant_pool,class->atribs, mi, &(fr));
			executarClinit(&fr);
			pop_frame(&fr);

		}
		/*Conferir, pois o java ja implementa a chamada dessa funcao quando chama as funcoes(construtores) INVOKE. PROVAVELMENTE ERRADO*/
		/*mi =getMethod("<init>",argv[1],"()V");procura a funcao init
		if (mi!=NULL){
			push_frame(class->classFl->constant_pool,class->atribs, mi, &(fr));
			executarClinit(&fr);
			pop_frame(&fr);
		}*/

        /*Chamada da execucao da main, usa Ljava/lang/String, pq toda main no java usa esse descritor*/
		executar("main","([Ljava/lang/String;)V",argv[1],0,&(fr),0);

	}
	else{
		printf("\nO parametro requerido e o arquivo .class, sem a extensao .class no final!\n");
	}
	return 1;

}



