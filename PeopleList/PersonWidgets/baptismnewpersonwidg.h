#ifndef BAPTISMNEWPERSONWIDG_H
#define BAPTISMNEWPERSONWIDG_H

#include <QWidget>
#include "CommonWidget/commonwidget.h"
#include "basenewpersonwidg.h"


namespace Ui {
class BaptismNewPersonWidg;
}

class BaptismNewPersonWidg : public BaseNewPersonWidg
{
    Q_OBJECT

public:
    explicit BaptismNewPersonWidg(QWidget *parent = nullptr);
    ~BaptismNewPersonWidg();

    const QDate bornDate() const;
    const QString bornPlace() const;
    const QDate baptismDate() const;

    const QString godMother() const;
    const QString godFather() const;
    const QString getMinister() const;

    const QString father() const;
    const QString fatherPlace() const;
    const QString mother() const;
    const QString motherPlace() const;

    //abuelos paternos
    const QString paternalGrandPa() const;
    const QString paternalGrandPaPlace() const;
    const QString paternalGrandMa() const;
    const QString paternalGrandMaPlace() const;

    //abuelos maternos
    const QString maternalGrandPa() const;
    const QString maternalGrandPaPlace() const;
    const QString maternalGrandMa() const;
    const QString maternalGrandMaPlace() const;

    //--------------------------------- Setters-----------------------
     void setBornDate(const QDate &date) ;
     void setBornPlace(const QString &str) ;
     void setBaptismDate(const QDate &date) ;

     void setGodMother(const QString &str) ;
     void setGodFather(const QString &str) ;
     void setMinister(const QString &str) ;

     void setFather(const QString &str) ;
     void setFatherPlace(const QString &str) ;
     void setMother(const QString &str) ;
     void setMotherPlace(const QString &str) ;

    //abuelos paternos
     void setPaternalGrandPa(const QString &str) ;
     void setPaternalGrandPaPlace(const QString &str) ;
     void setPaternalGrandMa(const QString &str) ;
     void setPaternalGrandMaPlace(const QString &str) ;

    //abuelos maternos
     void setMaternalGrandPa(const QString &str) ;
     void setMaternalGrandPaPlace(const QString &str) ;
     void setMaternalGrandMa(const QString &str) ;
     void setMaternalGrandMaPlace(const QString &str) ;



    COMMON_GETTERS


private slots:
    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::BaptismNewPersonWidg *ui;

};

#endif // BAPTISMNEWPERSONWIDG_H
