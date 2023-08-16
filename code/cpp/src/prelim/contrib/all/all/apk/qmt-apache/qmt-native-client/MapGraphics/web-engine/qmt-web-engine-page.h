
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef QMT_WEB_ENGINE_PAGE__H
#define QMT_WEB_ENGINE_PAGE__H

#include <QWebEngineView>
#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineContextMenuData>

//class NavigationRequestInterceptor;
class NavigationRequestInterceptor : public QWebEnginePage
{
 QWebEnginePage* target;
public:
 NavigationRequestInterceptor(QWebEnginePage* parent);
 bool acceptNavigationRequest(const QUrl &url, NavigationType type,
                              bool isMainFrame) Q_DECL_OVERRIDE;
};


class QMT_Web_Engine_Page : public QWebEnginePage
{
 Q_OBJECT

public:
 QMT_Web_Engine_Page();
 QMT_Web_Engine_Page(QMT_Web_Engine_Page* parent);

 bool acceptNavigationRequest(const QUrl &url, NavigationType type,
                              bool isMainFrame) override;

 NavigationRequestInterceptor*
 createWindow(QWebEnginePage::WebWindowType type) override;

 void emit_navRequest(const QUrl &url);

Q_SIGNALS:

 void navRequest(const QUrl &url);

};


#endif  //  QMT_WEB_ENGINE_PAGE__H