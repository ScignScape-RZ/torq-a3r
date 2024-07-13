
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "chtr-prep-prerun-anticipate.h"

#include "../chtr-asg-visitor.h"


#include "textio.h"

USING_AQNS(Chasm_TR)

USING_KANS(TextIO)


ChTR_Prep_Prerun_Anticipate::ChTR_Prep_Prerun_Anticipate(ChTR_ASG_Visitor& visitor
  , QString core_pairs_path)
 : visitor_(visitor), core_pairs_path_(core_pairs_path)
{

}

void ChTR_Prep_Prerun_Anticipate::scan(std::function<void()> fn)
{
 visitor_.anticipate(fn);
}

void ChTR_Prep_Prerun_Anticipate::write_core_pairs(u2 generation)
{
 QString text;
 visitor_.write_core_pairs(generation, text);
 if(!text.isEmpty())
   save_file(QString("%1.%2.txt").arg(core_pairs_path_).arg(generation), text);
}

u2 ChTR_Prep_Prerun_Anticipate::run_core_pairs(u2 generation)
{
 return visitor_.run_core_pairs(generation);
}

void ChTR_Prep_Prerun_Anticipate::run_core_pairs_generations()
{
 u2 g = 0;
 while(true)
 {
  write_core_pairs(g);
  u2 sz = run_core_pairs(g);
  ++g;
  if(g >= sz)
    break;
 }
}

