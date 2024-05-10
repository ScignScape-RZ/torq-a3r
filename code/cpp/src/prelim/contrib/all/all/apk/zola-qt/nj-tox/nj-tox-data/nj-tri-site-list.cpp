
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "nj-tri-site-list.h"


#include "textio.h"

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"


NJ_TRI_Site_List::NJ_TRI_Site_List(QString file_path)
  :  file_path_(file_path)
{
}

void NJ_TRI_Site_List::read_csv_file(decltype(csv_field_setters_)& mds,
  QString csv_file_path, u4 max)
{
 QList<QStringList> lines = QtCSV::Reader::readToList(csv_file_path);

 if(max)
   sites_.reserve(max);
 else
   sites_.reserve(lines.length());

 original_header_ = lines.takeFirst();

 u4 count = 0;
 for(QStringList line : lines)
 {
  if(line.isEmpty())
    continue;

  ++count;

  if(max && count == max)
    break;

  sites_.push_back({});

  NJ_TRI_Site& site = sites_.last();

  for(u1 column = 0; column < line.size(); ++column)
  {
   auto it = mds.methods.find(column);
   if(it == mds.methods.end())
   {
    auto it1 = mds.non_methods.find(column);
    if(it1 != mds.non_methods.end())
      (**it1)(line[column]);
   }
   else
   {
    (site.**it)(line[column]);
   }
  }

 }


}
