
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef CHTR_ASG_POSITION__H
#define CHTR_ASG_POSITION__H

#include "accessors.h"
#include "flags.h"


#include "kernel/graph/chtr-node.h"
#include "kernel/query/chtr-query.h"

//#include "tuple/chasm-rz-tuple-info.h"
//#include "code/chasm-rz-function-def-kinds.h"

#include <QList>
#include <QStack>
#include <QMap>
#include <QVector>

#include "aqns.h"

AQNS_(Chasm_TR)

class ChTR_Graph_Build;

//class ChasmRZ_Token;
//class ChasmRZ_Graph_Build;
//class ChasmRZ_Sentence;
//class ChasmRZ_Sentence_Part;
//class ChasmRZ_Tile_Sentence_Handshake;
//class ChasmRZ_Paralexeme;
//class ChasmRZ_Connectors;

class ChTR_ASG_Position
{
public:
 flags_(1)

  bool awaiting_function_def_note:1;
  bool pending_equalizer_value:1;
  bool possible_pending_equalizer_nested_entry:1;
  bool currently_implied_call_entry:1;
  bool if_block_pending_follow:1;
  bool elsif_block_pending_follow:1;
  bool active_type_indicator_node:1;
  bool holding_retval_node:1;
 _flags


 enum class Position_States {

  Root, Prep_Casement_Sequence,


  Active_Run_Casement_Node, Active_Run_Casement_Chief,

  Active_Run_Token, Active_Run_Chief,
  End_Of_Logical_Scope, Data_Entry,
  Run_Cross_Sequence, Run_Pchasm_rz_Entry, Cross_Run_Chief,
  Block_Entry, Cross_Block_Entry, Active_Closed_Do_Entry,



 };

private:

 ChTR_Node* root_node_;

 caon_ptr<ChTR_Node> current_prep_node_;

 Position_States position_state_;
 ChTR_Graph_Build* graph_build_;
// caon_ptr<ChasmRZ_Token>  active_run_token_;

 int current_depth_;

// QStack<caon_ptr<ChasmRZ_Node>> block_chiefs_;
// QStack<caon_ptr<ChasmRZ_Node>> chiefs_;
// QStack<caon_ptr<ChasmRZ_Node>> over_chiefs_;
// QStack<caon_ptr<ChasmRZ_Node>> block_chiefs_ifs_;

// caon_ptr<ChasmRZ_Node> current_tag_entry_node_;
// caon_ptr<ChasmRZ_Node> current_function_def_entry_node_;

// caon_ptr<ChasmRZ_Node> last_pchasm_rz_entry_node_;
// caon_ptr<ChasmRZ_Node> last_statement_entry_node_;
// caon_ptr<ChasmRZ_Node> last_do_map_block_statement_entry_node_;

// caon_ptr<ChasmRZ_Node> type_indicator_node_;

// caon_ptr<ChasmRZ_Node> current_closed_do_entry_node_;
// caon_ptr<ChasmRZ_Node> held_assignment_annotation_node_;

// caon_ptr<ChasmRZ_Call_Entry> current_closed_do_entry();

 void check_append_chief(caon_ptr<ChTR_Node> new_chief);
 void check_pop_chief();

 void check_hold_closed_do_entry();

 caon_ptr<ChTR_Node> pop_chief();

// void check_if_block_non_continue(caon_ptr<ChasmRZ_Token> token);
 void reset_if_block_pending_follow();


 ChTR_Frame& Cf;
 ChTR_Frame& Sf;
 ChTR_Frame& Pf;

 const ChTR_Query& Qy;



public:

 ChTR_ASG_Position(ChTR_Graph_Build* graph_build);

 ACCESSORS(Position_States ,position_state)
 ACCESSORS(ChTR_Node* ,root_node)


//? ACCESSORS(caon_ptr<ChTR_Node> ,current_node)


 void insert_prep_casement_entry_node(caon_ptr<ChTR_Node> macro_node,
   caon_ptr<ChTR_Node> symbol_node);

 void insert_opaque_token(caon_ptr<ChTR_Node> token_node);
 void insert_numeric_literal(caon_ptr<ChTR_Node> literal_node);


};


_AQNS(Chasm_TR)

#endif //CHTR_ASG_POSITION__H

