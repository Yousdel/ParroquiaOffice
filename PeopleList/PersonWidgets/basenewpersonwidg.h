#ifndef BASENEWPERSONWIDG_H
#define BASENEWPERSONWIDG_H

#include <QWidget>
#include <QVector>
#include <QVariant>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

#include "CommonWidget/commonwidget.h"
#include "Books/createbookwidget.h"

class BaseNewPersonWidg : public QWidget
{
    Q_OBJECT

public:
    bool datesCoherency(bool b, const QString &strIfError) {
        if (b)
            setDatesOk();
        else
            setDatesError(strIfError);
        if (!datesAreOk()) {
            QMessageBox::warning(this, tr("Fechas incoherentes"),
                                 tr("Las fechas introducidas son erróneas porque %1"
                                    ", y por eso no puedes guardar.")
                                     .arg(datesError()));
            return false;
        }
        return true;
    }
private:
    bool _saved=false, dates_ok=false;
    QVector <QVariant> values;
    int indexForShow=0;
    QString dateErrStr;

    void setDatesOk() { dates_ok=true; }
    bool datesAreOk() const { return dates_ok; }

    void setDatesError(const QString &strError){
        dateErrStr = strError;
    }
    const QString &datesError() const { return dateErrStr; }

    void append(const QVariant &value){
        values.append(value);
    }

    void appendCommonValues(){
        append(QVariant(getBookName()));
        append(QVariant(getFolio()));
        append(QVariant(getInscriptionNumber()));
    }
    void appendSinglePersonValues(const CreateBookWidget::BookType &type){
        if (!CreateBookWidget::isSinglePersonType(type))
            return;
        append(QVariant(getFirstName()));
        append(QVariant(getLastName()));
        append(QVariant(getName()));
    }
    void appendBaptism(const CreateBookWidget::BookType &type);
    void appendMarriage(const CreateBookWidget::BookType &type);
    void appendDefunction(const CreateBookWidget::BookType &type);
    void appendConfirmation(const CreateBookWidget::BookType &type);
    void appendFinalCommonValues() {
        append(QVariant(getMarginalsNotes()));
        append(QVariant(getOtherData()));
    }
    //-----------------------------------------------------------------------set values & show
    const QVariant &nextValue()
    {
        ++indexForShow; //empiezo con index=1 para que se ssalte el id pk
        return values.at(indexForShow);
    }
    void showCommonValues(){
        indexForShow=0;
        setBookName(nextValue().toString());
        setFolio(nextValue().toString());
        setInscriptionNumber(nextValue().toString());
    }
    void showSinglePersonValues(const CreateBookWidget::BookType &type){
        if (!CreateBookWidget::isSinglePersonType(type))
            return;
        setFirstName(nextValue().toString());
        setLastName(nextValue().toString());
        setName(nextValue().toString());
    }
    void showBaptism(const CreateBookWidget::BookType &type);
    void showMarriage(const CreateBookWidget::BookType &type);
    void showDefunction(const CreateBookWidget::BookType &type);
    void showConfirmation(const CreateBookWidget::BookType &type);
    void showFinalCommonValues(){
        setMarginalNotes(nextValue().toString());
        setOtherData(nextValue().toString());
    }
    void showCurrentValues(const CreateBookWidget::BookType &type) {
        showCommonValues();
        showSinglePersonValues(type);
        showBaptism(type);
        showMarriage(type);
        showDefunction(type);
        showConfirmation(type);
        showFinalCommonValues();
    }
public:
    explicit BaseNewPersonWidg(QWidget *parent = nullptr);

    void saveData(const CreateBookWidget::BookType &type){
        values.clear();
        appendCommonValues();
        appendSinglePersonValues(type);
        appendBaptism(type);
        appendMarriage(type);
        appendDefunction(type);
        appendConfirmation(type);
        appendFinalCommonValues();
    }


    bool canSave(){
        int i=0x0;
        for (const QVariant &item : std::as_const(values)) {
            if (item.toString().isEmpty()){
                QMessageBox::warning(this, tr("Campos vacíos"),
                                     QString(tr("Hay campos sin llenar. Llénelos para poder"
                                        " salvar y agregar al libro. Campo :%1")).arg(i));
                return false;
            }
            ++i;
        }
        return true;
    }

    bool setSaved(){
        if (canSave()){
            _saved=true;
            return true;
        }
        return false;
    }
    bool saved() const { return _saved; }

    const QVector<QVariant> &allValues() const {
        return values;
    }

    void setValues(const QVector<QVariant> &v,
                   const CreateBookWidget::BookType &type){
        values = v;
        qDebug() << "setValues:" << values;
        showCurrentValues(type);
    }

    virtual const QString getName() const { return QString(); }
    virtual void setName(const QString &name) { (void) name; }
    virtual const QString getFirstName() const { return QString(); }
    virtual void setFirstName(const QString &firstNm) { (void) firstNm; }
    virtual const QString getLastName() const { return QString(); }
    virtual void setLastName(const QString &lastname) { (void) lastname; }
    virtual const QString getParroquia() const { return QString(); }    
    virtual const QString getBookName() const { return QString(); }

    virtual const QString getInscriptionNumber() const { return QString(); }
    virtual void setInscriptionNumber(const QString &inscription_number) { (void) inscription_number; }
    virtual const QString getFolio() const { return QString(); }
    virtual void setFolio(const QString &foliostr) { (void) foliostr; }
    virtual const QString getMarginalsNotes() const { return QString(); }
    virtual void setMarginalNotes(const QString &str) { (void) str; }
    virtual const QString getOtherData() const { return QString(); }
    virtual void setOtherData(const QString &str) { (void) str; }

    virtual void setCurrentIdToShow(int id) { (void) id; }
    virtual void setParroquia(const QString &parroquia) { (void) parroquia; }
    virtual void setBookName(const QString &bookName) { (void) bookName; }

    //libro de bautismo **************************************************************
    virtual const QDate bornDate() const { return QDate(); }
    virtual const QString bornPlace() const { return QString(); }
    virtual const QDate baptismDate() const { return QDate(); }

    virtual const QString godMother() const { return QString(); }
    virtual const QString godFather() const { return QString(); }
    virtual const QString getMinister() const { return QString(); }

    virtual const QString father() const { return QString(); }
    virtual const QString fatherPlace() const { return QString(); }
    virtual const QString mother() const { return QString(); }
    virtual const QString motherPlace() const { return QString(); }

    virtual void setBornDate(const QDate &date) { (void) date; }
    virtual void setBornPlace(const QString &str) { (void) str; }
    virtual void setBaptismDate(const QDate &date) { (void) date; }
    virtual void setGodMother(const QString &str) { (void) str; }
    virtual void setGodFather(const QString &str) { (void) str; }
    virtual void setMinister(const QString &str) { (void) str; }
    virtual void setFather(const QString &str) { (void) str; }
    virtual void setFatherPlace(const QString &str) { (void) str; }
    virtual void setMother(const QString &str) { (void) str; }
    virtual void setMotherPlace(const QString &str) { (void) str; }

    //abuelos paternos
    virtual const QString paternalGrandPa() const { return QString(); }
    virtual const QString paternalGrandPaPlace() const { return QString(); }
    virtual const QString paternalGrandMa() const { return QString(); }
    virtual const QString paternalGrandMaPlace() const { return QString(); }

    virtual void setPaternalGrandPa(const QString &str) { (void) str; }
    virtual void setPaternalGrandPaPlace(const QString &str) { (void) str; }
    virtual void setPaternalGrandMa(const QString &str) { (void) str; }
    virtual void setPaternalGrandMaPlace(const QString &str) { (void) str; }

    //abuelos maternos
    virtual const QString maternalGrandPa() const { return QString(); }
    virtual const QString maternalGrandPaPlace() const { return QString(); }
    virtual const QString maternalGrandMa() const { return QString(); }
    virtual const QString maternalGrandMaPlace() const { return QString(); }

    virtual void setMaternalGrandPa(const QString &str) { (void) str; }
    virtual void setMaternalGrandPaPlace(const QString &str) { (void) str; }
    virtual void setMaternalGrandMa(const QString &str) { (void) str; }
    virtual void setMaternalGrandMaPlace(const QString &str) { (void) str; }

    //libro de matrimonios ******************************************************************
    virtual const QString getMalePerson() const { return QString(); }
    virtual void setMalePerson(const QString &str) { (void) str; }
    virtual const QString getFemalePerson() const { return QString(); }
    virtual void setFemalePerson(const QString &str) { (void) str; }

    virtual const QString maleBornPlace() const { return QString(); }
    virtual void setMaleBornPlace(const QString &str) { (void) str; }
    virtual const QString femaleBornPlace() const { return QString(); }
    virtual void setFemaleBornPlace(const QString &str) { (void) str; }

    virtual const QDate marriageDate() const { return QDate(); }
    virtual void setMarriageDate(const QDate &date) { (void) date; }

    virtual const QString maleFather() const { return QString(); }
    virtual void setMaleFather(const QString &str) { (void) str; }
    virtual const QString maleMother() const { return QString(); }
    virtual void setMaleMother(const QString &str) { (void) str; }
    virtual const QString femaleFather() const { return QString(); }
    virtual void setFemaleFather(const QString &str) { (void) str; }
    virtual const QString femaleMother() const { return QString(); }
    virtual void setFemaleMother(const QString &str) { (void) str; }

    virtual const QString maleWitness() const { return QString(); }
    virtual void setMaleWitness(const QString &str) { (void) str; }
    virtual const QString femaleWitness() const { return QString(); }
    virtual void setFemaleWitness(const QString &str) { (void) str; }

    virtual const QString maleGodfather() const { return QString(); }
    virtual void setMaleGodfather(const QString &str) { (void) str; }
    virtual const QString femaleGodmother() const { return QString(); }
    virtual void setFemaleGodmother(const QString &str) { (void) str; }

    // virtual const QString getMinister() const { return QString(); } //ya esta
    //libro de defunciones ********************************************************************
    virtual const QDate burialDate() const { return QDate(); }
    virtual void setBurialDate(const QDate &date) { (void) date; }
    virtual const QDate dateOfDeath() const { return QDate(); }
    virtual void setDateOfDeath(const QDate &date) { (void) date; }
    virtual const QString causeOfDeath() const { return QString(); }
    virtual void setCauseOfDeath(const QString &str) { (void) str; }

    virtual const QString age() const { return QString(); }
    virtual void setAge(const QString &str) { (void) str; }

    //libro de confirmaciones *****************************************************************
    virtual const QDate confirmationDate() const { return QDate(); }
    virtual void setConfirmationDate(const QDate &date) { (void) date; }
    virtual const QString godFatherOrMother() const { return QString(); }
    virtual void setGodFatherOrMother(const QString &str) { (void) str; }
    virtual const QString minister() const { return QString(); }
    // virtual void setMinister(const QString &str) { (void) str; }

signals:
    void widgetClosed(bool save);
};

#endif // BASENEWPERSONWIDG_H
