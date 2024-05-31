
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


int main(int argc, char *argv[])
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

 QJsonDocument qjd;
 {
  QFile f(json_file);
  f.open(QIODevice::ReadOnly);
  QByteArray qba = f.readAll();
  qjd = QJsonDocument::fromJson(qba);
 }

 QJsonArray qja_pages = qjd.array();

 QMap<u2, QSizeF> page_sizes;
 QMap<u2, QString> page_titles;

 QMap<u2, QVector<QPair<QString, QRectF>>> annotations;

 for(auto obj: qja_pages)
 {
  QJsonObject qjo = obj.toObject();

  bool is_arrow = qjo.value("arrow").toBool();

  if(is_arrow)
    continue;

  u2 page = qjo.value("page").toInt();
  QString title = qjo.value("title").toString();
  page_titles[page] = title;

  QSizeF page_size;
  {
   QJsonArray qja1 = qjo.value("page-size").toArray();
   page_size.setWidth(qja1[0].toDouble());
   page_size.setHeight(qja1[1].toDouble());
  }
  page_sizes[page] = page_size;

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
   annotations[page].push_back({text, boundary});
  }
 }

 QMapIterator<u2, QString> it(page_titles);
 while(it.hasNext())
 {
  it.next();

  u2 page = it.key();

  QString svg_file = "%1/p%2.svg"_qt.arg(pages_folder).arg(page, 3, 10, QLatin1Char('0'));

  qDebug() << svg_file;


 }

 return 0;

}



int main23(int argc, char *argv[])
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
    [9]  (& NJ_TRI_Site::set_zip_code)


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


 ntsl.read_csv_file(10);

 QMap<QString, NJ_TRI_Site_List> sites_by_county;

 QString base_folder = "/home/nlevisrael/docker/tox/objects/tir/summaries/counties/";

 for(NJ_TRI_Site site : ntsl.sites())
 {
  QString county = site.county_ucfirsr();

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

  NJ_TRI_Site_List& ntsl = it.value();

  ntsl.default_json_field_getters();

//  auto g = getters.copy();
//  g.insert_default(it.key());
//  ntsl.set_csv_field_getters(g);
//  ntsl.save_to_csv_file("!", &header);

  ntsl.save_to_json_file();

 }



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
