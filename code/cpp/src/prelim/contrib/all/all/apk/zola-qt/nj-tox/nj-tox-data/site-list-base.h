
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
 QVector<u2> held_arg;
 QVector<QPair<u2, u2>> held_range;
 QVector<s4> held_pre;
 QVector<QString> held_string;

 u2 last_column;

 std::function<u2 (QVariant)> column_resolver;

 _define_setters_data(); // : last_column(0) {}

 const QVector<s4>& held_pre_or_range();

 void get_current_arg(QVector<u2>& result);
 s4 get_current_arg(QVector<u2>& result, const QVector<QString>& keys);

 void reset(const QVector<u2>& lc);
 void reset(u2 lc);
 void reset();

private:

 QVector<s4> _range;

};



template<typename SITE_Type>
struct csv_field_setters_by_column
{
 enum class Proc_Options {

   m_QString_u2, m_QString_QString,
   n_QString_u2, n_QString_QString,

   m_QString, n_QString,

   m_QString_u2_n0, m_QString_QString_n0,
   n_QString_u2_n0, n_QString_QString_n0,

   m_QString_n0, n_QString_n0,

 };

 QMap<u2, void (SITE_Type::*)(QString, u2)> m_QString_u2, m_QString_u2_n0;
 QMap<u2, void (SITE_Type::*)(QString, QString)> m_QString_QString, m_QString_QString_n0;
 QMap<u2, void (*)(QString, u2)> n_QString_u2, n_QString_u2_n0;
 QMap<u2, void (*)(QString, QString)> n_QString_QString, n_QString_QString_n0;

 QMap<u2, void (SITE_Type::*)(QString)> m_QString, m_QString_n0;
 QMap<u2, void (*)(QString)> n_QString, n_QString_n0;

 QMap<u2, Proc_Options> proc_options;

 QMap<u2, u2> preset_args_u2;
 QMap<u2, QString> preset_args_QString;


 template<typename FN_Type>
 void add(Proc_Options props,
   QVector<u2> cols, FN_Type fn, const void* pre = nullptr)
 {
  switch(props)
  {
#define CASE_MACRO(m) \
   case Proc_Options::m: \
    for(u2 col : cols) { m[col] = (decltype(m[col])) fn; } break;


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

  if(pre)
  {
   u2 count = 0;
   switch (props)
   {
   case Proc_Options::m_QString_u2:
   case Proc_Options::n_QString_u2:
   case Proc_Options::m_QString_u2_n0:
   case Proc_Options::n_QString_u2_n0:
    for(int p : * (const QVector<int>*) pre)
    {
     preset_args_QString[cols.value(count)] = (u2) p;
    }
    break;
   case Proc_Options::m_QString_QString:
   case Proc_Options::n_QString_QString:
   case Proc_Options::m_QString_QString_n0:
   case Proc_Options::n_QString_QString_n0:
    for(QString p : * (const QVector<QString>*) pre)
    {
     preset_args_QString[cols.value(count)] = p;
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

  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString)::mapped_type m_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString_u2)::mapped_type m_QString_u2_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::m_QString_QString)::mapped_type m_QString_QString_type;

  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString)::mapped_type n_QString_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString_u2)::mapped_type n_QString_u2_type;
  typedef typename decltype(csv_field_setters_by_column<SITE_Type>::n_QString_QString)::mapped_type n_QString_QString_type;

  typedef typename csv_field_setters_by_column<SITE_Type>::Proc_Options Props;

  _define_setters operator [] (m_QString_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   _this->add_setter(Props::m_QString_n0, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator [] (m_QString_u2_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   const QVector<s4>& pre = _this->define_setters_data_.held_pre;
   _this->add_setter(Props::m_QString_u2_n0, cols, arg, &pre);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator [] (m_QString_QString_type arg)
  {
   QVector<u2> cols;
   const QVector<QString>& pre = _this->define_setters_data_.held_string;
   s4 pre_used = _this->define_setters_data_.get_current_arg(cols, pre);
   if(pre_used)
     _this->add_setter(Props::m_QString_QString_n0, cols, arg, &pre);
   else
     _this->add_setter(Props::m_QString_QString_n0, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator [] (n_QString_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   _this->add_setter(Props::n_QString_n0, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator [] (n_QString_u2_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);   
   const QVector<s4>& pre = _this->define_setters_data_.held_pre_or_range();
   _this->add_setter(Props::n_QString_u2_n0, cols, arg, &pre);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator [] (n_QString_QString_type arg)
  {
   QVector<u2> cols;
   const QVector<QString>& pre = _this->define_setters_data_.held_string;
   s4 pre_used = _this->define_setters_data_.get_current_arg(cols, pre);
   if(pre_used)
     _this->add_setter(Props::n_QString_QString_n0, cols, arg, &pre);
   else
     _this->add_setter(Props::n_QString_QString_n0, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }


  _define_setters operator [] (u2 arg)
  {
   _this->define_setters_data_.held_arg.push_back(arg);
   return *this;
  }


  _define_setters operator () (m_QString_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   _this->add_setter(Props::m_QString, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator () (m_QString_u2_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   const QVector<s4>& pre = _this->define_setters_data_.held_pre_or_range();
   _this->add_setter(Props::m_QString_u2, cols, arg, &pre);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator () (m_QString_QString_type arg)
  {
   QVector<u2> cols;
   const QVector<QString>& pre = _this->define_setters_data_.held_string;
   s4 pre_used = _this->define_setters_data_.get_current_arg(cols, pre);
   if(pre_used)
     _this->add_setter(Props::m_QString_QString, cols, arg, &pre);
   else
     _this->add_setter(Props::m_QString_QString, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator () (n_QString_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   _this->add_setter(Props::n_QString, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator () (n_QString_u2_type arg)
  {
   QVector<u2> cols;
   _this->define_setters_data_.get_current_arg(cols);
   const QVector<s4>& pre = _this->define_setters_data_.held_pre;
   _this->add_setter(Props::n_QString_u2, cols, arg, &pre);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator () (n_QString_QString_type arg)
  {
   QVector<u2> cols;
   const QVector<QString>& pre = _this->define_setters_data_.held_string;
   s4 pre_used = _this->define_setters_data_.get_current_arg(cols, pre);
   if(pre_used)
     _this->add_setter(Props::n_QString_QString, cols, arg, &pre);
   else
     _this->add_setter(Props::n_QString_QString, cols, arg);
   _this->define_setters_data_.reset();
   return *this;
  }

  _define_setters operator () (int arg)
  {
   _this->define_setters_data_.held_pre.push_back(arg);
   return *this;
  }


  _define_setters operator () (QString arg)
  {
   _this->define_setters_data_.held_string.push_back(arg);
   return *this;
  }

  _define_setters operator () (int arg, int arg1)
  {
   _this->define_setters_data_.held_range.push_back({arg, arg1});
   return *this;
  }

  template<typename ...Ts>
  _define_setters operator () (QString a1, QString a2, Ts... ts)
  {
   QVector<QString> qvs({a1, a2, ts...});
   _this->define_setters_data_.held_string.append(qvs);
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
    const QVector<u2>& cols, FN_Type fn, const void* pre = nullptr)
 {
  csv_field_setters_.add(props, cols, fn, pre);
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
