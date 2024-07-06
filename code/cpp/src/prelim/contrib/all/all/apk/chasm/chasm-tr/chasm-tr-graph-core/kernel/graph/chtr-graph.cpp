
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-graph.h"

#include "code/chtr-scoped-carrier.h"
#include "code/chtr-prep-casement-entry.h"
#include "code/chtr-opaque-token.h"

#include "chtr-connection.h"

#include "chtr-source-file.h"

#include "aqns.h"

USING_AQNS(Chasm_TR)


ChTR_Graph::ChTR_Graph(ChTR_Node* root_node)
  :  root_node_(root_node)
{
 set_user_data(&hypernodes_);
 set_node_add_function([](phaong<pg_t>& _pg, phaong<pg_t>::Hypernode* hn)
 {
  QVector<hypernode_type*>* hh = _pg.user_data_as<QVector<hypernode_type*>>();
  hh->push_back(hn);
 });
}

void ChTR_Graph::report(QTextStream& qts)
{
 if(caon_ptr<ChTR_Source_File> root = root_node_->source_file())
 {
  qts << "Root node: " << root->document_path();
 }
 report_from_node(qts, *root_node_);
}

void ChTR_Graph::report_from_node(QTextStream& qts,
 const ChTR_Node& node, u1 indent)
{
 QString padding(indent, ' ');
 qts << "\n" << padding;
 if(caon_ptr<ChTR_Scoped_Carrier> csc = node.scoped_carrier())
 {
  qts << "[scoped carrier= " << csc->symbol() << "]";
 }
 else if(caon_ptr<ChTR_Prep_Casement_Entry> pce = node.prep_casement_entry())
 {
  CAON_PTR_DEBUG(ChTR_Prep_Casement_Entry ,pce)
  QString extra;
  if(!pce->prefix().isEmpty())
  {
   extra = QString(" (%1) ").arg(pce->prefix());
  }
//  if(pce->flags.no_normalize)
//  {
//   extra += "nn";
//  }
//  if(pce->flags.no_anticipate)
//  {
//   extra += "na";
//  }
  qts << QString("<call %1%2>").arg(pce->call_id()).arg(extra);
 }
// else if(caon_ptr<ChasmRZ_Block_Entry> rbe = node.chasm_rz_block_entry())
// {
//  qts << QString("<block %1:%2>").arg(rbe->block_id()).arg(rbe->nested_depth());
// }
// else if(caon_ptr<ChasmRZ_Tuple_Info> rti = node.chasm_rz_tuple_info())
// {
//  if(rti->is_entry())
//   qts << QString("<data %1 ...>").arg(rti->data_id());
//  else
//   qts << "<... data>";
// }

 else if(caon_ptr<ChTR_Opaque_Token> cot = node.opaque_token())
 {
  qts << QString("<opaque token: %1>").arg(cot->symbol());
 }

 else
 {
  qts << "<<node/" << node.label() << ">>";
 }
  //Run_Data_Entry
 node.each_connection([this, node, &qts, &padding, &indent]
  (const ChTR_Frame& frame, u2 count_in_frame, u2 rest_in_frame,
     const ChTR_Connectors& connector, const ChTR_Node& target, const ChTR_Connection* connection)
 {
  // //   For debugging...
  QString label = node.label();

  if(count_in_frame == 0)
  {
   qts << "\n\n" << padding << "__________ \n" << padding << "| Frame: " << frame.label()
    << "\n" << padding << "|"; // << padding << "|\n";
  }


//  // //  Somehow, this connector is causing trouble
//  if(connector.case_label == ChasmRZ_Connectors_Case_Labels::Run_Fundef_Map_Key_Sequence)
//  {
//   //?return;
//  }

  // //  This connector is tangential ...
//  if(connector.case_label == ChTR_Connectors_Case_Labels::Assignment_Annotation)
//  {
//   qts << "\n" << padding << " (Has connection: " << connector.label() << ")\n";
//   return;
//  }

  // //  This connector loops ...
//  if(connector.case_label == ChTR_Connectors_Case_Labels::Parent_Block_Map)
//  {
//   qts << "\n\n" << padding << "Has connection: " << connector.label() << "\n";
//   return;
//  }

  qts << "\n\n" << padding << "  For connection: " << connector.label() << "\n"
      << padding << "  ==== ";

  if(connection)
  {
   qts << "\n\n" << padding << "  Annotated: \n";

   if(caon_ptr<ChTR_Node> cn = connection->chtr_node())
   {
    qts << " [[" << cn->label() << "]]\n";
   }

   qts << padding << "  ---- ";
  }

  report_from_node(qts, target, indent + 2);
  qts << "\n" << padding << "  ....";

  if(rest_in_frame == 0)
    qts << "\n" << padding << "|\n" << padding << "| ++++ ";



 });

}

