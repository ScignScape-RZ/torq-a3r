
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "nj-tox-site-list.h"

#include "textio.h"

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

#include <cmath>


#include <QDebug>
#include <QEventLoop>

#include <QDir>

#include <iostream>
#include <sstream>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


#include "textio.h"

NJ_Tox_Site_List::NJ_Tox_Site_List(QString file_path)
  :  file_path_(file_path), address_edit_callback_(nullptr),
     municipality_edit_callback_(nullptr)
{

}


s4 address_to_lat_lon(QGeoCodingManager* gcm,
  QString address, QString muni, QList<QGeoLocation>& reply_locations)
{
 // fill in request
 QGeoAddress* pQGeoAddr = new QGeoAddress;

 pQGeoAddr->setCountry("USA");

 pQGeoAddr->setStreet(address);
 pQGeoAddr->setCity(muni);
 pQGeoAddr->setState("NJ");


 QGeoCodeReply *pQGeoCode
   = gcm->geocode(*pQGeoAddr);

 if (!pQGeoCode)
 {
  delete pQGeoAddr;
  qDebug() << "GeoCoding totally failed!";
  return 0;
 }
 {
  std::ostringstream out;
  out << "Sending request for:\n"
      << pQGeoAddr->country().toUtf8().data() << "; "
      << pQGeoAddr->postalCode().toUtf8().data() << "; "
      << pQGeoAddr->city().toUtf8().data() << "; "
      << pQGeoAddr->street().toUtf8().data() << "...\n";
  qDebug() << QString::fromStdString( out.str() );
 }

 QEventLoop qel;

 // install signal handler to process result later
 QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
                 [pQGeoAddr, pQGeoCode, &reply_locations, &qel]()
 {

  // process reply
  std::ostringstream out;
  out << "Reply: " << pQGeoCode->errorString().toStdString() << '\n';
  switch (pQGeoCode->error())
  {
  case QGeoCodeReply::NoError:
    reply_locations = pQGeoCode->locations();
    break;
#define CASE(ERROR) \
   case QGeoCodeReply::ERROR: out << #ERROR << '\n'; break
    CASE(EngineNotSetError);
    CASE(CommunicationError);
    CASE(ParseError);
    CASE(UnsupportedOptionError);
    CASE(CombinationError);
    CASE(UnknownError);
#undef CASE
   default: out << "Undocumented error!\n";
  }
  // log result

  qDebug() << QString::fromStdString( out.str() );
  // clean-up
  delete pQGeoAddr;
  /* delete sender in signal handler could be lethal
        * Hence, delete it later...
        */
  pQGeoCode->deleteLater();
  qel.exit();

 });

 qel.exec();

 return reply_locations.size();
}


void NJ_Tox_Site_List::check_addresses_json(QStringList geo_service_providers,
  QString found_file_path, QString missing_file_path)
{
 QVector<QPair<QString, QGeoCodingManager*>> geo_coding_managers;

 QMap<QString, QGeoServiceProvider*> gsps;

 for(QString str: geo_service_providers)
 {
  QGeoServiceProvider* gsp = new QGeoServiceProvider(str);
  QGeoCodingManager* gcm = gsp->geocodingManager();
  if(gcm)
  {
   geo_coding_managers.push_back({str, gcm});
   gsps[str] = gsp;
  }
 }

 if(geo_coding_managers.isEmpty())
 {
  qDebug() << "Unable to find any geocoding managers; aborting";
  return;
 }

 QJsonDocument qjd_found;
 QJsonDocument qjd_missing;

 QJsonArray qja_found;
 QJsonArray qja_missing;

 read_csv_file();

 int i = 0;
 for(NJ_Tox_Site& site : sites_)
 {
  ++i;
//  if(i > 14)
//    break;

  QJsonObject qjo;
  qjo.insert("site-id", QJsonValue((int) site.site_id()));

  QString muni = site.municipality();
  if(municipality_edit_callback_)
    municipality_edit_callback_(muni);
  qjo.insert("query-m", muni);

  QString address = site.street_address();
  if(address_edit_callback_)
    address_edit_callback_(address);
  qjo.insert("query-a", address);

  QJsonObject responses;

  for(auto pr : geo_coding_managers)
  {
   QList<QGeoLocation> reply_locations;

   if(s4 size = address_to_lat_lon(pr.second, address, muni, reply_locations))
   {
    QJsonObject response;

    response.insert("count", size);

    QJsonArray coords;

    for(QGeoLocation loc: reply_locations)
    {
     QJsonArray c;
     c.append(loc.coordinate().latitude());
     c.append(loc.coordinate().longitude());
     coords.append(c);
    }

    response.insert("coords", coords);
    responses.insert(pr.first, response);
   }
  }

  if(responses.isEmpty())
  {
   qja_missing.append(qjo);
  }
  else
  {
   qjo.insert("locations", responses);
   qja_found.append(qjo);
  }

 }

// qja = QJsonArray::fromStringList(geo_service_providers);

 qjd_found.setArray(qja_found);
 qjd_missing.setArray(qja_missing);

 KA::TextIO::save_file(found_file_path, qjd_found.toJson());
 KA::TextIO::save_file(missing_file_path, qjd_missing.toJson());

 for(QGeoServiceProvider* gsp : gsps.values())
 {
  delete gsp;
 }
}


void NJ_Tox_Site_List::read_json_county_file(QString county_name, QString file_name)
{
 file_path_ += "/" + county_name + "/" + file_name;
 read_json_file();
}


void NJ_Tox_Site_List::read_csv_county_file(QString county_name, QString file_name)
{
 file_path_ += "/" + county_name + "/" + file_name;
 read_csv_file();
}


void NJ_Tox_Site_List::save_to_csv_file(
  QVector<QString (NJ_Tox_Site::*)() const> mds,
  QString out_file_path, QStringList* header)
{
 if(out_file_path.isEmpty())
 {
  out_file_path = file_path_ + ".save.csv";
 }

 if(!header)
   header = &original_header_;


 QtCSV::StringData lines;

 lines.addRow(*header);
 lines.addEmptyRow();


 for(NJ_Tox_Site& site : sites_)
 {
  QStringList row;
  for(auto md : mds)
  {
   if(md)
     row.push_back((site.*md)());
   else
     row.push_back(data_source_string_);
  }

  lines.addRow(row);
 }


 QtCSV::Writer::write(out_file_path, lines);

}




void address_to_lat_lon(QGeoCodingManager* gcm,
  NJ_Tox_Site& site,  QMap<QString, QString>* repl = nullptr) //, int& size, r8& lat, r8& lon, QString& str)
{
 QList<QGeoLocation> reply_locations;

 QString address = site.street_address();

 if(repl && !repl->isEmpty())
 {

  QMapIterator<QString, QString> it(*repl);
  while(it.hasNext())
  {
   it.next();
   if(address.endsWith(it.key()))
   {
    address.chop(it.key().length());
    address += it.value();
   }
  }
 }

 QString muni = site.municipality();

 s4 size = address_to_lat_lon(gcm, address, muni, reply_locations);

 if(size)
 {
  QString str;

  QGeoLocation loc1 = reply_locations.first();
  r8 lat = loc1.coordinate().latitude();
  r8 lon = loc1.coordinate().longitude();

  for(QGeoLocation loc : reply_locations)
  {
   str += "%1/%2;"_qt.arg(loc.coordinate().latitude()).arg(loc.coordinate().longitude());
  }

  site.set_coords_options(str);
  site.set_coords_count(size);

  site.set_latitude(lat);
  site.set_longitude(lon);
 }

}



void NJ_Tox_Site_List::check_addresses(QGeoCodingManager* gcm,
  QMap<QString, QString> repl)
{
 for(NJ_Tox_Site& site : sites_)
 {
  address_to_lat_lon(gcm, site, &repl);
 }
}

QPair<r8, r8> NJ_Tox_Site_List::check_address(QGeoCodingManager* gcm,
  QString street, QString muni)
{
 NJ_Tox_Site site;
 site.set_municipality(muni);
 site.set_street_address(street);
 address_to_lat_lon(gcm, site);
 return {site.latitude(), site.longitude()};
}

void NJ_Tox_Site_List::check_address(QGeoCodingManager* gcm,
  QString address, QString muni, QVector<QPair<r8, r8>>& results)
{
 QList<QGeoLocation> reply_locations;

 s4 size = address_to_lat_lon(gcm, address, muni, reply_locations);

 results.resize(size);

 std::transform(reply_locations.begin(), reply_locations.end(),
   results.begin(), [](const QGeoLocation& qgl) -> QPair<r8, r8>
 {
  return {qgl.coordinate().latitude(), qgl.coordinate().longitude()};
 });

}


void NJ_Tox_Site_List::distribute_by_county(QString folder_path)
{
 read_csv_file();

 sort_sites(
 [](const NJ_Tox_Site& lhs, const NJ_Tox_Site& rhs)
  {
   if(lhs.county() == rhs.county())
     return lhs.site_id() < rhs.site_id();

   return lhs.county() < rhs.county();
  }
 );

 QString current_county;
 //QString current_county_folder_path;

 NJ_Tox_Site_List* temp_list = nullptr;

 auto finalize_temp_list = [&]()
 {
  if(!temp_list)
    return;
  temp_list->save_to_csv_file(*this);
  delete temp_list;
 };

 int i = 0;

 QString county_list;

 for(const NJ_Tox_Site& site : sites_)
 {
  ++i;

//  if(i > 200)
//    break;

  if(site.county() != current_county)
  {
   finalize_temp_list();

   current_county = site.county();

   QString county_folder_name = current_county.simplified();
   county_folder_name.replace(' ', '_');

   county_list += county_folder_name + "\n";

   QString county_folder_path = folder_path + "/" + county_folder_name;

   QDir qd(county_folder_path);
   if(!qd.exists())
   {
    bool ok = qd.mkpath(county_folder_path);
    if(!ok)
    {
     qDebug() << "Unable to make path: " << county_folder_path;
     return;
    }
   }

   QString county_file_path = county_folder_path + "/pre-lookup.csv";
   temp_list = new NJ_Tox_Site_List(county_file_path);
  }

  temp_list->add_site(site);
 }

 finalize_temp_list();

 KA::TextIO::save_file(folder_path + "/counties.txt", county_list);
}

void NJ_Tox_Site_List::add_site(const NJ_Tox_Site& site)
{
 sites_.push_back(site);
}


void NJ_Tox_Site_List::merge_with(const NJ_Tox_Site_List& other_list)
{
 sites_ += other_list.sites();
// u4 this_size = sites_.size();
// u4 overall_size = this_size + other_list.sites().size();

// std::inplace_merge(v_one.begin(), v_one.begin() + size_one, v_one.end(),
//   [](Square const &a, Square const &b) -> bool
//   { return a.id < b.id; });
}

void NJ_Tox_Site_List::sort_sites(bool (*comparer)
  (const NJ_Tox_Site& lhs, const NJ_Tox_Site& rhs))
{
 std::sort(sites_.begin(), sites_.end(), comparer);
}


void NJ_Tox_Site_List::sort_by_site_id()
{
 std::sort(sites_.begin(), sites_.end(), [](const NJ_Tox_Site& lhs, const NJ_Tox_Site& rhs)
 {
  return lhs.site_id() < rhs.site_id();
 });
}


s1 NJ_Tox_Site_List::compare(QVector<QPair<r8, r8>>& lhs, QVector<QPair<r8, r8>>& rhs)
{
 u4 ls = lhs.size();
 u4 rs = rhs.size();

 if(ls < rs)
   return -1;

 if(rs < ls)
   return 1;

 QSet<u4> rem_l, rem_r;

 auto round4 = [](r8& r)
 {
  r *= 10000;
  r = std::round(r);
  r /= 10000;
 };

 auto round4pr = [round4](QPair<r8, r8>& pr)
 {
  round4(pr.first);
  round4(pr.second);
 };

 auto clean_vec = [](QVector<QPair<r8, r8>>& vec, const QSet<u4>& indexes)
 {
  auto ii = indexes.toList();
  std::sort(ii.begin(), ii.end());
  u4 count = 0;
  for(u4 i : ii)
  {
   vec.remove(i - count);
   ++count;
  }
 };

 std::for_each(rhs.begin(), rhs.end(), round4pr);

 for(u4 i = 0; i < ls; ++i)
 {
  QPair<r8, r8>& lp = lhs[i];
  round4pr(lp);

  for(u4 j = 0; j < rs; ++j)
  {
   QPair<r8, r8> rp = rhs[j];
   if(rp == lp)
   {
    rem_r.insert(j);
    rem_l.insert(i);
   }
  }

  if(!rem_r.isEmpty())
  {
   clean_vec(rhs, rem_r);
   rs -= rem_r.size();
   rem_r.clear();
  }

 }

 clean_vec(lhs, rem_l);

 ls = lhs.size();
 rs = rhs.size();

 if(ls < rs)
   return -1;

 if(rs < ls)
   return 1;

 for(u4 i = 0; i < ls; ++i)
 {
  if(lhs[i] == rhs[i])
    continue;

  return lhs[i] < rhs[i]? -1 : 1;
 }

 return 0;
}


void NJ_Tox_Site_List::merge_json(const QMap<u4, QVector<QPair<r8, r8>>>& merges,
  const QMap<u4, QPair<u4, QStringPair>>& merge_addresses, QString key)
{
 QJsonDocument qjd;
 {
  QFile f(file_path_);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja = qjd.array();

 u4 i = 0;
 for(auto obj: qja)
 {
  QJsonObject qjo = obj.toObject();
  u4 site_id = qjo.value("site-id").toInt();

  auto it = merges.find(site_id);
  if(it == merges.end())
  {
   ++i;
   continue;
  }

  const QVector<QPair<r8, r8>>& prs = *it;

  auto overlap_qsp = merge_addresses.value(site_id);
  u4 overlap = overlap_qsp.first;
  QStringPair qsp = overlap_qsp.second;

  QJsonObject qjol = qjo.value("locations").toObject();

  QJsonObject locations;

  locations.insert("count", prs.size());
  locations.insert("overlap", (int) overlap);

  QJsonArray coords;

  for(auto pr : prs)
  {
   QJsonArray c;
   c.append(pr.first);
   c.append(pr.second);
   coords.append(c);
  }

  locations.insert("coords", coords);
  locations.insert("address-s", qsp.first);
  locations.insert("address-m", qsp.second);


  qjol.insert(key, locations);

  qjo.remove("locations");
  qjo.insert("locations", qjol);

  qja.replace(i, qjo);
  ++i;
 }

 QJsonDocument qjd1;
 qjd1.setArray(qja);

 KA::TextIO::save_file(file_path_, qjd1.toJson());

}


void NJ_Tox_Site_List::import_json_file(QString path)
{
 QMap<u4, NJ_Tox_Site*> sites_by_id;

 for(NJ_Tox_Site& site : sites_)
 {
  sites_by_id[site.site_id()] = &site;
 }

 QJsonDocument qjd;
 {
  QFile f(path);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja = qjd.array();

 for(auto obj: qja)
 {
  QJsonObject qjo = obj.toObject();
  u4 site_id = qjo.value("site-id").toInt();

  NJ_Tox_Site& site = *sites_by_id[site_id];

  QJsonObject qjol = qjo.value("locations").toObject().value("osm").toObject();
  u1 count = qjol.value("count").toInt();

  QJsonArray ca = qjol.value("coords").toArray().first().toArray();
  site.set_latitude(ca.first().toDouble());
  site.set_longitude(ca.last().toDouble());

  site.set_coords_count(count);
 }


}


void NJ_Tox_Site_List::read_json_file()
{
 QJsonDocument qjd;
 {
  QFile f((file_path_));
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja = qjd.array();

 sites_.reserve(qja.size());

 for(auto obj: qja)
 {
  QJsonObject qjo = obj.toObject();
  u4 site_id = qjo.value("site-id").toInt();

  QJsonObject qjol = qjo.value("locations").toObject().value("osm").toObject();
  u1 count = qjol.value("count").toInt();
//  qDebug() << "site: " << site_id << " (" << count << ")";

  QString query_a = qjo.value("query-a").toString();
  QString query_m = qjo.value("query-m").toString();

  sites_.push_back({});
  NJ_Tox_Site& site = sites_.last();

  site.set_site_id(site_id);
  site.set_coords_count(count);
  site.set_street_address(query_a);
  site.set_municipality(query_m);

  site.init_ref_coords();
  QJsonArray qjac = qjol.value("coords").toArray();
  for(QJsonValue qjv : qjac)
  {
   site.ref_coords()->push_back(
     {qjv.toArray().first().toDouble(), qjv.toArray().last().toDouble()});
  }

 }

}


void NJ_Tox_Site_List::to_qmap(QMap<u4, NJ_Tox_Site*>& result)
{
 for(NJ_Tox_Site& site : sites_)
 {
  result.insert(site.site_id(), &site);
 }
}


void NJ_Tox_Site_List::read_csv_file(QVector<void (NJ_Tox_Site::*)(QString)> mds, u4 max)
{
 QList<QStringList> lines = QtCSV::Reader::readToList(file_path_);

 if(max)
   sites_.reserve(max);
 else
   sites_.reserve(lines.length());

 original_header_ = lines.takeFirst();

 u4 count = 0;
 for(QStringList line : lines)
 {
  if(line.isEmpty())
    continue;


  ++count;

  if(max && count == max)
    break;

  sites_.push_back({});

  NJ_Tox_Site& site = sites_.last();

  for(u1 row = 0; row < line.size(); ++row)
  {
   (site.*mds[row])(line[row]);
  }

 }

}
