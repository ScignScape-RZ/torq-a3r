
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "pdf-enhanced-search-dialog.h"

#include "styles.h"

#include "add-minimize-frame.h"
//?




#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QButtonGroup>
#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>

#include <QPlainTextEdit>
#include <QTextStream>

#include <QtMultimedia/QMediaPlayer>

#include <QPainter>
#include <QPushButton>
#include <QLabel>

//#include <QNetworkAccessManager>
//#include <QNetworkReply>

#include <QTableWidget>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QDebug>
#include <QClipboard>

#include <QProcess>

#include <QGraphicsView>
#include <QScrollArea>

//#include <QTcpServer>
//#include <QNetworkAccessManager>

#include <QHeaderView>

#include <QMenu>
#include <QAction>

#include <QListWidget>

#include <QComboBox>

#include <QGeoCoordinate>

#include "global-types.h"

//#include "case-map-gis-service.h"

PDF_Enhanced_Search_Dialog::PDF_Enhanced_Search_Dialog(QWidget* parent)
  : QDialog(parent)
{
 // // setup RZW

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("Proceed");
// button_proceed_ = new QPushButton("Edit");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

// button_proceed_->setDefault(false);
// button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setEnabled(false);

 // // unless this is being embedded ...
// button_proceed_->setEnabled(false);
 button_cancel_->setText("Close");

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
// button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

// button_ok_->setStyleSheet(colorful_toggle_button_mixed_style_sheet_());

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());


// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

// connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;
 entry_layout_ = new QVBoxLayout;

 info_group_box_ = new QGroupBox("Search", this);
 sources_group_box_ = new QGroupBox("Sources", this);
 index_entry_group_box_ = new QGroupBox("Index Entry", this);

 info_group_box_layout_ = new QGridLayout(info_group_box_);

 sources_group_box_layout_ = new QVBoxLayout;

 sources_group_box_top_layout_ = new QHBoxLayout;
 sources_group_box_bottom_layout_ = new QHBoxLayout;


 sources_group_box_left_layout_ = new QFormLayout;
 sources_group_box_right_layout_ = new QGridLayout;


 lbl_local_file_ = new QLabel("Local File", this);
 le_local_file_ = new QLineEdit(this);
 le_local_file_->setPlaceholderText("(local file path)");

 sources_group_box_top_layout_->addWidget(lbl_local_file_);
 sources_group_box_top_layout_->addWidget(le_local_file_);

 btn_local_file_browse_ = new QPushButton("Browse", this);
 sources_group_box_top_layout_->addWidget(btn_local_file_browse_);

 btn_local_file_browse_->setStyleSheet(colorful_toggle_button_style_sheet_());


 le_meta_index_ = new QLineEdit(this);
 le_meta_index_->setPlaceholderText("(URL)");
 sources_group_box_left_layout_->addRow("Meta-Index", le_meta_index_);

 cbb_access_type_ = new QComboBox(this);
 cbb_access_type_->addItem("Public");
 cbb_access_type_->addItem("Login");
 cbb_access_type_->addItem("Keyring");
 sources_group_box_left_layout_->addRow("Access Type", cbb_access_type_);

 cbb_user_type_ = new QComboBox(this);
 cbb_user_type_->addItem("Reader");
 cbb_user_type_->addItem("Author");
 cbb_user_type_->addItem("Editor");
 cbb_user_type_->addItem("Admin");
 sources_group_box_left_layout_->addRow("User Type", cbb_user_type_);

  QTextEdit* address_text_edit = new QTextEdit(this);
  address_text_edit->setPlaceholderText("Enter username then password, or enter security code");
  sources_group_box_right_layout_->addWidget(address_text_edit, 0, 0, 1, 2);
  address_text_edit->setMaximumHeight(65);
  sources_group_box_right_layout_->addWidget(
    new QLabel("Credentials (if needed)", this), 1, 1);
  sources_group_box_right_layout_->setColumnStretch(0, 1);



// cb_state_or_province_ = new QComboBox(this);


// cb_state_or_province_->setMaxVisibleItems(12);
// cb_state_or_province_->setStyleSheet("combobox-popup: 0;");

// sources_group_box_left_layout_->addRow("Meta-Index", le_meta_index_);
// sources_group_box_left_layout_->addRow("State/Territory\nor Province", cb_state_or_province_);

// sources_group_box_bottom_layout_->addLayout(sources_group_box_left_layout_);

// sources_group_box_right_layout_ = new QVBoxLayout;
// sources_group_box_right_layout_->addWidget(new QLabel("Your address (optional):", this));
// QTextEdit* address_text_edit = new QTextEdit(this);
// address_text_edit->setPlaceholderText("Enter address here, or leave empty");
// sources_group_box_right_layout_->addWidget(address_text_edit);
// address_text_edit->setMaximumHeight(65);


 sources_group_box_bottom_layout_->addLayout(sources_group_box_left_layout_);
 sources_group_box_bottom_layout_->addLayout(sources_group_box_right_layout_);

 credentials_file_layout_ = new QHBoxLayout;

 lbl_credentials_file_ = new QLabel("Credentials File", this);
 le_credentials_file_ = new QLineEdit("(local file path)");

 btn_load_credentials_ = new QPushButton("load", this);
 btn_load_credentials_->setMaximumHeight(30);
 btn_load_credentials_->setMaximumWidth(50);
 btn_set_credentials_file_ = new QPushButton("set", this);
 btn_set_credentials_file_->setMaximumHeight(30);
 btn_set_credentials_file_->setMaximumWidth(50);

 btn_load_credentials_->setStyleSheet(colorful_small_button_style_sheet_alt_());
 btn_set_credentials_file_->setStyleSheet(colorful_small_button_style_sheet_alt_());

 btn_load_credentials_->setMaximumHeight(21);
 btn_set_credentials_file_->setMaximumHeight(21);

 credentials_file_layout_->addWidget(lbl_credentials_file_);
 credentials_file_layout_->addWidget(le_credentials_file_);
 credentials_file_layout_->addWidget(btn_load_credentials_);
 credentials_file_layout_->addWidget(btn_set_credentials_file_);



 sources_group_box_layout_->addLayout(sources_group_box_top_layout_);
 sources_group_box_layout_->addLayout(sources_group_box_bottom_layout_);

 QFrame* hl = new QFrame(this);
 hl->setFrameShape(QFrame::HLine);
 hl->setFrameShadow(QFrame::Sunken);
 sources_group_box_layout_->addWidget(hl);

 sources_group_box_layout_->addLayout(credentials_file_layout_);

 sources_group_box_->setLayout(sources_group_box_layout_);

 entry_layout_->addWidget(info_group_box_);

 le_search_term_ = new QLineEdit(this);

 lbl_search_term_ = new QLabel("Term(s):", this);

 info_group_box_layout_->addWidget(lbl_search_term_, 0, 0);
 info_group_box_layout_->addWidget(le_search_term_, 0, 1, 1, 11);

 cb_fixed_phrase_ = new QCheckBox("Fixed Phrase", this);
 info_group_box_layout_->addWidget(cb_fixed_phrase_, 1, 0, 1, 2);

 cb_free_phrase_ = new QCheckBox("Free Phrase", this);
 info_group_box_layout_->addWidget(cb_free_phrase_, 1, 3, 1, 2);

 cb_or_ = new QCheckBox("Or", this);
 info_group_box_layout_->addWidget(cb_or_, 1, 6, 1, 2);

 cb_and_ = new QCheckBox("And", this);
 info_group_box_layout_->addWidget(cb_and_, 1, 8, 1, 2);

 cb_case_sensitive_ = new QCheckBox("Case Sensitive", this);
 info_group_box_layout_->addWidget(cb_case_sensitive_, 1, 10, 1, 2);

// lbl_filter_ = new QLabel("Filters", this);
// info_group_box_layout_->addWidget(lbl_filter_, 2, 0);

 QFormLayout* qfl = new QFormLayout;
 filters_layout_ = new QVBoxLayout;

 filters_layout1_ = new QHBoxLayout;
 filters_layout2_ = new QHBoxLayout;
 filters_layout3_ = new QHBoxLayout;
 filters_layout4_ = new QHBoxLayout;

 cb_main_text_ = new QCheckBox("Main Text", this);
 cb_footnote_text_ = new QCheckBox("Foonote Text", this);
 cb_sentences_with_footnote_ = new QCheckBox("Sentences with Footnotes", this);
 cb_block_quotes_ = new QCheckBox("Block Quotes", this);
 cb_all_quotes_ = new QCheckBox("Quotes", this);
 cb_chapter_titles_ = new QCheckBox("Chapter Titles", this);
 cb_section_titles_ = new QCheckBox("Section Titles", this);
 cb_bibliography_ = new QCheckBox("Bibliography", this);
 cb_local_index_ = new QCheckBox("Index", this);
 cb_current_chapter_ = new QCheckBox("Current Chapter", this);
 cb_current_section_ = new QCheckBox("Current Section", this);
 cb_comments_edits_ = new QCheckBox("Comments/Edits", this);


 filters_layout1_->addWidget(cb_main_text_);
 filters_layout1_->addStretch();
 filters_layout1_->addWidget(cb_comments_edits_);
 filters_layout1_->addStretch();
 filters_layout1_->addWidget(cb_chapter_titles_);
 filters_layout1_->addStretch();
 filters_layout1_->addWidget(cb_section_titles_);

 filters_layout2_->addWidget(cb_sentences_with_footnote_);
 filters_layout2_->addStretch();
 filters_layout2_->addWidget(cb_footnote_text_);
 filters_layout2_->addStretch();
 filters_layout2_->addWidget(cb_bibliography_);
 filters_layout2_->addStretch();
 filters_layout2_->addWidget(cb_local_index_);

 filters_layout3_->addWidget(cb_all_quotes_);
 filters_layout3_->addStretch();
 filters_layout3_->addWidget(cb_block_quotes_);
 filters_layout3_->addStretch();
 filters_layout3_->addWidget(cb_current_chapter_);
 filters_layout3_->addStretch();
 filters_layout3_->addWidget(cb_current_section_);

 filters_layout_->addLayout(filters_layout1_);
 filters_layout_->addLayout(filters_layout2_);
 filters_layout_->addLayout(filters_layout3_);
// filters_layout_->addLayout(filters_layout4_);

 // cb_chapter_titles_->setMaximumWidth(100);

//  filters_layout_->setColumnStretch(3, 1);

// filters_layout_->addWidget(cb_section_titles_, 1, 0);
// filters_layout_->addWidget(cb_bibliography_, 1, 1);

// filters_layout_->addWidget(cb_local_index_, 1, 3);

// info_group_box_layout_->addLayout(filters_layout_, 2, 1, 2, 7);

 filters_layout_->setSpacing(0);
 filters_layout_->setContentsMargins(0, 0, 0, 0);

 QFrame* filters_f = new QFrame(this);
 filters_f->setFrameStyle(QFrame::Box | QFrame::Sunken);

//  QGridLayout* fl = new QGridLayout;
//  fl->addWidget(new QLabel("xxx"), 0, 0);


// filters_f->setMaximumWidth(300);


// QGridLayout* fl = new QGridLayout(filters_f);
// fl->addWidget(new QLabel("xxx"), 0, 0);

 filters_f->setLayout(filters_layout_);

 qfl->addRow("Filters", filters_f);

 info_group_box_layout_->addLayout(qfl, 2, 0, 1, 12);

//  info_group_box_layout_->addWidget(new QLabel("xxx"), 2, 1, 1, 8);


// info_group_box_layout_->addWidget(cb_main_text_, 2, 2, 1, 3);
// info_group_box_layout_->addWidget(cb_footnote_text_, 2, 5, 1, 3);
// info_group_box_layout_->addWidget(cb_sentences_with_footnote_, 2, 8, 1, 3);

// info_group_box_layout_->addWidget(cb_chapter_titles_, 3, 1, 1, 3);
// info_group_box_layout_->addWidget(cb_section_titles_, 3, 4, 1, 2);
// info_group_box_layout_->addWidget(cb_bibliography_, 3, 6, 1, 2);
// info_group_box_layout_->addWidget(cb_local_index_, 3, 8, 1, 2);






 entry_layout_->addWidget(sources_group_box_);


 index_entry_group_box_layout_ = new QGridLayout(index_entry_group_box_);

 lbl_index_file_ = new QLabel("File", this);
 le_index_file_ = new  QLineEdit(this);
 le_index_file_->setPlaceholderText("(local file)");
 btn_index_entry_data_ = new QPushButton("data", this);
 btn_index_entry_data_->setMaximumWidth(40);
 btn_index_entry_data_->setMaximumHeight(20);

 btn_index_entry_data_->setStyleSheet(qmessagebox_button_style_sheet());


 index_entry_group_box_layout_->addWidget(lbl_index_file_, 0, 0);
 index_entry_group_box_layout_->addWidget(le_index_file_, 0, 1, 1, 2);
 index_entry_group_box_layout_->addWidget(btn_index_entry_data_, 0, 3);

 lbl_index_entry_term_ = new QLabel("Term", this);
 le_index_entry_term_ = new QLineEdit(this);
 le_index_entry_term_->setPlaceholderText("(heading)");
 lbl_index_entry_number_ = new QLabel("#", this);
 le_index_entry_number_ = new QLineEdit(this);
 le_index_entry_number_->setPlaceholderText("(code)");
 le_index_entry_number_->setMaximumWidth(50);

 index_entry_group_box_layout_->addWidget(lbl_index_entry_term_, 1, 0);
 index_entry_group_box_layout_->addWidget(le_index_entry_term_, 1, 1);
 index_entry_group_box_layout_->addWidget(lbl_index_entry_number_, 1, 2);
 index_entry_group_box_layout_->addWidget(le_index_entry_number_, 1, 3);

 index_entry_group_box_layout_->setColumnStretch(1, 1);


 lbl_parent_entry_term_ = new QLabel("Parent", this);
 le_parent_entry_term_ = new QLineEdit(this);
 le_parent_entry_term_->setPlaceholderText("(heading)");
 lbl_parent_entry_number_ = new QLabel("#", this);
 le_parent_entry_number_ = new QLineEdit(this);
 le_parent_entry_number_->setPlaceholderText("(code)");
 le_parent_entry_number_->setMaximumWidth(50);

 index_entry_group_box_layout_->addWidget(lbl_parent_entry_term_, 2, 0);
 index_entry_group_box_layout_->addWidget(le_parent_entry_term_, 2, 1);
 index_entry_group_box_layout_->addWidget(lbl_parent_entry_number_, 2, 2);
 index_entry_group_box_layout_->addWidget(le_parent_entry_number_, 2, 3);

 entry_layout_->addWidget(index_entry_group_box_);



// index_entry_group_box_layout_ = new QVBoxLayout(index_entry_group_box_);
// index_entry_group_box_layout_top_ = new QFormLayout; //(index_entry_group_box_)

// cb_number_of_index_entry_ = new QComboBox(this);
// cb_number_of_index_entry_->addItems({QString::number(1),
//   QString::number(2), QString::number(3), QString::number(4),
//   QString::number(5), QString::number(6), QString::number(7),
//   QString::number(8) });

// index_entry_group_box_layout_top_->addRow("Number of Children: ",  cb_number_of_index_entry_);

// index_entry_group_box_layout_->addLayout(index_entry_group_box_layout_top_);

// index_entry_grid_layout_ = new QGridLayout;

// index_entry_grid_layout_->addWidget(new QLabel("Child's Name:", this), 0, 0);
// index_entry_grid_layout_->addWidget(new QLabel("Birth Year:", this), 0, 1);
// index_entry_group_box_layout_->addLayout(index_entry_grid_layout_);

// entry_layout_->addWidget(index_entry_group_box_);

 main_layout_->addLayout(entry_layout_);

// button_do_map_ = new QPushButton("Map", this);


 bottom_layout_ = new QHBoxLayout;

// bottom_layout_->addWidget(button_do_map_);


 QPushButton* minimize_button = new QPushButton(QChar(0x2735), this);
 QLabel* minimize_label = new QLabel(this);
 minimize_label->setText("Minimize");
 style_minimize_button(minimize_button);

 bottom_layout_->addWidget(minimize_button);
 bottom_layout_->addWidget(minimize_label);

 bottom_layout_->addStretch();
 bottom_layout_->addWidget(button_box_);

 main_layout_->addLayout(bottom_layout_);

 button_cancel_->setStyleSheet(colorful_toggle_button_mixed_style_sheet_());


 setLayout(main_layout_);

 setWindowTitle("Index/Meta-Index Search");


//stop:1 rgba(55, 14, 110, 85)


 setStyleSheet(R"_(

               QCheckBox::indicator {
                   width: 12px;
                   height: 12;
                   background-color: rgb(244, 250, 255);
                   border-radius: 2px;
                   border-style: solid;
                   border-width: 1px;
                   border-color: white white black black;
               }

               QCheckBox:hover {
                   width: 12px;
                   height: 12;
                   background-color: rgb(244, 25, 255);
                   border-radius: 2px;
                   border-style: solid;
                   border-width: 1px;
                   border-color: white white black black;
               }

               QCheckBox::indicator:hover {
                   width: 12px;
                   height: 12;
                   background-color: rgb(244, 125, 125);
                   border-radius: 2px;
                   border-style: solid;
                   border-width: 1px;
                   border-color: white white black black;
               }

               QCheckBox::indicator:checked {
                   background-color: qradialgradient(spread:pad,
                                           cx:0.5,
                                           cy:0.5,
                                           radius:0.3,
                                           fx:0.5,
                                           fy:0.5,
                                           stop:0 rgba(0, 0, 255, 255),
                                           stop:1 rgba(255, 214, 110, 255)
               );
               }
               QCheckBox:checked, QCheckBox::indicator:checked {
                   border-color: black black white white;
               }
               QCheckBox:checked {
                   background-color: qradialgradient(spread:pad,
                                           cx:0.739,
                                           cy:0.278364,
                                           radius:0.378,
                                           fx:0.997289,
                                           fy:0.00289117,
                                           stop:0 rgba(255, 255, 255, 255),
                                           stop:1 rgba(220, 220, 160, 255));
               }

               )_");

}


void PDF_Enhanced_Search_Dialog::add_index_entry_line()
{
// u1 rc = index_entry_grid_layout_->rowCount();

// QLineEdit* cn = new QLineEdit(this);
// QComboBox* cy = new QComboBox(this);

// for(u2 y = 2010; y <= 2023; ++y)
// {
//  cy->addItem(QString::number(y));
// }

// index_entry_grid_layout_->addWidget(cn, rc, 0);
// index_entry_grid_layout_->addWidget(cy, rc, 1);

}




//QHBoxLayout* pics = new QHBoxLayout;
//pics->addWidget(new QLabel("2"));

//QPushButton* pics_btn = new QPushButton("show");
//pics_btn->setMaximumWidth(37);

//pics_btn->setMaximumHeight(20);
//pics->addWidget(pics_btn);

//QPushButton* add_btn = new QPushButton("add");
//add_btn->setMaximumWidth(37);
//add_btn->setMaximumHeight(20);
//pics->addWidget(add_btn);

//pics->addStretch();

//QPushButton* folder_btn = new QPushButton("folder:");
//folder_btn->setMaximumWidth(47);
//folder_btn->setMaximumHeight(20);

//QLabel* folder_label = new QLabel("/home/demo");

//pics->addWidget(folder_btn);
//pics->addWidget(folder_label);
//pics->addStretch();



//top_buttons_layout_ = new QHBoxLayout;

//take_screenshot_button_ = new QPushButton("Screenshot", this);

//activate_tcp_button_ = new QPushButton("Activate TCP", this);

//take_screenshot_button_->setStyleSheet(colorful_button_style_sheet_());
//activate_tcp_button_->setStyleSheet(colorful_button_style_sheet_());

//connect(take_screenshot_button_, SIGNAL(clicked()),
//  this, SLOT(handle_take_screenshot_requested()));

//connect(activate_tcp_button_, SIGNAL(clicked()),
//  this, SLOT(activate_tcp_requested()));

//top_buttons_layout_->addStretch();

//top_buttons_layout_->addWidget(activate_tcp_button_);

//top_buttons_layout_->addWidget(take_screenshot_button_);


PDF_Enhanced_Search_Dialog::~PDF_Enhanced_Search_Dialog()
{

}

void PDF_Enhanced_Search_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void PDF_Enhanced_Search_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
