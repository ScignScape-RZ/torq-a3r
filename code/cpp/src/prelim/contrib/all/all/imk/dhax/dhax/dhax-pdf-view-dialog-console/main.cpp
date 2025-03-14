
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


int main(int argc, char *argv[])
{
 QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
 QString aotfile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out-test.txt";

 QFile outfile(aotfile);
 if (!outfile.open(QIODevice::WriteOnly))
   return 0;

 QTextStream qts(&outfile);


 QString text = KA::TextIO::load_file(aofile);

 QVector<Index_Ref_Group> refs;

 refs.resize(428);

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

  refs[index].entry_id = entry_id.toInt();
  refs[index].type = type;
  refs[index].follow = follow;
  refs[index].supplement = supp;

  QRegularExpression qre0("\\s*\\[([^/]+)/(\\d+)\\]\\s+");
  QRegularExpressionMatch match0 = qre0.match(heading);

  if(match0.hasMatch())
  {
   refs[index].parent_hint = match0.captured(1);
   refs[index].parent_id = match0.captured(2);
   refs[index].heading = heading.mid(match0.capturedEnd());
  }
  else
    refs[index].heading = heading;

  QStringList pp = pages.split(",,");

  for(QString p : pp)
  {
//   QRegularExpression qre1("([\\dlxvi]+)([*-]*)([\\dxvi]*)\\s@([\\w?]+)");
   QRegularExpression qre1("([\\dlxvin*-]+)\\s@([\\w?]+)");
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
    else if(range.contains("n" && range.contains("--")))
    {
     QRegularExpression qre2("(\\d+)--(\\d+)n(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      high = match2.captured(2);
      note_low = match2.captured(3);
      between = "--";
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
     QRegularExpression qre2("(\\d+)([*?-])(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      high = match2.captured(2);
     }
    }
    else
      low = range.simplified();

    refs[index].index_refs.push_back(
       {low, high, between, note_low, note_high, para});
   }
  }
 }
 return 0;
}


int main6(int argc, char *argv[])
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

int main5(int argc, char *argv[])
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


 QApplication qapp(argc, argv);

 Index_Entry_Review_Dialog* ierd = new Index_Entry_Review_Dialog(ifile, bfile, ftp_folder);


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
