
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef INDEX_ENTRY_REVIEW_DIALOG__H
#define INDEX_ENTRY_REVIEW_DIALOG__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QTableWidget>

#include <functional>

#include <QGeoLocation>

#include "m2m.h"

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
class QCheckBox;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

class Index_Entry_Review_Dialog : public QDialog
{

 Q_OBJECT


 QString prior_match_file_;
 QVector<Index_Entry> index_entries_;
 Index_Entry* current_index_entry_;

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;

 QPushButton* entry_forward_button_;
 QPushButton* entry_backward_button_;

 QHBoxLayout* bottom_layout_;

 QVBoxLayout* main_layout_;

 QVBoxLayout* entry_layout_;

 QGroupBox* info_group_box_;
 QGroupBox* prior_match_group_box_;
 QGroupBox* current_search_group_box_;

 QVBoxLayout* info_group_box_layout_;
 QHBoxLayout* info_group_box_bottom_layout_;
 QFormLayout* info_group_box_top_layout_;
 QFormLayout* info_group_box_left_layout_;
 QFormLayout* info_group_box_right_layout_;

 QVBoxLayout* prior_match_group_box_layout_;
 QHBoxLayout* prior_match_group_box_bottom_layout_;
 QFormLayout* prior_match_group_box_top_layout_;
 QFormLayout* prior_match_group_box_left_layout_;
 QVBoxLayout* prior_match_group_box_right_layout_;

 QVBoxLayout* current_search_group_box_layout_;
 QFormLayout* current_search_group_box_layout_top_;
 QGridLayout* current_matches_grid_layout_;

 QLineEdit* search_text_line_edit_;

 QLineEdit* prior_match_code_update_line_edit_;
 QLineEdit* active_prior_match_code_line_edit_;
 QCheckBox* active_prior_match_code_updated_check_box_;

 QTextEdit* match_codes_text_edit_;

 QLineEdit* heading_line_edit_;
 QLineEdit* parent_heading_line_edit_;

 QLineEdit* entry_id_line_edit_;
 QLineEdit* number_of_match_components_line_edit_;

 QLineEdit* count_in_parent_line_edit_;
 QLineEdit* subheading_count_line_edit_;

 QHBoxLayout* active_prior_match_code_nav_layout_;

 QPushButton* active_prior_match_code_forward_button_;
 QPushButton* active_prior_match_code_backward_button_;

 u2 active_prior_match_code_index_;
 u2 max_prior_match_code_index_;

 QVector<QPair<Page_Ref_Pair, QString>> prior_match_codes_;

 void reset_active_prior_match_code();
 Page_Ref_Pair current_page_ref_pair_;
 QString current_page_ref_string_;

 QString current_page_ref_long_display_;

 u2 flip_count_;
 u2 slurp_count_;

 //QLabel* sentence_label_;

 void prior_match_forward();
 void prior_match_backward();

 void entry_forward();
 void entry_backward();

 void load_entry(u2 id);

 void add_current_match_line();
 void load_prior_matches();

 QString match_code_long_display(const Page_Ref_Pair& pr);
 void match_code_display(QString& text);

 QString match_code_display(const QVector<QPair<Page_Ref_Pair, QString>>& prs);

 void check_nav_buttons();

 u2 current_entry_id_;
 u2 max_entry_id_;

 QStringList current_search_word_list_;
 u2 available_search_word_list_count_;
 u2 current_search_word_list_low_;
 u2 current_search_word_list_high_;

 QHBoxLayout* search_words_layout_;
 QPushButton* search_words_inc_high_button_;
 QPushButton* search_words_dec_high_button_;
 QPushButton* search_words_inc_low_button_;
 QPushButton* search_words_dec_low_button_;

 QPushButton* search_words_flip_button_;
 QPushButton* search_words_slurp_button_;

 void reset_search_word_list(QStringList words);
 void reset_search_word_list(u2 low, u2 high);
 void reset_search_word_list();

 void search_words_inc_high();
 void search_words_dec_high();

 void search_words_inc_low();
 void search_words_dec_low();

 void search_words_flip();
 void search_words_slurp();

public:



 Index_Entry_Review_Dialog(QString prior_match_file, QWidget* parent = nullptr);

 ~Index_Entry_Review_Dialog();





Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();

 void location_marker_requested(QGeoLocation loc);

public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif //  INDEX_ENTRY_REVIEW_DIALOG__H



