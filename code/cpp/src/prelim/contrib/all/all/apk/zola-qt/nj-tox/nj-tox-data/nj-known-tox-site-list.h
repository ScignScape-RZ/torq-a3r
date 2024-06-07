
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_KNOWN_TOX_SITE_LIST__H
#define NJ_KNOWN_TOX_SITE_LIST__H


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
#include "nj-known-tox-site.h"


#define NJ_Known_Tox_Site_KMD_MACRO_2(k, md) {#k, &NJ_Known_Tox_Site::md},
#define NJ_Known_Tox_Site_KMD_MACRO_1(k) NJ_Known_Tox_Site_KMD_MACRO_2(k, k)

#define NJ_Known_Tox_Site_KMD_MACRO(...) _preproc_CONCAT(NJ_Known_Tox_Site_KMD_MACRO_, \
  _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)

#define NJ_Known_Tox_Site_STR_KMD_MACRO(k) NJ_Known_Tox_Site_KMD_MACRO_2(k, str##_##k)


#define NJ_Known_Tox_Site_SET_KMD_MACRO_2(k, md) {#k, &NJ_Known_Tox_Site::md},
#define NJ_Known_Tox_Site_SET_KMD_MACRO_1(k) NJ_Known_Tox_Site_SET_KMD_MACRO_2(k, set_##k)

#define NJ_Known_Tox_Site_SET_KMD_MACRO(...) _preproc_CONCAT(NJ_Known_Tox_Site_SET_KMD_MACRO_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)



class NJ_Known_Tox_Site_List : public Site_List_Base<NJ_Known_Tox_Site>
{
 QStringList original_header_;

 QString data_source_string_;

public:

 NJ_Known_Tox_Site_List(QString file_path = {});

 ACCESSORS(QString ,file_path)
 ACCESSORS__RGET(QVector<NJ_Known_Tox_Site> ,sites)
 ACCESSORS__CONST_RGET(QVector<NJ_Known_Tox_Site> ,sites)

 ACCESSORS(QString ,data_source_string)

 ACCESSORS(QStringList ,original_header)

 void default_json_field_getters();
 void default_json_field_setters();

 void read_csv_file(decltype(csv_field_setters_)& mds, QString csv_file_path, u4 max = 0);

 void read_csv_file(QString csv_file_path, u4 max = 0)
 {
  read_csv_file(csv_field_setters_, csv_file_path, max);
 }

 void read_csv_file(u4 max = 0)
 {
  read_csv_file(file_path_, max);
 }


 void save_to_json_file(QString file);

 void save_to_json_file()
 {
  QString f = file_paths_.value("json");

  if(f.isEmpty())
    f = file_path_ + ".json";

  save_to_json_file(f);

 }


 void read_json_file(QString file_path, void (*cb)
   (NJ_Known_Tox_Site&, QJsonObject) = nullptr);

 void merge_with_json_found_or_missing_file(QString found_file,
   QString missing_file);


 void save_aggregate_json_file(QString file_path);
 void read_aggregate_json_file(QString file_path);

};


#endif // NJ_KNOWN_TOX_SITE_LIST__H
