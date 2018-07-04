#ifndef __OPCODES__
#define __OPCODE__


/*Opcodes */

typedef enum opcode{op_nop=0,op_aconst_null,op_iconst_m1,op_iconst_0,op_iconst_1,op_iconst_2,
op_iconst_3,op_iconst_4,op_iconst_5,op_lconst_0,op_lconst_1,
op_fconst_0,op_fconst_1,op_fconst_2,op_dconst_0,op_dconst_1,
op_bipush,op_sipush,op_ldc,op_ldc_w,op_ldc2_w,
op_iload,op_lload,op_fload,op_dload,op_aload,
op_iload_0,op_iload_1,op_iload_2,op_iload_3,op_lload_0,
op_lload_1,op_lload_2,op_lload_3,op_fload_0,op_fload_1,
op_fload_2,op_fload_3,op_dload_0,op_dload_1,op_dload_2,
op_dload_3,op_aload_0,op_aload_1,op_aload_2,op_aload_3,
op_iaload,op_laload,op_faload,op_daload,op_aaload,
op_baload,op_caload,op_saload,op_istore,op_lstore,
op_fstore,op_dstore,op_astore,op_istore_0,op_istore_1,
op_istore_2,op_istore_3,op_lstore_0,op_lstore_1,op_lstore_2,
op_lstore_3,op_fstore_0,op_fstore_1,op_fstore_2,op_fstore_3,
op_dstore_0,op_dstore_1,op_dstore_2,op_dstore_3,op_astore_0,
op_astore_1,op_astore_2,op_astore_3,op_iastore,op_lastore,
op_fastore,op_dastore,op_aastore,op_bastore,op_castore,
op_sastore,op_pop,op_pop2,op_dup,op_dup_x1,
op_dup_x2,op_dup2,op_dup2_x1,op_dup2_x2,op_swap,
op_iadd,op_ladd,op_fadd,op_dadd,op_isub,
op_lsub,op_fsub,op_dsub,op_imul,op_lmul,
op_fmul,op_dmul,op_idiv,op_ldiv,op_fdiv,
op_ddiv,op_irem,op_lrem,op_frem,op_drem,
op_ineg,op_lneg,op_fneg,op_dneg,op_ishl,
op_lshl,op_ishr,op_lshr,op_iushr,op_lushr,
op_iand,op_land,op_ior,op_lor,op_ixor,
op_lxor,op_iinc,op_i2l,op_i2f,op_i2d,
op_l2i,op_l2f,op_l2d,op_f2i,op_f2l,
op_f2d,op_d2i,op_d2l,op_d2f,op_i2b,
op_i2c,op_i2s,op_lcmp,op_fcmpl,op_fcmpg,
op_dcmpl,op_dcmpg,op_ifeq,op_ifne,op_iflt,
op_ifge,op_ifgt,op_ifle,op_if_icmpeq,op_if_icmpne,
op_if_icmplt,op_if_icmpge,op_if_icmpgt,op_if_icmple,op_if_acmpeq,
op_if_acmpne,op_goto,op_jsr,op_ret,op_tableswitch,
op_lookupswitch,op_ireturn,op_lreturn,op_freturn,op_dreturn,
op_areturn,op_return,op_getstatic,op_putstatic,op_getfield,
op_putfield,op_invokevirtual,op_invokespecial,op_invokestatic,op_invokeinterface,
op_xxxunusedxxx1,op_new,op_newarray,op_anewarray,op_arraylength,
op_athrow,op_checkcast,op_instanceof,op_monitorenter,op_monitorexit,
op_wide,op_multianewarray,op_ifnull,op_ifnonnull,op_goto_w,
op_jsr_w,op_breakpoint,op_impdep1 = 254 ,op_impdep} opcodes;

#endif
