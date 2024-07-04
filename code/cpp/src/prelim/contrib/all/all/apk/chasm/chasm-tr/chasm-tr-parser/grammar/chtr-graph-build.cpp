
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-graph-build.h"

#include "kernel/frame/chtr-frame.h"

#include "kernel/graph/chtr-graph.h"

#include "kernel/query/chtr-query.h"


#include "chtr-source-file.h"

#include <QMap>

#include "global-types.h"

#include "chasm-tr/chtr-channel-object.h"
#include "chasm-tr/chtr-channel-package.h"
#include "chasm-tr/chtr-code-statement.h"

#include "relae-graph/relae-caon-ptr.h"
#include "relae-graph/relae-node-ptr.h"

#include "chtr-document.h"

#include "chasm-tr-graph-core/code/chtr-prep-casement-entry.h"
#include "chasm-tr-graph-core/code/chtr-scoped-carrier.h"
#include "chasm-tr-graph-core/code/chtr-opaque-token.h"



//?#include "chasm-tr/kernel/dominion/types.h"


USING_AQNS(Chasm_TR)


ChTR_Graph_Build::ChTR_Graph_Build(ChTR_Document* d, ChTR_Parser& p, ChTR_Graph& g)
 : Flags(0)
   ,document_(d)
   ,graph_(g)
   ,parser_(p)
   ,Cf(ChTR_Frame::instance("casement"))
   ,Sf(ChTR_Frame::instance("semantic"))
   ,Pf(ChTR_Frame::instance("prep"))
   ,Qy(ChTR_Query::instance())
   ,asg_position_(this)
   ,held_line_number_(0)
   ,current_context_code_(0)
   ,current_source_type_(nullptr)
   ,current_channel_package_(nullptr)
   ,current_channel_object_(nullptr)
   ,current_code_statement_(nullptr)
   ,current_statement_level_node_(nullptr)
   ,prep_macro_entry_count_(0)
   ,block_entry_count_(0)
   ,tuple_entry_count_(0)
{
 current_source_file_ = new ChTR_Source_File;
}

void ChTR_Graph_Build::init()
{
 ChTR_Channel_Package::set_channel_object_encoder([](ChTR_Channel_Object* cco)
 {
  //caon_ptr<ChTR_Channel_Object> pcco(cco);
  ChTR_Node* node = new ChTR_Node(caon_ptr<ChTR_Channel_Object>(cco));
  return (void*) node;
 });

 ChTR_Channel_Package::set_channel_object_decoder([](void* pv)//  -> ChTR_Channel_Object*
 {
  //caon_ptr<ChTR_Channel_Object> pcco(cco);
  ChTR_Node* node = (ChTR_Node*) pv;
  return node->channel_object().raw_pointer();
 });

 ChTR_Source_File* root_file = new ChTR_Source_File(document_->local_path());

 ChTR_Node* root_node = new ChTR_Node(root_file);

 graph_.set_root_node(root_node);
 asg_position_.set_root_node(root_node);

 current_statement_level_node_ = root_node;

 //graph_.set
}

void ChTR_Graph_Build::read_channel_string(QString channel_string)
{
 ChTR_Channel_Object* cco = new ChTR_Channel_Object(channel_string);

 if(!current_channel_package_)
 {
  current_channel_package_ = new ChTR_Channel_Package;
 }

 if(parse_context_.flags.awaiting_statement_body)
 {
  parse_context_.flags.awaiting_statement_body = false;
  current_code_statement_->set_channel_package(current_channel_package_);
 }

 current_channel_package_->add_channel_object(cco);
 current_channel_object_ = cco;

 parse_context_.flags.active_channel = true;
}


caon_ptr<ChTR_Node> ChTR_Graph_Build::make_new_node(caon_ptr<ChTR_Prep_Casement_Entry> pce)
{
 caon_ptr<ChTR_Node> result = new ChTR_Node(pce);
 RELAE_SET_NODE_LABEL(result, QString("<prep-macro %1>").arg(pce->call_id()));
 return result;
}


caon_ptr<ChTR_Node> ChTR_Graph_Build::make_new_node(caon_ptr<ChTR_Scoped_Carrier> csc)
{
 caon_ptr<ChTR_Node> result = new ChTR_Node(csc);
 RELAE_SET_NODE_LABEL(result, QString("<scoped-carrier %1>").arg(scs->symbol()));
 return result;
}


caon_ptr<ChTR_Node> ChTR_Graph_Build::make_new_node(caon_ptr<ChTR_Opaque_Token> token)
{
 caon_ptr<ChTR_Node> result = new ChTR_Node(token);
 RELAE_SET_NODE_LABEL(result, QString("<opaque-token %1>").arg(token->symbol()));
 return result;
}



caon_ptr<ChTR_Node> ChTR_Graph_Build::new_scoped_carrier_node(QString macro_name)
{
 caon_ptr<ChTR_Scoped_Carrier> new_carrier = new ChTR_Scoped_Carrier(macro_name);

 caon_ptr<ChTR_Node> result = make_new_node(new_carrier);
 return result;
}


caon_ptr<ChTR_Node> ChTR_Graph_Build::new_prep_casement_entry_node(QString macro_name,
  caon_ptr<ChTR_Prep_Casement_Entry> parent_entry)
{
 caon_ptr<ChTR_Prep_Casement_Entry> new_entry = new ChTR_Prep_Casement_Entry(prep_macro_entry_count_);
 ++prep_macro_entry_count_;

 caon_ptr<ChTR_Node> result = make_new_node(new_entry);
 return result;
}

ChTR_Node* ChTR_Graph_Build::get_root_node()
{
 return graph_.root_node();
}


void ChTR_Graph_Build::prepare_carrier_declaration(QString symbol)
{
 caon_ptr<ChTR_Node> macro_node = new_prep_casement_entry_node("type-decl");
 caon_ptr<ChTR_Node> carrier_node = new_scoped_carrier_node(symbol);

 asg_position_.insert_prep_casement_entry_node(macro_node, carrier_node);
}

void ChTR_Graph_Build::prepare_symbol_binding_for_initialization(QString symbol)
{

}

void ChTR_Graph_Build::non_prefixed_symbol(QString symbol)
{
 caon_ptr<ChTR_Opaque_Token> token = new ChTR_Opaque_Token(symbol);

 CAON_PTR_DEBUG(ChTR_Opaque_Token ,token)

 caon_ptr<ChTR_Node> node = make_new_node(token);
 asg_position_.insert_opaque_token(node);


 //asg_position_.insert_

}

void ChTR_Graph_Build::enter_statement_body()
{
 ChTR_Code_Statement* ccs = new ChTR_Code_Statement;

 current_code_statement_ = ccs;
 parse_context_.flags.awaiting_statement_body = true;

 if(current_statement_level_node_ == graph_.root_node())
 {
  ChTR_Node* n = new ChTR_Node(ccs);
  current_statement_level_node_ << Cf/Qy.Root_Sequence >> n;
 }
}

void ChTR_Graph_Build::enter_channel_body()
{
 parse_context_.flags.open_channel_body = true;
}

void ChTR_Graph_Build::leave_channel_body()
{
 parse_context_.flags.open_channel_body = false;
}

void ChTR_Graph_Build::read_carrier_string(QString carrier_string)
{
 current_channel_object_->add_carrier(carrier_string);
}
