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

#include "AuxiliarInstructions.h"

#ifndef __INSTRUCTIONS__
#define __INSTRUCTIONS__

#define SIZE_DOUBLE 8



/**
 *  \brief Esta fun��o empilha um imediato de um byte.
 *
 * A fun��o opera inserindo  um valor byte no topo do pilha
 * \param  valor Um byte a ser empilhado.
 * \param  *fs O ponteiro para o frame.
 */
void bipush(char valor, FrameStack *fs);

/**
 * \brief Esta fun��o desempilha o valor est�tico de um atributo de uma classe, 
 * e faz uma atribui��o ao campo.
 *
 * \param *fs O ponteiro para o frame onde se efetuar� a opera��o.
 */
void putstatic(FrameStack *fs);

/**************int*************/

/**
 *  \brief Esta função empilha um valor constante na pilha de operandos
 *
 * A função opera inserindo  um valor inteiro no topo do pilha
 * \param  *fs O ponteiro para o frame.
 * \param  valor Um inteiro a ser empilhado.
 */
void iconst(u4 val, FrameStack *fs );

/**
 * \brief Esta função simplesmente armazena um int do topo da pilha de operandos no vetor de variáveis locais
 * 
 * A função primeiro desempilha o valor do topo da pilha e esse valor é armazenado no vetor de variáveis locais na posição
 * indicada por val.
 * \param  val Índice do vetor de variaveis locais.
 * \param  *fs O ponteiro para o frame.
 */
void istoren(u4 val,FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um int na pilha de operandos
 * 
 * A função empilha o valor do int armazenado no vetor de variáveis locais do índice dado.
 * \param  val Índice do valor a ser empilhado.
 * \param  *fs O ponteiro para o frame.
 */
void iloadn(u4 val, FrameStack *fs );

/**
 *  \brief Esta função multiplica dois valores inteiros
 *
 * A função opera desempilhando dois valores da pilha, multiplicando os dois e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void imul(FrameStack *fs);

/**
 *  \brief Esta função soma dois valores inteiros
 *
 * A função opera desempilhando dois valores da pilha, somando os dois e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void iadd(FrameStack *fs);

/**
 *  \brief Esta função subtrai dois valores inteiros
 *
 * A função opera desempilhando dois valores da pilha, subtraindo o primeiro pelo segundo e 
 *  empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void isub(FrameStack *fs);

/**
 *  \brief Esta função divide dois valores inteiros
 *
 * A função opera desempilhando dois valores da pilha, dividindo os dois e truncando
 * a parte fracionaria da operação e empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void idiv(FrameStack *fs);


/**
 *  \brief Esta função faz a operação "e" logico entre dois valores inteiros
 *
 * A função opera desempilhando dois valores da pilha, e faz o "e" logico entre os valores e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void iand(FrameStack *fs);

/**
 *  \brief Esta função passa o valor para negativo de um inteiro
 *
 * A função opera desempilhando um valor da pilha, e acresenta o sinal negativo a este valor,
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void ineg(FrameStack *fs);

/**
 *  \brief Esta função faz a operação "ou" logico entre dois valores inteiros
 *
 * A função opera desempilhando dois valores da pilha, e faz o "ou" logico ente os valores e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void ior(FrameStack *fs);

/**
 *  \brief Esta função faz a operação logica "xor" entre dois valores inteiros
 *
 *  A função opera desempilhando dois valores da pilha, e faz operação logica entre os dois e
 *  empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void ixor(FrameStack *fs);

/**
 *  \brief Esta função pela o resto de uma divisão inteira
 *
 * A função opera desempilhando dois valores da pilha, dividindo os dois valores e pegando o resto 
 *  entre eles e empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void irem(FrameStack *fs);

/**
 *  \brief Esta função faz o deslocamento de bits a esquerda de valores inteiros
 *
 * A função opera desempilhando um valor fazendo sua extensao de sinal, e desempilha
 * outro valor para fazer o deslocamento de bits a esquerda do dado retirado anteriomente e 
 * empilhando este resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void ishl(FrameStack *fs);

/**
 *  \brief Esta função faz o deslocamento de bits a direita de valores inteiros
 *
 * A função opera desempilhando um valor fazendo sua extensao de sinal, e desempilha
 * outro valor para fazer o deslocamento de bits a direita do dado retirado anteriomente e 
 * empilhando este resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void ishr(FrameStack *fs);

/**
 *  \brief Esta função faz o deslocamento de bits a direita de valores inteiros
 *
 * A função opera desempilhando um valor fazendo sem extensao de sinal, e desempilha
 * outro valor para fazer o deslocamento de bits a direita do dado retirado anteriomente e 
 * empilhando este resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void iushr(FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um int na pilha de operandos
 * 
 * A função empilha o valor do int armazenado no vetor de variáveis locais do índice index dado. Caso o indicador 
 * wide seja 0, o índice não é concatenado e seu alcance é de 8 bits. Caso seja 1, o índice é concatenado para que 
 * o mesmo possa ter um alcance maior de 16 bits.
 * \param  *fs O ponteiro para o frame.
 */
void iload(FrameStack *fs );

/**
 * \brief Esta fun��o simplesmente armazena um int do topo da pilha de operandos no vetor de vari�veis locais
 * 
 * A função primeiro desempilha o valor do topo da pilha e esse valor é armazenado no vetor de variáveis locais na posição
 * indicada por index. Caso o indicador wide seja 0, o índice não é concatenado e seu alcance é de 8 bits. Caso seja 1, o 
 * índice é concatenado para que o mesmo possa ter um alcance maior de 16 bits.
 * \param  *fs O ponteiro para o frame.
 */
void istore(FrameStack *fs);

/**
 * \brief Esta função armazena um int do topo da pilha de operandos em um vetor de ints 
 * 
 * A função retira da pilha de operandos o valor do int a ser armazenado do vetor, o índice
 * para a posição onde esse elemento será armazenado e uma referência a posição do início desse
 * vetor na memória 
 * \param  *fs O ponteiro para o frame.
 */
void iastore(FrameStack *fs);

/**
 *  \brief Esta funçao converte um int para long long
 * 
 * A funçao desempilha um int. Entao, faz um casting para long long, depois empilha no topo da pilha, primeiro o mais 
 * significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void i2l(FrameStack *fs);

/**
 *  \brief Esta funçao converte um int para double
 * 
 * A funçao desempilha um int. Entao, faz um casting para double, depois empilha no topo da pilha, primeiro o mais 
 * significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void i2d(FrameStack *fs);

/**
 *  \brief Esta funçao converte um int para char
 * 
 * A funçao desempilha um int. Entao, faz um casting para char.  
 * \param  *fs O ponteiro para o frame.
 */
void i2c(FrameStack *fs);

/**
 *  \brief Esta funçao converte um int para byte
 * 
 * A funçao desempilha um int. Entao, faz um casting para byte, depois empilha no topo da pilha.  
 * \param  *fs O ponteiro para o frame.
 */
void i2b(FrameStack *fs);

/**
 *  \brief Esta funçao converte um int para short
 * 
 * A funçao desempilha um int. Entao, faz um casting para short, depois empilha no topo da pilha.  
 * \param  *fs O ponteiro para o frame.
 */
void i2s(FrameStack *fs);

/*************long long*************/
/**
 *  \brief Esta fun��o empilha um valor constante na pilha de operandos
 *
 * A fun��o opera inserindo  um valor long long no topo do pilha
 * \param  *fs O ponteiro para o frame.
 * \param  valor Um long long a ser empilhado.
 */
void lconstn(long val1, FrameStack *fs );

/**
 * \brief Esta função simplesmente armazena um long long do topo da pilha de operandos no vetor de variáveis locais
 * 
 * A função primeiro desempilha o valor menos significativo do topo da pilha e esse valor é armazenado no
 * vetor de variáveis locais na posição indicada por val. O valor mais significativo � retirado do topo da pilha
 * e armazenado no vetor de vari�veis locais na posi��o val+1.
 * \param  val Índice do vetor de variaveis locais.
 * \param  *fs O ponteiro para o frame.
 */
void lstoren(u4 val,FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um long long na pilha de operandos
 * 
 * A função empilha o valor do long long armazenado no vetor de variáveis locais do índice dado.
 * \param  val Índice do valor a ser empilhado.
 * \param  *fs O ponteiro para o frame.
 */
void lloadn(u4 val, FrameStack *fs );

/**
 *  \brief Esta função soma dois valores long long
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Soma os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void ladd(FrameStack *fs);

/**
 *  \brief Esta função subtrai dois valores long long
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Subtrai os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lsub(FrameStack *fs);

/**
 *  \brief Esta função divide dois valores long long
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Divide os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lldiv_(FrameStack *fs);

/**
 *  \brief Esta função divide dois valores long long e armazena o resto da divisao
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Divide os dois operandos e empilha o resto da divisao no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lrem(FrameStack *fs);

/**
 *  \brief Esta função multiplicaçao dois valores long long
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando. Multiplica os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lmul(FrameStack *fs);

/**
 *  \brief Esta funçao passa o valor para negativo de um long long
 *
 * A função opera desempilhando dois valores da pilha, o menos significativo depois o mais significativo
 * do operando. Acrescenta o sinal negativo a este valor, e empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void lneg(FrameStack *fs);

/**
 *  \brief Esta funçao faz a operaçao "e" logico entre dois valores long long
 *
 * * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando. Faz o "e" logico entre os valores e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void land(FrameStack *fs);

/**
 *  \brief Esta funçao faz a operaçao "ou" logico entre dois valores long long
 *
 * * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando. Faz o "ou" logico entre os valores e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lor(FrameStack *fs);

/**
 *  \brief Esta funçao faz a operaçao "ou exclusivo" logico entre dois valores long long
 *
 * * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando. Faz o "ou exclusivo" logico entre os valores e empilha o resultado no topo da pilha, o mais  
 * significativo depois o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lxor(FrameStack *fs);

/**
 *  \brief Esta função faz o deslocamento de bits a esquerda de valores long long
 *
 * A funçao desempilha um valor para fazer o deslocamento de bits a esquerda do dado retirado posteriomente.
 * Entao a função opera desempilhando dois valores da pilha, o menos significativo depois o mais significativo
 * do operando. Empilhando o resultado do deslocamento no topo da pilha, primeiro o mais significativo
 * depois o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lshl(FrameStack *fs);

/**
 *  \brief Esta função faz o deslocamento de bits a direita de valores long long
 *
 * A funçao desempilha um valor para fazer o deslocamento de bits a direita do dado retirado posteriomente.
 * Entao a função opera desempilhando dois valores da pilha, o menos significativo depois o mais significativo
 * do operando. Empilhando o resultado do deslocamento no topo da pilha, primeiro o mais significativo
 * depois o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lshr(FrameStack *fs);

/**
 *  \brief Esta função faz o deslocamento de bits a direita de valores long long
 *
 * A função opera desempilhando um valor fazendo sem extensao de sinal. 
 * Entao a função opera desempilhando dois valores da pilha, o menos significativo depois o mais significativo
 * do operando. Empilhando o resultado do deslocamento no topo da pilha, primeiro o mais significativo
 * depois o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lushr(FrameStack *fs);

/**
 *  \brief Esta funçao executa o retorno de um metodo, empilhando o valor long long de retorno na pilha de
 * operandos do frame do metodo chamador 
 * 
 * A funçao desempilha dois valores, primeiro o menos significativo depois o mais significativo. Depois empilha
 * na ordem contraria.
 * \param  *fs O ponteiro para o frame.
 */
void lreturn(FrameStack *fs);

/**
 *  \brief Esta funçao converte um long long para double
 * 
 * A funçao desempilha um long long, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * double, depois empilha no top da pilha, primeiro o mais significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void l2d(FrameStack *fs);

/**
 *  \brief Esta funçao converte um long long para float
 * 
 * A funçao desempilha um long long, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * float, depois empilha no top da pilha, primeiro o mais significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void l2f(FrameStack *fs);

/**
 *  \brief Esta funçao converte um long long para int
 * 
 * A funçao desempilha um long long, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * int, depois empilha no top da pilha.  
 * \param  *fs O ponteiro para o frame.
 */
void l2i(FrameStack *fs);

/**
 *  \brief Esta compara dois valores long long que estao no topo da pilha
 * 
 * A funçao desempilha dois long long's, primeiro o menos significativo depois o mais significativo de cada operando.
 * Entao, faz uma subtraçao entre os operandos, depois empilha um valor int, que sera 1 caso o primeiro operando
 * for maior que o segundo, sera 0 caso os operandos sejam iguais, ou sera -1 caso o primeiro operando seja menor que o  
 * segundo.   
 * \param  *fs O ponteiro para o frame.
 */
void lcmp(FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um long long na pilha de operandos
 * 
 * A função empilha o valor do long long armazenado no vetor de variáveis locais do índice dado. Empilha o mais significativo
 * depois o menso significativo.
 * \param  *fs O ponteiro para o frame.
 */
void lload(FrameStack *fs );

/**
 * \brief Esta função simplesmente carrega um float na pilha de operandos
 * 
 * A função empilha o valor do float armazenado no vetor de variáveis locais do índice presente no byte imediatamente após o opcode.
 * \param  *fs O ponteiro para o frame.
 */
void fload(FrameStack *fs );

/**
 * \brief Esta função simplesmente carrega uma constante float na pilha de operandos
 * 
 * A função empilha o valor do float armazenado no vetor de variáveis locais. 
 * \param  val Índice do valor a ser empilhado.
 * \param  *fs O ponteiro para o frame.
 */
void floadn(u4 val, FrameStack *fs);

/**
 * \brief Esta funcao simplesmente armazena um long long do topo da pilha de operandos no vetor de variaveis locais
 * 
 * A função primeiro desempilha o valor do topo da pilha e esse valor é armazenado no vetor de variáveis locais na posição
 * indicada por index. Isso e feito para as partes mais e menos significativas.
 * Caso o indicador wide seja 0, o índice não é concatenado e seu alcance é de 8 bits. Caso seja 1, o 
 * índice é concatenado para que o mesmo possa ter um alcance maior de 16 bits.
 * \param  *fs O ponteiro para o frame.
 */
void lstore(FrameStack *fs);

/**
 * \brief Esta função armazena um long long do topo da pilha de operandos em um vetor de long long's 
 * 
 * A função retira da pilha de operandos o valor do long long a ser armazenado do vetor, o índice
 * para a posição onde esse elemento será armazenado e uma referência a posição do início desse
 * vetor na memória 
 * \param  *fs O ponteiro para o frame.
 */
void lastore(FrameStack *fs);
/***************double***************/

/**
 *  \brief Esta fun��o empilha um valor constante na pilha de operandos
 *
 * A fun��o opera inserindo  um valor double no topo do pilha
 * \param  *fs O ponteiro para o frame.
 * \param  valor Um double a ser empilhado.
 */
void dconstn(double val1, FrameStack *fs );

/**
 * \brief Esta função simplesmente armazena um double do topo da pilha de operandos no vetor de variáveis locais
 * 
 * A função primeiro desempilha o valor menos significativo do topo da pilha e esse valor é armazenado no
 * vetor de variáveis locais na posição indicada por val. O valor mais significativo � retirado do topo da pilha
 * e armazenado no vetor de vari�veis locais na posi��o val+1.
 * \param  val Índice do vetor de variaveis locais.
 * \param  *fs O ponteiro para o frame.
 */
void dstoren(u4 val,FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um double na pilha de operandos
 * 
 * A função empilha o valor do double armazenado no vetor de variáveis locais do índice dado.
 * \param  val Índice do valor a ser empilhado.
 * \param  *fs O ponteiro para o frame.
 */
void dloadn(u4 val, FrameStack *fs );

/**
 *  \brief Esta função soma dois valores double
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Soma os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void dadd(FrameStack *fs);

/**
 *  \brief Esta função subtrai dois valores double
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Subtrai os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void dsub(FrameStack *fs);

/**
 *  \brief Esta função divide dois valores double
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Divide os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void ddiv(FrameStack *fs);

/**
 *  \brief Esta função divide dois valores double e armazena o resto da divisao
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando.Divide os dois operandos e empilha o resto da divisao no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void dRem(FrameStack *fs);

/**
 *  \brief Esta função multiplica dois valores double
 *
 * A função opera desempilhando quatro valores da pilha, o menos significativo depois o mais significativo
 * de cada operando. Multiplica os dois operandos e empilha o resultado no topo da pilha, o mais significativo depois
 * o menos significativo.
 * \param  *fs O ponteiro para o frame.
 */
void dmul(FrameStack *fs);

/**
 *  \brief Esta funçao passa o valor para negativo de um double
 *
 * A função opera desempilhando dois valores da pilha, o menos significativo depois o mais significativo
 * do operando. Acrescenta o sinal negativo a este valor, e empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void dneg(FrameStack *fs);

/**
 *  \brief Esta compara dois valores double que estao no topo da pilha
 * 
 * A funçao desempilha dois double's, primeiro o menos significativo depois o mais significativo de cada operando.
 * Entao, faz uma subtraçao entre os operandos, depois empilha um valor int, que sera 1 caso o primeiro operando
 * for maior que o segundo, sera 0 caso os operandos sejam iguais, ou sera -1 caso o primeiro operando seja menor que o  
 * segundo.
 * \param  *fs O ponteiro para o frame.
 */
void dcmpl(FrameStack *fs);

/**
 *  \brief Esta � uma fun��o de compara��o de dois doubles da pilha de operandos utilizando o padr�o IEEE 754
 * 
 * A fun��o desempilha quatro valores, primeiro o menos significativo e o 
 * mais significativo do primeiro operando, e depois o menos significativo e o 
 * mais significativo do segundo operando. Se o valor do primeiro operando for 
 * maior que o valor do segundo operando, a fun��o empilha 1 na pilha de operandos. 
 * Se os valores forem iguais, a fun��o empilha 0. Caso o valor do segundo
 * operando seja maior que o valor do primeiro, ent�o -1 � inserido na pilha. 
 * \param  *fs O ponteiro para o frame.
 */
void dcmpg(FrameStack *fs);

/**
 *  \brief Esta funçao executa o retorno de um metodo, empilhando o valor double de retorno na pilha de
 * operandos do frame do metodo chamador 
 * 
 * A funçao desempilha dois valores, primeiro o menos significativo depois o mais significativo. Depois empilha
 * na ordem contraria.
 * \param  *fs O ponteiro para o frame.
 */
void dreturn(FrameStack *fs);

/**
 *  \brief Esta funçao converte um double para long long
 * 
 * A funçao desempilha um double, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * long long, depois empilha no top da pilha, primeiro o mais significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void d2l(FrameStack *fs);

/**
 *  \brief Esta funçao converte um double para float
 * 
 * A funçao desempilha um double, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * float, depois empilha no top da pilha, primeiro o mais significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void d2f(FrameStack *fs);

/**
 *  \brief Esta funçao converte um double para int
 * 
 * A funçao desempilha um double, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * int, depois empilha no top da pilha.  
 * \param  *fs O ponteiro para o frame.
 */
void d2i(FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um double na pilha de operandos
 * 
 * A função empilha o valor do int armazenado no vetor de variáveis locais do índice dado. Empilha o mais significativo
 * depois o menso significativo.
 * \param  *fs O ponteiro para o frame.
 */
void dload(FrameStack *fs );

/**
 * \brief Esta funcao simplesmente armazena um double do topo da pilha de operandos no vetor de variaveis locais
 * 
 * A função primeiro desempilha o valor do topo da pilha e esse valor é armazenado no vetor de variáveis locais na posição
 * indicada por index. Isso e feito para as partes mais e menos significativas.
 * Caso o indicador wide seja 0, o índice não é concatenado e seu alcance é de 8 bits. Caso seja 1, o 
 * índice é concatenado para que o mesmo possa ter um alcance maior de 16 bits.
 * \param  *fs O ponteiro para o frame.
 */
void dstore(FrameStack *fs);

/**
 * \brief Esta função armazena um double do topo da pilha de operandos em um vetor de long long's 
 * 
 * A função retira da pilha de operandos o valor do double a ser armazenado do vetor, o índice
 * para a posição onde esse elemento será armazenado e uma referência a posição do início desse
 * vetor na memória. 
 * \param  *fs O ponteiro para o frame.
 */
void dastore(FrameStack *fs);

/**********dups*****************/

/**
 *  \brief Esta função faz o duplica o valor deo topo da pilha.
 *
 * A função opera desempilhando um valor e em seguida empilha este
 * valor duas vezes.
 * \param  *fs O ponteiro para o frame.
 */
void dup(FrameStack *fs);

/**
 *  \brief Esta função duplica um valor intercalado a outro.
 *
 * A função opera desempilhando dois valores da pilha, e logo em seguida
 * empilha o primeiro valor retirado, depois o segundo e novamente o primeiro valor.
 * \param  *fs O ponteiro para o frame.
 */
void dupx1(FrameStack *fs);

/**
 *  \brief Esta função empilha valores no topo da pilha segundo uma determinada regra.
 *
 * A função opera desempilhando tres valores da pilha, e em seguida empilha o primeiro valor
 * que foi retirado, depois empilha o terceiro valor, depois o segundo valor e repete o primeiro valor.
 * \param  *fs O ponteiro para o frame.
 */
void dupx2_1(FrameStack *fs);

/**
 *  \brief Esta função refaz a forma utilizada pela função dupx1.
 *
 * A função funciona analogamente a funçao dupx1
 * \param  *fs O ponteiro para o frame.
 */
void dupx2_2(FrameStack *fs);

/**
 *  \brief Esta função empilha valores na pilha segundo uma determinada regra
 *
 * A função opera desempilhando dois valores, e logo em seguida
 * empilha o segundo valor, depois o primeiro valor, novamente o segundo valor e
 * por fim o primeiro valor novamente.
 * \param  *fs O ponteiro para o frame.
 */
void dup2(FrameStack *fs);

/**
 *  \brief Esta função empilha valores na pilha segundo uma determinada regra
 *
 * A função opera desempilhando tres valores, e logo em seguida
 * empilha o segundo valor, depois o primeiro valor,depois o terceiro valor,
 * empilha novamente o segundo e por fim o primeiro valor novamente.
 * \param  *fs O ponteiro para o frame.
 */
void dup2x1_1(FrameStack *fs);

/**
 *  \brief Esta função refaz a forma utilizada pela função dupx1.
 *
 * A função funciona analogamente a funçao dupx1
 * \param  *fs O ponteiro para o frame.
 */
void dup2x1_2(FrameStack *fs);

/**
 *  \brief Esta função empilha valores na pilha segundo uma determinada regra
 *
 * A função opera desempilhando quatro valores, e logo em seguida
 * empilha o segundo valor, depois o primeiro valor,depois o quarto valor,depois o terceiro valor
 * empilha novamente o segundo e por fim o primeiro valor novamente.
 * \param  *fs O ponteiro para o frame.
 */
void dup2x2_1(FrameStack *fs);

/**
 *  \brief Esta função empilha valores na pilha segundo uma determinada regra
 *
 * A função opera desempilhando tres valores, e logo em seguida
 * empilha o primeiro valor, depois o tecceiro valor,depois o segundo valor novamente,
 * e por fim o primeiro valor novamente.
 * \param  *fs O ponteiro para o frame.
 */
void dup2x2_2(FrameStack *fs);

/**
 *  \brief Esta função refaz a forma utilizada pela função dupx2x1_1.
 *
 * A função funciona analogamente a funçao dupx2x1_1
 * \param  *fs O ponteiro para o frame.
 */
void dup2x2_3(FrameStack *fs);

/**
 *  \brief Esta função refaz a forma utilizada pela função dupx1.
 *
 * A função funciona analogamente a funçao dupx1
 * \param  *fs O ponteiro para o frame.
 */
void dup2x2_4(FrameStack *fs);


/*************Float*****************/

/**
 *  \brief Esta função obtém o resto de uma divisão de ponto flutuante
 *
 * A função opera desempilhando dois valores da pilha, dividindo os dois valores e pegando o resto 
 *  entre eles e empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void frem(FrameStack *fs);

/**
 *  \brief Esta função multiplica dois do tipo float
 *
 * A função opera desempilhando dois valores da pilha, multiplicando os dois e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void fmul(FrameStack *fs);

/**
 *  \brief Esta função passa o valor para negativo de um float
 *
 * A função opera desempilhando um valor da pilha, e acresenta o sinal negativo a este valor,
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void fneg(FrameStack *fs);

/**
 *  \brief Esta função insere na pilha um valor de ponto flutuante
 *
 * A função opera recebendo um parametro do tipo float,
 * empilhando o parametro no  topo da pilha.
 * \param  *fs O ponteiro para o frame.
 * \param  constante Um valor flutuante para a pilha.
 */
void fconstn(u4 val,FrameStack *fs);

/**
 * \brief Esta função simplesmente armazena um float do topo da pilha de operandos no vetor de variáveis locais
 * 
 * A função primeiro desempilha o valor do topo da pilha e esse valor é armazenado no vetor de variáveis locais na posição
 * indicada pelo indice correspondente ao primeiro byte após o opcode.
 * \param  *fs O ponteiro para o frame.
 */
void fstore(FrameStack *fs);

/**
 * \brief Esta função simplesmente armazena um float do topo da pilha de operandos no vetor de variáveis locais
 * 
 * A função primeiro desempilha o valor do topo da pilha e esse valor é armazenado no vetor de variáveis locais na posição
 * indicada por val.
 * \param  *fs O ponteiro para o frame.
 */
void fstoren(u4 val,FrameStack *fs);

/**
 *  \brief Esta função armazena um float do topo da pilha de operandos em um vetor de floats 
 * 
 * A função retira da pilha de operandos o valor do float a ser armazenado do vetor, o índice
 * para a posição onde esse elemento será armazenado e uma referência a posição do início desse
 * vetor na memória 
 * \param  *fs O ponteiro para o frame.
 */
void fastore(FrameStack *fs);

/**
 *  \brief Esta função soma dois valores do tipo float
 *
 * A função opera desempilhando dois valores da pilha, somando os dois e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void fadd(FrameStack *fs);

/**
 *  \brief Esta função subtrai dois valores do tipo float
 *
 * A função opera desempilhando dois valores da pilha, subtraindo os dois e
 * empilha o resultado no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void fsub(FrameStack *fs);

/**
 *  \brief Esta função divide dois valores do tipo float
 *
 * A função opera desempilhando dois valores da pilha, dividindo os dois e
 * empilha o resultado no topo da pilha. Note que nesta divisão não há o truncamento
 * da parte fracionaria.
 * \param  *fs O ponteiro para o frame.
 */
void fdiv(FrameStack *fs);

/**
 *  \brief Esta funçao converte um float para double
 * 
 * A funçao desempilha um float, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * double, depois empilha no topo da pilha, primeiro o mais significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void f2d(FrameStack *fs);

/**
 *  \brief Esta funçao converte um float para int
 * 
 * A funçao desempilha um float, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * int, depois empilha no topo da pilha.
 * \param  *fs O ponteiro para o frame.
 */
void f2i(FrameStack *fs);

/**
 *  \brief Esta funçao converte um float para long long
 * 
 * A funçao desempilha um float, primeiro o menos significativo depois o mais significativo. Entao, faz um casting para
 * long long, depois empilha no topo da pilha, primeiro o mais significativo depois o menos significativo.  
 * \param  *fs O ponteiro para o frame.
 */
void f2l(FrameStack *fs);

/**
 * \brief Esta fun��o simplesmente empilha um short (2 bytes) dado na pilha de operandos.
 * 
 * A fun��o apenas empilha um byte informado na pilha de operandos. H� extens�o de sinal.
 * \param  *fs O ponteiro para o frame.
 */
void sipush(FrameStack *fs);

/**
 * \brief Esta fun��o busca uma constante no pool de constantes e a empilha na pilha de operandos.
 *
 * Fun��o usada para strig, floats e ints
 * \param *fs O ponteiro para o frame onde a opera��o � efetuada.
 */
void ldc(FrameStack *fs);

/**
 * \brief Esta fun��o busca uma constante no pool de constantes e a empilha na pilha de operandos.
 *
 * Usada para doubles e long longs
 * \param *fs O ponteiro para o frame onde a opera��o � efetuada.
 */
void ldc2(FrameStack *fs);

/**
 * \brief Esta função simplesmente carrega um int na pilha de operandos
 * 
 * A função empilha o valor do int armazenado no vetor de variáveis locais do índice dado.
 * \param  *fs O ponteiro para o frame.
 */
void iload(FrameStack *fs );

/**
 *  \brief Esta fun��o armazena uma refer�ncia do topo da pilha de operandos em um vetor de refer�ncias 
 * 
 * A fun��o retira da pilha de operandos o valor da refer�ncia a ser armazenado do vetor, o �ndice
 * para a posi��o onde esse elemento ser� armazenado e uma refer�ncia a posi��o do in�cio desse
 * vetor na mem�ria 
 * \param  *fs O ponteiro para o frame.
 */
void aaload(FrameStack *fs);

/**
 * \brief Esta fun��o empilha o valor em um dado �ndice de um array de bytes ou booleans
 * na pilha de operandos, extendendo o sinal se a vari�vel for byte e n�o extendendo o 
 * sinal se a vari�vel for boolean.
 *
 * A fun��o opera desempilhando o �ndice e o endere�o do vetor da pilha de operandos,
 * ap�s isso o endere�o do vetor � copiado para um ponteiro para a estrutura array.
 * O tipo do vetor � determinado, se for byte o valor naquele �ndice do vetor tem seu
 * sinal extendido para 32 bits e armazenado na pilha de operandos. Caso o tipo do vetor
 * seja boolean o valor naquela posi��o � empilhado na pilha de operandos, sem extens�o
 * de sinal.
 * \param *fs O ponteiro para a pilha de frames.
 */
void baload(FrameStack *fs);

/**
 *  \brief Esta fun��o armazena um int do topo da pilha de operandos em um vetor de ints 
 * 
 * A fun��o retira da pilha de operandos o valor do int a ser armazenado do vetor, o �ndice
 * para a posi��o onde esse elemento ser� armazenado e uma refer�ncia a posi��o do in�cio desse
 * vetor na mem�ria 
 * \param  *fs O ponteiro para o frame.
 */
void iaload(FrameStack *fs );

/**
 *  \brief Esta fun��o armazena um long long do topo da pilha de operandos em um vetor de long longs 
 * 
 * A fun��o retira da pilha de operandos o valor do long long a ser armazenado do vetor, o �ndice
 * para a posi��o onde esse elemento ser� armazenado e uma refer�ncia a posi��o do in�cio desse
 * vetor na mem�ria 
 * \param  *fs O ponteiro para o frame.
 */
void laload(FrameStack *fs );

/**
 *  \brief Esta fun��o armazena um double do topo da pilha de operandos em um vetor de doubles 
 * 
 * A fun��o retira da pilha de operandos o valor do double a ser armazenado do vetor, o �ndice
 * para a posi��o onde esse elemento ser� armazenado e uma refer�ncia a posi��o do in�cio desse
 * vetor na mem�ria 
 * \param  *fs O ponteiro para o frame.
 */
void daload(FrameStack *fs );

/**
 * \brief Esta fun��o empilha o valor presente em um dado �ndice de um array de chars na pilha de operandos.
 *
 * A fun��o opera desempilhando um �ndice e uma refer�ncia para um array de chars, buscando o valor presente
 * naquele �ndice do array, e empilhando esse valor na pilha de operandos.
 * \param *fs O ponteiro para o frame onde a opera��o � executada.
 */
void caload(FrameStack *fs );

/**
 *  \brief Esta fun��o armazena um short do topo da pilha de operandos em um vetor de shorts 
 * 
 * A fun��o retira da pilha de operandos o valor do short a ser armazenado do vetor, o �ndice
 * para a posi��o onde esse elemento ser� armazenado e uma refer�ncia a posi��o do in�cio desse
 * vetor na mem�ria 
 * \param  *fs O ponteiro para o frame.
 */
void saload(FrameStack *fs );

/**
 *  \brief Esta função carrega um float na pilha de operandos a partir de um array de floats
 * 
 * A função retira da pilha de operandos o valor do índice do vetor e a referência ao vetor 
 * na memória, retira o valor encontrado na posição referência + indice do vetor e empilha esse
 * valor na pilha de operandos.
 * \param  *fs O ponteiro para o frame.
 */
void faload(FrameStack *fs );

/**
 * \brief Esta fun��o armazena um valor em um dado �ndice de um array de shorts.
 *
 * A fun��o opera desempilhando o valor a ser armazenado no vetor, o �ndice a ser alterado
 * e a refer�ncia para o array de shorts. Ap�s isso o valor desempilhado � armazenado naquele
 * �ndice do array.
 * \param *fs O ponteiro para o frame onde se efetuar� a opera��o.
 */
void sastore(FrameStack *fs);

/**
 * \brief Esta fun��o armazena um valor em um dado �ndice de um array de chars.
 *
 * A fun��o opera desempilhando o valor a ser armazenado no vetor, o �ndice a ser alterado
 * e a refer�ncia para o array de chars. Ap�s isso o valor desempilhado � armazenado naquele
 * �ndice do array.
 * \param *fs O ponteiro para o frame onde se efetuar� a opera��o.
 */
void castore(FrameStack *fs);

/**
 * \brief Esta fun��o empilha um valor do tipo refer�ncia armazenado em um certo
 * �ndice do vetor de vari�veis locais na pilha de operandos.
 *
 * Esta fun��o na verdade implementa a fam�lia de instru��es aload_\<n\> onde n
 * varia de 0 a 3 inclusive.
 * \param *fs O ponteiro para o frame onde se executar� a opera��o.
 * \param val O �ndice no vetor de vari�veis locais onde o valor do tipo 
 * refer�ncia est� armazenado.
 */
void aloadn(u4 val, FrameStack *fs);

/**
 * \brief Esta fun��o simplesmente armazena uma refer�ncia do topo da pilha de operandos no vetor de vari�veis locais
 * 
 * A fun��o primeiro desempilha o valor do topo da pilha e esse valor � armazenado no vetor de vari�veis locais na posi��o
 * indicada por �ndice.
 * \param  *fs O ponteiro para o frame.
 * \param val O �ndice indicando a posi��o do vetor de vari�veis locais onde a refer�ncia ser� armazenada.
 */
void astoren(u1 val, FrameStack *fs);

/**
 * \brief Esta função faz um pop na pilha de operandos.
 * \param  *fs O ponteiro para o frame.
 */
void pop(FrameStack *fs);

/**
 * \brief Esta função faz dois pops na pilha de operandos.
 * \param  *fs O ponteiro para o frame.
 */
void pop2(FrameStack *fs);

/**
 *  \brief Esta função faz a troca de posição entre dois valores da pilha.
 *
 * A função retira dois valores da pilha ,e empilha o segundo valor na pilha e depois o primeiro.
 * \param  *fs O ponteiro para o frame.
 */
void swap(FrameStack *fs);

/**
 * \brief Esta fun��o simplesmente incrementa um valor do vetor de vari�veis locais.
 * \param  *fs O ponteiro para o frame e o byte informado.
 */
void iinc(FrameStack *fs);

/**
 *  \brief Esta função coverte um valor inteiro para o tipo float.
 *
 * A função retira um valor da pilha ,e converte o valor retirado para o tipo float.
 * \param  *fs O ponteiro para o frame.
 */
void i2f(FrameStack *fs);

/**
 *  \brief Esta é uma função de comparação de dois floats da pilha de operandos utilizando o padrão IEEE 754
 * 
 * A função desempilha dois valores (dado1 e dado2) da pilha de operandos. Se o valor de dado1 for maior que o
 * valor de dado2, a função empilha 1 na pilha de operandos. Se os valores forem iguais, a função empilha 0.
 * Caso o valor de dado2 seja maior que o valor de dado1, então -1 é inserido na pilha. Se ou dos valores for
 * um número não suportado pela máquina (NaN), o valor a ser empilhado na pilha é -1.
 * \param  *fs O ponteiro para o frame.
 */
void fcmpl(FrameStack *fs);

/**
 *  \brief Esta � uma fun��o de compara��o de dois floats da pilha de operandos utilizando o padrão IEEE 754
 * 
 * A função desempilha dois valores (dado1 e dado2) da pilha de operandos. Se o valor de dado1 for maior que o
 * valor de dado2, a função empilha 1 na pilha de operandos. Se os valores forem iguais, a função empilha 0.
 * Caso o valor de dado2 seja maior que o valor de dado1, então -1 é inserido na pilha. Se ou dos valores for
 * um número não suportado pela máquina (NaN), o valor a ser empilhado na pilha é 1.
 * \param  *fs O ponteiro para o frame.
 */
void fcmpg(FrameStack *fs);

/**
 * \brief Esta fun��o compara os dois valores inteiros no topo da pilha
 * de operandos, e calcula o offset a partir do qual PC deve ser incrementado para
 * alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando os dois valores inteiros, e verificando se os mesmos s�o
 * iguais, caso eles sejam, o pc � modificado para pc+idx-3.
 * \param *fs O frame onde a opera��o � executada. 
 */
void if_icmpeq(FrameStack *fs);

/**
 * \brief Esta fun��o compara os dois valores inteiros no topo da pilha
 * de operandos, e calcula o offset a partir do qual PC deve ser incrementado para
 * alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando os dois valores inteiros, e verificando se os mesmos s�o
 * iguais, caso eles sejam, o pc � modificado para pc+idx-3.
 * \param *fs O frame onde a opera��o � executada. 
 */
void if_icmpne(FrameStack *fs);

/**
 * \brief Esta fun��o compara se o valor no topo da pilha de operandos � maior que o segundo valor,
 * e calcula o offset a partir do qual PC deve ser incrementado para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando os dois valores inteiros, e verificando se o segundo
 * valor desempilhado � menor que o primeiro valor desempilhado. Caso isso seja
 * verdade, o pc � modificado para pc+idx-3. 
 * \param *fs O frame onde a opera��o � executada.
 */
void if_icmplt(FrameStack *fs);

/**
 * \brief Esta fun��o retira dois elementos do topo da pilha, e calcula um offset a partir do
 * qual PC deve ser incrementado para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando dois valores do topo da pilha e verificando se o segundo valor
 * desempilhado � maior ou igual ao primeiro. 
 * Se isso for verdade, o pc � modificado para pc+idx-3.  
 * \param *fs O frame onde a opera��o � executada.
 */
void if_icmpge(FrameStack *fs);

/**
 * \brief Esta fun��o retira dois elementos do topo da pilha, e produz um offset a partir do
 * qual PC deve ser incrementado para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando dois valores do topo da pilha e verificando se o segundo valor
 * desempilhado � maior que o primeiro. Se isso for verdade.
 * Se isso for verdade, o pc � modificado para pc+idx-3.  
 * \param *fs O frame onde a opera��o � executada. 
 */
void if_icmpgt(FrameStack *fs);

/**
 * \brief Esta fun��o compara se o valor no topo da pilha de operandos � maior ou igual ao segundo valor,
 * e calcula o offset a partir do qual PC deve ser incrementado para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando os dois valores inteiros, e verificando se o segundo
 * valor desempilhado � menor ou igual ao primeiro valor desempilhado. Caso isso seja
 * verdade, o pc � modificado para pc+idx-3.  
 * \param *fs O frame onde a opera��o � executada. 
 */
void if_icmple(FrameStack *fs);

/**
 * \brief Esta fun��o produz um deslocamento de 16 bits a ser somado ao valor de
 * PC para implementar um desvio incondicional.
 *
 * A fun��o opera construindo um offset de 16 bits a partir de um vetor de bytes e
 * modifica o pc.
 * \param *fs O frame onde a opera��o � executada.
 */
void Goto(FrameStack *fs);

/**
 * \brief Esta fun��o produz um deslocamento de 32 bits a ser somado ao valor de
 * PC para implementar um desvio incondicional.
 *
 * A fun��o opera construindo um offset de 32 bits a partir de um vetor de bytes e
 * modifica o pc.
 * \param *fs O frame onde a opera��o � executada.
 */
void Goto_w(FrameStack *fs);

/**
 *  \brief Esta funçao executa o retorno de um metodo, empilhando o valor int de retorno na pilha de
 * operandos do frame do metodo chamador 
 * 
 * \param  *fs O ponteiro para o frame.
 */
void ireturn(FrameStack *fs);

/**
 * \brief Esta fun��o executa o retorno de um metodo, empilhando o valor float de retorno na pilha de
 * operandos do frame do metodo chamador 
 * 
 * \param  *fs O ponteiro para o frame.
 */
void freturn(FrameStack *fs);

/**
 * \brief Esta fun��o faz um push de uma referencia no frame que est� na pilha de frame 
 * 
 * \param  *fs O ponteiro para o frame.
 */
void aload(FrameStack *fs );

/**
 * \brief Esta fun��o faz um pop de uma referencia no frame que est� na pilha de frame 
 * 
 * \param  *fs O ponteiro para o frame.
 */
void astore(FrameStack *fs);


void anewarray(FrameStack *fs);
/**
 * \brief Esta fun��o coloca no frame o operador est�tico.
 *
 * A fun��o tem como objetivo prepara para fazer o printf, identificando o tipo de operando.
 * \param *fs O frame onde a opera��o � executada.
 */
void getstatic(FrameStack *fs);

/**
 * \brief Esta fun��o empilha a refer�ncia e aloca a mem�ria para um array unidimensional.
 *
 * \param *fs O frame onde a opera��o � executada.
 */
void newarray(FrameStack *fs);

/**
 * \brief Esta fun��o empilha a refer�ncia e aloca a mem�ria para um array multidimensional.
 *
 * A fun��o desemplinha o valor de cada dimens�o ,e l� dois bytes paro o �ndice do cp que cont�m o descritor do tipo
 * e um byte que cont�m a quantidade de dimens�es.
 * \param *fs O frame onde a opera��o � executada.
 */
void multianewarray(FrameStack *fs);

/**
 * \brief Esta fun��o procura a classe e cria um novo objeto dessa classe. 
 *
 * \param *fs O frame onde a opera��o � executada.
 */
void newObj(FrameStack *fs);

/**
 * \brief Esta fun��o reduz uma �nica dimens�o do array multidimensional. 
 *
 * \param *dimen ponteiro para o array multidimensional.
 * \param qualpos �ndice para a dimens�o que ser� reduzida.
 * \return arrayMult* retorna um ponteiro para uma struct que cont�m um vetor de offsets 
 * e a quantidade e o valor de cada dimens�o do array multidimensional.
 */
arrayMult *ReduceDimension(arrayMult *dimen, u4 qualpos);

/**
 * \brief Esta fun��o retorna uma refer�ncia.
 *
 * \param *fs O frame onde a opera��o � executada.
 */
void areturn(FrameStack *fs);

/**
 * \brief Esta fun��o emplilha um ponteiro com o valor null. 
 *
 * \param *fs O frame onde a opera��o � executada.
 */
void aconstnull(FrameStack *fs);

/**
 * \brief Esta fun��o armazena um valor em um dado �ndice de um array de byte ou boolean.
 *
 * A fun��o opera desempilhando o valor a ser armazenado no vetor, o �ndice a ser alterado
 * e a refer�ncia para o array de bytes ou booleans. Ap�s isso o valor desempilhado � armazenado naquele
 * �ndice do array.
 * \param *fs O ponteiro para o frame onde se efetuar� a opera��o.
 */
void bastore(FrameStack *fs);

/**
 * \brief Esta fun��o empilha o valor de um atributo de uma classe.
 *
 * \param *fs O ponteiro para o frame onde se efetuar� a opera��o.
 */
void getfield(FrameStack *fs);

/**
 * \brief Esta fun��o desempilha o valor de um atributo de uma classe, e faz uma atribui��o ao campo.
 *
 * \param *fs O ponteiro para o frame onde se efetuar� a opera��o.
 */
void putfield(FrameStack *fs);

/**
 * \brief Esta fun��o implementa um desvio condicional do tipo vari�vel igual a zero, 
 * calculando um deslocamento a ser adicionado ao valor de PC para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando o valor no topo da pilha, e verificando se o mesmo � igual a zero.
 * Se isso proceder, pc recebe pc+idx-3.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifeq(FrameStack *fs);

/**
 * \brief Esta fun��o implementa um desvio condicional do tipo vari�vel diferente de zero, 
 * calculando um deslocamento a ser adicionado ao valor de PC para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando o valor no topo da pilha, e verificando se o mesmo � diferente de zero.
 * Se isso proceder, pc recebe pc+idx-3.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifne(FrameStack *fs);

/**
 * \brief Esta fun��o implementa um desvio condicional do tipo vari�vel menor que zero, 
 * calculando um deslocamento a ser adicionado ao valor de PC para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando o valor no topo da pilha, e verificando se o mesmo � menor que zero.
 * Se isso proceder, pc recebe pc+idx-3.
 * \param *fs O frame onde a opera��o � executada.
 */
void iflt(FrameStack *fs);

/**
 * \brief Esta fun��o implementa um desvio condicional do tipo vari�vel menor ou igual a zero, 
 * calculando um deslocamento a ser adicionado ao valor de PC para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando o valor no topo da pilha, e verificando se o mesmo � menor ou igual a zero.
 * Se isso proceder, pc recebe pc+idx-3.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifle(FrameStack *fs);

/**
 * \brief Esta fun��o implementa um desvio condicional do tipo vari�vel maior que zero, 
 * calculando um deslocamento a ser adicionado ao valor de PC para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando o valor no topo da pilha, e verificando se o mesmo � maior que zero.
 * Se isso proceder, pc recebe pc+idx-3.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifgt(FrameStack *fs);

/**
 * \brief Esta fun��o implementa um desvio condicional do tipo vari�vel maior ou igual a zero, 
 * calculando um deslocamento a ser adicionado ao valor de PC para alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando o valor no topo da pilha, e verificando se o mesmo � maior ou igual a zero.
 * Se isso proceder, pc recebe pc+idx-3.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifge(FrameStack *fs);

/**
 * \brief Esta fun��o compara os dois valores do tipo refer�ncia no topo da pilha
 * de operandos, e produz o offset a partir do qual PC deve ser incrementado para
 * alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando as duas refer�ncias, e verificando se as mesmas s�o
 * iguais, caso elas sejam, pc recebe pc+idx-3. 
 * \param *fs O frame onde a opera��o � executada.
 */
void if_acmpeq(FrameStack *fs);

/**
 * \brief Esta fun��o compara os dois valores do tipo refer�ncia no topo da pilha
 * de operandos, e produz o offset a partir do qual PC deve ser incrementado para
 * alcan�ar a pr�xima instru��o.
 *
 * A fun��o opera desempilhando as duas refer�ncias, e verificando se as mesmas s�o
 * iguais, caso elas n�o sejam, pc recebe pc+idx-3. 
 * \param *fs O frame onde a opera��o � executada.
 */
void if_acmpne(FrameStack *fs);

/**
 * \brief Esta fun��o empilha o endere�o da pr�xima execu��o a ser executada e retorna
 * um deslocamento de 16 bits a ser somado a PC.
 *
 * A fun��o guarda o endere�o da pr�xima instru��o no topo da pilha de operandos,
 * depois atualiza o pc. O offset � de 16 bits.
 * \param *fs O ponteiro para o frame onde a instru��o � executada.
 */
void jsr (FrameStack *fs);

/**
 * \brief Esta fun��o empilha o endere�o da pr�xima execu��o a ser executada e retorna
 * um deslocamento de 32 bits a ser somado a PC.
 *
 * A fun��o guarda o endere�o da pr�xima instru��o no topo da pilha de operandos,
 * depois atualiza o pc. O offset � de 32 bits.
 * \param *fs O ponteiro para o frame onde a instru��o � executada.
 */
void jsr_w (FrameStack *fs);

/**
 * \brief Esta fun��o l� o novo ppc do vetor de vari�veis locais. 
 * \param *fs O ponteiro para o frame onde a instru��o � executada.
 */
void ret (FrameStack *fs);

/**
 * \brief Esta fun��o verifica se o valor no topo da pilha � uma refer�ncia nula,
 * e produz um offset a ser somado ao PC para alcan�ar a pr�xima instru��o a ser
 * executada.
 *
 * A fun��o opera retirando o valor do topo da pilha que servir� de �ndice
 * para o vetor de ponteiros. Depois verifica se o ponteiro aponta para NULL. Se ele
 * apontar para NULL, o pc � atualizado.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifnull(FrameStack *fs);

/**
 * \brief Esta fun��o verifica se o valor no topo da pilha � uma refer�ncia nula,
 * e produz um offset a ser somado ao PC para alcan�ar a pr�xima instru��o a ser
 * executada.
 *
 * A fun��o opera retirando o valor do topo da pilha que servir� de �ndice
 * para o vetor de ponteiros. Depois verifica se o ponteiro aponta para NULL. 
 * Se ele n�o apontar para NULL, o pc � atualizado.
 * \param *fs O frame onde a opera��o � executada.
 */
void ifnonull(FrameStack *fs);

/**
 * \brief Esta fun��o que executa o comando switch
 *
 * A fun��o possui tamanho varialvel com 0 a 3 bytes de preenchimento para que os
 * endereço de offset sejam multiplos de 4.
 * \param *fs O frame onde a opera��o � executada.
 */

void tableswitch (FrameStack *fs);

#endif
