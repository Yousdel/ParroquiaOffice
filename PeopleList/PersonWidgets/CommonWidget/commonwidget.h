#ifndef COMMONWIDGET_H
#define COMMONWIDGET_H

#include <QWidget>

#define COMMON_GETTERS \
virtual const QString getName() const;\
virtual const QString getFirstName() const;\
virtual const QString getLastName() const;\
virtual const QString getParroquia() const;\
virtual const QString getBookName() const;\
virtual const QString getInscriptionNumber() const;\
virtual const QString getFolio() const;\
virtual const QString getMarginalsNotes() const;\
virtual const QString getOtherData() const;\
virtual void setName(const QString &str) ;\
virtual void setFirstName(const QString &str) ;\
virtual void setLastName(const QString &str) ;\
virtual void setCurrentIdToShow(int id);\
virtual void setParroquia(const QString &parroquia);\
virtual void setBookName(const QString &bookName);\
virtual void setFolio(const QString &str);\
virtual void setInscriptionNumber(const QString &str);\
virtual void setMarginalNotes(const QString &str);\
virtual void setOtherData(const QString &str) ;\
void hideSinglePersonCommonWidget();

#define COMMON_IMPLEMENTATIONS(Cl)\
void Cl::hideSinglePersonCommonWidget(){\
    ui->commonWidget->hideSinglePersonCommonWidget();\
}\
void Cl::setCurrentIdToShow(int id)\
{\
    ui->commonWidget->setCurrentIdToShow(id);\
}\
void Cl::setParroquia(const QString &parroquia)\
{\
    ui->commonWidget->setParroquia(parroquia);\
}\
void Cl::setBookName(const QString &bookName)\
{\
    ui->commonWidget->setBookName(bookName);\
}\
const QString Cl::getName() const\
{\
    return ui->commonWidget->getName();\
}\
const QString Cl::getFirstName() const\
{\
    return ui->commonWidget->getFirstName();\
}\
const QString Cl::getLastName() const\
{\
    return ui->commonWidget->getLastName();\
}\
void Cl::setName(const QString &str)\
{\
    ui->commonWidget->setName(str);\
}\
void Cl::setFirstName(const QString &str)\
{\
    ui->commonWidget->setFirstName(str);\
}\
void Cl::setLastName(const QString &str){\
    ui->commonWidget->setLastName(str);\
}\
void Cl::setFolio(const QString &str){\
    ui->commonWidget->setFolio(str);\
}\
void Cl::setInscriptionNumber(const QString &str){\
    ui->commonWidget->setInscriptionNumber(str);\
}\
const QString Cl::getInscriptionNumber() const\
{\
    return ui->commonWidget->getInscriptionNumber();\
}\
const QString Cl::getParroquia() const\
{\
    return ui->commonWidget->getParroquia();\
}\
const QString Cl::getBookName() const\
{\
    return ui->commonWidget->getBookName();\
}\
const QString Cl::getFolio() const\
{\
    return ui->commonWidget->getFolio();\
}\
const QString Cl::getMarginalsNotes() const\
{\
    return ui->commonWidget->getMarginalsNotes();\
}\
const QString Cl::getOtherData() const\
{\
    return ui->commonWidget->getOtherData();\
}\
void Cl::setMarginalNotes(const QString &str){\
    ui->commonWidget->setMarginalNotes(str);\
}\
void Cl::setOtherData(const QString &str) {\
    ui->commonWidget->setOtherData(str);\
}

namespace Ui {
class CommonWidget;
}

class CommonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommonWidget(QWidget *parent = nullptr);
    ~CommonWidget();

    COMMON_GETTERS
private:
    Ui::CommonWidget *ui;
};

#endif // COMMONWIDGET_H
