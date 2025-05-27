
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

// QVector<Index_Ref_Group>& refs = *result;
 QVector<Index_Ref_Group>& refs = *result;

 // // //
 refs.resize(623);

 QRegularExpression qre("#(\\d+)\\s+\\$([serv])<([^>]+)>([,:.]?)\\s+\\$\\[([^\\]]+)]\\s+\\+\\{([^}]+)\\}"
                        );

// QRegularExpression qre1("#(\\d+)\\s+\\$([serv])<([^>]+)>([,:.])\\s+\\$\\[([^\\]]+)]\\s+" //\\s+\\+\\{([^}]+)\\}"
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

  if(index == 168)
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
   QRegularExpression qre1("([\\d!lxvin*?-]+)\\s@+([\\w?:;]+)");
   QRegularExpressionMatch match1 = qre1.match(p.simplified());

   if(match1.hasMatch())
   {
//    QString low = match1.captured(1);
//    QString between = match1.captured(2);
//    QString high = match1.captured(3);

    QString low, high, between, note_low, note_high ;

    QString range = match1.captured(1);
    QString para = match1.captured(2);

    if(range.contains("!nn"))
    {
     QRegularExpression qre2("([\\divxl]+)!nn(\\d+)-(\\d+)");
     QRegularExpressionMatch match2 = qre2.match(range.simplified());
     if(match2.hasMatch())
     {
      low = match2.captured(1);
      note_low = match2.captured(2);
      note_high = match2.captured(3);
     }
    }
    else if(range.contains("nn"))
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
     QRegularExpression qre2("([\\divxl]+)!n(\\d+)");
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

QString _par_to_F(QString para)
{
 u2 num = para.mid(2).toInt();

 if(para.startsWith("Pr"))
 {
  if(num >= 49)  // //  grant quote business ,,,
    num += 2;
  else if(num >= 14)
    num += 1;

  return "F5P" + QString::number(num);
 }

 if(para.startsWith("Io"))
 {
  return "F6P" + QString::number(num);
 }

 return "????";

}

QVector<QPair<QStringList, QVector<Index_Ref_Summary>>>* make_review_vector(QVector<Index_Ref_Group>* refs)
{
 QVector<QPair<QStringList, QVector<Index_Ref_Summary>>>* result = new
   QVector<QPair<QStringList, QVector<Index_Ref_Summary>>>;

 QMap<QString, QVector<QPair<u2, Index_Ref>>> rmap;



 for(Index_Ref_Group& g : *refs)
 {
  for(const Index_Ref& ir : g.index_refs)
  {
   for(QString para : ir.paragraph_codes)
   {
    QRegularExpression rxp("(C\\d+P|Pr|Io)(\\d+)");
    QRegularExpressionMatch mp = rxp.match(para);

    if(mp.hasMatch())
      para = mp.captured();

    rmap[para].push_back({g.entry_id, ir});
   }
  }
 }

 QVector<QString> keys = rmap.keys().toVector();

 result->resize(keys.size());

 std::sort(keys.begin(), keys.end(), [](QString lhs, QString rhs)
 {
  QRegularExpression rx("(C(\\d+)P|Pr|Io)(\\d+)");
  QRegularExpressionMatch ml = rx.match(lhs);
  QRegularExpressionMatch mr = rx.match(rhs);

  u1 lch = 0, rch = 0, lpar = 0, rpar = 0;

  if(ml.hasMatch())
  {
   QString c1 = ml.captured(1);
   QString c2 = ml.captured(2);
   QString c3 = ml.captured(3);

   if(c1.startsWith("C"))
     lch = c2.toInt() + 2;
   else if(c1 == "Pr")
     lch = 1;
   else if(c1 == "Io")
     lch = 2;

   lpar = c3.toInt();
  }

  if(mr.hasMatch())
  {
   QString c1 = mr.captured(1);
   QString c2 = mr.captured(2);
   QString c3 = mr.captured(3);

   if(c1.startsWith("C"))
     rch = c2.toInt() + 2;
   else if(c1 == "Pr")
     rch = 1;
   else if(c1 == "Io")
     rch = 2;

   rpar = c3.toInt();
  }

  if(lch == rch)
    return lpar < rpar;

  return lch < rch;
 });

 u2 i = 0;
 for(QString k : keys)
 {
  (*result)[i].first.push_back(k);

  if(!k.startsWith("C"))
    (*result)[i].first.push_back( _par_to_F(k) );


  QVector<QPair<u2, Index_Ref>>& v = rmap[k];

//  qts << "\n\n" << k << "\n";

  for(QPair<u2, Index_Ref> pr : v)
  {
   Index_Ref ir = pr.second;

   Index_Ref_Summary irs;
   irs.entry_id = pr.first;

   Index_Ref_Group& g = (*refs)[pr.first - 1];

   irs.heading = g.heading;
   irs.parent_id = g.parent_id;
   irs.parent_hint = g.parent_hint;

   if(irs.parent_id)
   {
    Index_Ref_Group& p = (*refs)[irs.parent_id - 1];
    irs.parent = p.heading;
   }

   irs.first_page_string = ir.first_page_to_string("r. ", "p. ");

//   qts << (*refs)[pr.first - 1].heading << " {" << pr.first << "} ";
//   qts << " " << ir.first_page_to_string("r. ", "p. ");

   if(pr.second.note_low)
   {
    irs.note_low = pr.second.note_low;
//    qts << "  => n" << pr.second.note_low;
   }
   else
     irs.note_low = 0;

   if(pr.second.note_high)
   {
    irs.note_high = pr.second.note_high;
//    qts << ";" << pr.second.note_high;
   }
   else
     irs.note_high = 0;

   (*result)[i].second.push_back(irs);

//   qts << "\n";
  }
  ++i;
 }

 return result;
}

int main1(int argc, char *argv[])
{
 QString afile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(afile);

 QVector<QPair<QStringList, QVector<Index_Ref_Summary>>>* rsvec = make_review_vector(refs);


 QString rfile = "/home/nlevisrael/Downloads/m2m/review/r.txt";

 QFile outfile(rfile);
 if (!outfile.open(QIODevice::WriteOnly))
   return 0;

 QTextStream qts(&outfile);


 for(const QPair<QStringList, QVector<Index_Ref_Summary>>& pr : *rsvec)
 {
  qts << "\n\n" << pr.first.first() << "\n";

  for(Index_Ref_Summary irs : pr.second)
  {
   qts << irs.heading << " {" << irs.entry_id << "} ";
   qts << " " << irs.first_page_string;

   if(irs.note_low)
     qts << "  => n" << irs.note_low;

   if(irs.note_high)
     qts << ";" << irs.note_high;

   qts << "\n";
  }
 }

 outfile.close();
 return 0;
}


int main23(int argc, char *argv[])
{
 QString afile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(afile);

// QString lfile = "/home/nlevisrael/Downloads/m2m/latex/prologue.tex";
 QString lfile = "/home/nlevisrael/Downloads/m2m/latex/intro.tex";
 QString ltext = KA::TextIO::load_file(lfile);

 //QRegularExpression rx(" ")

 QStringList pars = ltext.split("\\pfl{}");

 QVector<QVector<QPair<u2, QString>>> par_pages;

// // par_pages.resize(40);
 par_pages.resize(14);

// u2 current_page = 32, last_page = 0;
// u2 ix = 0;
 u2 current_page = 72, last_page = 0;

 u1 par_code = 0;
 for(QString par : pars)
 {
  //qDebug() << par.trimmed();

  QRegularExpression rx("\\\\notePage\\{(\\w+)\\}");

  QRegularExpressionMatch match = rx.match(par);
  if(match.hasMatch())
  {
   int cs = match.capturedStart();
   int ce = match.capturedEnd();
   last_page = current_page;
   current_page = _roman_to_u2(match.captured(1));

   QString pre = par.mid(0, cs);
   QString post = par.mid(ce);

   par_pages[last_page - 72].push_back({par_code, pre});
   par_pages[current_page - 72].push_back({par_code, post});
  }
  else
  {
   par_pages[current_page - 72].push_back({par_code, par});
  }
  ++par_code;
 }

 for(Index_Ref_Group& g : *refs)
 {
  QString h = g.heading.simplified();
//  h.replace(QRegularExpression("[^a-zA-Z0-9'-]"), "");
//  h.remove(QRegularExpression("[^a-zA-Z0-9'-]"));

  h.remove("``");
  h.remove("''");

  QStringList hs = h.split(' ');
  for(Index_Ref ir : g.index_refs)
  {
   if(ir.region_code == 1 && ir.low >= 72)
   {
    QVector<QPair<u2, QString>> par_page = par_pages[ir.low - 72];
    for(QPair<u2, QString> pr : par_page)
    {
     if(pr.second.contains(hs.first()))
     {
      qDebug() << "\n" << g.entry_id << g.heading
       << _to_roman(ir.low) << " => " << "@Pr%1"_qt.arg(pr.first);
     }
    }
   }
  }
 }

 return 0;
}



int main30(int argc, char *argv[])
{
 QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 QString ifile = "/home/nlevisrael/Downloads/m2m/new/dindex-add.txt";
 QVector<Index_Entry> ies;
 QString itext = KA::TextIO::load_file(ifile);
 read_index_entries(itext, ies);

 QVector<QPair<u2, u2>> chapter_ranges_m {
  {3, 25},
  {26, 36},
  {39, 56},
  {57, 111},
  {112, 144},

  {145, 201},
  {202, 258},
  {259, 273},
  {277, 284},
  {285, 304},
  {305, 327},
 };


 for(Index_Ref_Group& g : *refs)
 {
  for(Index_Ref ir : g.index_refs)
  {
   if(ir.note_low)
     continue;

   for(QString para : ir.paragraph_codes)
   {
    if(para.startsWith("Pr"))
    {
     if(ir.region_code != 1)
       qDebug() << "R?";

     u2 page = ir.low;
     if( (page < 32) || (page > 71) )
     {
      qDebug() << "Page? " << page << " {"
         << g.entry_id << "}  " << g.heading;
     }
     continue;
    }

    if(para.startsWith("Io"))
    {
     if(ir.region_code != 1)
       qDebug() << "R?";

     u2 page = ir.low;
     if( (page < 72) || (page > 85) )
     {
      qDebug() << "Page? " << page << " {"
         << g.entry_id << "}  " << g.heading;
     }
     continue;
    }


    QRegularExpression rx("C(\\d+)P");
    QRegularExpressionMatch m = rx.match(para);
    if(m.hasMatch())
    {
     u2 cn = m.captured(1).toInt();
     u2 page = ir.low;

     QPair<u2, u2> pr = chapter_ranges_m[cn - 1];

     if(page < pr.first || page > pr.second)
       qDebug() << "Page? " << page << " {"
          << g.entry_id << "}  " << g.heading;

    }

   }

  }


 }

}




void make_html(QVector<Index_Ref_Group>* refs,
  QMap<QString, QString>* front_par_map = nullptr)
{

 QVector<QPair<u2, u2>> chapter_ranges_m {
  {3, 25},
  {26, 36},
  {39, 56},
  {57, 111},
  {112, 144},

  {145, 201},
  {202, 258},
  {259, 273},
  {277, 284},
  {285, 304},
  {305, 327},
 };

// QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
// QString aotfile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out-test.txt";

//? QString aofile = "/home/nlevisrael/Downloads/m2m/new/all.txt";
// QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda.txt";


 //? QString ifile = "/home/nlevisrael/Downloads/m2m/new/dindex-updated.txt";
 QString ifile = "/home/nlevisrael/Downloads/m2m/new/dindex-add.txt";

 QVector<Index_Entry> ies;
 QString itext = KA::TextIO::load_file(ifile);
 read_index_entries(itext, ies);

 QString aotfile = "/home/nlevisrael/Downloads/m2m/new/all-out.html";
 QString aotbfile = "/home/nlevisrael/Downloads/m2m/new/all-out-b.html";

 QString aosfile = "/home/nlevisrael/Downloads/m2m/new/all-out-summary.txt";

 QFile outfile(aotfile);
 if (!outfile.open(QIODevice::WriteOnly))
   return;

 QFile soutfile(aosfile);
 if (!soutfile.open(QIODevice::WriteOnly))
   return;

 QFile boutfile(aotbfile);
 if (!boutfile.open(QIODevice::WriteOnly))
   return;

 QTextStream qts(&outfile);
 QTextStream bqts(&boutfile);
 QTextStream sqts(&soutfile);

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

 auto str_clean = [] (QString& s)
 {
  s.replace("&agrave;", "");

  s.replace("&ldquo;", "");
  s.replace("&rdquo;", "");
  s.replace("&lsquo;", "");
  s.replace("&rsquo;", "");
  s.replace("&uuml;", "u");
  s.replace("`", "");
  s.replace("'", "");
  s.replace("<i>", "");
  s.replace("</i>", "");

  if(s.startsWith(":"))
    s = s.mid(1);

  if(s.endsWith(":"))
    s.chop(1);

  s4 ix = s.indexOf(QRegularExpression(":\\s*\\("));
  if(ix != -1)
    s = s.mid(0, ix);

  s = s.toLower();
 };

 auto str_compare = [str_clean](QString lhs, QString rhs) -> bool
 {
  str_clean(lhs);
  str_clean(rhs);

  return lhs < rhs;
 };


 std::sort(refs->begin(), refs->end(), [&ies, str_compare]
   (const Index_Ref_Group& lhs, const Index_Ref_Group& rhs)
   -> bool
 {
  u2 lid = lhs.entry_id;
  u2 rid = rhs.entry_id;

//  if(lid == 43)
//    qDebug() << "lid";

//  if(rid == 43)
//    qDebug() << "rid";

//  if(lid == 43 && rid == 97)
//    qDebug() << "lr";

//  if(rid == 43 && lid == 97)
//    qDebug() << "rl";

  u2 lpid = lhs.parent_id;
  u2 rpid = rhs.parent_id;

  if(lpid && rpid)
  {
   if(lpid == rpid)
     return lid < rid;

   Index_Entry& lie = ies[lpid - 1];
   Index_Entry& rie = ies[rpid - 1];

   return str_compare(lie.key, rie.key);
  }

  else if(lpid)
  {
   if(lpid == rid)
     return false; // parents always come before children

   Index_Entry& lie = ies[lpid - 1];
   return str_compare(lie.key, rhs.heading);
  }

  else if(rpid)
  {
   if(rpid == lid)
     return true; // parents always come before children

   Index_Entry& rie = ies[rpid - 1];
   bool c = str_compare(lhs.heading, rie.key);
   return c;
  }

  bool cc = str_compare(lhs.heading, rhs.heading);
  return cc;
 });


 QVector<QPair<u2, u2>> chapter_ranges {
  {332, 334},
  {334, 334},
  {334, 335},
  {336, 343},
  {344, 347},

  {348, 353},
  {353, 359},
  {360, 361},
  {361, 361},
  {362, 362},
  {363, 364},
 };




 QString held;

 u2 i = 0;
 for(Index_Ref_Group& g : *refs)
 {
#ifdef HIDE
  for(Index_Ref ir : g.index_refs)
  {
   if(ir.note_low)
   {
    QString pc = ir.paragraph_codes.value(0);
    QRegularExpression qre("C(\\d+)");
    QRegularExpressionMatch m = qre.match(pc);
    if(m.hasMatch())
    {
     u2 chap = m.captured(1).toInt();
     QPair<u2, u2> r = chapter_ranges[chap - 1];
     if(ir.low >= r.first && ir.low <= r.second)
       qDebug() << "ok";
     else
       qDebug() << "\n\n!!!!!!!\nnot ok\n!!!!!!\n\n";
    }
   }
  }
#endif //def HIDE


  //Index_Entry& ie = ies[i];
  Index_Entry& ie = ies[g.entry_id - 1];

  ++i;

  sqts << "\n%1: %2 = %3"_qt.arg(i).arg(g.heading).arg(g.entry_id);
  if(g.parent_id)
    sqts << " (%1 -> %2 = %3)"_qt.arg(g.parent_hint).arg(g.parent_id).arg(ie.count_in_parent);


  if(g.entry_id == 431)
    qDebug() << i;

  if(!held.isEmpty() && !ie.parent_id)
  {
   bqts << held;
   held.clear();
  }


  if(g.entry_id)
  {
   if(g.entry_id == 580)
     qDebug() << g.entry_id;

   if(g.entry_id == 24)
     qDebug() << g.entry_id;

   if(g.type == "v")
     continue;

   for(const Index_Ref& ir : g.index_refs)
   {
    if(ir.region_code == 1 && ir.low <= 31)
      continue; //qDebug() << ir.low << ": " << _to_roman(ir.low);

    for(QString pc : ir.paragraph_codes)
    {
     QRegularExpression rx ("C(\\d+)");
     QRegularExpressionMatchIterator it = rx.globalMatch(pc);
     while(it.hasNext())
     {
      QRegularExpressionMatch m = it.next();
      int ch = m.captured(1).toInt();

      QPair<u2, u2> range = chapter_ranges_m[ch - 1];
      if(ir.low < range.first || ir.high > range.second)
      {
       qDebug() << "\n\n\n!!!\n!!!" << g.entry_id;
      }
     }

    }

    //ir.low
   }


   Index_Entry* parent = g.parent_id? &ies[g.parent_id - 1] : nullptr;
   Index_Ref_Group* pg = g.parent_id? &((*refs)[g.parent_id - 1]) : nullptr;

   QPair<QString, QString> divs = g.to_html_bookstyle(ie, front_par_map, parent, pg);

   QString div = g.to_html(ie);

   if(g.entry_id == 406)
     qDebug() << "\n\n" << divs.first;

   if(divs.first.contains("::"))
   {
    divs.first.replace("@C4P23::C4P35", "@C4S2");
    divs.first.replace("@C8P42::C8P55", "@C8S7");
    divs.first.replace("@C7P41::C7P47", "@C7S4");
    divs.first.replace("@C10P34::C10P39", "@C10S4");
    divs.first.replace("@C5P82::C5P89", "@C5S5");
    divs.first.replace("@C5P90::C5P93", "@C5S6");
    divs.first.replace("@C9P3::C9P13", "@C9S1");

    divs.first.replace("@C8P11::C8P21", "@C8S2");

    divs.first.replace("@C8P22::C8P27", "@C8S3");

    divs.first.replace("@C6P176::C6P182", "@C6S23");
    divs.first.replace("@C6P183::C6P187", "@C6S24");
    divs.first.replace("@C6P188::C6P192", "@C6S25");

    divs.first.replace("@C4P154::C4P157", "@C4S12");
    divs.first.replace("@C4P162::C4P163", "@C4S16");
   }


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
   divs.first.replace("s-'", "s&rsquo;");

   bool clean = true;
   if(clean)
   {

//    if(divs.first.contains("Trish"))
//      qDebug() << divs.first;

    divs.first.replace(QRegularExpression("\\d+nn(\\d+)-(\\d+)\\s+@@?([FCP\\d]+)"),
                       "\\3nn\\1&ndash;\\2");

    divs.first.replace(QRegularExpression("\\d+--\\*?\\d+\\s+@@?"), "");

    // C\\d+P\\d+
    divs.first.replace(QRegularExpression("\\d+(n\\d+)\\s+@([FCPIor\\d]+)"), "\\2\\1");

    if(divs.first.contains("!!nn"))
    {
     divs.first.replace(QRegularExpression("!!nn(\\d+)-(\\d+)\\s+(@+[FCPIor\\d]+)"),
       "\\3nn\\1&ndash;\\2");
    }

    if(divs.first.contains("!!n"))
    {
     divs.first.replace(QRegularExpression("!!n(\\d+)\\s+(@+[FCPIor\\d]+)"), "\\2n\\1");
    }

    divs.first.replace(QRegularExpression("\\d+\\s+@@?"), "");

//    divs.first.replace(QRegularExpression("::"), "&ndash;");

    if(divs.first.contains("&ndash;"))
    {
//     if(divs.first.contains("Pr16"))
//     {
//      qDebug() << "\n\n" << divs.first;
//      divs.first.replace("@Pr16&ndashPr20", "@F5S4");
//     }

     divs.first.replace("@F5P17&ndash;F5P21", "@F5S4");

    }


    //    divs.first.replace(QRegularExpression(";C\\d+P\\d+;"), ";;");

    divs.first.replace(QRegularExpression("(F5P\\d+\\(=Pr\\d+\\));(F5P\\d+\\(=Pr\\d+\\))"),
      "\\1&ndash;\\2");
    divs.first.replace(QRegularExpression("(F6P\\d+\\(=Io\\d+\\));(F6P\\d+\\(=Io\\d+\\))"),
      "\\1&ndash;\\2");

    divs.first.replace(QRegularExpression(";[FCPIor\\d;]+;"), ";;");
    divs.first.replace(QRegularExpression("((?:C\\d+|Io|Pr|F5|F6)P\\d+);+((?:C\\d+|Io|Pr|F5|F6)P\\d+)"),
      "\\1&ndash;\\2");

    divs.first.replace(QRegularExpression("((?:C\\d+|Io|Pr|F5|F6)P\\d+)::((?:C\\d+|Io|Pr|F5|F6)P\\d+)"), "\\1&ndash;\\2");

    divs.first.replace(QRegularExpression("Cn(\\d+)\\?\\?\\?"), "C?P?n\\1");


    divs.first.replace(QRegularExpression("[ivxl]+\\s+@"), "");

   }


   // for anne grant
   if(g.entry_id == 474)
     divs.first.replace("51", "50");

   //?divs.first.replace(QRegularExpression("\\s+;"), ";");
   //divs.first.replace(QRegularExpression("\\.\\s*;"), ";");

   div.replace(QRegularExpression("\\s+\\.</span>"), ".</span>");
   div.replace(QRegularExpression("\\s+</span>;"), "</span>;");



   {
    u2 chapter = 0;
    u2 par = 0;
    QRegularExpression rx("C(\\d+)P(\\d+)(?![\\dn])");
    QRegularExpressionMatchIterator it = rx.globalMatch(divs.first);
    while(it.hasNext())
    {
     QRegularExpressionMatch match = it.next();
     u2 this_chapter = match.captured(1).toInt();
     u2 this_par = match.captured(2).toInt();
     if(this_chapter < chapter)
       qDebug() << "\n\nerr: " << g.entry_id << " " << match.captured();
     else if(this_chapter == chapter && this_par < par)
       qDebug() << "\n\nerr: " << g.entry_id << " " << match.captured();
     else if(this_chapter == chapter && this_par == par)
       qDebug() << "\n\n= err: " << g.entry_id << " " << match.captured();
     chapter = this_chapter;
     par = this_par;
    }



   }


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
 boutfile.close();
 soutfile.close();
}

int main44(int argc, char *argv[])
{
 QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";

 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 make_html(refs);

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



int main31(int argc, char *argv[])
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

#include "indexing/pdf-enhanced-search-dialog.h"

#include "indexing/single-index-entry-dialog.h"

#include "indexing/search-template-dialog.h"




int main02(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 DHAX_PDF_View_Dialog* pvd = new DHAX_PDF_View_Dialog(nullptr, nullptr,
   "/home/nlevisrael/Downloads/xml-db/pisa-readthedocs-io-en-latest.pdf",
   "",
   0, 1);

 pvd->show();


 return qapp.exec();

}


QStringList parse_locators(QString text)
{
 static QRegularExpression locators_rx("[\\d-]+|[lxvi-]+|\\[.+?\\]|[.]");

 QRegularExpressionMatchIterator lit = locators_rx.globalMatch(text);

 QStringList locators;

 while(lit.hasNext())
 {
  QRegularExpressionMatch m = lit.next();

  QString c = m.captured();

  if(c == ".")
    break;

  if(c.startsWith("["))
  {
   c = c.mid(1);
   c.chop(1);
  }

  locators.push_back(c);
 }

 return locators;
}


void parse_index(QString index_text, QMap<QString, QStringList>& result)
{
 static QRegularExpression entry_rx(">([^|/]+?)([|/]+)");

 QRegularExpressionMatchIterator it = entry_rx.globalMatch(index_text);


 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();

  QString heading = match.captured(1);
  QString end_text = match.captured(2);



  QString locators_text;
  if(heading.contains("@"))
  {
   s4 ux = heading.indexOf("@");
   locators_text = heading.mid(ux + 1);
   heading = heading.left(ux);
  }

  if(end_text == "|")
  {
   s4 pos = match.capturedStart(2);

   s4 end_pos = index_text.indexOf("//", pos);

   QString subs = index_text.mid(pos, end_pos - pos + 1);

   static QRegularExpression subs_rx("\\|([^/]+)/");

   QRegularExpressionMatchIterator subs_it = subs_rx.globalMatch(subs);

   while(subs_it.hasNext())
   {
    QString sub = subs_it.next().captured(1);

    if(sub.contains("@"))
    {
     s4 ux = sub.indexOf("@");
     QString sub_text = sub.mid(ux + 1);
     sub = sub.left(ux);

     QStringList qsl = parse_locators(sub_text);

     result[heading + ":" + sub] = qsl;
    }

   }

  }


  QStringList locators = parse_locators(locators_text);

  if(!locators.isEmpty())
    result[heading] = locators;


  //QStringList qsl = locators_text.split(",");

 }

}


void parse_page_numbers(QStringList& qsl, QVector<u2>& result)
{
 u2 count = 0;
 result.resize(qsl.size());
 for(QString& locator : qsl)
 {
  u2& page_num = result[count];
  ++count;

  QRegularExpression rx ("^[\\dlxvi]+");

  QRegularExpressionMatch m = rx.match(locator);

  if(m.hasMatch())
  {
   locator = m.captured();
   if(locator.contains("x") || locator.contains("v") || locator.contains("l") || locator.contains("i"))
     page_num = _roman_to_u2(locator);
   else
     page_num = locator.toUInt() + 90;
  }
 }
}


int main(int argc, char *argv[])
{
 QString index_file = "/home/nlevisrael/Downloads/m2m/index.txt";

 QString index_text = KA::TextIO::load_file(index_file);

 QMap<QString, QStringList> index_qsl;
 QMap<QString, QVector<u2>> index_vec;

 parse_index(index_text, index_qsl);

 QMapIterator<QString, QStringList> it(index_qsl);

// QFile outfile(out_path);
// if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
//   return 0;

 while(it.hasNext())
 {
  it.next();

  QStringList qsl = it.value();
  QVector<u2> numbers;
  parse_page_numbers(qsl, numbers);
  index_qsl[it.key()] = qsl;
  index_vec[it.key()] = numbers;
 }


 QMap<u2, QStringList> reverse_map;

 {
  QMapIterator<QString, QVector<u2>> it(index_vec);

  while(it.hasNext())
  {
   it.next();

   QString key = it.key().simplified();

   key.replace(QRegularExpression("[^\\w,()\\s:]"), "");

   if(key.endsWith(","))
     key.chop(1);

   key.replace(" :", ": ");
   key.replace(",:", ":");

   for(u2 page : it.value())
   {
    reverse_map[page].push_back(key);
   }
  }
 }

 {
  QString out_path = "/home/nlevisrael/Downloads/m2m/out.txt";

  QMapIterator<u2, QStringList> it(reverse_map);

  QFile outfile(out_path);
  if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
    return 0;

  QTextStream outstream(&outfile);

  while(it.hasNext())
  {
   it.next();
   outstream << "\n\n >> " << it.key() << "\n -> \n" << it.value().join("  \n");
  }
 }

// outfile.close();


 QApplication qapp(argc, argv);


 DHAX_PDF_View_Dialog* pvd = new DHAX_PDF_View_Dialog(nullptr, nullptr,
    "/home/nlevisrael/Downloads/m2m/Neustein_Lesher_9780197661222_US_BITS.pdf",
    "",
    91, 32);

 pvd->set_arabic_start(91);
 pvd->set_roman_end(90);
 pvd->set_roman_start(1);

 pvd->setWindowFlags(pvd->windowFlags() | Qt::WindowStaysOnTopHint);

 pvd->set_pages_folder("/home/nlevisrael/Downloads/m2m/pages");

 pvd->set_reverse_map(&reverse_map);

 QString out_path = "/home/nlevisrael/Downloads/m2m/summary.txt";

 QFile outfile(out_path);
 if (outfile.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream outstream(&outfile);
  pvd->run_pages(37, 365, outstream);
 }

 outfile.close();

 pvd->load_page(93);

 pvd->show();






 return qapp.exec();
}


int main05(int argc, char *argv[])
{

 QApplication qapp(argc, argv);


 DHAX_PDF_View_Dialog* pvd = new DHAX_PDF_View_Dialog(nullptr, nullptr,
    "/home/nlevisrael/Downloads/m2m/Neustein_Lesher_9780197661222_US_BITS.pdf",
    "",
    86, 32);

 pvd->set_arabic_start(86);
 pvd->set_roman_end(85);
 pvd->set_roman_start(1);

 pvd->load_page(292);

 pvd->setWindowFlags(pvd->windowFlags() | Qt::WindowStaysOnTopHint);

 pvd->show();


 return qapp.exec();

}




int main03(int argc, char *argv[])
{
// QString pdf_file = "pisa-readthedocs-io-en-latest.pdf"

 QApplication qapp(argc, argv);


 DHAX_PDF_View_Dialog* pvd = new DHAX_PDF_View_Dialog(nullptr, nullptr,
    "/home/nlevisrael/Downloads/m2m/Neustein_Lesher_9780197661222_US_BITS.pdf",
    "",
    86, 32);

 pvd->set_arabic_start(86);
 pvd->set_roman_end(85);
 pvd->set_roman_start(1);

 pvd->load_page(292);

 pvd->setWindowFlags(pvd->windowFlags() | Qt::WindowStaysOnTopHint);

 pvd->show();


 return qapp.exec();

}


int main01(int argc, char *argv[])
{
 QApplication qapp(argc, argv);

 Single_Index_Entry_Dialog* dlg = new Single_Index_Entry_Dialog(nullptr);

  PDF_Enhanced_Search_Dialog* pesd = new
   PDF_Enhanced_Search_Dialog;

 pesd->show();
 dlg->show();

 return qapp.exec();

}


int main00(int argc, char *argv[])
{


// return 0;


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

// QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
// QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 QString afile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(afile);

 QVector<QPair<QStringList, QVector<Index_Ref_Summary>>>* rsvec = make_review_vector(refs);

 QApplication qapp(argc, argv);

 Index_Entry_Review_Dialog* ierd = new Index_Entry_Review_Dialog(ifile, bfile, ftp_folder);

 ierd->set_ref_groups(refs);
 ierd->filter_ref_groups();
 ierd->set_review_vector(rsvec);

// DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(ierd, nullptr,
//   "/home/nlevisrael/Downloads/m2m/m2m-2003.pdf",
//   n1file,
//   13, 13);
// pvd1->set_arabic_start(24);
// pvd1->set_roman_end(23);
// pvd1->set_roman_start(1);

  DHAX_PDF_View_Dialog* pvd1 = new DHAX_PDF_View_Dialog(ierd, nullptr,
    "/home/nlevisrael/Downloads/m2m/fs/Neustein_Lesher_9780197661222_US_BITS.pdf",
    n1file,
    85, 30);
  pvd1->set_arabic_start(85);
  pvd1->set_roman_end(84);
  pvd1->set_roman_start(1);


 pvd1->setWindowTitle("Earlier Document");

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

 pvd2->show_status("Document Loaded");

 ierd->set_earlier_pdf_dialog(pvd1);
 ierd->set_later_pdf_dialog(pvd2);

 QString mfile = "/home/nlevisrael/Downloads/m2m/review/pm.txt";
 ierd->create_par_code_mapping(mfile);

 QMap<QString, QString>& front_par_map = ierd->get_front_par_map();

 make_html(refs, &front_par_map);

// return 0;

 QString ffile = "/home/nlevisrael/Downloads/m2m/review/rf.txt";
 ierd->make_review_file(ffile);

 QString rfile = "/home/nlevisrael/Downloads/m2m/review/rp.txt";
 QString pfile = "/home/nlevisrael/Downloads/m2m/review/rpf.txt";

 QString r_file = "/home/nlevisrael/Downloads/m2m/review/rp_f.txt";
 QString p_file = "/home/nlevisrael/Downloads/m2m/review/rpf_f.txt";

 ierd->check_review_vector(rfile, pfile, r_file, p_file);

 pvd1->show();

 pvd2->show();

 ierd->show();

// Single_Index_Entry_Dialog* dlg = new Single_Index_Entry_Dialog(nullptr);

//  PDF_Enhanced_Search_Dialog* pesd = new
//   PDF_Enhanced_Search_Dialog;


// pesd->setModal(false);
// pesd->show();

// dlg->setModal(false);

// dlg->show();



// ierd->reclaim_focus();
// ierd->setWindowFlags(ierd->windowFlags() | Qt::WindowStaysOnTopHint);

 qapp.exec();
 return 0;
}

//ROOT_FOLDER "/../docs/ch6.pdf");
