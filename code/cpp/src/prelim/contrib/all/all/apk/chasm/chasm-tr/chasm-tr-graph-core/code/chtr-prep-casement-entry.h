
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_PREP_CASEMENT_ENTRY__H
#define CHTR_PREP_CASEMENT_ENTRY__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include <QString>
#include <QMap>

#include "aqns.h"

#include "global-types.h"


AQNS_(Chasm_TR)

//class ChTR_Node;
//class ChasmRZ_Connectors;

class ChTR_Node;

class ChTR_Prep_Casement_Entry
{

public:


private:

// quint32 call_depth_;
// quint16 line_number_;
// quint16 file_id_;


 u4 call_id_;

 caon_ptr<ChTR_Node> ref_node_;
 caon_ptr<ChTR_Node> parent_entry_node_;


 caon_ptr<ChTR_Node> self_node_;
 caon_ptr<ChTR_Node> block_entry_node_;
 caon_ptr<ChTR_Node> block_chief_node_;
 caon_ptr<ChTR_Node> block_continue_node_;

 QString prefix_;

 // //   For debug only
 QString debug_text_hint_;

public:

 ChTR_Prep_Casement_Entry(u4 call_id, QString prefix = QString());

 ACCESSORS(caon_ptr<ChTR_Node> ,ref_node)
 ACCESSORS(caon_ptr<ChTR_Node> ,parent_entry_node)

 ACCESSORS(caon_ptr<ChTR_Node> ,self_node)
 ACCESSORS(caon_ptr<ChTR_Node> ,block_entry_node)
 ACCESSORS(caon_ptr<ChTR_Node> ,block_chief_node)
 ACCESSORS(caon_ptr<ChTR_Node> ,block_continue_node)

 ACCESSORS(QString ,prefix)
 ACCESSORS(QString ,debug_text_hint)

//? ACCESSORS(quint16 ,call_depth)
//? ACCESSORS(quint16 ,line_number)
//? ACCESSORS(quint16 ,file_id)

 ACCESSORS__GET(int ,call_id)

// caon_ptr<ChTR_Node> get_parent_entry_node_unwind();
// caon_ptr<ChTR_Node> get_next_entry_node(caon_ptr<ChasmRZ_Call_Entry>& next_call_entry, int& unwind_count);
// caon_ptr<ChasmRZ_Call_Entry> unwind();
// caon_ptr<ChasmRZ_Call_Entry> unwind(int& unwind_count);


 caon_ptr<ChTR_Node> get_next_entry_node();
 caon_ptr<ChTR_Node> get_node();

// void debug_check_entry(const ChasmRZ_Connectors& conn);

};

_AQNS(Chasm_TR)

#endif //CHTR_PREP_CASEMENT_ENTRY__H
