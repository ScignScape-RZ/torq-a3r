

#include <stdio.h>

#define ___VERSION 409005


#include "chasm-utils.h"

#include <new>

extern "C" {
 #include "gambit.h"
 #include "chasm-slib.h"
 #include "chasm-slib-decl.h"

 char* scm_symbol_to_chars(___SCMOBJ s);
 char* scm_kw_to_chars(___SCMOBJ s);
}


void test_symbol(___SCMOBJ s)
{
 char* cs = nullptr;
 long r = scheme_symbol_to_chars(s, cs);

// char* rr = scm_symbol_to_chars(s);
// printf("\nrr = %s\n", rr);
// ___release_string(rr);

 printf("\nsymbol = %s\n", cs);

 if(cs)
   ___release_string(cs);
}



void test_kw(___SCMOBJ s)
{
 char* cs = nullptr;
 long r = scheme_kw_to_chars(s, cs);

// char* rr = scm_kw_to_chars(s);
// printf("\nrr = %s\n", rr);
// ___release_string(rr);

 printf("\nkw = %s\n", cs);

 if(cs)
   ___release_string(cs);
}


//int inc(int x)
//{
// return x + 1;
//}


#include <QString>

QString file = SCRIPTS_FOLDER "/t1.scm";


int main(int argc, char** argv)
{
  GAMBIT* g = setup_gambit();
  char* result;
  eval_scheme_file(file, result);
  printf("%s = %s\n", argv[1], result);
  ___release_string(result);
  cleanup_gambit(g);
  return 0;
}


#ifdef HIDE

int main(int argc, char** argv)
{
  printf("Hello World from C\n\n");

  GAMBIT* g = setup_gambit();

  printf("From Scheme:\n");

//  char* result = eval_string ("(println (incs \"(+ 2 5)\"))");
//  char* result = eval_string ("(write 'xx)(incs \"(symbol->string 'xx)\")");
//
  char* result;
  eval_scheme_file(file, result);
//  char* result = eval_string ("(incs (symbol->string 'xx))");

  printf("%s = %s\n", argv[1], result);
  ___release_string(result);

//  start_repl();


  cleanup_gambit(g);

  return 0;
}



#include <stdio.h>

#define ___VERSION 409005
#include "gambit.h"

#include "somescheme.h"

#define SCHEME_LIBRARY_LINKER ____20_somescheme__

___BEGIN_C_LINKAGE
//extern "C" {
extern ___mod_or_lnk SCHEME_LIBRARY_LINKER (___global_state_struct*);
//}
___END_C_LINKAGE


int main(int argc, char** argv) {
  printf("Hello World, this is from C\n");

  ___setup_params_struct setup_params;
  ___setup_params_reset (&setup_params);

  setup_params.version = ___VERSION;
  setup_params.linker = SCHEME_LIBRARY_LINKER;

  ___setup (&setup_params);

  hello_from_scheme();

  ___cleanup();

  return 0;
}



//int main(int argc, char* rgv[])
//{



//  eval_string("(begin "
//              "(input-port-readtable-set! "
//              "(current-input-port) "
//              "(readtable-keywords-allowed?-set "
//              "(current-readtable) "
//              "(quote prefix) "
//              ") "
//              ") "

//              "(output-port-readtable-set! "
//              "(current-output-port) "
//              "(readtable-keywords-allowed?-set "
//              "(current-readtable) "
//              "(quote prefix) "
//              ") "
//              ") "

//              "(write :asa) )");



#endif

//}
