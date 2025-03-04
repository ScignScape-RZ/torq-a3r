
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SVG_PDF_WEB_VIEW_DIALOG__H
#define SVG_PDF_WEB_VIEW_DIALOG__H

#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QDialog>

#include <QTableWidget>
#include <QFrame>

#include <QTabWidget>

#include "svg-pdf-web-engine-view.h"
#include "svg-pdf-web-engine-page.h"

//#include "my-page.h"

#include "qwc-context.h"

#include "global-types.h"

#include "accessors.h"

//#include "url-or-event-pattern.h"

#include <QScrollArea>


class SVG_PDF_Web_View_Dialog : public QDialog
{
 Q_OBJECT


 //Fore_Geometric1D_Panel fore_panel_;
 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QScrollArea* wev_scroll_area_;
 SVG_PDF_Web_Engine_View* wev_;
 //wev->setGeometry(0,0,700,600);

 QWebEngineView* iwev_;

//?
 SVG_PDF_Web_Engine_Page* wep_;
//? MyPage* myp_;

 QWC_Context* qwc_context_;

 QTabWidget* qtw_;

 QFrame* url_patterns_frame_;
 QTableWidget* url_patterns_table_;
 QVBoxLayout* url_patterns_layout_;

// QVector<URL_Or_Event_Pattern> url_patterns_;


public:


 SVG_PDF_Web_View_Dialog(QWidget* parent);
 ~SVG_PDF_Web_View_Dialog();

// ACCESSORS__RGET(QVector<URL_Or_Event_Pattern> ,url_patterns)


 ACCESSORS(SVG_PDF_Web_Engine_View* ,wev)

 void handle_edit_url_patterns_row(int rc);
 void handle_save_url_patterns_row(int rc);
 void handle_cancel_remove_url_patterns_row(int rc);
 void handle_add_url_patterns_row();

 void check_url_patterns(QString url);

 void mouseReleaseEvent(QMouseEvent* mouseEvent) Q_DECL_OVERRIDE;
 void mousePressEvent(QMouseEvent* mouseEvent) Q_DECL_OVERRIDE;

 void resizeEvent(QResizeEvent* resize_event) Q_DECL_OVERRIDE;
 void moveEvent(QMoveEvent* move_event) Q_DECL_OVERRIDE;


 void reset_tab_selection();

 QRect get_web_view_geometry();

Q_SIGNALS:


 void snapshot_saved(QString file_path);
 void web_view_geometry_updated(QRect);


};

#endif
