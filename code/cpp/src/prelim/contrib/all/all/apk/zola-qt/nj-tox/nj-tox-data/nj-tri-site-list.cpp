
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
  :  Site_List_Base(file_path)
{
}

manual_ptr_handles<NJ_TRI_Site_List> NJ_TRI_Site_List::split_by_county(
  QMap<QString, NJ_TRI_Site_List*>& results, QString* file_pattern)
{
 read_csv_file();

 manual_ptr_handles<NJ_TRI_Site_List> result;

 for(const NJ_TRI_Site& site : sites_)
 {
  QString county = site.county();

  auto it = results.find(county);

  NJ_TRI_Site_List* ntsl;

  if(it == results.end())
  {
   QString f;
   if(file_pattern)
   {
    f = file_pattern->arg(county);
   }
   else
     f = file_path_;

   ntsl = new NJ_TRI_Site_List(f);
   results[county] = ntsl;
   result.objs.push_back(ntsl);
  }
  else
    ntsl = results[county];

  ntsl->sites().push_back(site);

 }

 for(NJ_TRI_Site_List* ntsl : results)
 {
  ntsl->sort_sites(
  [](const NJ_TRI_Site& lhs, const NJ_TRI_Site& rhs)
  {
   if(lhs.county() == rhs.county())
     return lhs.frs_id() < rhs.frs_id();

   return lhs.county() < rhs.county();
  }
  );
 }

 return result;
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
