
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "chtr-asg-position.h"


#include "aqns.h"

USING_AQNS(Chasm_TR)


ChTR_ASG_Position::ChTR_ASG_Position(ChTR_Graph_Build* graph_build)
 : Flags(0), graph_build_(graph_build),
   Cf(ChTR_Frame::instance("casement")),
   Sf(ChTR_Frame::instance("semantic")),
   Pf(ChTR_Frame::instance("casement")),
   Qy(ChTR_Query::instance())
{
}


