
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "chasm-rz-frame.h"

#include "kernel/graph/chasm-rz-node.h"

#include "rzns.h"

#include <QDebug>


USING_RZNS(RZ_Core)

ChasmRZ_Frame::ChasmRZ_Frame()
 : node_frame<ChasmRZ_Dominion>()
{


}

ChasmRZ_Frame& ChasmRZ_Frame::instance()
{
 static ChasmRZ_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new ChasmRZ_Frame;
 return *the_instance;
}
