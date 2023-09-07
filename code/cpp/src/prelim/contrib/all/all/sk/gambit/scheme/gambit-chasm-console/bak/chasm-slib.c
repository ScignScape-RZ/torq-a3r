#ifdef ___LINKER_INFO
; File: "chasm-slib.c", produced by Gambit v4.9.5
(
409005
(C)
"chasm-slib"
("chasm-slib")
()
(("chasm-slib"))
( #|*/"*/"symbols|#
"chasm-slib"
"chasm-slib#"
"chasm-slib#0"
"chasm-slib#1"
"chasm-slib#2"
) #|*/"*/"symbols|#
( #|*/"*/"keywords|#
) #|*/"*/"keywords|#
( #|*/"*/"globals-s-d|#
"catch-all-errors"
"chasm-slib#"
"chasm-slib#0"
"chasm-slib#1"
"chasm-slib#2"
"read-from-string"
"write-to-string"
) #|*/"*/"globals-s-d|#
( #|*/"*/"globals-s-nd|#
"eval-string"
"inc"
"inc-c"
"say_hello"
"scm-kw->chars"
"scm-symbol->chars"
"start-repl"
"test-kw"
"test-symbol"
) #|*/"*/"globals-s-nd|#
( #|*/"*/"globals-ns|#
"##start-repl-server"
"+"
"eval"
"keyword->string"
"pp"
"read"
"string-append"
"symbol->string"
"with-exception-catcher"
"with-input-from-string"
"with-output-to-string"
"write"
) #|*/"*/"globals-ns|#
( #|*/"*/"meta-info|#
) #|*/"*/"meta-info|#
)
#else
#define ___VERSION 409005
#define ___MODULE_NAME "chasm-slib"
#define ___LINKER_ID ___LNK_chasm_2d_slib
#define ___MH_PROC ___H_chasm_2d_slib
#define ___SCRIPT_LINE 0
#define ___SYMCOUNT 5
#define ___GLOCOUNT 28
#define ___SUPCOUNT 16
#define ___SUBCOUNT 8
#define ___LBLCOUNT 56
#define ___MODDESCR ___REF_SUB(5)
#include "gambit.h"

___NEED_SYM(___S_chasm_2d_slib)
___NEED_SYM(___S_chasm_2d_slib_23_)
___NEED_SYM(___S_chasm_2d_slib_23_0)
___NEED_SYM(___S_chasm_2d_slib_23_1)
___NEED_SYM(___S_chasm_2d_slib_23_2)

___NEED_GLO(___G__23__23_start_2d_repl_2d_server)
___NEED_GLO(___G__2b_)
___NEED_GLO(___G_catch_2d_all_2d_errors)
___NEED_GLO(___G_chasm_2d_slib_23_)
___NEED_GLO(___G_chasm_2d_slib_23_0)
___NEED_GLO(___G_chasm_2d_slib_23_1)
___NEED_GLO(___G_chasm_2d_slib_23_2)
___NEED_GLO(___G_eval)
___NEED_GLO(___G_eval_2d_string)
___NEED_GLO(___G_inc)
___NEED_GLO(___G_inc_2d_c)
___NEED_GLO(___G_keyword_2d__3e_string)
___NEED_GLO(___G_pp)
___NEED_GLO(___G_read)
___NEED_GLO(___G_read_2d_from_2d_string)
___NEED_GLO(___G_say__hello)
___NEED_GLO(___G_scm_2d_kw_2d__3e_chars)
___NEED_GLO(___G_scm_2d_symbol_2d__3e_chars)
___NEED_GLO(___G_start_2d_repl)
___NEED_GLO(___G_string_2d_append)
___NEED_GLO(___G_symbol_2d__3e_string)
___NEED_GLO(___G_test_2d_kw)
___NEED_GLO(___G_test_2d_symbol)
___NEED_GLO(___G_with_2d_exception_2d_catcher)
___NEED_GLO(___G_with_2d_input_2d_from_2d_string)
___NEED_GLO(___G_with_2d_output_2d_to_2d_string)
___NEED_GLO(___G_write)
___NEED_GLO(___G_write_2d_to_2d_string)

___BEGIN_SYM
___DEF_SYM(0,___S_chasm_2d_slib,"chasm-slib")
___DEF_SYM(1,___S_chasm_2d_slib_23_,"chasm-slib#")
___DEF_SYM(2,___S_chasm_2d_slib_23_0,"chasm-slib#0")
___DEF_SYM(3,___S_chasm_2d_slib_23_1,"chasm-slib#1")
___DEF_SYM(4,___S_chasm_2d_slib_23_2,"chasm-slib#2")
___END_SYM

#define ___SYM_chasm_2d_slib ___SYM(0,___S_chasm_2d_slib)
#define ___SYM_chasm_2d_slib_23_ ___SYM(1,___S_chasm_2d_slib_23_)
#define ___SYM_chasm_2d_slib_23_0 ___SYM(2,___S_chasm_2d_slib_23_0)
#define ___SYM_chasm_2d_slib_23_1 ___SYM(3,___S_chasm_2d_slib_23_1)
#define ___SYM_chasm_2d_slib_23_2 ___SYM(4,___S_chasm_2d_slib_23_2)

___BEGIN_GLO
___DEF_GLO(0,"catch-all-errors")
___DEF_GLO(1,"chasm-slib#")
___DEF_GLO(2,"chasm-slib#0")
___DEF_GLO(3,"chasm-slib#1")
___DEF_GLO(4,"chasm-slib#2")
___DEF_GLO(5,"eval-string")
___DEF_GLO(6,"inc")
___DEF_GLO(7,"inc-c")
___DEF_GLO(8,"read-from-string")
___DEF_GLO(9,"say_hello")
___DEF_GLO(10,"scm-kw->chars")
___DEF_GLO(11,"scm-symbol->chars")
___DEF_GLO(12,"start-repl")
___DEF_GLO(13,"test-kw")
___DEF_GLO(14,"test-symbol")
___DEF_GLO(15,"write-to-string")
___DEF_GLO(16,"##start-repl-server")
___DEF_GLO(17,"+")
___DEF_GLO(18,"eval")
___DEF_GLO(19,"keyword->string")
___DEF_GLO(20,"pp")
___DEF_GLO(21,"read")
___DEF_GLO(22,"string-append")
___DEF_GLO(23,"symbol->string")
___DEF_GLO(24,"with-exception-catcher")
___DEF_GLO(25,"with-input-from-string")
___DEF_GLO(26,"with-output-to-string")
___DEF_GLO(27,"write")
___END_GLO

#define ___GLO_catch_2d_all_2d_errors ___GLO(0,___G_catch_2d_all_2d_errors)
#define ___PRM_catch_2d_all_2d_errors ___PRM(0,___G_catch_2d_all_2d_errors)
#define ___GLO_chasm_2d_slib_23_ ___GLO(1,___G_chasm_2d_slib_23_)
#define ___PRM_chasm_2d_slib_23_ ___PRM(1,___G_chasm_2d_slib_23_)
#define ___GLO_chasm_2d_slib_23_0 ___GLO(2,___G_chasm_2d_slib_23_0)
#define ___PRM_chasm_2d_slib_23_0 ___PRM(2,___G_chasm_2d_slib_23_0)
#define ___GLO_chasm_2d_slib_23_1 ___GLO(3,___G_chasm_2d_slib_23_1)
#define ___PRM_chasm_2d_slib_23_1 ___PRM(3,___G_chasm_2d_slib_23_1)
#define ___GLO_chasm_2d_slib_23_2 ___GLO(4,___G_chasm_2d_slib_23_2)
#define ___PRM_chasm_2d_slib_23_2 ___PRM(4,___G_chasm_2d_slib_23_2)
#define ___GLO_eval_2d_string ___GLO(5,___G_eval_2d_string)
#define ___PRM_eval_2d_string ___PRM(5,___G_eval_2d_string)
#define ___GLO_inc ___GLO(6,___G_inc)
#define ___PRM_inc ___PRM(6,___G_inc)
#define ___GLO_inc_2d_c ___GLO(7,___G_inc_2d_c)
#define ___PRM_inc_2d_c ___PRM(7,___G_inc_2d_c)
#define ___GLO_read_2d_from_2d_string ___GLO(8,___G_read_2d_from_2d_string)
#define ___PRM_read_2d_from_2d_string ___PRM(8,___G_read_2d_from_2d_string)
#define ___GLO_say__hello ___GLO(9,___G_say__hello)
#define ___PRM_say__hello ___PRM(9,___G_say__hello)
#define ___GLO_scm_2d_kw_2d__3e_chars ___GLO(10,___G_scm_2d_kw_2d__3e_chars)
#define ___PRM_scm_2d_kw_2d__3e_chars ___PRM(10,___G_scm_2d_kw_2d__3e_chars)
#define ___GLO_scm_2d_symbol_2d__3e_chars ___GLO(11,___G_scm_2d_symbol_2d__3e_chars)
#define ___PRM_scm_2d_symbol_2d__3e_chars ___PRM(11,___G_scm_2d_symbol_2d__3e_chars)
#define ___GLO_start_2d_repl ___GLO(12,___G_start_2d_repl)
#define ___PRM_start_2d_repl ___PRM(12,___G_start_2d_repl)
#define ___GLO_test_2d_kw ___GLO(13,___G_test_2d_kw)
#define ___PRM_test_2d_kw ___PRM(13,___G_test_2d_kw)
#define ___GLO_test_2d_symbol ___GLO(14,___G_test_2d_symbol)
#define ___PRM_test_2d_symbol ___PRM(14,___G_test_2d_symbol)
#define ___GLO_write_2d_to_2d_string ___GLO(15,___G_write_2d_to_2d_string)
#define ___PRM_write_2d_to_2d_string ___PRM(15,___G_write_2d_to_2d_string)
#define ___GLO__23__23_start_2d_repl_2d_server ___GLO(16,___G__23__23_start_2d_repl_2d_server)
#define ___PRM__23__23_start_2d_repl_2d_server ___PRM(16,___G__23__23_start_2d_repl_2d_server)
#define ___GLO__2b_ ___GLO(17,___G__2b_)
#define ___PRM__2b_ ___PRM(17,___G__2b_)
#define ___GLO_eval ___GLO(18,___G_eval)
#define ___PRM_eval ___PRM(18,___G_eval)
#define ___GLO_keyword_2d__3e_string ___GLO(19,___G_keyword_2d__3e_string)
#define ___PRM_keyword_2d__3e_string ___PRM(19,___G_keyword_2d__3e_string)
#define ___GLO_pp ___GLO(20,___G_pp)
#define ___PRM_pp ___PRM(20,___G_pp)
#define ___GLO_read ___GLO(21,___G_read)
#define ___PRM_read ___PRM(21,___G_read)
#define ___GLO_string_2d_append ___GLO(22,___G_string_2d_append)
#define ___PRM_string_2d_append ___PRM(22,___G_string_2d_append)
#define ___GLO_symbol_2d__3e_string ___GLO(23,___G_symbol_2d__3e_string)
#define ___PRM_symbol_2d__3e_string ___PRM(23,___G_symbol_2d__3e_string)
#define ___GLO_with_2d_exception_2d_catcher ___GLO(24,___G_with_2d_exception_2d_catcher)
#define ___PRM_with_2d_exception_2d_catcher ___PRM(24,___G_with_2d_exception_2d_catcher)
#define ___GLO_with_2d_input_2d_from_2d_string ___GLO(25,___G_with_2d_input_2d_from_2d_string)
#define ___PRM_with_2d_input_2d_from_2d_string ___PRM(25,___G_with_2d_input_2d_from_2d_string)
#define ___GLO_with_2d_output_2d_to_2d_string ___GLO(26,___G_with_2d_output_2d_to_2d_string)
#define ___PRM_with_2d_output_2d_to_2d_string ___PRM(26,___G_with_2d_output_2d_to_2d_string)
#define ___GLO_write ___GLO(27,___G_write)
#define ___PRM_write ___PRM(27,___G_write)

___DEF_SUB_STR(___X0,1UL)
               ___STR1(33)
___DEF_SUB_STR(___X1,6UL)
               ___STR6(72,101,108,108,111,32)
___DEF_SUB_STR(___X2,15UL)
               ___STR8(108,111,99,97,108,104,111,115)
               ___STR7(116,58,52,52,53,53,53)
___DEF_SUB_STR(___X3,5UL)
               ___STR5(114,101,97,100,32)
___DEF_SUB_STR(___X4,4UL)
               ___STR4(100,111,110,101)
___DEF_SUB_VEC(___X5,6UL)
               ___VEC1(___REF_SUB(6))
               ___VEC1(___REF_SUB(7))
               ___VEC1(___REF_NUL)
               ___VEC1(___REF_FIX(1))
               ___VEC1(___REF_PRC(1))
               ___VEC1(___REF_FAL)
               ___VEC0
___DEF_SUB_VEC(___X6,1UL)
               ___VEC1(___REF_SYM(0,___S_chasm_2d_slib))
               ___VEC0
___DEF_SUB_VEC(___X7,0UL)
               ___VEC0

___BEGIN_SUB
 ___DEF_SUB(___X0)
,___DEF_SUB(___X1)
,___DEF_SUB(___X2)
,___DEF_SUB(___X3)
,___DEF_SUB(___X4)
,___DEF_SUB(___X5)
,___DEF_SUB(___X6)
,___DEF_SUB(___X7)
___END_SUB


#define ___C_LBL_scm_symbol_to_chars 12
#define ___C_LBL_scm_kw_to_chars 16
#define ___C_LBL_incc 19
#define ___C_LBL_say_hello 24
#define ___C_LBL_eval_string 41
#define ___C_LBL_start_repl 50

extern int inc ();
extern void test_symbol ();
extern char* scm_symbol_to_chars ___P((___SCMOBJ ___arg1),(___arg1)
___SCMOBJ ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_scm_symbol_to_chars),char* ___result)
___BEGIN_SFUN_ARG_SCMOBJ(1)
#define ___ARG1 ___arg1
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN_BODY
#undef ___ARG1
___END_SFUN_ARG_SCMOBJ(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}

extern char* scm_kw_to_chars ___P((___SCMOBJ ___arg1),(___arg1)
___SCMOBJ ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_scm_kw_to_chars),char* ___result)
___BEGIN_SFUN_ARG_SCMOBJ(1)
#define ___ARG1 ___arg1
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN_BODY
#undef ___ARG1
___END_SFUN_ARG_SCMOBJ(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}

extern int incc ___P((int ___arg1),(___arg1)
int ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_incc),int ___result)
___BEGIN_SFUN_ARG(1,___ARG1)
___BEGIN_SFUN_INT_TO_SCMOBJ(___arg1,___ARG1,1)
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___END_SFUN_BODY
___END_SFUN_INT_TO_SCMOBJ(___arg1,___ARG1,1)
___END_SFUN_ARG(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_INT(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}

extern char* say_hello ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_say_hello),char* ___result)
___BEGIN_SFUN_ARG(1,___ARG1)
___BEGIN_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN_BODY
___END_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___END_SFUN_ARG(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}

extern char* eval_string ___P((char* ___arg1),(___arg1)
char* ___arg1;)
{
#define ___NARGS 1
___BEGIN_SFUN(___MLBL(___C_LBL_eval_string),char* ___result)
___BEGIN_SFUN_ARG(1,___ARG1)
___BEGIN_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___BEGIN_SFUN_BODY
___SFUN_ARG(1,___ARG1)
___SFUN_CALL
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN_BODY
___END_SFUN_CHARSTRING_TO_SCMOBJ(___arg1,___ARG1,1)
___END_SFUN_ARG(1)
___SFUN_ERROR
___BEGIN_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___SFUN_SET_RESULT
___END_SFUN_SCMOBJ_TO_CHARSTRING(___SFUN_RESULT,___result)
___END_SFUN
return ___result;
#undef ___NARGS
}

extern void start_repl ___PVOID
{
#define ___NARGS 0
___BEGIN_SFUN_VOID(___MLBL(___C_LBL_start_repl))
___BEGIN_SFUN_BODY
___SFUN_CALL_VOID
___SFUN_SET_RESULT_VOID
___END_SFUN_BODY
___SFUN_ERROR_VOID
___SFUN_SET_RESULT_VOID
___END_SFUN_VOID
#undef ___NARGS
}

#define ___CFUN_SELECT(inl,ool)ool
#define ___NARGS 1
___BEGIN_CFUN(___chasm_2d_slib_23_0,int ___result)
#define ___ARG1 ___CFUN_ARG(1)
___BEGIN_CFUN_ARG(1,int ___arg1)
___BEGIN_CFUN_SCMOBJ_TO_INT(___ARG1,___arg1,1)
___BEGIN_CFUN_BODY
#undef ___AT_END
___CFUN_ASSIGN(___result,inc(___arg1))
#ifndef ___AT_END
#define ___AT_END
#endif
___BEGIN_CFUN_INT_TO_SCMOBJ(___result,___CFUN_RESULT)
___CFUN_SET_RESULT
___END_CFUN_INT_TO_SCMOBJ(___result,___CFUN_RESULT)
___END_CFUN_BODY
___END_CFUN_SCMOBJ_TO_INT(___ARG1,___arg1,1)
___END_CFUN_ARG(1)
#undef ___ARG1
___CFUN_ERROR
___END_CFUN
#undef ___NARGS
#undef ___CFUN_SELECT

#define ___CFUN_SELECT(inl,ool)ool
#define ___NARGS 1
___BEGIN_CFUN_VOID(___chasm_2d_slib_23_1)
#define ___ARG1 ___CFUN_ARG(1)
___BEGIN_CFUN_ARG_SCMOBJ(1)
#define ___arg1 ___ARG1
___BEGIN_CFUN_BODY
#undef ___AT_END
test_symbol(___arg1);
#ifndef ___AT_END
#define ___AT_END
#endif
___CFUN_SET_RESULT_VOID
___END_CFUN_BODY
#undef ___arg1
___END_CFUN_ARG_SCMOBJ(1)
#undef ___ARG1
___CFUN_ERROR_VOID
___END_CFUN_VOID
#undef ___NARGS
#undef ___CFUN_SELECT

#define ___CFUN_SELECT(inl,ool)ool
#define ___NARGS 1
___BEGIN_CFUN_VOID(___chasm_2d_slib_23_2)
#define ___ARG1 ___CFUN_ARG(1)
___BEGIN_CFUN_ARG_SCMOBJ(1)
#define ___arg1 ___ARG1
___BEGIN_CFUN_BODY
#undef ___AT_END
test_kw(___arg1);
#ifndef ___AT_END
#define ___AT_END
#endif
___CFUN_SET_RESULT_VOID
___END_CFUN_BODY
#undef ___arg1
___END_CFUN_ARG_SCMOBJ(1)
#undef ___ARG1
___CFUN_ERROR_VOID
___END_CFUN_VOID
#undef ___NARGS
#undef ___CFUN_SELECT


#undef ___MD_ALL
#define ___MD_ALL ___D_HEAP ___D_FP ___D_R0 ___D_R1 ___D_R2 ___D_R3 ___D_R4
#undef ___MR_ALL
#define ___MR_ALL ___R_HEAP ___R_FP ___R_R0 ___R_R1 ___R_R2 ___R_R3 ___R_R4
#undef ___MW_ALL
#define ___MW_ALL ___W_HEAP ___W_FP ___W_R0 ___W_R1 ___W_R2 ___W_R3 ___W_R4
___BEGIN_M_COD
___BEGIN_M_HLBL
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_chasm_2d_slib_23_)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_chasm_2d_slib_23_0)
___DEF_M_HLBL(___L1_chasm_2d_slib_23_0)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_chasm_2d_slib_23_1)
___DEF_M_HLBL(___L1_chasm_2d_slib_23_1)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_chasm_2d_slib_23_2)
___DEF_M_HLBL(___L1_chasm_2d_slib_23_2)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_scm_2d_symbol_2d__3e_chars)
___DEF_M_HLBL(___L1_scm_2d_symbol_2d__3e_chars)
___DEF_M_HLBL(___L2_scm_2d_symbol_2d__3e_chars)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_scm_2d_kw_2d__3e_chars)
___DEF_M_HLBL(___L1_scm_2d_kw_2d__3e_chars)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_inc_2d_c)
___DEF_M_HLBL(___L1_inc_2d_c)
___DEF_M_HLBL(___L2_inc_2d_c)
___DEF_M_HLBL(___L3_inc_2d_c)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_say__hello)
___DEF_M_HLBL(___L1_say__hello)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_catch_2d_all_2d_errors)
___DEF_M_HLBL(___L1_catch_2d_all_2d_errors)
___DEF_M_HLBL(___L2_catch_2d_all_2d_errors)
___DEF_M_HLBL(___L3_catch_2d_all_2d_errors)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_write_2d_to_2d_string)
___DEF_M_HLBL(___L1_write_2d_to_2d_string)
___DEF_M_HLBL(___L2_write_2d_to_2d_string)
___DEF_M_HLBL(___L3_write_2d_to_2d_string)
___DEF_M_HLBL(___L4_write_2d_to_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_read_2d_from_2d_string)
___DEF_M_HLBL(___L1_read_2d_from_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_eval_2d_string)
___DEF_M_HLBL(___L1_eval_2d_string)
___DEF_M_HLBL(___L2_eval_2d_string)
___DEF_M_HLBL(___L3_eval_2d_string)
___DEF_M_HLBL(___L4_eval_2d_string)
___DEF_M_HLBL(___L5_eval_2d_string)
___DEF_M_HLBL(___L6_eval_2d_string)
___DEF_M_HLBL(___L7_eval_2d_string)
___DEF_M_HLBL_INTRO
___DEF_M_HLBL(___L0_start_2d_repl)
___DEF_M_HLBL(___L1_start_2d_repl)
___DEF_M_HLBL(___L2_start_2d_repl)
___DEF_M_HLBL(___L3_start_2d_repl)
___DEF_M_HLBL(___L4_start_2d_repl)
___DEF_M_HLBL(___L5_start_2d_repl)
___END_M_HLBL

___BEGIN_M_SW

#undef ___PH_PROC
#define ___PH_PROC ___H_chasm_2d_slib_23_
#undef ___PH_LBL0
#define ___PH_LBL0 1
#undef ___PD_ALL
#define ___PD_ALL ___D_R0 ___D_R1
#undef ___PR_ALL
#define ___PR_ALL ___R_R0 ___R_R1
#undef ___PW_ALL
#define ___PW_ALL ___W_R1
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_chasm_2d_slib_23_)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_chasm_2d_slib_23_)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(0,0,0,0)
___DEF_GLBL(___L_chasm_2d_slib_23_)
   ___SET_GLO(6,___G_inc,___PRC(3))
   ___SET_GLO(14,___G_test_2d_symbol,___PRC(6))
   ___SET_GLO(13,___G_test_2d_kw,___PRC(9))
   ___SET_GLO(11,___G_scm_2d_symbol_2d__3e_chars,___PRC(12))
   ___SET_GLO(10,___G_scm_2d_kw_2d__3e_chars,___PRC(16))
   ___SET_GLO(7,___G_inc_2d_c,___PRC(19))
   ___SET_GLO(9,___G_say__hello,___PRC(24))
   ___SET_GLO(0,___G_catch_2d_all_2d_errors,___PRC(27))
   ___SET_GLO(15,___G_write_2d_to_2d_string,___PRC(32))
   ___SET_GLO(8,___G_read_2d_from_2d_string,___PRC(38))
   ___SET_GLO(5,___G_eval_2d_string,___PRC(41))
   ___SET_GLO(12,___G_start_2d_repl,___PRC(50))
   ___SET_R1(___VOID)
   ___JUMPRET(___R0)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_chasm_2d_slib_23_0
#undef ___PH_LBL0
#define ___PH_LBL0 3
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_chasm_2d_slib_23_0)
___DEF_P_HLBL(___L1_chasm_2d_slib_23_0)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_chasm_2d_slib_23_0)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_chasm_2d_slib_23_0)
   ___SET_STK(1,___R1)
   ___SET_STK(2,___R0)
   ___SET_R0(___LBL(1))
   ___ADJFP(8)
   ___CFUN_OOL(___chasm_2d_slib_23_0)
   ___JUMPRET(___R0)
___DEF_SLBL(1,___L1_chasm_2d_slib_23_0)
   ___ADJFP(-8)
   ___JUMPRET(___STK(2))
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_chasm_2d_slib_23_1
#undef ___PH_LBL0
#define ___PH_LBL0 6
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_chasm_2d_slib_23_1)
___DEF_P_HLBL(___L1_chasm_2d_slib_23_1)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_chasm_2d_slib_23_1)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_chasm_2d_slib_23_1)
   ___SET_STK(1,___R1)
   ___SET_STK(2,___R0)
   ___SET_R0(___LBL(1))
   ___ADJFP(8)
   ___CFUN_OOL(___chasm_2d_slib_23_1)
   ___JUMPRET(___R0)
___DEF_SLBL(1,___L1_chasm_2d_slib_23_1)
   ___ADJFP(-8)
   ___JUMPRET(___STK(2))
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_chasm_2d_slib_23_2
#undef ___PH_LBL0
#define ___PH_LBL0 9
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_chasm_2d_slib_23_2)
___DEF_P_HLBL(___L1_chasm_2d_slib_23_2)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_chasm_2d_slib_23_2)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_chasm_2d_slib_23_2)
   ___SET_STK(1,___R1)
   ___SET_STK(2,___R0)
   ___SET_R0(___LBL(1))
   ___ADJFP(8)
   ___CFUN_OOL(___chasm_2d_slib_23_2)
   ___JUMPRET(___R0)
___DEF_SLBL(1,___L1_chasm_2d_slib_23_2)
   ___ADJFP(-8)
   ___JUMPRET(___STK(2))
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_scm_2d_symbol_2d__3e_chars
#undef ___PH_LBL0
#define ___PH_LBL0 12
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_scm_2d_symbol_2d__3e_chars)
___DEF_P_HLBL(___L1_scm_2d_symbol_2d__3e_chars)
___DEF_P_HLBL(___L2_scm_2d_symbol_2d__3e_chars)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_scm_2d_symbol_2d__3e_chars)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_scm_2d_symbol_2d__3e_chars)
   ___IF(___NOT(___EQP(___GLO_symbol_2d__3e_string,___PRM_symbol_2d__3e_string)))
   ___GOTO(___L3_scm_2d_symbol_2d__3e_chars)
   ___END_IF
   ___IF(___SYMBOLP(___R1))
   ___GOTO(___L4_scm_2d_symbol_2d__3e_chars)
   ___END_IF
   ___GOTO(___L5_scm_2d_symbol_2d__3e_chars)
___DEF_GLBL(___L3_scm_2d_symbol_2d__3e_chars)
   ___GOTO(___L6_scm_2d_symbol_2d__3e_chars)
___DEF_GLBL(___L4_scm_2d_symbol_2d__3e_chars)
   ___IF(___SYMBOL2STRINGP_NOTFALSEP(___R2,___R1))
   ___GOTO(___L7_scm_2d_symbol_2d__3e_chars)
   ___END_IF
   ___SET_R2(___FAL)
   ___GOTO(___L8_scm_2d_symbol_2d__3e_chars)
___DEF_GLBL(___L5_scm_2d_symbol_2d__3e_chars)
___DEF_GLBL(___L6_scm_2d_symbol_2d__3e_chars)
   ___POLL(1)
___DEF_SLBL(1,___L1_scm_2d_symbol_2d__3e_chars)
   ___GOTO(___L9_scm_2d_symbol_2d__3e_chars)
___DEF_GLBL(___L7_scm_2d_symbol_2d__3e_chars)
   ___SET_R1(___R2)
   ___JUMPRET(___R0)
___DEF_GLBL(___L8_scm_2d_symbol_2d__3e_chars)
   ___POLL(2)
___DEF_SLBL(2,___L2_scm_2d_symbol_2d__3e_chars)
   ___JUMPGLOSAFE(___SET_NARGS(1),23,___G_symbol_2d__3e_string)
___DEF_GLBL(___L9_scm_2d_symbol_2d__3e_chars)
   ___JUMPGLOSAFE(___SET_NARGS(1),23,___G_symbol_2d__3e_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_scm_2d_kw_2d__3e_chars
#undef ___PH_LBL0
#define ___PH_LBL0 16
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_scm_2d_kw_2d__3e_chars)
___DEF_P_HLBL(___L1_scm_2d_kw_2d__3e_chars)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_scm_2d_kw_2d__3e_chars)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_scm_2d_kw_2d__3e_chars)
   ___POLL(1)
___DEF_SLBL(1,___L1_scm_2d_kw_2d__3e_chars)
   ___JUMPGLOSAFE(___SET_NARGS(1),19,___G_keyword_2d__3e_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_inc_2d_c
#undef ___PH_LBL0
#define ___PH_LBL0 19
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_inc_2d_c)
___DEF_P_HLBL(___L1_inc_2d_c)
___DEF_P_HLBL(___L2_inc_2d_c)
___DEF_P_HLBL(___L3_inc_2d_c)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_inc_2d_c)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_inc_2d_c)
   ___IF(___NOT(___EQP(___GLO__2b_,___PRM__2b_)))
   ___GOTO(___L4_inc_2d_c)
   ___END_IF
   ___IF(___FIXNUMP(___R1))
   ___GOTO(___L5_inc_2d_c)
   ___END_IF
   ___GOTO(___L6_inc_2d_c)
___DEF_GLBL(___L4_inc_2d_c)
   ___SET_R2(___FIX(2L))
   ___POLL(1)
___DEF_SLBL(1,___L1_inc_2d_c)
   ___GOTO(___L10_inc_2d_c)
___DEF_GLBL(___L5_inc_2d_c)
   ___IF(___FIXADDP_NOTFALSEP(___R2,___R1,___FIX(2L)))
   ___GOTO(___L7_inc_2d_c)
   ___END_IF
   ___SET_R2(___FAL)
   ___GOTO(___L8_inc_2d_c)
___DEF_GLBL(___L6_inc_2d_c)
   ___SET_R2(___FIX(2L))
   ___POLL(2)
___DEF_SLBL(2,___L2_inc_2d_c)
   ___GOTO(___L9_inc_2d_c)
___DEF_GLBL(___L7_inc_2d_c)
   ___SET_R1(___R2)
   ___JUMPRET(___R0)
___DEF_GLBL(___L8_inc_2d_c)
   ___SET_R2(___FIX(2L))
   ___POLL(3)
___DEF_SLBL(3,___L3_inc_2d_c)
   ___JUMPGLOSAFE(___SET_NARGS(2),17,___G__2b_)
___DEF_GLBL(___L9_inc_2d_c)
   ___JUMPGLOSAFE(___SET_NARGS(2),17,___G__2b_)
___DEF_GLBL(___L10_inc_2d_c)
   ___JUMPGLOSAFE(___SET_NARGS(2),17,___G__2b_)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_say__hello
#undef ___PH_LBL0
#define ___PH_LBL0 24
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R1 ___D_R2 ___D_R3 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R1 ___R_R2 ___R_R3 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_R1 ___W_R2 ___W_R3 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_say__hello)
___DEF_P_HLBL(___L1_say__hello)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_say__hello)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_say__hello)
   ___SET_R2(___R1)
   ___SET_R3(___SUB(0))
   ___SET_R1(___SUB(1))
   ___POLL(1)
___DEF_SLBL(1,___L1_say__hello)
   ___JUMPGLOSAFE(___SET_NARGS(3),22,___G_string_2d_append)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_catch_2d_all_2d_errors
#undef ___PH_LBL0
#define ___PH_LBL0 27
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_catch_2d_all_2d_errors)
___DEF_P_HLBL(___L1_catch_2d_all_2d_errors)
___DEF_P_HLBL(___L2_catch_2d_all_2d_errors)
___DEF_P_HLBL(___L3_catch_2d_all_2d_errors)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_catch_2d_all_2d_errors)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_catch_2d_all_2d_errors)
   ___SET_STK(1,___R1)
   ___SET_R1(___LBL(2))
   ___SET_R2(___STK(1))
   ___ADJFP(1)
   ___POLL(1)
___DEF_SLBL(1,___L1_catch_2d_all_2d_errors)
   ___GOTO(___L4_catch_2d_all_2d_errors)
___DEF_SLBL(2,___L2_catch_2d_all_2d_errors)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(2,1,0,0)
   ___POLL(3)
___DEF_SLBL(3,___L3_catch_2d_all_2d_errors)
   ___GOTO(___L5_catch_2d_all_2d_errors)
___DEF_GLBL(___L4_catch_2d_all_2d_errors)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(2),24,___G_with_2d_exception_2d_catcher)
___DEF_GLBL(___L5_catch_2d_all_2d_errors)
   ___JUMPGLOSAFE(___SET_NARGS(1),15,___G_write_2d_to_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_write_2d_to_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 32
#undef ___PD_ALL
#define ___PD_ALL ___D_HEAP ___D_FP ___D_R1 ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_HEAP ___R_FP ___R_R1 ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_HEAP ___W_FP ___W_R1 ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_write_2d_to_2d_string)
___DEF_P_HLBL(___L1_write_2d_to_2d_string)
___DEF_P_HLBL(___L2_write_2d_to_2d_string)
___DEF_P_HLBL(___L3_write_2d_to_2d_string)
___DEF_P_HLBL(___L4_write_2d_to_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_write_2d_to_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_write_2d_to_2d_string)
   ___SET_STK(1,___ALLOC_CLO(1UL))
   ___BEGIN_SETUP_CLO(1,___STK(1),3)
   ___ADD_CLO_ELEM(0,___R1)
   ___END_SETUP_CLO(1)
   ___SET_R2(___STK(1))
   ___SET_R1(___NUL)
   ___ADJFP(1)
   ___CHECK_HEAP(1,4096)
___DEF_SLBL(1,___L1_write_2d_to_2d_string)
   ___POLL(2)
___DEF_SLBL(2,___L2_write_2d_to_2d_string)
   ___GOTO(___L5_write_2d_to_2d_string)
___DEF_SLBL(3,___L3_write_2d_to_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_R1(___CLO(___R4,1))
   ___POLL(4)
___DEF_SLBL(4,___L4_write_2d_to_2d_string)
   ___GOTO(___L6_write_2d_to_2d_string)
___DEF_GLBL(___L5_write_2d_to_2d_string)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(2),26,___G_with_2d_output_2d_to_2d_string)
___DEF_GLBL(___L6_write_2d_to_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(1),27,___G_write)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_read_2d_from_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 38
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R2 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R2 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_R2 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_read_2d_from_2d_string)
___DEF_P_HLBL(___L1_read_2d_from_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_read_2d_from_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_read_2d_from_2d_string)
   ___SET_R2(___GLO_read)
   ___POLL(1)
___DEF_SLBL(1,___L1_read_2d_from_2d_string)
   ___JUMPGLOSAFE(___SET_NARGS(2),25,___G_with_2d_input_2d_from_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_eval_2d_string
#undef ___PH_LBL0
#define ___PH_LBL0 41
#undef ___PD_ALL
#define ___PD_ALL ___D_HEAP ___D_FP ___D_R0 ___D_R1 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_HEAP ___R_FP ___R_R0 ___R_R1 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_HEAP ___W_FP ___W_R0 ___W_R1 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_eval_2d_string)
___DEF_P_HLBL(___L1_eval_2d_string)
___DEF_P_HLBL(___L2_eval_2d_string)
___DEF_P_HLBL(___L3_eval_2d_string)
___DEF_P_HLBL(___L4_eval_2d_string)
___DEF_P_HLBL(___L5_eval_2d_string)
___DEF_P_HLBL(___L6_eval_2d_string)
___DEF_P_HLBL(___L7_eval_2d_string)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_eval_2d_string)
   ___IF_NARGS_EQ(1,___NOTHING)
   ___WRONG_NARGS(0,1,0,0)
___DEF_GLBL(___L_eval_2d_string)
   ___SET_STK(1,___ALLOC_CLO(1UL))
   ___BEGIN_SETUP_CLO(1,___STK(1),3)
   ___ADD_CLO_ELEM(0,___R1)
   ___END_SETUP_CLO(1)
   ___SET_R1(___STK(1))
   ___ADJFP(1)
   ___CHECK_HEAP(1,4096)
___DEF_SLBL(1,___L1_eval_2d_string)
   ___POLL(2)
___DEF_SLBL(2,___L2_eval_2d_string)
   ___GOTO(___L8_eval_2d_string)
___DEF_SLBL(3,___L3_eval_2d_string)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(3,0,0,0)
   ___SET_STK(1,___R0)
   ___SET_R1(___CLO(___R4,1))
   ___ADJFP(4)
   ___POLL(4)
___DEF_SLBL(4,___L4_eval_2d_string)
   ___GOTO(___L9_eval_2d_string)
___DEF_GLBL(___L8_eval_2d_string)
   ___ADJFP(-1)
   ___JUMPGLOSAFE(___SET_NARGS(1),0,___G_catch_2d_all_2d_errors)
___DEF_SLBL(5,___L5_eval_2d_string)
   ___SET_R0(___STK(-3))
   ___POLL(6)
___DEF_SLBL(6,___L6_eval_2d_string)
   ___GOTO(___L10_eval_2d_string)
___DEF_SLBL(7,___L7_eval_2d_string)
   ___SET_R0(___LBL(5))
   ___JUMPGLOSAFE(___SET_NARGS(1),18,___G_eval)
___DEF_GLBL(___L9_eval_2d_string)
   ___SET_R0(___LBL(7))
   ___JUMPGLOSAFE(___SET_NARGS(1),8,___G_read_2d_from_2d_string)
___DEF_GLBL(___L10_eval_2d_string)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),15,___G_write_2d_to_2d_string)
___END_P_SW
___END_P_COD

#undef ___PH_PROC
#define ___PH_PROC ___H_start_2d_repl
#undef ___PH_LBL0
#define ___PH_LBL0 50
#undef ___PD_ALL
#define ___PD_ALL ___D_FP ___D_R0 ___D_R1 ___D_R4
#undef ___PR_ALL
#define ___PR_ALL ___R_FP ___R_R0 ___R_R1 ___R_R4
#undef ___PW_ALL
#define ___PW_ALL ___W_FP ___W_R0 ___W_R1 ___W_R4
___BEGIN_P_COD
___BEGIN_P_HLBL
___DEF_P_HLBL_INTRO
___DEF_P_HLBL(___L0_start_2d_repl)
___DEF_P_HLBL(___L1_start_2d_repl)
___DEF_P_HLBL(___L2_start_2d_repl)
___DEF_P_HLBL(___L3_start_2d_repl)
___DEF_P_HLBL(___L4_start_2d_repl)
___DEF_P_HLBL(___L5_start_2d_repl)
___END_P_HLBL
___BEGIN_P_SW
___DEF_SLBL(0,___L0_start_2d_repl)
   ___IF_NARGS_EQ(0,___NOTHING)
   ___WRONG_NARGS(0,0,0,0)
___DEF_GLBL(___L_start_2d_repl)
   ___SET_STK(1,___R0)
   ___SET_R1(___SUB(2))
   ___ADJFP(4)
   ___POLL(1)
___DEF_SLBL(1,___L1_start_2d_repl)
   ___GOTO(___L6_start_2d_repl)
___DEF_SLBL(2,___L2_start_2d_repl)
   ___SET_R1(___SUB(3))
   ___SET_R0(___LBL(3))
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_pp)
___DEF_GLBL(___L6_start_2d_repl)
   ___SET_R0(___LBL(2))
   ___JUMPGLOSAFE(___SET_NARGS(1),16,___G__23__23_start_2d_repl_2d_server)
___DEF_SLBL(3,___L3_start_2d_repl)
   ___SET_R0(___LBL(4))
   ___JUMPGLOSAFE(___SET_NARGS(0),21,___G_read)
___DEF_SLBL(4,___L4_start_2d_repl)
   ___SET_R1(___SUB(4))
   ___SET_R0(___STK(-3))
   ___POLL(5)
___DEF_SLBL(5,___L5_start_2d_repl)
   ___ADJFP(-4)
   ___JUMPGLOSAFE(___SET_NARGS(1),20,___G_pp)
___END_P_SW
___END_P_COD

___END_M_SW
___END_M_COD

___BEGIN_LBL
 ___DEF_LBL_INTRO(___H_chasm_2d_slib_23_,___REF_SYM(1,___S_chasm_2d_slib_23_),___REF_FAL,1,0)
,___DEF_LBL_PROC(___H_chasm_2d_slib_23_,0,-1)
,___DEF_LBL_INTRO(___H_chasm_2d_slib_23_0,___REF_SYM(2,___S_chasm_2d_slib_23_0),___REF_FAL,2,0)
,___DEF_LBL_PROC(___H_chasm_2d_slib_23_0,1,-1)
,___DEF_LBL_RET(___H_chasm_2d_slib_23_0,___IFD(___RETN,2,1,0x3L))
,___DEF_LBL_INTRO(___H_chasm_2d_slib_23_1,___REF_SYM(3,___S_chasm_2d_slib_23_1),___REF_FAL,2,0)
,___DEF_LBL_PROC(___H_chasm_2d_slib_23_1,1,-1)
,___DEF_LBL_RET(___H_chasm_2d_slib_23_1,___IFD(___RETN,2,1,0x3L))
,___DEF_LBL_INTRO(___H_chasm_2d_slib_23_2,___REF_SYM(4,___S_chasm_2d_slib_23_2),___REF_FAL,2,0)
,___DEF_LBL_PROC(___H_chasm_2d_slib_23_2,1,-1)
,___DEF_LBL_RET(___H_chasm_2d_slib_23_2,___IFD(___RETN,2,1,0x3L))
,___DEF_LBL_INTRO(___H_scm_2d_symbol_2d__3e_chars,___REF_FAL,___REF_FAL,3,scm_symbol_to_chars)
,___DEF_LBL_PROC(___H_scm_2d_symbol_2d__3e_chars,1,-1)
,___DEF_LBL_RET(___H_scm_2d_symbol_2d__3e_chars,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_RET(___H_scm_2d_symbol_2d__3e_chars,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_scm_2d_kw_2d__3e_chars,___REF_FAL,___REF_FAL,2,scm_kw_to_chars)
,___DEF_LBL_PROC(___H_scm_2d_kw_2d__3e_chars,1,-1)
,___DEF_LBL_RET(___H_scm_2d_kw_2d__3e_chars,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_inc_2d_c,___REF_FAL,___REF_FAL,4,incc)
,___DEF_LBL_PROC(___H_inc_2d_c,1,-1)
,___DEF_LBL_RET(___H_inc_2d_c,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_RET(___H_inc_2d_c,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_RET(___H_inc_2d_c,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_say__hello,___REF_FAL,___REF_FAL,2,say_hello)
,___DEF_LBL_PROC(___H_say__hello,1,-1)
,___DEF_LBL_RET(___H_say__hello,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_catch_2d_all_2d_errors,___REF_FAL,___REF_FAL,4,0)
,___DEF_LBL_PROC(___H_catch_2d_all_2d_errors,1,-1)
,___DEF_LBL_RET(___H_catch_2d_all_2d_errors,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_catch_2d_all_2d_errors,1,-1)
,___DEF_LBL_RET(___H_catch_2d_all_2d_errors,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_write_2d_to_2d_string,___REF_FAL,___REF_FAL,5,0)
,___DEF_LBL_PROC(___H_write_2d_to_2d_string,1,-1)
,___DEF_LBL_RET(___H_write_2d_to_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_RET(___H_write_2d_to_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_write_2d_to_2d_string,0,1)
,___DEF_LBL_RET(___H_write_2d_to_2d_string,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_read_2d_from_2d_string,___REF_FAL,___REF_FAL,2,0)
,___DEF_LBL_PROC(___H_read_2d_from_2d_string,1,-1)
,___DEF_LBL_RET(___H_read_2d_from_2d_string,___IFD(___RETI,0,0,0x3fL))
,___DEF_LBL_INTRO(___H_eval_2d_string,___REF_FAL,___REF_FAL,8,eval_string)
,___DEF_LBL_PROC(___H_eval_2d_string,1,-1)
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,1,4,0x3f0L))
,___DEF_LBL_PROC(___H_eval_2d_string,0,1)
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETI,4,4,0x3f0L))
,___DEF_LBL_RET(___H_eval_2d_string,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_INTRO(___H_start_2d_repl,___REF_FAL,___REF_FAL,6,start_repl)
,___DEF_LBL_PROC(___H_start_2d_repl,0,-1)
,___DEF_LBL_RET(___H_start_2d_repl,___IFD(___RETI,4,0,0x3f1L))
,___DEF_LBL_RET(___H_start_2d_repl,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_start_2d_repl,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_start_2d_repl,___IFD(___RETN,1,0,0x1L))
,___DEF_LBL_RET(___H_start_2d_repl,___IFD(___RETI,4,4,0x3f0L))
___END_LBL

___BEGIN_MOD_PRM
___DEF_MOD_PRM(1,___G_chasm_2d_slib_23_,1)
___DEF_MOD_PRM(2,___G_chasm_2d_slib_23_0,3)
___DEF_MOD_PRM(3,___G_chasm_2d_slib_23_1,6)
___DEF_MOD_PRM(4,___G_chasm_2d_slib_23_2,9)
___END_MOD_PRM

___BEGIN_MOD_C_INIT
___END_MOD_C_INIT

___BEGIN_MOD_GLO
___DEF_MOD_GLO(1,___G_chasm_2d_slib_23_,1)
___DEF_MOD_GLO(2,___G_chasm_2d_slib_23_0,3)
___DEF_MOD_GLO(3,___G_chasm_2d_slib_23_1,6)
___DEF_MOD_GLO(4,___G_chasm_2d_slib_23_2,9)
___END_MOD_GLO

___BEGIN_MOD_SYM_KEY
___DEF_MOD_SYM(0,___S_chasm_2d_slib,"chasm-slib")
___DEF_MOD_SYM(1,___S_chasm_2d_slib_23_,"chasm-slib#")
___DEF_MOD_SYM(2,___S_chasm_2d_slib_23_0,"chasm-slib#0")
___DEF_MOD_SYM(3,___S_chasm_2d_slib_23_1,"chasm-slib#1")
___DEF_MOD_SYM(4,___S_chasm_2d_slib_23_2,"chasm-slib#2")
___END_MOD_SYM_KEY

#endif
