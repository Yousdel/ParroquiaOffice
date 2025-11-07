#ifndef CONFIRMATIONNEWPERSONWIDG_H
#define CONFIRMATIONNEWPERSONWIDG_H

#include <QWidget>

//app
#include "CommonWidget/commonwidget.h"
#include "basenewpersonwidg.h"

namespace Ui {
class ConfirmationNewPersonWidg;
}

class ConfirmationNewPersonWidg : public BaseNewPersonWidg
{
    Q_OBJECT

public:
    explicit ConfirmationNewPersonWidg(QWidget *parent = nullptr);
    ~ConfirmationNewPersonWidg();

    const QDate confirmationDate() const;
    const QString godFatherOrMother() const;
    const QString minister() const;

    // setters ---------------------------------------------------

    void setConfirmationDate(const QDate &date) ;
    void setGodFatherOrMother(const QString &str) ;
    void setMinister(const QString &str) ;

    COMMON_GETTERS

private slots:
    //guardar
    void on_pushButton_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::ConfirmationNewPersonWidg *ui;
};

#endif // CONFIRMATIONNEWPERSONWIDG_H
