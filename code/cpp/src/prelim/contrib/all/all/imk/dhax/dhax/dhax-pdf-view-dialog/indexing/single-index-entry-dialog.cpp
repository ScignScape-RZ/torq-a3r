
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

//#ifdef HIDE

#include "single-index-entry-dialog.h".h"

#include "styles.h"


#include "add-minimize-frame.h"

#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QDateTime>

#include <QScrollBar>

//USING_KANS(MPF)



template<typename WIDGET_Type>
inline void make_index_entry_forward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21E2);
// QString unicode = QString(QChar(0x21E2));
// w->setText(unicode);
 w->setMaximumWidth(19);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_index_entry_backward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x21E0);
// QString unicode = QString(QChar(0x21E0));
// w->setText(unicode);
 w->setMaximumWidth(19);
 w->setMaximumHeight(15);
}


template<typename WIDGET_Type>
inline void make_index_entry_fforward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x23e9);
// QString unicode = QString(QChar(0x21E2));
// w->setText(unicode);
 w->setMaximumWidth(19);
 w->setMaximumHeight(15);
}

template<typename WIDGET_Type>
inline void make_index_entry_bbackward_button(WIDGET_Type* w)
{
 make_unicode_text(w, 0x23ea);
// QString unicode = QString(QChar(0x21E0));
// w->setText(unicode);
 w->setMaximumWidth(19);
 w->setMaximumHeight(15);
}

inline void style_nav_button(QPushButton* btn)
{
 btn->setStyleSheet(mid_tight_button_style_sheet_());
 btn->setMaximumHeight(21);
 btn->setMaximumWidth(53);
}


Single_Index_Entry_Dialog::Single_Index_Entry_Dialog(Index_Entry_Info* info)
{
 setWindowTitle("Single Index Entry");

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");
 button_save_ = new QPushButton("Save");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_ok_->setDefault(true);

 button_ok_->setStyleSheet(colorful_toggle_button_mixed_style_sheet_());

// button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());
 button_save_->setStyleSheet(basic_button_style_sheet_());

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_save_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout;

 main_tab_widget_ = new QTabWidget(this);

 QString styles = quiet_tab_style_sheet_();

// QString line_clr = "rgb(197, 212, 217)";
// QString normal_bkg = "rgb(237, 232, 237)";
// QString back_bkg = "rgb(207, 217, 219)"; // "rgb(197, 212, 217)";
// QString mid_bkg = "rgb(207, 217, 219)";

//// styles.append(group_box_style_sheet_().arg(normal_bkg).arg(mid_bkg).arg(line_clr));

// styles.append(QString(
//   "QFrame {background-color: %1;}\n"
//   "QLabel {background-color: %2;}\n").arg(back_bkg).arg(normal_bkg)
// );

 main_tab_widget_->setStyleSheet(styles);

 basic_info_frame_ = new QFrame(this);

 basic_info_group_box_ = new QGroupBox("Plugin Origin", basic_info_frame_);

 basic_info_layout_ = new QVBoxLayout;

 basic_form_layout_ = new QFormLayout;

 le_entry_heading_ = new QLineEdit(basic_info_frame_);
 le_entry_heading_->setPlaceholderText("(entry label as it appears in the printed index)");

 le_entry_code_ = new QLineEdit(basic_info_frame_);
 le_entry_code_->setPlaceholderText("(unique numeric code)");

 le_entry_number_ = new QLineEdit(basic_info_frame_);
 le_entry_number_->setToolTip("Number, in alphabetized index");

 basic_form_layout_->addRow("Heading:", le_entry_heading_);
 basic_form_layout_->addRow("Code:", le_entry_code_);

 entry_number_layout_ = new QHBoxLayout;
 entry_number_layout_->addWidget(new QLabel("#"));
 entry_number_layout_->addWidget(le_entry_number_);
 le_entry_number_->setMaximumWidth(40);

 btn_view_entry_list_ = new QPushButton("view list", basic_info_frame_);
 btn_view_entry_list_->setStyleSheet(colorful_small_button_style_sheet_alt_());

 btn_view_entry_list_->setMaximumWidth(65);

 entry_number_layout_->addWidget(btn_view_entry_list_);
 entry_number_layout_->addStretch();

 btn_deactivate_entry_ = new QPushButton("deactivate", basic_info_frame_);
 btn_deactivate_entry_->setStyleSheet(basic_button_style_sheet_());
 entry_number_layout_->addWidget(btn_deactivate_entry_);

 basic_form_layout_->addRow("Context:", entry_number_layout_);

 fr_entry_type_ = new QFrame(basic_info_frame_);
 fr_entry_type_layout_ = new QHBoxLayout(fr_entry_type_);

 fr_entry_type_->setFrameStyle(QFrame::Panel | QFrame::Sunken);


 ckb_entry_type_top_level_ = new QCheckBox("Top-level", fr_entry_type_);
 ckb_entry_type_redirect_ = new QCheckBox("Redirect", fr_entry_type_);
 ckb_entry_type_subheadings_ = new QCheckBox("Subheadings", fr_entry_type_);

 fr_entry_type_layout_->addWidget(ckb_entry_type_top_level_);
 fr_entry_type_layout_->addWidget(ckb_entry_type_redirect_);
 fr_entry_type_layout_->addWidget(ckb_entry_type_subheadings_);

// entry_type_layout_->addWidget(fr_entry_type_);


 // can_layout_->addWidget(can_send_ckb_);
 // can_layout_->addWidget(can_receive_ckb_);
 // can_layout_->addWidget(can_launch_ckb_);


// plugin_active_ckb_ = new QCheckBox("Active", basic_info_frame_);
// plugin_active_ckb_->setChecked(true);
// plugin_active_layout_->addWidget(plugin_active_ckb_);
// plugin_active_button_ = new QPushButton("Deactivate", basic_info_frame_);
// plugin_active_button_->setStyleSheet(colorful_small_button_style_sheet_());
// plugin_active_layout_->addWidget(plugin_active_button_);
// plugin_active_layout_->addStretch();

 basic_form_layout_->addRow("Type:", fr_entry_type_);

 basic_info_group_box_->setLayout(basic_form_layout_);
 basic_info_layout_->addWidget(basic_info_group_box_);

// can_group_box_ = new QGroupBox("Plugin Can", basic_info_frame_);
// can_layout_ = new QHBoxLayout;
// can_send_ckb_ = new QCheckBox("Send Requests", basic_info_frame_);
// can_receive_ckb_ = new QCheckBox("Receive Requests", basic_info_frame_);
// can_launch_ckb_ = new QCheckBox("Launch Applications", basic_info_frame_);
// can_send_ckb_->setChecked(true);
// can_receive_ckb_->setChecked(true);
// can_launch_ckb_->setChecked(true);

// can_layout_->addWidget(can_send_ckb_);
// can_layout_->addWidget(can_receive_ckb_);
// can_layout_->addWidget(can_launch_ckb_);

// can_group_box_->setLayout(can_layout_);
// basic_info_layout_->addWidget(can_group_box_);




 parent_entry_group_box_ = new QGroupBox("Parent Entry", basic_info_frame_);
 parent_entry_layout_ = new QVBoxLayout(parent_entry_group_box_);

 parent_entry_layout1_ = new QHBoxLayout;
 parent_entry_layout2_ = new QHBoxLayout;

 le_parent_entry_heading_ = new QLineEdit(basic_info_frame_);
 le_parent_entry_heading_->setPlaceholderText("(parent entry heading)");
 parent_entry_layout1_->addWidget(new QLabel("Heading"));
 parent_entry_layout1_->addWidget(le_parent_entry_heading_);

 le_parent_entry_code_ = new QLineEdit(basic_info_frame_);
 le_parent_entry_code_->setMaximumWidth(50);
 le_parent_entry_code_->setPlaceholderText("(code)");
 parent_entry_layout2_->addWidget(new QLabel("Id"));
 parent_entry_layout2_->addWidget(le_parent_entry_code_);


 le_parent_entry_number_ = new QLineEdit(basic_info_frame_);
 le_parent_entry_number_->setMaximumWidth(20);
 parent_entry_layout2_->addWidget(new QLabel("#"));
 parent_entry_layout2_->addWidget(le_parent_entry_number_);

 parent_entry_layout2_->addStretch();

 le_position_in_parent_ = new QLineEdit(basic_info_frame_);
 le_position_in_parent_->setMaximumWidth(20);
 parent_entry_layout2_->addWidget(new QLabel("Position in parent"));
 parent_entry_layout2_->addWidget(le_position_in_parent_);

 le_parent_count_ = new QLineEdit(basic_info_frame_);
 le_parent_count_->setMaximumWidth(20);
 parent_entry_layout2_->addWidget(new QLabel("of"));
 parent_entry_layout2_->addWidget(le_parent_count_);


 parent_entry_layout_->addLayout(parent_entry_layout1_);
 parent_entry_layout_->addLayout(parent_entry_layout2_);

 basic_info_layout_->addWidget(parent_entry_group_box_);



 subentries_group_box_ = new QGroupBox("Subentries", basic_info_frame_);
 subentries_scroll_area_ = new QScrollArea(basic_info_frame_);
 subentries_area_frame_ = new QFrame(basic_info_frame_);

 subentries_area_frame_->setFrameStyle(QFrame::Box | QFrame::Raised);

 subentries_layout_ = new QGridLayout(subentries_area_frame_);

 subentries_layout_->addWidget(new QLabel("Count", basic_info_frame_), 0, 0, 1, 2);

 subentries_count_ = new QLineEdit(basic_info_frame_);
 subentries_layout_->addWidget(subentries_count_, 0, 2);

 subentries_count_->setMaximumWidth(20);

 subentries_layout_->addWidget(new QLabel("(list shows id, then heading)",
   basic_info_frame_), 0, 3);

 subentries_layout_->setColumnStretch(4, 1);

 subentries_heading_list_ = QStringList {"test 1", "test 2", "test 3"};
 subentries_id_list_ = {144, 145, 503};

 subentries_pair_list_.resize(subentries_heading_list_.size());
 {
  int count = 0;
  for(QString qs : subentries_heading_list_)
  {
   subentries_pair_list_[count] = {
     new QLabel("   %1"_qt.arg(subentries_id_list_[count]), basic_info_frame_),
     new QLineEdit(qs, basic_info_frame_)
   };
   subentries_pair_list_[count].second->setPlaceholderText("(subheading)");

   subentries_layout_->addWidget(subentries_pair_list_[count].first, count + 1, 0);

   subentries_layout_->addWidget(subentries_pair_list_[count].second, count + 1, 1, 1, 4);

   subentries_pair_list_[count].second->setMinimumWidth(260);

   ++count;
  }
 }

 subentries_scroll_area_->setWidget(subentries_area_frame_);

// subentries_scroll_area_->setHorizontalScrollBarPolicy(Qt::No);
 subentries_scroll_area_->horizontalScrollBar()->setEnabled(false);

 subentries_group_box_layout_ = new QVBoxLayout;
 subentries_group_box_layout_->addWidget(subentries_scroll_area_);
 subentries_group_box_->setLayout(subentries_group_box_layout_);

 basic_info_layout_->addWidget(subentries_group_box_);


// basic_list_layout_->setColumnStretch(0, 1);
// basic_list_layout_->setColumnStretch(2, 1);






 preview_group_box_ = new QGroupBox("Preview", basic_info_frame_);
 preview_layout_ = new QGridLayout(preview_group_box_);

 lbl_preview_index_pdf_ = new QLabel("Index File (PDF)", basic_info_frame_);
 preview_layout_->addWidget(lbl_preview_index_pdf_, 0, 0);

 le_preview_index_pdf_ = new QLineEdit(basic_info_frame_);
 le_preview_index_pdf_->setPlaceholderText("(local file path)");
 preview_layout_->addWidget(le_preview_index_pdf_, 0, 1);

 btn_preview_index_pdf_browse_ = new QPushButton("browse", basic_info_frame_);
 btn_preview_index_pdf_browse_->setStyleSheet(colorful_toggle_button_style_sheet_());


 btn_preview_index_pdf_load_ = new QPushButton("load", basic_info_frame_);
 btn_preview_index_pdf_load_->setStyleSheet(colorful_toggle_button_style_sheet_());

 btn_preview_index_pdf_browse_->setMaximumWidth(48);
 btn_preview_index_pdf_load_->setMaximumWidth(38);

 preview_layout_->addWidget(btn_preview_index_pdf_browse_, 0, 2);
 preview_layout_->addWidget(btn_preview_index_pdf_load_, 0, 3);



 lbl_web_index_pdf_ = new QLabel("Web Index (HTML)", basic_info_frame_);
 preview_layout_->addWidget(lbl_web_index_pdf_, 1, 0);

 le_web_index_pdf_ = new QLineEdit(basic_info_frame_);
 le_web_index_pdf_->setPlaceholderText("(local file path)");
 preview_layout_->addWidget(le_web_index_pdf_, 1, 1);

 btn_web_index_pdf_browse_ = new QPushButton("browse", basic_info_frame_);
 btn_web_index_pdf_browse_->setStyleSheet(colorful_toggle_button_style_sheet_());


 btn_web_index_pdf_load_ = new QPushButton("load", basic_info_frame_);
 btn_web_index_pdf_load_->setStyleSheet(colorful_toggle_button_style_sheet_());


 btn_web_index_pdf_browse_->setMaximumWidth(48);
 btn_web_index_pdf_load_->setMaximumWidth(38);

 preview_layout_->addWidget(btn_web_index_pdf_browse_, 1, 2);
 preview_layout_->addWidget(btn_web_index_pdf_load_, 1, 3);



 lbl_book_pdf_ = new QLabel("Entire Book (PDF)", basic_info_frame_);
 preview_layout_->addWidget(lbl_book_pdf_, 2, 0);

 le_book_pdf_ = new QLineEdit(basic_info_frame_);
 le_book_pdf_->setPlaceholderText("(local file path)");
 preview_layout_->addWidget(le_book_pdf_, 2, 1);

 btn_book_pdf_browse_ = new QPushButton("browse", basic_info_frame_);
 btn_book_pdf_browse_->setStyleSheet(colorful_toggle_button_style_sheet_());


 btn_book_pdf_load_ = new QPushButton("load", basic_info_frame_);
 btn_book_pdf_load_->setStyleSheet(colorful_toggle_button_style_sheet_());


 btn_book_pdf_browse_->setMaximumWidth(48);
 btn_book_pdf_load_->setMaximumWidth(38);

 preview_layout_->addWidget(btn_book_pdf_browse_, 2, 2);
 preview_layout_->addWidget(btn_book_pdf_load_, 2, 3);





 basic_info_layout_->addWidget(preview_group_box_);

 basic_info_layout_->addStretch();

 basic_info_frame_->setLayout(basic_info_layout_);

 main_tab_widget_->addTab(basic_info_frame_, "Basic Info");

 request_info_frame_ = new QFrame(this);
 request_info_layout_ = new QVBoxLayout;

 QGroupBox* request_app_box_ = new QGroupBox("Application Info", request_info_frame_);

 request_app_layout_ = new QFormLayout;

 request_app_layout_->addRow("Source Application Name: ", new QLabel("XpdfReader", request_info_frame_));
 request_app_layout_->addRow("Source Application Path: ", new QLabel("/home/.../xpdf-console", request_info_frame_));
 request_app_layout_->addRow("Target Application Name: ", new QLabel("IQmol", request_info_frame_));
 request_app_layout_->addRow("Target Application Path: ", new QLabel("/home/.../IQmol", request_info_frame_));

 request_app_box_->setLayout(request_app_layout_);
 request_info_layout_->addWidget(request_app_box_);


 QGroupBox* request_form_box_ = new QGroupBox("Request Info", request_info_frame_);
 request_form_layout_ = new QFormLayout;

 request_form_layout_->addRow("Request Resource Description: ", new QLabel("Lactose (3D View)", request_info_frame_));

 request_form_layout_->addRow("Request Resource Type: ", new QLabel("Molecular Data File", request_info_frame_));

 request_form_layout_->addRow("Request Resource File: ", new QLabel("14641-93-1.mol", request_info_frame_));

 request_detail_layout_ = new QHBoxLayout;
 request_detail_layout_->addWidget(new QLabel("NTXH", request_info_frame_));
 request_detail_button_ = new QPushButton("View Request Details", request_info_frame_);
 request_detail_button_->setStyleSheet(colorful_small_button_style_sheet_());
 request_detail_layout_->addWidget(request_detail_button_);
 request_detail_layout_->addStretch();

 request_form_layout_->addRow("Request Format: ", request_detail_layout_);
 request_form_box_->setLayout(request_form_layout_);

 request_info_layout_->addWidget(request_form_box_);

 launch_form_box_ = new QGroupBox("Launch Info", request_info_frame_);
 launch_form_layout_ = new QFormLayout;

 launch_form_layout_->addRow("TimeStamp: ", new QLabel(QDateTime::currentDateTime().toString(), request_info_frame_));

 launch_form_layout_->addRow("Launch/Request Info: ", new QLabel("Not Applicable", request_info_frame_));

 launch_form_box_->setLayout(launch_form_layout_);

 request_info_layout_->addWidget(launch_form_box_);

 request_info_frame_->setLayout(request_info_layout_);

 main_tab_widget_->addTab(request_info_frame_, "Locators");

 main_tab_widget_->addTab(new QFrame(), "Meta-Index");
 main_tab_widget_->addTab(new QFrame(), "History/Versioning");
 main_tab_widget_->addTab(new QFrame(), "Cloud Services");

 main_layout_->addWidget(main_tab_widget_);

 nav_layout_ = new QHBoxLayout;

 btn_forward_ = new QPushButton("->", basic_info_frame_);
 btn_back_ = new QPushButton("<-", basic_info_frame_);
 btn_forward_to_end_  = new QPushButton("=>", basic_info_frame_);
 btn_back_to_start_ = new QPushButton("<=", basic_info_frame_);

 btn_forward_->setMaximumWidth(20);
 btn_forward_to_end_->setMaximumWidth(30);
 btn_back_->setMaximumWidth(20);
 btn_back_to_start_->setMaximumWidth(30);


 make_index_entry_fforward_button(btn_forward_to_end_);
 style_nav_button(btn_forward_to_end_);

 make_index_entry_forward_button(btn_forward_);
 style_nav_button(btn_forward_);

 make_index_entry_backward_button(btn_back_);
 style_nav_button(btn_back_);

 make_index_entry_bbackward_button(btn_back_to_start_);
 style_nav_button(btn_back_to_start_);



 nav_layout_->addWidget(btn_back_);
 nav_layout_->addWidget(btn_forward_);

 nav_layout_->addSpacing(10);

 nav_layout_->addWidget(btn_back_to_start_);
 nav_layout_->addWidget(btn_forward_to_end_);

 nav_layout_->addStretch();

 nav_layout_->addWidget(button_box_);

 main_layout_->addLayout(nav_layout_ );


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

 setLayout(main_layout_);
}

Single_Index_Entry_Dialog::~Single_Index_Entry_Dialog()
{

}

//#endif //def HIDE
