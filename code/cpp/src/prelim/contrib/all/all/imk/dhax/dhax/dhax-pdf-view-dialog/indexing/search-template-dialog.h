
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SEARCH_TEMPLATE_DIALOG__H
#define SEARCH_TEMPLATE_DIALOG__H

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

#include <QRadioButton>

class Search_Template_Dialog : public QDialog
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


 QLabel* lbl_back_end_;

 QRadioButton* rb_manticore_;
 QRadioButton* rb_pisa_;
 QRadioButton* rb_htxn_;
 QRadioButton* rb_whitedb_;
 QRadioButton* rb_tkrzw_;


 QLabel* lbl_text_window_options_;
 QCheckBox* cb_proximity_distance_;
 QComboBox* cbb_proximity_distance_;
 QCheckBox* cb_quorum_;
 QComboBox* cbb_quorum_;
 QCheckBox* cb_strict_order_;
 QCheckBox* cb_near_;
 QComboBox* cbb_near_;

 QPushButton* btn_preview_;



 QLabel* lbl_scope_;

 QCheckBox* rb_scope_all_;

 QRadioButton* rb_sentence_;
 QRadioButton* rb_paragraph_;
 QRadioButton* rb_zone_;
 QRadioButton* rb_zonespan_;



 //QLabel* sentence_label_;

 void add_index_entry_line();


public:



 Search_Template_Dialog(QWidget* parent = nullptr);

 ~Search_Template_Dialog();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();


public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif //  SEARCH_TEMPLATE_DIALOG__H



