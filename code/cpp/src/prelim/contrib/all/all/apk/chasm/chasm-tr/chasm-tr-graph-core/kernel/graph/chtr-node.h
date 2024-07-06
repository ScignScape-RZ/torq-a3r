
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_NODE__H
#define CHTR_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "chasm-tr-graph-core/kernel/chtr-dominion.h"

#include "chasm-tr-graph-core/kernel/frame/chtr-frame.h"

#include "phaong/phaong.h"
#include "phaong/phaong-types.h"

#include "global-types.h"


#include <functional>

#include "aqns.h"


AQNS_(Chasm_TR)

class ChTR_Channel_Object;
class ChTR_Connection;
class ChTR_Connectors;


class ChTR_Node : public node_ptr<ChTR_Dominion>
{
public:
 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
//? #define DOMINION_HIDE_NO_NAMESPACE
 #define DOMINION_INNER_NAMESPACE Chasm_TR

 #include "kernel/dominion/types.h"

 #undef DOMINION_TYPE
// #undef DOMINION_HIDE_NO_NAMESPACE
 #undef DOMINION_INNER_NAMESPACE


 void each_connection(std::function<void(const ChTR_Frame& frame,
   u2 count_in_frame, u2 rest_in_frame,
   const ChTR_Connectors& connector,
   const ChTR_Node&, const ChTR_Connection* connection)> fn)  const;


};

_AQNS(Chasm_TR)

#endif
