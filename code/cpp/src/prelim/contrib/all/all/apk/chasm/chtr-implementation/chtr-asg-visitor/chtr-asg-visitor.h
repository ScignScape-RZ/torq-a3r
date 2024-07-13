
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_ASG_VISITOR__H
#define CHTR_ASG_VISITOR__H

#include <functional>

//#include "relae-graph/relae-grammar.h"

#include "aqns.h"

#include "global-types.h"


AQNS_(Chasm_TR)


class ChTR_Graph;

class ChTR_ASG_Visitor
{
 ChTR_Graph& graph_;

public:

 ChTR_ASG_Visitor(ChTR_Graph& graph);

 void anticipate(std::function<void()> fn);

 void write_core_pairs(u2 generation, QString& text);
 u2 run_core_pairs(u2 generation);

};

_AQNS(Chasm_TR)


#endif // CHTR_ASG_VISITOR__H
