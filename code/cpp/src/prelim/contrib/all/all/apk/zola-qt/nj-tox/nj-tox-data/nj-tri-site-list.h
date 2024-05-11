
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TRI_SITE_LIST__H
#define NJ_TRI_SITE_LIST__H


#include "nj-tri-site.h"

#include <QString>
#include <QVector>


#include <QGeoCodingManager>
#include <QGeoCodingManagerEngine>
#include <QGeoServiceProvider>
#include <QGeoAddress>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoServiceProvider>

#include <QMap>

#include "global-types.h"

#include "accessors.h"

#include "site-list-base.h"
#include "nj-tri-site.h"


class NJ_TRI_Site_List : public Site_List_Base<NJ_TRI_Site>
{
// QString file_path_;
// QVector<NJ_TRI_Site> sites_;

 QStringList original_header_;

 QString data_source_string_;

// QVector<void (NJ_TRI_Site::*)(QString)>  csv_field_setters_;
// QVector<QString (NJ_TRI_Site::*)() const>  csv_field_getters_;


public:

 NJ_TRI_Site_List(QString file_path = {});

 ACCESSORS(QString ,file_path)
 ACCESSORS__RGET(QVector<NJ_TRI_Site> ,sites)
 ACCESSORS__CONST_RGET(QVector<NJ_TRI_Site> ,sites)

 ACCESSORS(QString ,data_source_string)

// ACCESSORS__FNP__VOID(QString& ,address_edit_callback)
// ACCESSORS__FNP__VOID(QString& ,municipality_edit_callback)


 ACCESSORS(QStringList ,original_header)

// ACCESSORS(QVector<void (NJ_TRI_Site::*)(QString)> ,csv_field_setters)
// ACCESSORS(QVector<QString (NJ_TRI_Site::*)() const> ,csv_field_getters)

 manual_ptr_handles<NJ_TRI_Site_List> split_by_county(QMap<QString, NJ_TRI_Site_List*>& results,
   QString* file_pattern);


 void read_csv_file(decltype(csv_field_setters_)& mds, QString csv_file_path, u4 max = 0);

 void read_csv_file(QString csv_file_path, u4 max = 0)
 {
  read_csv_file(csv_field_setters_, csv_file_path, max);
 }

 void read_csv_file(u4 max = 0)
 {
  read_csv_file(file_path_, max);
 }

};


#endif // NJ_TRI_SITE_LIST__H
