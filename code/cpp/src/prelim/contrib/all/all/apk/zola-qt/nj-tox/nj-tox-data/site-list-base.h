
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SITE_LIST_BASE__H
#define SITE_LIST_BASE__H


#include "nj-tri-site.h"

#include <QString>
#include <QVector>
#include <QStack>

#include <QMap>

#include "global-types.h"

#include "accessors.h"

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

#include <QDebug>


#include <functional>


struct u2x3
{
 u2 first: 16;
 u2 second: 16;
 u2 third: 16;

 u2x3(u2 _1, u2 _2, u2 _3)
   : first(_1), second(_2), third(_3)
 {
 }

 u2x3()
   : first(0), second(0), third(0)
 {
 }

 u2x3(std::initializer_list<u2> u2s)
 {
  if(u2s.size() < 3)
  {
   third = 0;
   if(u2s.size() > 0)
     first = *u2s.begin();
   else
     first = 0;

   if(u2s.size() > 1)
     second = *(u2s.begin() + 1);
   else
     second = 0;

   qDebug() << "Incomplete u2x3 initializer list: {" << first << ", " << second << "}";
  }
  else
  {
   first = *u2s.begin();
   second = *(u2s.begin() + 1);
   third = *(u2s.begin() + 2);
  }

 }


};

// //  in "production" this should be checked in different environments ...
 //    e.g. obviously there should be no padding ...
union _u2x3_encoded { u2x3 _3_; n8 _1_; };

inline bool operator <(const u2x3& lhs, const u2x3& rhs)
{
 _u2x3_encoded _lhs {._3_ = lhs };
 _u2x3_encoded _rhs {._3_ = rhs };

 return _lhs._1_ < _rhs._1_;
}

inline bool operator ==(const u2x3& lhs, const u2x3& rhs)
{
 _u2x3_encoded _lhs {._3_ = lhs };
 _u2x3_encoded _rhs {._3_ = rhs };

 return _lhs._1_ == _rhs._1_;
}

inline u4 qHash(const u2x3& val)
{
 // //  what's the best way to hash these?
 return val.first & 16;
}


struct _define_setters_data
{
// typedef QPair<u2, u2> u2x3;

 enum class Arg_State {
   Init = 0,  Hanging_To = 9, Hanging_Plus = 8,
   Hanging_Freeze = 7,
   A = 1, P = 2, R = 3, S = 4,
   AP = 12, AR = 13, AS = 14,
   PA = 21, PR = 23, PS = 24,
   RA = 31, RP = 32, RS = 34,
   SA = 41, SP = 42, SR = 43,
   APR = 123, APS = 124,
   ARP = 132, ARS = 134,
   ASP = 142, ASR = 143,
   PAR = 213, PAS = 214,
   PRA = 231, PRS = 234,
   PSA = 241, PSR = 243,
   RAP = 312, RAS = 314,
   RPA = 321, RPS = 324,
   RSA = 341, RSP = 342,
   SAP = 412, SAR = 413,
   SPA = 421, SPR = 423,
   SRA = 431, SRP = 432,
   APRS = 1234, APSR = 1243,
   ARPS = 1324, ARSP = 1342,
   ASPR = 1423, ASRP = 1432,
   PARS = 2134, PASR = 2143,
   PRAS = 2314, PRSA = 2341,
   PSAR = 2413, PSRA = 2431,
   RAPS = 3124, RASP = 3142,
   RPAS = 3214, RPSA = 3241,
   RSAP = 3412, RSPA = 3421,
   SAPR = 4123, SARP = 4132,
   SPAR = 4213, SPRA = 4231,
   SRAP = 4312, SRPA = 4321,
 };

 enum { Arg = (u1) Arg_State::A,
  Pre_Arg = (u1) Arg_State::P,
  Range = (u1) Arg_State::R,
  String = (u1) Arg_State::S,

  Hanging_To = (u1) Arg_State::Hanging_To
 };

 enum class Call_Spec_Adenda {
   N_A = 0, Non_Zero = 1, Non_Simplified = 2
 };

 QStack<Call_Spec_Adenda> call_spec_adenda;

 void push_call_spec_adenda(Call_Spec_Adenda csa)
 {
  call_spec_adenda.push(csa);
 }

 Call_Spec_Adenda current_call_spec_adenda()
 {
  if(call_spec_adenda.isEmpty())
  {
   return Call_Spec_Adenda::N_A;
  }

  return call_spec_adenda.top();
 }

 Call_Spec_Adenda check_pop_call_spec_adenda()
 {
  if(call_spec_adenda.isEmpty())
  {
   return Call_Spec_Adenda::N_A;
  }

  return call_spec_adenda.pop();
 }

 static Arg_State add_state(Arg_State prior, Arg_State new_state);
 static Arg_State expand_state(Arg_State prior, Arg_State new_state);
 static Arg_State recollapse_state(Arg_State& prior);

 Arg_State current_arg_state;


 void add_state(Arg_State new_state)
 {
  current_arg_state = add_state(current_arg_state, new_state);
 }

 void add_state(u1 new_state)
 {
  add_state((Arg_State) new_state);
 }

 void expand_state(Arg_State new_state)
 {
  current_arg_state = expand_state(current_arg_state, new_state);
 }

 void expand_state(u1 new_state)
 {
  expand_state((Arg_State) new_state);
 }

 Arg_State recollapse_state()
 {
  return recollapse_state(current_arg_state);
 }

 QSet<QString> affirmative_flag_strings;
 QSet<QString> affirmative_case_sensitive_flag_strings;
 QSet<QString> falsifying_flag_strings;
 QSet<QString> falsifying_case_sensitive_flag_strings;

 u2 multi_call_count;

// u2 multi_call_count_adj()
// {
//  // //  0 -> 1, everything else the same
//  return multi_call_count + !multi_call_count;
// }

 QSet<u2x3> n0_overrides;

 QVector<u2x3> held_arg;
 QVector<QPair<u2, u2>> held_range;
 QVector<s4> held_pre;
 QVector<QString> held_string;

 QVector<u2x3> carried_arg;

 void check_reuse_carry()
 {
  if(held_arg.isEmpty())
  {
   held_arg = carried_arg;
   add_state(Arg);
  }
 }

 u2 hanging_plus_count;
 u2 suspended_plus_count;

 u2x3 last_column;

 u2 string_options_count;

 std::function<u2 (QVariant)> column_resolver;

 _define_setters_data(); // : last_column(0) {}




 const QVector<s4>& held_pre_or_range();

//? void check_n0_overrides()

 void get_current_arg(QVector<u2x3>& result);
 s4 get_current_arg(QVector<u2x3>& result,
   const QVector<QString>& keys, std::function<u2(u2)> counts_callback);

 const QVector<s4>& held_range_to_vector(QVector<u2x3>& result);

 void reset(u2* check_multi, const QVector<u2x3>& lc);
 void reset(u2* check_multi, u2x3 lc);
 void reset(u2* check_multi);

// bool check_multi(QVector<u2x3>& vec);

 void freeze_pre_arg()
 {
  if(held_pre.size())
    froze_pre_arg = held_pre.last();
  froze_pre_arg_ptr = &froze_pre_arg;
 }

 u2* froze_pre_arg_ptr;

private:

 QVector<s4> _range;

 u2 froze_pre_arg;


};



template<typename SITE_Type>
struct csv_field_setters_by_column
{
// typedef QPair<u2, u2> u2x3;

 enum class Proc_Options {

   m_QString_u2, m_QString_QString,
   n_QString_u2, n_QString_QString,

   m_QString, n_QString,

   m_void, n_void,

   m_QString_u2_n0, m_QString_QString_n0,
   n_QString_u2_n0, n_QString_QString_n0,

   m_QString_n0, n_QString_n0,

   m_void_indexed, n_void_indexed,
   m_void_n0, n_void_n0,

 };

 enum class Call_Specs : u2{
   Generic = 0,
   Non_Empty = 1,
   Only_Empty = 2,
   Space_Empty = 4,
   Non_Zero = 8,
   Void_Pre = 16,
   Void_True = 32,
   Void_False = 64,
   Void_Post = 128,
 };

 friend QPair<u2, u2> Call_Specs_split_u2(Call_Specs _s)
 {
  static u2 first_mask = 15;
  static u2 second_mask = 240;

  return {((u2) _s) & first_mask, ((u2) _s) & second_mask};
 }

 friend QPair<Call_Specs, Call_Specs> Call_Specs_split(Call_Specs _s)
 {
  auto pr = Call_Specs_split_u2(_s);

  return {(Call_Specs)pr.first, (Call_Specs)pr.second};
 }


 Proc_Options get_n0_override(Proc_Options procs)
 {
  switch (procs)
  {
#define CASE_MACRO(m) case Proc_Options::m##_n0: return Proc_Options::m;
  CASE_MACRO(m_QString_u2)
  CASE_MACRO(m_QString_QString)
  CASE_MACRO(n_QString_u2)
  CASE_MACRO(n_QString_QString)
  CASE_MACRO(m_QString)
  CASE_MACRO(n_QString)
  CASE_MACRO(m_void)
  CASE_MACRO(n_void)
#undef CASE_MACRO
  default:
   break;
  }
  return procs;
 }


 // Proc_Options
 void check_n0_switch(const QSet<u2x3>& n0_overrides, u2x3 col, Proc_Options props)
 {
  if(n0_overrides.contains(col))
  {
   switch (props)
   {
//   case Proc_Options::m_QString_u2_n0:
//    m_QString_u2[col] = m_QString_u2_n0.take(col);
//    proc_options[col] = get_n0_override(props);
//    break;

 #define CASE_MACRO(m) case Proc_Options::m##_n0: \
     m[col] = m##_n0.take(col); \
     proc_options[col] = {get_n0_override(props), Call_Specs::Generic}; \
     break;
    CASE_MACRO(m_QString_u2)
    CASE_MACRO(m_QString_QString)
    CASE_MACRO(n_QString_u2)
    CASE_MACRO(n_QString_QString)
    CASE_MACRO(m_QString)
    CASE_MACRO(n_QString)
    CASE_MACRO(m_void)
    CASE_MACRO(n_void)
 #undef CASE_MACRO
     break;
    default:
     // //  we shouldn't get here; maybe some debug message?
     break;
   }
  }
 }



 Proc_Options check_n0_override(const QSet<u2x3>& n0_overrides, u2x3 col, Proc_Options procs)
 {
  if(n0_overrides.contains(col))
    return get_n0_override(procs);
  return procs;
 }


 QMap<u2x3, void (SITE_Type::*)(QString, u2)> m_QString_u2, m_QString_u2_n0;
 QMap<u2x3, void (SITE_Type::*)(QString, QString)> m_QString_QString, m_QString_QString_n0;
 QMap<u2x3, void (*)(SITE_Type*, QString, u2)> n_QString_u2, n_QString_u2_n0;
 QMap<u2x3, void (*)(SITE_Type*, QString, QString)> n_QString_QString, n_QString_QString_n0;

 QMap<u2x3, void (SITE_Type::*)(QString)> m_QString, m_QString_n0;
 QMap<u2x3, void (*)(SITE_Type*, QString)> n_QString, n_QString_n0;

 QMap<u2x3, void (SITE_Type::*)()> m_void, m_void_n0;
 QMap<u2x3, void (*)(SITE_Type*)> n_void, n_void_n0;

 QMap<u2x3, QVector<QPair<void (SITE_Type::*)(), Call_Specs>>> m_void_supplement;
 QMap<u2x3, QVector<QPair<void (*)(SITE_Type*), Call_Specs>>> n_void_supplement;


 QMap<QPair<u2x3, QString>, void (SITE_Type::*)()> m_void_indexed;
 QMap<QPair<u2x3, QString>, void (*)(SITE_Type*)> n_void_indexed;

 QMap<u2x3, QPair<Proc_Options, Call_Specs>> proc_options;

 QMap<u2, QVector<u2>> proc_options_counts;

 QMap<u2x3, u2> preset_args_u2;
 QMap<u2x3, QString> preset_args_QString;

 QString column_string_pattern(QString* reset = nullptr)
 {
  if(reset)
    _column_string_pattern = *reset;
  else if(_column_string_pattern.isNull())
    _column_string_pattern = "C%1";
  return _column_string_pattern;
 }

 template<typename FN_Type>
 void add(Proc_Options props, Call_Specs call_specs, const QVector<u2x3>& cols,
   u2* multi_count,
   const QSet<u2x3>& n0_overrides,
   FN_Type fn, const void* pre = nullptr,
   const void* adjunct = nullptr, u2 insert_count = 0)
 {
  std::function<void(u2x3&)> reconcile_multi_count = (multi_count && *multi_count)?
    [multi_count](u2x3& col)
  {
   col.third = *multi_count;
  } : (std::function<void(u2x3&)>) [](u2x3& col) {};

  //(std::function<void(u2x3&)>) nullptr;

//  : nullptr;

//  auto reconcile_multi_count =  [_reconcile_multi_count](u2x3& col)
//  {
//   if(_reconcile_multi_count)
//     _reconcile_multi_count(col);
//  };


  switch(props)
  {

//  case Proc_Options::m_void:
//   for(u2 col : cols) { m_void[col] = (decltype(m_void[col])) fn; } break;

//  case Proc_Options::m_void_indexed:
//   {
//    QVector<QString>* qsv = (QVector<QString>*) pre;
//    u2 i = 0;
//    for(u2 col : cols)
//    {
//     m_void_indexed[{col, qsv->value(i)}] = (decltype(m_void[col])) fn;
//     ++i;
//    } break;
//   }

  // //  different case-code for the _indexed cases
#define CASE_MACRO(m) \
   case Proc_Options::m##_indexed: \
    {QVector<QString>* qsv = (QVector<QString>*) pre; \
     u2 i = 0; \
     for(u2x3 col : cols) \
     { \
      reconcile_multi_count(col); \
      m##_indexed[{col, qsv->value(i)}] = (decltype(m[col])) fn; \
      ++i; \
      proc_options[col] = {check_n0_override(n0_overrides, col, Proc_Options::m##_indexed), call_specs}; \
     }} break; \

    CASE_MACRO(m_void)
    CASE_MACRO(n_void)
#undef CASE_MACRO


#define CASE_MACRO(m) \
   case Proc_Options::m: \
    for(u2x3 col : cols) { reconcile_multi_count(col); \
      m[col] = (decltype(m[col])) fn; \
      proc_options[col] = {Proc_Options::m, call_specs}; check_n0_switch(n0_overrides, col, props);  }  break; \

  CASE_MACRO(m_void)
  CASE_MACRO(n_void)

  CASE_MACRO(m_void_n0)
  CASE_MACRO(n_void_n0)



  CASE_MACRO(m_QString_u2)
  CASE_MACRO(m_QString_QString)
  CASE_MACRO(n_QString_u2)
  CASE_MACRO(n_QString_QString)

  CASE_MACRO(m_QString)
  CASE_MACRO(n_QString)

  CASE_MACRO(m_QString_u2_n0)
  CASE_MACRO(m_QString_QString_n0)
  CASE_MACRO(n_QString_u2_n0)
  CASE_MACRO(n_QString_QString_n0)

  CASE_MACRO(m_QString_n0)
  CASE_MACRO(n_QString_n0)
  }

  if(pre || insert_count)
  {
   u2 count = 0;
   switch (props)
   {
   case Proc_Options::m_QString_u2:
   case Proc_Options::n_QString_u2:
   case Proc_Options::m_QString_u2_n0:
   case Proc_Options::n_QString_u2_n0:
    if(pre)
    {
     for(s4 p : * (const QVector<s4>*) pre)
     {
      preset_args_u2[cols.value(count)] = (u2) p;
      ++count;
     }
     if(adjunct)
     {
      u2 froze = *(u2*) adjunct;
      while(count < cols.size())
      {
       preset_args_u2[cols.value(count)] = froze;
       ++count;
      }
     }
    }
    else
    {
     for(count = 0; count < insert_count; ++count)
     {
      preset_args_u2[cols.value(count)] = cols.value(count).first; //?
     }
    }
    break;
   case Proc_Options::m_QString_QString:
   case Proc_Options::n_QString_QString:
   case Proc_Options::m_QString_QString_n0:
   case Proc_Options::n_QString_QString_n0:
    if(pre)
    {
     for(QString p : * (const QVector<QString>*) pre)
     {
      preset_args_QString[cols.value(count)] = p;
      ++count;
     }
    }
    else
    {
     // //  In this case we assume the column is identified by
      //    a key which incorporates the coulmn number somehow ...
     for(count = 0; count < insert_count; ++count)
     {
      preset_args_QString[cols.value(count)] =
        column_string_pattern().arg(cols.value(count).first);
     }
    }
    break;
   }
  }
 }


 csv_field_setters_by_column(QVector<void (SITE_Type::*)(QString, u2)> vec)
 {
  u2 column = 0;
  for(auto md : vec)
  {
   m_QString_u2[column] = md;
   ++column;
  }
 }

 csv_field_setters_by_column(QVector<void (SITE_Type::*)(QString)> vec)
 {
  u2 column = 0;
  for(auto md : vec)
  {
   m_QString[column] = md;
   ++column;
  }
 }

 csv_field_setters_by_column(decltype(m_QString) mds)
   : m_QString(mds)
 { }

 csv_field_setters_by_column(decltype(n_QString) nds)
   : n_QString(nds)
 { }

 csv_field_setters_by_column() {}

private:

 QString _column_string_pattern;


};




template<typename SITE_Type>
struct csv_field_getters_by_column
{
 typedef QVector<QString (SITE_Type::*)() const> methods_0_vector_type;

 typedef QMapIterator<u2, QString (SITE_Type::*)() const> methods_0_iterator_type;
 typedef QMapIterator<u2, QString (*)()> non_methods_0_iterator_type;
 typedef QMapIterator<u2, QString> defaults_iterator_type;

 methods_0_iterator_type methods_0_iterator()
 {
  return methods_0_iterator_type(methods_0);
 }

 non_methods_0_iterator_type non_methods_0_iterator()
 {
  return non_methods_0_iterator_type(non_methods_0);
 }

 defaults_iterator_type defaults_iterator()
 {
  return defaults_iterator_type(defaults);
 }

 QMap<u2, QString (SITE_Type::*)() const> methods_0;
 QMap<u2, QString (SITE_Type::*)(u1) const> methods_1;

 QMap<u2, QString (*)()> non_methods_0;
 QMap<u2, QString (*)(u1)> non_methods_1;

 QMap<u2, QString> defaults;

 QMap<u2, QString> methods_1_args;

 csv_field_getters_by_column<SITE_Type> copy()
 {
  csv_field_getters_by_column<SITE_Type> result;

  result.methods_0 = methods_0;
  result.methods_1 = methods_1;
  result.non_methods_0 = non_methods_0;
  result.non_methods_1 = non_methods_1;
  result.defaults = defaults;
  result.methods_1_args = methods_1_args;

  return result;
 }

 template<typename MAP_Type>
 u2 take_nullptr(MAP_Type& m)
 {
  u2 key = 0;
  QMapIterator<typename MAP_Type::key_type, typename MAP_Type::mapped_type> it(m);
  while(it.hasNext())
  {
   it.next();
   if(it.value() == nullptr)
   {
    key = it.key();
    break;
   }
  }

  if(key)
    m.remove(key);

  return key;
 }

#define INSERT_REPLACEMENT_IMPL(m) \
 csv_field_getters_by_column& insert_replacement(typename decltype(m)::mapped_type md) \
 { \
  u2 found = take_nullptr(m); \
  if(found) \
    m[found] = md; \
  return *this; \
 } \

 INSERT_REPLACEMENT_IMPL(methods_0)
 INSERT_REPLACEMENT_IMPL(non_methods_0)
 INSERT_REPLACEMENT_IMPL(methods_1)
 INSERT_REPLACEMENT_IMPL(non_methods_1)


 csv_field_getters_by_column& insert_default(QString str)
 {
  u2 found;
  do{
   if((found = take_nullptr(methods_0)))
     break;
   if((found = take_nullptr(non_methods_0)))
     break;
   if((found = take_nullptr(methods_1)))
     break;
   if((found = take_nullptr(non_methods_1)))
     break;
  } while(false);

  if(found)
    defaults[found] = str;

  return *this;
 }

 csv_field_getters_by_column() {}

 csv_field_getters_by_column(decltype(methods_0) mds)
   : methods_0(mds)
 { }


 csv_field_getters_by_column(methods_0_vector_type vec, s4 offset = 0)
 {
  u2 column = offset + 1;
  for(auto md : vec)
  {
   methods_0[column] = md;
   ++column;
  }
 }


 u2 total_columns()
 {
  QList<u2>
    m_0 = methods_0.keys(),
    n_0 = non_methods_0.keys(),
    m_1 = methods_1.keys(),
    n_1 = non_methods_1.keys(),
    d = defaults.keys()
   ;

  auto max_element = [](const QList<u2>& l) -> u2
  {
   if(l.isEmpty())
     return 0;

   return *std::max_element(l.begin(), l.end());
  };

  QList<u2> maxes {
    max_element(m_0),
    max_element(n_0),

    max_element(m_1),
    max_element(n_1),

    max_element(d),
  };

  return max_element(maxes);

//  return methods_0.size() + non_methods_0.size()
//    + methods_1.size() + non_methods_1.size()
//    + defaults.size();
 }


};


template<typename SITE_Type>
class Site_List_Base
{

protected:

 QVector<SITE_Type> sites_;


 csv_field_setters_by_column<SITE_Type>  csv_field_setters_;
 csv_field_getters_by_column<SITE_Type>  csv_field_getters_;

 QString file_path_;

 QMap<QString, QString> file_paths_;

 QMap<QString, QString (SITE_Type::*)() const> json_field_getters_;
 QMap<QString, void (SITE_Type::*)(QString)> json_field_setters_;

 QStringList original_header_;

 Site_List_Base(QString file_path = {})
   :  file_path_(file_path)
 {

 }

// ACCESSORS__RGET(QVector<NJ_TRI_Site> ,sites)
// ACCESSORS__CONST_RGET(QVector<NJ_TRI_Site> ,sites)

// ACCESSORS(QString ,data_source_string)

//// ACCESSORS__FNP__VOID(QString& ,address_edit_callback)
//// ACCESSORS__FNP__VOID(QString& ,municipality_edit_callback)


 _define_setters_data define_setters_data_;

private:

 auto& get_proc_options_counts()
 {
  return csv_field_setters_.proc_options_counts;
 }

 auto& get_proc_options()
 {
  return csv_field_setters_.proc_options;
 }

 union _define_setters;

 struct _define_setters_nonzero {
  Site_List_Base* _this;

  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString)::mapped_type m_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString)::mapped_type n_QString_type;

  _define_setters operator [](m_QString_type fn)
  {
   _define_setters result {_this};
   result._nonzero();
   return result.operator [](fn);
  }

  _define_setters operator [](n_QString_type fn)
  {
   _define_setters result {_this};
   result._nonzero();
   return result.operator [](fn);
  }


  template<typename FN_Type>
  _define_setters operator [](FN_Type fn)
  {
   _define_setters result {_this};
   result._nonzero();
   return result.operator [](fn);
  }

  template<typename... ARGS_Types>
  _define_setters operator()(ARGS_Types... args)
  {
   _define_setters result {_this};
   result._nonzero();
   return result.operator ()(args...);
  }
 };

 struct _define_setters_major {
  Site_List_Base* _this; // reup;
 };



 union _define_setters
 {
  _define_setters_major major;
  _define_setters_nonzero nonzero;


  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_void)::mapped_type m_void_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString)::mapped_type m_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString_u2)::mapped_type m_QString_u2_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString_QString)::mapped_type m_QString_QString_type;

  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_void)::mapped_type n_void_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString)::mapped_type n_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString_u2)::mapped_type n_QString_u2_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString_QString)::mapped_type n_QString_QString_type;

  typedef typename csv_field_setters_by_column<SITE_Type>::Proc_Options Props;


#define _th major._this

  _define_setters _nonzero()
  {
   _th->define_setters_data_.push_call_spec_adenda(decltype(_th->define_setters_data_)::Call_Spec_Adenda::Non_Zero);
   return *this;
  }

  _define_setters add_affirmative_flag_string(QString s)
  {
   _th->define_setters_data_.affirmative_flag_strings.insert(s.toLower());
   return *this;
  }

  _define_setters add_affirmative_flag_strings(QStringList ss)
  {
   for(QString s : ss)
     add_affirmative_flag_string(s);
   return *this;
  }

  _define_setters add_affirmative_case_sensitive_flag_string(QString s)
  {
   _th->define_setters_data_.affirmative_case_sensitive_flag_strings.insert(s);
   return *this;
  }

  _define_setters add_affirmative_case_sensitive_flag_strings(QStringList qsl)
  {
   for(QString s : qsl)
     add_affirmative_case_sensitive_flag_string(s);
   return *this;
  }


  _define_setters add_falsifying_flag_string(QString s)
  {
   _th->define_setters_data_.falsifying_flag_strings.insert(s.toLower());
   return *this;
  }

  _define_setters add_falsifying_flag_strings(QStringList ss)
  {
   for(QString s : ss)
     add_falsifying_flag_string(s);
   return *this;
  }

  _define_setters add_falsifying_case_sensitive_flag_string(QString s)
  {
   _th->define_setters_data_.falsifying_case_sensitive_flag_strings.insert(s);
   return *this;
  }

  _define_setters add_falsifying_case_sensitive_flag_strings(QStringList qsl)
  {
   for(QString s : qsl)
     add_falsifying_case_sensitive_flag_string(s);
   return *this;
  }


  _define_setters default_affirmative_flag_strings()
  {
   add_affirmative_flag_strings({"yes", "true"});
   return *this;
  }

  _define_setters default_nonempty_falsifying_flag_strings()
  {
   add_falsifying_flag_strings({"no", "false"});
   return *this;
  }

  _define_setters default_falsifying_flag_strings()
  {
   default_nonempty_falsifying_flag_strings();
   add_falsifying_flag_string({""});
   return *this;
  }

  _define_setters default_flag_strings()
  {
   default_affirmative_flag_strings();
   default_falsifying_flag_strings();
   return *this;
  }

  _define_setters reset_affirmative_flag_strings()
  {
   _th->define_setters_data_.affirmative_flag_strings.clear();
   return *this;
  }

  _define_setters reset_affirmative_case_sensitive_flag_strings()
  {
   _th->define_setters_data_.affirmative_case_sensitive_flag_strings.clear();
   return *this;
  }

  _define_setters reset_falsifying_flag_strings()
  {
   _th->define_setters_data_.falsifying_flag_strings.clear();
   return *this;
  }

  _define_setters reset_falsifying_case_sensitive_flag_strings()
  {
   _th->define_setters_data_.falsifying_case_sensitive_flag_strings.clear();
   return *this;
  }


  _define_setters reset_affirmative_flag_strings(QStringList qsl)
  {
   reset_affirmative_flag_strings();
   add_affirmative_flag_strings(qsl);
   return *this;
  }

  _define_setters reset_affirmative_case_sensitive_flag_strings(QStringList qsl)
  {
   reset_affirmative_case_sensitive_flag_strings();
   add_affirmative_case_sensitive_flag_strings(qsl);
   return *this;
  }

  _define_setters reset_falsifying_flag_strings(QStringList qsl)
  {
   reset_falsifying_flag_strings();
   add_falsifying_flag_strings(qsl);
   return *this;
  }

  _define_setters reset_falsifying_case_sensitive_flag_strings(QStringList qsl)
  {
   reset_falsifying_case_sensitive_flag_strings();
   add_falsifying_case_sensitive_flag_strings(qsl);
   return *this;
  }


//  typedef QPair<u2, u2> u2x3;

  template<typename FN_Type>
  void ops_void(Props props, FN_Type fn, QVector<u2x3>* cols = nullptr)
  {
   auto& dsd = _th->define_setters_data_;
   auto call_specs = pop_call_specs();

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::AS:
    _th->add_setter(props, call_specs, dsd.held_arg, &dsd.multi_call_count, dsd.n0_overrides, fn, &dsd.held_string);
    if(cols)
    {
     QVector<u2x3> c = dsd.held_arg;
     *cols = c;
    }
    dsd.reset(&dsd.multi_call_count, dsd.held_arg);
    break;

    // //  is this a case where &dsd.multi_call_count shuold be replaced by nullptr?
   case _define_setters_data::Arg_State::S:
    _th->add_setter(props, call_specs, {dsd.last_column}, &dsd.multi_call_count, dsd.n0_overrides, fn, &dsd.held_string);
    if(cols)
      *cols = {dsd.last_column};
    dsd.reset(&dsd.multi_call_count, dsd.last_column);
    break;

    // // anything else?

   default: //  mostly Arg_State::A, right?
    _th->add_setter(props, call_specs, dsd.held_arg, &dsd.multi_call_count, dsd.n0_overrides, fn);
    if(cols)
    {
     // //  don't want an assign-ref-to-ref situation ....
     QVector<u2x3> c = dsd.held_arg;
     *cols = c;
    }
    dsd.reset(&dsd.multi_call_count, dsd.held_arg);
   }
  }


  typename csv_field_setters_by_column<SITE_Type>::Call_Specs pop_call_specs()
  {
   auto& dsd = _th->define_setters_data_;

   switch (dsd.current_call_spec_adenda())
   {
   case _define_setters_data::Call_Spec_Adenda::N_A:
    return csv_field_setters_by_column<SITE_Type>::Call_Specs::Generic;
    break;

   case _define_setters_data::Call_Spec_Adenda::Non_Zero:
    return csv_field_setters_by_column<SITE_Type>::Call_Specs::Non_Zero;
    break;

   case _define_setters_data::Call_Spec_Adenda::Non_Simplified:
    // //  something about space not empty ...
    return csv_field_setters_by_column<SITE_Type>::Call_Specs::Generic;
    break;

   default:
    return csv_field_setters_by_column<SITE_Type>::Call_Specs::Generic;
    break;

   }
  }

  template<typename FN_Type>
  void ops_QString(Props props, FN_Type fn)
  {
   auto& dsd = _th->define_setters_data_;
   auto call_specs = pop_call_specs();

   QVector<u2x3> cols;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::Init:
    dsd.held_arg.push_back({dsd.last_column.first + 1, 1, 1}); //??dsd.multi_call_count_adj()}); // //z
    // //  fallthrough
   case _define_setters_data::Arg_State::A:
    dsd.get_current_arg(cols);
    _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, fn);
    break;

   case _define_setters_data::Arg_State::R:
    dsd.held_range_to_vector(cols);
    _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, fn);
    break;
   }
   dsd.reset(&dsd.multi_call_count, cols);
  }


  template<typename FN_Type>
  void ops_QString_u2(Props props, FN_Type arg)
  {
   auto& dsd = _th->define_setters_data_;
   auto call_specs = pop_call_specs();

   QVector<u2x3> cols;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::A:
    dsd.get_current_arg(cols);
    _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, nullptr, nullptr, cols.size());
    break;

   case _define_setters_data::Arg_State::PA:
    dsd.get_current_arg(cols);
    if(dsd.held_pre.isEmpty())
      _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, nullptr, nullptr, dsd.hanging_plus_count);
    else
      _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, &dsd.held_pre, dsd.froze_pre_arg_ptr);
    break;

   case _define_setters_data::Arg_State::R:
    {
     const QVector<s4>& r = dsd.held_range_to_vector(cols);
     _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, &r);
    }
    break;

   default:
    break;
   }
   dsd.reset(&dsd.multi_call_count, cols);
  }

  template<typename FN_Type>
  void ops_QString_QString(Props props, FN_Type arg)
  {
   auto& dsd = _th->define_setters_data_;
   auto call_specs = pop_call_specs();



   // for now ....
   auto counts_callback = [](u2) -> u2
   {
    return 1;
   };

   QVector<u2x3> cols;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::S:
    {
     const QVector<QString>& hs = dsd.held_string;

     // //   get_current_arg() with strings will
      //     return a nonzero value if the strings
      //     are matched by column_resolver lookups
     if(dsd.get_current_arg(cols, hs, counts_callback))
       _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, &hs);
     else
       _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, nullptr, nullptr, cols.count());
    }
    break;

   // //  what's the right way to handle mixed in these cases?
   case _define_setters_data::Arg_State::SA:
    dsd.get_current_arg(cols);
    _th->add_setter(props, call_specs, cols, &dsd.multi_call_count, dsd.n0_overrides, arg, &dsd.held_string);
    break;
   // //  case AS and so on ...

   default:
    break;
   }
   dsd.reset(&dsd.multi_call_count, cols);
  }

  _define_setters operator [] (m_void_type arg)
  {
   ops_void(Props::m_void_n0, arg);
   return *this;


//   auto& dsd = _th->define_setters_data_;
//   switch(dsd.current_arg_state)
//   {
//   case _define_setters_data::Arg_State::A:
//    ops_void(Props::m_void, arg);
//    break;
//   case _define_setters_data::Arg_State::AS:
//   case _define_setters_data::Arg_State::S:
//    // //  any others?
//    ops_void(Props::m_void_indexed, arg);
//    break;
//   default:
//    break;
//   }
//   return *this;

  }

  _define_setters operator [] (m_QString_type arg)
  {
   ops_QString(Props::m_QString_n0, arg);
   return *this;
  }

  _define_setters operator [] (m_QString_u2_type arg)
  {
   ops_QString_u2(Props::m_QString_u2_n0, arg);
   return *this;
  }

  _define_setters operator [] (m_QString_QString_type arg)
  {
   ops_QString_QString(Props::m_QString_QString_n0, arg);
   return *this;
  }

  _define_setters operator [] (n_void_type arg)
  {
   ops_void(Props::n_void, arg);
   return *this;

//   auto& dsd = _th->define_setters_data_;
//   switch(dsd.current_arg_state)
//   {
//   case _define_setters_data::Arg_State::A:
//    ops_void(Props::n_void_n0, arg);
//    break;
//   case _define_setters_data::Arg_State::AS:
//   case _define_setters_data::Arg_State::S:
//    // //  any others?
//    ops_void(Props::n_void_indexed, arg);
//    break;
//   default:
//    break;
//   }
//   return *this;

  }


  _define_setters operator [] (n_QString_type arg)
  {
   ops_QString(Props::n_QString_n0, arg);
   return *this;
  }

  _define_setters operator [] (n_QString_u2_type arg)
  {
   ops_QString_u2(Props::n_QString_u2_n0, arg);
   return *this;
  }

  _define_setters operator [] (n_QString_QString_type arg)
  {
   ops_QString_QString(Props::n_QString_QString_n0, arg);
   return *this;
  }


  _define_setters operator [] (QString arg)
  {
   auto& dsd = _th->define_setters_data_;
   ++dsd.string_options_count;
   dsd.held_string.push_back(arg);
   dsd.add_state(_define_setters_data::String);
   return *this;
  }

  _define_setters operator [] (int arg)
  {
   auto& dsd = _th->define_setters_data_;
   QMap<u2, QVector<u2>>& counts = _th->get_proc_options_counts();
   auto& props = _th->get_proc_options();


   _define_setters_data::Arg_State h = dsd.recollapse_state();

   if(h == _define_setters_data::Arg_State::Hanging_To)
   {
    u4 index = dsd.held_arg.size();
    u2 l = index ? dsd.held_arg.last().first : 0;
    u2 min = qMin(l, (u2) arg);
    u2 max = qMax(l, (u2) arg);
    u2 diff = max - min;

    dsd.held_arg.resize(index + diff);
    for(u2 i = min + 1; i <= max; ++i, ++index)
      dsd.held_arg[index] = {i, 1, 1}; //??dsd.multi_call_count}; //? 1?
   }
   else
   {
    u2 c;
    if(counts.contains(arg))
    {
     counts[arg].push_back(1);
     c = counts[arg].size();
    }
    else if(props.contains({arg, 1, 1})) //?? dsd.multi_call_count
    {
     counts[arg] = {1, 1};
     c = 2;
    }
    else
      c = 1;

    dsd.held_arg.push_back({arg, c, 1}); // //z
   }

   dsd.add_state(_define_setters_data::Arg);

   switch(dsd.current_arg_state)
   {
   // //  any others?
   case _define_setters_data::Arg_State::PA:
    // //  the hanging_plus signals right after ++;
     //    we assume this continues to next setter
    if(h == _define_setters_data::Arg_State::Hanging_Plus)
    {
     if(dsd.suspended_plus_count) // // so we're resuming
     {
      dsd.held_pre.push_back(arg);
      dsd.hanging_plus_count = dsd.suspended_plus_count + 1;
     }
     else
       dsd.hanging_plus_count = 1;
    }
    else if(dsd.hanging_plus_count)
    {
     if(dsd.suspended_plus_count) // // we've suspended before
     {
      dsd.held_pre.push_back(arg);
     }
     ++dsd.hanging_plus_count;
    }
    else if(dsd.froze_pre_arg_ptr)
      ; // // anything to do?
    else
    {
     while(dsd.held_pre.size() < dsd.held_arg.size())
       dsd.held_pre.push_back(dsd.held_pre.last() + 1);
    }
    break;
   default: break;
   }
   return *this;
  }


  _define_setters operator () ()
  {
   auto& dsd = _th->define_setters_data_;

   if(dsd.multi_call_count)
   {
    auto& counts = _th->csv_field_setters_.proc_options_counts;
    auto& cols = dsd.held_arg;

    for(u2x3 col : cols)
    {
     QVector<u2>& vec = counts[col.first];
     if(vec.size() < col.second)
       vec.resize(col.second);
     vec[col.second - 1] = dsd.multi_call_count - 1;
    }

    dsd.multi_call_count = 0;
    dsd.reset(nullptr, dsd.held_arg);
   }

   else if(dsd.held_arg.isEmpty())
   {
    // // anything here?
   }
   else
   {
    dsd.n0_overrides.insert(dsd.held_arg.last());
   }

   return *this;
  }

  void op_mvoid(m_void_type arg, QVector<u2x3>* cols = nullptr)
  {
   auto& dsd = _th->define_setters_data_;

   switch(dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::A:
    ops_void(Props::m_void, arg, cols);
    break;
   case _define_setters_data::Arg_State::AS:
   case _define_setters_data::Arg_State::S:
    // //  any others?
    ops_void(Props::m_void_indexed, arg, cols);
    break;
   default:
    break;
   }
  }

  _define_setters operator () (m_void_type arg)
  {
   op_mvoid(arg);
   return *this;
  }


  _define_setters Pre (m_void_type arg)
  {
   auto& dsd = _th->define_setters_data_;
   dsd.check_reuse_carry();

   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr].push_back({arg, specs::Void_Pre});

   dsd.carried_arg = cols;
   return *this;
  }

  _define_setters True (m_void_type arg)
  {
   auto& dsd = _th->define_setters_data_;
   dsd.check_reuse_carry();

   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr].push_back({arg, specs::Void_True});

   dsd.carried_arg = cols;
   return *this;
  }

  _define_setters False (m_void_type arg)
  {
   auto& dsd = _th->define_setters_data_;
   dsd.check_reuse_carry();

   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr].push_back({arg, specs::Void_False});

   dsd.carried_arg = cols;
   return *this;
  }

  _define_setters Fin (m_void_type arg)
  {
   auto& dsd = _th->define_setters_data_;
   dsd.check_reuse_carry();

   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr].push_back({arg, specs::Void_Post});

   dsd.carried_arg = cols;
   return *this;
  }


  _define_setters operator () (m_void_type arg1, m_void_type arg2)
  {
   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg2, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr] = {
       {arg1, specs::Void_True},
       {arg2, specs::Void_False} };
   return *this;
  }

  _define_setters operator () (m_void_type arg1, m_void_type arg2, m_void_type arg3)
  {
   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg3, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr] = {
       {arg1, specs::Void_True},
       {arg2, specs::Void_False},
       {arg3, specs::Void_Post}
     };

//     _th->csv_field_setters_.m_void_supplement[pr] = {arg1, arg2, arg3};
   return *this;
  }

  _define_setters operator () (m_void_type arg1, m_void_type arg2,
     m_void_type arg3, m_void_type arg4)
  {
   typedef typename decltype(_th->csv_field_setters_)::Call_Specs specs;

   QVector<u2x3> cols;
   op_mvoid(arg4, &cols);

   for(auto pr : cols)
     _th->csv_field_setters_.m_void_supplement[pr] = {
         {arg1, specs::Void_Pre},
         {arg2, specs::Void_True},
         {arg3, specs::Void_False},
         {arg4, specs::Void_Post}
       }
       ;
   return *this;
  }

  _define_setters operator () (m_QString_type arg)
  {
   ops_QString(Props::m_QString, arg);
   return *this;
  }

  _define_setters operator () (m_QString_u2_type arg)
  {
   ops_QString_u2(Props::m_QString_u2, arg);
   return *this;
  }

  _define_setters operator () (m_QString_QString_type arg)
  {
   ops_QString_QString(Props::m_QString_QString_n0, arg);
   return *this;
  }

  _define_setters operator () (n_void_type arg)
  {
   auto& dsd = _th->define_setters_data_;
   switch(dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::A:
    ops_void(Props::n_void_n0, arg);
    break;
   case _define_setters_data::Arg_State::AS:
   case _define_setters_data::Arg_State::S:
    // //  any others?
    ops_void(Props::n_void_indexed, arg);
    break;
   default:
    break;
   }
   return *this;
  }

  _define_setters operator () (n_QString_type arg)
  {
   ops_QString(Props::n_QString, arg);
   return *this;
  }

  _define_setters operator () (n_QString_u2_type arg)
  {
   ops_QString_u2(Props::n_QString_u2, arg);
   return *this;
  }

  _define_setters operator () (n_QString_QString_type arg)
  {
   ops_QString_QString(Props::n_QString_QString, arg);
   return *this;
  }

  _define_setters operator () (int arg)
  {
   auto& dsd = _th->define_setters_data_;

   if(dsd.hanging_plus_count)
   {
    // //  if hanging_plus gets suspended then thereafter
     //    the arg should be copied into pre_arg for the
     //    hanging-plus sections ...

    if(dsd.suspended_plus_count == 0)
    {
     // //  i.e., suspended for the first time
     for(u2 i = 0; i < dsd.hanging_plus_count; ++i)
       dsd.held_pre.push_back(dsd.held_arg.value(i).first);
    }
    dsd.suspended_plus_count = dsd.hanging_plus_count;
    dsd.hanging_plus_count = 0;
   }

   dsd.held_pre.push_back(arg);
   dsd.add_state(_define_setters_data::Pre_Arg);

   return *this;
  }

  _define_setters operator ++ (int)
  {
   auto& dsd = _th->define_setters_data_;
   if(dsd.current_arg_state == _define_setters_data::Arg_State::Init)
   {
    dsd.add_state(_define_setters_data::Pre_Arg);
    dsd.expand_state(_define_setters_data::Arg_State::Hanging_Plus);
   }
   else
     ++dsd.multi_call_count;

   return *this;
  }

  _define_setters operator () (QString arg)
  {
   _th->define_setters_data_.held_string.push_back(arg);
   _th->define_setters_data_.add_state(_define_setters_data::String);
   return *this;
  }

  _define_setters operator () (int arg, int arg1)
  {
   _th->define_setters_data_.held_range.push_back({arg, arg1});
   _th->define_setters_data_.add_state(_define_setters_data::Range);
   return *this;
  }

  template<typename ...Ts>
  _define_setters operator () (QString a1, QString a2, Ts... ts)
  {
   QVector<QString> qvs({a1, a2, ts...});
   _th->define_setters_data_.held_string.append(qvs);
   _th->define_setters_data_.add_state(_define_setters_data::String);
   return *this;
  }

  _define_setters operator -- (int)
  {
   auto& dsd = _th->define_setters_data_;

   if(dsd.current_arg_state == _define_setters_data::Arg_State::P)
     dsd.freeze_pre_arg();
   else
     dsd.expand_state(_define_setters_data::Arg_State::Hanging_To);
   return *this;
  }


 };


public:

 typedef SITE_Type Site_type;

 ACCESSORS(QString ,file_path)

 ACCESSORS(QStringList ,original_header)


 ACCESSORS(csv_field_setters_by_column<SITE_Type> ,csv_field_setters)
 ACCESSORS(csv_field_getters_by_column<SITE_Type> ,csv_field_getters)

 ACCESSORS__RGET(QMap<QString, QString (SITE_Type::*)() const> ,json_field_getters)
 ACCESSORS__RGET(QMap<QString, void (SITE_Type::*)(QString)> ,json_field_setters)

 _define_setters define_setters() { return {this}; }

 SITE_Type& add_site()
 {
  sites_.push_back(SITE_Type{});
  return sites_.last();
 }

 //typedef QPair<u2, u2> u2x3;

 template<typename FN_Type>
 void add_setter(typename decltype(csv_field_setters_)::Proc_Options props,
    typename decltype(csv_field_setters_)::Call_Specs call_specs,
    const QVector<u2x3>& cols, u2* check_multi_count,
    const QSet<u2x3>& n0_overrides,
    FN_Type fn, const void* pre = nullptr,
    const void* adjunct = nullptr, u2 insert_count = 0)
 {
  csv_field_setters_.add(props, call_specs, cols, check_multi_count, n0_overrides, fn, pre, adjunct, insert_count);
 }


 void sort_sites(bool (*comparer)
   (const SITE_Type& lhs, const SITE_Type& rhs))
 {
  std::sort(sites_.begin(), sites_.end(), comparer);
 }

 void save_to_csv_file(QString out_file_path = {}, QStringList* header = nullptr)
 {
  if(out_file_path.isEmpty())
  {
   out_file_path = file_path_ + ".save.csv";
  }
  else if(out_file_path == "!")
  {
   out_file_path = file_path_;
  }

  if(!header)
    header = &original_header_;


  QtCSV::StringData lines;

  lines.addRow(*header);
  lines.addEmptyRow();


  for(SITE_Type& site : sites_)
  {
   QVector<QString> row;
   row.resize(csv_field_getters_.total_columns());

   {
    auto it = csv_field_getters_.methods_0_iterator();
    while(it.hasNext())
    {
     it.next();
     row[it.key() - 1] = (site.*it.value())();
    }
   }

   {
    auto it = csv_field_getters_.non_methods_0_iterator();
    while(it.hasNext())
    {
     it.next();
     row[it.key() - 1] = (*it.value())();
    }
   }

   {
    auto it = csv_field_getters_.defaults_iterator();
    while(it.hasNext())
    {
     it.next();
     row[it.key() - 1] = it.value();
    }
   }

//   for(auto it : csv_field_getters_.non_methods)
//   {
//    row[it->key()] = (*it->value())();
//   }

//   for(auto it : csv_field_getters_.defaults)
//   {
//    row[it->key()] = it->value();
//   }

   lines.addRow(row.toList());
  }


  QtCSV::Writer::write(out_file_path, lines);

 }

 void add_default_field_getter(u2 column, QString default_value)
 {
  csv_field_getters_.defaults[column] = default_value;
 }

 void add_file_path(QString key, QString file_path)
 {
  file_paths_[key] = file_path;
 }

 QString get_file_path(QString key)
 {
  return file_paths_.value(key);
 }


// void read_csv_file(QString csv_file_path, u4 max = 0);

// void read_csv_file(u4 max = 0)
// {
//  read_csv_file(file_path_, max);
// }

};


#endif // SITE_LIST_BASE__H
