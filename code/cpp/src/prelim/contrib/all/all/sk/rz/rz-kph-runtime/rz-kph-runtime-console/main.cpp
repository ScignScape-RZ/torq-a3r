
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifdef HIDE

// //   The purpose of this code is to show several
 //     contexts where pre/post-condition annotations
 //     can clarify details that would otherwise be
 //     merely implicit.
 //
 //     The code builds a map whose keys represents
 //     months (distinguishing different years)
 //     and whose values are strings.  Months are
 //     indexed by number.  The map is then converted
 //     to a vector, extending over a period of
 //     multiple months and supplying a default
 //     value for months whose keys are not present
 //     in the map to begin with.
 //
 //     The presence of a default value indicated
 //     potential for some information to be missing:
 //     a lookup against a map could result in this
 //     value because the provided key is not present,
 //     or because the key is present and actually
 //     maps to that value.  In this case the
 //     lookup() procedure simply returns an
 //     std::pair whose second is -1 if the key is in
 //     fact missing, but we can imagine a kind of
 //     "alternate return channel" which could capture
 //     this value while the "normal" return from
 //     lookup() would just be the mapped value (or a
 //     fallback given as one of lookup()'s parameters).
 //
 //     Meanwhile, the "slogans" data is actually an
 //     ordered map (based on Tessil's implementation:
 //     see https://github.com/Tessil/ordered-map).
 //     Such maps are not (automatically) sorted;
 //     instead, they preserve insertion order.
 //     For illustration, here the map is initialized
 //     alphabetically, rather than chronologically.
 //     However, the procedure to vectorize that map
 //     requires the map to be sorted ahead of time,
 //     which is performed here via a sort() method.
 //
 //     The fact that sort() has been called is therefore
 //     a precondition for the map_to_full_vector()
 //     procedure.  We can imagine sort() returning
 //     some "certificate" value that could subsequently
 //     be passed to map_to_full_vector() as confirmation
 //     that its argument is, indeed, sorted by key.
 //
 //     Another precondition is that the vector
 //     passed by reference to map_to_full_vector()
 //     must have been resized to hold the "correct"
 //     array size: for numeric (int-like) keys,
 //     enough to span the full range of integers
 //     between its min and max (i.e., max - min + 1).
 //     (But -- as a fallback for non-arithmetic key
 //     types -- this procedure just uses one vector
 //     index per key; it does not try to fill in
 //     intermediate positions with default values.)
 //
 //     A couple asserts represent a simple way
 //     to test that these requirements are
 //     fulfilled, but I am speculating on how
 //     "certificate objects" of some kind might
 //     provide more robust guarantees in these cases.

#include <map>
#include <iostream>

#include <tsl/ordered_map.h>

#include <functional>

template<typename MAP_Type, bool S =
  std::is_same<typename MAP_Type::key_type, typename MAP_Type::mapped_type> ::value>
class map_builder;


template<typename MAP_Type>
class _map_builder
{

protected:

 typedef typename MAP_Type::mapped_type mapped_type;
 typedef typename MAP_Type::key_type key_type;


 MAP_Type& the_map;
 const key_type* current_key = nullptr;
 key_type* initial_key = nullptr;

 int insert_count = 0;

 _map_builder(MAP_Type& m)
   : the_map(m) {}

 _map_builder(MAP_Type& m, key_type& k)
   : the_map(m)
 {
  initial_key = new key_type;
  *initial_key = k;
  ++insert_count;
 }

 _map_builder(const _map_builder& rhs)
   : the_map(rhs.the_map), current_key(rhs.current_key),
     insert_count(rhs.insert_count),
     key_callback(rhs.key_callback)
 {

 }

 void read_key(const key_type& k)
 {
  if(key_callback)
    key_callback(k);

  current_key = &k;
  ++insert_count;
 }

 void read_value(const mapped_type& v)
 {
  ++insert_count;
  if(initial_key)
  {
   the_map.insert({*initial_key, v});
   delete initial_key;
  }
  else
    the_map.insert({*current_key, v});
 }

public:
 std::function<void(const key_type&)> key_callback = nullptr;

};



template<typename MAP_Type>
struct map_builder<MAP_Type, true>
   :  _map_builder<MAP_Type>
{
 typedef _map_builder<MAP_Type> base;

 map_builder(MAP_Type& m)
    : base(m)
 {}

 map_builder(MAP_Type& m, typename base::key_type& k)
   : map_builder(m, k) {}

 map_builder(const map_builder<MAP_Type, true>& rhs)
   : base(rhs)
 {

 }



 map_builder operator<<(const typename base::key_type& k)
 {
  if(base::insert_count % 2)
    base::read_value(k);
  else
    base::read_key(k);
  return *this;
 }

};

template<typename MAP_Type>
struct map_builder<MAP_Type, false>
  : _map_builder<MAP_Type>
{
 typedef _map_builder<MAP_Type> base;

 map_builder(MAP_Type& m)
   : base(m) {}

 map_builder(MAP_Type& m, typename base::key_type& k)
   : base(m,k) {}

 map_builder(const map_builder<MAP_Type, false>& rhs)
   : base(rhs)
 {

 }


 map_builder operator<<(const typename base::key_type& k)
 {
  base::read_key(k);
  return *this;
 }

 map_builder operator<<(const typename base::mapped_type& v)
 {
  base::read_value(v);
  return *this;
 }


};


struct _pre_month_of
{
 int month_index;
 int operator()(int year)
 {
  return (year - 2000) * 12 + month_index;
 }
};

_pre_month_of operator ""_of(const char* m, size_t len)
{
 std::string s(m, len);
 static std::map<std::string, int> months {
  {"Jan", 0},
  {"Feb", 1},
  {"Mar", 2},
  {"Apr", 3},
  {"May", 4},
  {"Jun", 5},
  {"Jul", 6},
  {"Aug", 7},
  {"Sep", 8},
  {"Oct", 9},
  {"Nov", 10},
  {"Dec", 11},
 };

 auto it = months.find(s);
 if(it == months.end())
   it = months.begin();
 return _pre_month_of {it->second};
}


template<typename KEY_Type, typename MAPPED_Type, typename T = std::is_arithmetic<KEY_Type>>
struct _sort_and_get_diff;


template<typename MAP_Type>
bool has_been_sorted(const MAP_Type& m)
{
 return true;
}

template<typename KEY_Type, typename MAPPED_Type>
class ordered_map
{
 int sort_count;

 tsl::ordered_map<KEY_Type, MAPPED_Type>* tsl_map = nullptr;

 typedef ordered_map<KEY_Type, MAPPED_Type> Self_type;

public:

 typedef MAPPED_Type mapped_type;

 ~ordered_map() { if(tsl_map) delete tsl_map; }

 ordered_map() : sort_count(0)
 {
  tsl_map = new tsl::ordered_map<KEY_Type, MAPPED_Type>;
 }

 int has_been_sorted() const
 {
  // //   this is just a hack to get some
   //     simplistic test for sort()
   //     having been called.  More
   //     realistically, of course,
   //     altering the collection should
   //     "invalidate" the sort_count,
   //     presumably resetting it to 0.

  return sort_count;
 }

 friend int has_been_sorted(const Self_type& s)
 {
  return s.has_been_sorted();
 }

 auto& the_values_container() { return tsl_map->values_container(); }

 map_builder<tsl::ordered_map<KEY_Type, MAPPED_Type>> builder()
 {
  return map_builder<tsl::ordered_map<KEY_Type, MAPPED_Type>>(*tsl_map);
 }

 template<typename T>
 map_builder<tsl::ordered_map<KEY_Type, MAPPED_Type>> operator <<(T t)
 {
  map_builder<tsl::ordered_map<KEY_Type, MAPPED_Type>> result(*tsl_map, t);

  result.key_callback = [this](const KEY_Type& key)
  {
   // //  for sake of argument, we'll prohibit duplicates
   assert(tsl_map->find(key) == end());
  };

  return result;
 }

 std::pair<const MAPPED_Type&, signed int> lookup(const KEY_Type& key, MAPPED_Type& default_value)
 {
  auto it = tsl_map->find(key);

  if(it == end())
    return {default_value, -1};

  return {it->second, it - begin()};
 }


 void sort()
 {
  ++sort_count;

  if(sort_count > 1)
    // //   assume that anything that could "unsort"
     //     causes sort_count to become 0 again,
     //     so we don't need to repeat the sort
     //     in this case.  We still increment, in
     //     case someone wants to identify where
     //     repeat calls to sort() are coming from.
    return;

  auto new_tsl_map = new tsl::ordered_map<KEY_Type, MAPPED_Type>;

  if(tsl_map)
  {
   int s = tsl_map->size();
   auto& c = tsl_map->values_container();
   std::vector<const KEY_Type*> keys;
   keys.resize(s);
   std::transform(c.begin(), c.end(), keys.begin(), [](const auto& pr)
   {
    return  &pr.first;
   });
   std::sort(keys.begin(), keys.end(), [](auto& lhs, auto& rhs)
   {
    return *lhs < *rhs;
   });
   for(auto k: keys)
   {
    new_tsl_map -> insert({*k, (*tsl_map)[*k]});
   }
   tsl_map = new_tsl_map;
  }
 }

 int sort_and_get_diff()
 {
  sort();
  if constexpr(std::is_arithmetic_v<KEY_Type>)
  {
   return tsl_map->values_container().back().first - tsl_map->values_container().front().first;
  }
  else
  {
   return size();
  }
 }

 auto size() const
 {
  return tsl_map->values_container().size();
 }

 auto begin()
 {
  return tsl_map->begin();
 }

 auto end()
 {
  return tsl_map->end();
 }


 auto begin() const
 {
  return tsl_map->begin();
 }

 auto end() const
 {
  return tsl_map->end();
 }

};

template<typename MAP_Type, typename VEC_Type>
void map_to_full_vector(const MAP_Type& m, VEC_Type& vec,
  const typename MAP_Type::mapped_type& default_value)
{
 assert(has_been_sorted(m));

 // //  This assertion is actually too weak.
  //    We want vec.size() to equal
  //    max - min + 1 if MAP_Type's keys
  //    are numeric.  But this is simpler
  //    and illustrates the point that
  //    some of these assertions should
  //    (well, ideally -- hypothetically) be
  //    confirmed by certificates produced
  //    by called procedures themselves.
 assert(vec.size() >= m.size());

 int i = 0;

 for(auto it = m.begin();;)
 {
  vec[i] = it->second;

  auto it1 = it;
  ++it;
  if(it == m.end())
    break;

  int g2 = it->first;
  int g1 = it1->first;

  int gap = g2 - g1;
  while(gap > 1)
  {
   vec[++i] = default_value;
   --gap;
  }
  ++i;
 }


}

int main()
{
 std::map<int, int> one_three;

  // //  just to test both that map_builder
   //    workd with std::map as well as
   //    tsl::ordered_map and alsp works
   //    with identical key and value
   //    types as well as different ones.
 map_builder<std::map<int, int>>(one_three)
    << 1 << 2
    << 3 << 4;

 assert(has_been_sorted(one_three));


 ordered_map<int, std::string> slogans;
 slogans
    <<  "Aug"_of(2024) << "Too hot"
        // //  uncomment to test non-duplicate keys
        // <<  "Aug"_of(2024) << " (error) "
    <<  "Dec"_of(2023) << "Too cold"
    <<  "Feb"_of(2024) << "Another boring Super Bowl party"
    <<  "Jan"_of(2024) << "Still too cold!"
    <<  "Jul"_of(2024) << "Actually, Born in the USA is not a patriotic song"
    <<  "Mar"_of(2024) << "Bracket busted on the first day again!"
    <<  "May"_of(2024) << "Yeah, I forgot memorial day"
    <<  "Sep"_of(2024) << "I gotta work on labor day"
        ;

 std::string missing = "(not found)";

 std::cout << "An index of -1 means the key was not found:\n\n";

 auto [v1, i1] = slogans.lookup("Jul"_of(2024), missing);
 printf("index %d = %s\n", i1, v1.c_str());

 auto [v2, i2] = slogans.lookup("Jun"_of(2024), missing);
 printf("index %d = %s\n", i2, v2.c_str());

 std::cout << "------------\n\n";

 auto print = [&]
 {
  for(auto [k, v] : slogans)
  {
   printf("key %d = %s\n", k, v.c_str());
  }
 };

 print();

 slogans.sort();

 std::cout << "\nafter sorting:\n";

 print();

 int diff = slogans.sort_and_get_diff();
 std::cout << "\ndiff = " << diff;


 std::vector<std::string> all_slogans;
 all_slogans.resize(diff + 1);

 map_to_full_vector(slogans, all_slogans, "I got nothing ...");

 std::cout << "\nfull:\n";

 for(auto s : all_slogans)
 {
  std::cout << s << "\n";
 }

 return 0;
}




//  @[error] err;
//
//  ; [cert-call] c
//  int m = sorted_diff(foo);
//
//  std::vector<std::string> slogans_vec(m + 1);
//
//  [-> c; assume $d: size_cert(slogans)]
//  map_to_full_vector(slogans_vec, slogans);
//
//

//qDebug() << m;



//#ifdef HIDE

//#include <QDebug>
//#include <QString>

#include <iostream>

// //  The purpose of this code is to
 //    demonstrate an idea for extending
 //    lifetimes of temporary values.
 //
 //    More precisely, to introduce
 //    non-temporary values behind the scenes
 //    whose values *look* like temporaries.
 //
 //    The normal way to extend temporaries'
 //    lifetimes is simply not allow them
 //    to be temporaries: use a local variable
 //    instead, whose lifetime will extend
 //    to the end of the current lexical scope
 //    (as in version_2 and version_3 below).
 //
 //    However, we can imagine scenarios
 //    where we need to initialize the
 //    value at the last possible moment --
 //    as if it were a temporary after all --
 //    this code presents a rather contrived
 //    example where a procedure that
 //    consumes two values whose lifetimes
 //    have to be in sync is itself returned
 //    from a different procedure with a
 //    side-effect that affects the object
 //    whose lifetime must be extended.
 //
 //    Apart from side-effect issues, arguably
 //    for stylistic reasons it would be
 //    preferable *not* to visibly declare
 //    named local variables which are nowhere
 //    used except to pass a value into a
 //    procedure when that value cannot be a
 //    temporary -- in other words, when the
 //    sole purpose of a local variable is
 //    to extend some value's lifetime.
 //
 //    I'm curious whether it is feasible
 //    to introduce some notation that would
 //    "invisibly" add some local variable
 //    similarly to version_4, only without
 //    the alloca, placement new, and
 //    force_dispose actually being
 //    present in the source code -- maybe
 //    some kind of attribute which could
 //    cause the equivalent of that
 //    extra code to be added silently?
 //
 //    In this case the lifetime-extended
 //    object is initialized from the string
 //    "ok4", so maybe some annotation
 //    on that string literal?  The $$ macro
 //    intends to suggest one notation.  In
 //    place of the code as written imagine
 //    instead it just said ` $$ "ok4" ` ...
 //

#define $$


class A_Number
{
 int n_;

public:

 explicit A_Number(int n) : n_(n)
 {
  printf("A_Number = %d (constructor)\n", n_);
 }

 ~A_Number()
 {
  printf("A_Number = %d (destructor)\n", n_);
 }

 int n() const { return n_; }

};



struct Message
{
 int id;
 std::string test;

 Message() : id(get_current_id())
 {
  printf("id = %d (default constructor)\n", id);

  add_secret_message();
 }


 Message(const char* cs) : id(get_current_id()), test(cs)
 {
  printf("id = %d (constructor with literal)\n", id);

  add_secret_message();
 }

 Message(const A_Number& n) :  id(get_current_id())
 {
  printf("id = %d (constructor with number)\n", id);

  test = std::to_string(n.n());
  add_secret_message();
 }

 Message(const Message& m) = delete;

 Message& operator=(const Message& m)
 {
  printf("assignment operator (id = %d, source = %d)\n", id, m.id);
  test = m.test;
  return *this;
 }

 ~Message()
 {
  printf("destructor (id = %d)\n", id);
 }

 void clear()
 {
  test.clear();
 }

 static void activate(std::string secret_message)
 {
  (void) get_secret_message(&secret_message);
 }

 static void deactivate()
 {
  static std::string clear_string;
  (void) get_secret_message(&clear_string);
 }

private:

 void add_secret_message()
 {
  test.append( get_secret_message() );
 }

 static int get_current_id()
 {
  static int current_id = 0;
  return ++current_id;
 }

 static std::string get_secret_message(std::string* reset = nullptr)
 {
  static std::string secret_message;
  if(reset)
  {
   secret_message = *reset;
  }
  return secret_message;
 }

};



auto activate = []()
{
 Message::activate( " (inebriated Swedish moose rescued from fermented-apple tree)");
};

auto deactivate = []()
{
 Message::deactivate();
};



const Message& _test(const Message& m1, const Message& m2)
{
 if(m1.test.empty())
   return m2;

 return m1;
}


auto test = [](auto callback)
{
 callback();

 return &_test;
};

A_Number make_a_number()
{
 static int count = 0;
 ++count;
 return A_Number(count + 100);
}

const A_Number& test1(const A_Number& lhs, const A_Number& rhs)
{
 if(lhs.n() == 0)
   return rhs;

 return lhs;
}


void version_1()
{
 std::cout  << "In version 1 ...\n";

 Message m1 {make_a_number()};

 std::cout  << "m1 = " << m1.test << "\n";

 m1.clear();

 // //  this is deliberately broken: "ok1" will go out of scope
 const Message& m2 = test(activate)(m1, "ok1");
 std::cout  << "m2 = " << m2.test << "\n";

 deactivate();
}


void version_2()
{
 std::cout  << "\nIn version 2 ...\n";

 const A_Number& t1 = test1(A_Number(0), make_a_number());
 const A_Number& n1 = make_a_number();

 Message m1 {test1(A_Number(0), make_a_number())};

 std::cout  << "m1 = " << m1.test << "\n";
 std::cout  << "t1 = " << t1.n() << "\n";
 std::cout  << "n1 = " << n1.n() << "\n";

 m1.clear();


 Message m1a = "ok2";

 // //  Initializing m1a ahead of time ensures
  //    that it's lifetime matches m1, but
  //    this is too soon to register the
  //    side-effect of test(activate)

 const Message& m2 = test(activate)(m1, m1a);
 std::cout  << "m2 = " << m2.test << "\n";

 deactivate();
}


void version_3()
{
 std::cout  << "\nIn version 3 ...\n";

 Message m1;
 Message m1a;

 // //  Here we both ensure m1a has sufficient
  //    lifetime and also reflect the desired
  //    test(activate) side-effect, but at the
  //    cost of additional constructor and
  //    assignment operator calls -- especially
  //    a problem if those too had side-effects

 const Message& m2 = test(activate)(m1, m1a = "ok3");
 std::cout  << "m2 = " << m2.test << "\n";

 deactivate();
}

template<typename T>
void force_dispose(void* ptr)
{
 std::cout << "in force_dispose ...\n";
 static_cast<T*>(ptr)->T::~T();
}

void version_4()
{
 std::cout  << "\nIn version 4 ...\n";

 Message m1;
 void* m1a = alloca(sizeof(Message));

 // //  This is the desired semantics.
  //    The m1a lifetime is extended far enough,
  //    but the Message object is not initialized
  //    until just before it is passed to test_(),
  //    so it does reflect the test(activate)
  //    side-effect.  The problem is that it's ugly.

 const Message& m2 = test(activate)(m1, $$ *new(m1a)Message("ok4") );

 std::cout  << "m2 = " << m2.test << "\n";

 deactivate();

 force_dispose<Message>(m1a);
}

int main()
{
 version_1();
 version_2();
 version_3();
 version_4();

 return 0;
}

// Message m1aa ("ok2");
// Message m1a = Message("ok2");
// Message m1ac = "ok2";
// Message m1ad = Message("ok2");

//#endif

#endif

#ifdef HIDE


#include "rz-graph-visit/rz-graph-visitor-phaon.h"


#include <QtEndian>

#include <QtGlobal>
#include <QtCore>

#include <QDebug>

#include "rzns.h"

#include "rz-graph-core/kernel/document/rz-re-document.h"
#include "rz-graph-core/output/rz-re-pre-normal-lisp.h"

#include "rz-graph-code/prerun/rz-re-prerun-tokens.h"
#include "rz-graph-code/prerun/rz-re-prerun-normalize.h"
#include "rz-graph-code/prerun/rz-re-prerun-anticipate.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"
#include "rz-code-generators/rpi/rpi-output.h"

#include "phr-graph-core/kernel/graph/phr-graph.h"
#include "phr-graph-core/kernel/graph/phr-graph-build.h"

#include "phr-graph-core/output/phr-graph-phr-output.h"
#include "phr-graph-core/kernel/document/phr-graph-document.h"

#include "phr-graph-core/kernel/graph/pgb-ir-build.h"

#include "kans.h"


#include "phaon-ir/phaon-ir.h"

#include "phaon-ir/eval/phr-channel-group-evaluator.h"
#include "phaon-ir/eval/phr-minimal-evaluator.h"

#include "phaon-ir/channel/phr-channel-system.h"

#include <QDebug>


#include "phr-direct-eval/phr-direct-eval.h"

#include <functional>
#include <QDebug>

#include <QRegularExpression>
#include <QRegularExpressionMatch>


USING_RZNS(RZ_Core)

USING_KANS(Phaon)


QString compile_rz(QString file_name)
{
 QString result;

 RE_Document* doc = new RE_Document(file_name);
 doc->parse();

 doc->report_graph(file_name + ".txt");

 RE_Pre_Normal_Lisp prenorm(doc);
 prenorm.output("..prenorm.txt");

 RE_Prerun_Tokens tokens(doc);
 tokens.output("..prenorm2.txt");


 RE_Prerun_Normalize normalize(*doc->graph());


 caon_ptr<RZ_Lisp_Graph_Visitor> visitor = normalize.scan();

 visitor->set_document_directory(doc->local_directory());

 RZ_Graph_Visitor_Phaon visitor_phaon(*visitor);
 RPI_Output rpo(visitor_phaon);

 doc->report_graph(file_name + ".re1.txt");

 RE_Pre_Normal_Lisp prenorm1(doc);
 prenorm1.output("..prenorm1.txt");

 RE_Prerun_Anticipate anticipate(*visitor, doc->local_path() + ".cprs");

 anticipate.scan(nullptr);//[](RZ_Dynamo_Output& rzdo){rzdo.init_top_level_block();});

 anticipate.run_core_pairs_generations();

 PGB_IR_Build pgb(file_name + ".gen.pgb");


 rpo.build_phaon_graph(pgb);

 pgb.generate_file(rpo.step_forms());

 PHR_Graph phg;
 PHR_Graph_Build phgb(phg);

 phgb.load_from_pgb_file(pgb.out_file());
 PHR_Graph_PHR_Output pgo(pgb.out_file() + ".phr");
 pgo.document()->set_graph(&phg);
 pgo.generate();

 return pgb.out_file() + ".phr";

}


extern void local_program(PhaonIR& phr, QString phrf);


PHR_Channel_Group_Evaluator* load_evaluator(PhaonIR& phr, PHR_Channel_Group& pcg)
{
 QString fname = phr.get_first_raw_value_string("fground", pcg);
 if(fname.startsWith('#'))
 {
  PHR_Minimal_Evaluator::Kernal_Operators kop =
    PHR_Minimal_Evaluator::parse_kernel_operator(fname);
  if(kop != PHR_Minimal_Evaluator::Kernal_Operators::N_A)
  {
   PHR_Minimal_Evaluator* result = new PHR_Minimal_Evaluator(phr, pcg);
   result->set_kernel_operator(kop);
   return result;
  }
 }
 return nullptr;
}

void run_phaon(QString phrf)
{
 PHR_Channel_System pcs;

 PhaonIR phr(&pcs);

 phr.set_load_evaluator_fn(&load_evaluator);
 phr.set_direct_eval_fn(&phr_direct_eval);

 local_program(phr, phrf);
 qDebug() << "ok";
}

int main1(int argc, char *argv[])
{
 QString phrf = compile_rz(RZ_KPH_DIR "/t1.rz");

 run_phaon(phrf);

 return 0;
}



#include "ffi.h"


#include <functional>
#include <memory>
#include <typeinfo>
#include <iostream>
#include <stdio.h>
#include <ffi.h>

#include "src/c-callable-closure.hh"

//#include "src/iterate.hpp"


#include "global-types.h"

struct ffis {

 int v1, v2;

 u4 do_ffi(u2 arg2, u4 arg3, r8 arg4);

 u1 ddo_ffi(u2 arg1);
 u1 dddo_ffi(r8 arg1);

};


u1 fdo_ffi(ffis* arg1, u2 arg2, u4 arg3, r8 arg4)
{
 return arg1->do_ffi(arg2, arg3, arg4);
}

u1 ffis::ddo_ffi(u2 arg1)
{
 qDebug() << "this = " << this;
 ffis& a = *(ffis*)this;

 qDebug() << "this v1 = " << a.v1 << ", " << a.v2;
 qDebug() << "arg1 = " << arg1;

 return (u1) arg1;
}

u1 ffis::dddo_ffi(r8 arg1)
{
 qDebug() << "this = " << this;
 ffis& a = *(ffis*)this;

 qDebug() << "this v1 = " << a.v1 << ", " << a.v2;
 qDebug() << "arg1 = " << arg1;

 return (u1) arg1;
}


u4 ffis::do_ffi(//ffis* arg1,
               u2 arg2, u4 arg3, r8 arg4)
{
 // qDebug() << "arg1 = " << arg1;
 // ffis& a = *(ffis*)arg1;

  qDebug() << "arg1 = " << this;
  ffis& a = *(ffis*)this;

  qDebug() << "arg1 = " << a.v1 << ", " << a.v2;
  qDebug() << "arg2 = " << arg2;
  qDebug() << "arg3 = " << arg3;
  qDebug() << "arg4 = " << arg4;


   qint32 i;

   i = (qint32) ((float)a.v1/arg2 + ((float)arg3/(float)arg4));

   qDebug() << "i = " << i;

   return i;
 }


#include "wrap-as-ccallable.h"

#include "dlfcn.h"

#include "kph-test-lib/test-ffi.h"



typedef void(*FFI_GENERIC)(void);

void run_via_ffi(FFI_GENERIC fn, QString info, void** result = nullptr)
{
 qDebug() << "info = " << info;

 QStringList qsl = info.split(' ');
 QString ret = qsl.takeFirst();
 u1 num_args = qsl.takeFirst().toUInt();

 std::vector<ffi_type*> argument_types;
 std::vector<void*> values;
 argument_types.resize(num_args);
 values.resize(num_args);

 ffi_type* ret_type = get_ffi_type_from_string(ret);

 std::vector<u1> hold_for_u1;
 hold_for_u1.resize(num_args);

 std::vector<u2> hold_for_u2;
 hold_for_u2.resize(num_args);

 std::vector<u4> hold_for_u4;
 hold_for_u4.resize(num_args);

 std::vector<n8> hold_for_n8;
 hold_for_n8.resize(num_args);

 std::vector<r8> hold_for_r8;
 hold_for_r8.resize(num_args);

 int c = 0, ct = 0, cv = 0;
 Base_Types current_base_type = Base_Types::N_A;

 for(QString qs : qsl)
 {
  if(c % 2)
  {
   switch (current_base_type)
   {
   case Base_Types::bt_u1: { hold_for_u1[cv] = qs.toUInt(); values[cv] = &hold_for_u1[cv]; } break;
   case Base_Types::bt_u2: { hold_for_u2[cv] = qs.toUInt(); values[cv] = &hold_for_u2[cv]; } break;
   case Base_Types::bt_u4: { hold_for_u4[cv] = qs.toUInt(); values[cv] = &hold_for_u4[cv]; } break;
   case Base_Types::bt_n8: { hold_for_n8[cv] = qs.toULong(); //(quint64) &tests; //
     values[cv] = &hold_for_n8[cv]; } break;
   case Base_Types::bt_r8: { hold_for_r8[cv] = qs.toDouble(); values[cv] = &hold_for_r8[cv]; } break;

   }
   ++c;
   ++cv;
  }
  else
  {
   current_base_type = parse_base_type(qs);
   argument_types[ct] = get_ffi_type_from_base_type(current_base_type);
   ++c;
   ++ct;
  }

 }

 ffi_cif ffi_c_interface;

 u4 retval;

 if(ffi_prep_cif(&ffi_c_interface, FFI_DEFAULT_ABI, num_args,
      ret_type, argument_types.data()) == FFI_OK)
 {
  ffi_call(&ffi_c_interface, FFI_FN(fn), &retval, values.data());
 }


}

//
#include "kph-test-lib/test-ffi.h"

extern "C" {
 void do_test_ffi(u1 val);
}

#include "textio.h"

USING_KANS(TextIO)

int main111()
{
 QString src_file = "/home/nlevisrael/colony/newsletter/january/p1/page-style-odd.tex";
 QString dest_folder = "/home/nlevisrael/colony/newsletter/january/p%1";


 for(int i = 1; i < 20; i += 2)
 {
  qDebug() << "src = " << src_file;
  qDebug() << "dest = " << dest_folder.arg(i);

  QString src = load_file(src_file);
  src.replace("raisebox{6.4pt}", "raisebox{6pt}");

  src.replace("setcounter{hackpage}{1}", "setcounter{hackpage}{%1}"_qt.arg(i));
  save_file_to_folder(src_file, src, dest_folder.arg(i));
 }

}

int strip_pt(QString s)
{
 QStringView sv = s.endsWith("pt")?
   s.leftRef(s.size() - 2) : QStringView(s);

 return std::round(sv.toDouble());
}

QPair<int, int> strip_pt_px(QString s)
{
 QStringView sv = s.endsWith("pt")?
   s.leftRef(s.size() - 2) : QStringView(s);

 QString ss = sv.toString();

 // // we're keeping this a double because of
  //   the 4/3 multiplication ...
 int d = std::round(sv.toDouble());

 return {d, d * (4./3)};
}

//QPair<int, int> pt_to_px(QString s)
//{
// double pt = strip_pt(s);

// return {pt, pt * (4/3)};
//}

int pt_to_px(int i)
{
 return i * (4./3);
}

QString check_escape_strip(QString text)
{
 text.replace("\\%", "%");
 return text;

}

int main1()
{
 //QString ntxh_src = "/home/nlevisrael/colony/newsletter/january/work/p%1/out/p%1.ntxh";

 QString tex_folder = "/home/nlevisrael/colony/newsletter/january/work/p%1";

 QString ntxh_src = tex_folder + "/out/p%1.ntxh";

 QString pdf_file = tex_folder + "/out/p%1.pdf";

 QString cmds = "/home/nlevisrael/colony/newsletter/january/work/sdi-commands.tex";
 QString setup = "/home/nlevisrael/colony/newsletter/january/work/sdi-setup.tex";

 QString svg_folder = "/home/nlevisrael/Downloads/shonda/-colony/newsletter/january/svg1/embed";

// for(int i = 1; i <= 21; ++i)
// {
//  copy_file_to_folder(cmds, tex_folder.arg(i));
//  copy_file_to_folder(setup, tex_folder.arg(i));

////  QString src = ntxh_src.arg(i);
////  QString target = ntxh_src.arg(i);

// }
 //return 0;

 QString dest_folder = "/home/nlevisrael/Downloads/shonda/-colony/newsletter/january/pages1";

 //  width="612pt" height="792pt"

 int svg_height_pt = 792;
 int svg_height_px = pt_to_px(svg_height_pt);

 int text_wrap_x_indent = 9;

#ifdef HIDE

 for(int i = 21; i <= 21; ++i)
 {
  copy_binary_file_to_folder(pdf_file.arg(i), svg_folder + "/../pdfs");


  double scale = 1.75;
  int w = 612;
  int h = 792;


  QString html_file = svg_folder + "/p%1.htm"_qt.arg(i);

  static QString html_text = R"_(
<html>

<style>

:root {
 --scale-factor: %1;
 --bkg: 101, 110, 95;
}

body {
 background: linear-gradient(15deg, rgba(var(--bkg)), rgba(var(--bkg), 0.2) )
}

#scaled-frame {
  zoom: var(--scale-factor);
  -moz-transform: scale(var(--scale-factor));
  -moz-transform-origin: 0 0;
  -o-transform: scale(var(--scale-factor));
  -o-transform-origin: 0 0;
  -webkit-transform: scale(var(--scale-factor));
  -webkit-transform-origin: 0 0;

  border:inset rgba(var(--bkg), 0.1) 1px;

  width: %2pt;
  height: %3pt;

}

#wrap {
  width: %4pt;
  height: %5pt;
  padding: 0;
  overflow: hidden;
}

</style>

<body>


<div id="wrap">
  <iframe id="scaled-frame" src="p%6.svg"></iframe>
</div>

</body>

</html>
)_";


  save_file(html_file,
    html_text
      .arg(scale)
      .arg(w)
      .arg(h)
      .arg(scale * w)
      .arg(scale * h)
      .arg(i)
     );

 }
// return 0;
#endif

 for(int i = 0; i <= 20; ++i)
 {
  //copy_binary_file_to_folder(pdf_file.arg(i), svg_folder + "/../pdfs");


  QString src = ntxh_src.arg(i);

  //QString text = load_file(src);

  QVector<QMap<QString, QString>> reads;
  QMap<QString, QString> fields;


  load_file(src, [&] (QString line)
  {
//   qDebug() << "line = " << line;

   line = line.simplified();
   if(line.isEmpty())
     return 0;

//   QRegularExpression rx("^\\S\\$);
   QRegularExpression rx("(?:^(?<flag>\\S)$)|(?:^(?<field>\\w+):\\s(?<value>.+))");
   QRegularExpressionMatch rxm = rx.match(line);

   if(rxm.hasMatch())
   {
    if(rxm.captured("flag").isEmpty())
    {
     fields[rxm.captured("field")] = check_escape_strip( rxm.captured("value") );
    }
    else if(rxm.captured("flag") == "=")
    {
     reads.push_back(fields);
     fields.clear();
    }
    else if(rxm.captured("flag") == "+")
    {
     fields["id"] = QString::number(reads.length() + 1);
    }
   }

   return 0;
  });

  QString mark_text = "\n\n<!-- mark rectangles -->\n\n";

  QStringList g_texts;
  QStringList r_texts;
  QStringList c_texts;

  for(const QMap<QString, QString>& fields : reads)
  {

   QString popup_text;

   QString p_text = fields.value("p");
   if(p_text.startsWith('^'))
      p_text.replace(0, 1, fields.value("t"));

   QVector<QPair<QString, QString>>
     popup_text_lines = { {p_text, "popup-ts" } };

   QString popup_text_a_line = fields.value("a");

   QString popup_text_after_a;

   if(popup_text_a_line.startsWith("\\$"))
     popup_text_a_line = popup_text_a_line.mid(1);

   int index_for_after_a = popup_text_a_line.indexOf("-/");

   if(index_for_after_a != -1)
   {
    popup_text_after_a = popup_text_a_line.mid(index_for_after_a + 2);
    popup_text_a_line = popup_text_a_line.left(index_for_after_a).trimmed();
   }

   if(popup_text_a_line.startsWith("$"))
   {
    if( (popup_text_a_line.size() == 1) && (index_for_after_a == -1) )
      popup_text_after_a = " [wikipedia]";
    popup_text_a_line.replace(0, 1, "more info ...");
   }

   QString popup_text_a_href = fields.value("h");

   int x_indent = text_wrap_x_indent; // will this ever need to be adjusted per mark?
   static float dy = 1.2; // in em ....

   if(!popup_text_a_line.isEmpty())
   {
    if(popup_text_a_href.isEmpty())
      popup_text_lines.push_back(
      {"<a id='m-a%1' oncontextmenu='handle_a_contextmenu(%1)'"
       " \n class='text-popup-a'>%2</a>"_qt
         .arg(fields["id"]).arg(popup_text_a_line), "popup-a-after"});
    else
      popup_text_lines.push_back(
        {"<a id='m-a%1' oncontextmenu='handle_a_contextmenu(%1)'"
         " \n href='%2' class='text-popup-a'>%3</a>%4"_qt
        .arg(fields["id"])
        .arg(popup_text_a_href)
        .arg(popup_text_a_line)
        .arg(popup_text_after_a)
        , "popup-a-after"});
   }

   float dy_total = dy * popup_text_lines.length();

   for(auto [l, c] : popup_text_lines)
   {
    QString css_class;
    if(!c.isEmpty())
      css_class = " class='%1'"_qt.arg(c);

    popup_text +=
      " <tspan%1 x='%2' dy='%3em'>%4</tspan>\n"_qt
      .arg(css_class)
      .arg(x_indent)
      .arg(dy)
      .arg(l);
   }
//#ifdef HIDE #endif //def HIDE

   static QString g_text = R"_(  <!-- group %1 -->
<g id='m-g%1' class='text-wrapper' transform='translate(%2)'>
<rect width='2' height='2' class='text-rect-blank'
  oncontextmenu='handle_context_menu("m-c%1", event)'
  onmouseout='check_hide_popup_text_from_transient(event)' />
<rect width='2' height='2' class='text-rect-fill'
  onmouseout='check_hide_popup_text_from_transient(event)' />
<text class='popup-text' y='-%3em'>
%4
</text>
</g>
  <!-- end %1 -->
)_";

static QString r_text = R"_(<rect id='m-r%1' fill='url(#Mark-Gradient)'
  class='mark-rect popup-unadjusted' x='%2pt' y='%3pt' width='%4pt' height='%5pt'
  onmouseover='show_popup_text("m-g%1", event)'
  oncontextmenu='handle_context_menu("m-c%1", event)'
  onmouseout='check_hide_popup_text_from_mark_rect(this, "m-g%1", event)'/>
)_";


static QString c_text = R"_(<g class='context-menu-temp' id='m-c%1'
  onmouseout='hide_temp_context_menu(this, "m-g%1")'
  onclick='handle_temp_context_menu_href(this, "m-g%1")'
  onmousemove='quasi_hover_temp_context_menu(this, "m-g%1")' >
<text filter="url(#context-link-bkg)" font-size="12">%2</text>
<text class='foreground' font-size="12">%2</text>
</g>
)_";

   auto [x1pt, x1px] = strip_pt_px(fields["x1"]);
   auto [y1pt, y1px] = strip_pt_px(fields["y1"]);

   auto [x2pt, x2px] = strip_pt_px(fields["x2"]);
   auto [y2pt, y2px] = strip_pt_px(fields["y2"]);

   int bpt = strip_pt(fields["b"]);


   QString js = fields.value("j");
   if(!js.isEmpty())
   {
    QStringList kv = js.split(' ');

    QString current_key;
    for(QString k_or_v : kv)
    {
     if(current_key.isEmpty())
     {
      current_key = k_or_v;
      continue;
     }
     if(current_key == "v")
     {
      int v_adjust = k_or_v.toInt();
      bpt -= v_adjust;
      y1pt += v_adjust;
      y2pt += v_adjust;

      // // so far these aren't actually used ...
      y1px += pt_to_px(v_adjust);
      y2px += pt_to_px(v_adjust);
     }
     if(current_key == "r")
     {
      int r_adjust = k_or_v.toInt();
      x2pt -= r_adjust;
      x2px -= pt_to_px(r_adjust);
     }
    }
   }

   int popup_x_offset = 2; // px units

   int rect_left_padding = 2;
   int rect_right_padding = 0;
   signed int rect_right_adjust = -1;

   int rect_top_padding = 1;
   int rect_bottom_padding = 1;

   int wpt = x2pt - x1pt + rect_left_padding + rect_left_padding
     + rect_right_padding + rect_right_adjust;
   int hpt = bpt + rect_top_padding + rect_bottom_padding;

   int ry_offset = 5;
   int ry = svg_height_pt - y1pt - hpt + ry_offset + rect_top_padding;

   QString tr_xy = "%1, %2"_qt.arg(x2px + popup_x_offset).arg(svg_height_px - y2px
     - ry_offset * 2);

   g_texts.push_back(g_text
     .arg(fields["id"])                // "m-g%1"
     .arg(tr_xy)                       // translate(%2)
     .arg(dy_total)                    // -%3em
     .arg(popup_text)                  // %4 </text>
   );

   r_texts.push_back(r_text
     .arg(fields["id"])                // "m-r%1"
     .arg(x1pt - rect_left_padding)    // x='%2pt'
     .arg(ry)               // y='%3pt'
     .arg(wpt)                         // width='%4pt'
     .arg(hpt)              // height='%5pt'
   );

   if(fields.contains("h"))
     c_texts.push_back(c_text
       .arg(fields["id"])               // "m-c%1"
       .arg(fields["h"])                // %2</text>
     );

  }

  mark_text += r_texts.join("\n") + "\n<!-- end mark rectangles -->"
    "\n\n<!-- text popup groups -->\n\n"
    + g_texts.join("\n") + "\n<!-- end text popup groups -->"
    "\n\n<!-- temp context menus -->\n\n"
    + c_texts.join("\n") + "\n<!-- end temp context menus -->";

  QString top = load_file(svg_folder + "/template-top.txt");
  QString bottom = load_file(svg_folder + "/template-bottom.txt");


  QString outfile = svg_folder + "/p%1.svg"_qt.arg(i);

  save_file(outfile, top.arg(text_wrap_x_indent).arg(i)
    + mark_text + bottom);

 }
}


int main112()
{
 QString src_folder = "/home/nlevisrael/colony/newsletter/january";
 QString dest_folder = "/home/nlevisrael/Downloads/shonda/-colony/newsletter/january/pages1";

 for(int i = 1; i <= 20; ++i)
 {
  QString file = "%1/p%2/out/p%2.pdf"_qt.arg(src_folder).arg(i);

  copy_binary_file_to_folder(file, dest_folder);

 }

}


int main22()
{
 QString folder = "/home/nlevisrael/colony/newsletter/january";


 for(int i = 1; i <= 20; ++i)
 {
  QString sf = "%1/p%2"_qt.arg(folder).arg(i);
  qDebug() << "sf = " << sf;

  //  QString cmd = "cd %1; run-page.sh";
  QString cmd = "/bin/sh";
  QString scr = "run-page.sh";


  QProcess process;

  process.setWorkingDirectory(sf);
  process.setProgram(cmd);
  process.setArguments({scr});

  process.startDetached();
 }
}


int main2()
{
 void* kph_lib = dlopen(T_DIR "/kph-test-lib.so", RTLD_LAZY | RTLD_DEEPBIND);

 void (*fn)(n8) = reinterpret_cast<void (*)(n8)>(dlsym(kph_lib, "init_symbol_dictionary"));

 //fn(43);

 run_via_ffi((FFI_GENERIC)fn, "void 0");// n8 44");

}


int main1()
{

// ffi_function::CCallableClosure<quint32 (ffis*, quint16, quint32, qreal)>
//   bound_ffis_do_ffi(&ffis::do_ffi);

 // ffis tests {121, 210};
// bound_ffis_do_ffi.get_func_ptr()(&tests, 123, 234, 11.8);

 ffis tests {121, 210};



//? QString sargs = "u4 4 n8 ptr u2 1010 u4 9991010 r8 0.913";
 QString args = "u4 4 n8 %1 u2 1010 u4 9991010 r8 0.913"_qt.arg((n8)&tests);
 ffi_type* ret_type;

 std::vector<ffi_type*> arg_types;
 QVector<QString> values;
 QVector<QPair<QString, Base_Types>> type_strings;

 u1 num_args = parse_argument_types(args, ret_type, arg_types, values, type_strings);


#ifdef HIDE
 QStringList qsl = sargs.split(' ');

 QString ret = qsl.takeFirst();
 quint8 mnum_args = qsl.takeFirst().toUInt();

 std::vector<ffi_type*> argument_types;
 std::vector<void*> vvalues;
 argument_types.resize(num_args);
// values.resize(num_args);
 vvalues.resize(num_args);


// ffi_type* argument_types [4];
// void* values [4];


 //?ffi_type* ret_type = get_ffi_type_from_string(ret);

// std::shared_ptr<cctypes::Std_Function_Pointer_type> std_function_ptr
// {
//  new cctypes::Std_Function_Pointer_type{ (cctypes::Std_Function_Pointer_type)  &ffis::do_ffi}
// };


 quint8 hold_for_u1 [4];
 quint16 hold_for_u2 [4];
 quint32 hold_for_u4 [4];
 quint64 hold_for_n8 [4];
 qreal hold_for_r8 [4];

 int c = 0, ct = 0, cv = 0;
 Base_Types current_base_type = Base_Types::N_A;

 for(QString qs : qsl)
 {
  if(c % 2)
  {
   switch (current_base_type)
   {
   case Base_Types::bt_u1: { hold_for_u1[cv] = qs.toUInt(); vvalues[cv] = &hold_for_u1[cv]; } break;
   case Base_Types::bt_u2: { hold_for_u2[cv] = qs.toUInt(); vvalues[cv] = &hold_for_u2[cv]; } break;
   case Base_Types::bt_u4: { hold_for_u4[cv] = qs.toUInt(); vvalues[cv] = &hold_for_u4[cv]; } break;
   case Base_Types::bt_n8: { hold_for_n8[cv] = (quint64) &tests; //qs.toULong();
     vvalues[cv] = &hold_for_n8[cv]; } break;
   case Base_Types::bt_r8: { hold_for_r8[cv] = qs.toDouble(); vvalues[cv] = &hold_for_r8[cv]; } break;

   }
   ++c;
   ++cv;
  }
  else
  {
   current_base_type = parse_base_type(qs);
   argument_types[ct] = get_ffi_type_from_base_type(current_base_type);
   ++c;
   ++ct;
  }

 }

#endif


// typedef CCallable_Types<u4 (ffis*, u2, u4, r8)> cctypes1;

// cctypes::C_Function_Pointer_type* c_function_ptr;
//?

 ffi_cif _ffi_interface;

 auto get_c_function_ptr =
  wrap_as_ccallable<u4 (ffis*, u2, u4, r8)>(_ffi_interface, &ffis::do_ffi, num_args, ret_type, arg_types); //num_args, ret_type, arg_types);

// quint32 rint;
 quint32 rint;
// quint32 rint2;


// rint = tests.do_ffi(12, 345, 67.8);
// qDebug() << "rint = " << rint;

 rint = get_c_function_ptr(&tests, 12, 345, 67.8);
 qDebug() << "rint = " << rint;



 Test_Ffi tf;
 tf.set_val1(11);
 tf.set_val2(22);
 tf.set_val4(44);
 tf.set_valr8(55.5);



 QString args1 = "u4 1 n8 %1"_qt.arg((n8)&tf);
 ffi_type* ret_type1;

 std::vector<ffi_type*> arg_types1;
 QVector<QString> values1;
 QVector<QPair<QString, Base_Types>> type_strings1;

 u1 num_args1 = parse_argument_types(args1, ret_type1, arg_types1, values1, type_strings1);

 ffi_cif _ffi_interface1;

 auto get_c_function_ptr1 =
  wrap_as_ccallable<u4 (Test_Ffi*)>(_ffi_interface1, &Test_Ffi::test_report, num_args1, ret_type1, arg_types1); //num_args, ret_type, arg_types);

// quint32 rint;
 quint32 rint1;
// quint32 rint2;


// rint = tests.do_ffi(12, 345, 67.8);
// qDebug() << "rint = " << rint;

 rint1 = get_c_function_ptr1(&tf);
 qDebug() << "rint1 = " << rint1;





#ifdef HIDE
 cctypes::C_Function_Pointer_type* get_c_function_ptr;

 //?auto gt = [&ffi_interface, num_args, &arg_types, ret_type, &get_c_function_ptr]()

 {
  typedef CCallable_Types<u4 (ffis*, u2, u4, r8)> cctypes;
  //typedef CCallable_Types<quint32 (ffis*)> cctypes;

 // cctypes::C_Function_Pointer_type* c_function_ptr;

 // u4(*c_function_ptr)(ffis*, u2, u4, r8);

  std::shared_ptr<cctypes::Std_Function_Pointer_type> std_function_ptr
  {
   new cctypes::Std_Function_Pointer_type
   {
    (cctypes::Std_Function_Pointer_type)  &ffis::do_ffi
   }
  };


  void* al = ffi_closure_alloc(sizeof(ffi_closure),
  reinterpret_cast<void**>(&get_c_function_ptr));

  ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

  if(closure_descriptor)
  {
   if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
        ret_type, arg_types.data() //&argument_types[0]
                   ) == FFI_OK)
   {
    if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
       &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
static_cast<void*>(std_function_ptr.get()),
reinterpret_cast<void*>(get_c_function_ptr))
        == FFI_OK)
    {
     //c_function_ptr()
    }

   }

  }
 }
 //;

// gt();


 //gt( num_args, ret_type, arg_types, get_c_function_ptr);

// cctypes::C_Function_Pointer_type* get_c_function_ptr = get_cclosure<u4 (ffis*, u2, u4, r8)>
//   ( &ffis::do_ffi, num_args, ret_type, arg_types.data() );



 rint2 = get_c_function_ptr(&tests, 12, 345, 67.8);
 qDebug() << "rint2 = " << rint2;


// u1 num_args, ffi_type* ret_type, std::vector<ffi_type*> arg_types

#endif

#ifdef HIDE

 quint32 rint2;

 ffi_function::CCallableClosure<u4 (ffis*, u2, u4, r8)>
   bound_ffis_do_ffi(&ffis::do_ffi);

 rint2 = bound_ffis_do_ffi.get_func_ptr()(&tests, 12, 345, 67.8);
 qDebug() << "rint2 = " << rint2;


 typedef CCallable_Types<u1 (ffis*, r8)> cctypes;
 cctypes::C_Function_Pointer_type* c_function_ptr;
 std::shared_ptr<cctypes::Std_Function_Pointer_type> std_function_ptr
 {
  new cctypes::Std_Function_Pointer_type
  {
   (cctypes::Std_Function_Pointer_type)  &ffis::dddo_ffi
  }
 };


 void* al = ffi_closure_alloc(sizeof(ffi_closure),
 reinterpret_cast<void**>(&c_function_ptr));

 u1 num_args = 2;
 std::vector<ffi_type*> argument_types {&ffi_type_uint64, &ffi_type_double};

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

 ffi_type* ret_type = &ffi_type_uint8;

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
       ret_type, &argument_types[0]) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                            static_cast<void*>(std_function_ptr.get()),
                            reinterpret_cast<void*>(c_function_ptr))
       == FFI_OK)
   {
    //c_function_ptr()
   }

  }

 }

 u1 r = c_function_ptr(&tests, 123.456);
 qDebug() << "r = " << r;

#endif


 return 0;
}

#ifdef HIDE





template<typename Ps_Signature>
typename CCallable_Types<Ps_Signature>::C_Function_Pointer_type*
get_cclosure(typename CCallable_Types<Ps_Signature>::Std_Function_Pointer_type std_fptr,
  u1 num_args, ffi_type* ret_type, ffi_type** argument_types)//std::vector<ffi_type*>& argument_types)
{
 // typedef CCallable_Types<quint32 (ffis*, quint16, quint32, qreal)> cctypes;
 typedef CCallable_Types<Ps_Signature> cctypes;

 typename cctypes::C_Function_Pointer_type* c_function_ptr;

 std::shared_ptr<typename cctypes::Std_Function_Pointer_type> std_function_ptr
 {
  new typename cctypes::Std_Function_Pointer_type
  {
   (typename cctypes::Std_Function_Pointer_type) std_fptr
  }
 };


 void* al = ffi_closure_alloc(sizeof(ffi_closure),
 reinterpret_cast<void**>(&c_function_ptr));

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

 ffi_cif ffi_interface;

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
       ret_type, argument_types) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                            static_cast<void*>(std_function_ptr.get()),
                            reinterpret_cast<void*>(c_function_ptr))
       == FFI_OK)
   {
    //c_function_ptr()
   }

  }

 }

 return c_function_ptr;

}







int main()
{
 return ffi_function::_main();

}


template<typename FunctionType>
struct CCallable_Types {
 typedef FunctionType C_Function_Pointer_type;
 typedef std::function<FunctionType> Std_Function_Pointer_type;
};

//void run()
//{
// ffi_closure* closure_descriptor = static_cast<ffi_closure*>
//   (ffi_closure_alloc(sizeof(ffi_closure),
//                      reinterpret_cast<void**>(&c_function_pointer)));
//}

#define V_FFI_FN void (*)(void*)

int main()
{
 ffis tests {203, 124};

 //auto gw = gen_wrap(&ffis::do_ffi);

// ffi_function::CCallableClosure<void (void*)>
//     bound_ffis_do_ffi(&ffis::do_ffi);

// quint32 res = bound_ffis_do_ffi.get_func_ptr()(&tests, 123, 124, 125.5);
// qDebug() << "res = " << res;


// ffi_cif cif;
// ffi_type *args[MAX_ARGS];
 void *values[MAX_ARGS];

 std::vector<ffi_type*> argument_types;
// ffi_closure* closure_descriptor;
 ffi_cif ffi_interface;

 argument_types.resize(4);




// ffi_arg rint;
 quint32 rint;

 QString sargs = "u4 4 n8 ptr u2 1010 u4 9991010 r8 0.913";

 QStringList qsl = sargs.split(' ');

 QString ret = qsl.takeFirst();
 quint8 num_args = qsl.takeFirst().toUInt();

 ffi_type* ret_type = get_ffi_type_from_string(ret);

 if(ret_type != &ffi_type_uint32)
 {
  qDebug() << "no";
 }

 quint8 hold_for_u1 [4];
 quint16 hold_for_u2 [4];
 quint32 hold_for_u4 [4];
 quint64 hold_for_n8 [4];
 qreal hold_for_r8 [4];

 int c = 0, ct = 0, cv = 0;
 Base_Types current_base_type = Base_Types::N_A;

 for(QString qs : qsl)
 {
  if(c % 2)
  {
   switch (current_base_type)
   {
   case Base_Types::bt_u1: { hold_for_u1[cv] = qs.toUInt(); values[cv] = &hold_for_u1[cv]; } break;
   case Base_Types::bt_u2: { hold_for_u2[cv] = qs.toUInt(); values[cv] = &hold_for_u2[cv]; } break;
   case Base_Types::bt_u4: { hold_for_u4[cv] = qs.toUInt(); values[cv] = &hold_for_u4[cv]; } break;
   case Base_Types::bt_n8: { hold_for_n8[cv] = (quint64) &tests; //qs.toULong();
     values[cv] = &hold_for_n8[cv]; } break;
   case Base_Types::bt_r8: { hold_for_r8[cv] = qs.toDouble(); values[cv] = &hold_for_r8[cv]; } break;

   }
   ++c;
   ++cv;
  }
  else
  {
   current_base_type = parse_base_type(qs);
   argument_types[ct] = get_ffi_type_from_base_type(current_base_type);
   ++c;
   ++ct;
  }

 }

 /* Initialize the cif */
// CHECK(ffi_prep_cif(&cif, FFI_DEFAULT_ABI, num_args,
//      &ffi_type_uint32, args) == FFI_OK);


 void (*vfn) (void);

// typedef quint32(*func_type)(quint64, quint16, quint32, qreal);
// func_type* fn;

 //FunctionType * c_function_pointer

 typedef CCallable_Types<quint32 (ffis*, quint16, quint32, qreal)> cctypes;

 cctypes::C_Function_Pointer_type* c_function_ptr;
 std::shared_ptr<cctypes::Std_Function_Pointer_type> std_function_ptr;

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>
   (ffi_closure_alloc(sizeof(ffi_closure),
                      reinterpret_cast<void**>(c_function_ptr)));

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
       ret_type, &argument_types[0]) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*c_function_ptr)>::type>,
                            static_cast<void*>(std_function_ptr.get()),
                            reinterpret_cast<void*>(c_function_ptr))
       == FFI_OK)
   {

   }

  }

 }




// (si1, f, d, ld);

//#define FFI_FN_(f) ((void (*)(void))ffis::f)



// ffi_call(&cif, FFI_FN(forward_call<>), &rint, values);
//? ffi_call(&cif, FFI_FN(do_ffi), &rint, values);

//   ffi_call(&ffi_interface, FFI_FN(bound_ffis_do_ffi.get_func_ptr()), &rint, values);


// printf ("%d vs %d\n", (int)rint, floating (si1, f, d, ld));


// QString ff = "ffis::do_ffi";
// quint32 r = forward_call<ffis, quint16, quint32, qreal, quint32>((quint64)&ff, &tests, (quint16) 11, (quint32) 12, (qreal) 13);

// qDebug() << "rint = " << rint;






//  std::function<double (std::string const &, double)> my_fputs_wrapper = my_fputs;
//  ffi_function::CCallableClosure<double (std::string const &, double)>
//    bound_puts(my_fputs_wrapper);

//  qDebug() << bound_puts.get_func_ptr()("Hello world!", 17.5) << "\n";

//  std::function<int & (int, int)> return_ref_test = get_g;
//  ffi_function::CCallableClosure<int & (int, int)>
//    return_ref_test2(return_ref_test);

//  qDebug() << &(return_ref_test2.get_func_ptr()(1,1)) << "\n";
//  qDebug() << &g << "\n";

//  auto l = [](int x, int y, int z) { return x*y*z; };
//  std::function<int (int, int, int)> times = l;
//  ffi_function::CCallableClosure<int (int, int, int)> times2 = times;
//  int (*c_ptr)(int, int, int);
//  c_ptr = times2.get_func_ptr();

//  qDebug() << c_ptr(4,5,7) << "\n";


  return 0;
}


#endif



#ifdef HIDE

struct ffis {

 int v1, v2;

 quint32 do_ffi(quint16 arg2, quint32 arg3, qreal arg4);

};


quint32 do_ffi(ffis* arg1, quint16 arg2, quint32 arg3, qreal arg4)
{
 return arg1->do_ffi(arg2, arg3, arg4);
}

quint32 ffis::do_ffi(//ffis* arg1,
               quint16 arg2, quint32 arg3, qreal arg4)
{
 // qDebug() << "arg1 = " << arg1;
 // ffis& a = *(ffis*)arg1;

  qDebug() << "arg1 = " << this;
  ffis& a = *(ffis*)this;

  qDebug() << "arg1 = " << a.v1 << ", " << a.v2;
  qDebug() << "arg2 = " << arg2;
  qDebug() << "arg3 = " << arg3;
  qDebug() << "arg4 = " << arg4;


   qint32 i;

   i = (qint32) ((float)a.v1/arg2 + ((float)arg3/(float)arg4));

   qDebug() << "i = " << i;

   return i;
 }

#define MAX_ARGS 16

#define CHECK(x) \
   do { \
      if(!(x)){ \
         printf("Check failed:\n%s\n", #x); \
         abort(); \
      } \
   } while(0)


enum class Base_Types { N_A, bt_u1, bt_u2, bt_u4, bt_n8, bt_r8 };

Base_Types parse_base_type(QString str)
{
 static QMap<QString, Base_Types> static_map {{
    {"u1", Base_Types::bt_u1},
    {"u2", Base_Types::bt_u2},
    {"u4", Base_Types::bt_u4},
    {"n8", Base_Types::bt_n8},
    {"r8", Base_Types::bt_r8},
                 }};

 return static_map.value(str, Base_Types::N_A);
}

ffi_type* get_ffi_type_from_base_type(Base_Types bt)
{
 static QMap<Base_Types, ffi_type*> static_map {{
   {Base_Types::N_A, nullptr},
   {Base_Types::bt_u1, &ffi_type_uint8},
   {Base_Types::bt_u2, &ffi_type_uint16},
   {Base_Types::bt_u4, &ffi_type_uint32},
   {Base_Types::bt_n8, &ffi_type_uint64},
   {Base_Types::bt_r8, &ffi_type_longdouble}
                   }};
 return static_map[bt];
}

ffi_type* get_ffi_type_from_string(QString str)
{
 Base_Types bt = parse_base_type(str);
 if(bt == Base_Types::N_A)
   return nullptr;
 return get_ffi_type_from_base_type(bt);
}

/*
quint32 (*f)(quint16 arg2, quint32 arg3, qreal arg4);



template<typename T1, typename T2, typename T3, typename T4, typename ret> //, typename FN_Type>
std::function<ret(T1*, T2, T3, T4)> gen_wrap(ret (T1::*fn)(T2, T3, T4)) //ret(T1::f*)(T2, T3, T4))
{
// typedef ret (*f)(T1*, T2, T3, T4);
// auto f2 = (ret (*)(T1*, T2, T3, T4)) f;


 //ret (*f)(T2, T3, T4);
// f = fn;
 return [fn](T1* a1, T2 a2, T3 a3, T4 a4) { return (a1->*fn)(a2, a3, a4); };
}


template<typename T1, typename T2, typename T3, typename T4, typename ret> //, typename FN_Type>
std::function<ret(T1*, T2, T3, T4)> save_forward(QString fname, std::function<ret(T1*, T2, T3, T4)> fn)
{
 static QMap<QString, std::function<ret(T1*, T2, T3, T4)>> static_map;
 if(fn)
 {
  static_map[fname] = fn;
  return nullptr;
 }
 return static_map.value(fname);

}


template<typename T1, typename T2, typename T3, typename T4, typename ret> //, typename FN_Type>
ret forward_call(quint64 fname, T1* arg1, T2 arg2, T3 arg3, T4 arg4)
{
 std::function<ret(T1*, T2, T3, T4)> fn = save_forward(*(QString*)fname,
   (std::function<ret(T1*, T2, T3, T4)>)nullptr);

 return fn(arg1, arg2, arg3, arg4);
}
*/


int main12(int argc, char *argv[])
{
 ffi_cif cif;
 ffi_type *args[MAX_ARGS];
 void *values[MAX_ARGS];

// ffi_arg rint;
 qint32 rint;

// auto gw = gen_wrap(&ffis::do_ffi);
// save_forward("ffis::do_ffi", gw);

 //auto bdo_ffi = std::bind(ffis::do_ffi, )

// float f;
// signed int si1;
// double d;
// long double ld;

 ffis tests { 12, 113 };

 QString sargs = "u4 4 n8 1234 u2 1010 u4 9991010 r8 0.913";

 QStringList qsl = sargs.split(' ');

 QString ret = qsl.takeFirst();
 quint8 num_args = qsl.takeFirst().toUInt();

 ffi_type* ret_type = get_ffi_type_from_string(ret);

 if(ret_type != &ffi_type_uint32)
 {
  qDebug() << "no";
 }

 quint8 hold_for_u1 [4];
 quint16 hold_for_u2 [4];
 quint32 hold_for_u4 [4];
 quint64 hold_for_n8 [4];
 qreal hold_for_r8 [4];

 int c = 0, ct = 1, cv = 1;
 Base_Types current_base_type = Base_Types::N_A;

 for(QString qs : qsl)
 {
  if(c % 2)
  {
   switch (current_base_type)
   {
//   case Base_Types::N_A: pargs[cv] = nullptr; break;
//   case Base_Types::bt_u1: { arg1 = qs.toUInt(); values[cv] = &arg1; } break;
//   case Base_Types::bt_u2: { arg2 = qs.toUInt(); values[cv] = &arg2; } break;
//   case Base_Types::bt_u4: { arg3 = qs.toUInt(); values[cv] = &arg3; } break;
//   case Base_Types::bt_r8: { arg4 = qs.toUInt(); values[cv] = &arg4; } break;

   case Base_Types::bt_u1: { hold_for_u1[cv] = qs.toUInt(); values[cv] = &hold_for_u1[cv]; } break;
   case Base_Types::bt_u2: { hold_for_u2[cv] = qs.toUInt(); values[cv] = &hold_for_u2[cv]; } break;
   case Base_Types::bt_u4: { hold_for_u4[cv] = qs.toUInt(); values[cv] = &hold_for_u4[cv]; } break;
   case Base_Types::bt_n8: { hold_for_n8[cv] = (quint64) &tests; //qs.toULong();
     values[cv] = &hold_for_n8[cv]; } break;
   case Base_Types::bt_r8: { hold_for_r8[cv] = qs.toDouble(); values[cv] = &hold_for_r8[cv]; } break;

   }
   ++c;
   ++cv;
  }
  else
  {
   current_base_type = parse_base_type(qs);
   args[ct] = get_ffi_type_from_base_type(current_base_type);
   ++c;
   ++ct;
  }

 }

 QString fname = "ffis::do_ffi";
 quint64 _f = (quint64) &fname;

 values[0] = &_f;
 args[0] = &ffi_type_uint64;

 /* Initialize the cif */
// CHECK(ffi_prep_cif(&cif, FFI_DEFAULT_ABI, num_args,
//      &ffi_type_uint32, args) == FFI_OK);

 CHECK(ffi_prep_cif(&cif, FFI_DEFAULT_ABI, num_args + 1,
      ret_type, args) == FFI_OK);


// (si1, f, d, ld);

//#define FFI_FN_(f) ((void (*)(void))ffis::f)



// ffi_call(&cif, FFI_FN(forward_call<>), &rint, values);
// ffi_call(&cif, FFI_FN(gw), &rint, values);

// printf ("%d vs %d\n", (int)rint, floating (si1, f, d, ld));


// QString ff = "ffis::do_ffi";
// quint32 r = forward_call<ffis, quint16, quint32, qreal, quint32>((quint64)&ff, &tests, (quint16) 11, (quint32) 12, (qreal) 13);

// qDebug() << "rint = " << r;

// gw(&tests, 11, 12, 13);

 return 0;
}





int main11(int argc, char *argv[])
{
 ffi_cif cif;
 ffi_type *args[MAX_ARGS];
 void *values[MAX_ARGS];

// ffi_arg rint;
 qint32 rint;

// float f;
// signed int si1;
// double d;
// long double ld;


 quint8 arg1 = 10;
 args[0] = &ffi_type_uint8;
 values[0] = &arg1;

 quint16 arg2 = 1010;
 args[1] = &ffi_type_uint16;
 values[1] = &arg2;

 quint32 arg3 = 9991010;
 args[2] = &ffi_type_uint32;
 values[2] = &arg3;

 qreal arg4 = .9991010;
 args[3] = &ffi_type_longdouble;
 values[3] = &arg4;

 /* Initialize the cif */
 CHECK(ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 4,
      &ffi_type_sint32, args) == FFI_OK);


// (si1, f, d, ld);

 ffi_call(&cif, FFI_FN(do_ffi), &rint, values);

// printf ("%d vs %d\n", (int)rint, floating (si1, f, d, ld));

 qDebug() << "rint = " << rint;

 return 0;
}










----------------




cctypes::C_Function_Pointer_type* c_function_ptr;
//?
{
//
//typedef CCallable_Types<quint32 (ffis*)> cctypes;


// u4(*c_function_ptr)(ffis*, u2, u4, r8);

cctypes::Std_Function_Pointer_type* std_function_ptr
=
 new cctypes::Std_Function_Pointer_type
 {
  (cctypes::Std_Function_Pointer_type)  &ffis::do_ffi
 }
;

// std::shared_ptr<cctypes::Std_Function_Pointer_type> std_function_ptr
// {
//  new cctypes::Std_Function_Pointer_type
//  {
//   (cctypes::Std_Function_Pointer_type)  &ffis::do_ffi
//  }
// };


void* al = ffi_closure_alloc(sizeof(ffi_closure),
reinterpret_cast<void**>(&c_function_ptr));

ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

if(closure_descriptor)
{
 if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
      ret_type, arg_types.data() //&argument_types[0]
                 ) == FFI_OK)
 {
  if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
     &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                           static_cast<void*>(std_function_ptr),//.get()),
                           reinterpret_cast<void*>(c_function_ptr))
      == FFI_OK)
  {
   //c_function_ptr()
  }

 }

}
//?
}





int main4()
{
 qDebug() << "from dir: " << T_DIR;

// Test_Ffi tf;
// tf.set_val1(11);
// tf.set_val2(22);
// tf.set_val4(44);
// tf.set_valr8(10.234);

// u4 retval = tf.test_report();
// qDebug() << "retval = " << retval;


 void* kph_lib = dlopen(T_DIR "/kph-test-lib.so", RTLD_LAZY | RTLD_DEEPBIND);

 void (*fn)(u1) = reinterpret_cast<void (*)(u1)>(dlsym(kph_lib, "do_test_ffi"));

 //fn(43);

// run_via_ffi((FFI_GENERIC)fn, "void 1 u1 44");


// ffis tests {121, 210};
// QString sargs = "u4 4 n8 %1 u2 1010 u4 9991010 r8 11.913"_qt.arg((n8)&tests);
// run_via_ffi((FFI_GENERIC)&fdo_ffi, sargs);


 QString sargs1 = "void 1 u1 191";
// run_via_ffi((FFI_GENERIC)&do_test_ffi, sargs1);
// run_via_ffi((FFI_GENERIC)fn, sargs1);



 Test_Ffi tf;
 tf.set_val1(101);
 tf.set_val2(102);
 tf.set_val4(104);
 tf.set_valr8(105.6789);


 ffis tests {121, 210};
 // QString sargs = "u4 4 n8 %1 u2 1010 u4 9991010 r8 11.913"_qt.arg((n8)&tests);

 QString args = "u4 4 n8 %1 u2 1010 u4 9991010 r8 0.913"_qt.arg((n8)&tests);
 ffi_type* ret_type;

 std::vector<ffi_type*> arg_types;
 QVector<QString> values;
 QVector<QPair<QString, Base_Types>> type_strings;

 u1 num_args = parse_argument_types(args, ret_type, arg_types, values, type_strings);

// arg_types.push_back(&ffi_type_uint64);
// auto fp = get_cclosure<u4 (Test_Ffi*)>(&Test_Ffi::test_report, 1,
//   &ffi_type_uint32, &arg_types[0]);
// u4 fp_retval = fp(&tf);
// qDebug() << "fp retval = " << fp_retval;

  auto fp = get_cclosure<u4 (ffis*, u2, u4, r8)>(&ffis::do_ffi, num_args,
    ret_type, arg_types.data());

  fp(&tests, 123, 456, 78.9);

 // tf.test_report();


 dlclose(kph_lib);

 return 0;

}




int main5()
{
// ffi_function::CCallableClosure<quint32 (ffis*, quint16, quint32, qreal)>
//   bound_ffis_do_ffi(&ffis::do_ffi);

 // ffis tests {121, 210};
// bound_ffis_do_ffi.get_func_ptr()(&tests, 123, 234, 11.8);

 ffis tests {121, 210};

 ffi_cif ffi_interface;

 QString sargs = "u4 4 n8 ptr u2 1010 u4 9991010 r8 0.913";
 QString args = "u4 4 n8 %1 u2 1010 u4 9991010 r8 0.913"_qt.arg((n8)&tests);
 ffi_type* ret_type;

 std::vector<ffi_type*> arg_types;
 QVector<QString> values;
 QVector<QPair<QString, Base_Types>> type_strings;

 u1 num_args = parse_argument_types(args, ret_type, arg_types, values, type_strings);



 QStringList qsl = sargs.split(' ');

 QString ret = qsl.takeFirst();
 //?quint8 num_args = qsl.takeFirst().toUInt();

 std::vector<ffi_type*> argument_types;
 std::vector<void*> vvalues;
 argument_types.resize(num_args);
 values.resize(num_args);


// ffi_type* argument_types [4];
// void* values [4];


 //?ffi_type* ret_type = get_ffi_type_from_string(ret);

// std::shared_ptr<cctypes::Std_Function_Pointer_type> std_function_ptr
// {
//  new cctypes::Std_Function_Pointer_type{ (cctypes::Std_Function_Pointer_type)  &ffis::do_ffi}
// };


 quint8 hold_for_u1 [4];
 quint16 hold_for_u2 [4];
 quint32 hold_for_u4 [4];
 quint64 hold_for_n8 [4];
 qreal hold_for_r8 [4];

 int c = 0, ct = 0, cv = 0;
 Base_Types current_base_type = Base_Types::N_A;

 for(QString qs : qsl)
 {
  if(c % 2)
  {
   switch (current_base_type)
   {
   case Base_Types::bt_u1: { hold_for_u1[cv] = qs.toUInt(); vvalues[cv] = &hold_for_u1[cv]; } break;
   case Base_Types::bt_u2: { hold_for_u2[cv] = qs.toUInt(); vvalues[cv] = &hold_for_u2[cv]; } break;
   case Base_Types::bt_u4: { hold_for_u4[cv] = qs.toUInt(); vvalues[cv] = &hold_for_u4[cv]; } break;
   case Base_Types::bt_n8: { hold_for_n8[cv] = (quint64) &tests; //qs.toULong();
     vvalues[cv] = &hold_for_n8[cv]; } break;
   case Base_Types::bt_r8: { hold_for_r8[cv] = qs.toDouble(); vvalues[cv] = &hold_for_r8[cv]; } break;

   }
   ++c;
   ++cv;
  }
  else
  {
   current_base_type = parse_base_type(qs);
   argument_types[ct] = get_ffi_type_from_base_type(current_base_type);
   ++c;
   ++ct;
  }

 }



 //
 typedef CCallable_Types<quint32 (ffis*, quint16, quint32, qreal)> cctypes;
// typedef CCallable_Types<quint32 (ffis*)> cctypes;

 cctypes::C_Function_Pointer_type* c_function_ptr;

 std::shared_ptr<std::function<quint32(ffis*, quint32, quint32, qreal)>> std_function_ptr
 {
  new std::function<quint32(ffis*, quint32, quint32, qreal)>
  {
   (std::function<quint32(ffis*, quint32, quint32, qreal)>)  &ffis::do_ffi
  }
 };


 void* al = ffi_closure_alloc(sizeof(ffi_closure),
 reinterpret_cast<void**>(&c_function_ptr));

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
       ret_type, &argument_types[0]) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                            static_cast<void*>(std_function_ptr.get()),
                            reinterpret_cast<void*>(c_function_ptr))
       == FFI_OK)
   {
    //c_function_ptr()
   }

  }

 }





 quint32 rint;



// ffi_function::CCallableClosure<quint32 (ffis*, quint16, quint32, qreal)> ffcc(&ffis::do_ffi);

 ffi_cif ffi_c_interface;

//? ffi_call(&ffi_interface, FFI_FN(c_function_ptr), &rint, &values[0]);
// ffi_call(&ffi_interface, FFI_FN(&do_ffi), &rint, &values[0]);


 /* Initialize the cif */
 CHECK(ffi_prep_cif(&ffi_c_interface, FFI_DEFAULT_ABI, num_args,
      ret_type, argument_types.data()) == FFI_OK);

//
// ffi_call(&ffi_c_interface, FFI_FN(c_function_ptr), &rint, values.data());
// ffi_call(&ffi_c_interface, FFI_FN(ffcc.get_func_ptr()), &rint, values.data());
// ffi_call(&ffi_c_interface, FFI_FN(ff), &rint, values.data());


 return 0;
}


template<typename SIG>
void
gg(u1 num_args, ffi_type* ret_type, std::vector<ffi_type*> arg_types,
  typename CCallable_Types<SIG>::C_Function_Pointer_type*& _c_function_ptr)
{
 ffi_cif ffi_interface;

 typedef CCallable_Types<SIG> cctypes;
 //typedef CCallable_Types<quint32 (ffis*)> cctypes;

 typename cctypes::C_Function_Pointer_type* c_function_ptr;

// u4(*c_function_ptr)(ffis*, u2, u4, r8);

// typename cctypes::Std_Function_Pointer_type* std_function_ptr
// =
//  new typename cctypes::Std_Function_Pointer_type
//  {
//   (typename cctypes::Std_Function_Pointer_type)  &ffis::do_ffi
//  }
// ;

 std::shared_ptr<typename cctypes::Std_Function_Pointer_type> std_function_ptr
 {
  new typename cctypes::Std_Function_Pointer_type
  {
   (typename cctypes::Std_Function_Pointer_type)  &ffis::do_ffi
  }
 };


 void* al = ffi_closure_alloc(sizeof(ffi_closure),
 reinterpret_cast<void**>(&c_function_ptr));

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, num_args,
       ret_type, arg_types.data() //&argument_types[0]
                  ) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                            static_cast<void*>(std_function_ptr.get()),
                            reinterpret_cast<void*>(c_function_ptr))
       == FFI_OK)
   {
    _c_function_ptr = c_function_ptr;
    //c_function_ptr()
   }

  }

 }

 //return c_function_ptr;
}


template<typename SIG>
typename CCallable_Types<SIG>::C_Function_Pointer_type*
ggg (ffi_cif& ffi_interface, typename CCallable_Types<SIG>::Std_Function_Pointer_type fn, u1 _num_args,
  ffi_type* _ret_type, std::vector<ffi_type*>& _arg_types)//u1 _num_args, ffi_type* _ret_type, std::vector<ffi_type*> _arg_types)
{
 typedef CCallable_Types<SIG> cctypes;

 typename cctypes::C_Function_Pointer_type* c_function_ptr;

 //u1 _num_args = num_args;
 //ffi_type* _ret_type = ret_type;
 //std::vector<ffi_type*>& _arg_types = arg_types;
//
//typedef CCallable_Types<quint32 (ffis*)> cctypes;


// u4(*c_function_ptr)(ffis*, u2, u4, r8);

 typename cctypes::Std_Function_Pointer_type* std_function_ptr
 =
 new typename cctypes::Std_Function_Pointer_type
 {
  (typename cctypes::Std_Function_Pointer_type)  fn
 }
 ;

 void* al = ffi_closure_alloc(sizeof(ffi_closure),
reinterpret_cast<void**>(&c_function_ptr));

 ffi_closure* closure_descriptor = static_cast<ffi_closure*>(al);

 if(closure_descriptor)
 {
  if(ffi_prep_cif(&ffi_interface, FFI_DEFAULT_ABI, _num_args,
      _ret_type, _arg_types.data() //&argument_types[0]
                 ) == FFI_OK)
  {
   if(ffi_prep_closure_loc(closure_descriptor, &ffi_interface,
      &ffi_function::binder<typename std::remove_reference<decltype(*std_function_ptr)>::type>,
                           static_cast<void*>(std_function_ptr),//.get()),
                           reinterpret_cast<void*>(c_function_ptr))
      == FFI_OK)
   {
    return c_function_ptr;
   //c_function_ptr()
   }

  }

 }

 return nullptr;
//?
}




#endif





//template<typename KEY_Type, typename MAPPED_Type, bool a = std::is_arithmetic<KEY_Type>::v>
//struct _sort_and_get_diff<KEY_Type, MAPPED_Type,  = std::is_arithmetic<KEY_Type> >;


template<typename KEY_Type, typename MAPPED_Type>
struct _sort_and_get_diff<KEY_Type, MAPPED_Type, std::true_type>
{
 ordered_map<KEY_Type, MAPPED_Type>& the_map;
 int go()
 {
  the_map.sort();
  return the_map.the_values_container().back().first - the_map.the_values_container().front().first;
 }
};

template<typename KEY_Type, typename MAPPED_Type>
struct _sort_and_get_diff<KEY_Type, MAPPED_Type, std::false_type>
{
 ordered_map<KEY_Type, MAPPED_Type>& the_map;
 int go()
 {
  the_map.sort();
  return the_map.the_values_container().size();
 }
};





#endif

