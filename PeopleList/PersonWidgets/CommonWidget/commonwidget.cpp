#include "commonwidget.h"
#include "ui_commonwidget.h"

CommonWidget::CommonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CommonWidget)
{
    ui->setupUi(this);
}

CommonWidget::~CommonWidget()
{
    delete ui;
}

void CommonWidget::setCurrentIdToShow(int id)
{
    ui->idLabel->setText(
        QString(tr("Id : %1")).arg(id));
}

const QString CommonWidget::getName() const
{
    return ui->singlePersonWidg->getName();
}

const QString CommonWidget::getFirstName() const
{
    return ui->singlePersonWidg->getFirstName();
}

const QString CommonWidget::getLastName() const
{
    return ui->singlePersonWidg->getLastName();
}

const QString CommonWidget::getInscriptionNumber() const
{
    return ui->inscriptionNumber->text();
}

const QString CommonWidget::getParroquia() const
{
    return ui->parroquia->text();
}

void CommonWidget::setParroquia(const QString &parroquia)
{
    ui->parroquia->setText(parroquia);
}

void CommonWidget::setBookName(const QString &bookName)
{
    ui->book->setText(bookName);
}

void CommonWidget::setName(const QString &str)
{
    ui->singlePersonWidg->setName(str);
}

void CommonWidget::setFirstName(const QString &str)
{
    ui->singlePersonWidg->setFirstName(str);
}
void CommonWidget::setLastName(const QString &str)
{
    ui->singlePersonWidg->setLastName(str);
}

void CommonWidget::setFolio(const QString &str)
{
    ui->folio->setText(str);
}

void CommonWidget::setInscriptionNumber(const QString &str)
{
    ui->inscriptionNumber->setText(str);
}

void CommonWidget::hideSinglePersonCommonWidget()
{
    ui->singlePersonWidg->hide();
}

void CommonWidget::setMarginalNotes(const QString &str){
    ui->marginNotes->setPlainText(str);
}

void CommonWidget::setOtherData(const QString &str){
    ui->extraData->setPlainText(str);
}

const QString CommonWidget::getBookName() const
{
    return ui->book->text();
}

const QString CommonWidget::getFolio() const
{
    return ui->folio->text();
}

const QString CommonWidget::getMarginalsNotes() const
{
    return ui->marginNotes->document()->toPlainText();
}

const QString CommonWidget::getOtherData() const
{
    return ui->extraData->document()->toPlainText();
}

