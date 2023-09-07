
#include "chasm-utils.h"

extern "C" {
#include "chasm-slib-decl.h"
}


int inc(int x)
{
 return x + 1;
}


#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>
#include <QDir>



void _prepare_scheme_file_keywords(QString& str)
{
 QString _str = str;

 static QRegularExpression rx("(\\\\*)(%\\S+%)");

 static QMap<QString, QString> keys {{
   {"%test%", "ok!"}
 }};

 //QVector<int> escape_starts;
 QVector<QPair<int, QString>> replace_starts;

 QRegularExpressionMatchIterator mit = rx.globalMatch(str);
 while (mit.hasNext())
 {
  QRegularExpressionMatch rxm = mit.next();


  int prior_escape_run = rxm.captured(1).length();

  if( (prior_escape_run % 2) == 0)
  {
   QString arg = rxm.captured(2);
   int st = rxm.capturedStart(2);
   replace_starts.push_back({st, arg});

//   arg.prepend(":-");
//   str.replace(st - 1, arg.length(), arg);
  }
  else
  {
   replace_starts.push_back({rxm.capturedStart() + prior_escape_run - 1, {}});
  }
 }

 int offset = 0;
 for(auto const& st : replace_starts)
 {
  if(st.second.isEmpty())
  {
   str.remove(st.first - offset, 1);
   ++offset;
  }
  else
  {
   QString key = st.second;
   auto it = keys.find(key);
   QString value;
   if(it == keys.end())
   {
    value = key;
    //value.replace(0, 1, QChar('?'));
    value.prepend(QChar('?'));
   }
   else
     value = *it;

   signed int kl = key.length();
   str.replace(st.first - offset, kl, value);

   offset += (kl - value.length());
  }
 }
}

void _prepare_scheme_file(QString file_path, QString& result)
{
 QFile qf(file_path);

 if(qf.open(QIODevice::ReadOnly))
 {
  QString str = qf.readAll();

  QFileInfo qfi(file_path);
  QDir qd(qfi.absoluteDir());
  QString cbn = qfi.completeBaseName();
  QString sfx = qfi.suffix();

  QString gen_file_name = QString("_%1.gen.%3").arg(cbn).arg(sfx);
  QString gen_file_path = qd.absoluteFilePath(gen_file_name);

  _prepare_scheme_file_keywords(str);
  QFile qf1(gen_file_path);

  if(qf1.open(QIODevice::WriteOnly))
  {
   qf1.write(str.toLatin1());
   qf1.close();
  }

//  static QString load_template = R"(
//(parameterize
// ((current-readtable
//  (readtable-keywords-allowed?-set (current-readtable) 'prefix)
// ))
// (load "%1")
//)";

//  (current-readtable (readtable-keywords-allowed?-set (current-readtable) 'prefix) )

  static QString load_template = R"(

(parameterize
 ((current-readtable
  (readtable-keywords-allowed?-set
   (readtable-eval-allowed?-set (current-readtable) #t)
  'prefix)
 ))
(load "%1")
)

)";

  result = load_template.arg(gen_file_path);
 }
}

//(readtable-eval-allowed?-set (current-readtable) #t)


//(parameterize
// ((current-readtable
//  (readtable-keywords-allowed?-set
//   (readtable-eval-allowed?-set (current-readtable) 'prefix)
//   'prefix)

//  )
// )
// (load "%1")


void eval_scheme_file(QString file_path, char*& result)
{
 QString scheme_code;
 _prepare_scheme_file(file_path, scheme_code);

 result = eval_string((char*) scheme_code.toStdString().c_str());

}

long scheme_kw_to_chars(___SCMOBJ s, char*& result)
{
 long ___temp;
 long temp_result = 0;

 ___KEYWORD2STRINGP_NOTFALSEP(temp_result, s);

 if(temp_result)
 {
  return ___SCMOBJ_to_CHARSTRING(temp_result, &result, 0);
 }

 return 0;
}

long scheme_symbol_to_chars(___SCMOBJ s, char*& result)
{
 long ___temp;
 long temp_result = 0;

 ___SYMBOL2STRINGP_NOTFALSEP(temp_result, s);

 if(temp_result)
 {
  return ___SCMOBJ_to_CHARSTRING(temp_result, &result, 0);
 }

 return 0;
}


#ifdef HIDE
void _prepare_scheme_file_keywords(QString& str)
{
 QString _str = str;

 static QRegularExpression rx("(\\\\*):(\\w+)");

 QVector<int> starts;

 QRegularExpressionMatchIterator mit = rx.globalMatch(str);
 while (mit.hasNext())
 {
  QRegularExpressionMatch rxm = mit.next();

  int st = rxm.capturedStart(2);

  int prior_escape_run = rxm.captured(1).length();

  if( (prior_escape_run % 2) == 0)
  {
   QString arg = rxm.captured(2) + ":";
   str.replace(st - 1, rxm.capturedLength(2) + 1, arg);
  }
  else
  {
   starts.push_back(rxm.capturedStart() + prior_escape_run - 1);
  }
 }

 int offset = 0;
 for(int st : starts)
 {
  str.remove(st - offset, 1);
  ++offset;
 }
}
#endif
