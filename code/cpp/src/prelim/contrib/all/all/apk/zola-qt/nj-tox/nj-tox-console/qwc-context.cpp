
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qwc-context.h"

#include "textio.h"

QWC_Context::QWC_Context()
  : QObject()
{

}


void QWC_Context::note_line_height(int index, int lines_count, double height)
{
 qDebug() << "h " << height;
 line_heights_[index] = height;
}

void QWC_Context::note_file(const QString& str) const
{
 qDebug() << "f " << str;

 static QString base = "/home/nlevisrael/docker/gits/torq-wip/pres/introduction/composite/bases/";

 QString contents = KA::TextIO::load_file(base + str);

 KA::TextIO::save_file(base + str + ".bak", contents);

 qDebug() << contents;
 //?QString url_base = "file:///home/nlevisrael/docker/gits/torq-wip/pres/introduction/composite/bases/";


}


