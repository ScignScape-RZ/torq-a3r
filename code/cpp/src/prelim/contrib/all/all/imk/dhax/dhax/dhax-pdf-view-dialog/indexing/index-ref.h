
#ifndef INDEX_REF__H
#define INDEX_REF__H


#include "textio.h"

#include "global-types.h"


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

};



#endif
