
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_GENERIC_CARRIER__H
#define CHTR_GENERIC_CARRIER__H

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

class ChTR_Generic_Carrier
{

public:


private:

 QString symbol_;


public:

 ChTR_Generic_Carrier(QString symbol);

 ACCESSORS(QString ,symbol)

};

_AQNS(Chasm_TR)

#endif //CHTR_GENERIC_CARRIER__H
