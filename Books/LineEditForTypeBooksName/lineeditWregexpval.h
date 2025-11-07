#ifndef TYPESIGLAWIDGET_H
#define TYPESIGLAWIDGET_H

#include <QWidget>

#include <QCompleter>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class LineEditWReExpVal : public QWidget
{
    Q_OBJECT

public:
    LineEditWReExpVal(QWidget *parent = nullptr);
    ~LineEditWReExpVal();


    const QString text() const;

private:
    Ui::Widget *ui;

};
#endif // TYPESIGLAWIDGET_H
