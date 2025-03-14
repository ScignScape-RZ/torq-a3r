
#ifndef INDEX_REF__H
#define INDEX_REF__H


#include "textio.h"


struct Index_Ref {

 QString low;
 QString high;
 QString between;

 QString note_low;
 QString note_high;

 QString paragraph_code;

 QString to_string() const;

};


struct Index_Ref_Group {
  u2 entry_id;
  QVector<Index_Ref> index_refs;

  QString type;
  QString heading;
  QString follow;
  QString supplement;

  QString parent_id;
  QString parent_hint;

  QString to_string() const;

};



#endif
