
#ifndef CHASM_UTILS__H
#define CHASM_UTILS__H



#include <new>
extern "C" {
#include "gambit.h"
}


#include <QString>

void eval_scheme_file(QString file_path, char*& result);

long scheme_symbol_to_chars(___SCMOBJ s, char*& result);

long scheme_kw_to_chars(___SCMOBJ s, char*& result);

#endif
