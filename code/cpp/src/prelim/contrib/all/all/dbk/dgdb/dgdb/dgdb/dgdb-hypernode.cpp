
//           Copyright Nathaniel Christen 2021.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dgdb-hypernode.h"

#include "types/dh-type.h"

USING_KANS(DGDB)


DgDb_Hypernode::DgDb_Hypernode(n8 id)
  :  id_(id), dh_type_(nullptr), shm_block_(nullptr) //, shm_block_length_(0)
{

}

u4 DgDb_Hypernode::get_shm_block_size()
{
 if(dh_type_)
   return dh_type_->shm_block_size();
 return 0;
}