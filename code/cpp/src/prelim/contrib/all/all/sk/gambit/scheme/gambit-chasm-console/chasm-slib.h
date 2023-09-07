
//#ifndef CHASMSLIB_H
//#define CHASMSLIB_H

#include "gambit.h"

typedef ___setup_params_struct GAMBIT;

#define SCHEME_LIBRARY_LINKER ___LNK_chasm_2d_slib__

___BEGIN_C_LINKAGE
extern ___mod_or_lnk SCHEME_LIBRARY_LINKER (___global_state);
___END_C_LINKAGE


GAMBIT* setup_gambit()
{
  GAMBIT* g = (GAMBIT*) malloc(sizeof(GAMBIT));
    
  ___setup_params_reset(g);
  g->version = ___VERSION;
  g->linker = SCHEME_LIBRARY_LINKER;

  ___setup(g);
  return g;
}

void cleanup_gambit(GAMBIT* g)
{
  ___cleanup();
  free(g);
}



//extern char* say_hello(char* name);
//extern int inc(int);
//extern void test_symbol(___SCMOBJ);
//extern int fib(int);
//extern void start_repl();

// #endif
