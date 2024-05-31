
#include "dhax-pdf-view-dialog.h"

//#include "clg-db-antemodel.h";

#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QDockWidget>
#include <QFileInfo>

#include <QDesktopWidget>

#include <QPlainTextEdit>
#include <QTextStream>
#include <QProgressBar>

#include <QFileDialog>

#include <QProcess>

#include <QTableWidget>

#include <QMessageBox>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QHeaderView>

#include <QListWidget>



#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#include "subwindows/pdf-document-widget.h"


#include "kans.h"
#include "textio.h"



#include "styles.h"
//#include "silotypes/ndp-project/ndp-project.h"
//#include "silotypes/ndp-project/ndp-project-initial.h"

//?USING_QSNS(Cy_Mesh)

DHAX_PDF_View_Dialog::DHAX_PDF_View_Dialog(QWidget* parent, QString pdf_file_path) //, NDP_Antemodel* antemodel)//, QString url, QWN_XMLDB_Configuration* config)
 : QDialog(parent), pdf_file_path_(pdf_file_path)//, antemodel_(antemodel)//, config_(config)
{

 main_layout_ = new QVBoxLayout();

 //controls_dock_widget_ = nullptr;
 //controls_frame_ = new QFrame(this);

 controls_layout_ = new QVBoxLayout;

// controls_dock_widget_ = new QDockWidget(this);
// controls_dock_widget_->setObjectName(QString::fromUtf8("controlsDockWidget"));
// controls_dock_widget_->setEnabled(true);
// controls_dock_widget_->setFloating(false);
// controls_dock_widget_->setFeatures(QDockWidget::AllDockWidgetFeatures);
// controls_dock_widget_->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);

// QWidget* dockWidgetContents = new QWidget(this);
// dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
// QVBoxLayout* vboxLayout = new QVBoxLayout;//(dockWidgetContents);

 QHBoxLayout* hboxLayout = new QHBoxLayout(); // dockWidgetContents);
 hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
 hboxLayout->setContentsMargins(4, 0, 4, 0);
 QSpacerItem* horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(horizontalSpacer);

 QHBoxLayout* _2 = new QHBoxLayout();
 _2->setObjectName(QString::fromUtf8("_2"));

 page_label_ = new QLabel(this);
 page_label_->setObjectName(QString::fromUtf8("page_label_"));

 _2->addWidget(page_label_);

 page_spin_box_ = new Reverse_Spin_Box(this);
 //?page_spin_box_->setObjectName(QString::fromUtf8("page_spin_box_"));
//? page_spin_box_->setEnabled(false);

// page_spin_box_->setMaximum(0);
// page_spin_box_->setMinimum(-8);

 //page_spin_box_->set_maximum()


 _2->addWidget(page_spin_box_);


 hboxLayout->addLayout(_2);

 QSpacerItem* horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(horizontalSpacer_2);

 QHBoxLayout* _3 = new QHBoxLayout();
 _3->setObjectName(QString::fromUtf8("_3"));

 search_label_ = new QLabel(this);
 search_label_->setObjectName(QString::fromUtf8("search_label_"));
 search_label_->setTextFormat(Qt::AutoText);

 _3->addWidget(search_label_);

 search_line_edit_ = new QLineEdit(this);
 search_line_edit_->setObjectName(QString::fromUtf8("search_line_edit_"));
 search_line_edit_->setEnabled(false);

 _3->addWidget(search_line_edit_);

 search_combo_box_ = new QComboBox(this);
 search_combo_box_->setObjectName(QString::fromUtf8("search_combo_box_"));
 search_combo_box_->setEnabled(false);

 _3->addWidget(search_combo_box_);

 find_button_ = new QPushButton(this);
 find_button_->setObjectName(QString::fromUtf8("find_button_"));
 find_button_->setEnabled(false);

 _3->addWidget(find_button_);

 clear_button_ = new QPushButton(this);
 clear_button_->setObjectName(QString::fromUtf8("clear_button_"));
 clear_button_->setEnabled(false);

 _3->addWidget(clear_button_);

 box_button_ =  new QPushButton("Stencil", this);
 _3->addWidget(box_button_);

 hboxLayout->addLayout(_3);

 QSpacerItem* spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(spacerItem);

 scale_label_ = new QLabel(this);
 scale_label_->setObjectName(QString::fromUtf8("label"));

 hboxLayout->addWidget(scale_label_);

 scale_combo_box_ = new QComboBox(this);
 scale_combo_box_->setObjectName(QString::fromUtf8("scale_combo_box_"));
 scale_combo_box_->setEnabled(true);

 hboxLayout->addWidget(scale_combo_box_);

 QSpacerItem* horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

 hboxLayout->addItem(horizontalSpacer_3);

 controls_layout_->addLayout(hboxLayout);

// vboxLayout->addLayout(hboxLayout);
// dockWidgetContents->setLayout(vboxLayout);
// controls_frame_->setLayout(controls_layout_);

 //controls_layout_->addWidget(controls_frame_);

 main_layout_->addLayout(controls_layout_);

// controls_frame_

// controls_dock_widget_->setWidget(dockWidgetContents);
 //
 //local_main_window_->addDockWidget(static_cast<Qt::DockWidgetArea>(4), controls_dock_widget_);


// connect(scale_combo_box_, SIGNAL(currentIndexChanged(int)),
//         centerview_, SLOT(scale_document(int)));


// connect(centerview_, SIGNAL(activate_screenshot()),
//         this, SLOT(activate_screenshot_requested()));



 button_box_ = new QDialogButtonBox(this);

 button_close_ = new QPushButton("Close");
// button_ok_ = new QPushButton("OK");
// button_proceed_ = new QPushButton("Proceed");
// button_cancel_ = new QPushButton("Cancel");
// button_ok_->setDefault(false);
// button_ok_->setAutoDefault(false);
// button_proceed_->setDefault(false);
// button_proceed_->setAutoDefault(false);
// button_cancel_->setDefault(true);
// button_ok_->setEnabled(false);

// button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
// button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
// button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 button_box_->addButton(button_close_, QDialogButtonBox::AcceptRole);

 //connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));


 pdf_document_widget_ = new PDF_Document_Widget(this);

 connect(pdf_document_widget_, SIGNAL(save_stencil_to_file_requested()),
   this, SLOT(handle_save_stencil_to_file_requested()));

 connect(pdf_document_widget_, SIGNAL(open_stencil_from_file_requested()),
   this, SLOT(handle_open_stencil_from_file_requested()));

 connect(pdf_document_widget_, SIGNAL(ocr_conversion_requested()),
   this, SLOT(handle_ocr_conversion_requested()));


 pdf_document_widget_->setDocument(pdf_file_path_);

  //  "/home/nlevisrael/NDP/pain-management-center-new-patient-history-2012.pdf"

// QFrame* qf = new QFrame(this);
// QVBoxLayout* pdf_document_vbox = new QVBoxLayout;
// pdf_document_vbox->addWidget(pdf_document_widget_);
// qf->setLayout(pdf_document_vbox);

// pdf_document_scroll_area_ = new QScrollArea(this);
// pdf_document_scroll_area_->setWidget(pdf_document_widget_);
// pdf_document_widget_->set_surrounding_scroll_area(pdf_document_scroll_area_);

 pdf_document_scroll_area_ = nullptr;

 int nop = pdf_document_widget_->number_of_pages();

 page_spin_box_->set_maximum(nop - 1);

 connect(page_spin_box_, SIGNAL(value_changed(int)),
         pdf_document_widget_, SLOT(setPage(int)));

 connect(pdf_document_widget_, SIGNAL(pageChanged(int)),
         page_spin_box_, SLOT(set_value(int)));


//? qf->setMinimumSize(300, 300);

//? pdf_document_vbox->setSizeConstraint(QLayout::SetFixedSize);

 go_button_ = new QPushButton("Go", this);

 open_button_ = new QPushButton("Open", this);


 connect(go_button_, &QPushButton::clicked, [this]
 {
  pdf_file_path_ = url_line_edit_->text();
  pdf_document_widget_->setDocument(pdf_file_path_);
 });

 connect(open_button_, &QPushButton::clicked, [this]
 {
  QFileInfo qfi(pdf_file_path_);

  QString dir = qfi.absoluteDir().absolutePath();

  QString fp = QFileDialog::getOpenFileName(this, "Open PDF File", dir, "*.pdf");

  pdf_document_widget_->setDocument(fp);

  int nop = pdf_document_widget_->number_of_pages();

  if(nop == 0)
  {
   QMessageBox::information(this,
     "Load Error", "PDF File Not Recognized.  File not loaded.");

   pdf_document_widget_->setDocument(pdf_file_path_);
  }
  else
  {
   pdf_file_path_ = fp;
   url_line_edit_->setText(pdf_file_path_);
   //pdf_document_widget_->setDocument(pdf_file_path_);
   page_spin_box_->set_maximum(nop);
  }
 });

 url_label_  = new QLabel("URL", this);
 url_line_edit_ = new QLineEdit(this);

 url_layout_ = new QHBoxLayout;
 url_layout_->addWidget(url_label_);
 url_layout_->addWidget(url_line_edit_);
 url_layout_->addWidget(go_button_);
 url_layout_->addWidget(open_button_);


 main_layout_->addWidget(pdf_document_widget_);
 main_layout_->addLayout(url_layout_);

// QString colorful_button_style_sheet = colorful_button_style_sheet_();
// QString colorful_button_style_sheet_down = colorful_button_style_sheet_down_();
// QString colorful_button_quiet_style_sheet = colorful_button_quiet_style_sheet_();


// go_button_ = new QPushButton("Go", this);
// close_button_ = new QPushButton("Close", this);
// go_button_->setStyleSheet(colorful_button_style_sheet);

 box_button_->setCheckable(true);

 button_close_->setStyleSheet(basic_button_style_sheet_());

// go_button_layout_ = new QHBoxLayout;
// go_button_layout_->addStretch();
// go_button_layout_->addWidget(go_button_);
// go_button_layout_->addStretch();

// main_layout_->addLayout(go_button_layout_);

// close_button_layout_ = new QHBoxLayout;
// close_button_layout_->addStretch();
// close_button_layout_->addWidget(close_button_);
// close_button_layout_->addStretch();

// main_layout_->addLayout(close_button_layout_);

// connect(go_button_, SIGNAL(clicked()), this,
//         SLOT(go_button_clicked()));




 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 retranslate_ui();

 Poppler::Document* popd = pdf_document_widget_->document();


 QJsonDocument qjd;
 QJsonArray qja_pages;

 QSet<int> arrows {
  3, 5, 7, 9, 11, 13, 15, 17, 20, 25, 27, 29, 34, 37, 40, 42, 44, 46,
  48, 51, 54, 56, 59, 61, 66, 69, 74, 77, 80, 84, 87, 89, 91, 94, 96,
  98, 101, 103, 109, 111, 113, 116, 118, 120, 122, 124, 127, 129, 132,
  134, 136, 139, 141, 147, 150, 152, 154, 160, 162, 164, 172, 175, 178,
  182, 197, 200, 204, 208, 210, 213, 216, 219, 221, 223, 225, 227, 229,
  231, 233, 235, 237, 240, 242, 244, 246, 248, 250, 252, 254, 256, 258,
  260, 264, 266, 268, 271, 274, 277, 280, 282, 284, 287, 289, 292, 294,
  296, 298, 301, 304, 306, 309, 313, 315, 317, 319, 321, 326, 329, 336,
  338, 344, 347, 351, 354, 358, 360, 364, 366, 369, 372, 375, 378, 381,
  385, 393, 395, 401, 412, 414, 416, 418, 421, 424, 426, 429, 432
 };

 QStringList titles {
  "SAHANA - 2013  September 5 - Just to vent  --AN.pdf",
  "SAHANA - 2016.02.04 - Hot Springs Spa (while he was planning to kidnap) --Comments AN.pdf",
  "SAHANA - 2016.02.18 - Re_ Bulldog Tracks ingredient list --Comments AN.pdf",
  "SAHANA - 2016.03.09 - Re_ The kids --AN Comments.pdf",
  "SAHANA - 2016.03.10  - Re_ Indio and Tynan --AN comments.pdf",
  "SAHANA - 2016.03.10  - Re_ Indio and Tynan--Comments AN.pdf",
  "SAHANA - 2016.03.11 - Re_ Kids --AN Comments.pdf",
  "SAHANA - 2016.03.17 - Re_ photo from earlier --AN Comments.pdf",
  "SAHANA - 2016.03.24 - Re_ Resolution --AN Comments.pdf",
  "SAHANA - 2016.03.27 - Re_ Tuesday --AN Comments.pdf",
  "SAHANA - 2016.03.29 - last night  -AN Comments.pdf",
  "SAHANA - 2016.03.29 - Re_ Thursday  --AN Comments.pdf",
  "SAHANA - 2016.04.02 - Re_ Possible schedule for the interim  ---AN.pdf",
  "SAHANA - 2016.04.06 - Re_ Wednesday  --AN.pdf",
  "SAHANA - 2016.04.07 - Re_ Your Amazon.com order of Sanuk Kids Sideline Boys-K  --AN.pdf",
  "SAHANA - 2016.04.08 - Re_ Kid stuff  -AN.pdf",
  "SAHANA - 2016.04.12 - Re_ Talking to the kids  --AN.pdf",
  "SAHANA - 2016.12.15 - Re_ Indio and Tynan_s rashes  --AN.pdf",
  "SAHANA - 2017.01.04  - Re_ February 26th --AN.pdf",
  "SAHANA - 2017.01.05 - Re_ mediation --AN.pdf",
  "SAHANA - 2017.02.08 - Re_ The boys healthcare Feb 7_ 2017 --AN.pdf",
  "SAHANA - 2017.02.16.- Re_ Adobe _ Artwork--AN.pdf",
  "SAHANA - 2017.02.22 - Re_ Feb 26th --AN.pdf",
  "SAHANA - 2017.03.08 - Re_ March 26_ 2017 --AN.pdf",
  "SAHANA - 2017.12.14 - Re_ Indio _ Tynan Therapy --AN.pdf",
  "SAHANA - 2018.01.03 Re_ Monday 8th --AN.pdf",
  "SAHANA - 2018.01.29 Re_ The Week Ahead at Roots and Branches_ January 29- February 2 --AN.pdf",
  "SAHANA - 2018.01.31 Re_ Tuesday--AN.pdf",
  "SAHANA - 2018.02.07 Re_ This week --AN.pdf",
  "SAHANA - 2018.02.26 Re_ Next Week --AN.pdf",
  "SAHANA - 2018.03.09 Re_ Spring Break   --AN.pdf",
  "SAHANA - 2018.03.15 Exchanges this weekend. AN.pdf",
  "SAHANA - 2018.03.21 Fwd_ Thursday Field Trip  --AN.pdf",
  "SAHANA - 2018.03.21 Re_ March 22nd _ 23rd --AN.pdf",
  "SAHANA - 2018.03.25 Re_ March 28th _ 29th  --AN.pdf",
  "SAHANA - 2018.04.05 Memorial Day weekend --AN.pdf",
  "SAHANA - 2018.04.13 Re_ exchanges this weekend  --AN.pdf",
  "SAHANA - 2018.12.15 - Phone call --AN.pdf",
  "SAHANA - 2019-1-9 - 2019 Schedule  --AN.pdf",
  "SAHANA - 2019-10-12 - Tynan's Skin Followup --AN.pdf",
  "SAHANA - 2019-10-13 - More time with mom --AN.pdf",
  "SAHANA - 2019-1-12 - Schooling  --AN.pdf",
  "SAHANA - 2019-1-22 - Lunch with boys  --AN.pdf",
  "SAHANA - 2019-2-4 - Boys Lunch Containers  --AN.pdf",
  "SAHANA - 2019-3-26 - The boys schooling --AN.pdf",
  "SAHANA - 2019-3-5 - Showing up for the boys --AN.pdf",
  "SAHANA - 2019-4-22 - Family Fun Night --AN.pdf",
  "SAHANA - 2019-6-17 - Phone Call To Boys --AN.pdf",
  "SAHANA - 2019-6-18 - Tynan Rash --AN.pdf",
  "SAHANA - 2019-6-1 - Lunch --AN.pdf",
  "SAHANA - 2019-6-4 - Lunch with our boys --AN.pdf",
  "SAHANA - 2019-7-18 - Beach Trip --AN.pdf",
  "SAHANA - 2019-7-22 - Kids don't want to be with mom --AN.pdf",
  "SAHANA - 2024.02.18 - 16-CVD-1087 - Sahana v. Fiscus --AN.pdf",
  "SAHANA - 2024.03.09 - Court ordered phone call denied  --AN.pdf",
  "SAHANA - 2024.03.09 - Denying Tynan basketball today   --AN.pdf",
  "SAHANA - 2024.03.16 - Harrassing and stalking video recording   --AN.pdf",
  "SAHANA - 2022.12.20 - Phones for Indio & Tynan --AN.pdf",
  "SAHANA - 2022.12.21 - Tynan missed school - again - Dec 19 --AN.pdf",
  "SAHANA - 2023.01.20 Indio request --AN.pdf",
  "SAHANA - 2023.02.15 Boys summer basketball camp --AN.pdf",
  "SAHANA - 2023.03.20 Reminder - Your Son_s Spring Basketball League  --AN.pdf",
  "SAHANA - 2023.04.05 Tynan school events --AN.pdf",
  "SAHANA - 2023.04.14 Boys' invite to Carlos B-day Party  --AN.pdf",
  "SAHANA - 2023.05.08 Indio & Tynan Fiscus  --AN.pdf",
  "SAHANA - 2023.08.12 Boys' visitations with you  --AN.pdf",
  "SAHANA - 2023.10.01 - Upcoming visitation weekend - Oct 6-8  --AN.pdf",
  "SAHANA - 2023.10.30 - Indio basketball training  --AN.pdf",
  "SAHANA - 2023.11.15 - Visitation schedule for rest of Nov  --AN.pdf",
  "SAHANA - 2023.11.21 - Tynan water and headaches  --AN.pdf",
  "SAHANA - 2023.12.06 - Hank's Birthday Party Invite for Indio  --AN.pdf",
  "SAHANA - 2023.12.06 - Hank's Birthday Party Invite for Indio --AN.pdf",
  "SAHANA - 2024.01.31 - Our boys' schoolwork restriction  ---AN.pdf",
  "SAHANA - 2019-10-13 - More time with mom --AN.pdf",
  "SAHANA - 2019-10-23 - Nov 5th & Nov 11th --AN.pdf",
  "SAHANA - 2019-10-28 - Appt with Dr Curran --AN.pdf",
  "SAHANA - 2019-10-28 - Dinner this week --AN.pdf",
  "SAHANA - 2019-11-1 - Lunch Tomorrow --AN.pdf",
  "SAHANA - 2019-12-10 - Tynan's Skin Recap & Request --AN.pdf",
  "SAHANA - 2019-12-11 - Tynan's skin (from Shannon Mancz, teacher) --AN.pdf",
  "SAHANA - 2019-12-12 - lunch at school --AN.pdf",
  "SAHANA - 2019-12-16 - christmas break proposal --AN.pdf",
  "SAHANA - 2019-12-16 - Christmas Florida trip --AN.pdf",
  "SAHANA - 2019-12-16 - Tynan dentist appt recap --AN.pdf",
  "SAHANA - 2020-1-10 - Checking in --AN.pdf",
  "SAHANA - 2020-1-23 - Friday 1_24 --AN.pdf",
  "SAHANA - 2020-2-15 - Response to Fri text  --AN.pdf",
  "SAHANA - 2020-2-4 - Lunch with boys Priority topic for next session  --AN.pdf",
  "SAHANA - 2020-2-4 - Tynan spring soccer league  --AN.pdf",
  "SAHANA - 2020-3-6 - Friday  --AN.pdf",
  "SAHANA - 2020-10-30 - Re_ Exchange next week  --AN.pdf",
  "SAHANA - 2020-3-11 - weekend early pickup --AN.pdf",
  "SAHANA - 2020-3-13 - Your Son's Basketball Roster  --AN.pdf",
  "SAHANA - 2020-3-14 - School --AN.pdf",
  "SAHANA - 2020-3-24 - schedule for Indio and Tynan --AN.pdf",
  "SAHANA - 2020-4-22 - Tynan shaved eyebrows --AN.pdf",
  "SAHANA - 2020-4-25 - Boys' school work  --AN.pdf",
  "SAHANA - 2020-5-31 - Concern for Indio and Tynan  --AN.pdf",
  "SAHANA - 2020-6-24 - Summer exchanges --AN.pdf",
  "SAHANA - 2020-7-28 - Correct email address --AN.pdf",
  "SAHANA - 2020-8-13 - Exchange Tomorrow --AN.pdf",
  "SAHANA - 2020-9-23 - Request to meet at exit 228  -AN.pdf",
  "SAHANA - 2021.02.24 Re_ Exchange Friday --AN.pdf",
  "SAHANA - 2021.04.27 - Re_ June day switch --AN.pdf",
  "SAHANA - 2021.06.24 - Re_ Out of town  --AN.pdf",
  "SAHANA - 2021.07.10 Boys in TN this week  --AN.pdf",
  "SAHANA - 2021.07.14 Exchange July 16  --AN.pdf",
  "SAHANA - 2021.07.26 - Re_ Indio ear infection --AN.pdf",
  "SAHANA - 2021.08.16 Re_ Boys_ baseball this Fall - Aug to Oct  --AN.pdf",
  "SAHANA - 2021.09.26 Boys' lunch containers care --AN.pdf",
  "SAHANA - 2021.10.07 Fwd_ Boys baseball games Oct 8 _ 9  --AN.pdf",
  "SAHANA - 2021.11.18 Re_ B-day party for Tynan_s friend  --AN.pdf",
  "SAHANA - 2021.12.08 Re_ Children and their well-being --AN.pdf",
  "SAHANA - 2021.12.09 Boys 2Q progress reports and dentist visit  -AN.pdf",
  "SAHANA - 2021.12.14 Re_ Packages for boys  --AN.pdf",
  "SAHANA - 2021.12.27 Re_ MLK day --AN.pdf",
  "SAHANA - 2022.1.16 - Winter storm  --AN.pdf",
  "SAHANA - 2022.10.20 - Oct 19th_ Indio Whereabouts  --AN.pdf",
  "SAHANA - 2022.10.20 - Oct 20 update --AN.pdf",
  "SAHANA - 2022.10.28 - Co-parenting Therapy --AN.pdf",
  "SAHANA - 2022.10.6 - Oct 4th & 5th - Kids' Whereabouts --AN.pdf",
  "SAHANA - 2022.11.23 - Nov 19-20 phone call to our boys_ Nov 17 Indio call --AN.pdf",
  "SAHANA - 2022.11.24 - Text Messages Not Going Through --AN.pdf",
  "SAHANA - 2022.1.17 - Winter Storm Email 2 --AN.pdf",
  "SAHANA - 2022.2.24 - Re MPTLL Spring 2022 - baseball --AN.pdf",
  "SAHANA - 2022.2.9 - Tynan phone call --AN.pdf",
  "SAHANA - 2022.3.29 - Special Event request --AN.pdf",
  "SAHANA - 2022.4.20 - Tynan's rash --AN.pdf",
  "SAHANA - 2022.5.12 - Indio text request to attend baseball practices this weekend --AN.pdf",
  "SAHANA - 2022.5.5 - Tynan field trip --AN.pdf",
  "SAHANA - 2022.6.29 - Text messages for our boys --AN.pdf",
  "SAHANA - 2022.7.3 - Boys dentist updates --AN.pdf",
  "SAHANA - 2022.8.12 - Re_ Boys events this week and next - 2022.08.12 12.29 --AN.pdf",
  "SAHANA - 2022.8,26 - Re_ Communication and boys events --AN.pdf",
  "SAHANA - 2022.8.4 - Re_ Welcome 11U South Charlotte Football  --AN.pdf",
  "SAHANA - 2022.8.5 - Re_ Indio Ear infection  --AN.pdf",
  "SAHANA - 2022.8.7 - Re_ Welcome 11U South Charlotte Football --AN.pdf",
  "SAHANA - 2022.9.28 - Sept 27th Recap_ Homework_ Exchange_ Activities_ Appointments --AN.pdf",
  "SAHANA - 2022.9.2 - Re_ Phone calls to our boys this week --AN.pdf",
  "SAHANA - 2022.9.6 - Re_ Alarming text message to Tynan --AN.pdf",
  "Gmail - Coaching our sons' basketball - 2024.03.19 12.40--AN.pdf",
  "Gmail - Fwd_ Your Son's Basketball Roster & Schedule - 2024.03.19 19.59.pdf",
  "Gmail - Fwd_ Your Son's Basketball Roster & Schedule - 2024.03.20 09.32.pdf",
  "Gmail - Indio DC trip update - 2024.03.27 10.10.pdf",
  "Gmail - Indio not at basketball league today_ - 2024.03.23 14.51  --AN.pdf",
  "Gmail - Re_ Indio DC trip update - 2024.03.27 16.38  --AN.pdf",
  "Gmail - Tynan MVP Wed night - 2024.03.22 11.52.pdf",
 };

 int arrow_count = 0;
 int page_count = 0;

 QMap<QString, int> locals;

 for(int i = 0; i < popd->numPages(); ++i)
 {
  auto& vec = pdf_document_widget_->pdf_annotations_.value(i);


  Poppler::Page* page = popd->page(i + 1);

  if(!page)
    continue; //?

  QSizeF qsf = page->pageSizeF();


  QJsonObject qjo;

  QJsonArray qja_size;
  qja_size.append(qsf.width());
  qja_size.append(qsf.height());

  qjo.insert("page", i + 1);

  qjo.insert("page-size", qja_size);

  QString title;

  if(arrows.contains(i + 1))
  {
   ++arrow_count;
   qjo.insert("arrow", true);
   qjo.insert("count", arrow_count);
  }
  else
  {
   title = titles[arrow_count];
   ++locals[title];
   ++page_count;
   qjo.insert("arrow", false);
   qjo.insert("count", page_count);
   qjo.insert("local", locals[title]);
   qjo.insert("title", title);
  }


  if(!vec.isEmpty())
  {
   QJsonArray qja;

   for(auto& pr: vec)
   {
    QJsonObject qjo1;
    qjo1.insert("text", pr.first);

    QJsonArray qjo_boundary;
    qjo_boundary.append(pr.second.x());
    qjo_boundary.append(pr.second.y());
    qjo_boundary.append(pr.second.width());
    qjo_boundary.append(pr.second.height());

    qjo1.insert("boundary", qjo_boundary);
    qja.append(qjo1);

   }
   qjo.insert("notes", qja);
  }

  qja_pages.append(qjo);
 }

 qjd.setArray(qja_pages);

 KA::TextIO::save_file(pdf_file_path_ + ".json", qjd.toJson());


 Poppler::Page* popg = popd->page(1);
 QList<Poppler::Annotation*> popas = popg->annotations();

 for(Poppler::Annotation* popa : popas)
 {
//  QString aun = popa->uniqueName();
//  qDebug() << "AUN: " << aun;

  Poppler::Annotation::SubType antype = popa->subType();

  if(antype == Poppler::Annotation::AHighlight)
  {
   QString c = popa->contents();
   qDebug() << "c = " << c;

   QString un = popa->uniqueName();
   qDebug() << "u = " << un;

   Poppler::HighlightAnnotation* popha = dynamic_cast<Poppler::HighlightAnnotation*>(popa);

   QRectF qrf = popha->boundary();

   qreal tlx = qrf.topLeft().x();
   qreal tly = qrf.topLeft().y();

   qreal brx = qrf.bottomRight().x();
   qreal bry = qrf.bottomRight().y();

   quint64 tlx_pg = tlx * popg->pageSizeF().width();
   quint64 tly_pg = tly * popg->pageSizeF().height();

   quint64 brx_pg = brx * popg->pageSizeF().width();
   quint64 bry_pg = bry * popg->pageSizeF().height();

   qDebug() << "qrf: " << qrf;

   QGraphicsScene* sc = pdf_document_widget_->scene();

   QRect qr(QPoint(tlx_pg, tly_pg), QPoint(brx_pg, bry_pg));

   sc->addRect(qr);

  }

  if(antype == Poppler::Annotation::ALink)
  {
   QString con = popa->contents();
   Poppler::LinkAnnotation* popla = dynamic_cast<Poppler::LinkAnnotation*>(popa);
   Poppler::Link* popl = popla->linkDestination();
   if(popl)
   {
    Poppler::Link::LinkType ltype = popl->linkType();
    qDebug() << "LType: " << ltype;
    if(ltype == Poppler::Link::Goto)
    {
     Poppler::LinkGoto* poplg = dynamic_cast<Poppler::LinkGoto*>(popl);
     QString fn = poplg->fileName();
     Poppler::LinkDestination popld = poplg->destination();
     QString dn = popld.destinationName();
     QString ts = popld.toString();

     //?qDebug() << ts;
    }
    else if(ltype == Poppler::Link::JavaScript)
    {
     Poppler::LinkJavaScript* popljs = dynamic_cast<Poppler::LinkJavaScript*>(popl);
     QString js = popljs->script();
     qDebug() << js;
    }

   }
  }
  if(antype == Poppler::Annotation::AFileAttachment)
  {
   QString con = popa->contents();
   QString un = popa->uniqueName();
   Poppler::FileAttachmentAnnotation* popfa = dynamic_cast<Poppler::FileAttachmentAnnotation*>(popa);
   Poppler::EmbeddedFile* popef = popfa->embeddedFile();
   QRectF qrf = popfa->boundary();

   qreal tlx = qrf.topLeft().x();
   qreal tly = qrf.topLeft().y();

   qreal brx = qrf.bottomRight().x();
   qreal bry = qrf.bottomRight().y();

   quint64 tlx_pg = tlx * popg->pageSizeF().width();
   quint64 tly_pg = tly * popg->pageSizeF().height();

   quint64 brx_pg = brx * popg->pageSizeF().width();
   quint64 bry_pg = bry * popg->pageSizeF().height();

   qDebug() << "qrf: " << qrf;

   QByteArray qba = popef->data();
   qDebug() << "QBA: " << qba;

  }
  //qDebug() << "AUN: " << aun;

 }

 //?show();
}

bool DHAX_PDF_View_Dialog::wants_box()
{
 return box_button_->isChecked();
}



#define QUUTF8

void DHAX_PDF_View_Dialog::retranslate_ui()
{
//    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PDF Viewer", 0 QUUTF8));
//    openAction->setText(QApplication::translate("MainWindow", "&Open...", 0 QUUTF8));
//    openAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0 QUUTF8));
//    exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0 QUUTF8));
//    exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0 QUUTF8));
//    increaseScaleAction->setText(QApplication::translate("MainWindow", "&Increase Scale", 0 QUUTF8));
//    increaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0 QUUTF8));
//    decreaseScaleAction->setText(QApplication::translate("MainWindow", "&Decrease Scale", 0 QUUTF8));
//    decreaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0 QUUTF8));
//    documentControlsAction->setText(QApplication::translate("MainWindow", "&Document Controls", 0 QUUTF8));
//    selectedTextAction->setText(QApplication::translate("MainWindow", "&Selected Text", 0 QUUTF8));
//    menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0 QUUTF8));
//    menu_Windows->setTitle(QApplication::translate("MainWindow", "&Windows", 0 QUUTF8));
//    controlsDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Document Controls", 0 QUUTF8));
    page_label_->setText(QApplication::translate("CLG_DB_Anteview", "Page:", 0 QUUTF8));
    search_label_->setText(QApplication::translate("MainWindow", "Search for:", 0 QUUTF8));
    search_combo_box_->clear();
    search_combo_box_->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "Forwards", 0 QUUTF8)
     << QApplication::translate("MainWindow", "Backwards", 0 QUUTF8)
    );
    find_button_->setText(QApplication::translate("MainWindow", "Find", 0 QUUTF8));
    clear_button_->setText(QApplication::translate("MainWindow", "Clear", 0 QUUTF8));
    scale_label_->setText(QApplication::translate("MainWindow", "Scale PDF Document:", 0 QUUTF8));
    scale_combo_box_->clear();
    scale_combo_box_->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "25%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "50%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "75%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "100%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "125%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "150%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "200%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "300%", 0 QUUTF8)
     << QApplication::translate("MainWindow", "400%", 0 QUUTF8)
    );
    scale_combo_box_->setCurrentIndex(3);

     //selectionDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Selected Text", 0 QUUTF8));
} // retranslateUi






DHAX_PDF_View_Dialog::~DHAX_PDF_View_Dialog()
{
// delete button_ok_;
// delete button_proceed_;
// delete button_cancel_;

 delete button_close_;

// delete url_label_;
// delete name_qle_;
}



void DHAX_PDF_View_Dialog::cancel()
{
 Q_EMIT(canceled(this));Q_EMIT(rejected());close();
// close();
}

void DHAX_PDF_View_Dialog::accept()
{
 Q_EMIT(accepted(this));
// close();
}
