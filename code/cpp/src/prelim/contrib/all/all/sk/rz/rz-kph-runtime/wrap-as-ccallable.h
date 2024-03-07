
#ifndef WRAP_AS_CCALLABLE__H
#define WRAP_AS_CCALLABLE__H


enum class Base_Types { N_A, bt_void, bt_u1, bt_u2, bt_u4, bt_n8, bt_r8 };


ffi_type* get_ffi_type_from_base_type(Base_Types bt)
{
 static QMap<Base_Types, ffi_type*> static_map {{
   {Base_Types::N_A, nullptr},
   {Base_Types::bt_void, &ffi_type_void},
   {Base_Types::bt_u1, &ffi_type_uint8},
   {Base_Types::bt_u2, &ffi_type_uint16},
   {Base_Types::bt_u4, &ffi_type_uint32},
   {Base_Types::bt_n8, &ffi_type_uint64},
   {Base_Types::bt_r8, &ffi_type_double}
                                                }};
 return static_map[bt];
}


Base_Types parse_base_type(QString str)
{
 static QMap<QString, Base_Types> static_map {{
    {"u1", Base_Types::bt_u1},
    {"u2", Base_Types::bt_u2},
    {"u4", Base_Types::bt_u4},
    {"n8", Base_Types::bt_n8},
    {"r8", Base_Types::bt_r8},
    {"void", Base_Types::bt_void},
                                              }};

 return static_map.value(str, Base_Types::N_A);
}


ffi_type* get_ffi_type_from_string(QString str)
{
 Base_Types bt = parse_base_type(str);
 if(bt == Base_Types::N_A)
   return nullptr;
 return get_ffi_type_from_base_type(bt);
}




namespace {

u1 _parse_argument_types(QString args, ffi_type*& ret_type,
  std::vector<ffi_type*>& result, QVector<QString>& values,
  QVector<QPair<QString, Base_Types>>& type_strings)
{
 QStringList qsl = args.simplified().split(' ');

 QString ret = qsl.takeFirst();
 u1 num_args = qsl.takeFirst().toUInt();

// std::vector<ffi_type*> argument_types;
//  std::vector<void*> values;

 result.resize(num_args);
 values.resize(num_args);
 type_strings.resize(num_args);

// ffi_type* argument_types [4];
// void* values [4];

 ret_type = get_ffi_type_from_string(ret);

 int c = 0, ct = 0, cv = 0;
 Base_Types current_base_type = Base_Types::N_A;

 for(QString qs : qsl)
 {
  if(c % 2)
  {
   values[cv] = qs;
//   switch (current_base_type)
//   {
//   case Base_Types::bt_u1: { hold_for_u1[cv] = qs.toUInt(); values[cv] = &hold_for_u1[cv]; } break;
//   case Base_Types::bt_u2: { hold_for_u2[cv] = qs.toUInt(); values[cv] = &hold_for_u2[cv]; } break;
//   case Base_Types::bt_u4: { hold_for_u4[cv] = qs.toUInt(); values[cv] = &hold_for_u4[cv]; } break;
//   case Base_Types::bt_n8: { hold_for_n8[cv] = (quint64) &tests; //qs.toULong();
//     values[cv] = &hold_for_n8[cv]; } break;
//   case Base_Types::bt_r8: { hold_for_r8[cv] = qs.toDouble(); values[cv] = &hold_for_r8[cv]; } break;
//   }
   ++c;
   ++cv;
  }
  else
  {
   current_base_type = parse_base_type(qs);
   result[ct] = get_ffi_type_from_base_type(current_base_type);
   type_strings[ct] = {qs, current_base_type};
   ++c;
   ++ct;
  }

 }
 return num_args;
}

}

u1 parse_argument_types(QString args, ffi_type*& ret_type,
  std::vector<ffi_type*>& result, QVector<QString>& values,
  QVector<QPair<QString, Base_Types>>& type_strings)
{
 return _parse_argument_types(args, ret_type, result, values,
   type_strings);
}

#define MAX_ARGS 16

#define CHECK(x) \
   do { \
      if(!(x)){ \
         printf("Check failed:\n%s\n", #x); \
         abort(); \
      } \
   } while(0)


template<typename FunctionType>
struct CCallable_Types {
 typedef FunctionType C_Function_Pointer_type;
 typedef std::function<FunctionType> Std_Function_Pointer_type;
};




template<typename SIG>
typename CCallable_Types<SIG>::C_Function_Pointer_type*
wrap_as_ccallable(ffi_cif& ffi_interface, typename CCallable_Types<SIG>::Std_Function_Pointer_type fn, u1 _num_args,
  ffi_type* _ret_type, std::vector<ffi_type*>& _arg_types)//u1 _num_args, ffi_type* _ret_type, std::vector<ffi_type*> _arg_types)
{
 typedef CCallable_Types<SIG> cctypes;

 typename cctypes::C_Function_Pointer_type* c_function_ptr;

 //u1 _num_args = num_args;
 //ffi_type* _ret_type = ret_type;
 //std::vector<ffi_type*>& _arg_types = arg_types;
//
//typedef CCallable_Types<quint32 (ffis*)> cctypes;


// u4(*c_function_ptr)(ffis*, u2, u4, r8);

 typename cctypes::Std_Function_Pointer_type* std_function_ptr
 =
 new typename cctypes::Std_Function_Pointer_type
 {
  (typename cctypes::Std_Function_Pointer_type)  fn
 }
 ;

 void* al = ffi_closure_alloc(sizeof(ffi_closure),
                             reinterpret_cast<void**>(&c_function_ptr));

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, _num_args,
      _ret_type, _arg_types.data() //&argument_types[0]
                 ) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                           static_cast<void*>(std_function_ptr),//.get()),
                           reinterpret_cast<void*>(c_function_ptr))
      == FFI_OK)
   {
    return c_function_ptr;
   //c_function_ptr()
   }

  }

 }

 return nullptr;
//?
}



#endif // WRAP_AS_CCALLABLE__H
