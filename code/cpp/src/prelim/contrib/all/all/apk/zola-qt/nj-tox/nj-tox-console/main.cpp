
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "nj-tox-data/nj-tox-site-list.h"

#include "nj-tox-data/nj-tri-site-list.h"

#include <QDebug>

#include <QApplication>

#include "textio.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"

#include "global-types.h"

#include <vector>
#include <algorithm>

#include "qtcsv/writer.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QRectF>
#include <QSizeF>

#include "textio.h"

#include <QSvgRenderer>

#include <QTransform>

#include "nj-tox-data/nj-known-tox-site-list.h"


#include <QGeoLocation>

#include <QGeoCoordinate>


//int main(int argc, char *argv[])
//{
// QGeoCoordinate c1 (39.586500, -74.860500);

// QGeoCoordinate c2 (39.612500, -74.830500);

// r8 d1 = c1.distanceTo(c2);
// r8 d2 = c2.distanceTo(c1);

// qDebug() << d1;
// qDebug() << d2;

// return 0;
//}


//, typename FN_Type1, typename FN_Tyoe2

#ifdef HIDE
template<typename SType1, typename SType2, typename CB_Type1, typename CB_Tyoe2>
void make_distance_maps(SType1& s1, SType2& s2,
  QVector<QPair<r8, SType2::Site_type*>>& m1,
  QVector<QPair<r8, SType1::Site_type*>>& m2,
  r8 threshold,
  CB_Type1 cb1, CB_Type2 cb2)
{
 for(SType1::Site_type& site1 : s1.sites())
 {
  QGeoCoordinate qgc1(site1.latitude(), site1.longitude());

  for(SType1::Site_type& site2 : s2.sites())
  {
   QGeoCoordinate qgc2(site2.latitude(), site2.longitude());
   r8 dist = qgc2.distanceTo(qgc1);

   if(dist < threshold)
     m1.push_back({dist, &site2});
  }
 }

 for(SType2::Site_type& site2 : s2.sites())
 {
  QGeoCoordinate qgc2(site2.latitude(), site2.longitude());

  for(SType1::Site_type& site1 : s1.sites())
  {
   QGeoCoordinate qgc1(site1.latitude(), site1.longitude());
   r8 dist = qgc1.distanceTo(qgc2);

   if(dist < threshold)
     m2.push_back({dist, &site1});
  }
 }

 std::sort(m1.begin(), m1.end(), [](auto lhs, auto rhs)
 {
  return lhs.first < rhs.first;
 });

 std::sort(m2.begin(), m2.end(), [](auto lhs, auto rhs)
 {
  return lhs.first < rhs.first;
 });

}
#endif


template<typename sType1, typename SType2>
void make_distance_maps(sType1& site1, SType2& s2,
  QVector<QPair<r8, typename SType2::Site_type*>>& pair_vec,
  r8 threshold)
{
 QGeoCoordinate qgc1(site1.latitude(), site1.longitude());

 for(typename SType2::Site_type& site2 : s2.sites())
 {
  QGeoCoordinate qgc2(site2.latitude(), site2.longitude());
  r8 dist = qgc2.distanceTo(qgc1);

  if(dist < threshold)
    pair_vec.push_back({dist, &site2});
 }

 std::sort(pair_vec.begin(), pair_vec.end(), [](auto lhs, auto rhs)
 {
  return lhs.first < rhs.first;
 });

}


#include "Similarity.h"

bool compare_strings(QString s1, QString s2, QVector<r8>& results)
{
 Similarity sim;

 std::string ss1 = s1.toStdString();
 std::string ss2 = s2.toStdString();

 r8 j = sim.JaccardSimilarity(ss1, ss2);
 r8 p = sim.PSpectrumKernel(ss1, ss2);
 r8 l = sim.LengthWeightedKernel(ss1, ss2);

 results = {j, p, l};

 return j > 0.4 && p > 0 && l > 0.5;
}


int main22(int argc, char *argv[])
{
 QStringList counties = {
   "Atlantic",
   "Bergen",
   "Burlington",
   "Camden",
   "Cape_May",
   "Cumberland",
   "Essex",
   "Gloucester",
   "Hudson",
   "Hunterdon",
   "Mercer",
   "Middlesex",
   "Monmouth",
   "Morris",
   "Ocean",
   "Passaic",
   "Salem",
   "Somerset",
   "Sussex",
   "Union",
   "Warren"
 };


 QString nj_folder = "/home/nlevisrael/docker/tox/objects/active/counties";
 QString tri_folder = "/home/nlevisrael/docker/tox/objects/tri/json/counties/2022";

 u2 threshold = 500;

 QString kdistance_summary_file = "%1/k-tri-d-%2.txt"_qt.arg(tri_folder).arg(threshold);
 QString tdistance_summary_file = "%1/tri-k-d-%2.txt"_qt.arg(tri_folder).arg(threshold);

 QString kdistance_summary_text;
 QString tdistance_summary_text;

 for(QString county : counties)
 {
  kdistance_summary_text += "\n\n\n--- %1 ---"_qt.arg(county);
  tdistance_summary_text += "\n\n\n--- %1 ---"_qt.arg(county);

  QString aggregate_json_file = "%1/%2/ch/%2-aggregate.json"_qt.arg(nj_folder).arg(county);

  NJ_Known_Tox_Site_List nntsl; //(csv_file);
  nntsl.default_json_field_setters();
  nntsl.read_aggregate_json_file(aggregate_json_file);

  QString summary_file = "%1/%2/ch/%2-ds.txt"_qt.arg(nj_folder).arg(county);

  QString summary_text;

  QString tri_json_file = "%1/%2/%2-2022.json"_qt.arg(tri_folder).arg(county);

  NJ_TRI_Site_List ntsl;
  ntsl.default_json_field_setters();
  ntsl.read_json_file(tri_json_file);

//  QVector<QPair<r8, NJ_TRI_Site*>> ds1;
//  QVector<QPair<r8, NJ_Known_Tox_Site*>> ds2;
//  make_distance_maps(nntsl, ntsl, ds1, ds2, threshold);


//  1. s.CosineSimilarity(string1, string2)
//  2. s.LengthWeightedKernel(string1, string2)
//  3. s.JaccardSimilarity(string1, string2)
//  4. s.PSpectrumKernel(string1, string2)
//  5. s.LevenshteinSimilarity(string1, string2)


  for(NJ_Known_Tox_Site& nsite: nntsl.sites())
  {
   QVector<QPair<r8, NJ_TRI_Site*>> ds;
   make_distance_maps(nsite, ntsl, ds, threshold);

   QVector<QPair<r8, NJ_TRI_Site*>> dss;
   QVector<QVector<r8>> sim;

   for(auto pr: ds)
   {
    QVector<r8> sims;
    if(compare_strings(nsite.street_address(), pr.second->street_address(), sims))
    {
     dss.push_back(pr);
     sim.push_back(sims);
    }
   }

   if(dss.isEmpty())
     dss = ds;

   if(!dss.isEmpty())
   {
    kdistance_summary_text += "\n\n%1: %2 %3 = %4 (%5)"_qt.arg(nsite.site_id())
      .arg(nsite.latitude()).arg(nsite.longitude())
      .arg(nsite.street_address()).arg(nsite.municipality());

    u1 count = 0;
    for(auto pr: dss)
    {
     kdistance_summary_text += "\n %1 -> %2: %3 %4 = %5 (%6)"_qt
       .arg(pr.first).arg(pr.second->frs_id())
       .arg(pr.second->latitude()).arg(pr.second->longitude())
       .arg(pr.second->street_address()).arg(pr.second->municipality());

     if(!sim.isEmpty())
       kdistance_summary_text += "\n  Jaccard: %1; PSpectum: %2; LengthWeighted: %3"_qt
         .arg(sim[count][0]).arg(sim[count][1]).arg(sim[count][2]);

     ++count;
    }
   }
  }

  for(NJ_TRI_Site& site: ntsl.sites())
  {
   QVector<QPair<r8, NJ_Known_Tox_Site*>> ds;
   make_distance_maps(site, nntsl, ds, threshold);

   QVector<QPair<r8, NJ_Known_Tox_Site*>> dss;
   QVector<QVector<r8>> sim;

   for(auto pr: ds)
   {
    QVector<r8> sims;

    if(compare_strings(site.street_address(), pr.second->street_address(), sims))
    {
     dss.push_back(pr);
     sim.push_back(sims);
    }
   }

   if(dss.isEmpty())
     dss = ds;

   if(!dss.isEmpty())
   {
    tdistance_summary_text += "\n\n%1: %2 %3 = %4 (%5)"_qt.arg(site.frs_id())
      .arg(site.latitude()).arg(site.longitude())
      .arg(site.street_address()).arg(site.municipality());

    u1 count = 0;
    for(auto pr: dss)
    {
     tdistance_summary_text += "\n %1 -> %2: %3 %4 = %5 (%6)"_qt
      .arg(pr.first).arg(pr.second->site_id())
      .arg(pr.second->latitude()).arg(pr.second->longitude())
      .arg(pr.second->street_address()).arg(pr.second->municipality());

     if(!sim.isEmpty())
       tdistance_summary_text += "\n Jaccard: %1; PSpectum: %2; LengthWeighted: %3"_qt
         .arg(sim[count][0]).arg(sim[count][1]).arg(sim[count][2]);

     ++count;
    }
   }
  }




#ifdef HIDE
  for(NJ_Known_Tox_Site& nsite: nntsl.sites())
  {
   QVector<QPair<r8, NJ_TRI_Site*>> ds;

   QGeoCoordinate nqgc(nsite.latitude(), nsite.longitude());

   for(NJ_TRI_Site& site: ntsl.sites())
   {
    QGeoCoordinate qgc(site.latitude(), site.longitude());
    r8 dist = qgc.distanceTo(nqgc);

    if(dist < threshold)
      ds.push_back({dist, &site});
   }

   std::sort(ds.begin(), ds.end(), [](auto lhs, auto rhs)
   {
    return lhs.first < rhs.first;
   });

   if(!ds.isEmpty())
   {
    kdistance_summary_text += "\n\n%1: %2 %3 = %4 (%5)"_qt.arg(nsite.site_id())
      .arg(nsite.latitude()).arg(nsite.longitude())
      .arg(nsite.street_address()).arg(nsite.municipality());

    for(auto pr: ds)
    {
     kdistance_summary_text += "\n %1 -> %2: %3 %4 = %5 (%6)"_qt
       .arg(pr.first).arg(pr.second->frs_id())
       .arg(pr.second->latitude()).arg(pr.second->longitude())
       .arg(pr.second->street_address()).arg(pr.second->municipality());
    }
   }
  }


  for(NJ_TRI_Site& site: ntsl.sites())
  {
   QVector<QPair<r8, NJ_Known_Tox_Site*>> ds;

   QGeoCoordinate qgc(site.latitude(), site.longitude());

   for(NJ_Known_Tox_Site& nsite: nntsl.sites())
   {
    QGeoCoordinate nqgc(nsite.latitude(), nsite.longitude());
    r8 dist = nqgc.distanceTo(qgc);

    if(dist < threshold)
      ds.push_back({dist, &nsite});
   }

#endif


  //     kdistance_summary_text += "\n\n%1: %2 %3 = %4 (%5)"_qt.arg(nsite.site_id())
  //       .arg(nsite.latitude()).arg(nsite.longitude())
  //       .arg(nsite.street_address()).arg(nsite.municipality());
  //     current_site_id = nsite.site_id();

  //     summary_text += "\n %1 -> %2: %3 %4 = %5 (%6)"_qt
  //       .arg(dist).arg(site.frs_id())
  //       .arg(site.latitude()).arg(site.longitude())
  //       .arg(site.street_address()).arg(site.municipality());

  //     kdistance_summary_text += "\n %1 -> %2: %3 %4 = %5 (%6)"_qt
  //       .arg(dist).arg(site.frs_id())
  //       .arg(site.latitude()).arg(site.longitude())
  //       .arg(site.street_address()).arg(site.municipality());




//  tdistance_summary_text += "\n\n%1: %2 %3 = %4 (%5)"_qt.arg(site.frs_id())
//    .arg(site.latitude()).arg(site.longitude())
//    .arg(site.street_address()).arg(site.municipality());

//  tdistance_summary_text += "\n %1 -> %2: %3 %4 = %5 (%6)"_qt
//    .arg(dist).arg(nsite.site_id())
//    .arg(nsite.latitude()).arg(nsite.longitude())
//    .arg(nsite.street_address()).arg(nsite.municipality());



//  summary_text += "\n\n%1: %2 %3 = %4 (%5)"_qt.arg(nsite.site_id())
//    .arg(nsite.latitude()).arg(nsite.longitude())
//    .arg(nsite.street_address()).arg(nsite.municipality());


//  KA::TextIO::save_file(summary_file, summary_text);
  KA::TextIO::save_file(kdistance_summary_file, kdistance_summary_text);
  KA::TextIO::save_file(tdistance_summary_file, tdistance_summary_text);

 }





 return 0;
}



int main4(int argc, char *argv[])
{
 QStringList counties = {
   "Atlantic",
   "Bergen",
   "Burlington",
   "Camden",
   "Cape_May",
   "Cumberland",
   "Essex",
   "Gloucester",
   "Hudson",
   "Hunterdon",
   "Mercer",
   "Middlesex",
   "Monmouth",
   "Morris",
   "Ocean",
   "Passaic",
   "Salem",
   "Somerset",
   "Sussex",
   "Union",
   "Warren"
 };

 QString folder = "/home/nlevisrael/docker/tox/objects/active/counties/";


 for(QString county : counties)
 {
  QString county_folder = folder + county;
  QString csv_file = "%1/%2-KCSNJ-active.csv"_qt.arg(county_folder).arg(county);
  QString json_found_file = "%1/%2-found.json"_qt.arg(county_folder).arg(county);
  QString json_missing_file = "%1/%2-missing.json"_qt.arg(county_folder).arg(county);

  QString aggregate_json_file = "%1/%2-aggregate.json"_qt.arg(county_folder).arg(county);



  NJ_Known_Tox_Site_List ntsl(csv_file);

  ntsl.define_setters()

    [1]  (& NJ_Known_Tox_Site::set_site_id)
    [2]  (& NJ_Known_Tox_Site::set_pi_number)
    [3]  (& NJ_Known_Tox_Site::set_pi_name)
    [4]  (& NJ_Known_Tox_Site::set_street_address)
    [6]  (& NJ_Known_Tox_Site::set_municipality)
    [7]  (& NJ_Known_Tox_Site::set_county)
    [8]  (& NJ_Known_Tox_Site::set_latitude)
    [9]  (& NJ_Known_Tox_Site::set_longitude)
   [10]  (& NJ_Known_Tox_Site::set_coords_count)
   [11]  (& NJ_Known_Tox_Site::set_data_source)

    ;

  ntsl.read_csv_file();

  ntsl.merge_with_json_found_or_missing_file(json_found_file,
    json_missing_file);

  ntsl.default_json_field_getters();

  ntsl.save_aggregate_json_file(aggregate_json_file);
 }

 return 0;

}

int main5(int argc, char *argv[])
{
 QString json_file = "/home/nlevisrael/docker/tox/objects/tir/summaries/counties/Camden/Camden-2022.json";

 NJ_TRI_Site_List ntsl;

 ntsl.default_json_field_setters();

 ntsl.read_json_file(json_file);

 return 0;
}


int main7(int argc, char *argv[])
{

// QString csv_file_path = "/home/nlevisrael/docker/tox/2022_nj.csv";

// QList<QStringList> lines = QtCSV::Reader::readToList(csv_file_path);

// QtCSV::StringData newlines;

// int c = 0;

// for(QStringList line : lines)
// {
//  if(line[119].size())
//  {
//   ++c;
//   QString l34 = line.takeAt(34);
//   line[33] += "..." + l34;
//  }
//  newlines.addRow(line);
// }

// qDebug() << "c = " << c;

// QString new_path = "/home/nlevisrael/docker/tox/2022_nj-corrected.csv";

// QtCSV::Writer::write(new_path, newlines);

// return 0;

 NJ_TRI_Site_List ntsl ("/home/nlevisrael/docker/tox/2022_nj-corrected.csv");


 ntsl.define_setters()

//    [1]  ++
//         (& NJ_TRI_Site::set_year)
//         (& NJ_TRI_Site::set_year)
//         (& NJ_TRI_Site::set_year)
//    ()

    [1]  (& NJ_TRI_Site::set_year)

    [2]  (& NJ_TRI_Site::set_trifd)
    [3]  (& NJ_TRI_Site::set_frs_id)
    [4]  (& NJ_TRI_Site::set_facility_name)
    [5]  (& NJ_TRI_Site::set_street_address)
    [6]  (& NJ_TRI_Site::set_municipality)
    [7]  (& NJ_TRI_Site::set_county)
    [9]  (& NJ_TRI_Site::read_zip_code)


    [11]  [& NJ_TRI_Site::set_tribe_name]

    [12]  (& NJ_TRI_Site::set_latitude)
    [13]  (& NJ_TRI_Site::set_longitude)
    [14]  (& NJ_TRI_Site::read_horizontal_datum)
    [15]  (& NJ_TRI_Site::set_parent_company_name)
    [16]  (& NJ_TRI_Site::set_parent_company_db_number)
    [17]  (& NJ_TRI_Site::set_parent_company_standardized_name)

    [19]  (& NJ_TRI_Site::set_industry_sector_code)
    [20]  (& NJ_TRI_Site::set_industry_sector)

(0) [21]  ()
     --
    [26]  [& NJ_TRI_Site::add_SIC_code]

(27, 32)  [& NJ_TRI_Site::add_NAICS_code]

   [33]  (& NJ_TRI_Site::set_document_control_number)
   [34]  (& NJ_TRI_Site::set_chemical_name)
   [36]  (& NJ_TRI_Site::set_TRI_chemical_id)
   [37]  (& NJ_TRI_Site::set_CAS_registry_number)
   [38]  (& NJ_TRI_Site::set_SRS_id)
   [40]  (& NJ_TRI_Site::read_classification)

   [42]  (& NJ_TRI_Site::read_metal_category_with_corrections)


//   48 - 61

  ( "5.1"
  , "5.2"
  , "5.3"
  , "5.4"
  , "5.4.1"
  , "5.4.2"
  , "5.5.1"
  , "5.5.1A"
  , "5.5.1B"
  , "5.5.2"
  , "5.5.3"
  , "5.5.3A"
  , "5.5.3B"
  , "5.5.4"
  ) .nonzero [& NJ_TRI_Site::read_discharge_amount]


   [63]  (& NJ_TRI_Site::set_potw_release_or_disposal)
   [64]  (& NJ_TRI_Site::set_potw_further_treatment)
   [65]  [& NJ_TRI_Site::set_potw_total]



   ( "M10"
   , "M41"
   , "M62"
   , "M40_metal"
   , "M61_metal"
   , "M71"
   , "M81"
   , "M82"
   , "M72"
   , "M63"
   , "M66"
   , "M67"
   , "M64"
   , "M65"
   , "M73"
   , "M79"
   , "M90"
   , "M94"
   , "M99"
   , "M20"
   , "M24"
   , "M26"
   , "M28"
   , "M93"
   , "M56"
   , "M92"
   , "M40_non_metal"
   , "M50"
   , "M54"
   , "M61_non_metal"
   , "M69"
   , "M95"
   ) .nonzero [& NJ_TRI_Site::read_offsite_transfer_amount]

++ [85]
   [91]
   [94]
   [101]
   [102]
   [106]
   [107] .nonzero (& NJ_TRI_Site::read_offsite_transfer_or_release_total)


  ( "Onsite_Contained"
  , "Onsite_Other"
  , "Offsite_Contained"
  , "Offsite_Other"
  , "Onsite_Energy_Recovery"
  , "Offsite_Energy_Recovery"
  , "Onsite_Recycling"
  , "Offsite_Recycling"
  , "Onsite_Treatment"
  , "Offsite_Treatment"
  ) .nonzero (& NJ_TRI_Site::read_onsite_and_offsite_amounts)


  [103] (& NJ_TRI_Site::set_overall_offsite_transfer_total)
  [104] (& NJ_TRI_Site::set_onsite_and_offsite_releases_total)
  [105] (& NJ_TRI_Site::set_source_reduction_releases_total)


  [116] (& NJ_TRI_Site::set_production_waste)
  [117] .nonzero [& NJ_TRI_Site::set_one_time_release]
  [119] (& NJ_TRI_Site::set_production_ratio)


  .default_flag_strings()

  [10]  [& NJ_TRI_Site::set_BIA_code]
  [10]  (& NJ_TRI_Site::set_flag <NJ_TRI_Site::on_tribal_land>)


  [18]  (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)

//  [18] ++
//       (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)
//       (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)
//       (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)
//   ()


  [35] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::elemental_metal_included>)      // csv col 35
  [39] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::clean_air_act_chemical>)        // csv col 39
  [41] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::classified_as_metal>)           // csv col 41
  [43] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::carcinogen>)                    // csv col 43
  [44] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::pbt>)                           // csv col 44
  [45] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::pfas>)                          // csv col 45

  [46]
   ("R") (& NJ_TRI_Site::set_flag <NJ_TRI_Site::form_r>)                        // csv col 46
   ["A"] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::form_a>)                        // csv col 46


  [47]
   ("Pounds")  (& NJ_TRI_Site::set_flag <NJ_TRI_Site::units_pounds>)                  // csv col 47
   ["Grams"]   (& NJ_TRI_Site::set_flag <NJ_TRI_Site::units_grams>)                   // csv col 47

  [118]
   ("PRODUCTION") (& NJ_TRI_Site::set_flag <NJ_TRI_Site::production_ratio_value>)        // csv col 118
   ["ACTIVITY"] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::activity_index_value>)          // csv col 118

   ;


 ntsl.read_csv_file();

 QMap<QString, NJ_TRI_Site_List> sites_by_county;

 QString base_folder = "/home/nlevisrael/docker/tox/objects/tir/json/counties/2022/";

 for(NJ_TRI_Site site : ntsl.sites())
 {
  QString county = site.county_ucfirst();

  if(!sites_by_county.contains(county))
  {
   QString county_folder = base_folder + county;

   QDir qd(county_folder);
   if(!qd.exists())
     qd.mkpath(".");

   QString county_file = "%1/%2-2022-simplified.csv"_qt.arg(county_folder).arg(county);

   QString json_file = "%1/%2-2022.json"_qt.arg(county_folder).arg(county);

   sites_by_county[county] = NJ_TRI_Site_List(county_file);

   sites_by_county[county].add_file_path("json", json_file);


  }

  sites_by_county[county].sites().push_back(site);
 }

 auto getters =  csv_field_getters_by_column<NJ_TRI_Site>
     ( //(typename csv_field_getters_by_column<NJ_TRI_Site>::methods_0_vector_type)
      {
       &NJ_TRI_Site::str_frs_id,
       &NJ_TRI_Site::facility_name,
       &NJ_TRI_Site::street_address,
       &NJ_TRI_Site::municipality,
       nullptr,
       &NJ_TRI_Site::str_zip_code,
       &NJ_TRI_Site::str_zplus_4,
       &NJ_TRI_Site::str_latitude,
       &NJ_TRI_Site::str_longitude,
       &NJ_TRI_Site::industry_sector,
       &NJ_TRI_Site::str_industry_sector_code,
 //?      &NJ_TRI_Site::chemical,
       &NJ_TRI_Site::enum_to_numeric_str<NJ_TRI_Site::Classification_Keys>,
 //?      &NJ_TRI_Site::metal_category,
     }, 2  // 2 is the offset, allowing for 2 default columns
     );



 QStringList header {
  "_0", "_1",
  "frs_id",
  "facility_name",
  "street_address",
  "municipality",
  "county",
  "zip_code",
  "zplus_4",
  "latitude",
  "longitude",
  "industry_sector",
  "industry_sector_code",
  "classification",
 };


 QMutableMapIterator it(sites_by_county);

 while(it.hasNext())
 {
  it.next();
//  qDebug() << it.key() << ": " << it.value().file_path();

  NJ_TRI_Site_List& county_ntsl = it.value();

  county_ntsl.default_json_field_getters();

  auto g = getters.copy();
  g.insert_default(it.key());
  county_ntsl.set_csv_field_getters(g);
  county_ntsl.save_to_csv_file("!", &header);

  county_ntsl.save_to_json_file();

 }


// auto g = getters.copy();
// g.insert_default(it.key());

 getters.insert_replacement(&NJ_TRI_Site::county);

 ntsl.set_csv_field_getters(getters);


 ntsl.save_to_csv_file(base_folder + "/nj.csv", &header);



 return 0;
}



// //   MAIN...


int main(int argc, char *argv[])
{
 u2 current_year = 2022;

 NJ_TRI_Site_List ntsl ("/home/nlevisrael/docker/gits/torq-wip/pres/tri/%1_nj-corrected.csv"_qt.arg(current_year));


 ntsl.define_setters()

//    [1]  ++
//         (& NJ_TRI_Site::set_year)
//         (& NJ_TRI_Site::set_year)
//         (& NJ_TRI_Site::set_year)
//    ()

    [1]  (& NJ_TRI_Site::set_year)

    [2]  (& NJ_TRI_Site::set_trifd)
    [3]  (& NJ_TRI_Site::set_frs_id)
    [4]  (& NJ_TRI_Site::set_facility_name)
    [5]  (& NJ_TRI_Site::set_street_address)
    [6]  (& NJ_TRI_Site::set_municipality)
    [7]  (& NJ_TRI_Site::set_county)
    [9]  (& NJ_TRI_Site::read_zip_code)


    [11]  [& NJ_TRI_Site::set_tribe_name]

    [12]  (& NJ_TRI_Site::set_latitude)
    [13]  (& NJ_TRI_Site::set_longitude)
    [14]  (& NJ_TRI_Site::read_horizontal_datum)
    [15]  (& NJ_TRI_Site::set_parent_company_name)
    [16]  (& NJ_TRI_Site::set_parent_company_db_number)
    [17]  (& NJ_TRI_Site::set_parent_company_standardized_name)

    [19]  (& NJ_TRI_Site::set_industry_sector_code)
    [20]  (& NJ_TRI_Site::set_industry_sector)

(0) [21]  ()
     --
    [26]  [& NJ_TRI_Site::add_SIC_code]

(27, 32)  [& NJ_TRI_Site::add_NAICS_code]

   [33]  (& NJ_TRI_Site::set_document_control_number)
   [34]  (& NJ_TRI_Site::set_chemical_name)
   [36]  (& NJ_TRI_Site::set_TRI_chemical_id)
   [37]  (& NJ_TRI_Site::set_CAS_registry_number)
   [38]  (& NJ_TRI_Site::set_SRS_id)
   [40]  (& NJ_TRI_Site::read_classification)

   [42]  (& NJ_TRI_Site::read_metal_category_with_corrections)


//   48 - 61

  ( "5.1"
  , "5.2"
  , "5.3"
  , "5.4"
  , "5.4.1"
  , "5.4.2"
  , "5.5.1"
  , "5.5.1A"
  , "5.5.1B"
  , "5.5.2"
  , "5.5.3"
  , "5.5.3A"
  , "5.5.3B"
  , "5.5.4"
  ) .nonzero [& NJ_TRI_Site::read_discharge_amount]


   [63]  (& NJ_TRI_Site::set_potw_release_or_disposal)
   [64]  (& NJ_TRI_Site::set_potw_further_treatment)
   [65]  [& NJ_TRI_Site::set_potw_total]



   ( "M10"
   , "M41"
   , "M62"
   , "M40_metal"
   , "M61_metal"
   , "M71"
   , "M81"
   , "M82"
   , "M72"
   , "M63"
   , "M66"
   , "M67"
   , "M64"
   , "M65"
   , "M73"
   , "M79"
   , "M90"
   , "M94"
   , "M99"
   , "M20"
   , "M24"
   , "M26"
   , "M28"
   , "M93"
   , "M56"
   , "M92"
   , "M40_non_metal"
   , "M50"
   , "M54"
   , "M61_non_metal"
   , "M69"
   , "M95"
   ) .nonzero [& NJ_TRI_Site::read_offsite_transfer_amount]

++ [85]
   [91]
   [94]
   [101]
   [102]
   [106]
   [107] .nonzero (& NJ_TRI_Site::read_offsite_transfer_or_release_total)


  ( "Onsite_Contained"
  , "Onsite_Other"
  , "Offsite_Contained"
  , "Offsite_Other"
  , "Onsite_Energy_Recovery"
  , "Offsite_Energy_Recovery"
  , "Onsite_Recycling"
  , "Offsite_Recycling"
  , "Onsite_Treatment"
  , "Offsite_Treatment"
  ) .nonzero (& NJ_TRI_Site::read_onsite_and_offsite_amounts)


  [103] (& NJ_TRI_Site::set_overall_offsite_transfer_total)
  [104] (& NJ_TRI_Site::set_onsite_and_offsite_releases_total)
  [105] (& NJ_TRI_Site::set_source_reduction_releases_total)


  [116] (& NJ_TRI_Site::set_production_waste)
  [117] .nonzero [& NJ_TRI_Site::set_one_time_release]
  [119] (& NJ_TRI_Site::set_production_ratio)


  .default_flag_strings()

  [10]  [& NJ_TRI_Site::set_BIA_code]
  [10]  (& NJ_TRI_Site::set_flag <NJ_TRI_Site::on_tribal_land>)


  [18]  (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)

//  [18] ++
//       (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)
//       (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)
//       (& NJ_TRI_Site::set_flag <NJ_TRI_Site::federal_facility>)
//   ()


  [35] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::elemental_metal_included>)      // csv col 35
  [39] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::clean_air_act_chemical>)        // csv col 39
  [41] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::classified_as_metal>)           // csv col 41
  [43] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::carcinogen>)                    // csv col 43
  [44] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::pbt>)                           // csv col 44
  [45] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::pfas>)                          // csv col 45

  [46]
   ("R") (& NJ_TRI_Site::set_flag <NJ_TRI_Site::form_r>)                        // csv col 46
   ["A"] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::form_a>)                        // csv col 46


  [47]
   ("Pounds")  (& NJ_TRI_Site::set_flag <NJ_TRI_Site::units_pounds>)                  // csv col 47
   ["Grams"]   (& NJ_TRI_Site::set_flag <NJ_TRI_Site::units_grams>)                   // csv col 47

  [118]
   ("PRODUCTION") (& NJ_TRI_Site::set_flag <NJ_TRI_Site::production_ratio_value>)        // csv col 118
   ["ACTIVITY"] (& NJ_TRI_Site::set_flag <NJ_TRI_Site::activity_index_value>)          // csv col 118

   ;


 ntsl.read_csv_file();

 QMap<QString, NJ_TRI_Site_List> sites_by_county;

 QString html_folder = "/home/nlevisrael/docker/gits/torq-wip/pres/tri/html/";
 QString base_folder = html_folder + "counties/%1/"_qt.arg(current_year);

 for(NJ_TRI_Site site : ntsl.sites())
 {
  QString county = site.county_ucfirst();

  if(!sites_by_county.contains(county))
  {
   QString county_folder = base_folder + county;

   QDir qd(county_folder);
   if(!qd.exists())
     qd.mkpath(".");

//   QString county_file = "%1/%2-2022-simplified.csv"_qt.arg(county_folder).arg(county);

   QString html_file = "%1/%2-2022.htm"_qt.arg(county_folder).arg(county); // -simplified

   sites_by_county[county] = NJ_TRI_Site_List(); //county_file);

   sites_by_county[county].add_file_path("html", html_file);

  }

  sites_by_county[county].sites().push_back(site);
 }

// auto getters =  csv_field_getters_by_column<NJ_TRI_Site>
//     ( //(typename csv_field_getters_by_column<NJ_TRI_Site>::methods_0_vector_type)
//      {
//       &NJ_TRI_Site::str_frs_id,
//       &NJ_TRI_Site::facility_name,
//       &NJ_TRI_Site::street_address,
//       &NJ_TRI_Site::municipality,
//       nullptr,
//       &NJ_TRI_Site::str_zip_code,
//       &NJ_TRI_Site::str_zplus_4,
//       &NJ_TRI_Site::str_latitude,
//       &NJ_TRI_Site::str_longitude,
//       &NJ_TRI_Site::industry_sector,
//       &NJ_TRI_Site::str_industry_sector_code,
// //?      &NJ_TRI_Site::chemical,
//       &NJ_TRI_Site::enum_to_numeric_str<NJ_TRI_Site::Classification_Keys>,
// //?      &NJ_TRI_Site::metal_category,
//     }, 2  // 2 is the offset, allowing for 2 default columns
//     );



// QStringList header {
//  "_0", "_1",
//  "frs_id",
//  "facility_name",
//  "street_address",
//  "municipality",
//  "county",
//  "zip_code",
//  "zplus_4",
//  "latitude",
//  "longitude",
//  "industry_sector",
//  "industry_sector_code",
//  "classification",
// };


 QString html_template = html_folder + "template.htm";
 QString template_text = KA::TextIO::load_file(html_template);


 QMutableMapIterator it(sites_by_county);

 u1 index = 0;
 i1 max_index = sites_by_county.size();

 QString last_county = sites_by_county.lastKey();
 QString first_county = sites_by_county.firstKey();

// u1 previous_index = 0;
// u1 previous_index = 0;

 u1 year_page = 1;
 u1 previous_year_page = 0;
 u1 max_year_page = 1;




 while(it.hasNext())
 {
  it.next();

  ++index;

  QString html_template_text = template_text;


  html_template_text.replace("%year%", QString::number(current_year));
  html_template_text.replace("%year-page%", QString::number(year_page));
  html_template_text.replace("%max-year-page%", QString::number(max_year_page));

  html_template_text.replace("%county%", it.key());

  html_template_text.replace("%pgnum%", QString::number(index));
  html_template_text.replace("%max-pgnum%", QString::number(max_index));

  if(index == 1)
  {
   html_template_text.replace("%uu-active%", "inactive");
   html_template_text.replace("%uu-onclick%", "");
  }
  else
  {
   html_template_text.replace("%uu-active%", "active");
   html_template_text.replace("%uu-onclick%", "location.href='../../%2/%1/%1-%2.htm'"_qt
     .arg(first_county).arg(current_year));
  }

  if(index == max_index)
  {
   html_template_text.replace("%dd-active%", "inactive");
   html_template_text.replace("%dd-onclick%", "");
  }
  else
  {
   html_template_text.replace("%dd-active%", "active");
   html_template_text.replace("%dd-onclick%", "location.href='../../%2/%1/%1-%2.htm'"_qt
     .arg(last_county).arg(current_year));
  }

// lup-active

  if(year_page < max_year_page)
  {
   html_template_text.replace("%year-down%", "location.href='%1-%2.htm'"_qt
     .arg(last_county).arg(current_year - 1));
   html_template_text.replace("%year-down-active%", "active");
  }
  else
  {
   html_template_text.replace("%year-down%", "");
   html_template_text.replace("%year-down-active%", "inactive");
  }

  if(year_page > 1)
  {
   html_template_text.replace("%year-up%", "location.href='%1-%2.htm'"_qt
     .arg(last_county).arg(current_year + 1));
   html_template_text.replace("%year-up-active%", "active");
  }
  else
  {
   html_template_text.replace("%year-up%", "");
   html_template_text.replace("%year-up-active%", "inactive");
  }

  if(index < max_index)
  {
   html_template_text.replace("%county-down%", "location.href='../../%2/%1/%1-%2.htm'"_qt
     .arg(sites_by_county.keys()[index]).arg(current_year));
   html_template_text.replace("%county-down-active%", "active");
  }
  else
  {
   html_template_text.replace("%county-down%", "");
   html_template_text.replace("%county-down-active%", "inactive");
  }


  if(index > 1)
  {
   html_template_text.replace("%county-up%", "location.href='../../%2/%1/%1-%2.htm'"_qt
     .arg(sites_by_county.keys()[index - 1]).arg(current_year));
   html_template_text.replace("%county-up-active%", "active");
  }
  else
  {
   html_template_text.replace("%county-up%", "");
   html_template_text.replace("%county-up-active%", "inactive");
  }


//  uu-active

  NJ_TRI_Site_List& county_ntsl = it.value();

//  county_ntsl.default_json_field_getters();
//  auto g = getters.copy();
//  g.insert_default(it.key());
//  county_ntsl.set_csv_field_getters(g);
//  county_ntsl.save_to_csv_file("!", &header);
//  county_ntsl.save_to_json_file();


  QString path = county_ntsl.get_file_path("html");

  QString html_text = "<tr><td colspan='2' class='county-plus-count'>"
    "<span class='osa:scalar' data-osa_field='county'>"
    "%1: %2 sites"
    "</span>\n"_qt
    .arg(it.key()).arg(county_ntsl.sites().size());

  QString tr_text = R"(
<tr><td class='field-name'>%1</td>
<td><span class='osa:scalar'  data-osa_field='%2'>%3</span>
</td></tr>)";


  for(const NJ_TRI_Site& site : county_ntsl) //.sites())
  {
   html_text += "\n\n<!-- site -->\n";
   html_text += "\n<tr class='new-site'><td colspan='2'>&nbsp;</td></tr>\n";

   // // NAICS_codes
   // // SIC_codes

#define _as_tr_text(n, f, m) tr_text.arg(n).arg(#f).arg(site.m())
#define as_tr_text(n, f) _as_tr_text(n, f, f)
#define as_tr_text_str(n, f) tr_text.arg(n).arg(#f).arg(site.str_##f())
#define as_tr_text_str_map(n, f) tr_text.arg(n).arg(#f).arg(site.str_map_##f())

#define as_tr_text_str_enum(n, f, e) tr_text.arg(n).arg(#f).arg(site.enum_to_numeric_str<NJ_TRI_Site::e>())

   //site.NAICS_codes()


   html_text += as_tr_text_str("NAICS Codes", NAICS_codes).replace("class='field-name'",
     "class='field-name first-line'");
   html_text += as_tr_text_str("SIC Codes", SIC_codes);

   html_text += as_tr_text("SRS ID", SRS_id); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='SRS_id'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.SRS_id());


   html_text += as_tr_text("TRI Chemical Id", TRI_chemical_id); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='TRI_chemical_id'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.TRI_chemical_id());
   html_text += as_tr_text("Chemical Name", chemical_name); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='chemical_name'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.chemical_name());

   // // classification
   html_text += as_tr_text_str_enum("Classification", classification, Classification_Keys);

   html_text += as_tr_text("Document Control Number", document_control_number); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='document_control_number'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.document_control_number());
   html_text += as_tr_text("Facility Name", facility_name); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='facility_name'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.facility_name());
   html_text += as_tr_text("FRS ID", frs_id); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='frs_id'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.frs_id());

   // //  horizontal datum
   html_text += as_tr_text_str_enum("Horizontal Datum", horizontal_datum, Horizontal_Datum_Options);


   html_text += as_tr_text("Industry Sector", industry_sector); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='industry_sector'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.industry_sector());
   html_text += as_tr_text("Industry Sector Code", industry_sector_code); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='industry_sector_code'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.industry_sector_code());
   html_text += as_tr_text("Latitude", latitude); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='latitude'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.latitude());
   html_text += as_tr_text("Longitude", longitude); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='longitude'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.longitude());

   // //  metal category
   html_text += as_tr_text_str_enum("Metal Category", metal_category, Metal_Category);


   html_text += as_tr_text("Municipality", municipality); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='municipality'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.municipality());

   // // offsite transfer amounts
   html_text += as_tr_text_str_map("Offsite Transfer Amounts", offsite_transfer_amounts);

   // // offsite transfer or release totals
   html_text += as_tr_text_str_map("Offsite Transfer or Release Totals", offsite_transfer_or_release_totals);


   html_text += as_tr_text("One Iime Release", one_time_release); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='one_time_release'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.one_time_release());

   // //  onsite_and_offsite_amounts
   html_text += as_tr_text_str_map("Onsite and Offsite Amounts", onsite_and_offsite_amounts);

   html_text += as_tr_text("Onsite and Offsite Releases Total", onsite_and_offsite_releases_total); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='onsite_and_offsite_releases_total'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.onsite_and_offsite_releases_total());
   html_text += as_tr_text("Onsite Release Total", onsite_release_total); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='onsite_release_total'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.onsite_release_total());
   html_text += as_tr_text("Overall Offsite Transfer Total", overall_offsite_transfer_total); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='overall_offsite_transfer_total'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.overall_offsite_transfer_total());

   // //  parent company
   html_text += _as_tr_text("Parent Company Name", parent_company:name, get_parent_company_name);
   html_text += _as_tr_text("Parent Company Standardized Name", parent_company:name,
     get_parent_company_standardized_name);
   html_text += _as_tr_text("Parent Company DB#", parent_company:db_number, get_parent_company_db_number);



   html_text += as_tr_text("POTW Further Treatment", potw_further_treatment); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='potw_further_treatment'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.potw_further_treatment());
   html_text += as_tr_text("POTW Release or Disposal", potw_release_or_disposal); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='potw_release_or_disposal'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.potw_release_or_disposal());
   html_text += as_tr_text("POTW Total", potw_total); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='potw_total'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.potw_total());
   html_text += as_tr_text("Production Ratio", production_ratio); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='production_ratio'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.production_ratio());
   html_text += as_tr_text("Production Waste", production_waste); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='production_waste'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.production_waste());
   html_text += as_tr_text("Source Reduction Releases Total", source_reduction_releases_total); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='source_reduction_releases_total'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.source_reduction_releases_total());
   html_text += as_tr_text("Street Address", street_address); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='street_address'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.street_address());
   html_text += as_tr_text("TRIFD", trifd); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='trifd'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.trifd());
   html_text += as_tr_text("ZIP Code", zip_code); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='zip_code'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.zip_code(), 5, 10, QChar('0'));
   html_text += as_tr_text("ZIP plus 4", zplus_4); // "\n<tr><td></td><td><span   class='osa:scalar'  data-osa_field='zplus_4'>%1</span></td></tr>"_qt
     // .arg("#field").arg(site.zplus_4(), 9, 10, QChar('0'));

  }

  html_template_text.replace("%%TEXT%%", html_text);

  KA::TextIO::save_file(path, html_template_text);
 }


// auto g = getters.copy();
// g.insert_default(it.key());

// getters.insert_replacement(&NJ_TRI_Site::county);
// ntsl.set_csv_field_getters(getters);
// ntsl.save_to_csv_file(base_folder + "/nj.csv", &header);



 return 0;
}







#ifdef HIDE

void main_by_year(u2 year)
{
 QStringList counties = {
   "Atlantic",
   "Bergen",
   "Burlington",
   "Camden",
   "Cape_May",
   "Cumberland",
   "Essex",
   "Gloucester",
   "Hudson",
   "Hunterdon",
   "Mercer",
   "Middlesex",
   "Monmouth",
   "Morris",
   "Ocean",
   "Passaic",
   "Salem",
   "Somerset",
   "Sussex",
   "Union",
   "Warren"
 };

// std::map<QString, QString> case_lower;
// std::transform(counties.begin(), counties.end(), std::inserter(case_lower, case_lower.end()),
//   [](const QString& c)
// {
//  return std::make_pair(c.toLower(), c);
// });

//? QString counties_folder = "/home/nlevisrael/docker/tox/objects/active/counties";
//
 QString counties_folder = "/home/nlevisrael/docker/tox/objects/tir/counties";


 NJ_TRI_Site_List ntsl("/home/nlevisrael/docker/tox/objects/tir/years/%1_nj.csv"_qt.arg(year));

// csv_field_setters_by_column<NJ_TRI_Site> s{{
//  &NJ_TRI_Site::set_frs_id,
//  &NJ_TRI_Site::set_street_address,
//  &NJ_TRI_Site::set_municipality,
//  &NJ_TRI_Site::set_county,
//  }};

 ntsl.set_csv_field_setters(csv_field_setters_by_column<NJ_TRI_Site>
    {{
      {2, &NJ_TRI_Site::set_frs_id},
      {3, &NJ_TRI_Site::set_facility_name},
      {4, &NJ_TRI_Site::set_street_address},
      {5, &NJ_TRI_Site::set_municipality},
      {6, &NJ_TRI_Site::set_county},
      {8, &NJ_TRI_Site::set_zip_code},
      {11, &NJ_TRI_Site::set_latitude},
      {12, &NJ_TRI_Site::set_longitude},
      {19, &NJ_TRI_Site::set_industry_sector},
      {18, &NJ_TRI_Site::set_industry_sector_code},
//      {33, &NJ_TRI_Site::set_chemical},
      {39, &NJ_TRI_Site::set_classification},
//      {41, &NJ_TRI_Site::set_metal_category},
    }}
    );


// QVector<QString (NJ_TRI_Site::*)() const>  qv;
// qv.push_back(&NJ_TRI_Site::str_frs_id);
// ntsl.set_csv_field_getters(csv_field_getters_by_column<NJ_TRI_Site>(qv));

 ntsl.set_csv_field_getters(csv_field_getters_by_column<NJ_TRI_Site>
    ((typename decltype(ntsl.csv_field_getters())::methods_vector_type) // QVector<QString (NJ_TRI_Site::*)() const>
     {
      &NJ_TRI_Site::str_frs_id,
      &NJ_TRI_Site::facility_name,
      &NJ_TRI_Site::street_address,
      &NJ_TRI_Site::municipality,
      &NJ_TRI_Site::county,
      &NJ_TRI_Site::str_zip_code,
      &NJ_TRI_Site::str_latitude,
      &NJ_TRI_Site::str_longitude,
      &NJ_TRI_Site::industry_sector,
      &NJ_TRI_Site::str_industry_sector_code,
//?      &NJ_TRI_Site::chemical,
      &NJ_TRI_Site::classification,
//?      &NJ_TRI_Site::metal_category,
    }, 2  // 2 is the offset, allowing for 2 default columns
    )
    );

 ntsl.add_default_field_getter(0, "tri");
 ntsl.add_default_field_getter(1, QString::number(year));



 QString file_pattern = counties_folder + "/%1/years/%1" +
   "-tri-%1.csv"_qt.arg(year);

 QMap<QString, NJ_TRI_Site_List*> split;

 auto mph = ntsl.split_by_county(split, &file_pattern);

 QMapIterator<QString, NJ_TRI_Site_List*> it(split);
 while (it.hasNext())
 {
  it.next();

  QString lower = it.key().toLower().simplified();

  lower.replace(' ', '_');

  for(QString c : counties)
  {
   if(c.toLower() == lower)
   {
    QString file_path = it.value()->file_path();
    file_path.replace(it.key(), c);
    it.value()->set_file_path(file_path);
   }
  }

//  qDebug() << "county: " << it.value()->file_path();
 }

// &NJ_TRI_Site::str_frs_id,
// &NJ_TRI_Site::facility_name,
// &NJ_TRI_Site::street_address,
// &NJ_TRI_Site::municipality,
// &NJ_TRI_Site::county,
// &NJ_TRI_Site::str_zip_code,
// &NJ_TRI_Site::str_latitude,
// &NJ_TRI_Site::str_longitude,
// &NJ_TRI_Site::industry_sector,
// &NJ_TRI_Site::str_industry_sector_code,
// &NJ_TRI_Site::chemical,
// &NJ_TRI_Site::classification,
// &NJ_TRI_Site::metal_category,

 QStringList header {{
   "Data_Source",
   "Year",
   "FRS_ID",
   "Facility_Name",
   "Street_Address",
   "Municipality",
   "County",
   "Zip_Code",
   "Latitude",
   "Longitude",
   "Industry_Sector",
   "Industry_Sector_Code",
   "Chemical",
   "Classification",
   "Metal_Category",
                     }};

 for(NJ_TRI_Site_List* ntslc : split.values())
 {
  ntslc->set_csv_field_getters(ntsl.csv_field_getters());

  ntslc->save_to_csv_file("!", &header);
 // ntslc->
 }


 mph.delete_now();

// for(QString county : counties)
// {

// }

}

int main(int argc, char *argv[])
{
 for(u2 y = 2022; y >= 1987; --y)
 {
  main_by_year(y);
 }
 return 0;
}

int main8(int argc, char *argv[])
{
 QStringList counties = {
//   "Atlantic",
//   "Bergen",
   "Burlington",
   "Camden",
   "Cape_May",
   "Cumberland",
   "Essex",
   "Gloucester",
   "Hudson",
   "Hunterdon",
   "Mercer",
   "Middlesex",
   "Monmouth",
   "Morris",
   "Ocean",
   "Passaic",
   "Salem",
   "Somerset",
   "Sussex",
   "Union",
   "Warren"
 };

//?
 QString counties_folder = "/home/nlevisrael/docker/tox/objects/active/counties";
// QString counties_folder = "/home/nlevisrael/docker/tox/objects/tir/counties";


 for(QString county : counties)
 {
  NJ_Tox_Site_List ntsl(counties_folder + "/%1/pre-lookup.csv"_qt.arg(county));

  ntsl.set_csv_field_setters({
   &NJ_Tox_Site::set_site_id,
   &NJ_Tox_Site::set_pi_number,
   &NJ_Tox_Site::set_pi_name,
   &NJ_Tox_Site::set_street_address,
   &NJ_Tox_Site::set_home_owner_status,
   &NJ_Tox_Site::set_municipality,
   &NJ_Tox_Site::set_county,
//   &NJ_Tox_Site::set_latitude,
//   &NJ_Tox_Site::set_longitude,
//   &NJ_Tox_Site::set_coords_count,
//   &NJ_Tox_Site::set_coords_options,
//   &NJ_Tox_Site::set_data_source
  });

  ntsl.read_csv_file();

  ntsl.import_json_file(counties_folder + "/%1/%1-found.json"_qt.arg(county));

  QStringList header = ntsl.original_header();

  header.append({"latitude", "Longitude", "Coords_Count", "Data_Source"});

  QString out_file = counties_folder + "/%1/%1-KCSNJ-active.csv"_qt.arg(county);

  ntsl.set_data_source_string("KCSNJ-active");

  ntsl.save_to_csv_file({
    &NJ_Tox_Site::str_site_id,
    &NJ_Tox_Site::str_pi_number,
    &NJ_Tox_Site::pi_name,
    &NJ_Tox_Site::street_address,
    &NJ_Tox_Site::home_owner_status,
    &NJ_Tox_Site::municipality,
    &NJ_Tox_Site::county,
    &NJ_Tox_Site::str_latitude,
    &NJ_Tox_Site::str_longitude,
    &NJ_Tox_Site::str_coords_count,
    nullptr // "KCSNJ-active"
   }, out_file, &header);
 }

 return 0;
}



int main7(int argc, char *argv[])
{
 QCoreApplication qapp(argc, argv);

 QGeoServiceProvider gsp("osm");
 QGeoCodingManager* gcm = gsp.geocodingManager();

 QStringList counties = {
   "Atlantic",
   "Bergen",
   "Burlington",
   "Camden",
   "Cape_May",
   "Cumberland",
   "Essex",
   "Gloucester",
   "Hudson",
   "Hunterdon",
   "Mercer",
   "Middlesex",
   "Monmouth",
   "Morris",
   "Ocean",
   "Passaic",
   "Salem",
   "Somerset",
   "Sussex",
   "Union",
   "Warren"
 };

 QString counties_folder = "/home/nlevisrael/docker/tox/objects/active/counties";

 QStringList counties_s = {
  "Union",
  "Warren"
 };

// "Hudson",
// "Hunterdon",
// "Mercer",

 NJ_Tox_Site_List ntsl1("/home/nlevisrael/docker/tox/KCSNJ/active-found_merged.csv");

 ntsl1.set_csv_field_setters({
  &NJ_Tox_Site::set_site_id,
  &NJ_Tox_Site::set_pi_number,
  &NJ_Tox_Site::set_pi_name,
  &NJ_Tox_Site::set_street_address,
  &NJ_Tox_Site::set_home_owner_status,
  &NJ_Tox_Site::set_municipality,
  &NJ_Tox_Site::set_county,
  &NJ_Tox_Site::set_latitude,
  &NJ_Tox_Site::set_longitude,
  &NJ_Tox_Site::set_coords_count,
  &NJ_Tox_Site::set_coords_options,
  &NJ_Tox_Site::set_data_source
 });



 ntsl1.read_csv_file();

 QMap<u4, NJ_Tox_Site*> sites_by_id;
 ntsl1.to_qmap(sites_by_id);

 for(QString county : counties_s)
 {
  QMap<u4, QVector<QPair<r8, r8>>> merges;
  QMap<u4, QPair<u4, QStringPair>> merge_addresses;

  NJ_Tox_Site_List ntsl(counties_folder);
  ntsl.read_json_county_file(county, county + "-found.json");

  NJ_Tox_Site_List ntsl2(counties_folder);
  ntsl2.set_csv_field_setters({
   &NJ_Tox_Site::set_site_id,
   &NJ_Tox_Site::set_pi_number,
   &NJ_Tox_Site::set_pi_name,
   &NJ_Tox_Site::set_street_address,
   &NJ_Tox_Site::set_home_owner_status,
   &NJ_Tox_Site::set_municipality,
   &NJ_Tox_Site::set_county
  });
  ntsl2.read_csv_county_file(county, "pre-lookup.csv");

  QMap<u4, NJ_Tox_Site*> pre_sites_by_id;
  ntsl2.to_qmap(pre_sites_by_id);


  for(NJ_Tox_Site& site : ntsl.sites())
  {
   u4 id = site.site_id();

   u1 count = site.coords_count();
   NJ_Tox_Site* ps = sites_by_id.value(id);

   NJ_Tox_Site* pps = pre_sites_by_id.value(id);


   if(ps)
   {
    bool mismatch = false;
    if(count != ps->coords_count())
      mismatch = true;
    else if(site.municipality() != ps->municipality())
      mismatch = true;
    else if(site.street_address() != ps->street_address())
      mismatch = true;

    else if(count != pps->coords_count())
      mismatch = true;
    else if(site.municipality() != pps->municipality())
      mismatch = true;
    else if(site.street_address() != pps->street_address())
      mismatch = true;

    if(mismatch)
    {
     if(QVector<QPair<r8, r8>>* ref = site.ref_coords())
     {
      QVector<QPair<r8, r8>>* addresses;
      QStringPair qsp;

      QVector<QPair<r8, r8>> addresses1;
      NJ_Tox_Site_List::check_address(gcm, ps->street_address(), ps->municipality(), addresses1);

      QVector<QPair<r8, r8>> addresses2;
      NJ_Tox_Site_List::check_address(gcm, pps->street_address(), pps->municipality(), addresses2);

      if(addresses1.size() < addresses2.size())
      {
       addresses = &addresses2;
       qsp = {pps->street_address(), pps->municipality()};
      }
      else
      {
       addresses = &addresses1;
       qsp = {ps->street_address(), ps->municipality()};
      }

      if(addresses->isEmpty())
        continue;

      QVector<QPair<r8, r8>> r = *ref, a = *addresses;

      s1 comp = NJ_Tox_Site_List::compare(r, a);

      if(comp != 0)
      {
       u4 s_before = addresses->size();

       auto it = std::remove_if(addresses->begin(), addresses->end(), [ref](const QPair<r8, r8>& pr)
       {
        for(const QPair<r8, r8>& rpr : *ref)
        {
         if(pr == rpr)
           return true;
        }
        return false;
       });
       addresses->erase(it, addresses->end());

       u4 s_after = addresses->size();

       if(s_after)
       {
        qDebug() << "\nMismatch: " << id << " ___________";
        qDebug() << " " << r << "\n-------\n " << a << "\n.........\n";

        merges[id] = *addresses;
        merge_addresses[id] = {s_before - s_after, qsp};
       }
      }
     }
    }
   }
   else
   {
    qDebug() << "Site missing: site id " << id;
   }
  }

  QString bak = ntsl.file_path();
  KA::TextIO::copy_binary_file(bak, bak + ".bak.txt");

  ntsl.merge_json(merges, merge_addresses, "osm-alt");

 }

}



int main5(int argc, char *argv[])
{
 QCoreApplication qapp(argc, argv);

 QGeoServiceProvider gsp("osm");
 QGeoCodingManager* gcm = gsp.geocodingManager();


 QString s1 = "2 ABSECON BLVD";
 QString s2 = "2 ABSECON BLVD";

 QString m1 = "Absecon";
 QString m2 = "Absecon City";

 QVector<QPair<r8, r8>> r1;
 QVector<QPair<r8, r8>> r2;

 NJ_Tox_Site_List::check_address(gcm, s1, m1, r1);
 NJ_Tox_Site_List::check_address(gcm, s2, m2, r2);

 qDebug() << r1 << "\n";
 qDebug() << r2 << "\n";


}


int main3(int argc, char *argv[])
{
 QCoreApplication qapp(argc, argv);

 QStringList counties = {
   "Atlantic",
   "Bergen",
   "Burlington",
   "Camden",
   "Cape_May",
   "Cumberland",
   "Essex",
   "Gloucester",
   "Hudson",
   "Hunterdon",
   "Mercer",
   "Middlesex",
   "Monmouth",
   "Morris",
   "Ocean",
   "Passaic",
   "Salem",
   "Somerset",
   "Sussex",
   "Union",
   "Warren"
 };

 QString counties_folder = "/home/nlevisrael/docker/tox/objects/active/counties";

 QStringList counties_s = {
  "Somerset",
  "Sussex",
  "Union",
  "Warren"
 };

 for(QString county : counties_s)
 {
  NJ_Tox_Site_List ntsl(counties_folder);

  ntsl.set_csv_field_setters({
   &NJ_Tox_Site::set_site_id,
   &NJ_Tox_Site::set_pi_number,
   &NJ_Tox_Site::set_pi_name,
   &NJ_Tox_Site::set_street_address,
   &NJ_Tox_Site::set_home_owner_status,
   &NJ_Tox_Site::set_municipality,
   &NJ_Tox_Site::set_county,
 //  &NJ_Tox_Site::set_latitude,
 //  &NJ_Tox_Site::set_longitude,
 //  &NJ_Tox_Site::set_coords_count,
 //  &NJ_Tox_Site::set_coords_options,
 //  &NJ_Tox_Site::set_data_source
  });

  ntsl.set_csv_field_getters(
  {
   &NJ_Tox_Site::str_site_id,
   &NJ_Tox_Site::str_pi_number,
   &NJ_Tox_Site::pi_name,
   &NJ_Tox_Site::street_address,
   &NJ_Tox_Site::home_owner_status,
   &NJ_Tox_Site::municipality,
   &NJ_Tox_Site::county,
 //  &NJ_Tox_Site::str_latitude,
 //  &NJ_Tox_Site::str_longitude,
 //  &NJ_Tox_Site::str_coords_count,
 //  &NJ_Tox_Site::coords_options,
 //  &NJ_Tox_Site::data_source
  });


  ntsl.read_csv_county_file(county, "pre-lookup.csv");

  QStringList qGeoSrvList = { "osm" };

  ntsl.set_municipality_edit_callback([](QString& muni)
  {
   if(muni.endsWith(" Twp"))
   {
    muni.chop(4);
    //? muni += "Township";
   }
   else if(muni.endsWith(" Boro"))
   {
    muni.chop(5);
   }
   else if(muni.endsWith(" Village"))
   {
    muni.chop(8);
   }
   else if(muni.endsWith(" City"))
   {
    if(muni == "Union City")
      goto after_cities;
    if(muni == "Jersey City")
      goto after_cities;
    if(muni == "Perth Amboy City")
      goto after_cities;
    if(muni == "Atlantic City")
      goto after_cities;
    if(muni == "Gloucester City")
      goto after_cities;

    muni.chop(5);
   }
   else if(muni.endsWith(" Town"))
   {
    muni.chop(5);
   }
  after_cities:;
  });


  QString found_file = "%1/%2/%2-found.json"_qt.arg(counties_folder).arg(county);
  QString missing_file = "%1/%2/%2-missing.json"_qt.arg(counties_folder).arg(county);

  ntsl.check_addresses_json(qGeoSrvList, found_file, missing_file);

 }

 return 0;
}

int main12(int argc, char *argv[])
{


 NJ_Tox_Site_List ntsl("/home/nlevisrael/docker/tox/KCSNJ/active-clean.csv");

 ntsl.set_csv_field_setters({
  &NJ_Tox_Site::set_site_id,
  &NJ_Tox_Site::set_pi_number,
  &NJ_Tox_Site::set_pi_name,
  &NJ_Tox_Site::set_street_address,
  &NJ_Tox_Site::set_home_owner_status,
  &NJ_Tox_Site::set_municipality,
  &NJ_Tox_Site::set_county,
//  &NJ_Tox_Site::set_latitude,
//  &NJ_Tox_Site::set_longitude,
//  &NJ_Tox_Site::set_coords_count,
//  &NJ_Tox_Site::set_coords_options,
//  &NJ_Tox_Site::set_data_source
 });

 ntsl.set_csv_field_getters(
 {
  &NJ_Tox_Site::str_site_id,
  &NJ_Tox_Site::str_pi_number,
  &NJ_Tox_Site::pi_name,
  &NJ_Tox_Site::street_address,
  &NJ_Tox_Site::home_owner_status,
  &NJ_Tox_Site::municipality,
  &NJ_Tox_Site::county,
//  &NJ_Tox_Site::str_latitude,
//  &NJ_Tox_Site::str_longitude,
//  &NJ_Tox_Site::str_coords_count,
//  &NJ_Tox_Site::coords_options,
//  &NJ_Tox_Site::data_source
 });

 ntsl.distribute_by_county("/home/nlevisrael/docker/tox/objects/active/counties");

 return 0;
}


int main6(int argc, char *argv[])
{
// QStringList qGeoSrvList
//     = QGeoServiceProvider::availableServiceProviders();

// qDebug() << qGeoSrvList;

// QApplication qapp(argc, argv);


// QGeoServiceProvider gsp("osm");
// QGeoCodingManager* gcm = gsp.geocodingManager();

// QPair<r8, r8> pr = NJ_Tox_Site_List::check_address(gcm,
//   "1501 MARINA BLVD",
//   "Atlantic City");

// qDebug() << pr;


 return 0;
}




int main4(int argc, char *argv[])
{
// QStringList qGeoSrvList
//     = QGeoServiceProvider::availableServiceProviders();

// qDebug() << qGeoSrvList;

// QApplication qapp(argc, argv);


// QGeoServiceProvider gsp("osm");
// QGeoCodingManager* gcm = gsp.geocodingManager();

// QPair<r8, r8> pr = NJ_Tox_Site_List::check_address(gcm,
//   "1501 MARINA BLVD",
//   "Atlantic City");

// qDebug() << pr;


 return 0;
}

int main2(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 QGeoServiceProvider gsp("osm");
 QGeoCodingManager* gcm = gsp.geocodingManager();

 //NJ_Tox_Site_List ntsl("/home/nlevisrael/docker/tox/KCSNJ/active-m-m.csv");

 NJ_Tox_Site_List ntsl("/home/nlevisrael/docker/tox/KCSNJ/m-temp.csv");

 auto setters = {
  &NJ_Tox_Site::set_site_id,
  &NJ_Tox_Site::set_pi_number,
  &NJ_Tox_Site::set_pi_name,
  &NJ_Tox_Site::set_street_address,
  &NJ_Tox_Site::set_home_owner_status,
  &NJ_Tox_Site::set_municipality,
  &NJ_Tox_Site::set_county,
  &NJ_Tox_Site::set_latitude,
  &NJ_Tox_Site::set_longitude,
  &NJ_Tox_Site::set_coords_count,
  &NJ_Tox_Site::set_coords_options,
  &NJ_Tox_Site::set_data_source
 };

 ntsl.read_csv_file(setters);

 ntsl.check_addresses(gcm,
 {
  {"BLVD", "Boulevard"}
 });

 ntsl.save_to_csv_file(
 {
  &NJ_Tox_Site::str_site_id,
  &NJ_Tox_Site::str_pi_number,
  &NJ_Tox_Site::pi_name,
  &NJ_Tox_Site::street_address,
  &NJ_Tox_Site::home_owner_status,
  &NJ_Tox_Site::municipality,
  &NJ_Tox_Site::county,
  &NJ_Tox_Site::str_latitude,
  &NJ_Tox_Site::str_longitude,
  &NJ_Tox_Site::str_coords_count,
  &NJ_Tox_Site::coords_options,
  &NJ_Tox_Site::data_source
 }
 );

 return 0;
}

int main1(int argc, char *argv[])
{
 NJ_Tox_Site_List ntsl1("/home/nlevisrael/docker/tox/KCSNJ/active-found.csv");
 NJ_Tox_Site_List ntsl2("/home/nlevisrael/docker/tox/KCSNJ/active-m-f.csv");

 auto setters = {
  &NJ_Tox_Site::set_site_id,
  &NJ_Tox_Site::set_pi_number,
  &NJ_Tox_Site::set_pi_name,
  &NJ_Tox_Site::set_street_address,
  &NJ_Tox_Site::set_home_owner_status,
  &NJ_Tox_Site::set_municipality,
  &NJ_Tox_Site::set_county,
  &NJ_Tox_Site::set_latitude,
  &NJ_Tox_Site::set_longitude,
  &NJ_Tox_Site::set_coords_count,
  &NJ_Tox_Site::set_coords_options,
  &NJ_Tox_Site::set_data_source
 };

 ntsl1.read_csv_file(setters);
 ntsl2.read_csv_file(setters);

 ntsl1.merge_with(ntsl2);
 ntsl1.sort_by_site_id();

 ntsl1.save_to_csv_file(
 {
  &NJ_Tox_Site::str_site_id,
  &NJ_Tox_Site::str_pi_number,
  &NJ_Tox_Site::pi_name,
  &NJ_Tox_Site::street_address,
  &NJ_Tox_Site::home_owner_status,
  &NJ_Tox_Site::municipality,
  &NJ_Tox_Site::county,
  &NJ_Tox_Site::str_latitude,
  &NJ_Tox_Site::str_longitude,
  &NJ_Tox_Site::str_coords_count,
  &NJ_Tox_Site::coords_options,
  &NJ_Tox_Site::data_source
 },
 "/home/nlevisrael/docker/tox/KCSNJ/active-found_merged.csv"
 );


 return 0;
}




flags_(2)
 bool on_tribal_land:1;                // csv col 10
 bool federal_facility:1;              // csv col 18
 bool elemental_metal_included:1;      // csv col 35
 bool clean_air_act_chemical:1;        // csv col 39
 bool classified_as_metal:1;           // csv col 41
 bool carcinogen:1;                    // csv col 43
 bool pbt:1;                           // csv col 44
 bool pfas:1;                          // csv col 45
 bool form_r:1;                        // csv col 46
 bool form_a:1;                        // csv col 46
 bool units_pounds:1;                  // csv col 47
 bool units_grams:1;                   // csv col 47
 bool production_ratio_value:1;        // csv col 118
 bool activity_index_value:1;          // csv col 118
_flags

// //  Note: there appears to be a typo in the TIR guide;
 //    csv col 118 is listed as "189", but only 118
 //    makes sense in context

enum Flag_Values {
  N_A, on_tribal_land, federal_facility
};

template<Flag_Values fv>
void set_flag_()
{
 _set_flag_(fv);
}

void _set_flag_(Flag_Values fv)
{
 switch(fv)
 {
 case Flag_Values::on_tribal_land:
  flags.on_tribal_land = true; break;
 case Flag_Values::federal_facility:
  flags.federal_facility = true; break;


 }
}


void set_flag__on_tribal_land()  // csv col 10
{
 flags.on_tribal_land = true;
}

void set_flag__federal_facility()  // csv col 18
{
 flags.federal_facility = true;
}

void set_flag__elemental_metal_included()    // csv col 35
{
 flags.elemental_metal_included = true;
}

void set_flag__clean_air_act_chemical()   // csv col 39
{
 flags.on_tribal_land = true;
}

void set_flag__classified_as_metal()   // csv col 41
{
 flags.on_tribal_land = true;
}

void set_flag__carcinogen()     // csv col 43
{
 flags.on_tribal_land = true;
}

void set_flag__pbt()   // csv col 44
{
 flags.on_tribal_land = true;
}

void set_flag__pfas()     // csv col 45
{
 flags.on_tribal_land = true;
}

// //  note when flags are paired,
 //    this code chooses not to
 //    explicitly clear the one
 //    flag when the other is set

void set_flag__form_r()     // csv col 46
{
 flags.form_r = true;
}

void set_flag__form_a()     // csv col 46
{
 flags.form_a = true;
}

void set_flag__units_pounds()     // csv col 47
{
 flags.form_r = true;
}

void set_flag__units_grams()     // csv col 47
{
 flags.form_a = true;
}

void set_flag__production_ratio_value()     // csv col 118
{
 flags.form_r = true;
}

void set_flag__activity_index_value()     // csv col 118
{
 flags.form_a = true;
}




#endif // HIDE




// #ifdef HIDE
int pt_to_px(int i)
{
 return i * (4./3);
}

QPointF pt_to_px(QPointF p)
{
 return {pt_to_px(p.x()), pt_to_px(p.y())};
}

int px_to_pt(int i)
{
 return i * (3./4);
}


struct Doc_Page {
 u2 index;
 u2 number;
 u2 local;
 u2 email;
 QString title;
 QDate email_date;

 u2 date_rank;

 u2 adj;

 QVector<QPair<QString, QRectF>> annotations;
};

struct Email {
 u2 index;
 u2 start_page;
 u2 page_count;
 QString title;
};



void sort_with_emails(QVector<Doc_Page>& doc_pages,
  QVector<Email>& emails, QVector<Doc_Page*>& result)
{
 result.resize(doc_pages.size());

 int i = 0;
 for(Doc_Page& doc_page : doc_pages)
 {
  result[i++] = &doc_page;
 }

 std::sort(result.begin(), result.end(), [](Doc_Page* lhs, Doc_Page* rhs)
 {
  if(lhs->email_date == rhs->email_date)
    return lhs->number < rhs->number;
  return lhs->email_date < rhs->email_date;
 });




// Email* e;
// if(local == 1)
// {
//  emails.push_back({});
//  e = &emails.last();
//  e->index = emails.size() - 1;
//  e->page_count = 1;
//  e->start_page = page;
//  e->title = title;
// }
// else
// {
//  e = &emails.last();
//  ++e->page_count;
// }
// doc_page.email = e->index;


}


//?void map_arrows()

void json_to_doc_pages(QString json_file,
  QVector<Doc_Page>& doc_pages, QVector<int>& arrow_pages)
{

 QJsonDocument qjd;
 {
  QFile f(json_file);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja_pages = qjd.array();

 for(auto obj: qja_pages)
 {
  QJsonObject qjo = obj.toObject();

  u2 page = qjo.value("page").toInt();

  bool is_arrow = qjo.value("arrow").toBool();

  if(is_arrow)
  {
   arrow_pages.push_back(page);
   continue;
  }

  QString title = qjo.value("title").toString();

  u2 local = qjo.value("local").toInt();

  doc_pages.push_back({});
  Doc_Page& doc_page = doc_pages.last();
  doc_page.index = doc_pages.size() - 1;
  doc_page.number = page;
  doc_page.local = local;
  doc_page.title = title;
  doc_page.date_rank = 0;
  doc_page.adj = 0;

  doc_page.email = 0;




  auto& annotations = doc_page.annotations;

  QJsonArray qja_notes = qjo.value("notes").toArray();

  for(auto obj1: qja_notes)
  {
   QJsonObject obj_notes = obj1.toObject();
   QString text = obj_notes.value("text").toString();
   QRectF boundary;
   {
    QJsonArray qja2 = obj_notes.value("boundary").toArray();
    boundary.setX(qja2[0].toDouble());
    boundary.setY(qja2[1].toDouble());
    boundary.setWidth(qja2[2].toDouble());
    boundary.setHeight(qja2[3].toDouble());
   }
   annotations.push_back({text, boundary});
  }

   QRegularExpression rx("(20\\d\\d)[.,-](\\d+)[.,-](\\d+)");

   QRegularExpressionMatch rxm = rx.match(doc_page.title);

   QString date;
   if(rxm.hasMatch())
   {
    date = "%1.%2.%3"_qt.arg(rxm.captured(1))
      .arg(rxm.captured(2), 2, '0').arg(rxm.captured(3), 2, '0');
   }
   else
   {
    date = "2013.09.05";
   }

   doc_page.email_date = QDate::fromString(date, "yyyy.MM.dd");

//     if(!doc_page.email_date.isValid())
//     {
//      qDebug() << doc_page.number << ": invalid date: ";
//     }
//     else
//     {
//      qDebug() << doc_page.number << ": " << doc_page.email_date.toString();
//     }

 }
}




int main1(int argc, char *argv[])
{

 QString json_file = "/home/nlevisrael/sahana/S.pdf.json";
 QString sjson_file = "/home/nlevisrael/sahana/sorted/Sc.pdf.json";


 QVector<Doc_Page> doc_pages, sdoc_pages;

 QVector<int> arrows, sarrows;


 json_to_doc_pages(json_file, doc_pages, arrows);
 json_to_doc_pages(sjson_file, sdoc_pages, sarrows);

 QVector<Email> emails;
 QVector<Doc_Page*> sorted;// = doc_pages;

 sort_with_emails(sdoc_pages, emails, sorted);


 int i = 0;
 for(Doc_Page* sdoc_page : sorted)
 {
  if(i)
  {
   if(sdoc_page->local == 1)
     ++i;
  }
  ++i;
  sdoc_page->adj = i;

 }

 QString u_lines = KA::TextIO::load_file("/home/nlevisrael/sahana/t/u");
 QString us_lines = KA::TextIO::load_file("/home/nlevisrael/sahana/t/us");

 QStringList u_list = u_lines.split("\n");
 QStringList us_list = us_lines.split("\n");

 QMap<QString, QPair<int, int>> u_map;

 i = 0;
 for(QString s : u_list)
 {
  if(u_map.contains(s))
  {
   qDebug() << s;

  }
  ++i;
  u_map[s].first = i;
 }

 i = 0;
 for(QString s : us_list)
 {
  ++i;
  u_map[s].second = i;
 }

 QString ustr;
 QMapIterator<QString, QPair<int, int>> uit(u_map);

 while(uit.hasNext())
 {
  uit.next();
  ustr += "\n%1 -> %2 / %3"_qt.arg(uit.key()).arg(uit.value().first)
    .arg(uit.value().second);
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/t/um.txt", ustr);



 QMap<QString, Doc_Page*> pg_map;
 QMap<int, QPair<QString, Doc_Page*>> pg_pr_map;

 QMap<QString, Doc_Page*> spg_map;
 QMap<int, QPair<QString, Doc_Page*>> spg_pr_map;

 QMap<QString, Doc_Page*> _spg_map;
 QMap<int, QPair<QString, Doc_Page*>> _spg_pr_map;

 QMap<QString, Doc_Page*> _pg_map;
 QMap<int, QPair<QString, Doc_Page*>> _pg_pr_map;


 for(Doc_Page& doc_page : doc_pages)
 {
  QString key = doc_page.email_date.toString("ddd/MMM/d/yyyy") + ": "
    + doc_page.title + " (p. " + QString::number(doc_page.local) + ")";

  if(pg_map.contains(key))
    qDebug() << "??? " << key;

  if(pg_pr_map.contains(doc_page.number))
    qDebug() << "??? " << key;

  pg_pr_map[doc_page.number] = {key, &doc_page};

  pg_map[key] = &doc_page;
 }



 for(Doc_Page* sdoc_page : sorted)
 {
  QString key = sdoc_page->email_date.toString("ddd/MMM/d/yyyy") + ": "
    + sdoc_page->title + " (p. " + QString::number(sdoc_page->local) + ")";

  if(spg_map.contains(key))
    qDebug() << "??? " << key;

  if(spg_pr_map.contains(sdoc_page->number))
    qDebug() << "??? " << key;

  spg_map[key] = sdoc_page;
  spg_pr_map[sdoc_page->number] = {key, sdoc_page};
 }

 QString ss_pg_sum;

 for(Doc_Page& doc_page : doc_pages)
 {
  QString key = doc_page.email_date.toString("ddd/MMM/d/yyyy") + ": "
    + doc_page.title + " (p. " + QString::number(doc_page.local) + ")";

  if(spg_map.contains(key))
  {
   Doc_Page* doc_page = spg_map.take(key);
   ss_pg_sum += "%1: %2"_qt.arg(doc_page->adj).arg(doc_page->number);
   _spg_map[key] = doc_page;

   spg_pr_map.take(doc_page->number);
   _spg_pr_map[doc_page->number] = {key, doc_page};
  }
 }


 QString s_pg_sum;

 for(Doc_Page* sdoc_page : sorted)
 {
  QString key = sdoc_page->email_date.toString("ddd/MMM/d/yyyy") + ": "
    + sdoc_page->title + " (p. " + QString::number(sdoc_page->local) + ")";

  if(pg_map.contains(key))
  {
   Doc_Page* doc_page = pg_map.take(key);
   s_pg_sum += "%1: %2"_qt.arg(sdoc_page->adj).arg(doc_page->number);
   _pg_map[key] = doc_page;

   pg_pr_map.take(doc_page->number);

   _pg_pr_map[doc_page->number] = {key, doc_page};
  }
 }

 QString sall;
 for(int i = 1; i <= 426; ++i)
 {
  if(_spg_pr_map.contains(i))
  {
   auto pr = _spg_pr_map[i];

   Doc_Page* doc_page = _pg_map.value(pr.first);

   if(doc_page)
     sall += "\n%2 | %1 -> %3"_qt.arg(pr.first).arg(pr.second->number).arg(doc_page->number);

   else
     sall += "\n%2 | %1 -> %3"_qt.arg(pr.first).arg(pr.second->number).arg(" XXXXX ");
  }
  else if(spg_pr_map.contains(i))
  {
   auto pr = spg_pr_map[i];
   sall += "\n%2 ! %1 -> %3"_qt.arg(pr.first).arg(pr.second->number).arg(" ==== ");
  }
  else if(sarrows.contains(i))
  {
   sall += "\n%1 => arrow"_qt.arg(i);
  }
  else
  {
   sall += "\n%1 ?????"_qt.arg(i);
  }

 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/sall.txt", sall);


 QMap<int, QString> all_map;

 QString all;
 for(int i = 1; i <= 433; ++i)
 {
  if(_pg_pr_map.contains(i))
  {
   auto pr = _pg_pr_map[i];

   Doc_Page* sdoc_page = _spg_map.value(pr.first);

   if(sdoc_page)
   {
    all_map[sdoc_page->adj] = pr.first;
    all += "\n%2 => %3 | %1"_qt.arg(pr.first).arg(pr.second->number).arg(sdoc_page->adj);
   }

   else
     all += "\n%2 | %1 -> %3"_qt.arg(pr.first).arg(pr.second->number).arg(" xxxxx ");

  }
  else if(pg_pr_map.contains(i))
  {
   auto pr = pg_pr_map[i];
   all += "\n%2 (deleted: blank) %1"_qt.arg(pr.first).arg(pr.second->number);
  }
  else if(arrows.contains(i))
  {
   all += "\n%1 => arrow"_qt.arg(i);
  }
  else
  {
   all += "\n%1 (deleted: repeat)"_qt.arg(i);
  }
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/all.txt", all);

 QString all_map_str;
 QMapIterator<int, QString> all_it(all_map);
 while(all_it.hasNext())
 {
  all_it.next();
  all_map_str += "\n%1 -> %2"_qt.arg(all_it.key()).arg(all_it.value());
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/all_map.txt", all_map_str);

 QString aall_map_str;
 for(int i = 1; i <= 433; ++i)
 {
  if(all_map.contains(i))
    continue;

  if(sarrows.contains(i))
    aall_map_str += "\n%1 => arrow"_qt.arg(i);
  else
    aall_map_str += "\n%1 => ???"_qt.arg(i);
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/aall_map.txt", aall_map_str);



 KA::TextIO::save_file("/home/nlevisrael/sahana/spg.txt", s_pg_sum);

 QMapIterator<QString, Doc_Page*> pg_it(pg_map);

 QString pggg;
 while(pg_it.hasNext())
 {
  pg_it.next();
  pggg += "\n%1 -> %2"_qt.arg(pg_it.key()).arg(pg_it.value()->number);
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/pggg.txt", pggg);


 return 0;




 for(Doc_Page* sdoc_page : sorted)
 {
  QString key = sdoc_page->email_date.toString("ddd/MMM/d/yyyy") + "=" +  sdoc_page->title;
//  smmap[key].push_back(sdoc_page);

//  qDebug() << key << "   =>   " << sdoc_page->adj;
 }

// for(Doc_Page& sdoc_page : sdoc_pages)
// {
//  QString key = sdoc_page.email_date.toString("ddd/MMM/yyyy=")+ sdoc_page.title;
//  smmap[key].push_back(&sdoc_page);
// }


// QMapIterator<QString, QVector<Doc_Page*>> it(mmap_a);
// while(it.hasNext())
// {
//  it.next();
//  int c = 0;

//  for(Doc_Page* dp : it.value())
//  {
//   ++c;
//   if(dp->local == 1 && c > 1)
//     qDebug() << "C!: " << dp->title;
//  }
// }

// QMapIterator<QString, QVector<Doc_Page*>> ita(mmap_a);
// while(ita.hasNext())
// {
//  ita.next();
//  int c = 0;

//  for(Doc_Page* dp : ita.value())
//  {
//   ++c;
//   if(c > 1)
//     qDebug() << "C!!: " << dp->title;
//  }
// }


// int i = 0;

 QString sum;


 QMap<Doc_Page*, QVector<int>> p2p;
 QMap<int, Doc_Page*> rev_p2p;

// for(Doc_Page& doc_page : doc_pages)
// {
//  QString key = doc_page.email_date.toString("ddd/MMM/d/yyyy") + "=" + doc_page.title;
// }


 for(Doc_Page& doc_page : doc_pages)
 {
  if(doc_page.local == 1)
  {

   QString key = doc_page.email_date.toString("ddd/MMM/d/yyyy") + "=" + doc_page.title;

//   int pn = 999;

   QString pns;

//   for(Doc_Page* dp : smmap.value(key))
//   {
//      pns += " %1"_qt.arg(dp->adj);

//    p2p[&doc_page].push_back(dp->adj);
//    rev_p2p[dp->adj] = &doc_page;
//   }


//   qDebug() << "pn = " << pn;

//   ++i;

   QString add = QString("\n%1 -> %2 : %3 (%4)").arg(doc_page.number)
     .arg(pns)
     .arg(doc_page.title).arg(doc_page.email_date.toString("ddd - MMM d - yyyy"));

     sum += add;

  }
 }


 KA::TextIO::save_file("/home/nlevisrael/sahana/sum.txt", sum);


 QString p2p_sum;
 QMapIterator<Doc_Page*, QVector<int>> p2p_it(p2p);
 while(p2p_it.hasNext())
 {
  p2p_it.next();

  QString j;
  for(int i : p2p_it.value())
  {
   j += "%1/"_qt.arg(i);
  }

  p2p_sum += "\n%1 -> %2"_qt.arg(p2p_it.key()->number).arg(j);
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/p2p.txt", p2p_sum);

 QString rev_p2p_sum;
 QMapIterator<int, Doc_Page*> rev_p2p_it(rev_p2p);
 while(rev_p2p_it.hasNext())
 {
  rev_p2p_it.next();
  rev_p2p_sum += "\n%1 -> %2 (%3)"_qt.arg(rev_p2p_it.key())
    .arg(rev_p2p_it.value()->number).arg(rev_p2p_it.value()->email_date.toString());
 }
 KA::TextIO::save_file("/home/nlevisrael/sahana/rev_p2p.txt", rev_p2p_sum);

// QString arrows;

// for(int a = 1; a <= 433; ++a)
// {
//  if(!rev_p2p.contains(a))
//  {
//   arrows += "\n" + QString::number(a);
//  }
// }
// KA::TextIO::save_file("/home/nlevisrael/sahana/arrows.txt", arrows);



 QString ssum;
// i = 0;
 for(Doc_Page* sdoc_page : sorted)
 {
  if(sdoc_page->local == 1)
  {
  QString key = sdoc_page->email_date.toString("ddd/MMM/d/yyyy") + "=" + sdoc_page->title;

  int y = sdoc_page->email_date.year();


  ssum += "%1 (%2) -> %3\n"_qt.arg(sdoc_page->adj).arg(y).arg(key);
  }

#ifdef HIDE
  if(sdoc_page->local == 1)
  {
   QString key = sdoc_page->email_date.toString("ddd/MMM/yyyy=") + sdoc_page->title;
   int pn = 0;

   Doc_Page* dp = mmap.value(key).first();


   if(dp)
     pn = dp->number;



   ssum += QString("\n%1 -> %2 : %3 (%4)").arg(sdoc_page->number)
     .arg(pn)
     .arg(sdoc_page->title).arg(sdoc_page->email_date.toString("ddd - MMM - yyyy"));
  }
#endif
 }

 KA::TextIO::save_file("/home/nlevisrael/sahana/ssum.txt", ssum);


 return 0;

#ifdef HIDE
 QVector<Doc_Page*> sorted;// = doc_pages;
 sorted.resize(doc_pages.size());

 int i = 0;
 for(Doc_Page& doc_page : doc_pages)
 {
  sorted[i++] = &doc_page;
 }

 std::sort(sorted.begin(), sorted.end(), [](Doc_Page* lhs, Doc_Page* rhs)
 {
  if(lhs->email_date == rhs->email_date)
    return lhs->number < rhs->number;
  return lhs->email_date < rhs->email_date;
 });

 i = 0;

 QMap<Doc_Page*, int> test1;

 for(Doc_Page* doc_page : sorted)
 {
  ++i;
  test1[doc_page] = i;
 }

 for(Doc_Page& doc_page : doc_pages)
 {
  if(doc_page.local == 1)
  {
   sum += QString("\n%1 -> %2 : %3 (%4)").arg(doc_page.number)
     .arg(test1[&doc_page])
     .arg(doc_page.title).arg(doc_page.email_date.toString("ddd - MMM d - yyyy"));
  }
 }

 KA::TextIO::save_file("/home/nlevisrael/sahana/sum.txt", sum);

 return 0;

#endif
}

int main20(int argc, char *argv[])
{
 QString json_file = "/home/nlevisrael/sahana/sorted/Sc.pdf.json";

 QString bases_folder = "/home/nlevisrael/sahana/sorted/bases";
 QString pages_folder = "/home/nlevisrael/sahana/sorted/pages";

 QString template_folder = "/home/nlevisrael/sahana/sorted/templates";


 QJsonDocument qjd;
 {
  QFile f(json_file);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja_pages = qjd.array();

 QVector<Doc_Page> doc_pages;
 //QVector<Email> emails;

 for(auto obj: qja_pages)
 {
  QJsonObject qjo = obj.toObject();

  bool is_arrow = qjo.value("arrow").toBool();

  if(is_arrow)
    continue;

  u2 page = qjo.value("page").toInt();
  QString title = qjo.value("title").toString();

//  qDebug() << "title: " << title;

  u2 local = qjo.value("local").toInt();

  doc_pages.push_back({});
  Doc_Page& doc_page = doc_pages.last();
  doc_page.index = doc_pages.size() - 1;
  doc_page.number = page;
  doc_page.local = local;
  doc_page.title = title;
  doc_page.date_rank = 0;
  doc_page.adj = 0;

  doc_page.email = 0;

  auto& annotations = doc_page.annotations;

  QJsonArray qja_notes = qjo.value("notes").toArray();

  for(auto obj1: qja_notes)
  {
   QJsonObject obj_notes = obj1.toObject();
   QString text = obj_notes.value("text").toString();
   QRectF boundary;
   {
    QJsonArray qja2 = obj_notes.value("boundary").toArray();
    boundary.setX(qja2[0].toDouble());
    boundary.setY(qja2[1].toDouble());
    boundary.setWidth(qja2[2].toDouble());
    boundary.setHeight(qja2[3].toDouble());
   }
   annotations.push_back({text, boundary});
  }

 }

 QVector<Doc_Page*> sorted;// = doc_pages;
 sorted.resize(doc_pages.size());

 u2 i = 0;

 for(Doc_Page& doc_page : doc_pages)
 {
  sorted[i++] = &doc_page;

//  qDebug() << "doc page: " << doc_page.email;

  QRegularExpression rx("(20\\d\\d)[.,-](\\d+)[.,-](\\d+)");

  QRegularExpressionMatch rxm = rx.match(doc_page.title);

  QString date;
  if(rxm.hasMatch())
  {
   date = "%1.%2.%3"_qt.arg(rxm.captured(1))
     .arg(rxm.captured(2), 2, '0').arg(rxm.captured(3), 2, '0');
  }
  else
  {
   date = "2013.09.05";
  }

  doc_page.email_date = QDate::fromString(date, "yyyy.MM.dd");

//  qDebug() << doc_page.number << ": " << doc_page.email_date.toString();

 }

 std::sort(sorted.begin(), sorted.end(), [](Doc_Page* lhs, Doc_Page* rhs)
 {
  if(lhs->email_date == rhs->email_date)
    return lhs->number < rhs->number;
  return lhs->email_date < rhs->email_date;
 });

// // QString titles = "pdfunite \\\n";

 QString last_title;

#ifdef HIDE
 for(Doc_Page* ptr : sorted)
 {
  if(ptr->title == last_title)
    continue;

  last_title = ptr->title;

//  qDebug() << ptr->date_rank << " = " << ptr->number << " ("
//    << ptr->title << ")";

  titles += "\"" + ptr->title + "\" \\\n inter.pdf \\\n";
 }

 titles += " \\\n \\\n Ssx.pdf";
 KA::TextIO::save_file("/home/nlevisrael/sahana/sorted/run-u-s.sh", titles);

// for(Doc_Page& doc_page : doc_pages)
// {
//  qDebug() << doc_page.number << ": " << doc_page.email_date.toString()
//    << " (" << doc_page.date_rank << ")";
// }


// //  QString titles = "pdfunite \\\n";


 return 0;
#endif


// i = 0;
// for(Doc_Page* ptr : sorted)
// {
//  Email& e =
//  ptr->date_rank = i++;
// }

 #ifdef HIDE
 QMap<QString, QVector<Doc_Page*>> titles;

  for(Doc_Page* ptr : sorted)
  {
   QString tt = ptr->title;
   titles[tt].push_back(ptr);
  }

  QMapIterator<QString, QVector<Doc_Page*>> it(titles);

  while(it.hasNext())
  {
   it.next();

   qDebug() << "\n=============\n" << it.key();
   for(auto p : it.value())
   {
    qDebug() << " " << p->number;
   }


  }

 return 0;
#endif


 QVector<Doc_Page> sdoc_pages;

 QVector<Email> emails;

 u2 dr = 0;

 u2 pdf_num = 0;
 u2 local = 0;
 for(Doc_Page* doc_page : sorted)
 {
  ++pdf_num;
  if(doc_page->title == last_title)
    ++local;
  else
  {
   if(!last_title.isEmpty())
     ++pdf_num; // // for the arrow
   local = 1;
   ++dr;
  }

  sdoc_pages.push_back({});
  Doc_Page& sdoc_page = sdoc_pages.last();
  sdoc_page.index = sdoc_pages.size() - 1;
  sdoc_page.number = pdf_num;
  sdoc_page.local = local;
  sdoc_page.title = doc_page->title;
  sdoc_page.date_rank = doc_page->date_rank;
  sdoc_page.email_date = doc_page->email_date;
  sdoc_page.annotations = doc_page->annotations;
  sdoc_page.date_rank = dr;

  sdoc_page.adj = 0;

  Email* e;
  if(local == 1)
  {
   emails.push_back({});
   e = &emails.last();
   e->index = emails.size() - 1;
   e->page_count = 1;
   e->start_page = pdf_num;
   e->title = sdoc_page.title;
  }
  else
  {
   e = &emails.last();
   ++e->page_count;
  }
  sdoc_page.email = e->index;

//  titles += "\"" + doc_page->title + "\" \\\n inter.pdf \\\n";
  last_title = sdoc_page.title;
 }

// for(Doc_Page& sdoc_page : sdoc_pages)
// {
//  u2 page = sdoc_page.number;
//  qDebug() << page << ": " << sdoc_page.title << " (" << sdoc_page.local << ")";
// }



 u2 max_page = std::max_element(sdoc_pages.begin(), sdoc_pages.end(),
   [](const auto& lhs, const auto& rhs)
 {
  return lhs.number < rhs.number;
 }) -> number;

 QString url_base = "http://amyneustein.com/-prv/sahana/sorted/bases/";


 // //   create the index
// <td class='categories'>%3</td>

 static QString static_index_text = R"_(

  <tr class='one-line'>
   <td class='page-number'>%1</td>
   <td class='date' colspan='4'>%2</td>
    <!-- categories -->
     <td class='fc'>&nbsp;</td> %3 <td class='lc'>&nbsp;</td>
    <!-- end categories -->
   <td class='link' colspan='3'>
    <a href='%4%5'>%6</a></td>
  </tr>
   )_";

 QString index_text;

 QMap<u2, u2> categories_map;

 {
  u2 held_first_page = 0;
  u2 held_categories = 0;
  for(Doc_Page& sdoc_page : sdoc_pages)
  {
   if(sdoc_page.local == 1)
   {
    if(held_first_page)
    {
     categories_map[held_first_page] = held_categories;
     held_categories = 0;
    }
    held_first_page = sdoc_page.number;
   }
   for(auto pr : sdoc_page.annotations)
   {
    QString annotation = pr.first;
    if(annotation.contains("DARVO", Qt::CaseInsensitive))
      held_categories |= 1;
    if(annotation.contains("Coercive", Qt::CaseInsensitive))
      held_categories |= 2;
    if(annotation.contains("Gaslighting", Qt::CaseInsensitive))
      held_categories |= 4;
    if(annotation.contains("idiom", Qt::CaseInsensitive))
      held_categories |= 8;
   }
  }
 }

 for(Doc_Page& sdoc_page : sdoc_pages)
 {
  if(sdoc_page.local != 1)
    continue;

  QString href = "p%1.htm"_qt.arg(sdoc_page.number, 3, 10, QLatin1Char('0'));

  QString categories;

  u2 cs = categories_map.value(sdoc_page.number);

//  if(cs & 1)
//     categories += "DARVO, ";
//  if(cs & 2)
//     categories += "Coercive Control, ";
//  if(cs & 4)
//     categories += "Gaslighting, ";
//  if(cs & 8)
//     categories += "Excessive Use of Idioms, ";

//  if(categories.endsWith(", "))
//    categories.chop(2);

//  if(categories.isEmpty())
//    categories = "Subclinical";


  if(cs & 1)
    categories += "\n<td class='checked fc'><span>&#10004;</span></td>";
  else
    categories += "\n<td class='unchecked fc'><span>1</span></td>";

  if(cs & 2)
    categories += "\n<td class='checked'><span>&#10004;</span></td>";
  else
    categories += "\n<td class='unchecked'><span>2</span></td>";

  if(cs & 4)
    categories += "\n<td class='checked'><span>&#10004;</span></td>";
  else
    categories += "\n<td class='unchecked'><span>3</span></td>";

  if(cs & 8)
    categories += "\n<td class='checked'><span>&#10004;</span></td>";
  else
    categories += "\n<td class='unchecked'><span>4</span></td>";

  if(cs == 0)
    categories += "\n<td class='checked'><span>&#10004;</span></td>";
  else
    categories += "\n<td class='unchecked'><span>5</span></td>";


  index_text += static_index_text.arg(sdoc_page.number)
    .arg(sdoc_page.email_date.toString("ddd - MMM d - yyyy")
         .replace('-', "<span class='nd'>&ndash;</span>"))
   .arg(categories).arg(url_base).arg(href).arg(sdoc_page.title);


//  u2 page = sdoc_page.number;
//  qDebug() << page << ": " << sdoc_page.title << " (" << sdoc_page.local << ")";
 }

//? QString index_file = "%1/pages-index.htm"_qt.arg(bases_folder);

 QString spreadsheet_index_file = "%1/spreadsheet.htm"_qt.arg(bases_folder);
 QString page_index_file = "%1/pages-index.htm"_qt.arg(bases_folder);

 // Sahana-Email-Compilation_annotated
 // Start page for email compilation document
 // Date of email
 // Analytic Categories
 // Title of Emails

 QString page_index_template = "%1/pages-index.htm"_qt.arg(template_folder);
 QString spreadsheet_index_template = "%1/spreadsheet.htm"_qt.arg(template_folder);


 QString page_index_html_text = KA::TextIO::load_file(page_index_template);
 QString spreadsheet_index_html_text = KA::TextIO::load_file(spreadsheet_index_template);

 spreadsheet_index_html_text.replace("%index-text%", index_text);
 page_index_html_text.replace("%index-text%", index_text);

 KA::TextIO::save_file(spreadsheet_index_file, spreadsheet_index_html_text);
 KA::TextIO::save_file(page_index_file, page_index_html_text);



 for(Doc_Page& sdoc_page : sdoc_pages)
 {
  u2 page = sdoc_page.number;

//  if(page < 48)
//    continue;

//  if(page == 48)
//    qDebug() << page;

  Email& email = emails[sdoc_page.email];


  QString svg_file = "%1/p%2.svg"_qt.arg(pages_folder).arg(page, 3, 10, QLatin1Char('0'));

  QSvgRenderer svr;
  svr.load(svg_file);

  QRectF view_box = svr.viewBoxF();

  r8 view_box_y_offset = 150;
  r8 view_box_extra_height = 0;

  r8 view_box_padding = 40;


  QString svg_view_box_string = "viewBox=\"%1 %2 %3 %4\""_qt
    .arg(view_box.x()).arg(view_box.y() - view_box_y_offset).arg(view_box.width())
    .arg(view_box.height() + view_box_y_offset);

  QString svg_wh_string = "width=\"%1pt\" height=\"%2pt\""_qt
    .arg(view_box.width()).arg(view_box.height() + view_box_y_offset + view_box_extra_height);

  QString main_image_wh = "width=\"%1\" height=\"%2\""_qt
    .arg(view_box.width()).arg(view_box.height());

  QString rbkg_inside_wh = "width=\"%1\" height=\"%2\""_qt
    .arg(view_box.width()).arg(view_box.height());

  QString rbkg_outside_y = "-%1"_qt.arg(view_box_y_offset);

 // %main-image-wh%

  QString base_file = "%1/p%2.svg"_qt.arg(bases_folder).arg(page, 3, 10, QLatin1Char('0'));
  QString html_file = "%1/p%2.htm"_qt.arg(bases_folder).arg(page, 3, 10, QLatin1Char('0'));

  QString html_template = "%1/overlay.htm"_qt.arg(template_folder);
  QString html_text = KA::TextIO::load_file(html_template);

  html_text.replace("%email-date%", sdoc_page.email_date.toString());
  html_text.replace("%email-date-rank%", QString::number(sdoc_page.date_rank));

  html_text.replace("%thread-number%", QString::number(email.index + 1));
  html_text.replace("%thread-number-max%", QString::number(emails.size()));

  html_text.replace("%wrw%", QString::number(view_box.width() + view_box_padding));
  html_text.replace("%wrh%", QString::number(view_box.height() + view_box_padding + view_box_y_offset));

  html_text.replace("%title%", email.title);
  html_text.replace("%local%", QString::number(sdoc_page.local));
  html_text.replace("%page%", "%1"_qt.arg(page, 3, 10, QLatin1Char('0')));
  html_text.replace("%dpage%", QString::number(page));

  html_text.replace("%local-max%", QString::number(email.page_count));
  html_text.replace("%max-page%", QString::number(max_page));

  html_text.replace("%iframe-width%", "%1pt"_qt.arg(view_box.width()));
  html_text.replace("%iframe-height%", "%1pt"_qt.arg(view_box.height() + view_box_y_offset));

  if(page == 1)
  {
   html_text.replace("%uu-active%", "inactive");
   html_text.replace("%uu-onclick%", "");
  }
  else
  {
   html_text.replace("%uu-active%", "active");
   html_text.replace("%uu-onclick%", "location.href='%1p001.htm'"_qt.arg(url_base));
  }

  if(page == max_page)
  {
   html_text.replace("%dd-active%", "inactive");
   html_text.replace("%dd-onclick%", "");
  }
  else
  {
   html_text.replace("%dd-active%", "active");
   html_text.replace("%dd-onclick%", "location.href='%1p%2.htm'"_qt.arg(url_base).arg(max_page, 3, 10, QLatin1Char('0')));
  }


  Email* prior_email = sdoc_page.email? &emails[sdoc_page.email - 1] : (Email*) nullptr;
  Email* next_email = sdoc_page.email < emails.size() - 1? &emails[sdoc_page.email + 1] : (Email*) nullptr;


  Doc_Page* prior_page = sdoc_page.index? &sdoc_pages[sdoc_page.index - 1] : (Doc_Page*) nullptr;
  Doc_Page* next_page = sdoc_page.index < sdoc_pages.size() - 1? &sdoc_pages[sdoc_page.index + 1] : (Doc_Page*) nullptr;

  if(next_page && next_page->email == sdoc_page.email)
  {
   html_text.replace("%ldown%", "location.href='%1p%2.htm'"_qt
                     .arg(url_base).arg(next_page->number, 3, 10, QLatin1Char('0')));
   html_text.replace("%ldown-active%", "active");
  }
  else
  {
   html_text.replace("%ldown%", "");
   html_text.replace("%ldown-active%", "inactive");
  }

  if(prior_page && prior_page->email == sdoc_page.email)
  {
   html_text.replace("%lup%", "location.href='%1p%2.htm'"_qt.arg(url_base)
     .arg(prior_page->number, 3, 10, QLatin1Char('0')));
   html_text.replace("%lup-active%", "active");
  }
  else
  {
   html_text.replace("%lup%", "");
   html_text.replace("%lup-active%", "inactive");
  }

  if(next_email)
  {
   html_text.replace("%edown%", "location.href='%1p%2.htm'"_qt
     .arg(url_base).arg(next_email->start_page, 3, 10, QLatin1Char('0')));
   html_text.replace("%edown-active%", "active");
  }
  else
  {
   html_text.replace("%edown%", "");
   html_text.replace("%edown-active%", "inactive");
  }


  if(prior_email)
  {
   html_text.replace("%eup%", "location.href='%1p%2.htm'"_qt
     .arg(url_base).arg(prior_email->start_page, 3, 10, QLatin1Char('0')));
   html_text.replace("%eup-active%", "active");
  }
  else
  {
   html_text.replace("%eup%", "");
   html_text.replace("%eup-active%", "inactive");
  }

//  if(prior_page)
//    html_text.replace("%nup%", "location.href='p%1.htm'"_qt.arg(prior_page->number, 3, 10, QLatin1Char('0')));
//  else
//    html_text.replace("%nup%", "");


  QString base_template = "%1/overlay.svg"_qt.arg(template_folder);
  QString base_text = KA::TextIO::load_file(base_template);
  base_text.replace("%page%", "%1"_qt.arg(page, 3, 10, QLatin1Char('0')));

  base_text.replace("%svg-wh%", svg_wh_string);
  base_text.replace("%svg-vb%", svg_view_box_string);

  base_text.replace("%rbkg-outside-y%", rbkg_outside_y);
  base_text.replace("%main-image-wh%", main_image_wh);
  base_text.replace("%rbkg-inside-wh%", rbkg_inside_wh);

  static QString static_marks_text = R"_(

  <!-- note %1 -->

  <g class='mark-g' id='mark-g-%1' onmouseover='show_popup_text_by_id(%1, event)'
    onmouseout='check_hide_popup_text_by_id(%1, event)'>

  <rect id='mark-r-%1'
    class='area-rect' x='%2pt' y='%3pt' width='%4pt' height='%5pt'
    />

  </g>

  <!-- end note %1 -->

  )_";

  static QString static_popup_text = R"_(

   <!-- for note %1 -->

  <g id='popup-%1' class='text-wrapper' transform='translate(%2, %3)'  data-xcoord='%2' >
    <rect width='%4pt' height='%5pt' data-ycoord='%3'  data-index='%1'
      x='%6pt' y='%7' class='foreign-object-bkg' id='fo-rect-%1'/>
  )_";

  static QString static_fo_text = R"_(
    <foreignObject width="%2pt" height="%3pt" x='0' y='0' id='fo-%1'
       requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility">
     <p xmlns="http://www.w3.org/1999/xhtml"
       style='background:pink; font-size:11pt'>
       %4
     </p>
   </foreignObject>
  </g>

   <!-- end for note %1 -->

  )_";


  static QString height_test = R"_(
  <div style='width:200px' id='test-d-%1'>
  <p class='for-height-test' font-size:11pt' id='test-p-%1'>
  %2
  </p>
  </div>

  )_";


  QString html_test = height_test.arg(0).arg("X");


  static QString static_trapezoids_text = R"_(
    <!-- for note %1 -->

    <!--  l: %2  bl: %3  br: %4  r: %5  tx: %6  tr: %7  tl: %8  -->
    <polygon id="trapz-%1" points="%2 %3 %4 %5 %6 %7 %8"
       class='trapz' onmouseout='leave_trapz(%1, event)' data-repl='%9' />

    <!-- end for note %1 -->
  )_";

  auto& vec = sdoc_page.annotations;

  QString marks_text;
  QString trapezoids_text;

  QString popup_text;

  u1 i = 0;
  for(auto& pr : vec)
  {
   ++i;

   QRectF rf = pr.second;

   QTransform qtr;
   qtr.scale(px_to_pt(view_box.width()), px_to_pt(view_box.height()));

   QRectF qr = qtr.mapRect(rf);

   r8 x = qr.x();
   r8 y = qr.y();
   r8 w = qr.width();
   r8 h = qr.height();

   static r8 trapz_x_offset = 50;
   static r8 trapz_y_offset = 12;

   static r8 trapz_x_width = 200;
   static r8 trapz_y_height = 90;

   static u2 popup_width = 200;
   static u2 popup_height = 90;


   r8 trapz_x = x + trapz_x_offset;
   r8 trapz_y = y + trapz_y_offset;

   r8 trapz_y_extra = 3;

   QString text = pr.first;


   marks_text += static_marks_text.arg(i).arg(x).arg(y)
     .arg(w).arg(h);


   static r8 rect_fo_pushout = 5;

   r8 rect_fo_x = -rect_fo_pushout;
   r8 rect_fo_y = -rect_fo_pushout;
   r8 rect_fo_width = popup_width + rect_fo_pushout + rect_fo_pushout;
   r8 rect_fo_height = popup_height + rect_fo_pushout + rect_fo_pushout;

   popup_text += static_popup_text.arg(i)
     .arg(pt_to_px( trapz_x )).arg(pt_to_px( trapz_y - trapz_y_height ))
     .arg(rect_fo_width).arg(rect_fo_height)
     .arg(rect_fo_x).arg(rect_fo_y);

   popup_text += static_fo_text.arg(i)
     .arg(popup_width).arg(popup_height).arg(text);


   html_test += height_test.arg(i).arg(text);

   QPointF trapezoid_l, trapezoid_bl, trapezoid_br,
     trapezoid_r, trapezoid_tr, trapezoid_tl;

   QString trapezoid_ls, trapezoid_bls, trapezoid_brs,
     trapezoid_rs, trapezoid_trs, trapezoid_tls;

   auto point_to_string = [](QPointF p, QString& s)
   {
    s = "%1,%2"_qt.arg(p.x()).arg(p.y());
   };

   auto points_to_strings = [&]()
   {
    point_to_string(trapezoid_l, trapezoid_ls);
    point_to_string(trapezoid_bl, trapezoid_bls);
    point_to_string(trapezoid_br, trapezoid_brs);
    point_to_string(trapezoid_r, trapezoid_rs);
    point_to_string(trapezoid_tr, trapezoid_trs);
    point_to_string(trapezoid_tl, trapezoid_tls);
   };

   static r8 trapezoid_pushout = 0;

   trapezoid_l = pt_to_px( qr.topLeft() );
   trapezoid_bl = pt_to_px( qr.bottomLeft() );
   trapezoid_br = pt_to_px( qr.bottomRight() );
   trapezoid_r = pt_to_px( qr.topRight() );
   trapezoid_tr = pt_to_px( {trapz_x + trapz_x_width + trapezoid_pushout,
     trapz_y - trapz_y_height - trapezoid_pushout + trapz_y_extra} );
   trapezoid_tl = pt_to_px( {trapz_x - trapezoid_pushout,
     trapz_y - trapz_y_height - trapezoid_pushout + trapz_y_extra } );

   points_to_strings();

   QString trapz_extra;
   QString trapz_points;

   if(w < popup_width)
   {
    trapz_points = "%1 %2 %3 %4 %5,Yx %6,Y1 %7,Y2"_qt
      .arg(trapezoid_ls).arg(trapezoid_bls).arg(trapezoid_brs)
      .arg(trapezoid_rs).arg(trapezoid_tr.x())
      .arg(trapezoid_tr.x()).arg(trapezoid_tl.x());

    trapz_extra = "%1,%2"_qt.arg(trapezoid_tr.x() + trapezoid_pushout)
      .arg(trapezoid_tr.y() + pt_to_px(popup_height) + trapezoid_pushout);
   }
   else
    trapz_points = "%1 %2 %3 %4 %5,Y1 %6,Y2"_qt
      .arg(trapezoid_ls).arg(trapezoid_bls).arg(trapezoid_brs)
      .arg(trapezoid_rs).arg(trapezoid_tr.x()).arg(trapezoid_tl.x());


   trapezoids_text += static_trapezoids_text.arg(i)
     .arg(trapezoid_ls).arg(trapezoid_bls).arg(trapezoid_brs)
     .arg(trapezoid_rs).arg(trapz_extra).arg(trapezoid_trs)
     .arg(trapezoid_tls).arg(trapz_points);





   //
  }

  base_text.replace("%MARKS%", marks_text);

  base_text.replace("%TEXTS%", popup_text);

  base_text.replace("%TRAPEZOIDS%", trapezoids_text);

  KA::TextIO::save_file(base_file, base_text);


  html_text.replace("%test-count%", QString::number(i));

  html_text.replace("%P%", html_test);
  KA::TextIO::save_file(html_file, html_text);

 }



// // titles += " \\\n \\\n Ss.pdf";
// // KA::TextIO::save_file("/home/nlevisrael/sahana/sorted/run-u-s.sh", titles);

 return 0;

}

#ifdef HIDE
int main21(int argc, char *argv[])
{
 QString bases_folder = "/home/nlevisrael/sahana/bases";
 QString pages_folder = "/home/nlevisrael/sahana/pages";

 QSet<int> arrow_pages {
  3, 5, 7, 9, 11, 13, 15, 17, 20, 25, 27, 29, 34, 37, 40, 42, 44, 46,
  48, 51, 54, 56, 59, 61, 66, 69, 74, 77, 80, 84, 87, 89, 91, 94, 96,
  98, 101, 103, 109, 111, 113, 116, 118, 120, 122, 124, 127, 129, 132,
  134, 136, 139, 141, 147, 150, 152, 154, 160, 162, 164, 172, 175, 178,
  182, 197, 200, 204, 208, 210, 213, 216, 219, 221, 223, 225, 227, 229,
  231, 233, 235, 237, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258,
  260, 264, 266, 268, 271, 274, 277, 280, 282, 284, 287, 289, 292, 294,
  296, 298, 301, 304, 306, 309, 313, 315, 317, 319, 321, 326, 329, 336,
  338, 344, 347, 351, 354, 358, 360, 364, 366, 369, 372, 375, 378, 381,
  385, 393, 395, 401, 412, 414, 416, 418, 421, 424, 426, 429, 432
 };


 QString json_file = "/home/nlevisrael/sahana/S.pdf.json";
 QString template_folder = "/home/nlevisrael/sahana/templates";

 QJsonDocument qjd;
 {
  QFile f(json_file);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja_pages = qjd.array();

// QMap<u2, QSizeF> page_sizes;
// QMap<u2, QPair<QString, u2>> page_titles;
// QMap<u2, QVector<QPair<QString, QRectF>>> annotations;
// QMap<u2, QVector<u2>> info;
// // 0 = start of prev email  1 = local  2 = start of next email

// u2 last_page = 0;
// u2 last_start_page = 0;

 QVector<Doc_Page> doc_pages;
 QVector<Email> emails;

 for(auto obj: qja_pages)
 {
  QJsonObject qjo = obj.toObject();

  bool is_arrow = qjo.value("arrow").toBool();

  if(is_arrow)
    continue;

  u2 page = qjo.value("page").toInt();
  QString title = qjo.value("title").toString();
  u2 local = qjo.value("local").toInt();
//  page_titles[page] = {title, local};
//  info[page].resize(3);

  doc_pages.push_back({});
  Doc_Page& doc_page = doc_pages.last();
  doc_page.index = doc_pages.size() - 1;
  doc_page.number = page;
  doc_page.local = local;

  Email* e;
  if(local == 1)
  {
   emails.push_back({});
   e = &emails.last();
   e->index = emails.size() - 1;
   e->page_count = 1;
   e->start_page = page;
   e->title = title;
  }
  else
  {
   e = &emails.last();
   ++e->page_count;
  }
  doc_page.email = e->index;

  auto& annotations = doc_page.annotations;

//  if(last_page)
//  {
//   info[page][1] = local;
//   if(local == 1)
//   {
//    info[last_page][2] = page;
//   }
//   if(last_start_page)
//   {
//    info[last_page][1] = last_start_page;
//   }

//  }

//  last_page = page;

//  QSizeF page_size;
//  {
//   QJsonArray qja1 = qjo.value("page-size").toArray();
//   page_size.setWidth(qja1[0].toDouble());
//   page_size.setHeight(qja1[1].toDouble());
//  }
//  page_sizes[page] = page_size;

  QJsonArray qja_notes = qjo.value("notes").toArray();

  for(auto obj1: qja_notes)
  {
   QJsonObject obj_notes = obj1.toObject();
   QString text = obj_notes.value("text").toString();
   QRectF boundary;
   {
    QJsonArray qja2 = obj_notes.value("boundary").toArray();
    boundary.setX(qja2[0].toDouble());
    boundary.setY(qja2[1].toDouble());
    boundary.setWidth(qja2[2].toDouble());
    boundary.setHeight(qja2[3].toDouble());
   }
   annotations.push_back({text, boundary});
  }
 }

// QMapIterator<u2, QPair<QString, u2>> it(page_titles);

//// while(it.hasNext())
//// {
////  it.next();

////  u2 page = it.key();



//// }

//// it.toFront();

// last_page = 0;

 u2 max_page = std::max_element(doc_pages.begin(), doc_pages.end(),
   [](const auto& lhs, const auto& rhs)
 {
  return lhs.number < rhs.number;
 }) -> number;


 for(Doc_Page& doc_page : doc_pages)
 {
  u2 page = doc_page.number;

  Email& email = emails[doc_page.email];


  QString svg_file = "%1/p%2.svg"_qt.arg(pages_folder).arg(page, 3, 10, QLatin1Char('0'));

  QSvgRenderer svr;
  svr.load(svg_file);

  QRectF view_box = svr.viewBoxF();

  r8 view_box_y_offset = 45;

  QString svg_view_box_string = "viewBox=\"%1 %2 %3 %4\""_qt
    .arg(view_box.x()).arg(view_box.y() - view_box_y_offset).arg(view_box.width()).arg(view_box.height() + view_box_y_offset);

  QString svg_wh_string = "width=\"%1pt\" height=\"%2pt\""_qt
    .arg(view_box.width()).arg(view_box.height() + view_box_y_offset);

  QString main_image_wh = "width=\"%1\" height=\"%2\""_qt
    .arg(view_box.width()).arg(view_box.height());

  QString rbkg_inside_wh = "width=\"%1\" height=\"%2\""_qt
    .arg(view_box.width()).arg(view_box.height());

  QString rbkg_outside_y = "-%1"_qt.arg(view_box_y_offset);

 // %main-image-wh%

  QString base_file = "%1/p%2.svg"_qt.arg(bases_folder).arg(page, 3, 10, QLatin1Char('0'));
  QString html_file = "%1/p%2.htm"_qt.arg(bases_folder).arg(page, 3, 10, QLatin1Char('0'));

  QString html_template = "%1/overlay.htm"_qt.arg(template_folder);
  QString html_text = KA::TextIO::load_file(html_template);



  html_text.replace("%title%", email.title);
  html_text.replace("%local%", QString::number(doc_page.local));
  html_text.replace("%page%", "%1"_qt.arg(page, 3, 10, QLatin1Char('0')));
  html_text.replace("%dpage%", QString::number(page));

  html_text.replace("%local-max%", QString::number(email.page_count));
  html_text.replace("%max-page%", QString::number(max_page));

  html_text.replace("%iframe-width%", "%1pt"_qt.arg(view_box.width()));
  html_text.replace("%iframe-height%", "%1pt"_qt.arg(view_box.height()));

  html_text.replace("%wrw%", QString::number(view_box.width()));
  html_text.replace("%wrh%", QString::number(view_box.height()));

  Email* prior_email = doc_page.email? &emails[doc_page.email - 1] : (Email*) nullptr;
  Email* next_email = doc_page.email < emails.size() - 1? &emails[doc_page.email + 1] : (Email*) nullptr;

  Doc_Page* prior_page = doc_page.index? &doc_pages[doc_page.index - 1] : (Doc_Page*) nullptr;
  Doc_Page* next_page = doc_page.index < doc_pages.size() - 1? &doc_pages[doc_page.index + 1] : (Doc_Page*) nullptr;

  if(next_page && next_page->email == doc_page.email)
  {
   html_text.replace("%ldown%", "location.href='p%1.htm'"_qt.arg(next_page->number, 3, 10, QLatin1Char('0')));
   html_text.replace("%ldown-active%", "active");
  }
  else
  {
   html_text.replace("%ldown%", "");
   html_text.replace("%ldown-active%", "inactive");
  }

  if(prior_page && prior_page->email == doc_page.email)
  {
   html_text.replace("%lup%", "location.href='p%1.htm'"_qt.arg(prior_page->number, 3, 10, QLatin1Char('0')));
   html_text.replace("%lup-active%", "active");
  }
  else
  {
   html_text.replace("%lup%", "");
   html_text.replace("%lup-active%", "inactive");
  }

  if(next_email)
  {
   html_text.replace("%edown%", "location.href='p%1.htm'"_qt.arg(next_email->start_page, 3, 10, QLatin1Char('0')));
   html_text.replace("%edown-active%", "active");
  }
  else
  {
   html_text.replace("%edown%", "");
   html_text.replace("%edown-active%", "inactive");
  }


  if(prior_email)
  {
   html_text.replace("%eup%", "location.href='p%1.htm'"_qt.arg(prior_email->start_page, 3, 10, QLatin1Char('0')));
   html_text.replace("%eup-active%", "active");
  }
  else
  {
   html_text.replace("%eup%", "");
   html_text.replace("%eup-active%", "inactive");
  }

//  if(prior_page)
//    html_text.replace("%nup%", "location.href='p%1.htm'"_qt.arg(prior_page->number, 3, 10, QLatin1Char('0')));
//  else
//    html_text.replace("%nup%", "");


  QString base_template = "%1/overlay.svg"_qt.arg(template_folder);
  QString base_text = KA::TextIO::load_file(base_template);
  base_text.replace("%page%", "%1"_qt.arg(page, 3, 10, QLatin1Char('0')));

  base_text.replace("%svg-wh%", svg_wh_string);
  base_text.replace("%svg-vb%", svg_view_box_string);

  base_text.replace("%rbkg-outside-y%", rbkg_outside_y);
  base_text.replace("%main-image-wh%", main_image_wh);
  base_text.replace("%rbkg-inside-wh%", rbkg_inside_wh);

  static QString static_marks_text = R"_(

  <!-- note %1 -->

  <g class='mark-g' id='mark-g-%1' onmouseover='show_popup_text_by_id(%1, event)'
    onmouseout='check_hide_popup_text_by_id(%1, event)'>

  <rect id='mark-r-%1'
    class='area-rect' x='%2pt' y='%3pt' width='%4pt' height='%5pt'
    />

  </g>

  <!-- end note %1 -->

  )_";

  static QString static_popup_text = R"_(

   <!-- for note %1 -->

  <g id='popup-%1' class='text-wrapper' transform='translate(%2, %3)'  data-xcoord='%2' >
    <rect width='%4pt' height='%5pt' data-ycoord='%3'  data-index='%1'
      x='%6pt' y='%7' class='foreign-object-bkg' id='fo-rect-%1'/>
  )_";

  static QString static_fo_text = R"_(
    <foreignObject width="%2pt" height="%3pt" x='0' y='0' id='fo-%1'
       requiredFeatures="http://www.w3.org/TR/SVG11/feature#Extensibility">
     <p xmlns="http://www.w3.org/1999/xhtml"
       style='background:pink; font-size:11pt'>
       %4
     </p>
   </foreignObject>
  </g>

   <!-- end for note %1 -->

  )_";


  static QString height_test = R"_(
  <div style='width:200px' id='test-d-%1'>
  <p class='for-height-test' font-size:11pt' id='test-p-%1'>
  %2
  </p>
  </div>

  )_";


  QString html_test = height_test.arg(0).arg("X");


  static QString static_trapezoids_text = R"_(
    <!-- for note %1 -->

    <!--  l: %2  bl: %3  br: %4  r: %5  tx: %6  tr: %7  tl: %8  -->
    <polygon id="trapz-%1" points="%2 %3 %4 %5 %6 %7 %8"
       class='trapz' onmouseout='leave_trapz(%1, event)' data-repl='%9' />

    <!-- end for note %1 -->
  )_";

  auto& vec = doc_page.annotations;

  QString marks_text;
  QString trapezoids_text;

  QString popup_text;

  u1 i = 0;
  for(auto& pr : vec)
  {
   ++i;

   QRectF rf = pr.second;

   QTransform qtr;
   qtr.scale(px_to_pt(view_box.width()), px_to_pt(view_box.height()));

   QRectF qr = qtr.mapRect(rf);

   r8 x = qr.x();
   r8 y = qr.y();
   r8 w = qr.width();
   r8 h = qr.height();

   static r8 trapz_x_offset = 50;
   static r8 trapz_y_offset = -10;

   static r8 trapz_x_width = 200;
   static r8 trapz_y_height = 90;

   static u2 popup_width = 200;
   static u2 popup_height = 90;


   r8 trapz_x = x + trapz_x_offset;
   r8 trapz_y = y + trapz_y_offset;

   QString text = pr.first;


   marks_text += static_marks_text.arg(i).arg(x).arg(y)
     .arg(w).arg(h);


   static r8 rect_fo_pushout = 5;

   r8 rect_fo_x = -rect_fo_pushout;
   r8 rect_fo_y = -rect_fo_pushout;
   r8 rect_fo_width = popup_width + rect_fo_pushout + rect_fo_pushout;
   r8 rect_fo_height = popup_height + rect_fo_pushout + rect_fo_pushout;

   popup_text += static_popup_text.arg(i)
     .arg(pt_to_px( trapz_x )).arg(pt_to_px( trapz_y - trapz_y_height ))
     .arg(rect_fo_width).arg(rect_fo_height)
     .arg(rect_fo_x).arg(rect_fo_y);

   popup_text += static_fo_text.arg(i)
     .arg(popup_width).arg(popup_height).arg(text);


   html_test += height_test.arg(i).arg(text);

   QPointF trapezoid_l, trapezoid_bl, trapezoid_br,
     trapezoid_r, trapezoid_tr, trapezoid_tl;

   QString trapezoid_ls, trapezoid_bls, trapezoid_brs,
     trapezoid_rs, trapezoid_trs, trapezoid_tls;

   auto point_to_string = [](QPointF p, QString& s)
   {
    s = "%1,%2"_qt.arg(p.x()).arg(p.y());
   };

   auto points_to_strings = [&]()
   {
    point_to_string(trapezoid_l, trapezoid_ls);
    point_to_string(trapezoid_bl, trapezoid_bls);
    point_to_string(trapezoid_br, trapezoid_brs);
    point_to_string(trapezoid_r, trapezoid_rs);
    point_to_string(trapezoid_tr, trapezoid_trs);
    point_to_string(trapezoid_tl, trapezoid_tls);
   };

   static r8 trapezoid_pushout = 0;

   trapezoid_l = pt_to_px( qr.topLeft() );
   trapezoid_bl = pt_to_px( qr.bottomLeft() );
   trapezoid_br = pt_to_px( qr.bottomRight() );
   trapezoid_r = pt_to_px( qr.topRight() );
   trapezoid_tr = pt_to_px( {trapz_x + trapz_x_width + trapezoid_pushout,
     trapz_y - trapz_y_height - trapezoid_pushout } );
   trapezoid_tl = pt_to_px( {trapz_x - trapezoid_pushout,
     trapz_y - trapz_y_height - trapezoid_pushout } );

   points_to_strings();

   QString trapz_extra;
   QString trapz_points;

   if(w < popup_width)
   {
    trapz_points = "%1 %2 %3 %4 %5,Yx %6,Y1 %7,Y2"_qt
      .arg(trapezoid_ls).arg(trapezoid_bls).arg(trapezoid_brs)
      .arg(trapezoid_rs).arg(trapezoid_tr.x())
      .arg(trapezoid_tr.x()).arg(trapezoid_tl.x());

    trapz_extra = "%1,%2"_qt.arg(trapezoid_tr.x() + trapezoid_pushout)
      .arg(trapezoid_tr.y() + pt_to_px(popup_height) + trapezoid_pushout);
   }
   else
    trapz_points = "%1 %2 %3 %4 %5,Y1 %6,Y2"_qt
      .arg(trapezoid_ls).arg(trapezoid_bls).arg(trapezoid_brs)
      .arg(trapezoid_rs).arg(trapezoid_tr.x()).arg(trapezoid_tl.x());


   trapezoids_text += static_trapezoids_text.arg(i)
     .arg(trapezoid_ls).arg(trapezoid_bls).arg(trapezoid_brs)
     .arg(trapezoid_rs).arg(trapz_extra).arg(trapezoid_trs)
     .arg(trapezoid_tls).arg(trapz_points);





   //
  }

  base_text.replace("%MARKS%", marks_text);

  base_text.replace("%TEXTS%", popup_text);

  base_text.replace("%TRAPEZOIDS%", trapezoids_text);

  KA::TextIO::save_file(base_file, base_text);


  html_text.replace("%test-count%", QString::number(i));

  html_text.replace("%P%", html_test);
  KA::TextIO::save_file(html_file, html_text);

 }



 return 0;

}


//#endif //def HIDE

#endif


