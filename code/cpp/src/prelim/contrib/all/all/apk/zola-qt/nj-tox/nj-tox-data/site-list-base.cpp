
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "site-list-base.h"

_define_setters_data::_define_setters_data()
   : last_column({0, 1, 1}), column_resolver(nullptr), // //z
     current_arg_state(Arg_State::Init),
     hanging_plus_count(0), suspended_plus_count(0),
     froze_pre_arg(0), froze_pre_arg_ptr(nullptr),
     string_options_count(0)
{

}


u2 _calc_3(u2 prior, u1 new_digit)
{
 u1 d100 = (u1)( prior / 100 );
 if(new_digit == d100)
   return prior;

 u1 d10 = (u1)((prior / 10) % 10);
 if(new_digit == d10)
   return prior;

 u1 d1 = prior % 10;
 if(new_digit == d1)
   return prior;

 return prior * 10 + new_digit;
}

u2 _calc_2(u1 prior, u1 new_digit)
{
 u1 d10 = prior / 10;
 if(new_digit == d10)
   return prior;

 u1 d1 = prior % 10;
 if(new_digit == d1)
   return prior;

 return ((u2) prior) * 10 + new_digit;
}


u1 _calc_1(u1 prior, u1 new_digit)
{
 if(prior == new_digit)
   return prior;
 return prior * 10 + new_digit;
}


_define_setters_data::Arg_State _define_setters_data::add_state(Arg_State prior, Arg_State new_state)
{
 u2 nn = (u2) new_state;

 if(nn > 4 || new_state == Arg_State::Init)
 {
  qDebug() << "Unexpected Arg_State at " << __FILE__;
  return prior;
 }

 if(prior == Arg_State::Init)
   return new_state;

 static QMap<QPair<Arg_State, Arg_State>, Arg_State> results;

 auto it = results.find({prior, new_state});

 u2 prior_num = (u2) prior;

 if(it == results.end())
 {
  u2 result;
  if(prior_num > 1000)
    result = prior_num;
  else if(prior_num > 100)
    result = _calc_3(prior_num, nn);
  else if(prior_num > 10)
    result = _calc_2(prior_num, nn);
  else
    result = _calc_1(prior_num, nn);

  results[{prior, new_state}] = (Arg_State) result;
  return (Arg_State) result;
 }

 return *it;
}

void _define_setters_data::get_current_arg(QVector<u2x3>& result)
{
 if(held_arg.isEmpty())
   result = {{last_column.first + 1, 1, 1}}; // //z
 else
   result = held_arg;
}

s4 _define_setters_data::get_current_arg(QVector<u2x3>& result,
  const QVector<QString>& keys,
  std::function<u2(u2)> counts_callback)
{
 if(!column_resolver)
 {
  get_current_arg(result);
  return 0;
 }

 result.resize(keys.size());

 u1 count = 0;

 // //  Returns the number of _distinct_ column_resolver
  //    results, which might potentially be different
  //    than result.size();
 QSet<u2> distinct;

 for(QString key : keys)
 {
  u2 c = column_resolver(QVariant(key));

  result[count] = {c, counts_callback(c)};
  distinct.insert(result[count].first);
  ++count;
 }

 return distinct.size();
}

_define_setters_data::Arg_State _define_setters_data::expand_state(Arg_State prior, Arg_State new_state)
{
 u2 nn = (u2) new_state;
 if( (nn < 5) || (nn > 9) )
 {
  qDebug() << "Unexpected arg state: " << nn << " at " << __FILE__;
  return prior;
 }
 return (Arg_State) (((u2) prior) * 10 + nn);
}


_define_setters_data::Arg_State _define_setters_data::recollapse_state(Arg_State& prior)
{
 u2 pn = (u2) prior;

 u1 d1 = (pn % 10);
 if(d1 > 4)
 {
  pn /= 10;
  prior = (Arg_State) pn;
  return (Arg_State) d1;
 }

 return (Arg_State) 0;
}


void _define_setters_data::reset(const QVector<u2x3>& lc)
{
 reset(lc.isEmpty()? u2x3{0, 1} : lc.last());
}

void _define_setters_data::reset(u2x3 lc)
{
 last_column = lc;
 reset();
}

void _define_setters_data::reset()
{
 current_arg_state = Arg_State::Init;
 held_arg.clear();
 held_range.clear();
 held_pre.clear();
 held_string.clear();
 _range.clear();
 hanging_plus_count = 0;
 suspended_plus_count = 0;
 froze_pre_arg = 0;
 froze_pre_arg_ptr = nullptr;
 n0_overrides.clear();

 //?string_options_count = 0;
}


const QVector<s4>& _define_setters_data::held_range_to_vector(QVector<u2x3>& result)
{
 for(auto pr : held_range)
 {
  s4 min = qMin(pr.first, pr.second);
  s4 max = qMax(pr.first, pr.second);
  s4 index = result.size();
  result.resize(index + max - min + 1);
  _range.resize(max - min + 1);
  for(s4 i = min, r = 0; i <= max; ++i, ++index, ++r)
  {
   _range[r] = i - pr.first;
   result[index] = {i, 1};
  }
 }

 return _range;
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

