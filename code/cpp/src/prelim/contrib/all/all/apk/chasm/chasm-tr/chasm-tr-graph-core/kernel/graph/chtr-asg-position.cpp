
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
   root_node_(nullptr),
   current_prep_node_(nullptr)
{
 //root_node_ = graph_build_->get_root_node();
}


void ChTR_ASG_Position::hold_null_anchor_macro_node(caon_ptr<ChTR_Node> entry_node,
  caon_ptr<ChTR_Node> macro_node)
{
 CAON_PTR_DEBUG(ChTR_Node ,entry_node)
 CAON_PTR_DEBUG(ChTR_Node ,macro_node)

 switch (position_state_)
 {
 case Position_States::Root:
  root_node_ << Pf/Qy.Prep_Casement_Entry >> entry_node;
  break;

 case Position_States::Prep_Casement_Sequence:
  current_prep_chief_ << Pf/Qy.Prep_Casement_Cross >> entry_node;
  break;

 default:
  break;
 }

 entry_node << Pf/Qy.Prep_Casement_Entry >> macro_node;

 current_prep_chief_ = entry_node;
 current_prep_node_ = macro_node;
 position_state_ = Position_States::Held_Null_Anchor;
}


void ChTR_ASG_Position::insert_prep_casement_entry_node(caon_ptr<ChTR_Node> entry_node,
  caon_ptr<ChTR_Node> macro_node, caon_ptr<ChTR_Node> symbol_node)
{
 CAON_PTR_DEBUG(ChTR_Node ,entry_node)
 CAON_PTR_DEBUG(ChTR_Node ,macro_node)
 CAON_PTR_DEBUG(ChTR_Node ,symbol_node)

 switch (position_state_)
 {
 case Position_States::Root:
  root_node_ << Pf/Qy.Prep_Casement_Entry >> entry_node;
  break;

 case Position_States::Prep_Casement_Sequence:
  current_prep_chief_ << Pf/Qy.Prep_Casement_Cross >> entry_node;
  break;

 default:
  break;
 }

 entry_node << Pf/Qy.Prep_Casement_Entry >> macro_node;

 macro_node << Pf/Qy.Prep_Casement_Sequence >> symbol_node;
 current_prep_node_ = symbol_node;

 current_prep_chief_ = entry_node;

 position_state_ = Position_States::Prep_Casement_Sequence;

}

void ChTR_ASG_Position::insert_numeric_literal(caon_ptr<ChTR_Node> literal_node)
{
 switch (position_state_)
 {
 case Position_States::Prep_Casement_Sequence:
  {
   current_prep_node_ << Pf/Qy.Prep_Casement_Sequence >> literal_node;
  }
  break;
 }


}


void ChTR_ASG_Position::insert_opaque_token(caon_ptr<ChTR_Node> token_node)
{
 CAON_PTR_DEBUG(ChTR_Node ,token_node)
 CAON_PTR_DEBUG(ChTR_Node ,current_prep_node_)

 switch (position_state_)
 {
 case Position_States::Held_Null_Anchor:
  current_prep_node_ << Pf/Qy.Prep_Casement_Entry >> token_node;
  break;

 case Position_States::Prep_Casement_Sequence:
  current_prep_node_ << Pf/Qy.Prep_Casement_Sequence >> token_node;
  break;
 }

 position_state_ = Position_States::Prep_Casement_Sequence;

}


