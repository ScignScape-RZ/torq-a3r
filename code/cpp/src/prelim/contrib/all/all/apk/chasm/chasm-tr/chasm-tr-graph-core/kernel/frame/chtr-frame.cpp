
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-frame.h"

#include "kernel/graph/chtr-node.h"

#include "aqns.h"

#include <QDebug>


USING_AQNS(Chasm_TR)

ChTR_Frame::ChTR_Frame(QString label)
  :  //label_(label),
     node_frame<ChTR_Dominion>(label)
{


}

ChTR_Frame& ChTR_Frame::instance(QString label)
{
 static QMap<QString, ChTR_Frame*> instances;

 auto it = instances.find(label);

 if(it == instances.end())
   it = instances.insert(label, new ChTR_Frame(label));

 return **it;




// static ChTR_Frame* the_instance = nullptr;
// if(!the_instance)
//  the_instance = new ChTR_Frame;
// return *the_instance;
}
