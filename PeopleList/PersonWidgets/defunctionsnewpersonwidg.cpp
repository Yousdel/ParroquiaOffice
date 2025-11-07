#include "defunctionsnewpersonwidg.h"
#include "ui_defunctionsnewpersonwidg.h"

DefunctionsNewPersonWidg::DefunctionsNewPersonWidg(QWidget *parent)
    : BaseNewPersonWidg(parent)
    , ui(new Ui::DefunctionsNewPersonWidg)
{
    ui->setupUi(this);
}

DefunctionsNewPersonWidg::~DefunctionsNewPersonWidg()
{
    delete ui;
}

const QDate DefunctionsNewPersonWidg::burialDate() const
{
    return ui->burialDate->date();
}

const QDate DefunctionsNewPersonWidg::dateOfDeath() const
{
    return ui->dateOfDeath->date();
}

const QString DefunctionsNewPersonWidg::causeOfDeath() const
{
    return ui->causeOfDeath->text();
}

const QString DefunctionsNewPersonWidg::age() const
{
    return ui->age->text();
}

const QString DefunctionsNewPersonWidg::father() const
{
    return ui->father->text();
}

const QString DefunctionsNewPersonWidg::mother() const
{
    return ui->mother->text();
}

const QString DefunctionsNewPersonWidg::minister() const
{
    return ui->minister->text();
}

void DefunctionsNewPersonWidg::setBurialDate(const QDate &date)
{
    ui->burialDate->setDate(date);
}

void DefunctionsNewPersonWidg::setDateOfDeath(const QDate &date)
{
    ui->dateOfDeath->setDate(date);
}

void DefunctionsNewPersonWidg::setCauseOfDeath(const QString &str)
{
    ui->causeOfDeath->setText(str);
}

void DefunctionsNewPersonWidg::setAge(const QString &str)
{
    ui->age->setText(str);
}

void DefunctionsNewPersonWidg::setFather(const QString &str)
{
    ui->father->setText(str);
}

void DefunctionsNewPersonWidg::setMother(const QString &str)
{
    ui->mother->setText(str);
}

void DefunctionsNewPersonWidg::setMinister(const QString &str)
{
    ui->minister->setText(str);
}



void DefunctionsNewPersonWidg::on_saveBtn_clicked()
{
    saveData(CreateBookWidget::GD);
    if (!setSaved()) {
        return;
    }

    if (!datesCoherency(ui->dateOfDeath->date() <= ui->burialDate->date(),
                        tr("La fecha de excequias es anterior a la "
                           "fecha de muerte del difunto.")))
        return;
    emit widgetClosed(true);
    close();
}

void DefunctionsNewPersonWidg::on_cancelBtn_clicked()
{
    emit widgetClosed(false);
    close();
}


COMMON_IMPLEMENTATIONS(DefunctionsNewPersonWidg)
