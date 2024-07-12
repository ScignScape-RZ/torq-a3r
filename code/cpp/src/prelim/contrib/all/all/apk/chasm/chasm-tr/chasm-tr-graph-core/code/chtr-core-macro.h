
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_CORE_MACRO__H
#define CHTR_CORE_MACRO__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include <QString>
#include <QMap>

#include "aqns.h"

#include "global-types.h"


AQNS_(Chasm_TR)

//class ChTR_Node;
//class ChasmRZ_Connectors;

class ChTR_Node;

class ChTR_Core_Macro
{

public:


private:

 QString name_;


public:

 ChTR_Core_Macro(QString name);

 ACCESSORS(QString ,name)

};

_AQNS(Chasm_TR)

#endif //CHTR_CORE_MACRO__H
