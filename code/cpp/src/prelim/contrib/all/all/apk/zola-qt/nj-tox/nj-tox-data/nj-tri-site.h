
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TRI_SITE__H
#define NJ_TRI_SITE__H

#include <QString>

#include <QDebug>

#include "global-types.h"

#include "accessors.h"

#include "global-macros.h"

#include "flags.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"


class NJ_TRI_Site
{
public:


#define Flags_List(m) \
 m(on_tribal_land)            /* csv col 10 */  \
 m(federal_facility)          /* csv col 18 */  \
 m(elemental_metal_included)  /* csv col 35 */  \
 m(clean_air_act_chemical)    /* csv col 39 */  \
 m(classified_as_metal)       /* csv col 41 */  \
 m(carcinogen)                /* csv col 43 */  \
 m(pbt)                       /* csv col 44 */  \
 m(pfas)                      /* csv col 45 */  \
 m(form_r)                    /* csv col 46 */  \
 m(form_a)                    /* csv col 46 */  \
 m(units_pounds)              /* csv col 47 */  \
 m(units_grams)               /* csv col 47 */  \
 m(production_ratio_value)    /* csv col 118 */ \
 m(activity_index_value)      /* csv col 118 */ \


 flags_(2)
#define K_MACRO(k) bool k:1;
Flags_List(K_MACRO)
#undef K_MACRO
 _flags


 // //  Note: there appears to be a typo in the TIR guide;
  //    csv col 118 is listed as "189", but only 118
  //    makes sense in context

 enum Flag_Values {
#define K_MACRO(k) k,
Flags_List(K_MACRO)
#undef K_MACRO
 };


 // //  note when flags are paired,
  //    this code chooses not to
  //    explicitly clear the one
  //    flag when the other is set

 template<Flag_Values fv>
 void set_flag()
 {
  _set_flag_(fv);
 }

 template<Flag_Values fv>
 bool get_flag()
 {
  return _get_flag_(fv);
 }

 template<Flag_Values fv>
 void clear_flag()
 {
  _set_flag_(fv, false);
 }

 template<Flag_Values fv>
 void toggle_flag()
 {
  _set_flag_(fv, !get_flag<fv>());
 }

 void _set_flag_(Flag_Values fv, bool t_or_f = true)
 {
  switch(fv)
  {
#define K_MACRO(k) case Flag_Values::k: flags.k = t_or_f; break;
Flags_List(K_MACRO)
#undef K_MACRO
  default: break;
  }
 }

 bool _get_flag_(Flag_Values fv)
 {
  switch(fv)
  {
#define K_MACRO(k) case Flag_Values::k: return flags.k;
Flags_List(K_MACRO)
#undef K_MACRO
  default: return false;
  }
 }



#define enum_class_KV_MACRO(k, v) k = v,

#define enum_class_2(ec, ecl) \
 enum class ec \
 { \
  N_A = 0, \
  ecl(enum_class_KV_MACRO) \
 }; \

#define enum_class_1(ec) \
  enum_class_2(ec, ec##_##List)

#define enum_class(...) \
   _preproc_CONCAT(enum_class_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)



#define Horizontal_Datum_Options_List(m) \
  m( NAD27 ,1 ) \
  m( NAD83 ,2 ) \
  m( WSG84 ,4 ) \
  m( Other ,8 ) \


 enum_class(Horizontal_Datum_Options)

// enum class Horizontal_Datum_Options
// {
//  N_A = 0,
//  Horizontal_Datum_Options_List(enum_class_KV_MACRO)
// };


#define Classification_Keys_List(m) \
  m(TRI ,1) \
  m(PBT ,2) \
  m(Dioxin ,4) \

 enum_class(Classification_Keys)

// enum class Classification_Keys
// {
//  N_A = 0,
//  Classification_Keys_List(enum_class_KV_MACRO)
// };


#define Metal_Category_List(m) \
  m(May_Contain ,1) \
  m(Elemental_Metals ,2) \
  m(Metal_Compound ,4) \
  m(Individually_Listed ,8) \
  m(Non_Metal ,16) \

 enum_class(Metal_Category)

// enum class Metal_Category
// {
//  N_A = 0,
//  Metal_Category_List(enum_class_KV_MACRO)
// };





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
  m(Fugitive_Air ,48) \
  m(Stack_Air ,49) \
  m(Surface_Water ,50) \
  m(Underground ,51) \
  m(Underground_Class_I ,52) \
  m(Underground_Class_II_to_V ,53) \
  m(Landfills ,54) \
  m(Landfills_RCRA_C ,55) \
  m(Landfills_Other ,56) \
  m(Land_Treatment ,57) \
  m(Surface_Impoundment ,58) \
  m(Surface_Impoundment_RCRA ,59) \
  m(Surface_Impoundment_Other ,60) \
  m(Other_Disposal ,61) \


#define Offsite_Keys_List(m) \
 m(M10 ,66 ,Disposal) \
 m(M41 ,67 ,Disposal) \
 m(M62 ,68 ,Disposal) \
 m(M40_metal ,69 ,Disposal) \
 m(M61_metal ,70 ,Disposal) \
 m(M71 ,71 ,Disposal) \
 m(M81 ,72 ,Disposal) \
 m(M82 ,73 ,Disposal) \
 m(M72 ,74 ,Disposal) \
 m(M63 ,75 ,Disposal) \
 m(M66 ,76 ,Disposal) \
 m(M67 ,77 ,Disposal) \
 m(M64 ,78 ,Disposal) \
 m(M65 ,79 ,Disposal) \
 m(M73 ,80 ,Disposal) \
 m(M79 ,81 ,Disposal) \
 m(M90 ,82 ,Disposal) \
 m(M94 ,83 ,Disposal) \
 m(M99 ,84 ,Disposal) \
 m(M20 ,86 ,Recycling) \
 m(M24 ,87 ,Recycling) \
 m(M26 ,88 ,Recycling) \
 m(M28 ,89 ,Recycling) \
 m(M93 ,90 ,Recycling) \
 m(M56 ,92 ,Energy_Recovery) \
 m(M92 ,93 ,Energy_Recovery) \
 m(M40_non_metal ,95 ,Treatment) \
 m(M50 ,96 ,Treatment) \
 m(M54 ,97 ,Treatment) \
 m(M61_non_metal ,98 ,Treatment) \
 m(M69 ,99 ,Treatment) \
 m(M95 ,100 ,Treatment) \


#define Onsite_and_Offsite_Keys_List(m) \
  m(Onsite_Contained ,106 ,Releases_Contained) \
  m(Onsite_Other ,107 ,Releases_Other) \
  m(Offsite_Contained ,108 ,Releases_Contained) \
  m(Offsite_Other ,109 ,Releases_Other) \
  m(Onsite_Energy_Recovery ,110 ,Energy_Recovery) \
  m(Offsite_Energy_Recovery ,111 ,Energy_Recovery) \
  m(Onsite_Recycling ,112 ,Recycling) \
  m(Offsite_Recycling ,113 ,Recycling) \
  m(Onsite_Treatment ,114 ,Treatment) \
  m(Offsite_Treatment ,115 ,Treatment) \



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
  QString standardized_name;  // csv col 17

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

 Horizontal_Datum_Options horizontal_datum_; // csv col 14
// QString alt_horizon_datum_;            // csv col 14

 Parent_Company parent_company_;  // csv cols 15 - 17;

 u2 industry_sector_code_;  // csv col 19
 QString industry_sector_;  // csv col 20

 QVector<u2> SIC_codes_;   // csv cols 21 - 26

 QVector<u4> NAICS_codes_;  // csv cols 27 - 32

 n8 document_control_number_;   // csv col 33

 QString chemical_name_;   // csv col 34

 QString TRI_chemical_id_;   // csv col 36
 QString CAS_registry_number_;   // csv col 37

 u4 SRS_id_;   // csv col 38

 Classification_Keys classification_;   // csv col 40

 Metal_Category metal_category_;   // csv col 42

 QMap<Discharge_Descriptions, r8> discharge_amounts_;   // csv cols 48 - 61

 r8 onsite_release_total_;   // csv col 62

 r8 potw_release_or_disposal_;   // csv col 63
 r8 potw_further_treatment_;   // csv col 64
 r8 potw_total_;   // csv col 65

 QMap<Offsite_Keys, r8> offsite_transfer_amounts_;    // csv cols 66 - 100

// r8 offsite_release_total_;   // csv col 85
// r8 offsite_recycled_total_;   // csv col 91

 QMap<Transfer_or_Release_Descriptions, r8> offsite_transfer_or_release_totals_;

 r8  overall_offsite_transfer_total_;    // csv cols 103
 r8  onsite_and_offsite_releases_total_;    // csv cols 104
 r8  source_reduction_releases_total_;    // csv cols 105

 QMap<Onsite_and_Offsite_Keys, r8> onsite_and_offsite_amounts_;   // csv cols 106 - 115

 r8  production_waste_;    // csv cols 116
 r8  one_time_release_;    // csv cols 117

 r8  production_ratio_;    // csv cols 119

// QString metal_category_;

 void check_supplemental()
 {
  if(supplemental_)
  {
   if(flags.on_tribal_land && (supplemental_->size() == 1) )
   {
    supplemental_->push_front({});
    supplemental_->push_front({});
   }
  }
  else
  {
   supplemental_ = new QStringList;
   if(flags.on_tribal_land)
   {
    supplemental_->push_back({});
    supplemental_->push_back({});
   }
  }
 }


public:

 NJ_TRI_Site();

 void set_test(QString val) //, u2 col)
 {
  qDebug() << "val = " << val;
 }

 ACCESSORS(u2 ,year)
 ACCESSORS(QString ,trifd)
 ACCESSORS(n8 ,frs_id)

 ACCESSORS(QString ,facility_name)

 ACCESSORS(QString ,street_address)
 ACCESSORS(QString ,municipality)
 ACCESSORS(QString ,county)

 ACCESSORS(u4 ,zip_code)

 ACCESSORS(QStringList* ,supplemental)

 ACCESSORS__DECLARE(QString ,BIA_code)
 ACCESSORS__DECLARE(QString ,tribe_name)

 ACCESSORS(r8 ,latitude)
 ACCESSORS(r8 ,longitude)

 ACCESSORS(Horizontal_Datum_Options ,horizontal_datum)
 ACCESSORS__DECLARE(QString ,horizontal_datum_string)


 ACCESSORS__RGET(Parent_Company ,parent_company)

 void set_parent_company_name(QString n)  // csv col 15
 {
  parent_company_.name = n;
 }
 void set_parent_company_db_number(QString n)  // csv col 16
 {
  parent_company_.db_number = n.toInt();
 }
 void set_parent_company_standardized_name(QString n) // csv col 17
 {
  parent_company_.standardized_name = n;
 }

 ACCESSORS(u4 ,industry_sector_code)
 ACCESSORS(QString ,industry_sector)

 ACCESSORS__RGET(QVector<u2> ,SIC_codes)

#define ADD_WITH_RESIZE_2(collection, fname) \
void fname(QString s, u2 index) \
{ \
 if(collection.size() <= index) \
   collection.resize(index + 1); \
 collection[index] = s.toInt(); \
} \

#define ADD_WITH_RESIZE_1(parameter) \
 ADD_WITH_RESIZE_2(parameter##s_, add_##parameter)

#define ADD_WITH_RESIZE(...) \
  _preproc_CONCAT(ADD_WITH_RESIZE_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)



 ADD_WITH_RESIZE(SIC_code)

// void add_SIC_code(QString s, u2 index)
// {
//  if(SIC_codes_.size() <= index)
//    SIC_codes_.resize(index + 1);

//  SIC_codes_[index] = s.toInt();
// }

 ACCESSORS__RGET(QVector<u4> ,NAICS_codes)
 ADD_WITH_RESIZE(NAICS_code)

// void add_NAICS_code(QString s, u2 index)
// {
//  if(NAICS_codes_.size() <= index)
//    NAICS_codes_.resize(index + 1);

//  NAICS_codes_[index] = s.toInt();
// }


// Horizontal_Datum_Options parse_horizontal_datum(QString key)
// {
//  static QMap<QString, Horizontal_Datum_Options> static_map {{
//#define K_MACRO(k, v) {#k, Horizontal_Datum_Options::k},
//  Horizontal_Datum_Options_List(K_MACRO)
//#undef K_MACRO
//  }};

//  return static_map.value(key, Horizontal_Datum_Options::N_A);
// }

// void read_horizontal_datum(QString s)
// {
//  set_horizontal_datum(parse_horizontal_datum(s));
// }

// Classification_Keys parse_classification(QString key)
// {
//  static QMap<QString, Classification_Keys> static_map {{
//#define K_MACRO(k, v) {#k, Classification_Keys::k},
//  Classification_Keys_List(K_MACRO)
//#undef K_MACRO
//  }};

//  return static_map.value(key, Classification_Keys::N_A);
// }

// void read_classification(QString s)
// {
//  set_classification(parse_classification(s));
// }


#define enum_class_read_K_MACRO(k, v) {#k, for_enum_class::k},


#define PARSE_AND_READ_3(enum_class, sh, m) \
enum_class parse_##sh(QString key) \
{ \
 static QMap<QString, enum_class> static_map {{ \
  _preproc_CONCAT(enum_class, _List)(m) \
  }}; \
  return static_map.value(key, enum_class::N_A); \
 } \
void read_##sh(QString s) \
{ \
 set_##sh(parse_##sh(s)); \
} \

#define PARSE_AND_READ_2(enum_class, sh) \
  PARSE_AND_READ_3(enum_class, sh, enum_class_read_K_MACRO)

#define PARSE_AND_READ_1(sh) \
  PARSE_AND_READ_2(for_enum_class, sh)

#define PARSE_AND_READ(...) _preproc_CONCAT(PARSE_AND_READ_, _preproc_NUM_ARGS (__VA_ARGS__))(__VA_ARGS__)

#define for_enum_class Classification_Keys
PARSE_AND_READ(classification)
              # undef for_enum_class

#define for_enum_class Horizontal_Datum_Options
PARSE_AND_READ(horizontal_datum)
              # undef for_enum_class


#define for_enum_class Metal_Category
PARSE_AND_READ(metal_category)
              # undef for_enum_class


 void read_metal_category_with_corrections(QString key)
 {
  QString correction = key.simplified().toLower();
  correction.replace(' ', '_');
  correction.replace("complound", "compound");

  QStringList qsl = correction.split("_", Qt::SkipEmptyParts);

  if(qsl.isEmpty())
    return;

  correction = qsl[0];
  correction[0] = correction[0].toUpper();

  if(qsl.size() > 1)
  {
   correction += "_";
   QString c = qsl[1];
   c[0] = c[0].toUpper();
   correction += c;
  }

  read_metal_category(correction);

 }

//  static QMap<QString, Metal_Category> static_map {
//   {"may_contain_metal", Metal_Category::Metal_Category_1},
//   {"elemental_metals", Metal_Category::Metal_Category_1},
//   {"metal_compound_categories", Metal_Category::Metal_Category_4},
//   {"non_metal", Metal_Category::Metal_Category_4},
//   {"individually-listed-compounds-that-contain-metal", Metal_Category::Metal_Category_4},

//  };

// }

 ACCESSORS(n8 ,document_control_number)

 ACCESSORS(QString ,chemical_name)

 ACCESSORS(QString ,TRI_chemical_id)
 ACCESSORS(QString ,CAS_registry_number)

 ACCESSORS(u4 ,SRS_id)

 ACCESSORS(Classification_Keys ,classification)
 ACCESSORS(Metal_Category ,metal_category)


 ACCESSORS__RGET(QMap<Discharge_Descriptions, r8> ,discharge_amounts)

 void note_discharge_amount(r8 amount, QString description)
 {
  discharge_amounts_[parse_discharge_description(description)] = amount;
 }

 void read_discharge_amount(QString amount, QString description)
 {
  note_discharge_amount(amount.toDouble(), description);
 }


 ACCESSORS(r8 ,onsite_release_total)

 ACCESSORS(r8 ,potw_release_or_disposal)
 ACCESSORS(r8 ,potw_further_treatment)
 ACCESSORS(r8 ,potw_total)

   // ACCESSORS(r8 ,offsite_release_total)

 ACCESSORS__RGET(QMap<Offsite_Keys, r8> ,offsite_transfer_amounts)

 ACCESSORS__RGET(QMap<Transfer_or_Release_Descriptions, r8> ,offsite_transfer_or_release_totals)

 void note_offsite_transfer_or_release_total(r8 amount, Transfer_or_Release_Descriptions description)
 {
  offsite_transfer_or_release_totals_[description] = amount;
 }

 void read_offsite_transfer_or_release_total(QString amount, u2 description)
 {
  note_offsite_transfer_or_release_total(amount.toDouble(),
    (Transfer_or_Release_Descriptions) description);
 }


// offsite_transfer_or_release_totals_


 ACCESSORS(r8 ,overall_offsite_transfer_total)
 ACCESSORS(r8 ,onsite_and_offsite_releases_total)
 ACCESSORS(r8 ,source_reduction_releases_total)

 ACCESSORS__RGET(QMap<Onsite_and_Offsite_Keys, r8> ,onsite_and_offsite_amounts)

 void note_onsite_and_offsite_amounts(r8 amount, QString key)
 {
  onsite_and_offsite_amounts_[parse_onsite_and_offsite_key(key)] = amount;
 }

 void read_onsite_and_offsite_amounts(QString amount, QString key)
 {
  note_onsite_and_offsite_amounts(amount.toDouble(), key);
 }




 ACCESSORS(r8 ,production_waste)
 ACCESSORS(r8 ,one_time_release)

 ACCESSORS(r8 ,production_ratio)
// ACCESSORS(QString ,metal_category)




// ACCESSORS(QString ,chemical)

// ACCESSORS(QString ,municipality)
// ACCESSORS(QString ,county)
// ACCESSORS(QString ,data_source)

// ACCESSORS__GET(QVector<QPair<r8, r8>>* ,ref_coords)

 SET_and_STR_ADAPTER_INT(year)

 SET_and_STR_ADAPTER_N8(frs_id)
 SET_and_STR_ADAPTER_INT(zip_code)

 SET_and_STR_ADAPTER_DBL(latitude)
 SET_and_STR_ADAPTER_DBL(longitude)

 SET_and_STR_ADAPTER_INT(industry_sector_code)
 SET_and_STR_ADAPTER_N8(document_control_number)
 SET_and_STR_ADAPTER_INT(SRS_id)

 SET_and_STR_ADAPTER_DBL(onsite_release_total)
 SET_and_STR_ADAPTER_DBL(potw_release_or_disposal)
 SET_and_STR_ADAPTER_DBL(potw_further_treatment)
 SET_and_STR_ADAPTER_DBL(potw_total)

// SET_and_STR_ADAPTER_DBL(offsite_release_total)
// SET_and_STR_ADAPTER_DBL(offsite_recycled_total)

 SET_and_STR_ADAPTER_DBL(overall_offsite_transfer_total)
 SET_and_STR_ADAPTER_DBL(onsite_and_offsite_releases_total)
 SET_and_STR_ADAPTER_DBL(source_reduction_releases_total)
 SET_and_STR_ADAPTER_DBL(production_waste)
 SET_and_STR_ADAPTER_DBL(one_time_release)
 SET_and_STR_ADAPTER_DBL(production_ratio)


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
