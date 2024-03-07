
#ifndef TEST_FFI__H
#define TEST_FFI__H

#include "global-types.h"

#include "accessors.h"

class Test_Ffi
{
 u1 val1_;
 u2 val2_;
 u4 val4_;
 r8 valr8_;

public:

 Test_Ffi();

 ACCESSORS(u1 ,val1)
 ACCESSORS(u2 ,val2)
 ACCESSORS(u4 ,val4)
 ACCESSORS(r8 ,valr8)

 u4 test_report();

};



struct Test_Ffi_Also {

 int v1, v2;

 u4 do_ffi(u2 arg2, u4 arg3, r8 arg4);

 u1 do_ffi_1(u2 arg1);
 u1 do_ffi_2(u2 arg1, r8 arg2);

};


extern "C" {

 void** lookup_dictionary_symbol(QString key, void** value);

 void init_symbol_dictionary();//quint64 user_data);

}

//u1 fdo_ffi(ffis* arg1, u2 arg2, u4 arg3, r8 arg4)
//{
// return arg1->do_ffi(arg2, arg3, arg4);
//}


#endif // def TEST_FFI__H
