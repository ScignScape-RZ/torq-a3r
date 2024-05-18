
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-tri-site.h"

#include <QDebug>


NJ_TRI_Site::NJ_TRI_Site()
  :  Flags(0), year_(0),
     frs_id_(0), supplemental_(nullptr),
     zip_code_(0), latitude_(0), longitude_(0),
     horizontal_datum_(Horizontal_Datum_Options::N_A),
     industry_sector_code_(0),
     document_control_number_(0),
     CAS_registry_number_(0),
     TRI_chemical_id_(0),
     SRS_id_(0),
     onsite_release_total_(0),
     potw_release_or_disposal_(0),
     potw_further_treatment_(0),
     potw_total_(0), //?offsite_release_total_(0),
     overall_offsite_transfer_total_(0),
     onsite_and_offsite_releases_total_(0),
     source_reduction_releases_total_(0),
     production_waste_(0),
     one_time_release_(0),
     production_ratio_(0)
{

}


// //  supplemental_ will have 1 element if only the
 //    horizontal_datum_string is set;
 //    it will have 2 elements for "indian affairs" data;
 //    and 3 elements for both cases.  The horizontal_datum_string
 //    will always be last.

void NJ_TRI_Site::set_horizontal_datum_string(QString horizontal_datum_string)
{
 check_supplemental();

 switch(supplemental_->size())
 {
 case 0:
 case 2:
  supplemental_->push_back(horizontal_datum_string);
  break;

 case 1:
 case 3:
  (*supplemental_)[0] = horizontal_datum_string;
  break;

 default:
  qDebug() << "Unexptected length of 'supplemental_' in " __FILE__;
  break;
 }
}

QString NJ_TRI_Site::horizontal_datum_string() const
{
 if(supplemental_)
 {
  if( (supplemental_->size() == 1) || (supplemental_->size() == 3) )
    return supplemental_->last();
 }

 return {};
}


void NJ_TRI_Site::set_BIA_code(QString bia_code)
{
 flags.on_tribal_land = true;
 check_supplemental();

 (*supplemental_)[0] = bia_code;
}

QString NJ_TRI_Site::BIA_code() const
{
 if(supplemental_)
 {
  if(supplemental_->size() > 1)
    return (*supplemental_)[0];
 }
 return {};
}




void NJ_TRI_Site::set_tribe_name(QString tribe_name)
{
 flags.on_tribal_land = true;
 check_supplemental();
 (*supplemental_)[1] = tribe_name;
}

QString NJ_TRI_Site::tribe_name() const
{
 if(supplemental_)
 {
  if(supplemental_->size() > 1)
    return (*supplemental_)[1];
 }
 return {};
}


