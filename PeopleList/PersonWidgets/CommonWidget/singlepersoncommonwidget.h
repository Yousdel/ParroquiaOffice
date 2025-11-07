#ifndef SINGLEPERSONCOMMONWIDGET_H
#define SINGLEPERSONCOMMONWIDGET_H

#include <QWidget>

namespace Ui {
class SinglePersonCommonWidget;
}

class SinglePersonCommonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SinglePersonCommonWidget(QWidget *parent = nullptr);
    ~SinglePersonCommonWidget();

    const QString getName() const;
    const QString getFirstName() const;
    const QString getLastName() const;

    void setName(const QString &str) ;
    void setFirstName(const QString &str) ;
    void setLastName(const QString &str) ;

private:
    Ui::SinglePersonCommonWidget *ui;
};

#endif // SINGLEPERSONCOMMONWIDGET_H
