
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TOX_SITE_LIST__H
#define NJ_TOX_SITE_LIST__H

#include "nj-tox-site.h"

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

class NJ_Tox_Site_List
{
 QString file_path_;

 QVector<NJ_Tox_Site> sites_;

 QStringList original_header_;

 QString data_source_string_;

 QVector<void (NJ_Tox_Site::*)(QString)>  csv_field_setters_;
 QVector<QString (NJ_Tox_Site::*)() const>  csv_field_getters_;

 void (*address_edit_callback_)(QString&);
 void (*municipality_edit_callback_)(QString&);

public:

 NJ_Tox_Site_List(QString file_path);

 ACCESSORS(QString ,file_path)

 ACCESSORS__RGET(QVector<NJ_Tox_Site> ,sites)
 ACCESSORS__CONST_RGET(QVector<NJ_Tox_Site> ,sites)

 ACCESSORS(QString ,data_source_string)

 ACCESSORS__FNP__VOID(QString& ,address_edit_callback)
 ACCESSORS__FNP__VOID(QString& ,municipality_edit_callback)


 ACCESSORS(QStringList ,original_header)

 ACCESSORS(QVector<void (NJ_Tox_Site::*)(QString)> ,csv_field_setters)
 ACCESSORS(QVector<QString (NJ_Tox_Site::*)() const> ,csv_field_getters)

 void check_addresses_json(QStringList geo_service_providers,
   QString found_file_path, QString missing_file_path);

 void read_csv_county_file(QString county_name, QString file_name);
 void read_json_county_file(QString county_name, QString file_name);

 void to_qmap(QMap<u4, NJ_Tox_Site*>& result);

 void read_json_file();

 void import_json_file(QString path);

 void read_csv_file(QVector<void (NJ_Tox_Site::*)(QString)> mds, u4 max = 0);

 void read_csv_file(u4 max = 0)
 {
  read_csv_file(csv_field_setters_, max);
 }

 void sort_sites(bool (*comparer)
   (const NJ_Tox_Site& lhs, const NJ_Tox_Site& rhs));

 void sort_by_site_id();

 void distribute_by_county(QString folder_path);

 void add_site(const NJ_Tox_Site& site);

 void save_to_csv_file(QVector<QString (NJ_Tox_Site::*)() const>  mds,
   QString out_file_path = {}, QStringList* header = nullptr);

 void save_to_csv_file(QVector<QString (NJ_Tox_Site::*)() const>  mds,
   QStringList header, QString out_file_path = {})
 {
  save_to_csv_file(mds, out_file_path, &header);
 }

 void save_to_csv_file(QString out_file_path = {},
   QStringList* header = nullptr)
 {
  save_to_csv_file(csv_field_getters_, out_file_path, header);
 }

 void save_to_csv_file(QStringList header,
   QString out_file_path = {})
 {
  save_to_csv_file(csv_field_getters_, out_file_path, &header);
 }

 void save_to_csv_file(NJ_Tox_Site_List& orig)
 {
  save_to_csv_file(orig.csv_field_getters_, file_path_,
    &orig.original_header_);
 }


 void merge_with(const NJ_Tox_Site_List& other_list);

 void check_addresses(QGeoCodingManager* gcm,
   QMap<QString, QString> repl = {});

 void merge_json(const QMap<u4, QVector<QPair<r8, r8>>>& merges,
   const QMap<u4, QPair<u4, QStringPair>>& merge_addresses, QString key);


 static s1 compare(QVector<QPair<r8, r8>>& lhs, QVector<QPair<r8, r8>>& rhs);

 static void check_address(QGeoCodingManager* gcm,
   QString address, QString muni, QVector<QPair<r8, r8>>& results);

 static QPair<r8, r8> check_address(QGeoCodingManager* gcm,
   QString street, QString muni);

// void save_to_csv_file_(QString (NJ_Tox_Site::*md)(),
//   QString out_file_path = {})
// {

// }

};


#endif // NJ_TOX_SITE_LIST__H
