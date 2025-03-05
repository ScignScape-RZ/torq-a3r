
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



//?#include "case-map-gis-service.h"

Index_Entry_Review_Dialog::Index_Entry_Review_Dialog(QString earlier_match_file, QWidget* parent)
  : QDialog(parent), current_entry_id_(0), max_entry_id_(0), current_index_entry_(nullptr),
    active_earlier_match_code_index_(0), max_earlier_match_code_index_(0),
    earlier_match_file_(earlier_match_file),
    current_search_word_list_low_(0), available_search_word_list_count_(0),
    current_search_word_list_high_(0), flip_count_(0), slurp_count_(0),
    current_page_ref_pair_(Page_Ref_Pair::default_values())
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

 info_group_box_ = new QGroupBox("Entry Info", this);
 earlier_match_group_box_ = new QGroupBox("earlier Match", this);
 search_text_line_edit_ = new QLineEdit(this);
 search_text_line_edit_->setPlaceholderText("(derived by default from each earlier entry)");
 search_text_line_edit_->setEnabled(false);


 info_group_box_layout_ = new QVBoxLayout;



 earlier_match_group_box_layout_ = new QVBoxLayout;
 earlier_match_group_box_top_layout_ = new QFormLayout;
 earlier_match_group_box_left_layout_ = new QFormLayout;
 earlier_match_group_box_bottom_layout_ = new QHBoxLayout;
 earlier_match_group_box_right_layout_ = new QVBoxLayout;


 earlier_match_code_update_line_edit_ = new QLineEdit(this);
 active_earlier_match_code_line_edit_ = new QLineEdit(this);
 active_earlier_match_code_updated_check_box_ = new QCheckBox(this);


 match_codes_text_edit_ = new QTextEdit(this);
 match_codes_text_edit_->setPlaceholderText("N/A");
 match_codes_text_edit_->setEnabled(false);

 match_codes_text_edit_->setReadOnly(true);
 match_codes_text_edit_->setMaximumHeight(60);

 earlier_match_group_box_top_layout_->addRow("Match Codes", match_codes_text_edit_);

 earlier_match_group_box_layout_->addLayout(earlier_match_group_box_top_layout_);

 earlier_match_group_box_left_layout_->addRow("Active", active_earlier_match_code_line_edit_);
 earlier_match_group_box_left_layout_->addRow("Update", earlier_match_code_update_line_edit_);
 earlier_match_group_box_left_layout_->addRow("Updated", active_earlier_match_code_updated_check_box_);

// earlier_match_code_update_line_edit_->hide();
// active_earlier_match_code_line_edit_->hide();
// active_earlier_match_code_updated_check_box_->hide();

 earlier_match_group_box_bottom_layout_->addLayout(earlier_match_group_box_left_layout_);

 active_earlier_match_code_nav_layout_ = new QHBoxLayout;
 active_earlier_match_code_highlight_layout_ = new QHBoxLayout;

 active_earlier_match_code_forward_button_ = new QPushButton("=>");
 active_earlier_match_code_backward_button_ = new QPushButton("<=");

 earlier_highlight_button_ = new QPushButton("show");
 clear_earlier_highlights_button_ = new QPushButton("clear");
 search_update_button_ = new QPushButton("re-search");

 earlier_highlight_button_->setMaximumWidth(45);
 clear_earlier_highlights_button_->setMaximumWidth(45);

 active_earlier_match_code_nav_layout_->addStretch();
 active_earlier_match_code_nav_layout_->addWidget(active_earlier_match_code_backward_button_);
 active_earlier_match_code_nav_layout_->addWidget(active_earlier_match_code_forward_button_);
 active_earlier_match_code_nav_layout_->addStretch();

 earlier_match_group_box_right_layout_->addLayout(active_earlier_match_code_nav_layout_);

 active_earlier_match_code_highlight_layout_->addStretch();
 active_earlier_match_code_highlight_layout_->addWidget(earlier_highlight_button_);
 active_earlier_match_code_highlight_layout_->addWidget(clear_earlier_highlights_button_);
 active_earlier_match_code_highlight_layout_->addStretch();
 active_earlier_match_code_highlight_layout_->addWidget(search_update_button_);
 active_earlier_match_code_highlight_layout_->addStretch();

 earlier_match_group_box_right_layout_->addLayout(active_earlier_match_code_highlight_layout_);

 connect(search_update_button_, &QPushButton::clicked, [this]()
 {
  search_update();
 });

 connect(clear_earlier_highlights_button_, &QPushButton::clicked, [this]()
 {
  clear_earlier_highlights();
 });

 connect(earlier_highlight_button_, &QPushButton::clicked, [this]()
 {
  earlier_highlight();
 });

 connect(active_earlier_match_code_forward_button_, &QPushButton::clicked, [this]()
 {
  earlier_match_forward();
 });

 connect(active_earlier_match_code_backward_button_, &QPushButton::clicked, [this]()
 {
  earlier_match_backward();
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
 search_words_dec_high_button_ = new QPushButton("-");
 search_words_inc_low_button_ = new QPushButton(".+");
 search_words_dec_low_button_ = new QPushButton(".-");

 search_words_flip_button_ = new QPushButton("<->");
 search_words_slurp_button_ = new QPushButton("<@>");

 connect(search_words_slurp_button_, &QPushButton::clicked, [this]()
 {
  search_words_slurp();
 });

 connect(search_words_flip_button_, &QPushButton::clicked, [this]()
 {
  search_words_flip();
 });

 connect(search_words_inc_high_button_, &QPushButton::clicked, [this]()
 {
  search_words_inc_high();
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
 search_words_layout_->addWidget(search_words_dec_high_button_);
 search_words_layout_->addWidget(search_words_inc_high_button_);
 search_words_layout_->addStretch();
 search_words_layout_->addWidget(search_words_flip_button_);
 search_words_layout_->addWidget(search_words_slurp_button_);
 search_words_layout_->addStretch();
 search_words_layout_->addWidget(search_words_dec_low_button_);
 search_words_layout_->addWidget(search_words_inc_low_button_);

 search_words_dec_high_button_->setMaximumWidth(20);
 search_words_inc_high_button_->setMaximumWidth(20);

 search_words_dec_low_button_->setMaximumWidth(20);
 search_words_inc_low_button_->setMaximumWidth(20);

 search_words_flip_button_->setMaximumWidth(30);
 search_words_flip_button_->setMaximumHeight(20);

 search_words_slurp_button_->setMaximumWidth(30);
 search_words_slurp_button_->setMaximumHeight(20);

 current_matches_grid_layout_->addLayout(search_words_layout_, 0, 0, 1, 2);

 current_matches_grid_layout_->addWidget(new QLabel("Current Match:", this), 1, 0);
 current_matches_grid_layout_->addWidget(new QLabel("Status:", this), 1, 1);


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

 entry_forward_button_  = new QPushButton("->>", this);
 entry_backward_button_  = new QPushButton("<<-", this);

 connect(entry_forward_button_, &QPushButton::clicked, [this]()
 {
  entry_forward();
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

 bottom_layout_ = new QHBoxLayout;

 bottom_layout_->addWidget(entry_backward_button_);
 bottom_layout_->addWidget(entry_forward_button_);
 bottom_layout_->addStretch();
 bottom_layout_->addWidget(button_box_);

 main_layout_->addLayout(bottom_layout_);


 setLayout(main_layout_);

 setWindowTitle("Index Entry Dialog");

 load_earlier_matches();

}


void Index_Entry_Review_Dialog::search_update()
{
 u2 page_number = ref_code_to_earlier_page_number(current_page_ref_pair_.first);
 later_pdf_dialog_->search_update(search_text_line_edit_->text(),
   active_earlier_match_code_index_, page_number);

 setWindowState(Qt::WindowState::WindowNoState);

 later_pdf_dialog_->setWindowState(Qt::WindowState::WindowActive);
 later_pdf_dialog_->activateWindow();
}

void Index_Entry_Review_Dialog::clear_earlier_highlights()
{
 earlier_pdf_dialog_->clear_all_highlights();
}

void Index_Entry_Review_Dialog::earlier_highlight()
{
 u2 page_number = ref_code_to_earlier_page_number(current_page_ref_pair_.first);
 earlier_pdf_dialog_->load_page(page_number);

 setWindowState(Qt::WindowState::WindowNoState);

 earlier_pdf_dialog_->setWindowState(Qt::WindowState::WindowActive);
 earlier_pdf_dialog_->activateWindow();

 earlier_pdf_dialog_->highlight_match(search_text_line_edit_->text());

}


void Index_Entry_Review_Dialog::create_split_window(QString text1, QString text2)
{
 QSplitter* splitter = new QSplitter(this);
 QTextEdit* left_text = new QTextEdit(text1, splitter);
 QTextEdit* right_text = new QTextEdit(text2, splitter);
 splitter->addWidget(left_text);
 splitter->addWidget(right_text);

 QMainWindow* mw = new QMainWindow(this);
 main_layout_->addWidget(mw);

 QDockWidget* dw = new QDockWidget(mw);
 dw->setWidget(splitter);
 mw->addDockWidget(Qt::TopDockWidgetArea, dw);

}


void Index_Entry_Review_Dialog::confirm_match(int page_number)
{
 create_split_window("text1", "text2");
}


void Index_Entry_Review_Dialog::reclaim_focus()
{
 setWindowState(Qt::WindowState::WindowActive);
}


QString Index_Entry_Review_Dialog::match_code_long_display(const Page_Ref_Pair& pr)
{
 return pr.to_long_display();
}


void Index_Entry_Review_Dialog::entry_forward()
{
 if(current_entry_id_ < max_entry_id_)
   load_entry(current_entry_id_ + 1);
}

void Index_Entry_Review_Dialog::entry_backward()
{
 if(current_entry_id_ > 1)
   load_entry(current_entry_id_ - 1);
}


void Index_Entry_Review_Dialog::earlier_match_forward()
{
 ++active_earlier_match_code_index_;
 reset_active_earlier_match_code();
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::earlier_match_backward()
{
 --active_earlier_match_code_index_;
 reset_active_earlier_match_code();
 check_nav_buttons();
}

void Index_Entry_Review_Dialog::reset_active_earlier_match_code()
{
 current_page_ref_pair_ = earlier_match_codes_[active_earlier_match_code_index_ - 1].first;
 current_page_ref_string_ = earlier_match_codes_[active_earlier_match_code_index_ - 1].second;
 current_page_ref_long_display_ = match_code_long_display(current_page_ref_pair_);
 active_earlier_match_code_line_edit_->setText(current_page_ref_long_display_);

 earlier_match_code_update_line_edit_->setFocus();
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
 if(current_entry_id_ < 2)
   entry_backward_button_->setEnabled(false);
 else
   entry_backward_button_->setEnabled(true);

 if(current_entry_id_ < max_entry_id_)
   entry_forward_button_->setEnabled(true);
 else
   entry_forward_button_->setEnabled(false);


 if(active_earlier_match_code_index_ < 2)
   active_earlier_match_code_backward_button_->setEnabled(false);
 else
   active_earlier_match_code_backward_button_->setEnabled(true);

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


void Index_Entry_Review_Dialog::load_entry(u2 id)
{
 current_entry_id_ = id;

 flip_count_ = 0;
 slurp_count_ = 0;

 Index_Entry& ie = index_entries_[id - 1];


 heading_line_edit_->setText(ie.key);
 heading_line_edit_->setCursorPosition(0);

 QStringList qre_matches;

 QRegularExpression qre("\\w+");
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

  earlier_match_code_update_line_edit_->setText("");
  earlier_match_code_update_line_edit_->setEnabled(false);

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
}

u2 roman_to_u2(QString roman)
{
 roman = roman.toLower();
 u2 result = 0;

 if(roman.contains("lx"))
   result += 40;
 else if(roman.contains("xxx"))
  result += 30;
 else if(roman.contains("xx"))
  result += 20;
 else if(roman.contains("x"))
  result += 10;

 if(roman.contains("iv"))
   result += 4;
 else if(roman.contains("iii"))
  result += 3;
 else if(roman.contains("ii"))
  result += 2;
 else if(roman.contains("i"))
  result += 1;

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
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Index_Entry_Review_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
