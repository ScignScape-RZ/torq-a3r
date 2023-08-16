
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef QH_WEB_ENGINE_PAGE__H
#define QH_WEB_ENGINE_PAGE__H

#include <QWebEngineView>
#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QContextMenuEvent>
#include <QMenu>
#include <QWebEngineContextMenuData>

#include "global-types.h"

#include "kans.h"

#include "accessors.h"


KANS_(RdSC)


//class NavigationRequestInterceptor;
class NavigationRequestInterceptor : public QWebEnginePage
{
 QWebEnginePage* target;
public:
 NavigationRequestInterceptor(QWebEnginePage* parent);
 bool acceptNavigationRequest(const QUrl &url, NavigationType type,
                              bool isMainFrame) Q_DECL_OVERRIDE;
};

class JsInterface;
class QH_Web_View_Dialog;
class QH_Web_Engine_View;



class QH_Web_Engine_Page : public QWebEnginePage
{
 Q_OBJECT

 QString last_youtube_link_;

 QH_Web_Engine_View* view_;

 QH_Web_View_Dialog* dialog_;

 QWebChannel* qweb_channel_;
 JsInterface* jsInterface_;


public:
 QH_Web_Engine_Page(QH_Web_Engine_View* view);
 QH_Web_Engine_Page(QH_Web_Engine_Page* parent);

 ACCESSORS(QH_Web_View_Dialog* ,dialog)

 bool acceptNavigationRequest(const QUrl &url, NavigationType type,
                              bool isMainFrame) override;

 NavigationRequestInterceptor*
 createWindow(QWebEnginePage::WebWindowType type) override;

 void emit_navRequest(const QUrl &url);

 void reset_last_youtube_link(const QUrl &url);

 QString last_youtube_link_as_non_embed();

 void load_with_web_channel(const QUrl &url);
 void setup_web_channel();
 void temp(r8 lat, r8 lon);

 void run_js_interface_callback(QString key, const QJsonValue& msg);
 void run_js_interface_callback(const QJsonValue& key, const QJsonValue& msg);
 void run_js_interface_callback(QString key, QString msg);


Q_SIGNALS:

 void navRequest(const QUrl& url, const QPoint pos);

 void qh_link_request(const QUrl& url, const QPoint pos,  const QSize window_size,
   QString cut_path, NavigationType type);

};

_KANS(RdSC)

#endif