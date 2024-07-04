
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-opaque-token.h"

#include "kernel/graph/chtr-node.h"

#include "aqns.h"

#include <QDebug>



USING_AQNS(Chasm_TR)


ChTR_Opaque_Token::ChTR_Opaque_Token(QString symbol)
  :  symbol_(symbol)
{

}

