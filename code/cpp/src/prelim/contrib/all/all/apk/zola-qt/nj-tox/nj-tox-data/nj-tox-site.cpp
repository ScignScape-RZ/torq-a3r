
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-tox-site.h"


NJ_Tox_Site::NJ_Tox_Site()
  :  latitude_(0), longitude_(0), coords_count_(0),
     site_id_(0), pi_number_(0), ref_coords_(nullptr)
{

}

void NJ_Tox_Site::init_ref_coords()
{
 ref_coords_ = new QVector<QPair<r8, r8>>;
}



