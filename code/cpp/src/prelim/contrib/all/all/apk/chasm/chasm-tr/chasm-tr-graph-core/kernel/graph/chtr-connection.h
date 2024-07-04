
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef CHTR_CONNECTION__H
#define CHTR_CONNECTION__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/chtr-dominion.h"

#include <QTextStream>

#include "rzns.h"
#include "accessors.h"

AQNS_(Chasm_TR)

class Run_Call_Entry;
class ChTR_Node;

class ChTR_Connection
{
 caon_ptr<ChTR_Node> chtr_node_;

public:

 ACCESSORS(caon_ptr<ChTR_Node> ,chtr_node)

 ChTR_Connection(caon_ptr<ChTR_Node> chtr_node);



};


_AQNS(Chasm_TR)

#endif //CHTR_CONNECTION__H

