
#include "index-ref.h"

#include "m2m.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>


u2 _roman_to_u2(QString roman)
{
 roman = roman.toLower();
 u2 result = 0;


 if(roman.contains("xl"))
   result += 40;
 else
 {
  if(roman.contains("l"))
   result += 50;

  if(roman.endsWith("ix"))
  {
   result += 9;
   roman.chop(2);
  }

  if(roman.contains("xxx"))
    result += 30;
  else if(roman.contains("xx"))
    result += 20;
  else if(roman.contains("x"))
    result += 10;
 }

 if(roman.contains("iv"))
   result += 4;
 else
 {
  if(roman.contains("v"))
    result += 5;

  if(roman.contains("iii"))
    result += 3;
  else if(roman.contains("ii"))
    result += 2;
  else if(roman.contains("i"))
    result += 1;
 }

 return result;
}

QString _to_roman(u2 value)
{
 QString result;

 static QMap<int, QString> values =
 {
  {1000, "m"}, {900, "cm"}, {500, "d"}, {400, "cd"},
  {100, "c"}, {90, "xc"}, {50, "l"}, {40, "xl"},
  {10, "x"}, {9, "ix"}, {5, "v"}, {4, "iv"}, {1, "i"}
 };

 static QVector<int> keys;
 if(keys.isEmpty())
 {
  keys = values.keys().toVector();
  std::sort(keys.begin(), keys.end(), std::greater<int>());
 }

 for(int k : keys)
 {
  while (value >= k)
  {
   result += values[k];
   value -= k;
  }
 }

 return result;
}


Index_Ref Index_Ref::from_strings(const Index_Ref_Strings& strings)
{
 u2 low = 0, high = 0, note_low = 0, note_high = 0, region_code = 0;

 bool strings_high = !strings.high.isEmpty();

 if(strings.low.contains(QRegularExpression("[lxvi]+")))
 {
  low = _roman_to_u2(strings.low);
  if(strings_high)
    high = _roman_to_u2(strings.high);
  region_code = 1;
 }
 else
 {
  low = strings.low.toInt();
  if(strings_high)
    high = strings.high.toInt();

  note_low = strings.note_low.toInt();
  note_high = strings.note_high.toInt();
 }

 return Index_Ref{low, high, strings.between, note_low, note_high, region_code,
   strings.paragraph_code.split(";")};

}


QString Index_Ref::to_string() const
{
 QString result;
 if(region_code == 1)
 {
  result += _to_roman(low);
  if(high)
  {
   result += between;
   result += _to_roman(high);
  }
 }
 else
 {
  result += QString::number(low);
  if(high)
  {
   result += between;
   result += QString::number(high);
  }
  if(note_low && note_high)
  {
   result += "nn";
   result += QString::number(note_low);
   result += "-";
   result += QString::number(note_high);
  }
  else if(note_low)
  {
   result += "n";
   result += QString::number(note_low);
  }
 }

 if(!paragraph_codes.isEmpty())
   result += " @" + paragraph_codes.join(";");


 return result;
}


QPair<QString, QString> Index_Ref_Group::to_html_bookstyle(const Index_Entry& ie,
   Index_Entry* parent, Index_Ref_Group* pg)  const
{
 QString div;
 QString close;

 QString div_or_span;

 QString s ;// = supplement;

 if(ie.id == 9)
 {
  qDebug() << ie.id;
 }


 if(ie.id >= 21 && ie.id < 24)
 {
  qDebug() << ie.id;
 }


 if(ie.sub_count > 1)
 {
  if(supplement.isEmpty())
    close = "\n\n  </div>\n";
  else
    close = "\n" + supplement + "\n  </div>\n";
 }
 else
 {
  div = "</div>\n";
  s = supplement;
 }



 static QString entry_template = R"(
   <%8 class='index-entry%6'><span>%1%2</span>, %3%4
    %5 %7
                                 )";

 static QString redirect_template = R"(
   <%6 class='index-redirect%4'><span>%1%2. </span>
    %3 %5
                                    )";

 static QString subentries_template = R"(
   <%6 class='index-subentries%5'><span>%1%2</span>
    %3 %4
                                      )";

// QString note = "\n  <span class='note'> {%1} </span> \n"_qt.arg(entry_id);

 QString p;

 if(parent_id)
 {
  div_or_span = "span";

  if(ie.count_in_parent == parent->sub_count - (pg->type == "e"))
  {
   if(parent->supplement.isEmpty())
     div = "</span>\n";
   else
     div = ".</span>\n";
  }
  else
    div = "</span>;\n";
  //?p = " [%1/%2] "_qt.arg(parent_hint).arg(parent_id);
 }
 else
 {
  div_or_span = "div";
 }

 QString dot = supplement.trimmed().isEmpty()? " " : ". ";

 QString h = heading;
 h.replace("``", "&ldquo;");
 h.replace("''", "&rdquo;");

 h.replace(QRegularExpression("\\(\\d+\\s+subentries\\)"), "");

 QString maybe_ital;

 if(h.startsWith(":"))
 {
  h = h.mid(1);
  maybe_ital = " ital";
 }

 h.replace("|", ">");

 if(type == "s")
   return {subentries_template.arg(p).arg(h).arg(s).arg(maybe_ital).arg(div).arg(div_or_span),
      close};

 if(type == "r")
   return {redirect_template.arg(p).arg(h).arg(s).arg(maybe_ital).arg(div).arg(div_or_span), close};

 QStringList pages;

 for(const Index_Ref& ir : index_refs)
 {
  if(ir.region_code == 1 && ir.low <= 31)
    continue; //qDebug() << ir.low << ": " << _to_roman(ir.low);

  pages.push_back(ir.to_string());
 }

 QString join = pages.join(", ");
 return {entry_template.arg(p).arg(h).arg(join).arg(dot)
   .arg(s).arg(maybe_ital).arg(div).arg(div_or_span), close};
}

QString Index_Ref_Group::to_html(const Index_Entry& ie) const
{
 static QString entry_template = R"(
   <div class='index-entry%7'><span>%1%2</span>, %3%4
    %5 %6 </div>
                                 )";

 static QString redirect_template = R"(
   <div class='index-redirect%5'><span>%1%2. </span>
    %3 %4 </div>
                                    )";

 static QString subentries_template = R"(
   <div class='index-subentries%5'><span>%1%2</span>
    %3 %4 </div>
                                      )";

 QString note = "\n  <span class='note'> {%1} </span> \n"_qt.arg(entry_id);

 QString p;

 if(parent_id)
 {
  p = " [%1/%2] "_qt.arg(parent_hint).arg(parent_id);
 }

 QString dot = supplement.trimmed().isEmpty()? " " : ". ";

 QString h = heading;
 h.replace("``", "&ldquo;");
 h.replace("''", "&rdquo;");

 QString maybe_ital;

 if(h.startsWith(":"))
 {
  h = h.mid(1);
  maybe_ital = " ital";
 }

 h.replace("|", ">");

 if(type == "s")
   return subentries_template.arg(p).arg(h).arg(supplement).arg(note).arg(maybe_ital);

 if(type == "r")
   return redirect_template.arg(p).arg(h).arg(supplement).arg(note).arg(maybe_ital);

 QStringList pages;

 for(const Index_Ref& ir : index_refs)
 {
  if(ir.region_code == 1 && ir.low <= 31)
    continue; //qDebug() << ir.low << ": " << _to_roman(ir.low);

  pages.push_back(ir.to_string());
 }

 QString join = pages.join(", ");
 return entry_template.arg(p).arg(h).arg(join).arg(dot).arg(supplement).arg(note).arg(maybe_ital);
}


QString Index_Ref_Group::to_string() const
{
 static QString ref_template = R"(
#%1 $%2<%3>%4
 $[%5]
 +{%6}
                              )";

 QString h = heading;

 if(parent_id)
 {
  h.prepend(" [%1/%2] "_qt.arg(parent_hint).arg(parent_id));
 }

 QStringList pages;

 for(const Index_Ref& ir : index_refs)
 {
  pages.push_back(ir.to_string());
 }

 QString join = pages.join(" ,, ");
 if(join.isEmpty())
   join = " ";

 QString supp = supplement;
 if(supp.isEmpty())
   supp = " ";

 return ref_template.arg(entry_id).arg(type).arg(h)
   .arg(follow).arg(join).arg(supp);
}
