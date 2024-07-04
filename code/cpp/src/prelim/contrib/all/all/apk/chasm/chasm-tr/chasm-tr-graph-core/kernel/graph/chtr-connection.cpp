
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "chtr-connection.h"


#include "aqns.h"
USING_AQNS(Chasm_TR)

ChTR_Connection::ChTR_Connection(caon_ptr<ChTR_Node> chtr_node)
 : chtr_node_(chtr_node)
{

}
