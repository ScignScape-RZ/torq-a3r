
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "pdf-enhanced-search-dialog.h"

//?#include "styles.h"




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

 button_ok_ = new QPushButton("OK");
 button_proceed_ = new QPushButton("Edit");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setEnabled(false);

 // // unless this is being embedded ...
 button_proceed_->setEnabled(false);
 button_cancel_->setText("Close");

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

 connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;
 entry_layout_ = new QVBoxLayout;

 info_group_box_ = new QGroupBox("Search", this);
 sources_group_box_ = new QGroupBox("Sources", this);
 children_group_box_ = new QGroupBox("About your Children", this);

 info_group_box_layout_ = new QGridLayout(info_group_box_);

 sources_group_box_layout_ = new QVBoxLayout;

 sources_group_box_top_layout_ = new QHBoxLayout;
 sources_group_box_bottom_layout_ = new QHBoxLayout;


 sources_group_box_left_layout_ = new QFormLayout;
 sources_group_box_right_layout_ = new QVBoxLayout;


 lbl_local_file_ = new QLabel("Local File", this);
 le_local_file_ = new QLineEdit(this);
 le_local_file_->setPlaceholderText("(local file path)");

 sources_group_box_top_layout_->addWidget(lbl_local_file_);
 sources_group_box_top_layout_->addWidget(le_local_file_);

 btn_local_file_browse_ = new QPushButton("Browse", this);
 sources_group_box_top_layout_->addWidget(btn_local_file_browse_);


 le_meta_index_ = new QLineEdit(this);
 le_meta_index_->setPlaceholderText("(URL)");
 sources_group_box_left_layout_->addRow("Meta-Index", le_meta_index_);

 cbb_access_type_ = new QComboBox(this);
 cbb_access_type_->addItem("Public");
 cbb_access_type_->addItem("Login");
 cbb_access_type_->addItem("Keyring");
 sources_group_box_left_layout_->addRow("Access Type", cbb_access_type_);


 credentials_file_layout_ = new QHBoxLayout;
 btn_load_credentials_ = new QPushButton("load", this);
 btn_set_credentials_file_ = new QPushButton("set file", this);
 credentials_file_layout_->addWidget(btn_load_credentials_);
 credentials_file_layout_->addWidget(btn_set_credentials_file_);

 sources_group_box_left_layout_->addRow("Credentials File", credentials_file_layout_);

  QTextEdit* address_text_edit = new QTextEdit(this);
  address_text_edit->setPlaceholderText("Enter username then password, or enter security code");
  sources_group_box_right_layout_->addWidget(address_text_edit);
  address_text_edit->setMaximumHeight(65);
  sources_group_box_right_layout_->addWidget(new QLabel("Credentials (if needed)", this));

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


 sources_group_box_layout_->addLayout(sources_group_box_top_layout_);
 sources_group_box_layout_->addLayout(sources_group_box_bottom_layout_);

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



 entry_layout_->addWidget(sources_group_box_);


// children_group_box_layout_ = new QVBoxLayout(children_group_box_);
// children_group_box_layout_top_ = new QFormLayout; //(children_group_box_)

// cb_number_of_children_ = new QComboBox(this);
// cb_number_of_children_->addItems({QString::number(1),
//   QString::number(2), QString::number(3), QString::number(4),
//   QString::number(5), QString::number(6), QString::number(7),
//   QString::number(8) });

// children_group_box_layout_top_->addRow("Number of Children: ",  cb_number_of_children_);

// children_group_box_layout_->addLayout(children_group_box_layout_top_);

// children_grid_layout_ = new QGridLayout;

// children_grid_layout_->addWidget(new QLabel("Child's Name:", this), 0, 0);
// children_grid_layout_->addWidget(new QLabel("Birth Year:", this), 0, 1);
// children_group_box_layout_->addLayout(children_grid_layout_);

// entry_layout_->addWidget(children_group_box_);

 main_layout_->addLayout(entry_layout_);

 button_do_map_ = new QPushButton("Map", this);


 bottom_layout_ = new QHBoxLayout;

 bottom_layout_->addWidget(button_do_map_);
 bottom_layout_->addStretch();
 bottom_layout_->addWidget(button_box_);

 main_layout_->addLayout(bottom_layout_);


 setLayout(main_layout_);

 setWindowTitle("Entry Dialog");

}


void PDF_Enhanced_Search_Dialog::add_children_line()
{
// u1 rc = children_grid_layout_->rowCount();

// QLineEdit* cn = new QLineEdit(this);
// QComboBox* cy = new QComboBox(this);

// for(u2 y = 2010; y <= 2023; ++y)
// {
//  cy->addItem(QString::number(y));
// }

// children_grid_layout_->addWidget(cn, rc, 0);
// children_grid_layout_->addWidget(cy, rc, 1);

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
