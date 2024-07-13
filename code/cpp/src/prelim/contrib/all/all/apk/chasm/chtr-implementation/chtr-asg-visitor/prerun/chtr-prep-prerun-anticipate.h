
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CHTR_PREP_PRERUN_ANTICIPATE__H
#define CHTR_PREP_PRERUN_ANTICIPATE__H

#include "accessors.h"
#include "flags.h"

#include "global-types.h"

#include "relae-graph/relae-node-ptr.h"

#include <QString>
#include <QTextStream>
#include <QMap>

#include <functional>

#include "aqns.h"


AQNS_(Chasm_TR)


class ChTR_Node;
class ChTR_Graph;
class ChTR_ASG_Visitor;

class ChTR_Prep_Prerun_Anticipate
{
 ChTR_ASG_Visitor& visitor_;

 QString core_pairs_path_;

public:

 ChTR_Prep_Prerun_Anticipate(ChTR_ASG_Visitor& visitor, QString core_pairs_path);

 void scan(std::function<void()> fn);

 void write_core_pairs(u2 generation);
 u2 run_core_pairs(u2 generation);
 void run_core_pairs_generations();

};

_AQNS(Chasm_TR)

#endif //CHTR_PREP_PRERUN_ANTICIPATE__H
