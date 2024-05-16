
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
 define_setters_data_.column_resolver = [this](QVariant qvar)
 {
  QString key = qvar.toString();
  return (u2) NJ_TRI_Site::parse_offsite_key(key);
 };
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
   auto it = mds.proc_options.find(column);
   if(it != mds.proc_options.end())
   {
    switch(*it)
    {
    case decltype(csv_field_setters_)::Proc_Options::m_QString:
     {
      auto it1 = mds.m_QString.find(column);
      if(it1 != mds.m_QString.end())
        (site.**it1)(line[column]);
     }
     break;

    case decltype(csv_field_setters_)::Proc_Options::m_QString_n0:
     {
      auto it1 = mds.m_QString_n0.find(column);
      if(it1 != mds.m_QString_n0.end() && !line[column].isEmpty())
        (site.**it1)(line[column]);
     }
     break;


    case decltype(csv_field_setters_)::Proc_Options::m_QString_u2:
     {
      auto it1 = mds.m_QString_u2.find(column);
      if(it1 != mds.m_QString_u2.end())
        (site.**it1)(line[column], mds.preset_args_u2.value(column, column));
     }
     break;


    case decltype(csv_field_setters_)::Proc_Options::m_QString_u2_n0:
     {
      auto it1 = mds.m_QString_u2_n0.find(column);
      if(it1 != mds.m_QString_u2_n0.end() && !line[column].isEmpty())
        (site.**it1)(line[column], mds.preset_args_u2.value(column, column));
     }
     break;

    case decltype(csv_field_setters_)::Proc_Options::m_QString_QString:
     {
      auto it1 = mds.m_QString_QString.find(column);
      if(it1 != mds.m_QString_QString.end())
        (site.**it1)(line[column], mds.preset_args_QString.value(column));
     }
     break;

    case decltype(csv_field_setters_)::Proc_Options::m_QString_QString_n0:
     {
      auto it1 = mds.m_QString_QString_n0.find(column);
      if(it1 != mds.m_QString_QString_n0.end() && !line[column].isEmpty())
        (site.**it1)(line[column], mds.preset_args_QString.value(column));
     }
     break;

    case decltype(csv_field_setters_)::Proc_Options::n_QString:
     {
      auto it1 = mds.n_QString.find(column);
      if(it1 != mds.n_QString.end())
        (**it1)(line[column]);
     }
     break;

    case decltype(csv_field_setters_)::Proc_Options::n_QString_u2:
     {
      auto it1 = mds.n_QString_u2.find(column);
      if(it1 != mds.n_QString_u2.end())
        (**it1)(line[column], mds.preset_args_u2.value(column, column));
     }
     break;

    case decltype(csv_field_setters_)::Proc_Options::n_QString_QString:
     {
      auto it1 = mds.n_QString_QString.find(column);
      if(it1 != mds.n_QString_QString.end())
        (**it1)(line[column], mds.preset_args_QString.value(column));
     }
     break;


    }
   }
  }

//    auto it_1 = mds.methods_1.find(column);
//    if(it_1 != mds.methods_1.end())
//      (site.**it_1)(line[column],  mds.methods_1_args.value(column, column));
//    else
//    {
//     auto it_n0 = mds.non_methods_0.find(column);
//     if(it_n0 != mds.non_methods_0.end())
//       (**it_n0)(line[column]);
//     else
//     {
//      auto it_n1 = mds.non_methods_1.find(column);
//      if(it_n1 != mds.non_methods_1.end())
//        (**it_n1)(line[column],  mds.methods_1_args.value(column, column));
//     }
//    }
//   }
//   else
//   {
//    (site.**it_0)(line[column]);
//   }
//  }

 }

}
