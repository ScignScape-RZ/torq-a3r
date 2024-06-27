
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-prep-casement-entry.h"

#include "kernel/graph/chtr-node.h"

#include "aqns.h"

#include <QDebug>



USING_AQNS(Chasm_TR)


ChTR_Prep_Casement_Entry::ChTR_Prep_Casement_Entry(u4 call_id, QString prefix) //caon_ptr<ChTR_Node> parent_entry_node)
 : // Flags(0), call_depth_(0),
// line_number_(0),
// file_id_(0),
// call_id_(call_id),
 ref_node_(nullptr),
 parent_entry_node_(nullptr),
  self_node_(nullptr),
  block_entry_node_(nullptr),
  block_chief_node_(nullptr), block_continue_node_(nullptr),
  prefix_(prefix)
{

// if(!prefix.isEmpty())
// {
//  if(prefix == "\\")
//  {
//   flags.is_deferred = true;
//  }
//  else if(prefix == "`")
//  {
//   flags.is_backquoted = true;
//   flags.no_normalize = true;
//   flags.no_anticipate = true;
//  }
//  else if(prefix == ",")
//  {
//   flags.is_unquoted = true;
//   flags.no_normalize = true;
//   flags.no_anticipate = true;
//  }

// }
}


// // //   After completed first pass graph build:
// // //    If ref_node_ == parent_entry_node_, or nullptr, then this
//           is in tail position.
//          If ref_node_ as ChasmRZ_Call_Entry is this, then this is an
//           expression followed by a nonnested token.
//          Otherwise ref_node_ points to a "sibling" tuple entry.
//
//caon_ptr<ChTR_Prep_Casement_Entry> ChTR_Prep_Casement_Entry::unwind()
//{
// if(parent_entry_node_)
//  return parent_entry_node_->prep_casement_entry();
// return nullptr;
//}

caon_ptr<ChTR_Node> ChTR_Prep_Casement_Entry::get_node()
{
 return self_node_;
}

