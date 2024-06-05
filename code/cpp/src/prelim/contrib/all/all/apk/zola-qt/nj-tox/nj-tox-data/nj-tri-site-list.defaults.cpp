
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-tri-site-list.h"

#include "textio.h"


#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"


#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>





void NJ_TRI_Site_List::default_json_field_setters()
{
#define kmd NJ_TRI_Site_SET_KMD_MACRO
#define read_kmd NJ_TRI_Site_READ_KMD_MACRO

 json_field_setters() = {

   kmd(flags, str_read_flag_union)

   kmd(year)
   kmd(trifd)
   kmd(frs_id)
   kmd(facility_name)
   kmd(street_address)
   kmd(municipality)
   kmd(county)
   kmd(zip_code)

   kmd(latitude)
   kmd(longitude)

   kmd(horizontal_datum, read_enum_numeric<NJ_TRI_Site::Horizontal_Datum_Options>)
   kmd(classification, read_enum_numeric<NJ_TRI_Site::Classification_Keys>)
   kmd(metal_category, read_enum_numeric<NJ_TRI_Site::Metal_Category>)

   kmd(document_control_number)

   kmd(chemical_name)

   kmd(TRI_chemical_id)
   kmd(CAS_registry_number)

   kmd(SRS_id)



   kmd(parent_company_name, set_parent_company_name)
   kmd(parent_company_standardized_name, set_parent_company_standardized_name)
   kmd(parent_company_db_number, set_parent_company_db_number)
   kmd(industry_sector)
   kmd(industry_sector_code)

   read_kmd(NAICS_codes)
   read_kmd(SIC_codes)

   kmd(discharge_amounts, str_read_discharge_amounts)

   kmd(offsite_transfer_amounts, str_read_offsite_transfer_amounts)
   kmd(offsite_transfer_or_release_totals, str_read_offsite_transfer_or_release_totals)
   kmd(onsite_and_offsite_amounts, str_read_onsite_and_offsite_amounts)

   kmd(onsite_release_total)
   kmd(potw_release_or_disposal)
   kmd(potw_further_treatment)
   kmd(potw_total)

   kmd(overall_offsite_transfer_total)
   kmd(onsite_and_offsite_releases_total)
   kmd(source_reduction_releases_total)

   kmd(production_waste)
   kmd(one_time_release)
   kmd(production_ratio)


 };

// json_field_setters_["year"] = &NJ_TRI_Site::set_year;
// xx = &NJ_TRI_Site::set_year;
#undef kmd
}



void NJ_TRI_Site_List::default_json_field_getters()
{
#define kmd NJ_TRI_Site_KMD_MACRO
#define str_kmd NJ_TRI_Site_STR_KMD_MACRO


 json_field_getters() = {

   kmd(flags, str_get_flag_union)

   str_kmd(year)
   kmd(trifd)
   str_kmd(frs_id)
   kmd(facility_name)
   kmd(street_address)
   kmd(municipality)
   kmd(county)
   str_kmd(zip_code)

   str_kmd(latitude)
   str_kmd(longitude)

   kmd(horizontal_datum, enum_to_numeric_str<NJ_TRI_Site::Horizontal_Datum_Options>)
   kmd(classification, enum_to_numeric_str<NJ_TRI_Site::Classification_Keys>)
   kmd(metal_category, enum_to_numeric_str<NJ_TRI_Site::Metal_Category>)

   str_kmd(document_control_number)

   kmd(chemical_name)

   kmd(TRI_chemical_id)
   kmd(CAS_registry_number)

   str_kmd(SRS_id)


    kmd(parent_company_name, get_parent_company_name)
    kmd(parent_company_standardized_name, get_parent_company_standardized_name)
    kmd(parent_company_db_number, str_get_parent_company_db_number)
    kmd(industry_sector)
    str_kmd(industry_sector_code)


  str_kmd(NAICS_codes)
  str_kmd(SIC_codes)



   kmd(discharge_amounts, str_map_discharge_amounts)
   kmd(offsite_transfer_amounts, str_map_offsite_transfer_amounts)
   kmd(offsite_transfer_or_release_totals, str_map_offsite_transfer_or_release_totals)
   kmd(onsite_and_offsite_amounts, str_map_onsite_and_offsite_amounts)

   str_kmd(onsite_release_total)
   str_kmd(potw_release_or_disposal)
   str_kmd(potw_further_treatment)
   str_kmd(potw_total)

   str_kmd(overall_offsite_transfer_total)
   str_kmd(onsite_and_offsite_releases_total)
   str_kmd(source_reduction_releases_total)

   str_kmd(production_waste)
   str_kmd(one_time_release)
   str_kmd(production_ratio)


 };

#undef kmd
#undef str_kmd
}

