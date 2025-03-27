
#include "dhax-pdf-view-dialog/paraviews/dhax-pdf-view-dialog.h"
#include "dhax-pdf-view-dialog/pleneviews/view-pdf-frame.h"
#include "dhax-pdf-view-dialog/subwindows/pdf-document-widget.h"

#include <QApplication>

//USING_QSNS(Cy_Mesh)

#include "indexing/m2m.h"

#include "indexing/index-entry-review-dialog.h"

#include "indexing/index-ref.h"


QSet<int>* make_addendum_pages()
{
 QSet<int>* result = new QSet<int>;

 for(int i = 1; i <= 451; ++i)
 {
  if(i < 32)
    continue;

  if(i <= 71)
  {
   result->insert(i);
   continue;
  }

  if(i < 183)
    continue;

  if(i <= 197) //  ch4
  {
   result->insert(i);
   continue;
  }


  if(i < 227)
    continue;

  if(i <= 230) //  ch5
  {
   result->insert(i);
   continue;
  }

  if(i < 269)
    continue;

  if(i <= 287)  //  ch6
  {
   result->insert(i);
   continue;
  }

  if(i < 332)
    continue;

  if(i <= 344) //  ch7
  {
   result->insert(i);
   continue;
  }

//  if(i < 269)
//    continue;

//  if(i < 287)
//  {
//   result->insert(i);
//   continue;
//  }

 }

 return result;

}


QVector<Index_Ref_Group>* make_ref_group_vector(QString file)
{
 QString text = KA::TextIO::load_file(file);

 QVector<Index_Ref_Group>* result = new QVector<Index_Ref_Group>;

 QVector<Index_Ref_Group>& refs = *result;

 // // //
 refs.resize(558);

 QRegularExpression qre("#(\\d+)\\s+\\$([ser])<([^>]+)>([,:.]?)\\s+\\$\\[([^\\]]+)]\\s+\\+\\{([^}]+)\\}"
                        );

// QRegularExpression qre1("#(\\d+)\\s+\\$([ser])<([^>]+)>([,:.])\\s+\\$\\[([^\\]]+)]\\s+" //\\s+\\+\\{([^}]+)\\}"
//                        );



// QRegularExpression qre("<div\\s+class='index-(\\w+)'><span>");


 QRegularExpressionMatchIterator it = qre.globalMatch(text);

 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();

  QString entry_id = match.captured(1);
  QString type = match.captured(2);
  QString heading = match.captured(3);
  QString follow = match.captured(4);
  QString pages = match.captured(5);
  QString supp = match.captured(6);



  int index = entry_id.toInt() - 1;

  if(index >= 449)
    qDebug() << entry_id;

  refs[index].entry_id = entry_id.toInt();
  refs[index].type = type;
  refs[index].follow = follow;
  refs[index].supplement = supp;

  QRegularExpression qre0("\\s*\\[([^/]+)/(\\d+)\\]\\s+");
  QRegularExpressionMatch match0 = qre0.match(heading);

  if(match0.hasMatch())
  {
   refs[index].parent_hint = match0.captured(1);
   refs[index].parent_id = match0.captured(2).toInt();
   refs[index].heading = heading.mid(match0.capturedEnd());
  }
  else
    refs[index].heading = heading;

  QStringList pp = pages.split(",,");

  for(QString p : pp)
  {
//   QRegularExpression qre1("([\\dlxvi]+)([*?-]*)([\\dxvi]*)\\s@([\\w?]+)");
   QRegularExpression qre1("([\\d!lxvin*?-]+)\\s@+([\\w?;]+)");
   QRegularExpressionMatch match1 = qre1.match(p.simplified());

   if(match1.hasMatch())
   {
//    QString low = match1.captured(1);
//    QString between = match1.captured(2);
//    QString high = match1.captured(3);

    QString low, high, between, note_low, note_high ;

    QString range = match1.captured(1);
    QString para = match1.captured(2);

    if(range.contains("nn"))
    {
     QRegularExpression qre2("(\\d+)nn(\\d+)-(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      note_low = match2.captured(2);
      note_high = match2.captured(3);
     }
    }
    else if(range.contains("!n"))
    {
     QRegularExpression qre2("([ivxl]+)!n(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      note_low = match2.captured(2);
     }
    }
    else if(range.contains("n" && range.contains("--")))
    {
     QRegularExpression qre2("(\\d+)([*?-])(\\d+)n(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      between = match2.captured(2);
      high = match2.captured(3);
      note_low = match2.captured(4);
     }
    }
    else if(range.contains("n"))
    {
     QRegularExpression qre2("(\\d+)n(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      note_low = match2.captured(2);
     }
    }
    else if(range.contains("--"))
    {
     QRegularExpression qre2("(\\d+)([*?-]+)(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      between = match2.captured(2);
      high = match2.captured(3);
     }
    }
    else
      low = range.simplified();

    refs[index].index_refs.push_back(
       Index_Ref::from_strings({low, high, between, note_low, note_high, para}));
   }
  }
 }

 return result;

}


int main11(int argc, char *argv[])
{
 QString ifile = "/home/nlevisrael/Downloads/m2m/new/dindex-updated.txt";

 QVector<Index_Entry> ies;
 QString itext = KA::TextIO::load_file(ifile);
 read_index_entries(itext, ies);

 QString ofile = "/home/nlevisrael/Downloads/m2m/new/dindex-test.txt";

 {
  QString otext;
  QTextStream oqts(&otext);

  write_index_entries(ies, oqts);
  KA::TextIO::save_file(ofile, otext);
 }

 return 0;
}




int main10(int argc, char *argv[])
{
 QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 QString ofile = "/home/nlevisrael/Downloads/m2m/dindex-updated.txt";

 QString ifile = "/home/nlevisrael/Downloads/m2m/w_pdf/dindex.txt";
 QVector<Index_Entry> ies;
 QString itext = KA::TextIO::load_file(ifile);
 read_index_entries(itext, ies);

 u2 i = 0;

 for(Index_Ref_Group& g : *refs)
 {
  ++i;

  if(i > 428)
  {
   Index_Entry ie;
   ie.parent_id = 0;
   ie.count_in_parent = 0;
   ie.id = g.entry_id;
   ie.sub_count = 0;
   ie.key = g.heading;
   ies.push_back(ie);
  }

 }

 {
  QString otext;
  QTextStream oqts(&otext);

  write_index_entries(ies, oqts);
  KA::TextIO::save_file(ofile, otext);
 }

 return 0;
}




int main13(int argc, char *argv[])
{
 QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 QString ofile = "/home/nlevisrael/Downloads/m2m/new/dindex-addenda.txt";

 QVector<Index_Entry> ies;

 u2 i = 0;

 for(Index_Ref_Group& g : *refs)
 {
  ++i;

  if(i >= 493)
  {
   Index_Entry ie;
   ie.parent_id = 0;
   ie.count_in_parent = 0;
   ie.id = g.entry_id;
   ie.sub_count = 0;
   ie.key = g.heading;
   ies.push_back(ie);
  }

 }

 {
  QString otext;
  QTextStream oqts(&otext);

  write_index_entries(ies, oqts);
  KA::TextIO::save_file(ofile, otext);
 }

 return 0;
}




int main(int argc, char *argv[])
{
// QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
// QString aotfile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out-test.txt";

//? QString aofile = "/home/nlevisrael/Downloads/m2m/new/all.txt";
 QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda.txt";

 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 //? QString ifile = "/home/nlevisrael/Downloads/m2m/new/dindex-updated.txt";
 QString ifile = "/home/nlevisrael/Downloads/m2m/new/dindex-add.txt";

 QVector<Index_Entry> ies;
 QString itext = KA::TextIO::load_file(ifile);
 read_index_entries(itext, ies);

 QString aotfile = "/home/nlevisrael/Downloads/m2m/new/all-out.html";
 QString aotbfile = "/home/nlevisrael/Downloads/m2m/new/all-out-b.html";

 QFile outfile(aotfile);
 if (!outfile.open(QIODevice::WriteOnly))
   return 0;

 QFile boutfile(aotbfile);
 if (!boutfile.open(QIODevice::WriteOnly))
   return 0;

 QTextStream qts(&outfile);
 QTextStream bqts(&boutfile);

 static QString pre_template = R"(
 <html><head><style>
div {padding-top:11pt; font-size:18pt;}
.ital span {font-style:italic;}
.norm {font-style: normal;}
 </style></head><body>

  )";

 static QString post_template = R"(
 </body></html>
                                )";

 qts << pre_template;
 bqts << pre_template;

 QString held;

 u2 i = 0;
 for(Index_Ref_Group& g : *refs)
 {
  Index_Entry& ie = ies[i];

  ++i;

  if(i == 548)
    qDebug() << i;

  if(!held.isEmpty() && !ie.parent_id)
  {
   bqts << held;
   held.clear();
  }


  if(g.entry_id)
  {
   Index_Entry* parent = g.parent_id? &ies[g.parent_id - 1] : nullptr;
   Index_Ref_Group* pg = g.parent_id? &((*refs)[g.parent_id - 1]) : nullptr;

   QPair<QString, QString> divs = g.to_html_bookstyle(ie, parent, pg);

   QString div = g.to_html(ie);


   if(div.contains(";</span>,"))
   {
    div.replace("&rsquo;</span>,", ",&rsquo;</span>");
   }

   if(divs.first.contains(";</span>,"))
   {
    divs.first.replace("&rdquo;</span>,", ",&rdquo;</span>");
   }

   divs.first.replace("&rdquo;.", ".&rdquo;");

   divs.first.replace(QRegularExpression("\\s+\\.</span>"), ".</span>");
   divs.first.replace(QRegularExpression("\\s+</span>;"), "</span>;");

   divs.first.replace("Munchausen", "M&uuml;nchausen");

   divs.first.replace("'s", "&rsquo;s");


   //?divs.first.replace(QRegularExpression("\\s+;"), ";");
   //divs.first.replace(QRegularExpression("\\.\\s*;"), ";");

   div.replace(QRegularExpression("\\s+\\.</span>"), ".</span>");
   div.replace(QRegularExpression("\\s+</span>;"), "</span>;");

   if(ie.sub_count > 0 && g.type == "e")
   {
    bqts << divs.first.trimmed() << ";";
   }
   else
   {
    bqts << divs.first;
   }

   qts << div;


   if(!divs.second.isEmpty())
     held = divs.second;
  }
  else
  {
//   g.entry_id = i;
//   g.heading = ies[i - 1].key;
//   g.type = "e";

//   qts << g.to_string();
   qDebug() << "Missing: " << g.heading;
  }
 }

 qts << post_template;
 bqts << post_template;

 outfile.close();

 return 0;
}


int main7(int argc, char *argv[])
{
 QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
 QString aotfile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out-test.txt";

 QFile outfile(aotfile);
 if (!outfile.open(QIODevice::WriteOnly))
   return 0;

 QTextStream qts(&outfile);


 QString text = KA::TextIO::load_file(aofile);

 QRegularExpression qre("#(\\d+)\\s+\\$([ser])<([^>]+)>([,:.]?)\\s+\\$\\[([^\\]]+)]\\s+\\+\\{([^}]+)\\}"
                        );

 QRegularExpression qre1("#(\\d+)\\s+\\$([ser])<([^>]+)>([,:.])\\s+\\$\\[([^\\]]+)]\\s+" //\\s+\\+\\{([^}]+)\\}"
                        );



// QRegularExpression qre("<div\\s+class='index-(\\w+)'><span>");


 QRegularExpressionMatchIterator it = qre.globalMatch(text);

 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();

  QString entry_id = match.captured(1);
  QString type = match.captured(2);
  QString heading = match.captured(3);
  QString follow = match.captured(4);
  QString pages = match.captured(5);
  QString supp = match.captured(6);

  if(entry_id == 30)
    qDebug() << entry_id;

  qts << "#" << entry_id << " ";

  qts << "$" << type[0] << "<" << heading << ">"
      << follow << "\n";

  qts << " $[" << pages << "]\n";
  qts << " +{" << supp << "}\n";


//  qts << type << "\n";
//  qts << heading << "\n";
//  qts << follow << "\n";

//  qts << pages << "\n";
//  qts << " += " << supp << "\n";
//  qts << entry_id << "\n";

  qts << "\n";
 }

 outfile.close();

 return 0;


}

int main4(int argc, char *argv[])
{
 QString ifile = "/home/nlevisrael/Downloads/m2m/w_pdf/dindex.txt";
 QString afile = "/home/nlevisrael/Downloads/m2m/w_pdf/all";
 QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";


 QFile outfile(aofile);
 if (!outfile.open(QIODevice::WriteOnly))
   return 0;

 QTextStream qts(&outfile);


 QString text = KA::TextIO::load_file(afile);

 QRegularExpression qre("<div\\s+class='index-(\\w+)'><span>([^<]+)</span>([,:.]?)"
   "\\s*((?:[^<]|<i>|</i>)+?)(?:[.]((?:[^<]|<i>|</i>)+?))?\\s+<span\\s+class='note'>\\s+\\{(\\d+)\\}\\s+</span>\\s+</div>"

 //  "\\s*[^<]+\\s+<span\\s+class='note'>\\s+\\{(\\d+\\}\\s+</span>\\s+</div>"
                        );

// QRegularExpression qre("<div\\s+class='index-(\\w+)'><span>");


 QRegularExpressionMatchIterator it = qre.globalMatch(text);

 QSet<int> ids;

 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();

  QString type = match.captured(1);
  QString heading = match.captured(2);
  QString follow = match.captured(3);
  QString pages = match.captured(4);
  QString supp = match.captured(5);
  QString entry_id = match.captured(6);

  if(supp.isEmpty() && follow == ":")
  {
   supp = pages;
   pages.clear();
  }


  qts << "#" << entry_id << " ";

  qts << "$" << type[0] << "<" << heading << ">"
      << follow << "\n";

  pages.replace(",", " ,,");

  qts << " $[" << pages << "]\n";
  qts << " +{ " << supp << "}\n";


//  qts << type << "\n";
//  qts << heading << "\n";
//  qts << follow << "\n";

//  qts << pages << "\n";
//  qts << " += " << supp << "\n";
//  qts << entry_id << "\n";

  qts << "\n";

  ids.insert(entry_id.toInt());
 }

 for(int i = 1; i <= 428; ++i)
 {
  if(ids.contains(i))
    continue;

  qDebug() << i;


 }

// 13
// 44
// 45
// 46
// 52
// 101
// 102
// 108
// 122
// 133
// 134
// 145
// 148
// 149
// 150
// 151
// 157
// 177
// 194
// 196
// 211
// 317
// 359
// 377
// 389
// 392
// 426


 return 0;


}



int main1(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 QString n1file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes1.txt";

 DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(nullptr, nullptr,
   "/home/nlevisrael/Downloads/m2m/m2m-2003.pdf",
   n1file, 1);

 pvd1->setWindowTitle("Earlier Document");
 pvd1->show();

 qapp.exec();
 return 0;
}

int main6(int argc, char *argv[])
{
 QString ifile = "/home/nlevisrael/Downloads/m2m/w_pdf/dindex.txt";
 QString bfile = "/home/nlevisrael/Downloads/m2m/w_pdf/bookmarks.txt";

 // QString ofile = "/home/nlevisrael/Downloads/m2m/w_pdf/tindex.txt";

 QString n1file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes1.txt";
 QString n2file = "/home/nlevisrael/Downloads/m2m/w_pdf/notes2.txt";

 QString ftp_folder = ROOT_FOLDER "/../ftp/m2m";

// QString otext;
// QTextStream oqts(&otext);

// write_index_entries(index_entries, oqts);
// KA::TextIO::save_file(ofile, otext);

// return 0;

 QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 QApplication qapp(argc, argv);

 Index_Entry_Review_Dialog* ierd = new Index_Entry_Review_Dialog(ifile, bfile, ftp_folder);

 ierd->set_ref_groups(refs);
 ierd->filter_ref_groups();

 DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(ierd, nullptr,
   "/home/nlevisrael/Downloads/m2m/m2m-2003.pdf",
   n1file,
   13, 13);

 pvd1->set_arabic_start(24);
 pvd1->set_roman_end(23);
 pvd1->set_roman_start(1);

 pvd1->setWindowTitle("Earlier Document");
 pvd1->show();

 DHAX_PDF_View_Dialog* pvd2 = new DHAX_PDF_View_Dialog(ierd, pvd1,
   "/home/nlevisrael/Downloads/m2m/Neustein_Lesher_9780197661222_US_BITS.pdf",
   n2file,
   86, 32);

 pvd2->set_arabic_start(86);
 pvd2->set_roman_end(85);
 pvd2->set_roman_start(1);

 QSet<int>* addendum = make_addendum_pages();

 pvd2->set_addendum_pages(addendum);
 ierd->set_addendum_pages(addendum);

 pvd2->setWindowTitle("Later Document");
 pvd2->show();

 ierd->set_earlier_pdf_dialog(pvd1);
 ierd->set_later_pdf_dialog(pvd2);

 ierd->show();

// ierd->reclaim_focus();
// ierd->setWindowFlags(ierd->windowFlags() | Qt::WindowStaysOnTopHint);

 qapp.exec();
 return 0;
}

//ROOT_FOLDER "/../docs/ch6.pdf");
