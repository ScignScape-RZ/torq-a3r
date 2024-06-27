
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "chtr-asg-position.h"

#include "chasm-tr-parser/grammar/chtr-graph-build.h"

#include "aqns.h"

USING_AQNS(Chasm_TR)


ChTR_ASG_Position::ChTR_ASG_Position(ChTR_Graph_Build* graph_build)
 : Flags(0), graph_build_(graph_build),
   Cf(ChTR_Frame::instance("casement")),
   Sf(ChTR_Frame::instance("semantic")),
   Pf(ChTR_Frame::instance("prep")),
   Qy(ChTR_Query::instance()),
   position_state_(Position_States::Root),
   root_node_(nullptr)
{
 //root_node_ = graph_build_->get_root_node();
}


void ChTR_ASG_Position::insert_prep_casement_entry_node(caon_ptr<ChTR_Node> macro_node)
{
 switch (position_state_)
 {
 case Position_States::Root:
  {
   root_node_ << Pf/Qy.Prep_Casement_Entry >> macro_node;
  }
  break;
 default:
  break;
 }


}
