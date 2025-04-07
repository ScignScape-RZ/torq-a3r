
#ifndef INDEX_REF__H
#define INDEX_REF__H


#include "textio.h"

#include "global-types.h"

u2 _roman_to_u2(QString roman);
QString _to_roman(u2 value);


struct Index_Entry;

struct Index_Ref_Summary {
 u2 entry_id;
 QString heading;
 QString first_page_string;
 u2 note_low;
 u2 note_high;

 QString parent;
 QString parent_hint;
 u2 parent_id;

 static u2 par_code_to_number(QString para);

 static void split(const QVector<Index_Ref_Summary>& v,
   QMap<u2, QVector<Index_Ref_Summary>>& result);

 u2 first_page_string_to_number() const;

 void to_string(QTextStream& qts, QString pre, QString alt_page);

 QStringList heading_to_words() const;

};


struct Index_Ref_Strings {

 QString low;
 QString high;
 QString between;

 QString note_low;
 QString note_high;

 QString paragraph_code;

};


struct Index_Ref {

 u2 low;
 u2 high;
 QString between;

 u2 note_low;
 u2 note_high;

 u2 region_code;

 QStringList paragraph_codes;

 static Index_Ref from_strings(const Index_Ref_Strings& strings);

 QString to_string() const;
 QString first_page_to_string(QString rpre = QString(), QString pre = QString()) const;

};


struct Index_Ref_Group {
  u2 entry_id;
  QVector<Index_Ref> index_refs;

  QString type;
  QString heading;
  QString follow;
  QString supplement;

  u2 parent_id;
  QString parent_hint;

  QString to_string() const;

  QString to_html(const Index_Entry& ie) const;

  QPair<QString, QString> to_html_bookstyle(const Index_Entry& ie,
    Index_Entry* parent = nullptr, Index_Ref_Group* pg = nullptr) const;

};



#endif
