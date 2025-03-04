
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QWC_CONTEXT__H
#define QWC_CONTEXT__H

#include <QObject>

#include <QDebug>

#include <QMap>

class QWC_Context : public QObject
{
 Q_OBJECT

 QMap<int, double> line_heights_;

public:

 QWC_Context();

 /// Log, for debugging
 Q_INVOKABLE void log(const QString& str) const
 {
     qDebug() << "LOG from JS: " << str;
 }

 Q_INVOKABLE void note_line_height(int index, int lines_count, double height);

 Q_INVOKABLE void note_file(const QString& str) const;
};


#endif
