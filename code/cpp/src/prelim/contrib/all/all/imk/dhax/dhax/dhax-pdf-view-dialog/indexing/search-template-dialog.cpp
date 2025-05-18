
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "search-template-dialog.h"

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

Search_Template_Dialog::Search_Template_Dialog(QWidget* parent)
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

 info_group_box_ = new QGroupBox("Read", this);
 sources_group_box_ = new QGroupBox("Write", this);
 forward_index_group_box_ = new QGroupBox("Forward Index", this);

 info_group_box_layout_ = new QGridLayout(info_group_box_);

 sources_group_box_layout_ = new QGridLayout;


 lbl_base_query_write_ = new QLabel("Base Query:", this);
 le_base_query_write_ = new QLineEdit(this);
// le_local_file_->setPlaceholderText("(local file path)");

 sources_group_box_layout_->addWidget(lbl_base_query_write_, 0, 0);
 sources_group_box_layout_->addWidget(le_base_query_write_, 0, 1, 1, 4);


 lbl_stemming_protocol_ = new QLabel("Stemming Protocol:", this);
 cbb_stemming_protocol_ = new QComboBox(this);
 cbb_stemming_protocol_->addItem("None");

 le_stemming_protocol_file_ = new QLineEdit(this);
 le_stemming_protocol_file_->setPlaceholderText("(script file path)");

// le_local_file_->setPlaceholderText("(local file path)");

 sources_group_box_layout_->addWidget(lbl_stemming_protocol_, 1, 0);
 sources_group_box_layout_->addWidget(cbb_stemming_protocol_, 1, 1);
 sources_group_box_layout_->addWidget(le_stemming_protocol_file_, 1, 2, 1, 3);



 lbl_record_boundary_ = new QLabel("Record Boundary:");
 rb_record_boundary_sentence_ = new QRadioButton("Sentence");
 rb_record_boundary_text_line_ = new QRadioButton("Text Line");
 rb_record_boundary_markup_tags_ = new QRadioButton("Markup Tags");
 rb_record_boundary_intersectional_ = new QRadioButton("Intersectional");

 rb_record_boundary_contextual_ = new QRadioButton("Contextual");

 sources_group_box_layout_->addWidget(lbl_record_boundary_, 2, 0);
 sources_group_box_layout_->addWidget(rb_record_boundary_sentence_, 2, 1);
 sources_group_box_layout_->addWidget(rb_record_boundary_text_line_, 2, 2);
 sources_group_box_layout_->addWidget(rb_record_boundary_markup_tags_, 2, 3);
 sources_group_box_layout_->addWidget(rb_record_boundary_intersectional_, 2, 4);

 QHBoxLayout* hbl = new QHBoxLayout;
 hbl->addSpacing(14);


 hbl->addWidget(rb_record_boundary_contextual_);

 le_word_vector_protocol_ = new QLineEdit(this);
 le_word_vector_protocol_->setPlaceholderText("(word vector protocol file)");
 hbl->addWidget(le_word_vector_protocol_);
 btn_word_vector_protocol_file_browse_ = new QPushButton("View", this);
 hbl->addWidget(btn_word_vector_protocol_file_browse_);
 btn_word_vector_protocol_file_browse_->setStyleSheet(colorful_toggle_button_style_sheet_());


 sources_group_box_layout_->addLayout(hbl, 3, 0, 1, 5, Qt::AlignRight);


 QFrame* line = new QFrame();
 line->setMinimumHeight(3);
 line->setMinimumWidth(133);
// line->setFrameShape(QFrame::Box); // Replace by VLine for vertical line
// line->setFrameShadow(QFrame::Sunken);
 line->setFrameStyle(QFrame::Box | QFrame::Sunken);

 sources_group_box_layout_->addWidget(line, 4, 0, 1, 5, Qt::AlignHCenter | Qt::AlignBottom);

// QPushButton* b = new QPushButton("ted");
// sources_group_box_layout_->addWidget(b, 4, 0);




 lbl_column_data_ = new QLabel("Column Data", this);
 lw_column_names_ = new QListWidget;
 lw_column_types_ = new QListWidget;

 QHBoxLayout* hbl_column_data_ = new QHBoxLayout;

 spl_column_data_ = new QSplitter(this);
 spl_column_data_->addWidget(lw_column_names_);
 spl_column_data_->addWidget(lw_column_types_);

 lw_column_names_->addItem("(name 1)");
 lw_column_names_->addItem("(name 2)");
 lw_column_names_->addItem(" ... ");

 lw_column_types_->addItem("(type 1)");
 lw_column_types_->addItem("(type 2)");
 lw_column_types_->addItem(" ... ");

 for(u1 r = 0; r < 3; ++r)
 {
  lw_column_names_->item(r)->setForeground(Qt::gray);
  lw_column_types_->item(r)->setForeground(Qt::gray);
 }


// QListWidgetItem* l3 = new QListWidgetItem;

 //lw_column_types_->setMaximumWidth(55);

 sources_group_box_layout_->addWidget(lbl_column_data_, 5, 0);

 hbl_column_data_->addSpacing(15);
 hbl_column_data_->addWidget(spl_column_data_);

 sources_group_box_layout_->addLayout(hbl_column_data_, 6, 0, 1, 5);




 sources_group_box_->setLayout(sources_group_box_layout_);

 entry_layout_->addWidget(info_group_box_);

 le_search_term_ = new QLineEdit(this);

 lbl_search_term_ = new QLabel("Base Query:", this);


 info_group_box_layout_->addWidget(lbl_search_term_, 0, 0);
 info_group_box_layout_->addWidget(le_search_term_, 0, 1, 1, 11);

 lbl_back_end_ = new QLabel("Back End:", this);
 info_group_box_layout_->addWidget(lbl_back_end_, 1, 0);

 rb_manticore_ = new QRadioButton("Manticore", this);
 info_group_box_layout_->addWidget(rb_manticore_, 1, 1, 1, 2);

 rb_pisa_ = new QRadioButton("Pisa", this);
 info_group_box_layout_->addWidget(rb_pisa_, 1, 3, 1, 2);

 rb_htxn_ = new QRadioButton("HTXN", this);
 info_group_box_layout_->addWidget(rb_htxn_, 1, 5, 1, 2, Qt::AlignHCenter);

 rb_tkrzw_ = new QRadioButton("Tkrzw", this);
 info_group_box_layout_->addWidget(rb_tkrzw_, 1, 7, 1, 2);

 rb_whitedb_ = new QRadioButton("WhiteDB", this);
 info_group_box_layout_->addWidget(rb_whitedb_, 1, 9, 1, 2);


 lbl_text_window_options_ = new QLabel("Text Window Options:", this);


 cb_proximity_distance_ = new QCheckBox("Proximity", this);
 cb_strict_order_ = new QCheckBox("Strict Order", this);
 cb_near_ = new QCheckBox("NEAR", this);

 info_group_box_layout_->addWidget(lbl_text_window_options_, 2, 0);
 info_group_box_layout_->addWidget(cb_strict_order_, 2, 1, 1, 3, Qt::AlignRight);


 info_group_box_layout_->addWidget(cb_near_, 2, 5, 1, 2, Qt::AlignRight);
 cbb_near_ = new QComboBox(this);

 cbb_near_->addItem("1");
 cbb_near_->addItem("2");
 info_group_box_layout_->addWidget(cbb_near_, 2, 7, 1, 2);


 info_group_box_layout_->addWidget(cb_proximity_distance_, 3, 0, 1, 2, Qt::AlignRight);
 cbb_proximity_distance_ = new QComboBox(this);

 cbb_proximity_distance_->addItem("1");
 cbb_proximity_distance_->addItem("2");

 info_group_box_layout_->addWidget(cbb_proximity_distance_, 3, 2, 1, 2);


 cb_quorum_ = new QCheckBox("Quorum", this);
 cbb_quorum_ = new QComboBox(this);

 cbb_quorum_->addItem("1");
 cbb_quorum_->addItem("2");

 info_group_box_layout_->addWidget(cb_quorum_, 3, 5, 1, 2, Qt::AlignRight);
 info_group_box_layout_->addWidget(cbb_quorum_, 3, 7, 1, 2);


 btn_preview_ = new QPushButton("Preview", this);
 info_group_box_layout_->addWidget(btn_preview_, 2, 10, 2, 1, Qt::AlignHCenter);
 btn_preview_->setMaximumHeight(26);
 btn_preview_->setMaximumWidth(70);
 btn_preview_->setStyleSheet(colorful_small_button_style_sheet_alt_());

// lbl_filter_ = new QLabel("Filters", this);
// info_group_box_layout_->addWidget(lbl_filter_, 2, 0);





 QFrame* scope_l = new QFrame(this);
 QHBoxLayout* scope_l_layout_ = new QHBoxLayout(scope_l);

 rb_sentence_ = new QRadioButton("Sentence", this);
 scope_l_layout_->addWidget(rb_sentence_);

 rb_paragraph_ = new QRadioButton("Paragraph", this);
 scope_l_layout_->addWidget(rb_paragraph_);


 QFrame* scope_r = new QFrame(this);
 QHBoxLayout* scope_r_layout_ = new QHBoxLayout(scope_r);

 rb_zone_ = new QRadioButton("Zone", this);
 scope_r_layout_->addWidget(rb_zone_);

 rb_zonespan_ = new QRadioButton("Zonespan", this);
 scope_r_layout_->addWidget(rb_zonespan_);

 scope_l->setFrameStyle(QFrame::Box | QFrame::Sunken);
 scope_r->setFrameStyle(QFrame::Box | QFrame::Sunken);

// QFormLayout* qfl = new QFormLayout;
// qfl->addRow("Scope:", options_f);

 lbl_scope_ = new QLabel("Scope:", this);
// info_group_box_layout_->addWidget(lbl_scope_, 4, 0);

 QHBoxLayout* scope_layout_ = new QHBoxLayout;
 scope_layout_->addWidget(lbl_scope_);

 rb_scope_all_ = new QCheckBox("All", this);

 scope_layout_->addStretch();
 scope_layout_->addWidget(rb_scope_all_);
 scope_layout_->addStretch();


 scope_layout_->addWidget(scope_l);
 scope_layout_->addStretch();

 scope_layout_->addWidget(scope_r);
 scope_layout_->addStretch();

 info_group_box_layout_->addLayout(scope_layout_, 5, 0, 1, 12);


// QFrame* options_f = new QFrame(this);
// options_f->setFrameStyle(QFrame::Box | QFrame::Sunken);

//  QGridLayout* fl = new QGridLayout;
//  fl->addWidget(new QLabel("xxx"), 0, 0);


// filters_f->setMaximumWidth(300);


// QGridLayout* fl = new QGridLayout(filters_f);
// fl->addWidget(new QLabel("xxx"), 0, 0);

 // // options_f->setLayout(filters_layout_);



//  info_group_box_layout_->addWidget(new QLabel("xxx"), 2, 1, 1, 8);


// info_group_box_layout_->addWidget(cb_main_text_, 2, 2, 1, 3);
// info_group_box_layout_->addWidget(cb_footnote_text_, 2, 5, 1, 3);
// info_group_box_layout_->addWidget(cb_sentences_with_footnote_, 2, 8, 1, 3);

// info_group_box_layout_->addWidget(cb_chapter_titles_, 3, 1, 1, 3);
// info_group_box_layout_->addWidget(cb_section_titles_, 3, 4, 1, 2);
// info_group_box_layout_->addWidget(cb_bibliography_, 3, 6, 1, 2);
// info_group_box_layout_->addWidget(cb_local_index_, 3, 8, 1, 2);






 entry_layout_->addWidget(sources_group_box_);


 forward_index_group_box_layout_ = new QGridLayout(forward_index_group_box_);

 lbl_forward_index_num_terms_ = new QLabel("Number of Terms:", this);
 le_forward_index_num_terms_ = new  QLineEdit(this);

 le_forward_index_num_terms_->setPlaceholderText("(number of search-index terms in current document)");

 forward_index_group_box_layout_->addWidget(lbl_forward_index_num_terms_, 0, 0);
 forward_index_group_box_layout_->addWidget(le_forward_index_num_terms_, 0, 1, 1, 4);



 lbl_meta_index_num_terms_ = new QLabel("Number of Meta-Index Terms:", this);
 le_meta_index_num_terms_ = new  QLineEdit(this);

 le_meta_index_num_terms_->setPlaceholderText("(number of meta-index terms in current document)");

 forward_index_group_box_layout_->addWidget(lbl_meta_index_num_terms_, 1, 0, 1, 2);
 forward_index_group_box_layout_->addWidget(le_meta_index_num_terms_, 1, 2, 1, 3);



 lbl_forward_index_num_records_ = new QLabel("Number of Records:", this);
 le_forward_index_num_records_ = new  QLineEdit(this);

 le_forward_index_num_records_->setPlaceholderText("(number of search-index records in current document)");

 forward_index_group_box_layout_->addWidget(lbl_forward_index_num_records_, 2, 0);
 forward_index_group_box_layout_->addWidget(le_forward_index_num_records_, 2, 1, 1, 4);


 lbl_measure_points_ = new QLabel("Frequency/Relevance Measure Points:");
 forward_index_group_box_layout_->addWidget(lbl_measure_points_, 3, 0, 1, 2);

 cb_measure_points_sentence_ = new QCheckBox("Sentence");
 cb_measure_points_paragraph_ = new QCheckBox("Paragraph");
 cb_measure_points_page_ = new QCheckBox("Page");
 cb_measure_points_section_ = new QCheckBox("Section");
 cb_measure_points_subsection_ = new QCheckBox("Subsection");
 cb_measure_points_chapter_ = new QCheckBox("Chapter");
 cb_measure_points_article_ = new QCheckBox("Article");
 cb_measure_points_other_ = new QCheckBox("Other");

 QHBoxLayout* forward_index_top_hbl = new QHBoxLayout;
 forward_index_top_hbl->addStretch();
 forward_index_top_hbl->addWidget(cb_measure_points_sentence_);
 forward_index_top_hbl->addStretch();
 forward_index_top_hbl->addWidget(cb_measure_points_paragraph_);

 forward_index_group_box_layout_->addLayout(forward_index_top_hbl, 3, 2, 1, 3, Qt::AlignRight);

 QHBoxLayout* forward_index_hbl = new QHBoxLayout;

 forward_index_hbl->addSpacing(16);
 forward_index_hbl->addWidget(cb_measure_points_page_);
 forward_index_hbl->addWidget(cb_measure_points_section_);
 forward_index_hbl->addWidget(cb_measure_points_subsection_);
 forward_index_hbl->addSpacing(16);
 forward_index_hbl->addWidget(cb_measure_points_chapter_);
 forward_index_hbl->addSpacing(9);
 forward_index_hbl->addWidget(cb_measure_points_article_);
 forward_index_hbl->addWidget(cb_measure_points_other_);

 forward_index_group_box_layout_->addLayout(forward_index_hbl, 4, 0, 1, 5);



 // forward_index_group_box_layout_->addWidget(btn_index_entry_data_, 0, 3);

// lbl_index_entry_term_ = new QLabel("Term", this);
// le_index_entry_term_ = new QLineEdit(this);
// le_index_entry_term_->setPlaceholderText("(heading)");
// lbl_index_entry_number_ = new QLabel("#", this);
// le_index_entry_number_ = new QLineEdit(this);
// le_index_entry_number_->setPlaceholderText("(code)");
// le_index_entry_number_->setMaximumWidth(50);

// forward_index_group_box_layout_->addWidget(lbl_index_entry_term_, 1, 0);
// forward_index_group_box_layout_->addWidget(le_index_entry_term_, 1, 1);
// forward_index_group_box_layout_->addWidget(lbl_index_entry_number_, 1, 2);
// forward_index_group_box_layout_->addWidget(le_index_entry_number_, 1, 3);

 forward_index_group_box_layout_->setColumnStretch(2, 1);



 entry_layout_->addWidget(forward_index_group_box_);



// forward_index_group_box_layout_ = new QVBoxLayout(index_entry_group_box_);
// forward_index_group_box_layout_top_ = new QFormLayout; //(index_entry_group_box_)

// cb_number_of_index_entry_ = new QComboBox(this);
// cb_number_of_index_entry_->addItems({QString::number(1),
//   QString::number(2), QString::number(3), QString::number(4),
//   QString::number(5), QString::number(6), QString::number(7),
//   QString::number(8) });

// forward_index_group_box_layout_top_->addRow("Number of Children: ",  cb_number_of_index_entry_);

// forward_index_group_box_layout_->addLayout(forward_index_group_box_layout_top_);

// index_entry_grid_layout_ = new QGridLayout;

// index_entry_grid_layout_->addWidget(new QLabel("Child's Name:", this), 0, 0);
// index_entry_grid_layout_->addWidget(new QLabel("Birth Year:", this), 0, 1);
// forward_index_group_box_layout_->addLayout(index_entry_grid_layout_);

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

 setWindowTitle("Database Query Template");


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


void Search_Template_Dialog::add_index_entry_line()
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


Search_Template_Dialog::~Search_Template_Dialog()
{

}

void Search_Template_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Search_Template_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
