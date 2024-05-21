
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SITE_LIST_BASE__H
#define SITE_LIST_BASE__H


#include "nj-tri-site.h"

#include <QString>
#include <QVector>


#include <QMap>

#include "global-types.h"

#include "accessors.h"

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

#include <QDebug>


#include <functional>

struct _define_setters_data
{
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


 QVector<u2> held_arg;
 QVector<QPair<u2, u2>> held_range;
 QVector<s4> held_pre;
 QVector<QString> held_string;

 u2 hanging_plus_count;
 u2 suspended_plus_count;

 u2 last_column;

 u2 string_options_count;

 std::function<u2 (QVariant)> column_resolver;

 _define_setters_data(); // : last_column(0) {}

 const QVector<s4>& held_pre_or_range();

 void get_current_arg(QVector<u2>& result);
 s4 get_current_arg(QVector<u2>& result, const QVector<QString>& keys);

 const QVector<s4>& held_range_to_vector(QVector<u2>& result);

 void reset(const QVector<u2>& lc);
 void reset(u2 lc);
 void reset();

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

 QMap<u2, void (SITE_Type::*)(QString, u2)> m_QString_u2, m_QString_u2_n0;
 QMap<u2, void (SITE_Type::*)(QString, QString)> m_QString_QString, m_QString_QString_n0;
 QMap<u2, void (*)(QString, u2)> n_QString_u2, n_QString_u2_n0;
 QMap<u2, void (*)(QString, QString)> n_QString_QString, n_QString_QString_n0;

 QMap<u2, void (SITE_Type::*)(QString)> m_QString, m_QString_n0;
 QMap<u2, void (*)(QString)> n_QString, n_QString_n0;

 QMap<u2, void (SITE_Type::*)()> m_void, m_void_n0;
 QMap<u2, void (*)()> n_void, n_void_n0;

 QMap<QPair<u2, QString>, void (SITE_Type::*)()> m_void_indexed;
 QMap<QPair<u2, QString>, void (*)()> n_void_indexed;

 QMap<u2, Proc_Options> proc_options;

 QMap<u2, u2> preset_args_u2;
 QMap<u2, QString> preset_args_QString;

 QString column_string_pattern(QString* reset = nullptr)
 {
  if(reset)
    _column_string_pattern = *reset;
  else if(_column_string_pattern.isNull())
    _column_string_pattern = "C%1";
  return _column_string_pattern;
 }

 template<typename FN_Type>
 void add(Proc_Options props,
   QVector<u2> cols, FN_Type fn, const void* pre = nullptr,
   const void* adjunct = nullptr, u2 insert_count = 0)
 {
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
     for(u2 col : cols) \
     { \
      m##_indexed[{col, qsv->value(i)}] = (decltype(m[col])) fn; \
      ++i; \
      proc_options[col] = Proc_Options::m; \
     }} break; \

    CASE_MACRO(m_void)
    CASE_MACRO(n_void)
#undef CASE_MACRO


#define CASE_MACRO(m) \
   case Proc_Options::m: \
    for(u2 col : cols) { m[col] = (decltype(m[col])) fn; \
      proc_options[col] = Proc_Options::m;}  break; \

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
      preset_args_u2[cols.value(count)] = cols.value(count);
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
        column_string_pattern().arg(cols.value(count));
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

 csv_field_getters_by_column() {}

 csv_field_getters_by_column(decltype(methods_0) mds)
   : methods_0(mds)
 { }


 csv_field_getters_by_column(methods_0_vector_type vec, u2 offset = 0)
 {
  u2 column = offset;
  for(auto md : vec)
  {
   methods_0[column] = md;
   ++column;
  }
 }


 u2 total_columns()
 {
  return methods_0.size() + non_methods_0.size()
    + methods_1.size() + non_methods_1.size()
    + defaults.size();
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

 struct _define_setters
 {
  Site_List_Base* _this;

  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_void)::mapped_type m_void_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString)::mapped_type m_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString_u2)::mapped_type m_QString_u2_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString_QString)::mapped_type m_QString_QString_type;

  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_void)::mapped_type n_void_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString)::mapped_type n_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString_u2)::mapped_type n_QString_u2_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString_QString)::mapped_type n_QString_QString_type;

  typedef typename csv_field_setters_by_column<SITE_Type>::Proc_Options Props;

  template<typename FN_Type>
  void ops_void(Props props, FN_Type fn)
  {
   auto& dsd = _this->define_setters_data_;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::AS:
    _this->add_setter(props, dsd.held_arg, fn, &dsd.held_string);
    dsd.reset(dsd.held_arg);
    break;

   case _define_setters_data::Arg_State::S:
    _this->add_setter(props, {dsd.last_column}, fn, &dsd.held_string);
    dsd.reset(dsd.last_column);
    break;

    // // anything else?

   default: //  mostly Arg_State::A, right?
    _this->add_setter(props, dsd.held_arg, fn);
    dsd.reset(dsd.held_arg);
   }

  }

  template<typename FN_Type>
  void ops_QString(Props props, FN_Type fn)
  {
   auto& dsd = _this->define_setters_data_;

   QVector<u2> cols;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::Init:
    dsd.held_arg.push_back(dsd.last_column + 1);
    // //  fallthrough
   case _define_setters_data::Arg_State::A:
    dsd.get_current_arg(cols);
    _this->add_setter(props, cols, fn);
    break;

   case _define_setters_data::Arg_State::R:
    dsd.held_range_to_vector(cols);
    _this->add_setter(props, cols, fn);
    break;
   }
   dsd.reset(cols);
  }


  template<typename FN_Type>
  void ops_QString_u2(Props props, FN_Type arg)
  {
   QVector<u2> cols;
   auto& dsd = _this->define_setters_data_;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::A:
    dsd.get_current_arg(cols);
    _this->add_setter(props, cols, arg, nullptr, nullptr, cols.size());
    break;

   case _define_setters_data::Arg_State::PA:
    dsd.get_current_arg(cols);
    if(dsd.held_pre.isEmpty())
      _this->add_setter(props, cols, arg, nullptr, nullptr, dsd.hanging_plus_count);
    else
      _this->add_setter(props, cols, arg, &dsd.held_pre, dsd.froze_pre_arg_ptr);
    break;

   case _define_setters_data::Arg_State::R:
    {
     const QVector<s4>& r = dsd.held_range_to_vector(cols);
     _this->add_setter(props, cols, arg, &r);
    }
    break;

   default:
    break;
   }
   dsd.reset(cols);
  }

  template<typename FN_Type>
  void ops_QString_QString(Props props, FN_Type arg)
  {
   auto& dsd = _this->define_setters_data_;

   QVector<u2> cols;

   switch (dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::S:
    {
     const QVector<QString>& hs = dsd.held_string;

     // //   get_current_arg() with strings will
      //     return a nonzero value if the strings
      //     are matched by column_resolver lookups
     if(dsd.get_current_arg(cols, hs))
       _this->add_setter(props, cols, arg, &hs);
     else
       _this->add_setter(props, cols, arg, nullptr, nullptr, cols.count());
    }
    break;

   // //  what's the right way to handle mixed in these cases?
   case _define_setters_data::Arg_State::SA:
    dsd.get_current_arg(cols);
    _this->add_setter(props, cols, arg, &dsd.held_string);
    break;
   // //  case AS and so on ...

   default:
    break;
   }
   dsd.reset(cols);
  }

  _define_setters operator [] (m_void_type arg)
  {
   ops_void(Props::m_void, arg);
   return *this;


//   auto& dsd = _this->define_setters_data_;
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

//   auto& dsd = _this->define_setters_data_;
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
   auto& dsd = _this->define_setters_data_;
   ++dsd.string_options_count;
   dsd.held_string.push_back(arg);
   dsd.add_state(_define_setters_data::String);
   return *this;
  }

  _define_setters operator [] (int arg)
  {
   auto& dsd = _this->define_setters_data_;

   _define_setters_data::Arg_State h = dsd.recollapse_state();

   if(h == _define_setters_data::Arg_State::Hanging_To)
   {
    u4 index = dsd.held_arg.size();
    u2 l = index ? dsd.held_arg.last() : 0;
    u2 min = qMin(l, (u2) arg);
    u2 max = qMax(l, (u2) arg);
    u2 diff = max - min;

    dsd.held_arg.resize(index + diff);
    for(u2 i = min + 1; i <= max; ++i, ++index)
      dsd.held_arg[index] = i;
   }
   else
     dsd.held_arg.push_back(arg);

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

  _define_setters operator () (m_void_type arg)
  {
   auto& dsd = _this->define_setters_data_;
   switch(dsd.current_arg_state)
   {
   case _define_setters_data::Arg_State::A:
    ops_void(Props::m_void_n0, arg);
    break;
   case _define_setters_data::Arg_State::AS:
   case _define_setters_data::Arg_State::S:
    // //  any others?
    ops_void(Props::m_void_indexed, arg);
    break;
   default:
    break;
   }
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
   ops_QString_QString(Props::m_QString_QString, arg);
   return *this;
  }

  _define_setters operator () (n_void_type arg)
  {
   auto& dsd = _this->define_setters_data_;
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
   auto& dsd = _this->define_setters_data_;

   if(dsd.hanging_plus_count)
   {
    // //  if hanging_plus gets suspended then thereafter
     //    the arg should be copied into pre_arg for the
     //    hanging-plus sections ...

    if(dsd.suspended_plus_count == 0)
    {
     // //  i.e., suspended for the first time
     for(u2 i = 0; i < dsd.hanging_plus_count; ++i)
       dsd.held_pre.push_back(dsd.held_arg.value(i));
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
   _this->define_setters_data_.add_state(_define_setters_data::Pre_Arg);
   _this->define_setters_data_.expand_state(_define_setters_data::Arg_State::Hanging_Plus);
   return *this;
  }

  _define_setters operator () (QString arg)
  {
   _this->define_setters_data_.held_string.push_back(arg);
   _this->define_setters_data_.add_state(_define_setters_data::String);
   return *this;
  }

  _define_setters operator () (int arg, int arg1)
  {
   _this->define_setters_data_.held_range.push_back({arg, arg1});
   _this->define_setters_data_.add_state(_define_setters_data::Range);
   return *this;
  }

  template<typename ...Ts>
  _define_setters operator () (QString a1, QString a2, Ts... ts)
  {
   QVector<QString> qvs({a1, a2, ts...});
   _this->define_setters_data_.held_string.append(qvs);
   _this->define_setters_data_.add_state(_define_setters_data::String);
   return *this;
  }

  _define_setters operator -- (int)
  {
   auto& dsd = _this->define_setters_data_;

   if(dsd.current_arg_state == _define_setters_data::Arg_State::P)
     dsd.freeze_pre_arg();
   else
     dsd.expand_state(_define_setters_data::Arg_State::Hanging_To);
   return *this;
  }


 };



public:

 ACCESSORS(QString ,file_path)

 ACCESSORS(QStringList ,original_header)


 ACCESSORS(csv_field_setters_by_column<SITE_Type> ,csv_field_setters)
 ACCESSORS(csv_field_getters_by_column<SITE_Type> ,csv_field_getters)


 _define_setters define_setters() { return {this}; }

 template<typename FN_Type>
 void add_setter(typename decltype(csv_field_setters_)::Proc_Options props,
    const QVector<u2>& cols, FN_Type fn, const void* pre = nullptr,
    const void* adjunct = nullptr, u2 insert_count = 0)
 {
  csv_field_setters_.add(props, cols, fn, pre, adjunct, insert_count);
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
     row[it.key()] = (site.*it.value())();
    }
   }

   {
    auto it = csv_field_getters_.non_methods_0_iterator();
    while(it.hasNext())
    {
     it.next();
     row[it.key()] = (*it.value())();
    }
   }

   {
    auto it = csv_field_getters_.defaults_iterator();
    while(it.hasNext())
    {
     it.next();
     row[it.key()] = it.value();
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


// void read_csv_file(QString csv_file_path, u4 max = 0);

// void read_csv_file(u4 max = 0)
// {
//  read_csv_file(file_path_, max);
// }

};


#endif // SITE_LIST_BASE__H
