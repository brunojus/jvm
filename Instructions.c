#include <stdio.h>
#include "FrameStack.h"
#include "Instructions.h"

void bipush(char valor, FrameStack *fs){
    int val = (int) valor;
    u4 v =0;
    v |= val;
    push_operand(v,&(fs->top->opStack));


}

void getstatic(FrameStack *fs){
    StaticAtrib *sa;
    long long natrib;
    int i,j;
    u2 idx,idx_class,idx_field;
    idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx = idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx_class = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.class_index].data.Class.name_index;
    idx_field = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.name_and_type_index].data.NameAndType.name_index;
    if (strcmp("out",(char *)fs->top->cPoolRunTime[idx_field].data.Utf8.bytes) || 
       strcmp("java/lang/System",(char *)fs->top->cPoolRunTime[idx_class].data.Utf8.bytes)){
        
        sa = getstaticAtrib((char *)fs->top->cPoolRunTime[idx_class].data.Utf8.bytes);
        natrib = getNAtribStatic((char *)fs->top->cPoolRunTime[idx_class].data.Utf8.bytes);
    
        for (i=0;i<natrib;i++){
    
        if (sa[i].name_index==idx_field){
        
            switch (sa[i].type){
                case (INTEGER):
                    push_operand(sa[i].data.staticInt,&(fs->top->opStack));
                    break;
          case (FLOAT):
                    push_operand(sa[i].data.staticFloat,&(fs->top->opStack));

                    break;
                case (STRING):
                    push_operand(sa[i].data.staticString.index_bytes,&(fs->top->opStack));

                    break;
        case (DOUBLE):
                    push_operand(sa[i].data.staticDouble.staticLowDouble,&(fs->top->opStack));
            push_operand(sa[i].data.staticDouble.staticHighDouble,&(fs->top->opStack));

                    break;
        case (LONG):
                    push_operand(sa[i].data.staticLong.staticLowLong,&(fs->top->opStack));
            push_operand(sa[i].data.staticLong.staticHighLong,&(fs->top->opStack));

                    break;
        case (REFERENCE_INTEGER):
        case (REFERENCE_STRING):
        case (REFERENCE_FLOAT):
        case (REFERENCE_DOUBLE):
        case (REFERENCE_LONG):
        case (REFERENCE_BYTE):
        case (REFERENCE_BOOLEAN):
        case (REFERENCE_CHAR):
        case (REFERENCE_SHORT):
            if (fs->top->countpoint==0){
                fs->top->pointers[fs->top->countpoint] = fs->top->pStaticAtrib[i].data.staticArray;
                push_operand((u4)fs->top->countpoint,&(fs->top->opStack));
                fs->top->countpoint++;
            }else{
                for (j=0;(j<fs->top->countpoint);j++){
                  if (fs->top->pointers[j] == fs->top->pStaticAtrib[i].data.staticArray){
                    push_operand((u4)j,&(fs->top->opStack));
                    break;
                    }
                 }
                 if (j==fs->top->countpoint){
                    fs->top->pointers[fs->top->countpoint] = fs->top->pStaticAtrib[i].data.staticArray;
                    push_operand((u4)fs->top->countpoint,&(fs->top->opStack));
                    fs->top->countpoint++;
                 }
                }
            
            break;
        
                    
        
                   
                }
            }

        }
    }
}

void putstatic(FrameStack *fs){
    int i;
    long long natrib;
    
    u2 idx =0;
    u2 idx_nome_class;
    u4 temp;
    u2 idx_attrib;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    
    idx_nome_class = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.class_index].data.Class.name_index;
    idx_attrib = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.name_and_type_index].data.NameAndType.name_index;

    natrib = getNAtribStatic((char *)fs->top->cPoolRunTime[idx_nome_class].data.Utf8.bytes);
    
    for (i=0;i<natrib;i++){
        if (fs->top->pStaticAtrib[i].name_index==idx_attrib){
        
            switch (fs->top->pStaticAtrib[i].type){
                case (INTEGER):
                    fs->top->pStaticAtrib[i].data.staticInt = pop_operand(&(fs->top->opStack));
			
                    break;
        case (FLOAT):
                    fs->top->pStaticAtrib[i].data.staticFloat = pop_operand(&(fs->top->opStack));

                    break;
        case (STRING):
                    idx=pop_operand(&(fs->top->opStack));

                    fs->top->pStaticAtrib[i].data.staticString.length = fs->top->cPoolRunTime[idx].data.Utf8.length;
                    fs->top->pStaticAtrib[i].data.staticString.staticString_bytes = fs->top->cPoolRunTime[idx].data.Utf8.bytes;
                    fs->top->pStaticAtrib[i].data.staticString.index_bytes=idx;
                    break;
        case (DOUBLE):

                    fs->top->pStaticAtrib[i].data.staticDouble.staticHighDouble = pop_operand(&(fs->top->opStack));
            fs->top->pStaticAtrib[i].data.staticDouble.staticLowDouble = pop_operand(&(fs->top->opStack));

                    break;
        case (LONG):
                    fs->top->pStaticAtrib[i].data.staticLong.staticHighLong = pop_operand(&(fs->top->opStack));
            fs->top->pStaticAtrib[i].data.staticLong.staticLowLong = pop_operand(&(fs->top->opStack));

                    break;
        case (REFERENCE_INTEGER):
        case (REFERENCE_STRING):
        case (REFERENCE_FLOAT):
        case (REFERENCE_DOUBLE):
        case (REFERENCE_LONG):
        case (REFERENCE_BYTE):
        case (REFERENCE_BOOLEAN):
        case (REFERENCE_CHAR):
        case (REFERENCE_SHORT):
            temp =pop_operand(&(fs->top->opStack));
                    fs->top->pStaticAtrib[i].data.staticArray =(arrayMult*) fs->top->pointers[temp];
            break;
            }
        }

    }
    
    

}

void ldc(FrameStack *fs){
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];

    switch (fs->top->cPoolRunTime[idx].tag){
        case(STRING):
            
            push_operand((u4) fs->top->cPoolRunTime[idx].data.String.string_index,&(fs->top->opStack));
        break;
        case(FLOAT):
            push_operand(fs->top->cPoolRunTime[idx].data.Float.bytes,&(fs->top->opStack));

        break;    
        case(INTEGER):
            push_operand(fs->top->cPoolRunTime[idx].data.Integer.bytes,&(fs->top->opStack));
            
        break;
    
    }
}

void ldc2(FrameStack *fs){
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx <<= 8;
    idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    switch (fs->top->cPoolRunTime[idx].tag){
        case(DOUBLE):
            push_operand(fs->top->cPoolRunTime[idx].data.Double.low_bytes,&(fs->top->opStack));
            push_operand(fs->top->cPoolRunTime[idx].data.Double.high_bytes,&(fs->top->opStack));
        
        break;
        case(LONG):
            push_operand(fs->top->cPoolRunTime[idx].data.Long.low_bytes,&(fs->top->opStack));
            push_operand(fs->top->cPoolRunTime[idx].data.Long.high_bytes,&(fs->top->opStack));
        break;    
        
    }
}


/*-------------------------coisas de int------------------------*/
void iconst(u4 val, FrameStack *fs ){
    push_operand(val,&(fs->top->opStack));
}

void istoren(u4 val,FrameStack *fs){
    fs->top->LocalVariables[val] = pop_operand(&(fs->top->opStack));


}

void iloadn(u4 val, FrameStack *fs ){
    push_operand(fs->top->LocalVariables[val],&(fs->top->opStack));
    
}

void iload(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->LocalVariables[idx],&(fs->top->opStack));
}

void istore(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->LocalVariables[idx] = pop_operand(&(fs->top->opStack));
}

void imul(FrameStack *fs){
    u4 op1 =pop_operand(&(fs->top->opStack));
    u4 op2 =pop_operand(&(fs->top->opStack));
    push_operand(op2*op1,&(fs->top->opStack));

}

void iadd(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op2+op1,&(fs->top->opStack));
    
}

void isub(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op2-op1,&(fs->top->opStack));

}

void idiv(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));    
    u4 res = op2/op1;
    push_operand(res,&(fs->top->opStack));

}

void iand(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op1 & op2,&(fs->top->opStack));

}

void ineg(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 res = -op1;
    push_operand(res,&(fs->top->opStack));
   
}

void ior(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op2 | op1,&(fs->top->opStack));

}

void ixor(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op2 ^ op1,&(fs->top->opStack));

}

void irem(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 res = op2%op1;
    push_operand(res,&(fs->top->opStack));
    
}

void ishl(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    op1 &= 0x0000001f;
    op2 <<= op1;
    push_operand(op2,&(fs->top->opStack));    
}

void ishr(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    op1 &= 0x0000001f;
    op2 >>= op1;
    push_operand(op2,&(fs->top->opStack));    
}

void iushr(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    op1 &= 0x0000001f;
    if((signed int)op2 >= 0){
        op2 >>= op1;
    }else{
        op2 = (op2>>op1)+(2<<(~op1));
    }
    push_operand(op2,&(fs->top->opStack)); 
}

void i2f(FrameStack *fs){
    float f;
    int t;
    t =(int)  pop_operand(&(fs->top->opStack));
    f = (float) t;
    memmove(&t,&f,sizeof(float));
    push_operand( t,&(fs->top->opStack)); 
}

void ireturn(FrameStack *fs){
    u4 temp =pop_operand(&(fs->top->opStack));
    push_operand(temp,&(fs->top->next->opStack));
    fs->top->pc = fs->top->method->attributes->data.Code_attribute.code_length;
}

void if_icmpge(FrameStack *fs){
    u2 idx =0;
    int op1;
    int op2;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 = (int) pop_operand(&(fs->top->opStack));
    op1 = (int) pop_operand(&(fs->top->opStack));

    if (op1>=op2){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void if_icmplt(FrameStack *fs){
    u2 idx =0;
    u4 op1;
    u4 op2;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 = pop_operand(&(fs->top->opStack));
    op1 = pop_operand(&(fs->top->opStack));

    if ((int)op1<(int)op2){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}

void if_icmpeq(FrameStack *fs){
    u2 idx =0;
    u4 op1;
    u4 op2;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 = pop_operand(&(fs->top->opStack));
    op1 = pop_operand(&(fs->top->opStack));

    if ((int)op1==(int)op2){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void if_icmpne(FrameStack *fs){
    u2 idx =0;
    u4 op1;
    u4 op2;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 =(int) pop_operand(&(fs->top->opStack));
    op1 =(int) pop_operand(&(fs->top->opStack));

    if (op1!=op2){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void if_icmpgt(FrameStack *fs){
    u2 idx =0;
    u4 op1;
    u4 op2;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 =(int) pop_operand(&(fs->top->opStack));
    op1 = (int) pop_operand(&(fs->top->opStack));
    if (op1>op2){
        fs->top->pc=fs->top->pc+(signed short)idx-3;
    }
}
void if_icmple(FrameStack *fs){
    u2 idx =0;
    u4 op1;
    u4 op2;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 = pop_operand(&(fs->top->opStack));
    op1 = pop_operand(&(fs->top->opStack));

    if ((int)op1<=(int)op2){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void iinc(FrameStack *fs){
    u4 idx;
    idx = 0 | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    char conts = 0 | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->LocalVariables[idx] = fs->top->LocalVariables[idx] + (int)conts;
}


/*----------------------coisas do long long-----------------------------------------------------*/
void lconstn(long val1, FrameStack *fs ){
    u4 aux[2];
    memmove(aux,&val1,sizeof(long));
    push_operand(aux[0] ,&(fs->top->opStack));
    push_operand(aux[1],&(fs->top->opStack));
}

void lstoren(u4 val,FrameStack *fs){
    fs->top->LocalVariables[val+1] = pop_operand(&(fs->top->opStack));
    fs->top->LocalVariables[val] = pop_operand(&(fs->top->opStack));
}

void lloadn(u4 val, FrameStack *fs ){
    push_operand(fs->top->LocalVariables[val],&(fs->top->opStack));
    push_operand(fs->top->LocalVariables[val+1],&(fs->top->opStack));
}

void lload(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->LocalVariables[idx],&(fs->top->opStack));
    push_operand(fs->top->LocalVariables[idx+1],&(fs->top->opStack));
}

void lstore(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->LocalVariables[idx+1] = pop_operand(&(fs->top->opStack));
    fs->top->LocalVariables[idx] = pop_operand(&(fs->top->opStack));
}

void ladd(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;     
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));    
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num1 + num2;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));    
}

void lsub(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;     
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));    
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2 - num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));    
}

void lldiv_(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2/num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));   
}

void lrem(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2%num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));   
}

void lmul(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2*num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));
}

void lneg(FrameStack *fs){
    u4 op1[2], resultado[2];
    long long num = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    memmove(&num,&op1,SIZE_DOUBLE);    
    res = -num;
    memmove(&resultado,&res,SIZE_DOUBLE);
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));     
}

void land(FrameStack *fs){
     u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2&num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));
}

void lor(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2|num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));
}

void lxor(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    long long num1 = 0;
    long long num2 = 0;
    long long res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2^num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));
}

void lshl(FrameStack *fs){
    u4 op2[2], op1=0, resultado[2];
    long long num1 = 0;
    op1 = pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op2,SIZE_DOUBLE);
    op1 &= 0x0000003f;
    num1 <<= op1;
    memmove(&resultado,&num1,SIZE_DOUBLE); 
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));   
}

void lshr(FrameStack *fs){
    u4 op2[2], op1=0, resultado[2];
    long long num1 = 0;
    op1 = pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op2,SIZE_DOUBLE);
    op1 &= 0x0000003f;
    num1 >>= op1;
    memmove(&resultado,&num1,SIZE_DOUBLE); 
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack)); 
}

void lushr(FrameStack *fs){
    u4 op2[2], op1, resultado[2];
    long long num1 = 0;
    op1 = pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op2,SIZE_DOUBLE);
    op1 &= 0x0000003f;
    if((signed int)op1 >= 0){
        num1 >>= op1;
    }else{
        num1 = (num1>op1)+(2<<(~op1));
    }
    memmove(&resultado,&num1,SIZE_DOUBLE); 
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack)); 
}

void lreturn(FrameStack *fs){
    u4 temp1,temp2;
    temp1= pop_operand(&(fs->top->opStack));
    temp2 =pop_operand(&(fs->top->opStack));
    push_operand(temp2,&(fs->top->next->opStack));
    push_operand(temp1,&(fs->top->next->opStack));
    fs->top->pc = fs->top->method->attributes->data.Code_attribute.code_length;
}

void l2d(FrameStack *fs){
    u4 val[2];
    long long tmp;
    val[1] = pop_operand(&(fs->top->opStack));
    val[0] = pop_operand(&(fs->top->opStack));
    memmove(&tmp,val,sizeof(tmp));
    double val2 = (double) tmp;
    u4 temp[2];
    memmove(&temp,&val2,sizeof(val2));
    push_operand(temp[0],&(fs->top->opStack));
    push_operand(temp[1],&(fs->top->opStack));
    
}

void l2f(FrameStack *fs){
    u4 val[2];
    long long tmp;
    val[1] = pop_operand(&(fs->top->opStack));
    val[0] = pop_operand(&(fs->top->opStack));
    memmove(&tmp,val,sizeof(tmp));
    float val2 = (float) tmp;
    u4 resultado;
    memmove(&resultado, &val2, sizeof(float));
    push_operand(resultado,&(fs->top->opStack));
}

void l2i(FrameStack *fs){
    u4 val[2];
    long long tmp;
    val[1] = pop_operand(&(fs->top->opStack));
    val[0] = pop_operand(&(fs->top->opStack));
    memmove(&tmp,val,sizeof(tmp));
    int val2 = (int) tmp;
    u4 resultado = (u4) val2;
    push_operand(resultado,&(fs->top->opStack));
}

void lcmp(FrameStack *fs){
    u4 val1[2];
    long long tmp1;
    val1[1] = pop_operand(&(fs->top->opStack));
    val1[0] = pop_operand(&(fs->top->opStack));
    memmove(&tmp1,val1,sizeof(tmp1));
    u4 val2[2];
    long long tmp2;
    val2[1] = pop_operand(&(fs->top->opStack));
    val2[0] = pop_operand(&(fs->top->opStack));
    memmove(&tmp2,val2,sizeof(tmp2));
    int ret;
    if(tmp2 > tmp1) ret = 1;
    else if(tmp2 == tmp1) ret = 0;
    else if(tmp2 < tmp1) ret = -1;
    push_operand((u4)ret,&(fs->top->opStack));
}


/*-------------------------------------coisas do double-------------------------------*/
void dconstn(double val1, FrameStack *fs ){
    u4 aux[2];
    memmove(aux,&val1,sizeof(double));
    push_operand(aux[0],&(fs->top->opStack));
    push_operand(aux[1],&(fs->top->opStack));

}

void dstoren(u4 val,FrameStack *fs){
    fs->top->LocalVariables[val+1] = pop_operand(&(fs->top->opStack));
    fs->top->LocalVariables[val] = pop_operand(&(fs->top->opStack));
}

void dloadn(u4 val, FrameStack *fs ){
    push_operand(fs->top->LocalVariables[val],&(fs->top->opStack));
    push_operand(fs->top->LocalVariables[val+1],&(fs->top->opStack));
}

void dload(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->LocalVariables[idx],&(fs->top->opStack));
    push_operand(fs->top->LocalVariables[idx+1],&(fs->top->opStack));
}

void dstore(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->LocalVariables[idx+1] = pop_operand(&(fs->top->opStack));
    fs->top->LocalVariables[idx] = pop_operand(&(fs->top->opStack));
    
}

void dadd(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    double num1 = 0;
    double num2 = 0;
    double res;     
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));    
    memmove(&num1,&op1,sizeof(double));
    memmove(&num2,&op2,sizeof(double));
    res = num1 + num2;
    memmove(&resultado,&res,sizeof(double));    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));    
}

void dsub(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    double num1 = 0;
    double num2 = 0;
    double res;     
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));    
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2 - num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));    
}

void ddiv(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    double num1 = 0;
    double num2 = 0;
    double res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2/num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));   
}

void dRem(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    double num1 = 0;
    double num2 = 0;
    double res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = fmod(num2,num1);
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));   
}

void dmul(FrameStack *fs){
    u4 op1[2], op2[2], resultado[2];
    double num1 = 0;
    double num2 = 0;
    double res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);
    res = num2*num1;
    memmove(&resultado,&res,SIZE_DOUBLE);    
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));
}

void dneg(FrameStack *fs){
    u4 op1[2], resultado[2];
    double num = 0;
    double res;    
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    memmove(&num,&op1,SIZE_DOUBLE);    
    res = -num;

    memmove(&resultado,&res,SIZE_DOUBLE);
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));     
}

void dreturn(FrameStack *fs){
    u4 temp1, temp2;
    temp1 = pop_operand(&(fs->top->opStack));
    temp2 =pop_operand(&(fs->top->opStack));
    push_operand(temp2,&(fs->top->next->opStack));
    push_operand(temp1,&(fs->top->next->opStack));
    fs->top->pc = fs->top->method->attributes->data.Code_attribute.code_length;
}

void d2l(FrameStack *fs){
    u4 op1[2], resultado[2];
    long long res;
    double val;
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    val = 0;
    memmove(&val,&op1,SIZE_DOUBLE);
    res = (long long) val;
    memmove(&resultado,&res,SIZE_DOUBLE);
    push_operand(resultado[0],&(fs->top->opStack));
    push_operand(resultado[1],&(fs->top->opStack));
}

void d2f(FrameStack *fs){
    u4 op1[2], resultado;
    double val;
    float result;
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    val = 0;
    memmove(&val,&op1,SIZE_DOUBLE);
    result= (float) val;
    memmove(&resultado, &result, sizeof(float));
    push_operand(resultado,&(fs->top->opStack));
}

void d2i(FrameStack *fs){
    u4 op1[2], resultado;
    int val2;
    double val;
    op1[1] =pop_operand(&(fs->top->opStack));
    op1[0] =pop_operand(&(fs->top->opStack));
    val = 0;
    memmove(&val,&op1,SIZE_DOUBLE);
    val2 = (int) val;
    resultado = (u4) val2;
    push_operand(resultado,&(fs->top->opStack));
}

void dcmpl(FrameStack *fs){
    u4 op1[2], op2[2];
    int ret;
    double num1 = 0;
    double num2 = 0;

    op1[0] =pop_operand(&(fs->top->opStack));
    op1[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);    
    if(num2>num1){
         ret = 1;                       
    }else if(num2<num1){
         ret = -1;                    
    }else{
         ret = 0;          
    }
    push_operand(ret,&(fs->top->opStack));     
}
void dcmpg(FrameStack *fs){
    u4 op1[2], op2[2];
    int ret;
    double num1 = 0;
    double num2 = 0;

    op1[0] =pop_operand(&(fs->top->opStack));
    op1[1] =pop_operand(&(fs->top->opStack));
    op2[0] =pop_operand(&(fs->top->opStack));
    op2[1] =pop_operand(&(fs->top->opStack));
    memmove(&num1,&op1,SIZE_DOUBLE);
    memmove(&num2,&op2,SIZE_DOUBLE);    
    if(num2>num1){
         ret = 1;                       
    }else if(num2<num1){
         ret = -1;                    
    }else{
         ret = 0;          
    }
    push_operand(ret,&(fs->top->opStack));     
}
/*--------------------dups*/

void dup(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
 
}

void dupx1(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
   
}

void dupx2_1(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op3 = pop_operand(&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op3,&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
  
}

void dupx2_2(FrameStack *fs){
     dupx1(fs);
}

void dup2(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    
}

void dup2x1_1(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op3 = pop_operand(&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op3,&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));    
}

void dup2x1_2(FrameStack *fs){
    dupx1(fs);
}

void dup2x2_1(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op3 = pop_operand(&(fs->top->opStack));
    u4 op4 = pop_operand(&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op4,&(fs->top->opStack));
    push_operand(op3,&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));    
}

void dup2x2_2(FrameStack *fs){
    u4 op1 = pop_operand(&(fs->top->opStack));
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op3 = pop_operand(&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));
    push_operand(op3,&(fs->top->opStack));
    push_operand(op2,&(fs->top->opStack));
    push_operand(op1,&(fs->top->opStack));    
}

void dup2x2_3(FrameStack *fs){
    dup2x1_1(fs);
}

void dup2x2_4(FrameStack *fs){
    dupx1(fs);
}



void Goto(FrameStack *fs){
    u2 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->pc = fs->top->pc + (signed short) idx - 3;
    

}
void newarray(FrameStack *fs){
    u4 tam = pop_operand(&(fs->top->opStack));
    u1 tipo = 0;
    int* pInt;
    char* pBoolean;
    char* pByte; 
    float* pFloat;
    double* pDouble;
    unsigned short* pUShort;
    short* pShort;
    long long* pLong; 
    tipo = tipo | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    switch (tipo){
        case (4):/* BOOLEAN */
            pBoolean = (char *) malloc(tam*sizeof(char));
            fs->top->pointers[fs->top->countpoint] = (void *) pBoolean;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;

        break;
        case (5):/* CHAR */
            pUShort = (unsigned short *) malloc((tam+1)*sizeof(unsigned short));
	    pUShort[tam] =0; /*Adequa��o para imprimir em ascii os caracteres unicode, 0 terminador de string*/ 
            fs->top->pointers[fs->top->countpoint] = (void *) pUShort;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;
            
        break;
        case (6):/* FLOAT */
            pFloat = (float *) malloc(tam*sizeof(float));
            fs->top->pointers[fs->top->countpoint] = (void *) pFloat;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;

        break;
        case (7):/* DOUBLE */
            pDouble = (double *) malloc(tam*sizeof(double));
            fs->top->pointers[fs->top->countpoint] = (void *) pDouble;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;

        break;
        case (8):/* BYTE */
            pByte = (char *) malloc(tam*sizeof(char));
            fs->top->pointers[fs->top->countpoint] = (void *) pByte;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;

        break;
        case (9):/* SHORT */
            pShort = (short *) malloc(tam*sizeof(short));
            fs->top->pointers[fs->top->countpoint] = (void *) pShort;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;

        break;
        case (10):/* INT */
            
            pInt = (int *) malloc(tam*sizeof(int));
            fs->top->pointers[fs->top->countpoint] = (void *) pInt;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;
            
        break;
        case (11):/* LONG */
            pLong = (long long *) malloc(tam*sizeof(long long));
            fs->top->pointers[fs->top->countpoint] = (void *) pLong;
            push_operand(fs->top->countpoint,&(fs->top->opStack));
            fs->top->countpoint++;

        break;
    
    
    
    
    
    
    }
}


void astore(FrameStack *fs){
    u1 idx =0 ;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->LocalVariables[idx] = pop_operand(&(fs->top->opStack));
}
void astoren(u1 val, FrameStack *fs){
    
    fs->top->LocalVariables[val] = pop_operand(&(fs->top->opStack));
}


void aload(FrameStack *fs){
    u1 idx =0 ;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->LocalVariables[idx],&(fs->top->opStack));
}

void aloadn(u4 val, FrameStack *fs){
    push_operand(fs->top->LocalVariables[val],&(fs->top->opStack));
}

void iastore(FrameStack *fs){
    
    u4 value;
    u4 index;
    u4 reference;
    arrayMult* pInt;
    int* temp;
    value = pop_operand(&(fs->top->opStack));/*valor em questao*/
    index = pop_operand(&(fs->top->opStack));/*posicao no array*/
    reference = pop_operand(&(fs->top->opStack));/*referencia ao array*/

    if ((int)reference<0){/*se referencia for negativa(multiarray)*/
        pInt = (arrayMult *) fs->top->tempMultArray;
        temp = (int*)pInt->ptr[index];
        *temp =(int) value;
        
    }else{/*sen�o(array normal)*/
        int* p = (int *) fs->top->pointers[reference];
        p[index]=(int) value;
    }
}
void iaload(FrameStack *fs){
    
    u4 index;
    u4 reference;
    u4 toreturn;
    arrayMult* pInt;
    int *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pInt = (arrayMult *) fs->top->tempMultArray;
        
        push_operand((u4)*((int*)pInt->ptr[index]),&(fs->top->opStack));
    }else{    
        p =(int *) fs->top->pointers[reference];
        memmove(&toreturn,&p[index], sizeof(u4));
        push_operand(toreturn,&(fs->top->opStack));
    }
}

void fastore(FrameStack *fs){
    
    u4 value;
    u4 index;
    u4 reference;
    arrayMult* pFloat;
    float* temp;
    value = pop_operand(&(fs->top->opStack));
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));

    if ((int)reference<0){
        pFloat = (arrayMult *) fs->top->tempMultArray;
        temp = (float*)pFloat->ptr[index];
        memmove(temp, &value, sizeof(float));/*aqui usa memmove porcausa do padrao IEEE*/
        
    }else{
        float* p = (float *) fs->top->pointers[reference];
        memmove(&(p[index]), &value,sizeof(float));
    }


}

void faload(FrameStack *fs){
    u4 index;
    u4 reference;
    u4 toreturn;
    arrayMult* pFloat;
    float *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pFloat = (arrayMult *) fs->top->tempMultArray;
        memmove(&toreturn,pFloat->ptr[index],sizeof(u4));
    }else{    
        p =(float *) fs->top->pointers[reference];
        memmove(&toreturn,&p[index], sizeof(u4));
    }
    push_operand(toreturn,&(fs->top->opStack));
}

void bastore(FrameStack *fs){
    
    u4 value;
    u4 index;
    u4 reference;
    arrayMult* pByte;
    char* temp;
    value = pop_operand(&(fs->top->opStack));
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pByte = (arrayMult *) fs->top->tempMultArray;
        temp = (char*)pByte->ptr[index];
        *temp =(char) value;
        
    }else{
        char* p = (char *) fs->top->pointers[reference];
        p[index]=(char) value;
    }



}

void baload(FrameStack *fs){
    u4 index;
    u4 reference;
    int toreturn=0;
    arrayMult* pByte;
    char *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pByte = (arrayMult *) fs->top->tempMultArray;
        
        push_operand((u4)*((char*)pByte->ptr[index]),&(fs->top->opStack));
    }else{    
        p =(char *) fs->top->pointers[reference];
        toreturn = (int) p[index];
        push_operand((u4)toreturn,&(fs->top->opStack));
    }
}

void castore(FrameStack *fs){
    
    u4 value;
    u4 index;
    u4 reference;
    arrayMult* pChar;
    unsigned short* temp;
    value = pop_operand(&(fs->top->opStack));
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));

    if ((int)reference<0){
        pChar = (arrayMult *) fs->top->tempMultArray;
        temp = (unsigned short*)pChar->ptr[index];
        *temp =(unsigned short) value;
        
    }else{
        unsigned short* p = (unsigned short *) fs->top->pointers[reference];
        p[index]=(unsigned short) value;
    }



}

void caload(FrameStack *fs){
    u4 index;
    u4 reference;
    u4 toreturn=0;
    arrayMult* pChar;
    unsigned short *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pChar = (arrayMult *) fs->top->tempMultArray;
        
        push_operand((u4)*((unsigned short*)pChar->ptr[index]),&(fs->top->opStack));
    }else{    
        p =(unsigned short *) fs->top->pointers[reference];
        memmove(&toreturn,&p[index], sizeof(unsigned short));
        push_operand(toreturn,&(fs->top->opStack));
    }
}


void sastore(FrameStack *fs){
    
    u4 value;
    u4 index;
    u4 reference;
    arrayMult* pShort;
    short* temp;
    value = pop_operand(&(fs->top->opStack));
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));

    if ((int)reference<0){
        pShort = (arrayMult *) fs->top->tempMultArray;
        temp = (short*)pShort->ptr[index];
        *temp =(short) value;
        
    }else{
        short* p = (short *) fs->top->pointers[reference];
        p[index]=(short) value;
    }



}

void saload(FrameStack *fs){
    u4 index;
    u4 reference;
    int tmp;
    arrayMult* pShort;
    short *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pShort = (arrayMult *) fs->top->tempMultArray;
        
        push_operand((u4)*((short*)pShort->ptr[index]),&(fs->top->opStack));
    }else{    
        p =(short *) fs->top->pointers[reference];
        tmp = (int)p[index];
        push_operand((u4)tmp,&(fs->top->opStack));
    }
}


void dastore(FrameStack *fs){

    u4 value[2];
    u4 index;
    u4 reference;
    arrayMult* pDouble;
    double* temp;
    value[1] = pop_operand(&(fs->top->opStack));
    value[0] = pop_operand(&(fs->top->opStack));
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pDouble = (arrayMult *) fs->top->tempMultArray;
        temp = (double*)pDouble->ptr[index];
        memmove(temp, &value,sizeof(double));
        
    }else{
        double* p = (double *) fs->top->pointers[reference];
        memmove(&(p[index]), &value,sizeof(double));
    }


}


void daload(FrameStack *fs){

    u4 index;
    u4 reference;
    u4 toreturn[2];
    arrayMult* pDouble;
    double *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pDouble = (arrayMult *) fs->top->tempMultArray;
        memmove(&toreturn, pDouble->ptr[index], sizeof(double));
    }else{    
        p =(double *) fs->top->pointers[reference];
        memmove(&toreturn,&p[index], sizeof(double));
    }
    push_operand(toreturn[0],&(fs->top->opStack));
    push_operand(toreturn[1],&(fs->top->opStack));

}

void lastore(FrameStack *fs){
    
    u4 value[2];
    u4 index;
    u4 reference;
    arrayMult* pLong;
    long long* temp;
    value[1] = pop_operand(&(fs->top->opStack));
    value[0] = pop_operand(&(fs->top->opStack));
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pLong = (arrayMult *) fs->top->tempMultArray;
        temp = (long long*)pLong->ptr[index];
        memmove(temp, &value,sizeof(long long));
        
    }else{
        long long* p = (long long *) fs->top->pointers[reference];
        memmove(&(p[index]), &value,sizeof(long long));
    }



}

void laload(FrameStack *fs){
    u4 index;
    u4 reference;
    u4 toreturn[2];
    arrayMult* pLong;
    long long *p;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    if ((int)reference<0){
        pLong = (arrayMult *) fs->top->tempMultArray;
        memmove(&toreturn, pLong->ptr[index], sizeof(long long));
    }else{    
        p =(long long *) fs->top->pointers[reference];
        memmove(&toreturn,&p[index], sizeof(long long));
    }
    push_operand(toreturn[0],&(fs->top->opStack));
    push_operand(toreturn[1],&(fs->top->opStack));
}


void aaload(FrameStack *fs){
    u4 index;
    u4 reference;
    arrayMult* pt;
    index = pop_operand(&(fs->top->opStack));
    reference = pop_operand(&(fs->top->opStack));
    arrayMult* dimen;
    if((int)reference >=0){
        pt= (arrayMult*)fs->top->pointers[reference];
        fs->top->tempMultArray =(void*) ReduceDimension(pt,index);
        push_operand((u4)-1,&(fs->top->opStack));
        
    }else{
        dimen =(arrayMult*) fs->top->tempMultArray;
        fs->top->tempMultArray =(void*) ReduceDimension((arrayMult*)fs->top->tempMultArray,index);
        free(dimen->dimensions);
        free(dimen->ptr);
        free(dimen);
        push_operand((u4)-1,&(fs->top->opStack));
    }
}
void fconstn(u4 val,FrameStack *fs) {
    float f;
    f = (float) val;
    memmove(&val,&f,sizeof(float));
    push_operand(val,&(fs->top->opStack));
}


void fadd(FrameStack *fs) {

    float value1,value2,temp = 0.0;
    u4 res = 0;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,sizeof(value1));
    memmove(&value2,&op2,sizeof(value2));
    temp = value1 + value2;
    memmove(&res,&temp,sizeof(res));
    push_operand(res,&(fs->top->opStack));
    

}

void fsub(FrameStack *fs) {

    float value1,value2,temp = 0.0;
    u4 res = 0;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,4);
    memmove(&value2,&op2,4);
    temp = value1 - value2;
    memmove(&res,&temp,4);
    push_operand(res,&(fs->top->opStack));

}
void fmul(FrameStack *fs) {

    float value1,value2,temp = 0.0;
    u4 res = 0;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,4);
    memmove(&value2,&op2,4);
    temp = value1 * value2;
    memmove(&res,&temp,4);
    push_operand(res,&(fs->top->opStack));

}

void fdiv(FrameStack *fs) {

    float value1,value2,temp = 0.0;
    u4 res = 0;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,4);
    memmove(&value2,&op2,4);
    temp = value1 / value2;
    memmove(&res,&temp,4);
    push_operand(res,&(fs->top->opStack));

}

void frem(FrameStack *fs) {

    float value1,value2,temp = 0.0;
    u4 res,quo = 0;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,4);
    memmove(&value2,&op2,4);
    quo = (int) quociente(value1,value2);
    temp = (value1 - (value2 * quo));
    memmove(&res,&temp,4);
    push_operand(res,&(fs->top->opStack));

}

void fneg(FrameStack *fs) {

    u4 res = 0;
    u4 op1 = pop_operand(&(fs->top->opStack));
    float temp = 0.0;
    memmove(&temp,&op1,4);
    temp = temp*-1;
    memmove(&res,&temp,4);
    push_operand(res,&(fs->top->opStack));
}


void fload(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->LocalVariables[idx],&(fs->top->opStack));
}

void fstore(FrameStack *fs ){
    u1 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->LocalVariables[idx] = pop_operand(&(fs->top->opStack));
}

void floadn(u4 val, FrameStack *fs) {

    push_operand(fs->top->LocalVariables[val],&(fs->top->opStack));

}

void freturn(FrameStack *fs){
    u4 temp = pop_operand(&(fs->top->opStack));
    push_operand(temp,&(fs->top->next->opStack));
    fs->top->pc = fs->top->method->attributes->data.Code_attribute.code_length;
    
}

void fstoren(u4 val,FrameStack *fs){
    fs->top->LocalVariables[val] = pop_operand(&(fs->top->opStack));

}

void fcmpg(FrameStack *fs) {

    float value1,value2 = 0.0;
    int res;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,4);
    memmove(&value2,&op2,4);

    if (value1 > value2) res =1; 
    else if (value1 == value2) res = 0;
    else if (value1 < value2) res = -1;
    push_operand((u4)res,&(fs->top->opStack));

}

void fcmpl(FrameStack *fs) {

    float value1,value2 = 0.0;
    int res;
    u4 op2 = pop_operand(&(fs->top->opStack));
    u4 op1 = pop_operand(&(fs->top->opStack));
    memmove(&value1,&op1,4);
    memmove(&value2,&op2,4);

    if (value1 > value2) res =1; 
    else if (value1 == value2) res = 0;
    else if (value1 < value2) res = -1;
    push_operand((u4)res,&(fs->top->opStack));
}

void pop2(FrameStack *fs){
    pop_operand(&(fs->top->opStack));
    pop_operand(&(fs->top->opStack));
}

void pop(FrameStack *fs){
    pop_operand(&(fs->top->opStack));
}


void sipush(FrameStack *fs){
    short temp;
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
        idx <<= 8;
        idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    temp = (short) idx;
    push_operand((u4)temp,&(fs->top->opStack));

}

void swap(FrameStack *fs){
    u4 temp1, temp2;
    temp1=pop_operand(&(fs->top->opStack));
    temp2 =pop_operand(&(fs->top->opStack));;
    push_operand(temp1,&(fs->top->opStack));
    push_operand(temp2,&(fs->top->opStack));
}

int acharTipoArray(char *descritor){
    char c;
    c = descritor[strlen(descritor)];
    
    switch(c){
        case 'Z':
            return REFERENCE_BOOLEAN;    
        case 'C':
            return REFERENCE_CHAR;
        case 'F':
            return REFERENCE_FLOAT;
        case 'D':
            return REFERENCE_DOUBLE;
        case 'B':
            return REFERENCE_BYTE;
        case 'S':
            return REFERENCE_SHORT;
        case 'I':
            return REFERENCE_INTEGER;
        case 'J':
            return REFERENCE_LONG;
        default:
            printf("** Erro na leitura do tipo do descritor **\n");
            exit(1);
    }
}



void anewarray(FrameStack *fs){
    int count = pop_operand(&(fs->top->opStack));
    int i;
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
        idx <<= 8;
        idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    /*u1 tipo = 0;*/
    int* pInt;
    char* ptByte;
    float* ptFloat;
    u2* ptChar;
    short* ptShort;
    double* ptDouble;
    long long* ptLong;
    arrayMult *dimen;
    /*tipo = tipo | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];*/
    int tipo;
    tipo  = acharTipoArray((char*)fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Class.name_index].data.Utf8.bytes);
    
    dimen = (void *) calloc(count, sizeof(void*));
    switch(tipo){
            case REFERENCE_BOOLEAN:
            case REFERENCE_BYTE:
                ptByte = (char*) calloc(count, sizeof(char));/*alocacao de espaco para o array*/
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(ptByte[i]);/*passagem dos valores para o espaco alocado*/

                }dimen->values = (void*)ptByte;/*atualiza o ponteiro para esse espaco alocado*/
            break;
            case REFERENCE_CHAR:
                ptChar = (u2*) calloc(count, sizeof(u2));
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(ptChar[i]);

                }dimen->values = (void*)ptChar;
            break;
            case REFERENCE_FLOAT:
                ptFloat = (float*) calloc(count, sizeof(float));
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(ptFloat[i]);

                }dimen->values = (void*)ptFloat;
            break;
            case REFERENCE_SHORT:
                ptShort = (short*) calloc(count, sizeof(short));
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(ptShort[i]);

                }dimen->values = (void*)ptShort;
            break;
            case REFERENCE_INTEGER:
                pInt = (int*) calloc(count, sizeof(int));
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(pInt[i]);

                }dimen->values = (void*)pInt;
            break;
            case REFERENCE_DOUBLE:
                ptDouble = (double*) calloc(count, sizeof(double));
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(ptDouble[i]);

                }dimen->values = (void*)ptDouble;
            break;
            case REFERENCE_LONG:
                ptLong = (long long*) calloc(count, sizeof(long long));
                for(i=0 ; i<count; i++){
                    dimen->ptr[i] = (void*) &(ptLong[i]);

                }dimen->values = (void*)ptLong;
            break;
        }

    
    fs->top->pointers[fs->top->countpoint] =(void *) dimen;
    push_operand(fs->top->countpoint,&(fs->top->opStack));

    fs->top->countpoint++;
}




void multianewarray(FrameStack *fs){
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
        idx <<= 8;
        idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    u1 dim = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    int i;
    int tipo;
    /*Ponteiros para os tipos*/
    int* pInt;
    char* ptByte;
    float* ptFloat;
    u2* ptChar;
    short* ptShort;
    double* ptDouble;
    long long* ptLong;

    u4 dimensTotal=1;
    arrayMult *dimen = (arrayMult*) malloc(sizeof(arrayMult));
    dimen->dimensions_count=dim;
    dimen->dimensions = (u2 *) malloc(sizeof(u2)*dim);
    
    for (i=dim-1;i>=0;i++){
        dimen->dimensions[i] = pop_operand(&(fs->top->opStack));
        dimensTotal *= dimen->dimensions[i];
    }
    tipo  = acharTipoArray((char*)fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Class.name_index].data.Utf8.bytes);
    dimen->ptr = (void **) calloc(dimensTotal, sizeof(void*));
    switch(tipo){
            case REFERENCE_BOOLEAN:
            case REFERENCE_BYTE:
                ptByte = (char*) calloc(dimensTotal, sizeof(char));/*alocacao de espaco para o array*/
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(ptByte[i]);/*passagem dos valores para o espa�o alocado*/

                }dimen->values = (void*)ptByte;/*atualiza o ponteiro para esse espaco alocado*/
            break;
            case REFERENCE_CHAR:
                ptChar = (u2*) calloc(dimensTotal, sizeof(u2));
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(ptChar[i]);

                }dimen->values = (void*)ptChar;
            break;
            case REFERENCE_FLOAT:
                ptFloat = (float*) calloc(dimensTotal, sizeof(float));
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(ptFloat[i]);

                }dimen->values = (void*)ptFloat;
            break;
            case REFERENCE_SHORT:
                ptShort = (short*) calloc(dimensTotal, sizeof(short));
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(ptShort[i]);

                }dimen->values = (void*)ptShort;
            break;
            case REFERENCE_INTEGER:
                pInt = (int*) calloc(dimensTotal, sizeof(int));
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(pInt[i]);

                }dimen->values = (void*)pInt;
            break;
            case REFERENCE_DOUBLE:
                ptDouble = (double*) calloc(dimensTotal, sizeof(double));
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(ptDouble[i]);

                }dimen->values = (void*)ptDouble;
            break;
            case REFERENCE_LONG:
                ptLong = (long long*) calloc(dimensTotal, sizeof(long long));
                for(i=0 ; i<dimensTotal; i++){
                    dimen->ptr[i] = (void*) &(ptLong[i]);

                }dimen->values = (void*)ptLong;
            break;
        }

    
    fs->top->pointers[fs->top->countpoint] =(void *) dimen;
    push_operand(fs->top->countpoint,&(fs->top->opStack));

    fs->top->countpoint++;
}

arrayMult *ReduceDimension(arrayMult *dimen, u4 qualpos){
    u4 index=1;
    u4 i,k;
    arrayMult *newdimen = (arrayMult*) malloc(sizeof(arrayMult));
    newdimen->dimensions_count = dimen->dimensions_count-1;
    newdimen->dimensions = (u2*) calloc(newdimen->dimensions_count,sizeof(u2));

    for(i=1;i<dimen->dimensions_count;i++){
        index *= dimen->dimensions[i];

        newdimen->dimensions[i-1] = dimen->dimensions[i];
    }
    
    newdimen->ptr = (void**) calloc(index,sizeof(void*));
    newdimen->values = dimen->values;

    for(i=index*qualpos, k=0; i<(index*qualpos)+index; i++,k++){
        newdimen->ptr[k] =(void*) dimen->ptr[i];

    }

    return newdimen;
} 

void newObj(FrameStack *fs){
    Object* obj;
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
        idx <<= 8;
        idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    ClassFile* cf = searchClass((char*)fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Class.name_index].data.Utf8.bytes)->classFl;
    obj = createObject(cf);
    fs->top->pointers[fs->top->countpoint] =(void *) obj;
    push_operand(fs->top->countpoint,&(fs->top->opStack));
    fs->top->countpoint++;
    

    
}

void putfield(FrameStack *fs){
    Object* obj;
    u4 value[2];
    u4 ref_obj;
    u2 idx_name, idx_descriptor;
    u2 idx_class;
    u4 temp;
    ClassFile* cf;
    int nAtrib, i;
    int tipo;
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
        idx <<= 8;
        idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx_name= fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.name_and_type_index].data.NameAndType.name_index;
    idx_class = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.class_index].data.Class.name_index;
    cf = searchClass((char*)fs->top->cPoolRunTime[idx_class].data.Utf8.bytes)->classFl;
    idx_descriptor = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.name_and_type_index].data.NameAndType.descriptor_index;
    tipo = TypeDescriptor((char*)fs->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes);
    value[0] = pop_operand(&(fs->top->opStack));
    if (tipo==DOUBLE || tipo==LONG ){
        value[1] = pop_operand(&(fs->top->opStack));
    }
    ref_obj = pop_operand(&(fs->top->opStack));
    nAtrib = CountAtrib(cf);
    obj = (Object *) fs->top->pointers[ref_obj];
    for (i=0;i<nAtrib;i++){
			
        if (obj[i].name_index == idx_name){
		
            switch(obj[i].type){
                case (INTEGER):
                    obj[i].data.Int = value[0];
                    break;
                case (FLOAT):
                    obj[i].data.Float = value[0];

                    break;
                case (STRING):
                    idx=value[0];
                    
                    obj[i].data.String.length = fs->top->next->cPoolRunTime[idx].data.Utf8.length;
                    obj[i].data.String.String_bytes = fs->top->next->cPoolRunTime[idx].data.Utf8.bytes;
                    obj[i].data.String.index_bytes=idx;
                    break;
                case (DOUBLE):

                    obj[i].data.Double.HighDouble = value[1];
                    obj[i].data.Double.LowDouble = value[0];

                    break;
                case (LONG):
                    obj[i].data.Long.HighLong = value[1];
                    obj[i].data.Long.LowLong = value[0];

                    break;
		case (REFERENCE_CHAR):
		case (REFERENCE_INTEGER):
		case (REFERENCE_STRING):
		case (REFERENCE_FLOAT):
		case (REFERENCE_DOUBLE):
		case (REFERENCE_LONG):
		case (REFERENCE_BYTE):
		case (REFERENCE_SHORT):
		case (REFERENCE_BOOLEAN):
			
			temp = value[0];
			obj[i].data.Array = (void*) fs->top->pointers[temp];
                    break;
     		


            }
            
        }

    }
    
    
    
}

void getfield(FrameStack *fs){
    Object* obj;
    u4 ref_obj;
    u2 idx_name, idx_descriptor;
    u2 idx_class;
    ClassFile* cf;
    int nAtrib, i,j;
    int tipo;
    u2 idx = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
        idx <<= 8;
        idx |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx_name= fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.name_and_type_index].data.NameAndType.name_index;
    idx_class = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.class_index].data.Class.name_index;
    cf = searchClass((char*)fs->top->cPoolRunTime[idx_class].data.Utf8.bytes)->classFl;
    idx_descriptor = fs->top->cPoolRunTime[fs->top->cPoolRunTime[idx].data.Fieldref.name_and_type_index].data.NameAndType.descriptor_index;
    tipo = TypeDescriptor((char*)fs->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes);
    
    ref_obj = pop_operand(&(fs->top->opStack));
    nAtrib = CountAtrib(cf);

    obj = (Object *) fs->top->pointers[ref_obj];

    for (i=0;i<nAtrib;i++){

        if (obj[i].name_index == idx_name){
		
            switch(obj[i].type){
                case (INTEGER):
                     
                    push_operand((u4)obj[i].data.Int,&(fs->top->opStack));
                    break;
                case (FLOAT):
                     
                    push_operand((u4)obj[i].data.Float,&(fs->top->opStack));
                    break;
                case (DOUBLE):
                    push_operand((u4)obj[i].data.Double.HighDouble,&(fs->top->opStack));
                    push_operand((u4)obj[i].data.Double.LowDouble,&(fs->top->opStack));
                     

                    break;
                case (LONG):
                    push_operand((u4)obj[i].data.Long.HighLong,&(fs->top->opStack));
                    push_operand((u4)obj[i].data.Long.LowLong,&(fs->top->opStack)); 
                     

                    break;
		case (REFERENCE_CHAR):
		case (REFERENCE_INTEGER):
		case (REFERENCE_STRING):
		case (REFERENCE_FLOAT):
		case (REFERENCE_DOUBLE):
		case (REFERENCE_LONG):
		case (REFERENCE_BYTE):
		case (REFERENCE_SHORT):
		case (REFERENCE_BOOLEAN):
			for (j=0;j<fs->top->countpoint;j++){
				if (obj[i].data.Array==fs->top->pointers[j]){
					push_operand((u4)j,&(fs->top->opStack)); 
					return;
				}
			}
			fs->top->pointers[fs->top->countpoint] = obj[i].data.Array;
			push_operand((u4)fs->top->countpoint,&(fs->top->opStack)); 
			fs->top->countpoint++;
                    break;
            }
            
        }

    }
    
    
    
}


void f2i(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    float tmp;
    memmove(&tmp,&val,sizeof(tmp));
    int res = (int) tmp;
    push_operand((u4)res,&(fs->top->opStack)); 
}
void f2l(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    float tmp;
    memmove(&tmp,&val,sizeof(tmp));
    long long res = (long long) tmp;
    u4 val2[2];
    memmove(val2,&res,sizeof(res));
    push_operand(val2[0],&(fs->top->opStack)); 
    push_operand(val2[1],&(fs->top->opStack)); 
}
void i2l(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    int tmp;
    memmove(&tmp,&val,sizeof(tmp));
    long long res = (long long) tmp;
    u4 val2[2];
    memmove(val2,&res,sizeof(res));
    push_operand(val2[0],&(fs->top->opStack)); 
    push_operand(val2[1],&(fs->top->opStack)); 
}
void i2d(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    int tmp;
    memmove(&tmp,&val,sizeof(tmp));
    double res = (double) tmp;
    u4 val2[2];
    memmove(val2,&res,sizeof(res));
    push_operand(val2[0],&(fs->top->opStack)); 
    push_operand(val2[1],&(fs->top->opStack)); 
}
void f2d(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    float tmp;
    memmove(&tmp,&val,sizeof(tmp));
    double res = (double) tmp;
    u4 val2[2];
    memmove(val2,&res,sizeof(res));
    push_operand(val2[0],&(fs->top->opStack)); 
    push_operand(val2[1],&(fs->top->opStack)); 
}
void i2b(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    int tmp;
    memmove(&tmp,&val,sizeof(tmp));
    char res = (char) tmp;
    u4 val2 = (u4) res;
    push_operand(val2,&(fs->top->opStack)); 
 
}
void i2c(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    int tmp;
    memmove(&tmp,&val,sizeof(tmp));
    unsigned short res = (unsigned short) tmp;
    u4 val2;
    memmove(&val2,&res,sizeof(res));
    push_operand(val2,&(fs->top->opStack)); 
 
}
void i2s(FrameStack *fs){
    u4 val = pop_operand(&(fs->top->opStack));
    int tmp;
    memmove(&tmp,&val,sizeof(tmp));
    short res = (short) tmp;
    u4 val2 = (u4) res;
    push_operand(val2,&(fs->top->opStack)); 
 
}

void aconstnull(FrameStack *fs){
    fs->top->pointers[fs->top->countpoint] =NULL;
    push_operand(fs->top->countpoint,&(fs->top->opStack));
    fs->top->countpoint++;
}

void ifeq(FrameStack *fs){
    u2 idx =0;
    u4 op;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op = pop_operand(&(fs->top->opStack));
    if ((int)op==0){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void ifne(FrameStack *fs){
    u2 idx =0;
    u4 op;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op = pop_operand(&(fs->top->opStack));
    if ((int)op!=0){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void iflt(FrameStack *fs){
    u2 idx =0;
    u4 op;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op = pop_operand(&(fs->top->opStack));
    if ((int)op<0){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void ifle(FrameStack *fs){
    u2 idx =0;
    int op;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op =(int) pop_operand(&(fs->top->opStack));
    if (op<=0){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void ifgt(FrameStack *fs){
    u2 idx =0;
    u4 op;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op = pop_operand(&(fs->top->opStack));
    if ((int)op>0){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}
void ifge(FrameStack *fs){
    u2 idx =0;
    u4 op;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op = pop_operand(&(fs->top->opStack));
    if ((int)op>=0){
        fs->top->pc=fs->top->pc+(signed short)idx-3;    
    }
}

void if_acmpeq(FrameStack *fs){
    u4 op1,op2;
    u2 idx;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 =pop_operand(&(fs->top->opStack));
    op1 = pop_operand(&(fs->top->opStack));
    if (fs->top->pointers[op1]==fs->top->pointers[op2])
        fs->top->pc=fs->top->pc+(signed short)idx-3;
}
void if_acmpne(FrameStack *fs){
    u4 op1,op2;
    u2 idx;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op2 =pop_operand(&(fs->top->opStack));
    op1 = pop_operand(&(fs->top->opStack));
    if (fs->top->pointers[op1]!=fs->top->pointers[op2])
        fs->top->pc=fs->top->pc+(signed short)idx-3;
}
void jsr (FrameStack *fs){
    u2 idx=0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->pc,&(fs->top->opStack));
    fs->top->pc = fs->top->pc + (signed short)idx -3;
}
void ret (FrameStack *fs){
    u1 idx=0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->pc = fs->top->LocalVariables[idx] ;
}

void ifnull(FrameStack *fs){
    u4 op1;
    u2 idx;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op1 = pop_operand(&(fs->top->opStack));
    if (fs->top->pointers[op1]==NULL)
        fs->top->pc=fs->top->pc+(signed short)idx-3;
}
void ifnonull(FrameStack *fs){
    u4 op1;
    u2 idx;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    op1 = pop_operand(&(fs->top->opStack));
    if (fs->top->pointers[op1]!=NULL)
        fs->top->pc=fs->top->pc+(signed short)idx-3;
}

void Goto_w(FrameStack *fs){
    u4 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    fs->top->pc += (int) idx - 5;
}
void jsr_w (FrameStack *fs){
    u4 idx = 0;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    idx =idx<<8;
    idx = idx | fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
    push_operand(fs->top->pc,&(fs->top->opStack));
    fs->top->pc = fs->top->pc + (int)idx -5;
}

void areturn(FrameStack *fs){
	u4 ref;
	int i;	

	ref = pop_operand(&(fs->top->opStack));
	for (i=0;i<fs->top->next->countpoint;i++){
		if (fs->top->next->pointers[i] == fs->top->pointers[ref]){
			push_operand((u4)i,&(fs->top->next->opStack));
			fs->top->pc = fs->top->method->attributes->data.Code_attribute.code_length;
			return;
		}
	}
	
	if (i==fs->top->next->countpoint){
		fs->top->next->pointers[fs->top->next->countpoint] = fs->top->pointers[ref];
		push_operand((u4)i,&(fs->top->next->opStack));
		fs->top->next->countpoint++;
		fs->top->pc = fs->top->method->attributes->data.Code_attribute.code_length;
	}
	
}

void tableswitch (FrameStack *fs){
	int start = fs->top->pc;
	u4 zero = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	int i=0;
	    while (fs->top->pc%4){
		zero = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];

	}

	int default_value = zero;
	default_value = default_value <<8;
	default_value |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	default_value = default_value <<8;
	default_value |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	default_value = default_value <<8;
	default_value |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];

	int lowbytes = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	lowbytes = lowbytes<<8;
	lowbytes |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	lowbytes = lowbytes<<8;
	lowbytes |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	lowbytes = lowbytes<<8;
	lowbytes |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];

	int highbytes = fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	highbytes = highbytes<<8;
	highbytes |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	highbytes = highbytes<<8;
	highbytes |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
	highbytes = highbytes<<8;
	highbytes |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];

	int jump=0;
 	int index = (int) pop_operand(&(fs->top->opStack));

	if (index<lowbytes || index>highbytes){
		fs->top->pc = start +default_value-1;

	}
	else{
		
		fs->top->pc = fs->top->pc +((index-lowbytes)*4)+1;

		jump = fs->top->method->attributes->data.Code_attribute.code[fs->top->pc];
		jump = jump<<8;
		jump |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
		jump = jump<<8;
		jump |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
		jump = jump<<8;
		jump |= fs->top->method->attributes->data.Code_attribute.code[++fs->top->pc];
		
		fs->top->pc = start + jump-1;
		
		
	}
	
}
