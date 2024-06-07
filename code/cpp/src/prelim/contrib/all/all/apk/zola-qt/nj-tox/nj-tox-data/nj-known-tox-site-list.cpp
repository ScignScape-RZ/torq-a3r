
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-known-tox-site-list.h"

#include "textio.h"


#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"


#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>



NJ_Known_Tox_Site_List::NJ_Known_Tox_Site_List(QString file_path)
  :  Site_List_Base(file_path)
{

}


void NJ_Known_Tox_Site_List::read_csv_file(decltype(csv_field_setters_)& mds,
  QString csv_file_path, u4 max)
{
 auto& counts = mds.proc_options_counts;

 QList<QStringList> lines = QtCSV::Reader::readToList(csv_file_path);

 u4 ll = lines.length();

 if(ll == 0)
   return;

 if(ll < max)
   sites_.reserve(ll);
 else if(max)
   sites_.reserve(max);
 else
   sites_.reserve(ll);

 original_header_ = lines.takeFirst();

 u4 count = 0;
 for(QStringList line : lines)
 {
  if(line.isEmpty())
    continue;

  ++count;

  if(max && count > max)
    break;



  sites_.push_back({});

  NJ_Known_Tox_Site& site = sites_.last();

  for(u2 column = 0; column < line.size(); ++column)
  {
   u2 column_key = column + 1;
   QVector<u2> cs = counts.value(column_key, {1});

   auto afs = define_setters_data_.affirmative_flag_strings;
   auto acs = define_setters_data_.affirmative_case_sensitive_flag_strings;

   auto ffs = define_setters_data_.falsifying_flag_strings;
   auto fcs = define_setters_data_.falsifying_case_sensitive_flag_strings;

   u2 c = cs.size();
   for(u2 index = 1; index <= c; ++index)
    for(u2 index1 = 1; index1 <= cs[index - 1]; ++index1)
   {
    u2x3 key = {column_key, index, index1};
    auto it = mds.proc_options.find(key);
    if(it != mds.proc_options.end())
    {
     typedef decltype(csv_field_setters_)::Call_Specs specs;
     //?

     auto [_s_info_u2, _s_u2] = Call_Specs_split_u2(it->second);

     if(_s_info_u2 & (u2) specs::Non_Zero)
     {
      if(!line[column].isEmpty())
      {
       bool ok;
       // //   this hopefully catches different 0s for different types ...
       double z = line[column].toDouble(&ok);

       // //  continue on to the call if the string has some non-numeric format ...
       if(ok)
       {
        if(z == 0.)
          continue;
       }
      }
     }

     switch(it->first)
     {
     case decltype(csv_field_setters_)::Proc_Options::m_void:
      {
       auto it1 = mds.m_void.find({column_key, index, index1});
       if(it1 != mds.m_void.end())
       {
        QString lc = line[column];

        auto vec = mds.m_void_supplement.value({column_key, index, index1});
        if(vec.isEmpty())
          vec = {{*it1, specs::Void_True}};

        QVector<u2> indices;

        u2 i = 0;
        for(auto pr : vec)
        {
         if(vec[i].first)
         {
          auto [_s_info, _s] = Call_Specs_split( pr.second );
          switch(_s)
          {
          case specs::Void_Pre:
           indices.push_front(i);
           break;
          case specs::Void_True:
           if(afs.contains(lc.toLower()) || acs.contains(lc))
            indices.push_back(i);
            break;
           case specs::Void_False:
            if(ffs.contains(lc.toLower()) || fcs.contains(lc))
             indices.push_back(i);
             break;
           case specs::Void_Post:
            indices.push_back(i);
            break;
          }
         }
         ++i;
        }
        for(u2 i : indices)
          (site.*(vec[i].first))();
       }
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::m_void_n0:
      { QString lc = line[column];
       auto it1 = mds.m_void_n0.find({column_key, index, index1}); // //z
       if(it1 != mds.m_void_n0.end())
       {
        if(!line[column].isEmpty())
          (site.**it1)();
       }
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::m_void_indexed:
      { QString lc = line[column];
       auto it1 = mds.m_void_indexed.find({{column_key, index, index1}, line[column]}); // //z
       if(it1 != mds.m_void_indexed.end())
         (site.**it1)();
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::n_void:
      {
       auto it1 = mds.n_void.find({column_key, index, index1});
       if(it1 != mds.n_void.end())
         (**it1)(&site);
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::n_void_n0:
      {
       auto it1 = mds.n_void_n0.find({column_key, index, index1}); // //z
       if(it1 != mds.n_void_n0.end())
       {
        if(!line[column].isEmpty())
          (**it1)(&site);
       }
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::n_void_indexed:
      {
       auto it1 = mds.n_void_indexed.find({{column_key, index, index1}, line[column]}); // //z
       if(it1 != mds.n_void_indexed.end())
         (**it1)(&site);
      }
      break;



     case decltype(csv_field_setters_)::Proc_Options::m_QString:
      {
       auto it1 = mds.m_QString.find({column_key, index, index1}); // //z
       if(it1 != mds.m_QString.end())
         (site.**it1)(line[column]);
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::m_QString_n0:
      {
       auto it1 = mds.m_QString_n0.find({column_key, index, index1}); // //z
       if(it1 != mds.m_QString_n0.end() && !line[column].isEmpty())
         (site.**it1)(line[column]);
      }
      break;


     case decltype(csv_field_setters_)::Proc_Options::m_QString_u2:
      {
       auto it1 = mds.m_QString_u2.find({column_key, index, index1}); // //z
       if(it1 != mds.m_QString_u2.end())
         (site.**it1)(line[column], mds.preset_args_u2.value({column_key, index, index1})); //? column_key));
      }
      break;


     case decltype(csv_field_setters_)::Proc_Options::m_QString_u2_n0:
      {
       auto it1 = mds.m_QString_u2_n0.find({column_key, index, index1});
       if(it1 != mds.m_QString_u2_n0.end() && !line[column].isEmpty())
         (site.**it1)(line[column], mds.preset_args_u2.value({column_key, index, index1})); //? column_key));
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::m_QString_QString:
      {
       auto it1 = mds.m_QString_QString.find({column_key, index, index1});
       if(it1 != mds.m_QString_QString.end())
         (site.**it1)(line[column], mds.preset_args_QString.value({column_key, index, index1}));
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::m_QString_QString_n0:
      {
       auto it1 = mds.m_QString_QString_n0.find({column_key, index, index1});
       if(it1 != mds.m_QString_QString_n0.end() && !line[column].isEmpty())
         (site.**it1)(line[column], mds.preset_args_QString.value({column_key, index, index1})); // //z
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::n_QString:
      {
       auto it1 = mds.n_QString.find({column_key, index, index1}); // //z
       if(it1 != mds.n_QString.end())
         (**it1)(&site, line[column]);
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::n_QString_u2:
      {
       auto it1 = mds.n_QString_u2.find({column_key, index, index1}); // //z
       if(it1 != mds.n_QString_u2.end())
         (**it1)(&site, line[column], mds.preset_args_u2.value({column_key, index, index1})); //? ,column_key // //z
      }
      break;

     case decltype(csv_field_setters_)::Proc_Options::n_QString_QString:
      {
       auto it1 = mds.n_QString_QString.find({column_key, index, index1}); // //z
       if(it1 != mds.n_QString_QString.end())
         (**it1)(&site, line[column], mds.preset_args_QString.value({column_key, index, index1})); // //z
      }
      break;

       // //  anything else?
     default:
      break;
     }
    }
   }
  }

//    auto it_1 = mds.methods_1.find(column);
//    if(it_1 != mds.methods_1.end())
//      (site.**it_1)(line[column],  mds.methods_1_args.value(column, column));
//    else
//    {
//     auto it_n0 = mds.non_methods_0.find(column);
//     if(it_n0 != mds.non_methods_0.end())
//       (**it_n0)(line[column]);
//     else
//     {
//      auto it_n1 = mds.non_methods_1.find(column);
//      if(it_n1 != mds.non_methods_1.end())
//        (**it_n1)(line[column],  mds.methods_1_args.value(column, column));
//     }
//    }
//   }
//   else
//   {
//    (site.**it_0)(line[column]);
//   }
//  }


 }

}


void NJ_Known_Tox_Site_List::read_aggregate_json_file(QString file_path)
{
 read_json_file(file_path, [](NJ_Known_Tox_Site& site, QJsonObject qjo)
 {
  QJsonObject sqjo = qjo.value("sai").toObject();
  site.qjo_to_supplemental_address_info(sqjo);

 });
}


void NJ_Known_Tox_Site_List::read_json_file(QString file_path,
  void (*cb) (NJ_Known_Tox_Site&, QJsonObject))
{
 QJsonDocument qjd;
 {
  QFile f(file_path);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja = qjd.array();

 u4 i = 0;
 for(auto obj: qja)
 {
  QJsonObject qjo = obj.toObject();

  NJ_Known_Tox_Site& site = add_site();

  QMapIterator<QString, typename decltype(json_field_setters_)::mapped_type> it(json_field_setters_);

  while(it.hasNext())
  {
   it.next();

   auto it1 = qjo.find(it.key());
   if(it1 == qjo.end())
     continue;

   (site.*it.value())(it1->toString());
  }

  if(cb)
    cb(site, qjo);


 }

}



void NJ_Known_Tox_Site_List::save_to_json_file(QString file)
{
 QJsonDocument qjd;

 QJsonArray qja;

 for(NJ_Known_Tox_Site site : sites_)
 {
  QJsonObject qjo;

  QMapIterator<QString, typename decltype(json_field_getters_)::mapped_type> it(json_field_getters_);

  while(it.hasNext())
  {
   it.next();
   qjo.insert(it.key(), (site.*it.value())());
  }

  qja.append(qjo);
 }

 qjd.setArray(qja);

 KA::TextIO::save_file(file, qjd.toJson());

}



void NJ_Known_Tox_Site_List::save_aggregate_json_file(QString file_path)
{
 QJsonDocument qjd;

 QJsonArray qja;

 for(NJ_Known_Tox_Site site : sites_)
 {
  QJsonObject qjo;

  QMapIterator<QString, typename decltype(json_field_getters_)::mapped_type> it(json_field_getters_);

  while(it.hasNext())
  {
   it.next();
   qjo.insert(it.key(), (site.*it.value())());
  }

  QJsonObject sqjo;
  site.supplemental_address_info_to_qjo(sqjo);
  qjo.insert("sai", sqjo);

  qja.append(qjo);
 }

 qjd.setArray(qja);

 KA::TextIO::save_file(file_path, qjd.toJson());



}


void NJ_Known_Tox_Site_List::merge_with_json_found_or_missing_file(QString found_file,
  QString missing_file)
{
 QJsonDocument qjd_found;
 {
  QFile f(found_file);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd_found = QJsonDocument::fromJson(qba);
 }

 QJsonDocument qjd_missing;
 {
  QFile f(missing_file);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd_missing = QJsonDocument::fromJson(qba);
 }

 QMap<u4, NJ_Known_Tox_Site::Supplemental_Address_Info> sai;

 QJsonArray qja_found = qjd_found.array();
 QJsonArray qja_missing = qjd_missing.array();

 for(auto obj: qja_missing)
 {
  QJsonObject qjo = obj.toObject();
  u4 site_id = qjo.value("site-id").toInt();
  sai[site_id].osm_address = qjo.value("query-a").toString();
  sai[site_id].osm_municipality = qjo.value("query-m").toString();
 }

 for(auto obj: qja_found)
 {
  QJsonObject qjo = obj.toObject();
  u4 site_id = qjo.value("site-id").toInt();
  sai[site_id].osm_address = qjo.value("query-a").toString();
  sai[site_id].osm_municipality = qjo.value("query-m").toString();

  if(qjo.contains("locations"))
  {
   QJsonObject qjols = obj.toObject()["locations"].toObject();
   if(qjols.contains("osm"))
   {
    QJsonArray qja1 = qjols["osm"].toObject()["coords"].toArray();
    for(auto v: qja1)
    {
     QJsonArray qja1 = v.toArray();
     sai[site_id].coords.push_back({qja1.first().toDouble(), qja1.last().toDouble()});
    }
   }
   if(qjols.contains("osm-alt"))
   {
    sai[site_id].osm_alt_address = qjols["osm-alt"].toObject()["address-s"].toString();
    sai[site_id].osm_alt_municipality = qjols["osm-alt"].toObject()["address-m"].toString();
    sai[site_id].overlap_count = qjols["osm-alt"].toObject().value("overlap").toInt();
    QJsonArray qja1 = qjols["osm-alt"].toObject()["coords"].toArray();
    for(auto v: qja1)
    {
     QJsonArray qja1 = v.toArray();
     sai[site_id].alt_coords.push_back({qja1.first().toDouble(), qja1.last().toDouble()});
    }
   }
  }
 }

 for(NJ_Known_Tox_Site& site : sites_)
 {
  auto it = sai.find(site.site_id());
  if(it == sai.end())
  {
   qDebug() << "Unexpected missing address info for site id: " << site.site_id();
   continue;
  }
  site.supplemental_address_info() = *it;
 }

}


void NJ_Known_Tox_Site_List::default_json_field_setters()
{
#define kmd NJ_Known_Tox_Site_SET_KMD_MACRO

 json_field_setters() = {

   kmd(latitude)
   kmd(longitude)
   kmd(coords_count)
   kmd(site_id)
   kmd(pi_number)
   kmd(pi_name)
   kmd(home_owner_status)
   kmd(coords_options)
   kmd(street_address)
   kmd(municipality)
   kmd(county)
   kmd(data_source)

 };
}


void NJ_Known_Tox_Site_List::default_json_field_getters()
{
#define kmd NJ_Known_Tox_Site_KMD_MACRO
#define str_kmd NJ_Known_Tox_Site_STR_KMD_MACRO


 json_field_getters() = {

   str_kmd(latitude)
   str_kmd(longitude)
   str_kmd(coords_count)
   str_kmd(site_id)
   str_kmd(pi_number)

   kmd(pi_name)
   kmd(home_owner_status)
   kmd(coords_options)
   kmd(street_address)
   kmd(municipality)
   kmd(county)
   kmd(data_source)

 };

}


