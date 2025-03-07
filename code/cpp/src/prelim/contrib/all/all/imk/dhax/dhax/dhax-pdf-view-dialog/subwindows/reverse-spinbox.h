#ifndef REVERSE_SPIN_BOX__H
#define REVERSE_SPIN_BOX__H

#include <QSpinBox>

#include <QLineEdit>


class DHAX_PDF_View_Dialog;

class RSB_Line_Edit : public QLineEdit
{
 public:

 RSB_Line_Edit(QWidget* parent);

 virtual void paintEvent(QPaintEvent* e)  Q_DECL_OVERRIDE;


// virtual void focusInEvent(QFocusEvent *e);
// virtual void focusOutEvent(QFocusEvent *e);

// void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;

// void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;

// void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;

};

class Reverse_Spin_Box : public QSpinBox
{
 Q_OBJECT

 DHAX_PDF_View_Dialog* parent_view_;
 QString highlights_;
 QString no_highlights_;

public:

 Reverse_Spin_Box(DHAX_PDF_View_Dialog* parent); // = nullptr);

 void set_maximum(int max);

 int valueFromText(const QString &text) const;
 QString textFromValue(int value) const;

 QValidator::State validate(QString &input, int &pos) const;

// virtual void focusInEvent(QFocusEvent *e);
// virtual void focusOutEvent(QFocusEvent *e);

 //QValidator validate()

Q_SIGNALS:

 void value_changed(int value);

public Q_SLOTS:
 void stepBy(int steps);
 void reverse_value_changed(int value);
 void set_value(int value);
};

#endif
