
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "index-entry-review-dialog.h"

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
#include <QListWidget>

#include <QDesktopWidget>
#include <QLabel>

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

#include <QDockWidget>

#include <QComboBox>

#include <QGeoCoordinate>

#include "global-types.h"

#include "dhax-pdf-view-dialog/paraviews/dhax-pdf-view-dialog.h"

#include "styles-alt.h"

#include <QInputDialog>


//?#include "case-map-gis-service.h"

Index_Entry_Review_Dialog::Index_Entry_Review_Dialog(QString earlier_match_file,
    QString bookmarks_file, QString ftp_folder)
  : current_entry_id_(0), max_entry_id_(0), current_index_entry_(nullptr),
    review_vector_(nullptr),
    active_earlier_match_code_index_(0), max_earlier_match_code_index_(0),
    earlier_match_file_(earlier_match_file), bookmarks_file_(bookmarks_file),
    ftp_folder_(ftp_folder), ref_groups_(nullptr), current_nav_filter_(Nav_Filters::None),
    current_search_word_list_low_(0), available_search_word_list_count_(0),
    current_search_word_list_high_(0), flip_count_(0), slurp_count_(0),
    current_page_ref_pair_(Page_Ref_Pair::default_values()),
    entry_index_range_({0, 0}), current_entry_key_({0, 0})
{
 main_frame_ = new QFrame(this);


 setup_comparison_window();

 button_box_ = new QDialogButtonBox(this);

 button_close_ = new QPushButton("Close");
 button_close_all_ = new QPushButton("Close All");

 button_close_->setDefault(false);
 button_close_->setAutoDefault(false);
 button_close_->setStyleSheet(basic_button_style_sheet_());

 button_close_all_->setDefault(false);
 button_close_all_->setAutoDefault(false);
 button_close_all_->setStyleSheet(colorful_button_style_sheet_());

 button_box_->addButton(button_close_all_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_close_, QDialogButtonBox::RejectRole);

// button_ok_->setStyleSheet(basic_button_style_sheet_());
// button_proceed_->setStyleSheet(basic_button_style_sheet_());
// button_cancel_->setStyleSheet(basic_button_style_sheet_());

 connect(button_box_, SIGNAL(accepted()), this, SLOT(close()));

 connect(button_box_, &QDialogButtonBox::accepted,
  [this]()
  {
   earlier_pdf_dialog_->close();
   later_pdf_dialog_->close();
   close();
  });


// connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;
 entry_layout_ = new QVBoxLayout;

 info_group_box_ = new QGroupBox("Entry Info", this);
 earlier_match_group_box_ = new QGroupBox("Earlier Match", this);
 search_text_line_edit_ = new QLineEdit(this);
 search_text_line_edit_->setPlaceholderText("(derived by default from each earlier entry)");
 search_text_line_edit_->setEnabled(false);


 connect(search_text_line_edit_, &QLineEdit::textChanged, [this](QString text)
 {
  static constexpr u2 max = 50;
  text = text.simplified().replace(" ", "-");
  if(text.size() > max)
    text = text.mid(0, max);

  text += "._%1.htm"_qt.arg(current_entry_id_);

  html_file_name_line_edit_->setText(text);
 });


 info_group_box_layout_ = new QVBoxLayout;



 earlier_match_group_box_layout_ = new QVBoxLayout;
 earlier_match_group_box_top_layout_ = new QFormLayout;
 earlier_match_group_box_left_layout_ = new QFormLayout;
 earlier_match_group_box_bottom_layout_ = new QHBoxLayout;
 earlier_match_group_box_right_layout_ = new QVBoxLayout;


 earlier_match_code_update_line_edit_ = new QLineEdit(this);

 earlier_match_code_update_line_edit_->setReadOnly(true);

 active_earlier_match_code_line_edit_ = new QLineEdit(this);


 match_codes_text_edit_ = new QTextEdit(this);
 match_codes_text_edit_->setPlaceholderText("N/A");
 match_codes_text_edit_->setEnabled(false);

 match_codes_text_edit_->setReadOnly(true);
 match_codes_text_edit_->setMaximumHeight(60);

 earlier_match_group_box_top_layout_->addRow("Match Codes", match_codes_text_edit_);

 earlier_match_group_box_layout_->addLayout(earlier_match_group_box_top_layout_);

 earlier_match_group_box_bottom_left_layout_ = new QHBoxLayout;

 earlier_match_group_box_left_layout_->addRow("Active", active_earlier_match_code_line_edit_);
//? earlier_match_group_box_left_layout_->addRow("Update", earlier_match_code_update_line_edit_);

 earlier_match_group_box_bottom_left_layout_->addWidget(new QLabel("Update", this));
 earlier_match_group_box_bottom_left_layout_->addWidget(earlier_match_code_update_line_edit_);

 earlier_match_code_update_line_edit_->setMaximumWidth(60);

 earlier_match_code_edit_line_edit_ = new QLineEdit(this);

 earlier_match_code_edit_line_edit_->setMaximumWidth(60);

 earlier_match_group_box_bottom_left_layout_->addWidget(new QLabel("Edit", this));
 earlier_match_group_box_bottom_left_layout_->addWidget(earlier_match_code_edit_line_edit_);

 earlier_match_group_box_left_layout_->addRow(earlier_match_group_box_bottom_left_layout_);


 earlier_match_group_box_middle_layout_ = new QGridLayout;

 active_earlier_match_code_exclude_check_box_ = new QCheckBox("Excluded", this);
 active_earlier_match_code_confirmed_check_box_ = new QCheckBox("Confirmed", this);
 detach_page_number_check_box_ = new QCheckBox("Detach Page Number", this);
 active_earlier_match_manual_update_check_box_ = new QCheckBox("Manual Edit", this);
 earlier_match_bookmarked_check_box_ = new QCheckBox("Bookmarked", this);

 auto uncheck_active_earlier_match_code_exclude_check_box = [this]()
 {
  active_earlier_match_code_exclude_check_box_->blockSignals(true);
  entry_update_clear_Excluded();
  active_earlier_match_code_exclude_check_box_->setChecked(false);
  active_earlier_match_code_exclude_check_box_->blockSignals(false);
 };

 connect(active_earlier_match_code_exclude_check_box_, &QCheckBox::toggled,
   [this](bool b)
 {
  entry_update_reset_Excluded(b);
  QVector<QCheckBox*> all = {active_earlier_match_code_confirmed_check_box_,
    detach_page_number_check_box_, active_earlier_match_manual_update_check_box_};
  if(b)
  {
   for(QCheckBox* qcb : all)
   {
    qcb->blockSignals(true);
    qcb->setEnabled(false);
    qcb->setChecked(false);
    entry_update_clear_Confirmed();
    entry_update_clear_Detach_Page_Number();
    entry_update_clear_Manually_Edited();
    qcb->blockSignals(false);
   }
  }
  else
  {
   for(QCheckBox* qcb : all)
   {
    qcb->blockSignals(true);
    qcb->setEnabled(true);
    qcb->blockSignals(false);
   }
  }
 });

 connect(active_earlier_match_code_confirmed_check_box_, &QCheckBox::toggled,
   [this, uncheck_active_earlier_match_code_exclude_check_box](bool b)
 {
  entry_update_reset_Confirmed(b);
  if(b)
    uncheck_active_earlier_match_code_exclude_check_box();

 });
 connect(detach_page_number_check_box_, &QCheckBox::toggled,
   [this, uncheck_active_earlier_match_code_exclude_check_box](bool b)
 {
  entry_update_reset_Detach_Page_Number(b);
  if(b)
    uncheck_active_earlier_match_code_exclude_check_box();

 });
 connect(active_earlier_match_manual_update_check_box_, &QCheckBox::toggled,
   [this, uncheck_active_earlier_match_code_exclude_check_box](bool b)
 {
  entry_update_reset_Manually_Edited(b);
  if(b)
    uncheck_active_earlier_match_code_exclude_check_box();
 });

 connect(earlier_match_bookmarked_check_box_, &QCheckBox::toggled,
   [this](bool b)
 {
  if(b)
    check_bookmark();
  else
    remove_bookmark();
  entry_update_reset_Bookmarked(b);
 });

 connect(earlier_match_code_edit_line_edit_, &QLineEdit::textEdited,
   [this](const QString&)
 {
  entry_update_note_Manually_Edited();
  active_earlier_match_manual_update_check_box_->blockSignals(true);
  active_earlier_match_manual_update_check_box_->setChecked(true);
  active_earlier_match_manual_update_check_box_->blockSignals(false);
 });


 earlier_match_group_box_middle_layout_->setRowStretch(0, 1);
 earlier_match_group_box_middle_layout_->setRowStretch(3, 1);

 earlier_match_group_box_middle_layout_->
   addWidget(detach_page_number_check_box_, 1, 3, 1, 3);
 earlier_match_group_box_middle_layout_->
   addWidget(earlier_match_bookmarked_check_box_, 1, 0, 1, 3);

 earlier_match_group_box_middle_layout_->
   addWidget(active_earlier_match_code_confirmed_check_box_, 2, 0, 1, 2);
 earlier_match_group_box_middle_layout_->
   addWidget(active_earlier_match_code_exclude_check_box_, 2, 2, 1, 2);
 earlier_match_group_box_middle_layout_->
   addWidget(active_earlier_match_manual_update_check_box_, 2, 4, 1, 2);

 earlier_match_group_box_middle_layout_->setVerticalSpacing(0);
 earlier_match_group_box_middle_layout_->setContentsMargins(0, 0, 0, 0); //layout->setSpacing(0);

// earlier_match_group_box_left_layout_->addRow(earlier_match_group_box_middle_layout_);

// earlier_match_code_update_line_edit_->hide();
// active_earlier_match_code_line_edit_->hide();
// active_earlier_match_code_updated_check_box_->hide();

 earlier_match_group_box_bottom_layout_->addLayout(earlier_match_group_box_left_layout_);

 earlier_match_group_box_bottom_layout_->addSpacing(7);
 earlier_match_group_box_bottom_layout_->addLayout(earlier_match_group_box_middle_layout_);
 earlier_match_group_box_bottom_layout_->addSpacing(9);


 active_earlier_match_code_nav_layout_ = new QHBoxLayout;
 active_earlier_match_code_highlight_layout_ = new QHBoxLayout;

 active_earlier_match_code_forward_button_ = new QPushButton("=>");
 make_index_entry_ref_forward_button(active_earlier_match_code_forward_button_);

 active_earlier_match_code_backward_button_ = new QPushButton("<=");
 make_index_entry_ref_backward_button(active_earlier_match_code_backward_button_);


 active_earlier_match_code_back_to_start_button_ = new QPushButton("<<=");
 make_index_entry_ref_double_backward_button(active_earlier_match_code_back_to_start_button_);

 //make_back_button(active_earlier_match_code_back_to_start_button_);


 active_earlier_match_code_forward_button_->setMaximumWidth(37);
 active_earlier_match_code_backward_button_->setMaximumWidth(37);
 active_earlier_match_code_back_to_start_button_->setMaximumWidth(42);



 earlier_track_highlight_button_ = new QPushButton("track");
 earlier_track_highlight_button_->setCheckable(true);
 clear_earlier_highlights_button_ = new QPushButton("clean");
 search_update_button_ = new QPushButton("update");
 search_update_button_->setCheckable(true);

 earlier_track_highlight_button_->setMaximumWidth(45);
 clear_earlier_highlights_button_->setMaximumWidth(45);
 search_update_button_->setMaximumWidth(45);

 active_earlier_match_code_nav_layout_->addStretch();
 active_earlier_match_code_nav_layout_->addWidget(active_earlier_match_code_backward_button_);
 active_earlier_match_code_nav_layout_->addWidget(active_earlier_match_code_forward_button_);
 active_earlier_match_code_nav_layout_->addStretch();
 active_earlier_match_code_nav_layout_->addWidget(active_earlier_match_code_back_to_start_button_);
 active_earlier_match_code_nav_layout_->addStretch();
 earlier_match_group_box_right_layout_->addLayout(active_earlier_match_code_nav_layout_);

 active_earlier_match_code_highlight_layout_->addStretch();
 active_earlier_match_code_highlight_layout_->addWidget(earlier_track_highlight_button_);
 active_earlier_match_code_highlight_layout_->addWidget(search_update_button_);
 active_earlier_match_code_highlight_layout_->addStretch();
 active_earlier_match_code_highlight_layout_->addWidget(clear_earlier_highlights_button_);
 active_earlier_match_code_highlight_layout_->addStretch();

 earlier_match_group_box_right_layout_->addLayout(active_earlier_match_code_highlight_layout_);

 connect(search_update_button_, &QPushButton::toggled, [this](bool)
 {
  check_search_update();
 });

 connect(clear_earlier_highlights_button_, &QPushButton::clicked, [this]()
 {
  clear_earlier_highlights();
 });

 connect(earlier_track_highlight_button_, &QPushButton::toggled, [this](bool)
 {
  check_earlier_highlight();
 });

 connect(active_earlier_match_code_forward_button_, &QPushButton::clicked, [this]()
 {
  earlier_match_forward();
 });

 connect(active_earlier_match_code_backward_button_, &QPushButton::clicked, [this]()
 {
  earlier_match_backward();
 });

 connect(active_earlier_match_code_back_to_start_button_, &QPushButton::clicked, [this]()
 {
  earlier_match_back_to_start();
 });


// QTextEdit* address_text_edit = new QTextEdit(this);
// address_text_edit->setPlaceholderText("Enter address here, or leave empty");
// earlier_match_group_box_right_layout_->addWidget(address_text_edit);
// address_text_edit->setMaximumHeight(65);

 earlier_match_group_box_bottom_layout_->addLayout(earlier_match_group_box_right_layout_);

 earlier_match_group_box_layout_->addLayout(earlier_match_group_box_bottom_layout_);

 earlier_match_group_box_->setLayout(earlier_match_group_box_layout_);


 entry_layout_->addWidget(info_group_box_);

 heading_line_edit_ = new QLineEdit(this);
 parent_heading_line_edit_ = new QLineEdit(this);

 entry_id_line_edit_ = new QLineEdit(this);
 number_of_match_components_line_edit_ = new QLineEdit(this);

 count_in_parent_line_edit_ = new QLineEdit(this);
 subheading_count_line_edit_ = new QLineEdit(this);




 info_group_box_left_layout_ = new QFormLayout;
 info_group_box_right_layout_ = new QFormLayout;
 info_group_box_top_layout_ = new QFormLayout;
 info_group_box_bottom_layout_ = new QHBoxLayout;
 info_group_box_layout_ = new QVBoxLayout;

 info_group_box_top_layout_->addRow("Heading", heading_line_edit_);
 info_group_box_top_layout_->addRow("Parent Heading", parent_heading_line_edit_);


 info_group_box_right_layout_->addRow("Entry Id", entry_id_line_edit_);
 info_group_box_right_layout_->addRow("Number of Match Components", number_of_match_components_line_edit_);

 info_group_box_left_layout_->addRow("Count in Parent", count_in_parent_line_edit_);
 info_group_box_left_layout_->addRow("Subheading Count", subheading_count_line_edit_);


 info_group_box_bottom_layout_->addLayout(info_group_box_left_layout_);
 info_group_box_bottom_layout_->addLayout(info_group_box_right_layout_);

 info_group_box_layout_->addLayout(info_group_box_top_layout_);
 info_group_box_layout_->addLayout(info_group_box_bottom_layout_);

 info_group_box_->setLayout(info_group_box_layout_);

 entry_layout_->addWidget(earlier_match_group_box_);


 current_search_group_box_ = new QGroupBox;

 current_search_group_box_layout_ = new QVBoxLayout; //(current_search_group_box_);


 current_search_group_box_layout_top_ = new QFormLayout; //(current_search_group_box_);

// cb_number_of_children_ = new QComboBox(this);
// cb_number_of_children_->addItems({QString::number(1),
//   QString::number(2), QString::number(3), QString::number(4),
//   QString::number(5), QString::number(6), QString::number(7),
//   QString::number(8) });

 current_search_group_box_layout_top_->addRow("Search Text: ",  search_text_line_edit_);

 current_search_group_box_layout_->addLayout(current_search_group_box_layout_top_);

 current_matches_grid_layout_ = new QGridLayout;

 search_words_inc_high_button_ = new QPushButton("+");
 make_nav_button(search_words_inc_high_button_, 0x2942, 14);
 search_words_inc_high_button_->setToolTip("Add entry word to search");


 search_words_dec_high_button_ = new QPushButton("-");
 make_nav_button(search_words_dec_high_button_, 0x2943, 14);
 search_words_dec_high_button_->setToolTip("Remove last word");

 redo_both_matches_button_ = new QPushButton("<~>");
 make_nav_button(redo_both_matches_button_, 0x2B80, 15);  //21DB
 redo_both_matches_button_->setToolTip("Search in both documents");


 redo_earlier_match_button_ = new QPushButton("~>");
 make_nav_button(redo_earlier_match_button_, 0x2AF8, 14);  //21DB
 redo_earlier_match_button_->setToolTip("Search in earlier document");
//? redo_earlier_match_button_->setMaximumWidth(20);

 redo_later_match_button_ = new QPushButton("<~");
 make_nav_button(redo_later_match_button_, 0x2AF7, 14);
 redo_later_match_button_->setToolTip("Search in later document");
// redo_later_match_button_->setMaximumWidth(20);

 clean_later_match_button_ = new QPushButton("clean");


 search_words_inc_low_button_ = new QPushButton(".+");
 make_nav_button(search_words_inc_low_button_, 0x2945, 14); // 2945
 search_words_inc_low_button_->setToolTip("Skip first (unflipped) word");

 search_words_dec_low_button_ = new QPushButton(".-");
 make_nav_button(search_words_dec_low_button_, 0x2946, 14);
 search_words_dec_low_button_->setToolTip("Unskip first (unflipped) word");


 search_words_flip_button_ = new QPushButton("<->");
 search_words_slurp_button_ = new QPushButton("<@>");
 make_slurp_button(search_words_slurp_button_);
 make_flip_button(search_words_flip_button_);

 search_words_flip_button_->setToolTip("Flip first and last words");
 search_words_slurp_button_->setToolTip("Merge all words into search");

 search_words_slurp_and_flip_button_ = new QPushButton("<@->");
 make_nav_button(search_words_slurp_and_flip_button_, 0x2BB6, 14);
 search_words_slurp_and_flip_button_->setToolTip("Merge and flip (e.g., reorder a proper name)");
 search_words_slurp_and_flip_button_->setMaximumHeight(22);

 search_words_reset_button_ = new QPushButton("reset");
 make_nav_button(search_words_reset_button_, 0x2386, 11, 28); //0x2940
 search_words_reset_button_->setToolTip("Reset");

 search_words_take_visible_first_button_ = new QPushButton("reset");
 make_nav_button(search_words_take_visible_first_button_, 0x293D, 11, 28);
 search_words_take_visible_first_button_->setToolTip("Use first word only");


 connect(search_words_reset_button_, &QPushButton::clicked, [this]()
 {
  search_words_reset();
 });

 connect(search_words_take_visible_first_button_, &QPushButton::clicked, [this]()
 {
  search_words_take_visible_first();
 });



 connect(search_words_slurp_button_, &QPushButton::clicked, [this]()
 {
  search_words_slurp();
 });

 connect(search_words_flip_button_, &QPushButton::clicked, [this]()
 {
  search_words_flip();
 });

 connect(search_words_slurp_and_flip_button_, &QPushButton::clicked, [this]()
 {
  search_words_slurp();
  search_words_flip();
 });



 connect(search_words_inc_high_button_, &QPushButton::clicked, [this]()
 {
  search_words_inc_high();
 });


 connect(clean_later_match_button_, &QPushButton::clicked, [this]()
 {
  clean_later_match();
 });


 connect(redo_both_matches_button_, &QPushButton::clicked, [this]()
 {
  redo_both_matches();
 });


 connect(redo_earlier_match_button_, &QPushButton::clicked, [this]()
 {
  redo_earlier_match();
 });

 connect(redo_later_match_button_, &QPushButton::clicked, [this]()
 {
  redo_later_match();
 });


 connect(search_words_dec_high_button_, &QPushButton::clicked, [this]()
 {
  search_words_dec_high();
 });

 connect(search_words_inc_low_button_, &QPushButton::clicked, [this]()
 {
  search_words_inc_low();
 });

 connect(search_words_dec_low_button_, &QPushButton::clicked, [this]()
 {
  search_words_dec_low();
 });


 search_words_layout_ = new QHBoxLayout;
 search_words_layout_->addWidget(search_words_reset_button_);
 search_words_layout_->addSpacing(14);
 search_words_layout_->addWidget(search_words_take_visible_first_button_);
 search_words_layout_->addSpacing(14);
 search_words_layout_->addWidget(search_words_dec_low_button_);
 search_words_layout_->addWidget(search_words_inc_low_button_);
 search_words_layout_->addSpacing(14);
 search_words_layout_->addWidget(search_words_dec_high_button_);
 search_words_layout_->addWidget(search_words_inc_high_button_);
 search_words_layout_->addSpacing(14);
 search_words_layout_->addWidget(search_words_flip_button_);
 search_words_layout_->addWidget(search_words_slurp_and_flip_button_);
 search_words_layout_->addSpacing(8);
 search_words_layout_->addWidget(search_words_slurp_button_);
 search_words_layout_->addStretch();
//? search_words_layout_->addStretch();

 search_words_layout_->addWidget(redo_both_matches_button_);
 search_words_layout_->addSpacing(17);

 search_words_layout_->addWidget(redo_earlier_match_button_);
 search_words_layout_->addSpacing(8);
 search_words_layout_->addWidget(redo_later_match_button_);
 search_words_layout_->addSpacing(8);
 search_words_layout_->addWidget(clean_later_match_button_);

 search_words_dec_high_button_->setMaximumWidth(20);
 search_words_inc_high_button_->setMaximumWidth(20);

 search_words_dec_low_button_->setMaximumWidth(20);
 search_words_inc_low_button_->setMaximumWidth(20);

 search_words_flip_button_->setMaximumWidth(30);
 search_words_flip_button_->setMaximumHeight(20);

 search_words_slurp_button_->setMaximumWidth(30);
 search_words_slurp_button_->setMaximumHeight(20);

 clean_later_match_button_->setMaximumWidth(40);

 current_matches_grid_layout_->addLayout(search_words_layout_, 0, 0, 1, 6);

 QFrame* current_matches_grid_layout_line = make_frame_as_line();

 current_matches_grid_layout_->addWidget(current_matches_grid_layout_line, 1, 0, 1, 6);

 current_matches_grid_layout_->addWidget(new QLabel("File:", this), 2, 2);

 html_file_name_line_edit_ = new QLineEdit(this);
 html_file_name_line_edit_->setPlaceholderText("N/A");

 current_matches_grid_layout_->addWidget(html_file_name_line_edit_, 2, 3);

 addendum_hits_line_edit_ = new QLineEdit(this);
 addendum_hits_line_edit_->setPlaceholderText("hits");
 addendum_hits_line_edit_->setMaximumWidth(120);

 current_matches_grid_layout_->addWidget(addendum_hits_line_edit_, 2, 4);


 html_details_layout_ = new QHBoxLayout;

 html_upload_button_ = new QPushButton("Upload");
 make_nav_button(html_upload_button_, 0x21EE, 14);  //21DB
 html_upload_button_->setToolTip("Upload");

 html_upload_button_->setMaximumWidth(50);

 connect(html_upload_button_, &QPushButton::clicked, [this]()
 {
  html_upload();
 });


 html_details_layout_->addWidget(new QLabel("Entries:", this));

 html_file_entries_line_edit_ = new QLineEdit(this);
 html_file_entries_line_edit_->setPlaceholderText("N/A");

 connect(html_file_entries_line_edit_, &QLineEdit::textChanged, [this](const QString& text)
 {
  composite_upload_button_->setEnabled(!text.isEmpty());
 });

 html_details_layout_->addWidget(html_file_entries_line_edit_);

 html_details_layout_->addStretch();
 html_details_layout_->addSpacing(10);

 current_matches_grid_layout_->addLayout(html_details_layout_, 2, 0, 1, 2);
// html_details_layout_->addSpacing(10);
// html_details_layout_->addWidget(html_upload_button_);
 current_matches_grid_layout_->addWidget(html_upload_button_, 2, 5);


 html_preview_dock_widget_ = new QDockWidget(this);

 html_preview_splitter_ = new QSplitter(Qt::Vertical, this);

 html_preview_text_edit_ = new QTextEdit(this);
 html_preview_supplement_text_edit_ = new QTextEdit(this);

 html_preview_text_edit_->setMaximumHeight(80);
 html_preview_supplement_text_edit_->setMaximumHeight(80);

 html_preview_splitter_->addWidget(html_preview_text_edit_);
 html_preview_splitter_->addWidget(html_preview_supplement_text_edit_);

 html_preview_dock_widget_->setWidget(html_preview_splitter_);
 html_preview_dock_widget_->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

 html_preview_dock_widget_->setMaximumWidth(3 * width() / 4);

 addDockWidget(Qt::BottomDockWidgetArea, html_preview_dock_widget_);

 page_text_view_tab_widget_ = new QTabWidget(this);
 page_text_view_text_edit_earlier_ = new QPlainTextEdit(this);
 page_text_view_text_edit_later_ = new QPlainTextEdit(this);
 page_text_view_tab_widget_->addTab(page_text_view_text_edit_earlier_, "Earlier");
 page_text_view_tab_widget_->addTab(page_text_view_text_edit_later_, "Later");
 page_text_view_dock_widget_ = new QDockWidget(this);

 page_text_view_dock_widget_->setMaximumWidth(width() / 4);
 page_text_view_dock_widget_->setMaximumHeight(80);

 page_text_view_dock_widget_->setWidget(page_text_view_tab_widget_);
 page_text_view_dock_widget_->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
 addDockWidget(Qt::TopDockWidgetArea, page_text_view_dock_widget_);

 connect(page_text_view_dock_widget_, &QDockWidget::topLevelChanged,
    [this](bool b)
 {
  if(b)
  {
   page_text_view_dock_widget_->setMaximumWidth(QDesktopWidget().availableGeometry().width());
   page_text_view_dock_widget_->setMaximumHeight(QDesktopWidget().availableGeometry().height());
   page_text_view_dock_widget_->resize(300, 400);

   html_preview_dock_widget_->setMaximumWidth(width());
  }
  else
  {
   page_text_view_dock_widget_->setMaximumWidth(width() / 4);
   page_text_view_dock_widget_->setMaximumHeight(80);
   page_text_view_dock_widget_->resize(width() / 4, 80);

  }

 });



 confirms_dock_widget_ = new QDockWidget(this);
 confirms_list_widget_ = new QListWidget(this);
 confirms_dock_widget_->setWidget(confirms_list_widget_);
 confirms_dock_widget_->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

 confirms_list_widget_->setMaximumWidth(width() / 3);

 connect(confirms_dock_widget_, &QDockWidget::topLevelChanged,
    [this](bool b)
 {
  if(b)
  {
   confirms_dock_widget_->setMaximumWidth(QDesktopWidget().availableGeometry().width());
   confirms_list_widget_->setMaximumWidth(QDesktopWidget().availableGeometry().width());
   html_preview_dock_widget_->setMaximumWidth(QDesktopWidget().availableGeometry().width());
  }
  else
  {
   confirms_dock_widget_->setMaximumWidth(width() / 3);
   confirms_list_widget_->setMaximumWidth(width() / 3);
   html_preview_dock_widget_->setMaximumWidth(2 * width() / 3);
  }


  //  confirms_dock_widget_->resize(300, 300);

//  html_preview_dock_widget_->setMaximumWidth(width());

 });


 confirms_list_widget_->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(confirms_list_widget_, &QListWidget::customContextMenuRequested,
   [this](const QPoint& qp)
 {
  QListWidgetItem* item = confirms_list_widget_->itemAt(qp);
  QMenu* menu = create_confirms_list_widget_context_menu(item);
  if(menu)
  {
   menu->setAttribute(Qt::WA_DeleteOnClose);
   menu->popup(confirms_list_widget_->viewport()->mapToGlobal(qp));
  }
 });

 connect(confirms_list_widget_, &QListWidget::itemChanged,
   [this](QListWidgetItem*)
 {
  check_generate_html();
 });

 addDockWidget(Qt::BottomDockWidgetArea, confirms_dock_widget_);


// void reset_html_details();

// connect(cb_number_of_children_,  QOverload<int>::of(&QComboBox::currentIndexChanged),
//   [this](int which)
// {
//  if(which < 0)
//    return;
//  u1 count = which + 1;
//  u1 rc = children_grid_layout_->rowCount() - 1;
//  if(count == rc)
//    return;
//  if(count < rc)
//  {
//   // // erase lines?
//   QMessageBox::StandardButton sb = QMessageBox::question(this, "Reduce number of lines?",
//     "Do you want to delete the extra %1 lines?"_qt.arg(rc - count));

//   if(sb == QMessageBox::Yes)
//   {
//    QVector<QWidget*> to_be_removed;
//    for(u1 c = count; c < rc; ++c)
//    {
//     to_be_removed << children_grid_layout_->itemAtPosition(c + 1, 0)->widget();
//     to_be_removed << children_grid_layout_->itemAtPosition(c + 1, 1)->widget();
//    }

//    for(QWidget* w : to_be_removed)
//    {
//     children_grid_layout_->removeWidget(w);
//     w->hide();
//     w->deleteLater();
//    }
////    children_grid_layout_->removeItem(children_grid_layout_->itemAtPosition(rrc - 1, 0));


//    //qDebug() << "erase!";
//   }
//  }
//  else
//  {
//  while(rc++ < count)
//    add_children_line();
//  }

// });


 current_search_group_box_layout_->addLayout(current_matches_grid_layout_);

 current_search_group_box_->setLayout(current_search_group_box_layout_);

 entry_layout_->addWidget(current_search_group_box_);

 main_layout_->addLayout(entry_layout_);

 composite_upload_button_ = new QPushButton("composite", this);
 make_nav_button(composite_upload_button_, 0x23C3, 16);  //21DB
 composite_upload_button_->setToolTip("Composite upload");

 entry_forward_button_  = new QPushButton("->>", this);
 entry_backward_button_  = new QPushButton("<<-", this);
 entry_double_backward_button_ = new QPushButton("<<--", this);
 make_entry_backward_button(entry_backward_button_);
 make_entry_forward_button(entry_forward_button_);
 make_entry_double_backward_button(entry_double_backward_button_);

 entry_forward_button_->setToolTip("Next index entry");
 entry_backward_button_->setToolTip("Previous index entry");
 entry_backward_button_->setToolTip("First index entry");

// entry_backward_button_->setEnabled(false);
// entry_double_backward_button_->setEnabled(false);

// entry_backward_button_->setMaximumWidth(60);

// entry_forward_button_->setMaximumWidth(60);
// entry_backward_button_->setMaximumWidth(60);

 connect(composite_upload_button_, &QPushButton::clicked, [this]()
 {
  composite_upload();
 });

 connect(entry_forward_button_, &QPushButton::clicked, [this]()
 {
  entry_forward();
 });

 connect(entry_double_backward_button_, &QPushButton::clicked, [this]()
 {
  entry_back_to_start();
 });

 connect(entry_backward_button_, &QPushButton::clicked, [this]()
 {
  entry_backward();

//  QString city = le_city_->text();
//  QString state = cb_state_or_province_->currentText();
//  //if(state == "N/A")

//  QRegularExpression rx("^(\\w\\w)\\s+\\(");
//  QRegularExpressionMatch rxm = rx.match(state);
//  if(!rxm.hasMatch())
//    return;
//  state = rxm.captured(1);

//  qDebug() << "state = " << state;

  //?Case_Map_GIS_Service cmgs("osm");
//  QPair<r8, r8> latlon; // cmgs.get_city_latitude_and_longitude(city, state);

//  qDebug() << "latlon = " << latlon;

//  QGeoLocation loc;
//  loc.setCoordinate(QGeoCoordinate(latlon.first, latlon.second));
//  Q_EMIT(location_marker_requested(loc));

 });


 generate_html_button_ = new QPushButton("html", this);
 generate_html_button_->setToolTip("Generate html");
 generate_html_button_->setMaximumWidth(50);
 generate_html_button_->setMaximumHeight(20);
 generate_html_button_->setStyleSheet(entry_nav_button_style_sheet_green_(10));


 connect(generate_html_button_, &QPushButton::clicked, [this]()
 {
  regenerate_html();
 });


 generate_then_forward_button_ = new QPushButton("html->", this);
 generate_then_forward_button_->setToolTip("Generate html, then entry forward");
 make_entry_nav_button(generate_then_forward_button_, 0x21ac);  //21DB


 connect(generate_then_forward_button_, &QPushButton::clicked, [this]()
 {
  regenerate_html();
  entry_forward();
 });


 always_generate_html_button_ = new QPushButton("auto", this);
 always_generate_html_button_->setCheckable(true);
 always_generate_html_button_->setToolTip("Always generate html on match confirm");
 always_generate_html_button_->setMaximumWidth(50);
 always_generate_html_button_->setMaximumHeight(20);
 always_generate_html_button_->setStyleSheet(entry_nav_button_style_sheet_green_(10));


 connect(always_generate_html_button_, &QPushButton::toggled, [this](bool b)
 {
  if(b)
    check_generate_html();
 });


 bottom_layout_ = new QHBoxLayout;

 bottom_layout_->addWidget(composite_upload_button_);
 bottom_layout_->addStretch();

 bottom_layout_->addWidget(entry_double_backward_button_);
 bottom_layout_->addSpacing(17);
 bottom_layout_->addWidget(entry_backward_button_);
 bottom_layout_->addWidget(entry_forward_button_);
 bottom_layout_->addStretch();
 bottom_layout_->addWidget(generate_html_button_);
 bottom_layout_->addSpacing(2);
 bottom_layout_->addWidget(generate_then_forward_button_);
 bottom_layout_->addSpacing(20);
 bottom_layout_->addWidget(always_generate_html_button_);
 bottom_layout_->addStretch();

 bottom_layout_->addWidget(button_box_);

 QFrame* bottom_line = make_frame_as_line();
 main_layout_->addWidget(bottom_line);

 main_layout_->addLayout(bottom_layout_);

 QFrame* far_bottom_line = make_frame_as_line();
 main_layout_->addWidget(far_bottom_line);

 main_frame_->setLayout(main_layout_);

 setCentralWidget(main_frame_);


 //?setStyleSheet(basic_button_style_sheet_());

 setWindowTitle("Index Entry Dialog");

 load_bookmarks_file();

 load_earlier_matches();

 setContextMenuPolicy(Qt::CustomContextMenu);
 connect(this, &QMainWindow::customContextMenuRequested,
   [this](const QPoint& qp)
 {
  QMenu* menu = new QMenu; //(item);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  menu->addAction("Browse to Entry", [this]()
  {
   QString text = QInputDialog::getText(this, "Enter Id",
     "Must be a valid number");

   u2 id = text.toInt();

   if(id == 0 || id > max_entry_id_)
     QMessageBox::warning(this, "Invalid", "Entry was not a valid number, or was too large");
   else
   {
    load_entry(id);
    entry_index_range_ = {id, id};
    reset_file_entries_text();
   }

  });

  menu->addAction("Back to First Entry", [this]()
  {
   load_entry(1);
   entry_index_range_ = {1, 1};
   reset_file_entries_text();
  });

  menu->addAction("Collapse Entry Range", [this]()
  {
   entry_index_range_.second = entry_index_range_.first;
   reset_file_entries_text();
  });

  menu->addAction("Merge HTML", [this]()
  {
   QString t = html_preview_text_edit_->toPlainText();
   QString s = html_preview_supplement_text_edit_->toPlainText();
   if(!s.isEmpty())
   {
    if(t.simplified().endsWith(":"))
      t += s;
    else
      t += ". " + s;
   }

   html_preview_text_edit_->setText(t);
   html_preview_supplement_text_edit_->clear();
  });

  menu->addAction("Search entry keys", [this]()
  {
   QString text = QInputDialog::getText(this, "Enter Search Term",
     "Will match entry keys");
  });

  menu->addAction("Search supplement", [this]()
  {
   QString text = QInputDialog::getText(this, "Enter Search Term",
       "Will match supplements (e.g., \"See Also\"");
  });


  menu->addAction("Toggle HTML/Plain Text", [this]()
  {
   toggle_html();
  });

  if(current_nav_filter_ != Nav_Filters::Range)
  {
   menu->addAction("Activate \"--\" Nav Filter", [this]()
   {
    activate_nav_filter(Nav_Filters::Range);
   });
  }

  if(current_nav_filter_ != Nav_Filters::Roman)
  {
   menu->addAction("Activate \"Roman\" Nav Filter", [this]()
   {
    activate_nav_filter(Nav_Filters::Roman);
   });
  }

  if(current_nav_filter_ != Nav_Filters::Missing)
  {
   menu->addAction("Activate \"Missing\" Nav Filter", [this]()
   {
    activate_nav_filter(Nav_Filters::Missing);
   });
  }

  if(current_nav_filter_ != Nav_Filters::New_Terms)
  {
   menu->addAction("Activate \"New Terms\" Nav Filter", [this]()
   {
    activate_nav_filter(Nav_Filters::New_Terms);
   });
  }

  if(current_nav_filter_ != Nav_Filters::None)
  {
   menu->addAction("Deactivate Nav Filter", [this]()
   {
    activate_nav_filter(Nav_Filters::None);
   });
  }

  menu->addAction("Close All", [this]()
  {
   earlier_pdf_dialog_->close();
   later_pdf_dialog_->close();
   close();
  });

  menu->popup(mapToGlobal(qp));

 });


}


QFrame* Index_Entry_Review_Dialog::make_frame_as_line()
{
 QFrame* result = new QFrame(this);
 result->setFrameShape(QFrame::HLine);
 result->setFrameShadow(QFrame::Sunken);
 return result;
}


void Index_Entry_Review_Dialog::note_addendum_hits(QVector<int>& hits)
{
 QString text;
 for(int i : hits)
   text += "%1;"_qt.arg(i);

 if(text.endsWith(";"))
   text.chop(1);

 addendum_hits_line_edit_->setText(text);
}


void Index_Entry_Review_Dialog::load_bookmarks_file()
{
 QString text = KA::TextIO::load_file(bookmarks_file_);
 QStringList qsl = text.simplified().split(" ");
 for(QString s : qsl)
 {
  QStringList qsl1 = s.split(";");
  bookmarks_.push_back({qsl1.first().toInt(),
    qsl1.last().toInt()});
 }
}

void Index_Entry_Review_Dialog::save_bookmarks_file()
{
 QString content;
 for(Entry_Update_Key k : bookmarks_)
 {
  content += "%1;%2 \n"_qt.arg(k.entry_id).arg(k.match_index);
 }
 KA::TextIO::save_file(bookmarks_file_, content);
}

void Index_Entry_Review_Dialog::check_for_bookmarks()
{
 if(bookmarks_.contains(current_entry_key_) && !entry_update_is_Bookmarked())
 {
  entry_update_note_Bookmarked();
 }

}


void Index_Entry_Review_Dialog::check_bookmark()
{
 if(!bookmarks_.contains(current_entry_key_))
 {
  bookmarks_.push_back(current_entry_key_);
  save_bookmarks_file();
 }
}


void Index_Entry_Review_Dialog::remove_bookmark()
{
 int ix = bookmarks_.indexOf(current_entry_key_);

 if(ix != -1)
 {
  bookmarks_.remove(ix);
  save_bookmarks_file();
 }

}


void Index_Entry_Review_Dialog::set_page_text_view_text_earlier(QString text)
{
 page_text_view_text_edit_earlier_->setPlainText(text);
}

void Index_Entry_Review_Dialog::set_page_text_view_text_later(QString text)
{
 page_text_view_text_edit_later_->setPlainText(text);
}

QString escape_context(QString context, QColor color)
{
 return context.replace("(@",
   QString("<span style='background:rgba(%1,%2,%3,%4)'>")
   .arg(color.red()).arg(color.green()).arg(color.blue())
   .arg(color.alpha())).replace("@)", "</span>");
}



void Index_Entry_Review_Dialog::check_entry_value_manual_update()
{
 if(entry_update_is_Manually_Edited())
 {
  entry_update_map_[current_entry_key_].manual_update = earlier_match_code_edit_line_edit_->text();
 }
}


void Index_Entry_Review_Dialog::search_update()
{
 if(active_earlier_match_code_index_ == 0)
   return;

 u2 page_number = ref_code_to_earlier_page_number(current_page_ref_pair_.first);

 QString context;
 QStringList paragraph_codes;

 later_pdf_dialog_->search_update(current_entry_key_.to_pair(), current_entry_id_, search_text_line_edit_->text(),
   active_earlier_match_code_index_, page_number, &paragraph_codes, &context);

 cached_paragraph_codes_[current_entry_key_] = paragraph_codes;

 comparison_left_text_edit_->setHtml(escape_context(context, QColor(50, 200, 100, 30)));

 setWindowState(Qt::WindowState::WindowNoState);

 later_pdf_dialog_->setWindowState(Qt::WindowState::WindowActive);
 later_pdf_dialog_->activateWindow();
}




void Index_Entry_Review_Dialog::composite_upload()
{
 update_generated_htmls();

 QString file = html_file_entries_line_edit_->text();
 if(file.isEmpty())
   return;

 QString text;
 QTextStream qts(&text);

 static QString pre_template = R"(
 <html><head><style>
div {padding-top:11pt; font-size:18pt;}
 </style></head><body>

  )";

 static QString post_template = R"(
 </body></html>)";

 qts << pre_template;

 for(u2 i = entry_index_range_.first; i <= entry_index_range_.second; ++i)
 {
  QStringList qsl = generated_htmls_.value(i);
  if(qsl.isEmpty())
    continue;

  QString ind = "\n  <span class='note'> {%1} </span> \n"_qt.arg(i);

  QString html = qsl.first();
  html.remove("<html>");
  html.remove("<body>");
  html.remove("</body>");
  html.remove("</html>");
  html.remove("</div>");

  qts //<< "<div class='index-entry'>"
      << html.simplified();

  if(qsl.size() == 1 || qsl[1].isEmpty())
  {
   qts << ind << "</div>\n\n";
   continue;
  }

  qDebug() << "  \n\n\n  ";

  qDebug() << text;

  qDebug() << "  \n\n\n  ";

  qDebug() << html.simplified();

  if(html.simplified().endsWith(": </span>"))
    qts << qsl[1] << ind << "</div>\n\n";
  else
    qts << ". " << qsl[1] << ind << "</div>\n\n";
 }

 qDebug() << "  \n\n\n  ";

 qDebug() << text;

 qts << post_template;

 KA::TextIO::save_file("/home/nlevisrael/Downloads/m2m/w_pdf/hold.txt", text);

 ftp_upload(file, text);
}



void Index_Entry_Review_Dialog::clear_most_recent_match(int page_number)
{
 earlier_pdf_dialog_->clear_most_recent_match(current_entry_id_, page_number);

 setWindowState(Qt::WindowState::WindowActive);
 activateWindow();
}


void Index_Entry_Review_Dialog::clear_earlier_highlights()
{
 earlier_pdf_dialog_->clear_all_highlights();
}


void Index_Entry_Review_Dialog::redo_later_match()
{
// if(earlier_match_codes_.isEmpty())
//   return;

 search_update();
}

void Index_Entry_Review_Dialog::clean_later_match()
{
 later_pdf_dialog_->clear_all_highlights();
}



void Index_Entry_Review_Dialog::redo_both_matches()
{
 redo_earlier_match();
 redo_later_match();
}


void Index_Entry_Review_Dialog::redo_earlier_match()
{
 if(earlier_match_codes_.isEmpty())
   return;

 earlier_highlight();
}

void Index_Entry_Review_Dialog::earlier_highlight()
{
 u2 page_number = ref_code_to_earlier_page_number(current_page_ref_pair_.first);
 earlier_pdf_dialog_->load_page(page_number);

 setWindowState(Qt::WindowState::WindowNoState);

 earlier_pdf_dialog_->setWindowState(Qt::WindowState::WindowActive);
 earlier_pdf_dialog_->activateWindow();

 QString context;
 //QStringList paragraph_codes;

 earlier_pdf_dialog_->highlight_match(current_entry_id_, search_text_line_edit_->text(),
   nullptr, context);

 comparison_right_text_edit_->setHtml(escape_context(context, QColor(50, 100, 200, 30)));
}


void Index_Entry_Review_Dialog::setup_comparison_window()
{
 comparison_dock_widget_ = new QDockWidget(this);

 comparison_splitter_ = new QSplitter(comparison_dock_widget_);
 comparison_left_text_edit_ = new QTextEdit(comparison_splitter_);
 comparison_right_text_edit_ = new QTextEdit(comparison_splitter_);
 comparison_splitter_->addWidget(comparison_left_text_edit_);
 comparison_splitter_->addWidget(comparison_right_text_edit_);

 comparison_dock_widget_->setWidget(comparison_splitter_);

 comparison_dock_widget_->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

 addDockWidget(Qt::TopDockWidgetArea, comparison_dock_widget_);

// comparison_right_text_edit_->setFormat(Qt::RichText);
// comparison_left_text_edit_->setFormat(Qt::RichText);

 //comparison_dock_widget_
}


void Index_Entry_Review_Dialog::clear_confirms_list_widget()
{
 confirms_list_widget_->clear();
}


QMenu* Index_Entry_Review_Dialog::create_confirms_list_widget_context_menu(QListWidgetItem* item)
{
 QMenu* result;

 if(!item)
 {
  QVector<QListWidgetItem*> restores;
  QVector<QListWidgetItem*> unselects;
  for(int row = 0; row < confirms_list_widget_->count(); ++row)
  {
   QListWidgetItem* i = confirms_list_widget_->item(row);
   if(i->isSelected())
     unselects.push_back(i);
   if(i->flags() & Qt::ItemIsEnabled)
     continue;
   restores.push_back(i);
  }

  if(restores.isEmpty() && unselects.isEmpty())
    return nullptr;

  result = new QMenu;

  if(!restores.isEmpty())
    result->addAction("Restore All", [this, restores]()
    {
     for(QListWidgetItem* r : restores)
     {
      r->setFlags(r->flags() | Qt::ItemIsEnabled);
     }
     check_generate_html();
    });

  // //  can there ever be more than one?  Maybe someday this
   //    will be a QListView subclass with multiple selections ...
  if(!unselects.isEmpty())
    result->addAction("Unselect", [this, unselects]()
    {
     for(QListWidgetItem* uns : unselects)
     {
      uns->setSelected(false);
     }
    });

  return result;
 }

 result = new QMenu;

 QString text = item->text();

 bool nn = text.contains("nn");
 bool n = nn? false : text.contains("n");

 if(nn)
   result->addAction("Remove nn", [this, item]()
   {
    QString text = item->text();
    int ix = text.indexOf("nn");
    text = text.mid(0, ix);
    item->setText(text);
   });

 if(n)
   result->addAction("Remove n", [this, item]()
   {
    QString text = item->text();
    int ix = text.indexOf("n");
    text = text.mid(0, ix);
    item->setText(text);
   });

 if(n && !nn)
   result->addAction("Add nn", [this, item]()
   {
    QString text = item->text();
    int ix = text.indexOf("n");
    text.insert(ix, "n");
    item->setText(text);
   });

 if(!n && !nn)
 {
  result->addAction("Add nn", [this, item]()
  {
   QString text = item->text();
   text += "nn";
   item->setText(text);
  });

  result->addAction("Add n", [this, item]()
  {
   QString text = item->text();
   text += "n";
   item->setText(text);
  });
 }

 if(!text.contains("--"))
 {
  result->addAction("Add --", [this, item]()
  {
   QString text = item->text();
   int ix = text.indexOf("n");
   if(ix != -1)
     text.insert(ix, "--");
   else
     text.prepend("--");
   item->setText(text);
  });
 }

 if(item->flags() & Qt::ItemIsEnabled)
 {
  result->addAction("Exclude", [this, item]()
  {
   item->setFlags(item->flags() & (~Qt::ItemIsEnabled));
   item->setSelected(false);
   check_generate_html();
  });

  if(item->isSelected())
  {
   result->addAction("Unselect", [this, item]()
   {
    item->setSelected(false);
   });
  }

  result->addAction("Edit", [this, item]()
  {
   confirms_list_widget_->editItem(item);
   item->setSelected(false);
  });
 }
 else
   result->addAction("Include", [this, item]()
   {
    item->setFlags(item->flags() | Qt::ItemIsEnabled);
    check_generate_html();
   });

 result->addAction("Generate HTML", [this]()
 {
  regenerate_html();
 });


 return result;
}


void Index_Entry_Review_Dialog::check_generate_html()
{
 if(always_generate_html_button_->isChecked())
 {
  regenerate_html();
 }
}


void Index_Entry_Review_Dialog::regenerate_html()
{
 QStringList codes;

 for(int row = 0; row < confirms_list_widget_->count(); ++row)
 {
  QListWidgetItem* i = confirms_list_widget_->item(row);
  if(i->flags() & Qt::ItemIsEnabled)
  {
   codes.push_back(i->text());
  }
 }

 update_html(codes);
}

void Index_Entry_Review_Dialog::html_upload()
{
 QString file_name = html_file_name_line_edit_->text();
 if(file_name.isEmpty())
   return;


 QString text = html_text_;

 QString s = html_preview_supplement_text_edit_->toPlainText();

 if(!s.isEmpty())
 {
  text.replace(": </span></div>", ": </span>%1<@/div>"_qt.arg(s));

  text.replace("</div>", ". %1</div>"_qt.arg(s));
  text.replace("<@/div>", "</div>");
 }

 static QString pre_template = R"(
 <html><head><style>
div {padding-top:11pt; font-size:18pt;}
 </style></head>)";


 text.replace("<html>", pre_template);

 if(text.isEmpty())
   return;

 ftp_upload(file_name, text);
}


void Index_Entry_Review_Dialog::ftp_upload(QString file_name, QString text)
{
 QString template_path = ftp_folder_ + "/template";
 QString template_text = KA::TextIO::load_file(template_path);

 template_text.replace("%FILE%", file_name);

 QString full_path = KA::TextIO::save_file_to_folder(file_name, text, ftp_folder_);

 qDebug() << template_text;

 QProcess* qp = new QProcess();

 qp->setWorkingDirectory(ftp_folder_);

 qp->start(template_text);
 qp->waitForFinished(-1);
 QString output = qp->readAllStandardOutput();
 qp->terminate();

 if(output.isEmpty())
 {
  later_pdf_dialog_->show_status("ftp upload: %1"_qt.arg(full_path));
 }
 else
 {
  later_pdf_dialog_->show_status("ftp output: %1"_qt.arg(output));
 }

 qDebug() << output;
 qp->deleteLater();
}


void Index_Entry_Review_Dialog::update_html(QStringList page_numbers)
{
 QString sub_only;
 if(page_numbers.isEmpty())
 {
  if(current_index_entry_)
  {
   QString supp = current_index_entry_->supplement;
   QString carr = current_index_entry_->carried;
   if(supp.isEmpty() && carr.isEmpty())
   {
    if(current_index_entry_->sub_count > 1)
      sub_only = "(%1 subentries)"_qt.arg(current_index_entry_->sub_count);
    else if(current_index_entry_->sub_count == 1)
      sub_only = "(%1 subentry)"_qt.arg(current_index_entry_->sub_count);
    else
      return;

   }
  }
 }

 if(current_index_entry_)
 {
  QString parent_ref;
  if(current_index_entry_->parent_id)
  {
   Index_Entry& ie = index_entries_[current_index_entry_->parent_id - 1];
   parent_ref = ie.key;
   if(parent_ref.size() > 12)
   {
    parent_ref.truncate(12);
    parent_ref.append("...");
   }
   parent_ref = " [%1/%2] "_qt.arg(parent_ref).arg(ie.id);
  }
  update_html(current_index_entry_->key, parent_ref, page_numbers, sub_only);
 }
}


void Index_Entry_Review_Dialog::update_html(QString key, QString parent_ref,
  QStringList page_numbers, QString sub_only)
{
 reset_toggle_html();

 html_text_.clear();

 //Index_Entry& ie = index_entries_[]

 static QString index_entry_template = R"(
   <html><body><div class='index-entry'><span>%1%2</span>, %3</div></body></html>
                                       )";

 static QString index_entry_template_redirect = R"(
   <html><body><div class='index-redirect'><span>%1%2: </span></div></body></html>
                                       )";

 static QString index_entry_template_subentries = R"(
   <html><body><div class='index-subentries'><span>%1%2: %3</span></div></body></html>
                                       )";

 if(page_numbers.isEmpty())
 {
  if(sub_only.isEmpty())
    html_text_ = index_entry_template_redirect.arg(parent_ref).arg(key);
  else
    html_text_ = index_entry_template_subentries.arg(parent_ref).arg(key).arg(sub_only);
 }
 else
 {
  QString pages_text = page_numbers.join(", ");
  html_text_ = index_entry_template.arg(parent_ref).arg(key).arg(pages_text);
 }

 html_preview_text_edit_->setPlainText(html_text_);
}


//void Index_Entry_Review_Dialog::clear_most_recent_match(int page_number)
//{
// update_split_window("text1", "text2");
//}


void Index_Entry_Review_Dialog::confirm_match(QPair<u2, s2> pr,
  int page_number, QString paragraph_code)
{
 activateWindow();

 if(!current_index_entry_)
   return;

 Entry_Update_Key key = Entry_Update_Key::from_pair(pr);

 QStringList paragraph_codes = cached_paragraph_codes_.value(key);

 if(key.entry_id != current_entry_id_)
 {
  load_entry(key.entry_id, &key.match_index);
  entry_index_range_ = {key.entry_id, key.entry_id};
  reset_file_entries_text();
 }
 else if(key.match_index != current_entry_key_.match_index)
 {
  earlier_match_set_index(key.match_index);
 }

 entry_update_note_Confirmed();
 // //  is there a way to avoid extraneous checks?
 reset_current_entry_check_boxes();

 //entry_update_map_.value(current_entry_key_)

 QString text;
 int roman = later_pdf_dialog_->page_number_to_text(page_number, text); //QString::number(page_number);

 const QVector<Page_Ref_Pair>& refs = current_index_entry_->refs;
 if(current_entry_key_.match_index > 0 && current_entry_key_.match_index <= refs.size())
 {

  if(entry_update_is_Manually_Edited())
  {
   QString upd = entry_update_map_.value(current_entry_key_).manual_update;
   if(upd.isEmpty())
     text += "??";
   else
     text = upd;
  }
  else
  {
   Page_Ref_Pair ref = refs[current_entry_key_.match_index - 1];
   if(!entry_update_is_Detach_Page_Number())
     text += ref.to_granular_text();

   if(text.endsWith("--"))
   {
    text += "*";
    Index_Entry& ie = index_entries_[current_entry_key_.entry_id - 1];
    Page_Ref_Pair pr1 = ie.refs[current_entry_key_.match_index - 1];
    if(pr1.second.is_valid())
    {
     if(pr1.second.number)
     {
      int diff = pr1.second.number - pr1.first.number;
      int n1 = page_number + diff;
      QString ntext;
      int nroman = later_pdf_dialog_->page_number_to_text(n1, ntext); //QString::number(page_number);
      text += ntext;
     }
     else text += "?";
    }
    else text += "?";
   }

  }
 }


 text += " @" + paragraph_codes.join(";");

 QListWidgetItem* item = new QListWidgetItem(text, confirms_list_widget_);
 item->setFlags(item->flags() | Qt::ItemIsEditable);
 confirms_list_widget_->addItem(item);
}


void Index_Entry_Review_Dialog::reclaim_focus()
{
 setWindowState(Qt::WindowState::WindowActive);
}


QString Index_Entry_Review_Dialog::match_code_long_display(const Page_Ref_Pair& pr)
{
 return pr.to_long_display();
}

void Index_Entry_Review_Dialog::reset_file_entries_text()
{
 if(entry_index_range_.first == entry_index_range_.second)
   html_file_entries_line_edit_->setText(QString("%1.htm")
     .arg(entry_index_range_.first));
 else
   html_file_entries_line_edit_->setText(QString("%1-%2.htm")
     .arg(entry_index_range_.first).arg(entry_index_range_.second));
}


void Index_Entry_Review_Dialog::entry_back_to_start()
{
 if(current_entry_id_ != 1)
 {
  load_entry(1);
  entry_index_range_.second = current_entry_id_;
  reset_file_entries_text();
 }
}


void Index_Entry_Review_Dialog::entry_forward(QVector<u2>& vec)
{
 if(vec.isEmpty())
   return;

 s4 ix = vec.indexOf(current_entry_id_);
 if(ix == -1)
 {
  if(vec.last() <= current_entry_id_)
    return;
  for(u2 i = 0; i < vec.size(); ++i)
  {
   if(vec[i] > current_entry_id_)
   {
    ix = i;
    break;
   }
  }
 }
 else if(ix == vec.size())
   return;
 else
   ++ix;

 load_entry(vec[ix]);
 entry_index_range_.second = current_entry_id_;
 reset_file_entries_text();
}

void Index_Entry_Review_Dialog::entry_forward()
{
 if(current_nav_filter_ != Nav_Filters::None)
 {
  entry_forward(ref_groups_filtered_[current_nav_filter_]);
  return;
 }

 if(current_entry_id_ < max_entry_id_)
 {
  load_entry(current_entry_id_ + 1);
  entry_index_range_.second = current_entry_id_;
  reset_file_entries_text();
 }
}

void Index_Entry_Review_Dialog::entry_backward(QVector<u2>& vec)
{
 if(vec.isEmpty())
   return;

 s4 ix = vec.indexOf(current_entry_id_);

 if(ix == -1)
 {
  if(vec.first() >= current_entry_id_)
    return;
  for(u2 i = 1; i < vec.size(); ++i)
  {
   if(vec[i] > current_entry_id_)
   {
    ix = i - 1;
    break;
   }
  }
 }
 else if(ix == 0)
   return;
 else
   --ix;

 load_entry(vec[ix]);
 entry_index_range_.first = current_entry_id_;
 reset_file_entries_text();
}


void Index_Entry_Review_Dialog::entry_backward()
{
 if(current_nav_filter_ != Nav_Filters::None)
 {
  entry_backward(ref_groups_filtered_[current_nav_filter_]);
  return;
 }

 if(current_entry_id_ > 1)
 {
  load_entry(current_entry_id_ - 1);
  entry_index_range_.first = current_entry_id_;
  reset_file_entries_text();
 }
}


void Index_Entry_Review_Dialog::check_search_update()
{
// if(earlier_match_codes_.isEmpty())
//   return;

 if(search_update_button_->isChecked())
   search_update();
}


void Index_Entry_Review_Dialog::check_earlier_highlight()
{
 if(earlier_match_codes_.isEmpty())
   return;

 if(earlier_track_highlight_button_->isChecked())
   earlier_highlight();
}


void Index_Entry_Review_Dialog::update_current_entry_map_index()
{
 current_entry_key_.match_index = active_earlier_match_code_index_;
 check_update_entry_update_map();
 check_for_bookmarks();
 reset_current_entry_check_boxes();
 reset_current_entry_update_text();
}


void Index_Entry_Review_Dialog::earlier_match_set_index(u2 target)
{
 if(target > max_earlier_match_code_index_)
   return;

 active_earlier_match_code_index_ = target;
 reset_active_earlier_match_code();
 check_nav_buttons();

 check_earlier_highlight();
 update_current_entry_map_index();
}


void Index_Entry_Review_Dialog::earlier_match_forward()
{
 ++active_earlier_match_code_index_;
 reset_active_earlier_match_code();
 check_nav_buttons();

 check_earlier_highlight();
 update_current_entry_map_index();
}

void Index_Entry_Review_Dialog::earlier_match_backward()
{
 --active_earlier_match_code_index_;
 reset_active_earlier_match_code();
 check_nav_buttons();

 check_earlier_highlight();
 update_current_entry_map_index();
}


void Index_Entry_Review_Dialog::earlier_match_back_to_start()
{
 active_earlier_match_code_index_ = 1;
 reset_active_earlier_match_code();
 check_nav_buttons();

 check_earlier_highlight();
 update_current_entry_map_index();
}


void Index_Entry_Review_Dialog::reset_active_earlier_match_code()
{
 current_page_ref_pair_ = earlier_match_codes_[active_earlier_match_code_index_ - 1].first;
 current_page_ref_string_ = earlier_match_codes_[active_earlier_match_code_index_ - 1].second;
 current_page_ref_long_display_ = match_code_long_display(current_page_ref_pair_);
 active_earlier_match_code_line_edit_->setText(current_page_ref_long_display_);

 earlier_match_code_edit_line_edit_->setFocus();
}



void Index_Entry_Review_Dialog::match_code_display(QString& text)
{
 text.replace("^", "");
 text.replace("--", "-");
 text.replace("%", "");
 text.replace("@", "");
 text.replace(";", "-");

 if(text.contains("/"))
 {
  text.replace("/", "(");
  text.append(")");
 }
}

QString Index_Entry_Review_Dialog::match_code_display(const QVector<QPair<Page_Ref_Pair, QString>>& prs)
{
 QString result;
 QTextStream qts(&result);

 int count = 0;
 for(auto pr : prs)
 {
  if(count)
    qts << " ";
  ++count;

  QString qs = pr.second;
  match_code_display(qs);

  qts << qs;
 }
 return result;
}

void Index_Entry_Review_Dialog::check_nav_buttons()
{
 if(max_entry_id_ > 1)
   search_words_take_visible_first_button_->setEnabled(true);
 else
   search_words_take_visible_first_button_->setEnabled(false);

 if(current_entry_id_ < 2)
   entry_backward_button_->setEnabled(false);
 else
   entry_backward_button_->setEnabled(true);

 if(current_entry_id_ < 3)
   entry_double_backward_button_->setEnabled(false);
 else
   entry_double_backward_button_->setEnabled(true);


 if(current_entry_id_ < max_entry_id_)
   entry_forward_button_->setEnabled(true);
 else
   entry_forward_button_->setEnabled(false);


 if(active_earlier_match_code_index_ < 2)
 {
  active_earlier_match_code_backward_button_->setEnabled(false);
  active_earlier_match_code_back_to_start_button_->setEnabled(false);
 }
 else
 {
  active_earlier_match_code_backward_button_->setEnabled(true);
  active_earlier_match_code_back_to_start_button_->setEnabled(true);
 }

 if(active_earlier_match_code_index_ < max_earlier_match_code_index_)
   active_earlier_match_code_forward_button_->setEnabled(true);
 else
   active_earlier_match_code_forward_button_->setEnabled(false);


 if(current_search_word_list_high_ < 2)
   search_words_dec_high_button_->setEnabled(false);
 else
   search_words_dec_high_button_->setEnabled(true);

 if(current_search_word_list_high_ < available_search_word_list_count_)
   search_words_inc_high_button_->setEnabled(true);
 else
   search_words_inc_high_button_->setEnabled(false);


 if(current_search_word_list_low_ < 2)
   search_words_dec_low_button_->setEnabled(false);
 else
   search_words_dec_low_button_->setEnabled(true);

 if(current_search_word_list_low_ < available_search_word_list_count_)
   search_words_inc_low_button_->setEnabled(true);
 else
   search_words_inc_low_button_->setEnabled(false);


 if(current_search_word_list_high_ > current_search_word_list_low_)
   search_words_flip_button_->setEnabled(true);
 else
   search_words_flip_button_->setEnabled(false);

 if(available_search_word_list_count_ > 1)
 {
  search_words_slurp_button_->setEnabled(true);
  if(current_search_word_list_low_ == 1 && current_search_word_list_high_ == available_search_word_list_count_)
    slurp_count_ = available_search_word_list_count_;
  else
    slurp_count_ = 0;
 }
 else
 {
  slurp_count_ = 0;
  search_words_slurp_button_->setEnabled(false);
 }

// u2 available_search_word_list_count_;
// u2 current_search_word_list_count_;
// u2 current_search_word_list_start_;


}


void Index_Entry_Review_Dialog::reset_search_word_list()
{
 reset_search_word_list(current_search_word_list_low_ - 1, current_search_word_list_high_ - 1);
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::reset_search_word_list(u2 low, u2 high)
{
 QString text;
// QTextStream qts(&text);

 QStringList words = current_search_word_list_.mid(low, high - low + 1);
 if(flip_count_)
 {
  QString w = words.takeLast();
  words.prepend(w);
 }

 text = words.join(" ");

 search_text_line_edit_->setText(text);
 search_text_line_edit_->setEnabled(true);
}


void Index_Entry_Review_Dialog::reset_search_word_list(QStringList words)
{
 current_search_word_list_ = words;

 if(words.isEmpty())
 {
  current_search_word_list_low_ = 0;
  current_search_word_list_high_ = 0;
  available_search_word_list_count_ = 0;
  search_text_line_edit_->setText("");
  search_text_line_edit_->setEnabled(false);
  return;
 }

 current_search_word_list_low_ = 1;
 current_search_word_list_high_ = 1;
 available_search_word_list_count_ = words.size();

// if(available_search_word_list_count_ > 1)
//   slurp_count_ = available_search_word_list_count_;
// else
//   slurp_count_ = 0;

 reset_search_word_list();
}

void Index_Entry_Review_Dialog::search_words_take_visible_first()
{
 if(flip_count_)
 {
  current_search_word_list_low_ = flip_count_;
  current_search_word_list_high_ = flip_count_;

  flip_count_ = 0;

  reset_search_word_list();
  check_nav_buttons();
 }
 else
   search_words_reset();
}



void Index_Entry_Review_Dialog::search_words_reset()
{
 flip_count_ = 0;
 current_search_word_list_low_ = 1;
 current_search_word_list_high_ = 1;

 reset_search_word_list();
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::search_words_slurp()
{
 flip_count_ = 0;
 current_search_word_list_low_ = 1;
 if(slurp_count_)
 {
  slurp_count_ = 0;
  current_search_word_list_high_ = 1;
 }
 else
 {
  slurp_count_ = current_search_word_list_high_;
  current_search_word_list_high_ = available_search_word_list_count_;
 }
 reset_search_word_list();
 check_nav_buttons();
}


void Index_Entry_Review_Dialog::search_words_flip()
{
 if(flip_count_)
   flip_count_ = 0;
 else
  flip_count_ = current_search_word_list_high_ - current_search_word_list_low_ + 1;

// QString f = current_search_word_list_.takeLast();
// current_search_word_list_.prepend(f);

 reset_search_word_list();
 //check_nav_buttons();
}


void Index_Entry_Review_Dialog::search_words_inc_high()
{
 ++current_search_word_list_high_;
 reset_search_word_list();
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::search_words_dec_high()
{
 --current_search_word_list_high_;

 if(current_search_word_list_high_ < current_search_word_list_low_)
   --current_search_word_list_low_;

 reset_search_word_list();
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::search_words_inc_low()
{
 ++current_search_word_list_low_;

 if(current_search_word_list_high_ < current_search_word_list_low_)
   ++current_search_word_list_high_;

 reset_search_word_list();
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::search_words_dec_low()
{
 --current_search_word_list_low_;
 reset_search_word_list();
 check_nav_buttons();
}


void Index_Entry_Review_Dialog::reset_toggle_html()
{
 if(current_phtml_.isEmpty()) // means plain
 {

 }
 else
 {
  current_phtml_.clear();
  html_preview_text_edit_->setPlainText(saved_phtml_);
  html_preview_supplement_text_edit_->setPlainText(saved_shtml_);
 }
}


void Index_Entry_Review_Dialog::toggle_html()
{
 if(current_phtml_.isEmpty()) // means plain
 {
  QString ptext = html_preview_text_edit_->toPlainText();
  QString stext = html_preview_supplement_text_edit_->toPlainText();

  saved_phtml_ = ptext;
  saved_shtml_ = stext;

  html_preview_text_edit_->setHtml(ptext);
  html_preview_supplement_text_edit_->setHtml(stext);

  current_phtml_ = html_preview_text_edit_->toHtml();
 }
 else
 {
  current_phtml_.clear();
  html_preview_text_edit_->setPlainText(saved_phtml_);
  html_preview_supplement_text_edit_->setPlainText(saved_shtml_);
 }
}

QString Index_Entry_Review_Dialog::get_preview_html()
{
 return html_preview_text_edit_->toPlainText();
}

QString Index_Entry_Review_Dialog::get_supplement_html()
{
 return html_preview_supplement_text_edit_->toPlainText();
}

void Index_Entry_Review_Dialog::supplement_italicize()
{
 QString text = get_supplement_html();

 //QString ital = "See Also";

 auto italicize = [&text](QString ital) -> bool
 {
  int index = text.indexOf(ital);
  if(index != -1)
  {
   text.insert(index + ital.size(), "</i>");
   text.insert(index, "<i>");
   return true;
  }
  return false;
 };

 italicize("See Also") || italicize("See also") || italicize("See");

 html_preview_supplement_text_edit_->setPlainText(text);
}


void Index_Entry_Review_Dialog::update_generated_htmls()
{
 if(current_entry_id_)
 {
  generated_htmls_[current_entry_id_] =
    QStringList{get_preview_html(), get_supplement_html()};
 }
}


void Index_Entry_Review_Dialog::reset_current_entry_update_text()
{
 earlier_match_code_edit_line_edit_
   ->setText(entry_update_map_.value(current_entry_key_).manual_update);
}


void Index_Entry_Review_Dialog::reset_current_entry_check_boxes()
{
 QVector<QCheckBox*> all = {active_earlier_match_code_exclude_check_box_,
   active_earlier_match_code_confirmed_check_box_,
   detach_page_number_check_box_,
   active_earlier_match_manual_update_check_box_,
   earlier_match_bookmarked_check_box_};

 for(QCheckBox* qcb : all)
 {
  qcb->blockSignals(true);
 }

 if(current_entry_key_.match_index)
 {
  active_earlier_match_code_exclude_check_box_->setChecked(entry_update_is_Excluded());
  active_earlier_match_code_confirmed_check_box_->setChecked(entry_update_is_Confirmed());
  detach_page_number_check_box_->setChecked(entry_update_is_Detach_Page_Number());
  active_earlier_match_manual_update_check_box_->setChecked(entry_update_is_Manually_Edited());
  earlier_match_bookmarked_check_box_->setChecked(entry_update_is_Bookmarked());
  for(QCheckBox* qcb : all)
  {
   qcb->setEnabled(true);
  }
 }
 else
 {
  for(QCheckBox* qcb : all)
  {
   qcb->setChecked(false);
   qcb->setEnabled(false);
  }
 }

 for(QCheckBox* qcb : all)
 {
  qcb->blockSignals(false);
 }

}


void Index_Entry_Review_Dialog::check_update_entry_update_map()
{
 if(!entry_update_map_.contains(current_entry_key_))
 {
  entry_update_map_[current_entry_key_]
    = Entry_Update_Value{Entry_Update_Status::N_A, 0};
 }
 //?else if(entry_update_map_[current_entry_key_].)
}



void Index_Entry_Review_Dialog::reset_current_entry_key(Index_Entry& ie,
  const s2* const maybe_match_index)
{
 if(maybe_match_index)
   current_entry_key_ = {ie.id, *maybe_match_index};
 else if(ie.refs.size())
   current_entry_key_ = {ie.id, 1};
 else
   current_entry_key_ = {ie.id, 0};
}


void Index_Entry_Review_Dialog::load_entry(u2 id, const s2* const maybe_match_index)
{
 check_entry_value_manual_update();

 update_generated_htmls();

 clear_confirms_list_widget();

 current_entry_id_ = id;

 flip_count_ = 0;
 slurp_count_ = 0;

 Index_Entry& ie = index_entries_[id - 1];

 reset_current_entry_key(ie, maybe_match_index);
 check_update_entry_update_map();
 check_for_bookmarks();
 reset_current_entry_check_boxes();
 reset_current_entry_update_text();

 if(!ie.supplement.isEmpty())
   html_preview_supplement_text_edit_->setText(ie.supplement);
 else if(!ie.carried.isEmpty())
   html_preview_supplement_text_edit_->setText(ie.carried);
 else
   html_preview_supplement_text_edit_->clear();

 supplement_italicize();



 html_preview_text_edit_->clear();

 current_index_entry_ = &ie;


 heading_line_edit_->setText(ie.key);
 heading_line_edit_->setCursorPosition(0);

 QStringList qre_matches;

 QRegularExpression qre("([\\w]'(?!')|[\\w-])+");
 QRegularExpressionMatchIterator it = qre.globalMatch(ie.key);
 while(it.hasNext())
 {
  QRegularExpressionMatch match = it.next();
  qre_matches.push_back(match.captured());
 }
 reset_search_word_list(qre_matches);

// if(match.hasMatch())
//   search_text_line_edit_->setText(match.captured());
// else
//   search_text_line_edit_->setText(ie.key);

// search_text_line_edit_->setEnabled(true);

 if(ie.parent_id)
 {
  parent_heading_line_edit_->setText(index_entries_[ie.parent_id - 1].key);
  parent_heading_line_edit_->setCursorPosition(0);
  parent_heading_line_edit_->setEnabled(true);
 }
 else
 {
  parent_heading_line_edit_->setPlaceholderText("N/A");
  parent_heading_line_edit_->setEnabled(false);
 }


// u2 id = ie.id;
 if(id)
 {
  entry_id_line_edit_->setText(QString::number(id));
  entry_id_line_edit_->setEnabled(true);
 }
 else
 {
  entry_id_line_edit_->setPlaceholderText("N/A");
  entry_id_line_edit_->setEnabled(false);
 }



 u2 number_of_match_components = ie.refs.size();
 if(number_of_match_components)
 {
  number_of_match_components_line_edit_->setText(QString::number(number_of_match_components));
  number_of_match_components_line_edit_->setEnabled(true);
 }
 else
 {
  number_of_match_components_line_edit_->setPlaceholderText("N/A");
  number_of_match_components_line_edit_->setEnabled(false);
 }

 earlier_match_codes_.clear();

 QString match_codes_text;

 if(number_of_match_components)
 {
  ref_pairs_to_string_list(ie.refs, earlier_match_codes_);
  match_codes_text = match_code_display(earlier_match_codes_);
 }
 else
 {
  match_codes_text_edit_->setText("");
  match_codes_text_edit_->setEnabled(false);

  earlier_match_code_edit_line_edit_->setText("");
  earlier_match_code_edit_line_edit_->setEnabled(false);

  active_earlier_match_code_line_edit_->setText("");
  active_earlier_match_code_line_edit_->setEnabled(false);

 }

 max_earlier_match_code_index_ = earlier_match_codes_.size();
 active_earlier_match_code_index_ = (bool)max_earlier_match_code_index_;



 if(match_codes_text.isEmpty())
 {
  match_codes_text_edit_->setPlaceholderText("N/A");
  match_codes_text_edit_->setEnabled(false);
 }
 else
 {
  reset_active_earlier_match_code();

  match_codes_text_edit_->setText(match_codes_text);
  match_codes_text_edit_->setEnabled(true);

//  earlier_match_code_update_line_edit_->setText(match_codes_text);

//  match_codes_label_->setText(match_codes_text);
//  match_codes_label_->setEnabled(true);
 }


 u2 count_in_parent = ie.count_in_parent;
 if(count_in_parent)
 {
  count_in_parent_line_edit_->setText(QString::number(count_in_parent));
  count_in_parent_line_edit_->setEnabled(true);
 }
 else
 {
  count_in_parent_line_edit_->setPlaceholderText("N/A");
  count_in_parent_line_edit_->setEnabled(false);
 }

 u2 subheading_count = ie.sub_count;
 if(subheading_count)
 {
  subheading_count_line_edit_->setText(QString::number(subheading_count));
  subheading_count_line_edit_->setEnabled(true);
 }
 else
 {
  subheading_count_line_edit_->setPlaceholderText("N/A");
  subheading_count_line_edit_->setEnabled(false);
 }

 check_nav_buttons();

 check_earlier_highlight();
}

u2 roman_to_u2(QString roman)
{
 roman = roman.toLower();
 u2 result = 0;


 if(roman.contains("xl"))
   result += 40;
 else
 {
  if(roman.contains("l"))
   result += 50;

  if(roman.contains("xxx"))
    result += 30;
  else if(roman.contains("xx"))
    result += 20;
  else if(roman.contains("x"))
    result += 10;
 }

 if(roman.contains("iv"))
   result += 4;
 else
 {
  if(roman.contains("v"))
    result += 5;

  if(roman.contains("iii"))
    result += 3;
  else if(roman.contains("ii"))
    result += 2;
  else if(roman.contains("i"))
    result += 1;
 }

 return result;
}

u2 Index_Entry_Review_Dialog::ref_code_to_earlier_page_number(const Page_Ref& page_ref)
{
 if(page_ref.number)
   return page_ref.number + 24;

 return roman_to_u2(page_ref.roman);
}

u2 Index_Entry_Review_Dialog::ref_code_to_later_page_number(const Page_Ref& page_ref)
{
 if(page_ref.number)
   return page_ref.number + 12;

 return roman_to_u2(page_ref.roman);
}


void Index_Entry_Review_Dialog::load_earlier_matches()
{
 QString text = KA::TextIO::load_file(earlier_match_file_);
 read_index_entries(text, index_entries_);
 max_entry_id_ = index_entries_.size();
 load_entry(1);
 entry_index_range_ = {1, 1};
 reset_file_entries_text();
}

void Index_Entry_Review_Dialog::add_current_match_line()
{
 u1 rc = current_matches_grid_layout_->rowCount();

 QLineEdit* cn = new QLineEdit(this);
 QComboBox* cy = new QComboBox(this);

 for(u2 y = 2010; y <= 2023; ++y)
 {
  cy->addItem(QString::number(y));
 }

 current_matches_grid_layout_->addWidget(cn, rc, 0);
 current_matches_grid_layout_->addWidget(cy, rc, 1);

}

void Index_Entry_Review_Dialog::create_par_code_mapping(QString review_file)
{
 QFile outfile(review_file);
 if (!outfile.open(QIODevice::WriteOnly))
   return;

 QTextStream qts(&outfile);

 u2 last_map_page = 1;
 u2 max_map_page = 411;

 for(const QPair<QStringList, QVector<Index_Ref_Summary>>& pr : *review_vector_)
 {
  QString para = pr.first.last();

  if(par_map_.contains(para))
    continue;

  QVector<Index_Ref_Summary> irss = pr.second;

  u2 low_page = 999;
  for(Index_Ref_Summary irs : irss)
  {
   u2 pn = irs.first_page_string_to_number();
   if(irs.first_page_string.startsWith("p. "))
     pn += 86;

   if(pn < low_page)
     low_page = pn;
  }

  u2 found_page = 0;

  if(para == "C3P26")
  {
   found_page = 27;
   last_map_page = 27;

   par_map_[para] = {low_page, found_page};
  }

  else
  {
   for(u2 n = last_map_page; n <= max_map_page; ++n)
   {
    QString et = earlier_pdf_dialog_->get_page_text(n - 1);
    if(et.contains(para))
    {
     par_map_[para] = {low_page, n};

     if(pr.first.size() == 1)
       qts << para << " => " << low_page << " -> " << n << "\n";

     else
       qts << para << " (" << pr.first.first() << ") => " << low_page << " -> " << n << "\n";

     last_map_page = n;
     found_page = n;
     break;
    }
   }
  }

  if(!found_page)
  {
   if(pr.first.size() == 1)
     qts << para << " => " << low_page << " ??\n";

   else
     qts << para << " (" << pr.first.first() << ") => " << low_page << "  ??\n";
  }


 }

}


void Index_Entry_Review_Dialog::check_review_vector(QString review_file, QString page_file,
  QString freview_file, QString fpage_file)
{
 QFile outfile(review_file);
 if (!outfile.open(QIODevice::WriteOnly))
   return;

 QTextStream qts(&outfile);


 QFile foutfile(freview_file);
 if (!foutfile.open(QIODevice::WriteOnly))
   return;

 QTextStream fqts(&foutfile);


 QString pre;

 u2 ix = 0;

 for(const QPair<QStringList, QVector<Index_Ref_Summary>>& pr : *review_vector_)
 {
  u2 offset = 86;

  if(pr.first.size() > 1)
    offset = 0;

  ++ix;

//  if(ix > 1)
//    break;

  qts << "\n\n" << pre << pr.first.first();
  if(pr.first.size() > 1)
    qts << " [" << pr.first[1] << "]";
  qts << "\n";

  QString l = pr.first.last();
  QPair<u2, u2> old_new = par_map_[l];

  fqts << "\n\n" << pre << pr.first.first();
  if(pr.first.size() > 1)
    fqts << " [" << pr.first[1] << "]";
  fqts << "\n";

  QMap<u2, QStringList> ffound;
  QMap<u2, QStringList> fdfound;
  QVector<u2> funfound;

  QMap<u2, QStringList> fwords;
  QMap<u2, QString> note_low;

  u2 fpage = old_new.second;
  fqts << pre << " page " << fpage
    << " (" << old_new.first << ") " << " ->\n";

  for(const Index_Ref_Summary& irs : pr.second)
  {
   if(irs.note_low)
     continue;

   QString ftext = earlier_pdf_dialog_->get_page_text(fpage - 1);
   QString fdtext = earlier_pdf_dialog_->get_page_text(fpage);

   KA::TextIO::save_file(fpage_file, ftext + "\n\n=======\n\n" + fdtext);

   ftext = ftext.toLower();
   fdtext = fdtext.toLower();

   QStringList words = irs.heading_to_words();

   fwords[irs.entry_id] = words;

   if(irs.note_low)
     note_low[irs.entry_id] = "[%1]"_qt.arg(irs.note_low);

   for(QString word : words)
   {
    if(word.size() < 4)
      continue;

    if(ftext.contains(word.toLower()))
      ffound[irs.entry_id].push_back(word);

    else
      if(fdtext.contains(word.toLower()))
        fdfound[irs.entry_id].push_back(word);
   }

   if( !(ffound.contains(irs.entry_id)) && !(fdfound.contains(irs.entry_id)) )
     funfound.push_back(irs.entry_id);
  }

  QMap<u2, QVector<Index_Ref_Summary>> m;
  Index_Ref_Summary::split(pr.second, m);

  QList<u2> ks = m.keys();
  std::sort(ks.begin(), ks.end());

  for(u2 page : ks)
  {
   page += offset;

   if(page >= 414)
     continue;

   qts << pre << " page " << page << " ->\n";

   QString text = later_pdf_dialog_->get_page_text(page - 1);


   KA::TextIO::save_file(page_file, text);

   text = text.toLower();

   for(const Index_Ref_Summary& irs : pr.second)
   {
    u2 pn = irs.first_page_string_to_number();

//    if(pn == 0)
//      qDebug() << "\n ------ 0 ------- \n";

    if(pn + offset != page)
      continue;

    QStringList words = irs.heading_to_words();

    qts << pre << " {" << irs.entry_id << "} \"" << words.join("-") << "\" ";

    if(irs.note_low)
      qts << "[" << irs.note_low << "]";

    QStringList found;

    for(QString word : words)
    {
     if(word.size() < 4)
       continue;

     if(text.contains(word.toLower()))
       found.push_back(word);
    }

    if(found.isEmpty())
    {
     if(irs.note_low)
       qts << ".[?]\n";

     else
       qts << " ..?? \n";
    }
    else
      qts << found.join(";") << "\n";
   }
  }

  QSet<u2> fk = ffound.keys().toSet();
  fk.unite(fdfound.keys().toSet());

  QVector<u2> fks = fk.toList().toVector();
  fks.append(funfound);

  std::sort(fks.begin(), fks.end());

  for(u2 uk : fks)
  {
   fqts << pre << " {" << uk << "} \"" << fwords[uk].join("-") << "\" ";
   fqts << note_low.value(uk);

   if(funfound.contains(uk))
     fqts << " ..??\n";

   else if(ffound.contains(uk))
     fqts << ffound[uk].join(";") << "\n";

   else if(fdfound.contains(uk))
     fqts << "+" << fdfound[uk].join(";") << "\n";
  }

 }

 outfile.close();
 foutfile.close();
}


void Index_Entry_Review_Dialog::make_review_file(QString review_file)
{
 QFile outfile(review_file);
 if (!outfile.open(QIODevice::WriteOnly))
   return;

 QTextStream qts(&outfile);
 QString pre = "    ";

 for(const QPair<QStringList, QVector<Index_Ref_Summary>>& pr : *review_vector_)
 {
  qts << "\n\n" << pre << pr.first.first();
  if(pr.first.size() > 1)
    qts << " [" << pr.first[1] << "]";
  qts << "\n";

  QMap<u2, QVector<Index_Ref_Summary>> m;
  Index_Ref_Summary::split(pr.second, m);

  QList<u2> ks = m.keys();
  std::sort(ks.begin(), ks.end());

  u2 last_page = 0;

  for(u2 page : ks)
  {
   if(last_page)
   {
    if(page - last_page > 1)
    {
     if(page < 328)
       qDebug() << "Page? " << page << " (" << pr.first << ")";
    }
   }

   for(Index_Ref_Summary& irs : m[page])
   {
    QStringList qsl = pr.first;
    auto pr1 = par_map_.value(pr.first.last());
    irs.to_string(qts, pre, QString::number(par_map_[pr.first.last()].second));
   }
   qts << pre << "=====\n";

   last_page = page;
  }
 }

}


void Index_Entry_Review_Dialog::filter_ref_groups()
{
 static u2 new_terms_threshold = 429;

 for(const Index_Ref_Group& irg : *ref_groups_)
 {
  bool _Range = false, _Missing = irg.index_refs.isEmpty() && irg.type == "e",
    _Roman = false, _New_Terms = irg.entry_id >= new_terms_threshold;

  for(const Index_Ref& ir : irg.index_refs)
  {
   _Range = _Range || ir.high;
   _Roman = _Roman || ir.region_code == 1;
  }
  if(_Range)
  {
   ref_groups_filtered_Range_.push_back(const_cast<Index_Ref_Group*>(&irg));
   ref_groups_filtered_[Nav_Filters::Range].push_back(irg.entry_id);
  }
  if(_Roman)
  {
   ref_groups_filtered_Roman_.push_back(const_cast<Index_Ref_Group*>(&irg));
   ref_groups_filtered_[Nav_Filters::Roman].push_back(irg.entry_id);
  }
  if(_Missing)
  {
   ref_groups_filtered_Missing_.push_back(const_cast<Index_Ref_Group*>(&irg));
   ref_groups_filtered_[Nav_Filters::Missing].push_back(irg.entry_id);
  }
  if(_New_Terms)
  {
   ref_groups_filtered_New_Terms_.push_back(const_cast<Index_Ref_Group*>(&irg));
   ref_groups_filtered_[Nav_Filters::New_Terms].push_back(irg.entry_id);
  }
 }
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


Index_Entry_Review_Dialog::~Index_Entry_Review_Dialog()
{

}

void Index_Entry_Review_Dialog::cancel()
{
// Q_EMIT(rejected());
// Q_EMIT(canceled(this));
// Q_EMIT(rejected());
 close();
}

void Index_Entry_Review_Dialog::accept()
{
// Q_EMIT(accepted(this));
}
