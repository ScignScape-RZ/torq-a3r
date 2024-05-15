
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TRI_SITE__H
#define NJ_TRI_SITE__H

#include <QString>

#include "global-types.h"

#include "accessors.h"

#include "flags.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"


class NJ_TRI_Site
{
public:

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


 enum class Horizontal_Datum_Options {
  N_A = 0, NAD27 = 1, NAD83 = 2,
  WGS84 = 4, Other = 8,
 };

 enum class Transfer_or_Release_Descriptions {
  N_A = 0,
  Disposal = 1,    // csv col 85
  Recycling = 2,      // csv col 91
  Energy_Recovery = 4,     // csv col 94
  Treatment = 8,     // csv col 101
  Releases_Contained = 16,     // csv col 106, 107
  Releases_Other = 32,     // csv col 106, 107
  Unclassified = 64    // csv col 102
 };



#define Discharge_Descriptions_List(m) \
  m(Fugitive_Air, 48) \
  m(Stack_Air, 49) \
  m(Surface_Water, 50) \
  m(Underground, 51) \
  m(Underground_Class_I, 52) \
  m(Underground_Class_II_to_V, 53) \
  m(Landfills, 54) \
  m(Landfills_RCRA_C, 55) \
  m(Landfills_Other, 56) \
  m(Land_Treatment, 57) \
  m(Surface_Impoundment, 58) \
  m(Surface_Impoundment_RCRA, 59) \
  m(Surface_Impoundment_Other, 60) \
  m(Other_Disposal, 61) \


#define Offsite_Keys_List(m) \
 m(M10, 66, Disposal) \
 m(M41, 67, Disposal) \
 m(M62, 68, Disposal) \
 m(M40_metal, 69, Disposal) \
 m(M61_metal, 70, Disposal) \
 m(M71, 71, Disposal) \
 m(M81, 72, Disposal) \
 m(M82, 73, Disposal) \
 m(M72, 74, Disposal) \
 m(M63, 75, Disposal) \
 m(M66, 76, Disposal) \
 m(M67, 77, Disposal) \
 m(M64, 78, Disposal) \
 m(M65, 79, Disposal) \
 m(M73, 80, Disposal) \
 m(M79, 81, Disposal) \
 m(M90, 82, Disposal) \
 m(M94, 83, Disposal) \
 m(M99, 84, Disposal) \
 m(M20, 86, Recycling) \
 m(M24, 87, Recycling) \
 m(M26, 88, Recycling) \
 m(M28, 89, Recycling) \
 m(M93, 90, Recycling) \
 m(M56, 92, Energy_Recovery) \
 m(M92, 93, Energy_Recovery) \
 m(M40_non_metal, 95, Treatment) \
 m(M50, 96, Treatment) \
 m(M54, 97, Treatment) \
 m(M61_non_metal, 98, Treatment) \
 m(M69, 99, Treatment) \
 m(M95, 100, Treatment) \


#define Onsite_and_Offsite_Keys_List(m) \
  m(Onsite_Contained, 106, Releases_Contained) \
  m(Onsite_Other, 107, Releases_Other) \
  m(Offsite_Contained, 108, Releases_Contained) \
  m(Offsite_Other, 109, Releases_Other) \
  m(Onsite_Energy_Recovery, 110, Energy_Recovery) \
  m(Offsite_Energy_Recovery, 111, Energy_Recovery) \
  m(Onsite_Recycling, 112, Recycling) \
  m(Offsite_Recycling, 113, Recycling) \
  m(Onsite_Treatment, 114, Treatment) \
  m(Offsite_Treatment, 115, Treatment) \


 enum class Offsite_Keys {
  N_A = 0,
  #define KV_MACRO(k, v, d) k = v,
  Offsite_Keys_List(KV_MACRO)
  #undef KV_MACRO
 };

 static Offsite_Keys parse_offsite_key(QString key)
 {
  static QMap<QString, Offsite_Keys> static_map {
   #define KV_MACRO(k, v, d) {#k, Offsite_Keys::k},
   Offsite_Keys_List(KV_MACRO)
   #undef KV_MACRO
  };

  return static_map.value(key, Offsite_Keys::N_A);
 }

 static Transfer_or_Release_Descriptions offsite_transer_description(Offsite_Keys key)
 {
  static QMap<Offsite_Keys, Transfer_or_Release_Descriptions> static_map {
   #define KV_MACRO(k, v, d) {Offsite_Keys::k, Transfer_or_Release_Descriptions::d},
   Offsite_Keys_List(KV_MACRO)
   #undef KV_MACRO
  };

  return static_map.value(key, Transfer_or_Release_Descriptions::N_A);
 }



 enum class Onsite_and_Offsite_Keys {
  N_A = 0,
  #define KV_MACRO(k, v, d) k = v,
  Onsite_and_Offsite_Keys_List(KV_MACRO)
  #undef KV_MACRO
 };

 static Onsite_and_Offsite_Keys parse_onsite_and_offsite_key(QString key)
 {
  static QMap<QString, Onsite_and_Offsite_Keys> static_map {
   #define KV_MACRO(k, v, d) {#k, Onsite_and_Offsite_Keys::k},
   Onsite_and_Offsite_Keys_List(KV_MACRO)
   #undef KV_MACRO
  };

  return static_map.value(key, Onsite_and_Offsite_Keys::N_A);
 }

 static Transfer_or_Release_Descriptions onsite_and_offsite_transer_description(Onsite_and_Offsite_Keys key)
 {
  static QMap<Onsite_and_Offsite_Keys, Transfer_or_Release_Descriptions> static_map {
   #define KV_MACRO(k, v, d) {Onsite_and_Offsite_Keys::k, Transfer_or_Release_Descriptions::d},
   Onsite_and_Offsite_Keys_List(KV_MACRO)
   #undef KV_MACRO
  };

  return static_map.value(key, Transfer_or_Release_Descriptions::N_A);
 }



 enum class Discharge_Descriptions {
  N_A = 0,
  #define KV_MACRO(k, v) k = v,
  Discharge_Descriptions_List(KV_MACRO)
  #undef KV_MACRO
 };


 static Discharge_Descriptions parse_discharge_description(QString key)
 {
  static QMap<QString, Discharge_Descriptions> static_map {
   #define KV_MACRO(k, v) {#k, Discharge_Descriptions::k},
   Discharge_Descriptions_List(KV_MACRO)
   #undef KV_MACRO
  };

  return static_map.value(key, Discharge_Descriptions::N_A);
 }

 struct Parent_Company {
  QString name;  // csv col 15
  u4 db_number;  // csv col 16
  QString standardized_name_;  // csv col 17

  Parent_Company() : db_number(0) {}
 };

private:

 u2 year_;  // csv col 1
 QString trifd_;  // csv col 2
 n8 frs_id_;  // csv col 3

 QString facility_name_; // csv col 4

 QString street_address_;  // csv col 5
 QString municipality_;  // csv col 6
 QString county_;   // csv col 7

 // //  exclude state field for this code, because it's consistently NJ

 u4 zip_code_;  // csv col 9

 QStringList* supplemental_;  // for fields likely to be rarely used,
   // e.g. "Indian Affairs" data (csv cols 10-11)

 r8 latitude_;  // csv col 12
 r8 longitude_;  // csv col 13

 Horizontal_Datum_Options horizon_datum_; // csv col 14
// QString alt_horizon_datum_;            // csv col 14

 Parent_Company parent_company_;  // csv cols 15 - 17;

 u2 industry_sector_code_;  // csv col 19
 QString industry_sector_;  // csv col 20

 QVector<u2> SIC_codes_;   // csv cols 21 - 26

 QVector<u4> NAICS_codes_;  // csv cols 27 - 32

 n8 document_control_number_;   // csv col 33

 QString chemical_name_;   // csv col 34

 u4 CAS_registry_number_;   // csv col 36
 u4 TRI_chemical_id_;   // csv col 37
 u4 SRS_id_;   // csv col 38

 QString classification_;   // csv col 40


 QMap<Discharge_Descriptions, r8> discharge_amounts_;   // csv cols 48 - 61

 r8 onsite_release_total_;   // csv col 62

 r8 potw_release_or_disposal_;   // csv col 63
 r8 potw_further_treatment_;   // csv col 64
 r8 potw_total_;   // csv col 65

 QMap<Offsite_Keys, r8> offsite_transfer_amounts_;    // csv cols 66 - 100

 QMap<Transfer_or_Release_Descriptions, r8> offsite_transfer_totals_;

 r8  overall_offsite_transfer_total_;    // csv cols 103
 r8  onsite_and_offsite_releases_total_;    // csv cols 104
 r8  source_reduction_releases_total_;    // csv cols 105

 QMap<Onsite_and_Offsite_Keys, r8> onsite_and_offsite_amounts_;   // csv cols 106 - 115

 r8  production_waste_;    // csv cols 116
 r8  one_time_release_;    // csv cols 117

 r8  production_ratio_;    // csv cols 119

// QString metal_category_;


public:

 NJ_TRI_Site();


 ACCESSORS(u2 ,year)
 ACCESSORS(QString ,trifd)
 ACCESSORS(n8 ,frs_id)

 ACCESSORS(QString ,facility_name)

 ACCESSORS(QString ,street_address)
 ACCESSORS(QString ,municipality)
 ACCESSORS(QString ,county)

 ACCESSORS(u4 ,zip_code)

 ACCESSORS(QStringList* ,supplemental)

 ACCESSORS(r8 ,latitude)
 ACCESSORS(r8 ,longitude)

 ACCESSORS(Horizontal_Datum_Options ,horizon_datum)
 ACCESSORS__DECLARE(QString ,horizon_datum_string)

 ACCESSORS__RGET(Parent_Company ,parent_company)


 ACCESSORS(u4 ,industry_sector_code)
 ACCESSORS(QString ,industry_sector)

 ACCESSORS__RGET(QVector<u2> ,SIC_codes)
 ACCESSORS__RGET(QVector<u4> ,NAICS_codes)

 ACCESSORS(n8 ,document_control_number)

 ACCESSORS(QString ,chemical_name)

 ACCESSORS(u4 ,CAS_registry_number)
 ACCESSORS(u4 ,TRI_chemical_id)
 ACCESSORS(u4 ,SRS_id)

 ACCESSORS(QString ,classification)


 ACCESSORS__RGET(QMap<Discharge_Descriptions, r8> ,discharge_amounts)

 ACCESSORS(r8 ,onsite_release_total)

 ACCESSORS(r8 ,potw_release_or_disposal)
 ACCESSORS(r8 ,potw_further_treatment)
 ACCESSORS(r8 ,potw_total)

 ACCESSORS__RGET(QMap<Offsite_Keys, r8> ,offsite_transfer_amounts)

 ACCESSORS__RGET(QMap<Transfer_or_Release_Descriptions, r8> ,offsite_transfer_totals)

 ACCESSORS(r8 ,overall_offsite_transfer_total)
 ACCESSORS(r8 ,onsite_and_offsite_releases_total)
 ACCESSORS(r8 ,source_reduction_releases_total)

 ACCESSORS__RGET(QMap<Onsite_and_Offsite_Keys, r8> ,onsite_and_offsite_amounts)

 ACCESSORS(r8 ,production_waste)
 ACCESSORS(r8 ,one_time_release)

 ACCESSORS(r8 ,production_ratio)
// ACCESSORS(QString ,metal_category)




// ACCESSORS(QString ,chemical)

// ACCESSORS(QString ,municipality)
// ACCESSORS(QString ,county)
// ACCESSORS(QString ,data_source)

// ACCESSORS__GET(QVector<QPair<r8, r8>>* ,ref_coords)

 SET_and_STR_ADAPTER_DBL(latitude)
 SET_and_STR_ADAPTER_DBL(longitude)

 SET_and_STR_ADAPTER_N8(frs_id)
 SET_and_STR_ADAPTER_INT(industry_sector_code)

 SET_and_STR_ADAPTER_INT(zip_code)


// SET_and_STR_ADAPTER_INT(site_id)
// SET_and_STR_ADAPTER_INT(pi_number)

};


#endif // NJ_TRI_SITE__H







//enum class Offsite_Disposal_Keys {
//  M10 = 66,
//  M41 = 67,
//  M62 = 68,
//  M40_metal = 69,
//  M61_metal = 70,
//  M71 = 71,
//  M81 = 72,
//  M82 = 73,
//  M72 = 74,
//  M63 = 75,
//  M66 = 76,
//  M67 = 77,
//  M64 = 78,
//  M65 = 79,
//  M73 = 80,
//  M79 = 81,
//  M90 = 82,
//  M94 = 83,
//  M99 = 84,
//  M20 = 86,
//  M24 = 87,
//  M26 = 88,
//  M28 = 89,
//  M93 = 90,
//  M56 = 92,
//  M92 = 93,
//  M40_non_metal = 95,
//  M50 = 96,
//  M54 = 97,
//  M61_non_metal = 98,
//  M69 = 99,
//  M95 = 100,
//};
