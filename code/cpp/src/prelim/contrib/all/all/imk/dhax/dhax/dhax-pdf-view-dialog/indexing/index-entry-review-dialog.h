
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

#include "enum-macros.h"


#include "m2m.h"
#include "index-ref.h"

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
class QListWidget;
class QListWidgetItem;

class QSplitter;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

class QFormLayout;

class QComboBox;

class DHAX_PDF_View_Dialog;

class Index_Entry_Review_Dialog : public QMainWindow
{

 Q_OBJECT

 QVector<QPair<QString, QVector<Index_Ref_Summary>>>* review_vector_;

 DHAX_PDF_View_Dialog* earlier_pdf_dialog_;
 DHAX_PDF_View_Dialog* later_pdf_dialog_;

 QSet<int>* addendum_pages_;
 QVector<Index_Ref_Group>* ref_groups_;

 QVector<Index_Ref_Group*> ref_groups_filtered_Range_;
 QVector<Index_Ref_Group*> ref_groups_filtered_Roman_;
 QVector<Index_Ref_Group*> ref_groups_filtered_Missing_;
 QVector<Index_Ref_Group*> ref_groups_filtered_New_Terms_;

 enum class Nav_Filters {
  None, Range, Roman, Missing, New_Terms
 };

 Nav_Filters current_nav_filter_;
 void activate_nav_filter(Nav_Filters f)
 {
  current_nav_filter_ = f;
 }

 QMap<Nav_Filters, QVector<u2>> ref_groups_filtered_;

 QString bookmarks_file_;
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
 QPushButton* button_close_all_;
 QPushButton* button_close_;
// QPushButton* button_proceed_;

 QPushButton* composite_upload_button_;

 QPushButton* entry_forward_button_;
 QPushButton* entry_backward_button_;

 QPushButton* entry_double_backward_button_;

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
 QHBoxLayout* earlier_match_group_box_bottom_left_layout_;

 QVBoxLayout* earlier_match_group_box_right_layout_;

 QVBoxLayout* current_search_group_box_layout_;
 QFormLayout* current_search_group_box_layout_top_;
 QGridLayout* current_matches_grid_layout_;

 QLineEdit* search_text_line_edit_;

 QLineEdit* earlier_match_code_edit_line_edit_;
 QLineEdit* earlier_match_code_update_line_edit_;
 QLineEdit* active_earlier_match_code_line_edit_;

 QCheckBox* active_earlier_match_code_confirmed_check_box_;
 QCheckBox* active_earlier_match_code_exclude_check_box_;
 QCheckBox* detach_page_number_check_box_;
 QCheckBox* active_earlier_match_manual_update_check_box_;
 QCheckBox* earlier_match_bookmarked_check_box_;
// QPushButton* auto_detach_button_;


 QGridLayout* earlier_match_group_box_middle_layout_;


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
 QPushButton* active_earlier_match_code_back_to_start_button_;

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

 enum class Entry_Update_Status {
  N_A = 0, Confirmed = 1, Excluded = 2, New = 4,
  Manually_Edited = 8, Detach_Page_Number = 16,
  Bookmarked = 32,
  Unset = 64
 };

 ENUM_FLAGS_OP_MACROS(Entry_Update_Status)

 struct Entry_Update_Key {
  u2 entry_id;
  s2 match_index;
  u2 earlier_match_index()
  {
   return qMax(match_index, (s2)0);
  }
  u2 later_match_index()
  {
   return -qMin(match_index, (s2)0);
  }
  static Entry_Update_Key from_pair(QPair<u2, s2> pr)
  {
   return {pr.first, pr.second};
  }

  QPair<u2, s2> to_pair() const { return {entry_id, match_index}; }
 };

 friend bool operator<(const Entry_Update_Key& lhs, const Entry_Update_Key& rhs)
 {
  return lhs.to_pair() < rhs.to_pair();
 }

 friend bool operator==(const Entry_Update_Key& lhs, const Entry_Update_Key& rhs)
 {
  return lhs.to_pair() == rhs.to_pair();
 }

 struct Entry_Update_Value {
   Entry_Update_Status status;
   u2 index_as_new;
   QString manual_update;
 };

 void check_entry_value_manual_update();

 Entry_Update_Key current_entry_key_;

 QMap<Entry_Update_Key, Entry_Update_Value> entry_update_map_;

#define ENTRY_UPDATE_NOTE_MACRO(x) \
 void entry_update_note_##x(Entry_Update_Key k) \
 { if(entry_update_map_.contains(k)) \
     entry_update_map_[k].status |= Entry_Update_Status::x; } \
 void entry_update_clear_##x(Entry_Update_Key k) \
 { if(entry_update_map_.contains(k)) \
     entry_update_map_[k].status &= ~Entry_Update_Status::x; } \
 void entry_update_reset_##x(Entry_Update_Key k, bool b) \
 { if(entry_update_map_.contains(k)) if(b) entry_update_note_##x(); \
     else entry_update_clear_##x(); } \
 void entry_update_reset_##x(bool b) { entry_update_reset_##x(current_entry_key_, b); } \
 void entry_update_clear_##x() { entry_update_clear_##x(current_entry_key_); } \
 void entry_update_note_##x() { entry_update_note_##x(current_entry_key_); } \
 bool entry_update_is_##x(Entry_Update_Key k) \
 { return entry_update_map_.contains(k) && \
     entry_update_map_[k].status & Entry_Update_Status::x; } \
 bool entry_update_is_##x() { entry_update_is_##x(current_entry_key_); } \

 ENTRY_UPDATE_NOTE_MACRO(Confirmed)
 ENTRY_UPDATE_NOTE_MACRO(Excluded)
 ENTRY_UPDATE_NOTE_MACRO(New)
 ENTRY_UPDATE_NOTE_MACRO(Manually_Edited)
 ENTRY_UPDATE_NOTE_MACRO(Detach_Page_Number)
 ENTRY_UPDATE_NOTE_MACRO(Bookmarked)

 //Page_Ref_Pair

 //QLabel* sentence_label_;

 void check_update_entry_update_map();

 void reset_current_entry_update_text();

 void reset_current_entry_check_boxes();
 void reset_current_entry_key(Index_Entry& ie, const s2* const maybe_match_index);

 void update_current_entry_map_index();

 void composite_upload();

 void earlier_match_set_index(u2 target);

 void earlier_match_forward();
 void earlier_match_backward();
 void earlier_match_back_to_start();

 void entry_forward();
 void entry_backward();

 void entry_forward(QVector<u2>& vec);
 void entry_backward(QVector<u2>& vec);

 void entry_back_to_start();

 void load_entry(u2 id, const s2* const maybe_match_index = nullptr);

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

 QPushButton* search_words_slurp_and_flip_button_;
 QPushButton* search_words_flip_button_;
 QPushButton* search_words_slurp_button_;
 QPushButton* search_words_reset_button_;
 QPushButton* search_words_take_visible_first_button_;

 QLineEdit* addendum_hits_line_edit_;

 QPushButton* redo_both_matches_button_;

 QPushButton* redo_earlier_match_button_;
 QPushButton* redo_later_match_button_;
 QPushButton* clean_later_match_button_;


 QLineEdit* html_file_name_line_edit_;
 QLineEdit* html_file_entries_line_edit_;

 QPushButton* html_upload_button_;

 QString html_text_;

 QDockWidget* html_preview_dock_widget_;

 QSplitter* html_preview_splitter_;
 QTextEdit* html_preview_text_edit_;
 QTextEdit* html_preview_supplement_text_edit_;


 QHBoxLayout* html_details_layout_;


 QDockWidget* confirms_dock_widget_;
 QListWidget* confirms_list_widget_;

 QTabWidget* page_text_view_tab_widget_;
 QPlainTextEdit* page_text_view_text_edit_earlier_;
 QPlainTextEdit* page_text_view_text_edit_later_;
 QDockWidget* page_text_view_dock_widget_;


 QMenu* create_confirms_list_widget_context_menu(QListWidgetItem* item);

 QPushButton* always_generate_html_button_;
 QPushButton* generate_html_button_;
 QPushButton* generate_then_forward_button_;

 QString saved_phtml_;
 QString saved_shtml_;
 QString current_phtml_;

 QPair<u2, u2> entry_index_range_;

 QMap<u2, QStringList> generated_htmls_;

 QMap<Entry_Update_Key, QStringList> cached_paragraph_codes_;


 QFrame* make_frame_as_line();

 void update_generated_htmls();

 QString get_preview_html();
 QString get_supplement_html();

 void toggle_html();
 void reset_toggle_html();

 void supplement_italicize();

 void clear_confirms_list_widget();
 void regenerate_html();
 void check_generate_html();

 void reset_html_details();
 void html_upload();
 void ftp_upload(QString file_name, QString text);


 void reset_file_entries_text();

 void redo_both_matches();
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

 void search_words_take_visible_first();
 void search_words_reset();

 void search_words_flip();
 void search_words_slurp();

 u2 ref_code_to_earlier_page_number(const Page_Ref& page_ref);
 u2 ref_code_to_later_page_number(const Page_Ref& page_ref);

 void update_html(QString key, QString parent_ref, QStringList page_numbers, QString sub_only);
 void update_html(QStringList page_numbers);

 //QMap<Page_Ref, >

public:

 Index_Entry_Review_Dialog(QString earlier_match_file, QString bookmarks_file, QString ftp_folder);

 void reclaim_focus();

 void filter_ref_groups();

 void confirm_match(QPair<u2, s2> pr, int page_number, QString paragraph_code);
 void clear_most_recent_match(int page_number);


 void set_page_text_view_text_earlier(QString text);
 void set_page_text_view_text_later(QString text);

 QVector<Entry_Update_Key> bookmarks_;

 void check_for_bookmarks();

 void check_bookmark();
 void remove_bookmark();

 void load_bookmarks_file();
 void save_bookmarks_file();


 ACCESSORS(DHAX_PDF_View_Dialog* ,earlier_pdf_dialog)
 ACCESSORS(DHAX_PDF_View_Dialog* ,later_pdf_dialog)
 ACCESSORS(QSet<int>* ,addendum_pages)

 ACCESSORS(QVector<Index_Ref_Group>* ,ref_groups)

 ACCESSORS(QVector<QPair<QString, QVector<Index_Ref_Summary>>>* ,review_vector)

 void check_review_vector(QString review_file);


 ~Index_Entry_Review_Dialog();


 void note_addendum_hits(QVector<int>& hits);


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



