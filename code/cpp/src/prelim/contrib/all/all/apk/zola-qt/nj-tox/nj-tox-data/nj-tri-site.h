
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TRI_SITE__H
#define NJ_TRI_SITE__H

#include <QString>

#include "global-types.h"

#include "accessors.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"


#define SET_ADAPTER_(fn, to_) void set_##fn(QString arg) { set_##fn(arg.to##to_()); }

#define SET_ADAPTER_DBL(fn) SET_ADAPTER_(fn, Double)
#define SET_ADAPTER_INT(fn) SET_ADAPTER_(fn, Int)
#define SET_ADAPTER_N8(fn) SET_ADAPTER_(fn, LongLong)


#define STR_ADAPTER(fn) QString str_##fn() const { return  QString::number(fn()); }

#define SET_and_STR_ADAPTER_DBL(fn) SET_ADAPTER_(fn, Double) STR_ADAPTER(fn)
#define SET_and_STR_ADAPTER_INT(fn) SET_ADAPTER_(fn, Int) STR_ADAPTER(fn)
#define SET_and_STR_ADAPTER_N8(fn) SET_ADAPTER_(fn, LongLong) STR_ADAPTER(fn)



class NJ_TRI_Site
{
 n8 frs_id_;

 QString facility_name_;
 QString trifd_;

 QString street_address_;
 QString municipality_;
 QString county_;

 u4 zip_code_;

 r8 latitude_;
 r8 longitude_;

 u4 industry_sector_code_;
 QString industry_sector_;

 QString classification_;
 QString metal_category_;

 QString chemical_;



public:

 NJ_TRI_Site();


 ACCESSORS(n8 ,frs_id)

 ACCESSORS(QString ,facility_name)
 ACCESSORS(QString ,trifd)

 ACCESSORS(QString ,street_address)
 ACCESSORS(QString ,municipality)
 ACCESSORS(QString ,county)

 ACCESSORS(u4 ,zip_code)

 ACCESSORS(r8 ,latitude)
 ACCESSORS(r8 ,longitude)

 ACCESSORS(QString ,industry_sector)
 ACCESSORS(u4 ,industry_sector_code)

 ACCESSORS(QString ,classification)
 ACCESSORS(QString ,metal_category)

 ACCESSORS(QString ,chemical)

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


#endif // NJ_TOX_SITE__H
