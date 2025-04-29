
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef SINGLE_INDEX_ENTRY_DIALOG__H
#define SINGLE_INDEX_ENTRY_DIALOG__H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QFrame>
#include <QTabWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QScrollArea>


#include "kans.h"


//KANS_(MPF)

class Index_Entry_Info;

class Single_Index_Entry_Dialog : public QDialog
{
 Q_OBJECT

 QHBoxLayout* nav_layout_;

 QPushButton* btn_forward_;
 QPushButton* btn_back_;
 QPushButton* btn_forward_to_end_;
 QPushButton* btn_back_to_start_;

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_save_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QFrame* basic_info_frame_;

 QFormLayout* basic_form_layout_;

 QLineEdit* le_entry_heading_;
 QLineEdit* le_entry_code_;
 QLineEdit* le_entry_number_;

 QVBoxLayout* basic_info_layout_;

 QGroupBox* basic_info_group_box_;


 QGroupBox* preview_group_box_;
 QGridLayout* preview_layout_;

 QLabel* lbl_preview_index_pdf_;
 QLineEdit* le_preview_index_pdf_;
 QPushButton* btn_preview_index_pdf_browse_;
 QPushButton* btn_preview_index_pdf_load_;


 QLabel* lbl_web_index_pdf_;
 QLineEdit* le_web_index_pdf_;
 QPushButton* btn_web_index_pdf_browse_;
 QPushButton* btn_web_index_pdf_load_;



 QLabel* lbl_book_pdf_;
 QLineEdit* le_book_pdf_;
 QPushButton* btn_book_pdf_browse_;
 QPushButton* btn_book_pdf_load_;


 QHBoxLayout* entry_number_layout_;

 QPushButton* btn_view_entry_list_;
 QPushButton* btn_deactivate_entry_;

 QHBoxLayout* fr_entry_type_layout_;

 QFrame* fr_entry_type_;

 QCheckBox* ckb_entry_type_top_level_;
 QCheckBox* ckb_entry_type_redirect_;
 QCheckBox* ckb_entry_type_subheadings_;



 QGroupBox* parent_entry_group_box_;
 QVBoxLayout* parent_entry_layout_;
 QHBoxLayout* parent_entry_layout1_;
 QHBoxLayout* parent_entry_layout2_;
 QLineEdit* le_parent_entry_heading_;
 QLineEdit* le_parent_entry_code_;
 QLineEdit* le_parent_entry_number_;
 QLineEdit* le_position_in_parent_;
 QLineEdit* le_parent_count_;



 QGroupBox* subentries_group_box_;
 QVBoxLayout* subentries_group_box_layout_;
 QFrame* subentries_area_frame_;
 QScrollArea* subentries_scroll_area_;
 QGridLayout* subentries_layout_;

 QStringList subentries_heading_list_;
 QVector<int> subentries_id_list_;

 QLineEdit* subentries_count_;
 QVector<QPair<QLabel*, QLineEdit*>> subentries_pair_list_;


// QHBoxLayout* can_layout_;
// QCheckBox* can_send_ckb_;
// QCheckBox* can_receive_ckb_;
// QCheckBox* can_launch_ckb_;
// QPushButton* plugin_active_button_;

// QGroupBox* can_group_box_;
// QHBoxLayout* can_layout_;
// QCheckBox* can_send_ckb_;
// QCheckBox* can_receive_ckb_;
// QCheckBox* can_launch_ckb_;

 QFrame* request_info_frame_;
 QVBoxLayout* request_info_layout_;

 QGroupBox* request_app_box_;
 QFormLayout* request_app_layout_;

 QGroupBox* request_form_box_;
 QFormLayout* request_form_layout_;

 QHBoxLayout* request_detail_layout_;
 QPushButton* request_detail_button_;

 QGroupBox* launch_form_box_;
 QFormLayout* launch_form_layout_;


 QTabWidget* main_tab_widget_;

 Index_Entry_Info* info_;


public:


 Single_Index_Entry_Dialog(Index_Entry_Info* info);

 ~Single_Index_Entry_Dialog();

Q_SIGNALS:


public Q_SLOTS:


};

//_KANS(MPF)

#endif // SINGLE_INDEX_ENTRY_DIALOG__H



