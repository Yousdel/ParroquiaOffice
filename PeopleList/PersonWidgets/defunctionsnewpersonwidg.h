#ifndef DEFUNCTIONSNEWPERSONWIDG_H
#define DEFUNCTIONSNEWPERSONWIDG_H

#include <QWidget>

//app
#include "basenewpersonwidg.h"

namespace Ui {
class DefunctionsNewPersonWidg;
}

class DefunctionsNewPersonWidg : public BaseNewPersonWidg
{
    Q_OBJECT

public:
    explicit DefunctionsNewPersonWidg(QWidget *parent = nullptr);
    ~DefunctionsNewPersonWidg();

    const QDate burialDate() const;
    const QDate dateOfDeath() const;
    const QString causeOfDeath() const;

    const QString age() const;

    const QString father() const;
    const QString mother() const;
    const QString minister() const;

    // setters --------------------------------------------------------

    void setBurialDate(const QDate &date) ;
    void setDateOfDeath(const QDate &date) ;
    void setCauseOfDeath(const QString &str) ;

    void setAge(const QString &str) ;

    void setFather(const QString &str);
    void setMother(const QString &str);
    void setMinister(const QString &str);


    COMMON_GETTERS

private slots:
    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::DefunctionsNewPersonWidg *ui;
};

#endif // DEFUNCTIONSNEWPERSONWIDG_H
