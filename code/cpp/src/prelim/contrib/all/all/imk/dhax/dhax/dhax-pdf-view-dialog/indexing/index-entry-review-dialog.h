
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
#include <QMainWindow>

#include <functional>


#include "m2m.h"

#include "accessors.h"

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

class QSplitter;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

class DHAX_PDF_View_Dialog;

class Index_Entry_Review_Dialog : public QMainWindow
{

 Q_OBJECT


 DHAX_PDF_View_Dialog* earlier_pdf_dialog_;
 DHAX_PDF_View_Dialog* later_pdf_dialog_;


 QString earlier_match_file_;
 QString ftp_folder_;


 QVector<Index_Entry> index_entries_;
 Index_Entry* current_index_entry_;

 QFrame* main_frame_;

 QDockWidget* comparison_dock_widget_;
 QSplitter* comparison_splitter_;
 QTextEdit* comparison_left_text_edit_;
 QTextEdit* comparison_right_text_edit_;


 void setup_comparison_window();

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
 QGroupBox* earlier_match_group_box_;
 QGroupBox* current_search_group_box_;

 QVBoxLayout* info_group_box_layout_;
 QHBoxLayout* info_group_box_bottom_layout_;
 QFormLayout* info_group_box_top_layout_;
 QFormLayout* info_group_box_left_layout_;
 QFormLayout* info_group_box_right_layout_;

 QVBoxLayout* earlier_match_group_box_layout_;
 QHBoxLayout* earlier_match_group_box_bottom_layout_;
 QFormLayout* earlier_match_group_box_top_layout_;
 QFormLayout* earlier_match_group_box_left_layout_;
 QVBoxLayout* earlier_match_group_box_right_layout_;

 QVBoxLayout* current_search_group_box_layout_;
 QFormLayout* current_search_group_box_layout_top_;
 QGridLayout* current_matches_grid_layout_;

 QLineEdit* search_text_line_edit_;

 QLineEdit* earlier_match_code_update_line_edit_;
 QLineEdit* active_earlier_match_code_line_edit_;
 QCheckBox* active_earlier_match_code_updated_check_box_;

 QTextEdit* match_codes_text_edit_;

 QLineEdit* heading_line_edit_;
 QLineEdit* parent_heading_line_edit_;

 QLineEdit* entry_id_line_edit_;
 QLineEdit* number_of_match_components_line_edit_;

 QLineEdit* count_in_parent_line_edit_;
 QLineEdit* subheading_count_line_edit_;

 QHBoxLayout* active_earlier_match_code_nav_layout_;
 QHBoxLayout* active_earlier_match_code_highlight_layout_;

 QPushButton* active_earlier_match_code_forward_button_;
 QPushButton* active_earlier_match_code_backward_button_;

 QPushButton* earlier_track_highlight_button_;
 QPushButton* clear_earlier_highlights_button_;
 QPushButton* search_update_button_;

 u2 active_earlier_match_code_index_;
 u2 max_earlier_match_code_index_;

 QVector<QPair<Page_Ref_Pair, QString>> earlier_match_codes_;

 void reset_active_earlier_match_code();
 Page_Ref_Pair current_page_ref_pair_;
 QString current_page_ref_string_;

 QString current_page_ref_long_display_;

 u2 flip_count_;
 u2 slurp_count_;

 //Page_Ref_Pair

 //QLabel* sentence_label_;

 void earlier_match_forward();
 void earlier_match_backward();

 void entry_forward();
 void entry_backward();

 void load_entry(u2 id);

 void add_current_match_line();
 void load_earlier_matches();

 void check_earlier_highlight();

 void earlier_highlight();
 void clear_earlier_highlights();


 QString match_code_long_display(const Page_Ref_Pair& pr);
 void match_code_display(QString& text);

 QString match_code_display(const QVector<QPair<Page_Ref_Pair, QString>>& prs);

 void check_nav_buttons();

 void check_search_update();
 void search_update();


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

 QPushButton* redo_earlier_match_button_;
 QPushButton* redo_later_match_button_;
 QPushButton* clean_later_match_button_;

 void redo_earlier_match();
 void redo_later_match();

 void clean_later_match();

 void reset_search_word_list(QStringList words);
 void reset_search_word_list(u2 low, u2 high);
 void reset_search_word_list();

 void search_words_inc_high();
 void search_words_dec_high();

 void search_words_inc_low();
 void search_words_dec_low();

 void search_words_flip();
 void search_words_slurp();

 u2 ref_code_to_earlier_page_number(const Page_Ref& page_ref);
 u2 ref_code_to_later_page_number(const Page_Ref& page_ref);

 //QMap<Page_Ref, >

public:

 Index_Entry_Review_Dialog(QString earlier_match_file, QString ftp_folder);

 void reclaim_focus();

 void confirm_match(int page_number);
 void clear_most_recent_match(int page_number);

 void ftp_upload(QString file_name, QString text);

 void update_split_window(QString text1, QString text2);


 ACCESSORS(DHAX_PDF_View_Dialog* ,earlier_pdf_dialog)
 ACCESSORS(DHAX_PDF_View_Dialog* ,later_pdf_dialog)

 ~Index_Entry_Review_Dialog();





Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();

 //?void location_marker_requested(QGeoLocation loc);

public Q_SLOTS:


 void accept();
 void cancel();


};

//_QSNS(ScignStage)


#endif //  INDEX_ENTRY_REVIEW_DIALOG__H



