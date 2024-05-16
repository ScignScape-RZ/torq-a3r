
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "site-list-base.h"

_define_setters_data::_define_setters_data()
   : last_column(0), column_resolver(nullptr)
{

}


s4 _define_setters_data::get_current_arg(QVector<u2>& result, const QVector<QString>& keys)
{
 if(!column_resolver)
 {
  get_current_arg(result);
  return 0;
 }

 result.resize(keys.size());

 u1 count = 0;
 for(QString key : keys)
 {
  result[count] = column_resolver(QVariant(key));
 }

 return result.size();

// if(held_arg.isEmpty())
// {
//  {

//  }
//  else
// }
// else
//   result = held_arg;

}


void _define_setters_data::get_current_arg(QVector<u2>& result)
{
 if(held_arg.isEmpty())
   result = {last_column + 1};
 else
   result = held_arg;
}

void _define_setters_data::reset(const QVector<u2>& lc)
{
 reset(lc.first());
}

void _define_setters_data::reset(u2 lc)
{
 last_column = lc;
 reset();
}

void _define_setters_data::reset()
{
 held_arg.clear();
 held_range.clear();
 held_pre.clear();
 held_string.clear();
 _range.clear();
}

const QVector<s4>& _define_setters_data::held_pre_or_range()
{
 if(held_pre.isEmpty())
 {
  for(auto pr : held_range)
  {
   s4 min = qMin(pr.first, pr.second);
   s4 max = qMax(pr.first, pr.second);
   for(s4 i = min; i <= max; ++i)
   {
    _range.push_back(i - pr.first);
   }
  }

  return _range;
 }

 return held_pre;
}

