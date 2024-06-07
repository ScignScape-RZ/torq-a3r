
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_KNOWN_TOX_SITE__H
#define NJ_KNOWN_TOX_SITE__H

#include <QString>

#include "global-types.h"

#include "accessors.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"


#define SET_ADAPTER_(fn, to_) void set_##fn(QString arg) { set_##fn(arg.to##to_()); }

#define SET_ADAPTER_DBL(fn) SET_ADAPTER_(fn, Double)
#define SET_ADAPTER_INT(fn) SET_ADAPTER_(fn, Int)


#define STR_ADAPTER(fn) QString str_##fn() const { return  QString::number(fn()); }

#define SET_and_STR_ADAPTER_DBL(fn) SET_ADAPTER_(fn, Double) STR_ADAPTER(fn)
#define SET_and_STR_ADAPTER_INT(fn) SET_ADAPTER_(fn, Int) STR_ADAPTER(fn)


#include <QJsonObject>

class NJ_Known_Tox_Site
{
 r8 latitude_;
 r8 longitude_;

 u1 coords_count_;

 u4 site_id_;
 u4 pi_number_;

 QString pi_name_;


 QString coords_options_;
 QString street_address_;
 QString municipality_;
 QString county_;

 QString home_owner_status_;
 QString data_source_;

 QVector<QPair<r8, r8>>* ref_coords_;

public:

 struct Supplemental_Address_Info
 {
  QString osm_address;
  QString osm_alt_address;
  QString osm_municipality;
  QString osm_alt_municipality;

  QVector<QPair<r8, r8>> coords;
  QVector<QPair<r8, r8>> alt_coords;

  u1 overlap_count;

  Supplemental_Address_Info() : overlap_count(0) { }
 };

 void supplemental_address_info_to_qjo(QJsonObject& qjo);
 void qjo_to_supplemental_address_info(QJsonObject& qjo);

private:
 Supplemental_Address_Info supplemental_address_info_;

public:

 NJ_Known_Tox_Site();

 ACCESSORS__RGET(Supplemental_Address_Info ,supplemental_address_info)

 ACCESSORS(r8 ,latitude)
 ACCESSORS(r8 ,longitude)

 ACCESSORS(u1 ,coords_count)

 ACCESSORS(u4 ,site_id)
 ACCESSORS(u4 ,pi_number)

 ACCESSORS(QString ,pi_name)

 ACCESSORS(QString ,home_owner_status)


 ACCESSORS(QString ,coords_options)
 ACCESSORS(QString ,street_address)
 ACCESSORS(QString ,municipality)
 ACCESSORS(QString ,county)
 ACCESSORS(QString ,data_source)

 ACCESSORS__GET(QVector<QPair<r8, r8>>* ,ref_coords)

 SET_and_STR_ADAPTER_DBL(latitude)
 SET_and_STR_ADAPTER_DBL(longitude)
 SET_and_STR_ADAPTER_INT(coords_count)
 SET_and_STR_ADAPTER_INT(site_id)
 SET_and_STR_ADAPTER_INT(pi_number)

 void init_ref_coords();

 ~NJ_Known_Tox_Site()
 {
  if(ref_coords_)
    delete ref_coords_;
 }


};


#endif // NJ_KNOWN_TOX_SITE__H
