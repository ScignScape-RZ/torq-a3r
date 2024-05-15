
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef NJ_TRI_SITE_MULTIYEAR_LIST__H
#define NJ_TRI_SITE_MULTIYEAR_LIST__H

#include <QString>

#include "global-types.h"

#include "accessors.h"

//"Site ID","PI Number","PI Name","Address","Home Owner","Muni","County","Latitude","Longitude","loc Size","loc String","Source"

#include "nj-tri-site-multiyear.h"

class NJ_TRI_Site_Multiyear_List
{
 n8 frs_id_;

 QVector<NJ_TRI_Site_Multiyear> sites_;


public:

 NJ_TRI_Site_Multiyear_List();


 ACCESSORS__RGET(QVector<NJ_TRI_Site_Multiyear> ,sites)


};


#endif // NJ_TRI_SITE_MULTIYEAR_LIST__H
