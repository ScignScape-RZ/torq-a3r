
#include "reverse-spinbox.h"

#include "pdf-document-widget.h"

#include "paraviews/dhax-pdf-view-dialog.h"

#include <QLineEdit>

#include <QFocusEvent>



RSB_Line_Edit::RSB_Line_Edit(QWidget* parent)
  :  QLineEdit(parent)
{
 setReadOnly(true);
}

void RSB_Line_Edit::focusInEvent(QFocusEvent *e)
{
 setFocusPolicy(Qt::NoFocus);
}

void RSB_Line_Edit::focusOutEvent(QFocusEvent *e)
{

}


void RSB_Line_Edit::mousePressEvent(QMouseEvent *)
{}

void RSB_Line_Edit::mouseMoveEvent(QMouseEvent *)
{}

void RSB_Line_Edit::mouseReleaseEvent(QMouseEvent *)
{}



void Reverse_Spin_Box::focusInEvent(QFocusEvent *e)
{
 e->accept();
}

void Reverse_Spin_Box::focusOutEvent(QFocusEvent *e)
{
 e->accept();
}


Reverse_Spin_Box::Reverse_Spin_Box(DHAX_PDF_View_Dialog* parent)
 : QSpinBox(parent)
{
 parent_view_ = parent;

 setLineEdit(new RSB_Line_Edit(this));

 connect(this, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
             [&, this](){this->findChild<QLineEdit*>()->deselect();}, Qt::QueuedConnection);

 connect(this, SIGNAL(valueChanged(int)),
   this, SLOT(reverse_value_changed(int)));
}

QValidator::State Reverse_Spin_Box::validate(QString &input, int &pos) const
{
 return QValidator::Acceptable;
}

int Reverse_Spin_Box::valueFromText(const QString& text) const
{
 int num = text.toInt();
 if(num == 0)
 {
  return 0;
 }
 else
 {
  return - (num - 1);
 }
}

QString Reverse_Spin_Box::textFromValue(int value) const
{
 QString tv = QSpinBox::textFromValue(1 - value);

 //return tv;

 //DHAX_PDF_View_Dialog* dialog = qobject_cast<DHAX_PDF_View_Dialog*>(parent());

 QString text;
 parent_view_->page_number_to_text(0 - value, text);

 lineEdit()->deselect();

 return tv + " -> " + text; // QSpinBox::textFromValue(1 - value);

}

void Reverse_Spin_Box::set_value(int value)
{
 this->QSpinBox::setValue(1 - value);
}

void Reverse_Spin_Box::reverse_value_changed(int value)
{
 Q_EMIT(value_changed(1 - value));
}

void Reverse_Spin_Box::set_maximum(int max)
{
 this->QSpinBox::setMaximum(0);
 this->QSpinBox::setMinimum(1 - max);
}


void Reverse_Spin_Box::stepBy(int steps)
{
 this->QSpinBox::stepBy(steps);
//    switch(steps) {
//        case 1 :    setValue(value()*2);
//                    break;
//        case -1 :   setValue(value()/2);
//                    break;
//        default:    QSpinBox::stepBy(steps);
//                    break;
//    }
}

