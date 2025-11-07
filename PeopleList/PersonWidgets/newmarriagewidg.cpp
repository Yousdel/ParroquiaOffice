#include "newmarriagewidg.h"
#include "ui_newmarriagewidg.h"

NewMarriageWidg::NewMarriageWidg(QWidget *parent)
    : BaseNewPersonWidg(parent)
    , ui(new Ui::MarryNewPersonWidg)
{
    ui->setupUi(this);
    hideSinglePersonCommonWidget();
}

NewMarriageWidg::~NewMarriageWidg()
{
    delete ui;
}

const QString NewMarriageWidg::getMalePerson() const
{
    return ui->male->text();
}

const QString NewMarriageWidg::getFemalePerson() const
{
    return ui->female->text();
}

const QString NewMarriageWidg::maleBornPlace() const
{
    return ui->maleBornPlace->text();
}

const QString NewMarriageWidg::femaleBornPlace() const
{
    return ui->femaleBornPlace->text();
}

const QDate NewMarriageWidg::marriageDate() const
{
    return ui->marriageDate->date();
}

const QString NewMarriageWidg::maleFather() const
{
    return ui->maleFather->text();
}

const QString NewMarriageWidg::maleMother() const
{
    return ui->maleMother->text();
}

const QString NewMarriageWidg::femaleFather() const
{
    return ui->femaleFather->text();
}

const QString NewMarriageWidg::femaleMother() const
{
    return ui->femaleMother->text();
}

const QString NewMarriageWidg::maleWitness() const
{
    return ui->maleWitness->text();
}

const QString NewMarriageWidg::femaleWitness() const
{
    return ui->femaleWitness->text();
}

const QString NewMarriageWidg::maleGodfather() const
{
    return ui->maleGodFather->text();
}

const QString NewMarriageWidg::femaleGodmother() const
{
    return ui->femaleGodMother->text();
}

const QString NewMarriageWidg::getMinister() const
{
    return ui->minister->text();
}

void NewMarriageWidg::setMalePerson(const QString &str)
{
    ui->male->setText(str);
}

void NewMarriageWidg::setFemalePerson(const QString &str)
{
    ui->female->setText(str);
}

void NewMarriageWidg::setMaleBornPlace(const QString &str)
{
    ui->maleBornPlace->setText(str);
}

void NewMarriageWidg::setFemaleBornPlace(const QString &str)
{
    ui->femaleBornPlace->setText(str);
}

void NewMarriageWidg::setMarriageDate(const QDate &date)
{
    ui->marriageDate->setDate(date);
}

void NewMarriageWidg::setMaleFather(const QString &str)
{
    ui->maleFather->setText(str);
}

void NewMarriageWidg::setMaleMother(const QString &str)
{
    ui->maleMother->setText(str);
}

void NewMarriageWidg::setFemaleFather(const QString &str)
{
    ui->femaleFather->setText(str);
}

void NewMarriageWidg::setFemaleMother(const QString &str)
{
    ui->femaleMother->setText(str);
}

void NewMarriageWidg::setMaleWitness(const QString &str)
{
    ui->maleWitness->setText(str);
}

void NewMarriageWidg::setFemaleWitness(const QString &str)
{
    ui->femaleWitness->setText(str);
}

void NewMarriageWidg::setMaleGodfather(const QString &str)
{
    ui->maleGodFather->setText(str);
}

void NewMarriageWidg::setFemaleGodmother(const QString &str)
{
    ui->femaleGodMother->setText(str);
}

void NewMarriageWidg::setMinister(const QString &str)
{
    ui->minister->setText(str);
}



void NewMarriageWidg::on_saveBtn_clicked()
{
    saveData(CreateBookWidget::GM);
    if (!setSaved()) {
        return;
    }
    emit widgetClosed(true);
    close();
}


void NewMarriageWidg::on_cancelBtn_clicked()
{
    emit widgetClosed(false);
    close();
}


COMMON_IMPLEMENTATIONS(NewMarriageWidg)
