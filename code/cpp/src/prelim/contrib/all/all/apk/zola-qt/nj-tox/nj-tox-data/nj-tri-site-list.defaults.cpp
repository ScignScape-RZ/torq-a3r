
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


    kmd(parent_company_name, get_parent_company_name)
    kmd(parent_company_standardized_name, get_parent_company_standardized_name)
    kmd(parent_company_db_number, str_get_parent_company_db_number)
    kmd(industry_sector)
    str_kmd(industry_sector_code)

 };

#undef kmd
#undef str_kmd
}

