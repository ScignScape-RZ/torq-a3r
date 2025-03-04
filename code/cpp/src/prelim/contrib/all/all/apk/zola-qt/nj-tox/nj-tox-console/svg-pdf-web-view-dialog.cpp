
//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "svg-pdf-web-view-dialog.h"

#include <QPushButton>
#include <QTabBar>

#include <QHeaderView>

#include <QRegularExpression>

//#include "context-menu-provider.h"

#include "svg-pdf-web-engine-view.h"

#include "styles.h"

//void WebGL_View_Dialog::check_url_patterns(QString url)
//{
// if(url_patterns_.isEmpty())
//   return;

// if(url.contains("/maps/place"))
//   qDebug() << url;

// QVector<Pattern_Matcher_Runtime::Action_Info> info;

// for(int i = url_patterns_.size() - 1; i >= 0; --i) //const QMap<QString, QString>& m : url_patterns_)
// {
//  URL_Or_Event_Pattern& uep = url_patterns_[i];
//  QString pattern = uep.pattern_expression();

//  if(pattern.isEmpty())
//    continue;

//  QRegularExpression rx(pattern);

//  QRegularExpressionMatch rxm = rx.match(url);

//  if(rxm.hasMatch())
//  {
//   QString proc = uep.procedure_name();
//   QString arguments = uep.procedure_arguments();
//   for(int i = 0; i < 10; ++i)
//     arguments.replace(QString("`.%1").arg(i), rxm.captured(i));
//   qDebug() << "Proc = " << proc;
//   qDebug() << "Arguments = " << arguments;

//   QStringList action_procedures;
//   QStringList option_labels;

//   context_menu_provider_->check_url(proc, arguments, info);

//   if(!info.isEmpty())
//     break;
//   //Q_EMIT url_pattern_match(proc, arguments);
//  }
// }

// if(info.isEmpty())
//   return;



// for(Pattern_Matcher_Runtime::Action_Info& ai : info)
// {
//  qDebug() << ai.option_label;
// }

//}

#include <QTimer>
#include <QScreen>


void SVG_PDF_Web_View_Dialog::reset_tab_selection()
{
 qtw_->setCurrentIndex(1);
 qtw_->setCurrentIndex(0);

// qtw_->setCurrentWidget(wev_scroll_area_);
}


SVG_PDF_Web_View_Dialog::SVG_PDF_Web_View_Dialog(QWidget* parent)
  :  QDialog(parent) //, context_menu_provider_(nullptr), pm_runtime_(nullptr)
{

 main_layout_ = new QVBoxLayout;

 wev_scroll_area_ = new QScrollArea(this);

 wev_ = new SVG_PDF_Web_Engine_View(this);
 //wev->setGeometry(0,0,700,600);

//?
 wep_ = new SVG_PDF_Web_Engine_Page;

 QObject::connect(wep_, &SVG_PDF_Web_Engine_Page::urlChanged,[this](const QUrl &url)
 {
  QString file_path = ROOT_FOLDER "/../testdia/logs/log.txt";

  QFile f(file_path);
  if (f.open(QIODevice::WriteOnly | QIODevice::Append))
  {
   QTextStream qts(&f);
   qts << "\n\nr: " << QDateTime::currentDateTime().toString() << "\n" << url.toString();
  }
  f.close();

  qDebug() << "r:" << url.toString();
  //? check_url_patterns(url.toString().prepend("urlChanged!"));
 });

 QObject::connect(wep_, &SVG_PDF_Web_Engine_Page::navRequest,[this](const QUrl &url){
  qDebug() << "req:" << url.toString();
  //? check_url_patterns(url.toString().prepend("navRequest!"));
 });


 QObject::connect(wep_, &SVG_PDF_Web_Engine_Page::linkHovered,[](const QUrl &url){
  qDebug() << "H:" << url.toString();
 });

//? //?
// myp_ = new MyPage;
// QWebChannel* channel = new QWebChannel(wev_);
// channel->registerObject(QStringLiteral("content"), myp_);
// wep_->setWebChannel(channel);

 //?

 qwc_context_ = new QWC_Context;

 QWebChannel* channel = new QWebChannel(wev_);
 channel->registerObject(QStringLiteral("qwc_context"), qwc_context_);
 wep_->setWebChannel(channel);

 wev_->setPage(wep_);

 connect(wev_, SIGNAL(snapshot_saved(QString)), this, SIGNAL(snapshot_saved(QString)));

// connect(wev_, &RPDF_Web_Engine_View::youtube_download_requested,
//   this, &SVG_PDF_Web_View_Dialog::youtube_download_requested);

 //?this->winId();

//?

// QString url = "http://amyneustein.com/-prv/tri/composite/bases/p021.htm";
 QString url = "file:///home/nlevisrael/docker/gits/torq-wip/pres/introduction/composite/bases/p021.htm";




 qDebug() << "url = " << url;
 //
 wep_->load(QUrl(url));

// wep_->load(QUrl("https://www.google.com/maps/place/Philadelphia,+PA/@39.9558052,-75.1581506,13.75z/data=!4m5!3m4!1s0x89c6b7d8d4b54beb:0x89f514d88c3e58c1!8m2!3d39.9525839!4d-75.1652215"));

 qtw_ = new QTabWidget(this);

 wev_scroll_area_->setWidget(wev_);

// wev_->resize(1000, 1000); //wep_->contentsSize().toSize());

 wev_->set_scroll_container(wev_scroll_area_);
 qtw_->addTab(wev_scroll_area_, "Tour");

 QString iurl = ROOT_FOLDER "/../testdia/matterport/info.html";

 iwev_ = new QWebEngineView(this);
 iwev_->page()->load(QUrl("file:///" + iurl));
 qtw_->addTab(iwev_, "360 Provider Info");

 qtw_->tabBar()->setShape(QTabBar::TriangularNorth);
 //?
 qtw_->setStyleSheet(tab_style_sheet_());


 url_patterns_frame_ = new QFrame(this);
 url_patterns_table_ = new QTableWidget(this);
 url_patterns_layout_ = new QVBoxLayout;
 url_patterns_layout_->addWidget(url_patterns_table_);
 url_patterns_frame_->setLayout(url_patterns_layout_);

 qtw_->addTab(url_patterns_frame_, "URL Patterns");

 url_patterns_table_->setColumnCount(6);
 url_patterns_table_->setRowCount(0);

 // // urlChanged!.*www.google.com/maps/place/([\w+]+) <QString-> PN:`.1
 url_patterns_table_->setHorizontalHeaderLabels({"Context", "Secondary", "Pettern Expression", "C++ Procedure", "Arguments", ""});

 url_patterns_table_->setColumnWidth(0, 60);

 url_patterns_table_->setColumnWidth(2, 130);
// url_patterns_table_->setSt

 url_patterns_table_->setColumnWidth(5, 150);
// url_patterns_table_->setColumnWidth(4, 50);
// url_patterns_table_->setColumnWidth(5, 60);


 url_patterns_table_->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);


 QHBoxLayout* add_row_layout = new QHBoxLayout;
 QPushButton* add_row_button = new QPushButton("Add", this);
 add_row_layout->addStretch();
 add_row_layout->addWidget(add_row_button);
 add_row_layout->addStretch();

 url_patterns_layout_->addLayout(add_row_layout);

// connect(add_row_button, &QPushButton::clicked,
//   [this]()
//   {
//    handle_add_url_patterns_row();
//   });


 url_patterns_layout_->addStretch();

// url_patterns_table_->horizontalHeaderItem(3)->set



 main_layout_->addWidget(qtw_);

 button_box_ = new QDialogButtonBox(this);

 //?url_label_ = new QLabel(this);
  //?url_label_->setText(url);

// name_qle_ = new QLineEdit(this);

 button_ok_ = new QPushButton("OK");
 //? button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 //?button_proceed_->setDefault(false);
 //?button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 //?button_ok_->setEnabled(false);

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 //?button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);


 //?connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 //->setCentralWidget(qtw);
 //mw->setGeometry(5,50,900,650);

 //wev->show();
 //this->show();

}

void SVG_PDF_Web_View_Dialog::resizeEvent(QResizeEvent* resize_event)
{
 Q_EMIT web_view_geometry_updated(get_web_view_geometry());
}

void SVG_PDF_Web_View_Dialog::moveEvent(QMoveEvent* move_event)
{
 if(this->isVisible())
   Q_EMIT web_view_geometry_updated(get_web_view_geometry());
}


QRect SVG_PDF_Web_View_Dialog::get_web_view_geometry()
{
 return wev_scroll_area_->geometry().translated
   (wev_scroll_area_->mapToGlobal(QPoint(0, 0)));
}


void SVG_PDF_Web_View_Dialog::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
 mouseEvent->ignore();
}


void SVG_PDF_Web_View_Dialog::mousePressEvent(QMouseEvent* mev)
{
 Qt::MouseButton mb = mev->button();

 if(mb == Qt::RightButton)
 {
  QWidget* qw = qtw_->currentWidget();
  if(SVG_PDF_Web_Engine_View* rwev = qobject_cast<SVG_PDF_Web_Engine_View*>(qw))
  {
//?   rwev->generate_context_menu(mev->globalPos(), (n8) this, nullptr, mev);
   mev->accept();
   return;
  }
 }
 mev->ignore();
}



SVG_PDF_Web_View_Dialog::~SVG_PDF_Web_View_Dialog()
{

}



