
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-node.h"

USING_AQNS(Chasm_TR)


void ChTR_Node::each_connection(std::function<void(const ChTR_Frame& frame,
  u2 count_in_frame, u2 rest_in_frame,
  const ChTR_Connectors& connector,
  const ChTR_Node&, const ChTR_Connection* connection)> fn) const
{
 targets_iterator_type it(targets_);
 while(it.hasNext())
 {
  it.next();
  in_frame_targets_iterator_type iit(it.value());
  u2 count = 0;
  while(iit.hasNext())
  {
   iit.next();
   const ChTR_Connectors& connector = *iit.key();
   const ChTR_Node& target = *iit.value();
   fn(*it.key(), count, it.value().size() - count - 1, connector, target, nullptr);
   ++count;
  }
 }

 annotated_targets_iterator_type ait(annotated_targets_);
 while(ait.hasNext())
 {
  ait.next();
  in_frame_annotated_targets_iterator_type iit(ait.value());
  u2 count = 0;
  while(iit.hasNext())
  {
   iit.next();
   const ChTR_Connectors& connector = *iit.key();
   const ChTR_Connection* connection = iit.value().first.raw_pointer();
   const ChTR_Node& target = *iit.value().second;
   fn(*ait.key(), count, ait.value().size() - count - 1,
     connector, target, connection);
   ++count;
  }
 }

}
