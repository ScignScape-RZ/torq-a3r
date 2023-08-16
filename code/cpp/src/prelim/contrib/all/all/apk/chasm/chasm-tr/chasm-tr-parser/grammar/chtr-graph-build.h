
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ChTR_GRAPH_BUILD__H
#define ChTR_GRAPH_BUILD__H

#include "flags.h"

#include "accessors.h"

#include "global-types.h"

#include "grammar/chtr-parse-context.h"

#include "kernel/graph/chtr-graph.h"

#include <QStack>


#include "aqns.h"
AQNS_(Chasm_TR)

class ChTR_Graph;
class ChTR_Node;
class ChTR_Document;
class ChTR_Parser;
class ChTR_Graph;
class ChTR_Relae_Frame;
class ChTR_Relae_Query;


class ChTR_Source_Type;
class ChTR_Source_File;

class ChTR_Channel_Package;
class ChTR_Channel_Object;
class ChTR_Code_Statement;




class ChTR_Graph_Build
{

public:

 flags_(1)
  bool discard_acc:1;
  bool split_acc:1;
  bool array_field:1;
  bool numeric_acc:1;
  bool replace_acc:1;
  bool wildcard_acc:1;
  bool define_replacement:1;
  //bool expecting_field:1;
 _flags

 typedef ChTR_Graph::hypernode_type hypernode_type;
 typedef ChTR_Graph::numeric_index_type numeric_index_type;

private:


 QString acc_;

 ChTR_Parse_Context parse_context_;


 ChTR_Document* document_;
 ChTR_Parser& parser_;
 ChTR_Graph& graph_;

 ChTR_Relae_Frame& fr_;
 const ChTR_Relae_Query& qry_;


 QVector<hypernode_type*> top_level_hypernodes_;

 u2 held_line_number_;
 u1 current_context_code_;

 ChTR_Source_Type* current_source_type_;

 ChTR_Source_File* current_source_file_;

 ChTR_Channel_Package* current_channel_package_;
 ChTR_Channel_Object* current_channel_object_;
 ChTR_Code_Statement* current_code_statement_;

 ChTR_Node* current_statement_level_node_;

public:

 ChTR_Graph_Build(ChTR_Document* d, ChTR_Parser& p, ChTR_Graph& g);

 ACCESSORS__RGET(ChTR_Parse_Context ,parse_context)
 ACCESSORS__RGET(QVector<hypernode_type*> ,top_level_hypernodes)


 void init();

 void enter_statement_body();

 void enter_channel_body();
 void leave_channel_body();

 void read_channel_string(QString channel_string);
 void read_carrier_string(QString carrier_string);


};

_AQNS(Chasm_TR)

#endif
