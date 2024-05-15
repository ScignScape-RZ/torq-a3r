
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TRI_SITE_MULTIYEAR__H
#define NJ_TRI_SITE_MULTIYEAR__H

#include <QString>

#include "global-types.h"

#include "accessors.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"

class NJ_TRI_Site;

class NJ_TRI_Site_Multiyear
{
 n8 frs_id_;

 QMap<u2, NJ_TRI_Site*> sites_by_year_;

 r8 latitude_;
 r8 longitude_;


public:

 NJ_TRI_Site_Multiyear(n8 frs_id);


 ACCESSORS(n8 ,frs_id)

 ACCESSORS(r8 ,latitude)
 ACCESSORS(r8 ,longitude)


 ACCESSORS__RGET(QMap<u2, NJ_TRI_Site*> ,sites_by_year)


};


#endif // NJ_TRI_SITE_MULTIYEAR__H
