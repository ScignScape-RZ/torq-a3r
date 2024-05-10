
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
 QMap<u2, QString (SITE_Type::*)() const> methods;
 QMap<u2, QString (*)()> non_methods;
 QMap<u2, QString> defaults;

 csv_field_getters_by_column() {}


};


template<typename SITE_Type>
class Site_List_Base
{

protected:

 QVector<SITE_Type> sites_;


 csv_field_setters_by_column<SITE_Type>  csv_field_setters_;
 csv_field_getters_by_column<SITE_Type>  csv_field_getters_;


 Site_List_Base()
 {

 }

// ACCESSORS(QString ,file_path)
// ACCESSORS__RGET(QVector<NJ_TRI_Site> ,sites)
// ACCESSORS__CONST_RGET(QVector<NJ_TRI_Site> ,sites)

// ACCESSORS(QString ,data_source_string)

//// ACCESSORS__FNP__VOID(QString& ,address_edit_callback)
//// ACCESSORS__FNP__VOID(QString& ,municipality_edit_callback)


// ACCESSORS(QStringList ,original_header)

public:

 ACCESSORS(csv_field_setters_by_column<SITE_Type> ,csv_field_setters)
 ACCESSORS(csv_field_getters_by_column<SITE_Type> ,csv_field_getters)


// void read_csv_file(QString csv_file_path, u4 max = 0);

// void read_csv_file(u4 max = 0)
// {
//  read_csv_file(file_path_, max);
// }

};


#endif // SITE_LIST_BASE__H
