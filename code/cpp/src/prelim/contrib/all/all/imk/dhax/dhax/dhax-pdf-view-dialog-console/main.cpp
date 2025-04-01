
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
 refs.resize(575);

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

  if(index == 430)
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


QVector<QPair<QString, QVector<Index_Ref_Summary>>>* make_review_vector(QVector<Index_Ref_Group>* refs)
{
 QVector<QPair<QString, QVector<Index_Ref_Summary>>>* result = new
   QVector<QPair<QString, QVector<Index_Ref_Summary>>>;

 QMap<QString, QVector<QPair<u2, Index_Ref>>> rmap;



 for(Index_Ref_Group& g : *refs)
 {
  for(const Index_Ref& ir : g.index_refs)
  {
   for(QString para : ir.paragraph_codes)
   {
    if(para.contains("Pr18"))
      qDebug() << para;

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
  (*result)[i].first = k;

  QVector<QPair<u2, Index_Ref>>& v = rmap[k];

//  qts << "\n\n" << k << "\n";

  for(QPair<u2, Index_Ref> pr : v)
  {
   Index_Ref ir = pr.second;

   Index_Ref_Summary irs;
   irs.entry_id = pr.first;
   irs.heading = (*refs)[pr.first - 1].heading;
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

int main(int argc, char *argv[])
{
 QString afile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(afile);

 QVector<QPair<QString, QVector<Index_Ref_Summary>>>* rsvec = make_review_vector(refs);


 QString rfile = "/home/nlevisrael/Downloads/m2m/review/r.txt";

 QFile outfile(rfile);
 if (!outfile.open(QIODevice::WriteOnly))
   return 0;

 QTextStream qts(&outfile);


 for(const QPair<QString, QVector<Index_Ref_Summary>>& pr : *rsvec)
 {
  qts << "\n\n" << pr.first << "\n";

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


int main22(int argc, char *argv[])
{
// QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
// QString aotfile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out-test.txt";

//? QString aofile = "/home/nlevisrael/Downloads/m2m/new/all.txt";
// QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda.txt";
 QString aofile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";

 QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

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
   return 0;

 QFile soutfile(aosfile);
 if (!soutfile.open(QIODevice::WriteOnly))
   return 0;

 QFile boutfile(aotbfile);
 if (!boutfile.open(QIODevice::WriteOnly))
   return 0;

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

  if(lid == 43 && rid == 97)
    qDebug() << "lr";

  if(rid == 43 && lid == 97)
    qDebug() << "rl";

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
  {305, 317},
 };


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
   if(g.entry_id == 431)
     qDebug() << g.entry_id;


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
   divs.first.replace("s-'", "s&rsquo;");

   bool clean = true;
   if(clean)
   {
//    if(divs.first.contains("Trish"))
//      qDebug() << divs.first;

    divs.first.replace(QRegularExpression("\\d+nn(\\d+)-(\\d+)\\s+@@?([CP\\d]+)"),
                       "\\3nn\\1&ndash;\\2");

    divs.first.replace(QRegularExpression("\\d+--\\*?\\d+\\s+@@?"), "");

    // C\\d+P\\d+
    divs.first.replace(QRegularExpression("\\d+(n\\d+)\\s+@([CPIor\\d]+)"), "\\2\\1");

    if(divs.first.contains("!!nn"))
    {
     divs.first.replace(QRegularExpression("!!nn(\\d+)-(\\d+)\\s+(@+[CPIor\\d]+)"),
       "\\3nn\\1&ndash;\\2");
    }

    if(divs.first.contains("!!n"))
    {
     divs.first.replace(QRegularExpression("!!n(\\d+)\\s+(@+[CPIor\\d]+)"), "\\2n\\1");
    }

    divs.first.replace(QRegularExpression("\\d+\\s+@@?"), "");

    //    divs.first.replace(QRegularExpression(";C\\d+P\\d+;"), ";;");

    divs.first.replace(QRegularExpression(";[CPIor\\d;]+;"), ";;");
    divs.first.replace(QRegularExpression("((?:C\\d+|Io|Pr)P\\d+);+((?:C\\d+|Io|Pr)P\\d+)"),
      "\\1&ndash;\\2");

    divs.first.replace(QRegularExpression("((?:C\\d+|Io|Pr)P\\d+)::((?:C\\d+|Io|Pr)P\\d+)"), "\\1&ndash;\\2");

    divs.first.replace(QRegularExpression("Cn(\\d+)\\?\\?\\?"), "C?P?n\\1");
   }

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
 boutfile.close();
 soutfile.close();

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

int main20(int argc, char *argv[])
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

// QString aofile = "/home/nlevisrael/Downloads/m2m/w_pdf/all-out.txt";
// QVector<Index_Ref_Group>* refs = make_ref_group_vector(aofile);

 QString afile = "/home/nlevisrael/Downloads/m2m/new/addenda-prcodes.txt";
 QVector<Index_Ref_Group>* refs = make_ref_group_vector(afile);

 QVector<QPair<QString, QVector<Index_Ref_Summary>>>* rsvec = make_review_vector(refs);


 QApplication qapp(argc, argv);

 Index_Entry_Review_Dialog* ierd = new Index_Entry_Review_Dialog(ifile, bfile, ftp_folder);

 ierd->set_ref_groups(refs);
 ierd->filter_ref_groups();
 ierd->set_review_vector(rsvec);

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

 pvd2->show_status("Document Loaded");

 ierd->set_earlier_pdf_dialog(pvd1);
 ierd->set_later_pdf_dialog(pvd2);

 QString rfile = "/home/nlevisrael/Downloads/m2m/review/rd.txt";

 ierd->check_review_vector(rfile);

 ierd->show();

// ierd->reclaim_focus();
// ierd->setWindowFlags(ierd->windowFlags() | Qt::WindowStaysOnTopHint);

 qapp.exec();
 return 0;
}

//ROOT_FOLDER "/../docs/ch6.pdf");
