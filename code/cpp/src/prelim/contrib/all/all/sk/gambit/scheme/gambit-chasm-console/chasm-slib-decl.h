
#ifndef CHASM_SLIB_DECL__H
#define CHASM_SLIB_DECL__H


#include "gambit.h"


extern char* eval_string(char* s);

extern int inc(int);
extern void test_symbol(___SCMOBJ);
extern void test_kw(___SCMOBJ);
extern void test_fn(___SCMOBJ);

extern ___SCMOBJ expr_writer(___SCMOBJ);

extern void expr_proceed(___SCMOBJ);

extern void store_expr_proceed(___SCMOBJ, ___SCMOBJ);

extern ___SCMOBJ get_expr_proceed();
extern ___SCMOBJ get_expr_proceed_1(___SCMOBJ);


extern void test_chin(___SCMOBJ, ___SCMOBJ);
extern void test_chout(___SCMOBJ, ___SCMOBJ);


#endif
