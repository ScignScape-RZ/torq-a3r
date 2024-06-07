
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-known-tox-site.h"

#include <QJsonArray>

NJ_Known_Tox_Site::NJ_Known_Tox_Site()
  :  latitude_(0), longitude_(0), coords_count_(0),
     site_id_(0), pi_number_(0), ref_coords_(nullptr)
{

}

void NJ_Known_Tox_Site::init_ref_coords()
{
 ref_coords_ = new QVector<QPair<r8, r8>>;
}

void NJ_Known_Tox_Site::qjo_to_supplemental_address_info(QJsonObject& qjo)
{
 supplemental_address_info_.osm_address = qjo.value("osm-address").toString();
 supplemental_address_info_.osm_municipality = qjo.value("osm-municipality").toString();

 if(qjo.contains("osm-alt-address"))
 {
  supplemental_address_info_.osm_alt_address = qjo.value("osm-alt-address").toString();
  supplemental_address_info_.osm_alt_municipality = qjo.value("osm-alt-municipality").toString();
 }

 QJsonArray qja = qjo["coords"].toArray();

 for(auto val : qja)
 {
  QJsonArray qja1 = val.toArray();
  supplemental_address_info_.coords.push_back(
    {qja1.first().toDouble(), qja1.last().toDouble()});
 }

 if(qjo.contains("alt-coords"))
 {

  QJsonArray qja = qjo["alt-coords"].toArray();

  for(auto val : qja)
  {
   QJsonArray qja1 = val.toArray();
   supplemental_address_info_.alt_coords.push_back(
      {qja1.first().toDouble(), qja1.last().toDouble()});
  }

 }

}

void NJ_Known_Tox_Site::supplemental_address_info_to_qjo(QJsonObject& qjo)
{
 qjo.insert("osm-address", supplemental_address_info_.osm_address);
 qjo.insert("osm-municipality", supplemental_address_info_.osm_municipality);

 if(!supplemental_address_info_.osm_alt_address.isEmpty())
 {
  qjo.insert("osm-alt-address", supplemental_address_info_.osm_alt_address);
  qjo.insert("osm-alt-municipality", supplemental_address_info_.osm_alt_municipality);
 }

 QJsonArray qja;

 for(const auto& pr : supplemental_address_info_.coords)
 {
  QJsonArray qja1;
  qja1.append(pr.first);
  qja1.append(pr.second);
  qja.append(qja1);
 }

 qjo.insert("coords", qja);


 if(!supplemental_address_info_.alt_coords.isEmpty())
 {
  QJsonArray qja;

  for(const auto& pr : supplemental_address_info_.alt_coords)
  {
   QJsonArray qja1;
   qja1.append(pr.first);
   qja1.append(pr.second);
   qja.append(qja1);
  }

  qjo.insert("alt-coords", qja);
 }

}


