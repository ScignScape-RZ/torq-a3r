
#include "test-ffi.h"

#include <QDebug>


void** lookup_dictionary_symbol(QString key, void** value)
{
 // // if value is nullptr, it means the caller is looking
  //   to insert something, so insert the key and return a
  //   pointer where they can add a value.  Otherwise,
  //   lookup the key and set *value to the result.

 static QMap<QString, void*>* static_map = new QMap<QString, void*>;

 if(value)
 {
  auto it = static_map->constFind(key);
  if(it == static_map->end())
  {
   *value = nullptr;
   // // here the caller is presumably expecting the key to be found.
    //   If it's not, return the whole map so they could check
    //   what's going on ...
   return (void**) &static_map;
  }
  *value = it.value();
  return nullptr;
 }

 auto it = static_map->insert(key, nullptr);

 if(it == static_map->end())
   return nullptr;

 return &it.value();
}


void init_symbol_dictionary()//quint64 user_data)
{
 qDebug() << "preparing symbol dictionary ...";

// qDebug() << " (user data = " << user_data << ")";

}


extern "C" {

void do_test_ffi(u1 val)
{
 qDebug() << "do test ffi = " << val;

 Test_Ffi tf;
 tf.set_val1(211);
 tf.set_val2(322);
 tf.set_val4(544);
 tf.set_valr8(3310.234);

 u4 retval = tf.test_report();
 qDebug() << "retval = " << retval;
}

}

Test_Ffi::Test_Ffi()
  :  val1_(0), val2_(0), val4_(0), valr8_(0)
{

}

u4 Test_Ffi::test_report()
{
 qDebug() << "val1 = " << val1_;
 qDebug() << "val2 = " << val2_;
 qDebug() << "val4 = " << val4_;
 qDebug() << "valr8 = " << valr8_;

 return val1_ + val2_ + val4_ + valr8_;


}


//int main()
//{

// qDebug() << "OK";

// return 0;
//}
