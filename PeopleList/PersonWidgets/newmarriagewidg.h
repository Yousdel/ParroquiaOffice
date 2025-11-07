#ifndef NEWMARRIAGEWIDG_H
#define NEWMARRIAGEWIDG_H

#include <QWidget>
//app
#include "basenewpersonwidg.h"

namespace Ui {
class MarryNewPersonWidg;
}

class NewMarriageWidg : public BaseNewPersonWidg
{
    Q_OBJECT

public:
    explicit NewMarriageWidg(QWidget *parent = nullptr);
    ~NewMarriageWidg();

    const QString getMalePerson() const;
    const QString getFemalePerson() const;

    const QString maleBornPlace() const;
    const QString femaleBornPlace() const;

    const QDate marriageDate() const;

    const QString maleFather() const;
    const QString maleMother() const;
    const QString femaleFather() const;
    const QString femaleMother() const;

    const QString maleWitness() const;
    const QString femaleWitness() const;

    const QString maleGodfather() const;
    const QString femaleGodmother() const;

    const QString getMinister() const;

    //setters ---------------------------------------------------------
    virtual void setMalePerson(const QString &str) ;
    virtual void setFemalePerson(const QString &str) ;

    virtual void setMaleBornPlace(const QString &str) ;
    virtual void setFemaleBornPlace(const QString &str) ;

    virtual void setMarriageDate(const QDate &date) ;

    virtual void setMaleFather(const QString &str) ;
    virtual void setMaleMother(const QString &str) ;
    virtual void setFemaleFather(const QString &str) ;
    virtual void setFemaleMother(const QString &str) ;

    virtual void setMaleWitness(const QString &str) ;
    virtual void setFemaleWitness(const QString &str) ;

    virtual void setMaleGodfather(const QString &str) ;
    virtual void setFemaleGodmother(const QString &str) ;

    virtual void setMinister(const QString &str);

    COMMON_GETTERS

private slots:
    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::MarryNewPersonWidg *ui;
};

#endif // NEWMARRIAGEWIDG_H
