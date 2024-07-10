
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_NUMERIC_LITERAL__H
#define CHTR_NUMERIC_LITERAL__H

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

class ChTR_Numeric_Literal
{
public:

 flags_(1)
  bool marked_positive:1;
  bool marked_negative:1;
  bool marked_octal:1;
  bool marked_binary:1;
  bool marked_hexadecimal:1;
 _flags


private:

 QString literal_;


public:

 ChTR_Numeric_Literal(QString literal);

 ACCESSORS(QString ,literal)

};

_AQNS(Chasm_TR)

#endif //CHTR_NUMERIC_LITERAL__H
