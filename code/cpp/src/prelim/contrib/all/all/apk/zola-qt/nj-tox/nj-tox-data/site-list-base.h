
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



template<typename SITE_Type>
struct csv_field_setters_by_column
{
 QMap<u2, void (SITE_Type::*)(QString)> methods;
 QMap<u2, void (*)(QString)> non_methods;

 csv_field_setters_by_column(QVector<void (SITE_Type::*)(QString)> vec)
 {
  u2 column = 0;
  for(auto md : vec)
  {
   methods[column] = md;
   ++column;
  }
 }

 csv_field_setters_by_column(decltype(methods) mds)
   : methods(mds)
 { }

 csv_field_setters_by_column() {}


};

template<typename SITE_Type>
struct csv_field_getters_by_column
{
 typedef QVector<QString (SITE_Type::*)() const> methods_vector_type;

 typedef QMapIterator<u2, QString (SITE_Type::*)() const> methods_iterator_type;
 typedef QMapIterator<u2, QString (*)()> non_methods_iterator_type;
 typedef QMapIterator<u2, QString> defaults_iterator_type;

 methods_iterator_type methods_iterator()
 {
  return methods_iterator_type(methods);
 }

 non_methods_iterator_type non_methods_iterator()
 {
  return non_methods_iterator_type(non_methods);
 }

 defaults_iterator_type defaults_iterator()
 {
  return defaults_iterator_type(defaults);
 }

 QMap<u2, QString (SITE_Type::*)() const> methods;
 QMap<u2, QString (*)()> non_methods;
 QMap<u2, QString> defaults;

 csv_field_getters_by_column() {}

 csv_field_getters_by_column(decltype(methods) mds)
   : methods(mds)
 { }


 csv_field_getters_by_column(methods_vector_type vec, u2 offset = 0)
 {
  u2 column = offset;
  for(auto md : vec)
  {
   methods[column] = md;
   ++column;
  }
 }


 u2 total_columns()
 {
  return methods.size() + non_methods.size() + defaults.size();
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

 ACCESSORS(QString ,file_path)
// ACCESSORS__RGET(QVector<NJ_TRI_Site> ,sites)
// ACCESSORS__CONST_RGET(QVector<NJ_TRI_Site> ,sites)

// ACCESSORS(QString ,data_source_string)

//// ACCESSORS__FNP__VOID(QString& ,address_edit_callback)
//// ACCESSORS__FNP__VOID(QString& ,municipality_edit_callback)


 ACCESSORS(QStringList ,original_header)

public:

 ACCESSORS(csv_field_setters_by_column<SITE_Type> ,csv_field_setters)
 ACCESSORS(csv_field_getters_by_column<SITE_Type> ,csv_field_getters)


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
    auto it = csv_field_getters_.methods_iterator();
    while(it.hasNext())
    {
     it.next();
     row[it.key()] = (site.*it.value())();
    }
   }

   {
    auto it = csv_field_getters_.non_methods_iterator();
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
