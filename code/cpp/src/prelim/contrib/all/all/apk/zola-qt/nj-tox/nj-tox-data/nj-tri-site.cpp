
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-tri-site.h"


NJ_TRI_Site::NJ_TRI_Site()
  :  Flags(0), year_(0),
     frs_id_(0), supplemental_(nullptr),
     zip_code_(0), latitude_(0), longitude_(0),
     industry_sector_code_(0),
     document_control_number_(0),
     CAS_registry_number_(0),
     TRI_chemical_id_(0),
     SRS_id_(0),
     onsite_release_total_(0),
     potw_release_or_disposal_(0),
     potw_further_treatment_(0),
     potw_total_(0),
     overall_offsite_transfer_total_(0),
     onsite_and_offsite_releases_total_(0),
     source_reduction_releases_total_(0),
     production_waste_(0),
     one_time_release_(0),
     production_ratio_(0)
{

}


void NJ_TRI_Site::set_horizon_datum_string(QString arg)
{

}

QString NJ_TRI_Site::horizon_datum_string() const
{

}
