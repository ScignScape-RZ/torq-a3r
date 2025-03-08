
#ifndef DHAX_PDF_VIEW_DIALOG__H
#define DHAX_PDF_VIEW_DIALOG__H


#include <QString>
#include <QMainWindow>

#include <QTextEdit>
//?#include <QWebView>

#include <QWebEngineView>
#include <QLabel>
#include <QPushButton>

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QRubberBand>

#include <QMainWindow>

#include "accessors.h"

#include "flags.h"

#include "qsns.h"

#include "global-types.h"

#include "subwindows/reverse-spinbox.h"

//?#include "view-ocr-fields-dialog.h"

#include "subwindows/pdf-document-widget.h"


//class PDF_Document_Widget;

//#include "incident-form-dialog.h"

class QPushButton;
class QTextEdit;
class QPlainTextEdit;
class QLineEdit;
class QTabWidget;
class QDialogButtonBox;
class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;
class QFormLayout;
class QSplitter;
class QGridLayout;
class QListWidget;
class QTableWidget;
class QScrollArea;
class QGroupBox;
class QTableWidgetItem;

//?QSNS_(Cy_Mesh)
//?namespace QScign{ namespace Cy_Mesh{


//?
//class NDP_Antemodel;
//class NDP_Project;
//class NDP_Project_Initial;

class Index_Entry_Review_Dialog;

class DHAX_PDF_View_Dialog : public QMainWindow
{
 Q_OBJECT

 QString pdf_file_path_;

 Index_Entry_Review_Dialog* entry_dialog_;
 DHAX_PDF_View_Dialog* earlier_document_ref_;

 QList<QRubberBand*> rubber_bands_;


 QFrame* main_frame_;

// QFrame* controls_frame_;
 QVBoxLayout* controls_layout_;
 //QDockWidget* controls_dock_widget_;
 Reverse_Spin_Box* page_spin_box_;
 QLineEdit* search_line_edit_;
 QLabel* search_label_;
 QLabel* page_label_;
 QLabel* scale_label_;
 QComboBox* scale_combo_box_;

 QComboBox* pages_combo_box_;

 QPushButton* find_button_;

 QPushButton* clear_most_recent_match_button_;
 QPushButton* confirm_match_button_;
 QPushButton* refocus_entry_dialog_button_;

 QDialogButtonBox* button_box_;
// QPushButton* button_ok_;
// QPushButton* button_cancel_;
// QPushButton* button_proceed_;
 QPushButton* button_close_;


 PDF_Document_Widget* pdf_document_widget_;

 QPair<u2, s2> held_index_entry_key_;

 QGridLayout* path_layout_;
 QLabel* file_label_;
 QLineEdit* file_line_edit_;
 QLineEdit* status_line_edit_;
 QLabel* notes_label_;
 QLineEdit* notes_line_edit_;


 QVBoxLayout* main_layout_;

 //?NDP_Antemodel* antemodel_;
 QScrollArea* pdf_document_scroll_area_;

// QHBoxLayout* go_button_layout_;
// QPushButton* go_button_;
// QPushButton* open_button_;

// QHBoxLayout* close_button_layout_;
// QPushButton* close_button_;

 QString notes_file_;

 void read_file(QString path, QPlainTextEdit* qpte);

 void retranslate_ui();

 QMap<QString, QVector<int>> cached_page_matches_;
 QMap<int, QPair<QString, QStringList>> rank_in_pages_;

 QMap<PDF_Document_Widget::Highlight_Key, PDF_Document_Widget::Highlight_Info> visible_highlights_;
 QMap<PDF_Document_Widget::Highlight_Key, PDF_Document_Widget::Highlight_Info> cached_highlights_;

 int roman_start_;
 int roman_end_;
 int arabic_start_;

 QVector<int> cached_pages_combo_values_;

public:

 DHAX_PDF_View_Dialog(Index_Entry_Review_Dialog* entry_dialog,
   DHAX_PDF_View_Dialog* earlier_document_ref,
   QString pdf_file_path, QString notes_file,
   int ars,   int requested_page = 1); //, NDP_Antemodel* antemodel);
 ~DHAX_PDF_View_Dialog();

 ACCESSORS(QString ,pdf_file_path)

 ACCESSORS(int ,roman_start)
 ACCESSORS(int ,roman_end)
 ACCESSORS(int ,arabic_start)


 int page_number_to_text(int i, QString& result, QString fallback_template = "(%1)");

 void show_status(QString text);

 void reset_pages_combo_box(QVector<int>* pages = {});

 void activate_search(QString text);

 bool wants_box();

 void load_page(int number, QObject* origin = nullptr);

 void clear_most_recent_match(int index_entry_id, int page_number);

 void highlight_match(int index_entry_id, QString text, int page_number,
   const PDF_Document_Widget::Highlight_Info& hi);

 void highlight_match(int index_entry_id, QString text,   QStringList* paragraph_codes, QString& context);

 void clear_all_highlights();

 void search_update(QPair<u2, s2> index_entry_key, int index_entry_id, QString text, int count_in_index,
   int page_hint, QStringList* page_paragraph_codes = nullptr, QString* context = nullptr);


 //int get_vertical_scroll();

Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);

public Q_SLOTS:
 void accept();
 void cancel();

 //?void proceed();
 //void go_button_clicked();

};

//?} } //_QSNS(Cy_Mesh)


#endif //  VIEW_PDF_DIALOG__H
