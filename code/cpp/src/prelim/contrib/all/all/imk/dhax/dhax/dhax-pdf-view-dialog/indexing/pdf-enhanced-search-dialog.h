
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef PDF_ENHANCED_SEARCH_DIALOG__H
#define PDF_ENHANCED_SEARCH_DIALOG__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QTableWidget>

#include <functional>


class QCheckBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;
class QScrollArea;
class QGridLayout;
class QMediaPlayer;
class QProcess;
class QTcpServer;
class QGridLayout;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

class PDF_Enhanced_Search_Dialog : public QDialog
{

 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
// QPushButton* button_proceed_;

// QPushButton* button_do_map_;

 QHBoxLayout* bottom_layout_;

 QVBoxLayout* main_layout_;

 QVBoxLayout* entry_layout_;

 QGroupBox* info_group_box_;
 QGroupBox* sources_group_box_;
 QGroupBox* index_entry_group_box_;

 QGridLayout* info_group_box_layout_;


 QVBoxLayout* sources_group_box_layout_;
 QHBoxLayout* sources_group_box_top_layout_;
 QHBoxLayout* sources_group_box_bottom_layout_;
 QFormLayout* sources_group_box_left_layout_;
 QGridLayout* sources_group_box_right_layout_;

 QGridLayout* index_entry_group_box_layout_;

 QLabel* lbl_index_file_;
 QLineEdit* le_index_file_;
 QPushButton* btn_index_entry_data_;

 QLabel* lbl_index_entry_term_;
 QLineEdit* le_index_entry_term_;
 QLabel* lbl_index_entry_number_;
 QLineEdit* le_index_entry_number_;

 QLabel* lbl_parent_entry_term_;
 QLineEdit* le_parent_entry_term_;
 QLabel* lbl_parent_entry_number_;
 QLineEdit* le_parent_entry_number_;

// QFormLayout* index_entry_group_box_layout_top_;
// QGridLayout* index_entry_grid_layout_;

// QComboBox* cb_number_of_index_entry_;

 QLabel* lbl_local_file_;
 QLineEdit* le_local_file_;
 QPushButton* btn_local_file_browse_;

 QLineEdit* le_meta_index_;
 QComboBox* cbb_access_type_;

 QComboBox* cbb_user_type_;

 QLabel* lbl_search_term_;
 QLineEdit* le_search_term_;

 QLabel* lbl_credentials_file_;
 QLineEdit* le_credentials_file_;
 QPushButton* btn_load_credentials_;
 QPushButton* btn_set_credentials_file_;
 QHBoxLayout* credentials_file_layout_;


 QCheckBox* cb_fixed_phrase_;
 QCheckBox* cb_free_phrase_;
 QCheckBox* cb_or_;
 QCheckBox* cb_and_;
 QCheckBox* cb_case_sensitive_;

 QLabel* lbl_filter_;

 QVBoxLayout* filters_layout_;
 QHBoxLayout* filters_layout1_;
 QHBoxLayout* filters_layout2_;
 QHBoxLayout* filters_layout3_;
 QHBoxLayout* filters_layout4_;

 QCheckBox* cb_main_text_;
 QCheckBox* cb_footnote_text_;
 QCheckBox* cb_sentences_with_footnote_;
 QCheckBox* cb_block_quotes_;
 QCheckBox* cb_all_quotes_;
 QCheckBox* cb_chapter_titles_;
 QCheckBox* cb_section_titles_;
 QCheckBox* cb_bibliography_;
 QCheckBox* cb_local_index_;
 QCheckBox* cb_current_chapter_;
 QCheckBox* cb_current_section_;
 QCheckBox* cb_comments_edits_;
// QCheckBox* cb_current_section_;


 //QLabel* sentence_label_;

 void add_index_entry_line();


public:



 PDF_Enhanced_Search_Dialog(QWidget* parent = nullptr);

 ~PDF_Enhanced_Search_Dialog();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();


public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif //  PDF_ENHANCED_SEARCH_DIALOG__H



