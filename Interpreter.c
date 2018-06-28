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





#include "Interpreter.h"


void executarInstrucao(unsigned char opcode,FrameStack* fr){
	u2 idx, idx_class, idx_method,idx_descriptor;

	switch (opcode){
		case(op_nop):
		break;
		case(op_aconst_null):
			aconstnull(fr);
		break;
		case(op_iconst_m1):
			
			iconst((u4)-1,fr);
		break;
		case(op_iconst_0):
			iconst(0,fr);
		break;
		case(op_iconst_1):
			iconst(1,fr);
		break;
		case(op_iconst_2):
			iconst(2,fr);
		break;
		case(op_iconst_3):
			iconst(3,fr);
		break;
		case(op_iconst_4):
			iconst(4,fr);
		break;
		case(op_iconst_5):
			iconst(5,fr);
		break;
		case(op_lconst_0):
			lconstn(0,fr);
		break;
		case(op_lconst_1):
			lconstn(1,fr);
		break;
		case(op_fconst_0):
			fconstn(0,fr);
		break;
		case(op_fconst_1):
			fconstn(1,fr);
		break;
		case(op_fconst_2):
			fconstn(2,fr);
		break;
		case(op_dconst_0):
			dconstn(0,fr);
		break;
		case(op_dconst_1):
			dconstn(1,fr);
		break;
		case(op_bipush):
			bipush(fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc],fr);
		break;
		case(op_sipush):
			sipush(fr);
		break;
		case(op_ldc):
			ldc(fr);
		break;
		case(op_ldc_w):
			
		break;
		case(op_ldc2_w):
			ldc2(fr);
		break;
		case(op_iload):
			iload(fr);
		break;
		case(op_lload):
			lload(fr);
		break;
		case(op_fload):
			fload(fr);
		break;
		case(op_dload):
			dload(fr);
		break;
		case(op_aload):
			aload(fr);
		break;
		case(op_iload_0):
			iloadn(0,fr);
		break;
		case(op_iload_1):
			iloadn(1,fr);
		break;
		case(op_iload_2):
			iloadn(2,fr);
		break;
		case(op_iload_3):
			iloadn(3,fr);
		break;
		case(op_lload_0):
			lloadn(0,fr);
		break;
		case(op_lload_1):
			lloadn(1,fr);
		break;
		case(op_lload_2):
			lloadn(2,fr);
		break;
		case(op_lload_3):
			lloadn(3,fr);
		break;
		case(op_fload_0):
			floadn(0,fr);
		break;
		case(op_fload_1):
			floadn(1,fr);
		break;
		case(op_fload_2):
			floadn(2,fr);
		break;
		case(op_fload_3):
			floadn(3,fr);
		break;
		case(op_dload_0):
			dloadn(0,fr);
		break;
		case(op_dload_1):
			dloadn(1,fr);
		break;
		case(op_dload_2):
			dloadn(2,fr);
		break;
		case(op_dload_3):
			dloadn(3,fr);
		break;
		case(op_aload_0):
			aloadn(0,fr);
		break;
		case(op_aload_1):
			aloadn(1,fr);
		break;
		case(op_aload_2):
			aloadn(2,fr);
		break;
		case(op_aload_3):
			aloadn(3,fr);
		break;
		case(op_iaload):
			iaload(fr);
		break;
		case(op_laload):
			laload(fr);
		break;
		case(op_faload):
			faload(fr);
		break;
		case(op_daload):
			daload(fr);
		break;
		case(op_aaload):
			aaload(fr);
		break;
		case(op_baload):
			baload(fr);
		break;
		case(op_caload):
			caload(fr);
		break;
		case(op_saload):
			saload(fr);
		break;
		case(op_istore):
			istore(fr);
		break;
		case(op_lstore):
			lstore(fr);
		break;
		case(op_fstore):
			fstore(fr);
		break;
		case(op_dstore):
			dstore(fr);
		break;
		case(op_astore):
			astore(fr);
		break;
		case(op_istore_0):
			istoren(0,fr);
		break;
		case(op_istore_1):
			istoren(1,fr);
		break;
		case(op_istore_2):
			istoren(2,fr);
		break;
		case(op_istore_3):
			istoren(3,fr);
		break;
		case(op_lstore_0):
			lstoren(0,fr);
		break;
		case(op_lstore_1):
			lstoren(1,fr);
		break;
		case(op_lstore_2):
			lstoren(2,fr);
		break;
		case(op_lstore_3):
			lstoren(3,fr);
		break;
		case(op_fstore_0):
			fstoren(0,fr);
		break;
		case(op_fstore_1):
			fstoren(1,fr);
		break;
		case(op_fstore_2):
			fstoren(2,fr);
		break;
		case(op_fstore_3):
			fstoren(3,fr);
		break;
		case(op_dstore_0):
			dstoren(0,fr);
		break;
		case(op_dstore_1):
			dstoren(1,fr);
		break;
		case(op_dstore_2):
			dstoren(2,fr);
		break;
		case(op_dstore_3):
			dstoren(3,fr);
		break;
		case(op_astore_0):
			astoren(0,fr);
		break;
		case(op_astore_1):
			astoren(1,fr);
		break;
		case(op_astore_2):
			astoren(2,fr);
		break;
		case(op_astore_3):
			astoren(3,fr);
		break;
		case(op_iastore):
			iastore(fr);
		break;
		case(op_lastore):
			lastore(fr);
		break;
		case(op_fastore):
			fastore(fr);
		break;
		case(op_dastore):
			dastore(fr);
		break;
		case(op_aastore):
			printf("Erro. Instrucao aastore nao implementada\n");
			exit(1);
		break;
		case(op_bastore):
			bastore(fr);
		break;
		case(op_castore):
			castore(fr);
		break;
		case(op_sastore):
			sastore(fr);
		break;
		case(op_pop):
			pop(fr);
		break;
		case(op_pop2):
			pop2(fr);
		break;
		case(op_dup):
			dup(fr);
		break;
		case(op_dup_x1):
			dupx1(fr);
		break;
		case(op_dup_x2):
			dupx2_1(fr);
		break;
		case(op_dup2):
			dup2(fr);
		break;
		case(op_dup2_x1):
			dup2x1_1(fr);
		break;
		case(op_dup2_x2):
			dup2x1_2(fr);
		break;
		case(op_swap):
			swap(fr);
		break;
		case(op_iadd):
			iadd(fr);
		break;
		case(op_ladd):
			ladd(fr);
		break;
		case(op_fadd):
			fadd(fr);
		break;
		case(op_dadd):
			dadd(fr);
		break;
		case(op_isub):
			isub(fr);
		break;
		case(op_lsub):
			lsub(fr);
		break;
		case(op_fsub):
			fsub(fr);
		break;
		case(op_dsub):
			dsub(fr);
		break;
		case(op_imul):
			imul(fr);
		break;
		case(op_lmul):
			lmul(fr);
		break;
		case(op_fmul):
			fmul(fr);
		break;
		case(op_dmul):
			dmul(fr);
		break;
		case(op_idiv):
			idiv(fr);
		break;
		case(op_ldiv):
			lldiv_(fr);
		break;
		case(op_fdiv):
			fdiv(fr);
		break;
		case(op_ddiv):
			ddiv(fr);
		break;
		case(op_irem):
			irem(fr);
		break;
		case(op_lrem):
			lrem(fr);
		break;
		case(op_frem):
			frem(fr);
		break;
		case(op_drem):
			dRem(fr);
		break;
		case(op_ineg):
			ineg(fr);
		break;
		case(op_lneg):
			lneg(fr);
			
		break;
		case(op_fneg):
			fneg(fr);
		break;
		case(op_dneg):
			dneg(fr);
		break;
		case(op_ishl):
			ishl(fr);
		break;
		case(op_lshl):
			lshl(fr);
		break;
		case(op_ishr):
			ishr(fr);
		break;
		case(op_lshr):
			lshr(fr);
		break;
		case(op_iushr):
			iushr(fr);
		break;
		case(op_lushr):
			lushr(fr);
		break;
		case(op_iand):
			iand(fr);
		break;
		case(op_land):
			land(fr);
		break;
		case(op_ior):
			ior(fr);
		break;
		case(op_lor):
			lor(fr);
		break;
		case(op_ixor):
			ixor(fr);
		break;
		case(op_lxor):
			lxor(fr);
		break;
		case(op_iinc):
			iinc(fr);
		break;
		case(op_i2l):
			i2l(fr);
		break;
		case(op_i2f):
			i2f(fr);
		break;
		case(op_i2d):
			i2d(fr);
		break;
		case(op_l2i):
			l2i(fr);
		break;
		case(op_l2f):
			l2f(fr);
		break;
		case(op_l2d):
			l2d(fr);
		break;
		case(op_f2i):
			f2i(fr);
		break;
		case(op_f2l):
			f2l(fr);
		break;
		case(op_f2d):
			f2d(fr);
		break;
		case(op_d2i):
			d2i(fr);
		break;
		case(op_d2l):
			d2l(fr);
		break;
		case(op_d2f):
			d2f(fr);
		break;
		case(op_i2b):
			i2b(fr);
		break;
		case(op_i2c):
			i2c(fr);
		break;
		case(op_i2s):
			i2s(fr);
		break;
		case(op_lcmp):
			lcmp(fr);
		break;
		case(op_fcmpl):
			fcmpl(fr);
		break;
		case(op_fcmpg):
			fcmpg(fr);
		break;
		case(op_dcmpl):
			dcmpl(fr);
		break;
		case(op_dcmpg):
			dcmpg(fr);
		break;
		case(op_ifeq):
			ifeq(fr);
		break;
		case(op_ifne):
			ifne(fr);
		break;
		case(op_iflt):
			iflt(fr);
		break;
		case(op_ifge):
			ifge(fr);
		break;
		case(op_ifgt):
			ifgt(fr);
		break;
		case(op_ifle):
			ifle(fr);
		break;
		case(op_if_icmpeq):
			if_icmpeq(fr);
		break;
		case(op_if_icmpne):
			if_icmpne(fr);
		break;
		case(op_if_icmplt):
			if_icmplt(fr);
		break;
		case(op_if_icmpge):
			if_icmpge(fr);
			
		break;
		case(op_if_icmpgt):
			if_icmpgt(fr);
		break;
		case(op_if_icmple):
			if_icmple(fr);
		break;
		case(op_if_acmpeq):
			if_acmpeq(fr);
		break;
		case(op_if_acmpne):
			if_acmpne(fr);
		break;
		case(op_goto):
			Goto(fr);
		break;
		case(op_jsr):
			jsr(fr);
		break;
		case(op_ret):
			ret(fr);
		break;
		case(op_tableswitch):
			tableswitch (fr);
		break;
		case(op_lookupswitch):
			printf("Erro. Instrucao lookupswitck nao implementada\n");
			exit(1);
		break;
		case(op_ireturn):
			ireturn(fr);
		break;
		case(op_lreturn):
			lreturn(fr);
		break;
		case(op_freturn):
			freturn(fr);
		break;
		case(op_dreturn):
			dreturn(fr);
		break;
		case(op_areturn):
			areturn(fr);
		break;
		case(op_return):
			fr->top->pc=fr->top->method->attributes->data.Code_attribute.code_length;
		break;
		case(op_getstatic):
			getstatic(fr);
		break;
		case(op_putstatic):
			putstatic(fr);
		break;
		case(op_getfield):
			getfield(fr);
		break;
		case(op_putfield):
			putfield(fr);
		break;
		case(op_invokevirtual):
			idx = 0;
			idx = idx | fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc];
			idx = idx<<8;
			idx = idx | fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc];
			idx_class = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.class_index].data.Class.name_index;
			idx_method = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.name_and_type_index].data.NameAndType.name_index;
			idx_descriptor = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.name_and_type_index].data.NameAndType.descriptor_index;
			/*interceptacao da chamada a println*/
      
			if( (strcmp((char *)fr->top->cPoolRunTime[idx_class].data.Utf8.bytes,"java/io/PrintStream") == 0) && (strcmp((char *)fr->top->cPoolRunTime[idx_method].data.Utf8.bytes,"println") == 0)){ 
				executarPrintln(fr,(char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,fr->top->cPoolRunTime[idx_descriptor].data.Utf8.length );
			}
			else{
				executar((char *)fr->top->cPoolRunTime[idx_method].data.Utf8.bytes,(char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,(char *) fr->top->cPoolRunTime[idx_class].data.Utf8.bytes, Nargs((char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,fr->top->cPoolRunTime[idx_descriptor].data.Utf8.length),fr,1 );
			}
		break;
		case(op_invokespecial):
			idx = 0;
			
			idx = idx | fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc];
			idx = idx<<8;
			idx = idx | fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc];
			idx_class = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.class_index].data.Class.name_index;
			idx_method = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.name_and_type_index].data.NameAndType.name_index;
			idx_descriptor = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.name_and_type_index].data.NameAndType.descriptor_index;
			/*interceptacao da chamada a class object*/
			if (strcmp("java/lang/Object",(char*)fr->top->cPoolRunTime[idx_class].data.Utf8.bytes)){
			executar((char *)fr->top->cPoolRunTime[idx_method].data.Utf8.bytes,(char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,(char *) fr->top->cPoolRunTime[idx_class].data.Utf8.bytes, Nargs((char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,fr->top->cPoolRunTime[idx_descriptor].data.Utf8.length),fr,1 );
			}
		break;
		case(op_invokestatic):
			idx = 0;
			idx = idx | fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc];
			idx = idx<<8;
			idx = idx | fr->top->method->attributes->data.Code_attribute.code[++fr->top->pc];
			idx_class = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.class_index].data.Class.name_index;
			idx_method = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.name_and_type_index].data.NameAndType.name_index;
			idx_descriptor = fr->top->cPoolRunTime[fr->top->cPoolRunTime[idx].data.Methodref.name_and_type_index].data.NameAndType.descriptor_index;
			executar((char *)fr->top->cPoolRunTime[idx_method].data.Utf8.bytes,(char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,(char *) fr->top->cPoolRunTime[idx_class].data.Utf8.bytes, Nargs((char *)fr->top->cPoolRunTime[idx_descriptor].data.Utf8.bytes,fr->top->cPoolRunTime[idx_descriptor].data.Utf8.length),fr,0 );
			
		break;
		case(op_invokeinterface):
			printf("Erro. Instrucao invokeinterface nao implementada\n");
			exit(1);
		break;
		case(op_new):
			newObj(fr);
		break;
		case(op_newarray):
			newarray(fr);
		break;
		case(op_anewarray):
			anewarray(fr);
		break;
		case(op_arraylength):
			printf("Erro. Instrucao arraylength nao implementada\n");
			exit(1);
		break;
		case(op_athrow):
			printf("Erro. Instrucao athrow nao implementada\n");
			exit(1);
		break;
		case(op_checkcast):
			printf("Erro. Instrucao checkcast nao implementada\n");
			exit(1);
		break;
		case(op_instanceof):
			printf("Erro. Instrucao instanceof nao implementada\n");
			exit(1);
		break;
		case(op_monitorenter):
			printf("Erro. Instrucao monitorenter nao implementada\n");
			exit(1);
		break;
		case(op_monitorexit):
			printf("Erro. Instrucao monitorexit nao implementada\n");
			exit(1);
		break;
		case(op_wide):
			printf("Erro. Instrucao wide nao implementada\n");
			exit(1);
		break;
		case(op_multianewarray):
			multianewarray(fr);
		break;
		case(op_ifnull):
			ifnull(fr);
		break;
		case(op_ifnonnull):
			ifnonull(fr);
		break;
		case(op_goto_w):
			Goto_w(fr);
		break;
		case(op_jsr_w):
			jsr_w(fr);
		break;
		case(op_breakpoint):
			printf("Erro. Instrucao breakpoint nao implementada\n");
			exit(1);
		break;
		case(op_impdep1):
			printf("Erro. Instrucao inpedep1 nao implementada\n");
			exit(1);
		break;
		case(op_impdep):
			printf("Erro. Instrucao impdep nao implementada\n");
			exit(1);
		break;
		default:
		break;
	}	
}
