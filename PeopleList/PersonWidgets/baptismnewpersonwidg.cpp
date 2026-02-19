#include "baptismnewpersonwidg.h"
#include "ui_baptismnewpersonwidg.h"

BaptismNewPersonWidg::BaptismNewPersonWidg(QWidget *parent)
    : BaseNewPersonWidg(parent)
    , ui(new Ui::BaptismNewPersonWidg)
{
    ui->setupUi(this);
    setWindowTitle("Creando Persona para Libro de Bautismos");
}

BaptismNewPersonWidg::~BaptismNewPersonWidg()
{
    delete ui;
}

const QDate BaptismNewPersonWidg::bornDate() const
{
    return ui->bornDate->date();
}

const QString BaptismNewPersonWidg::bornPlace() const
{
    return ui->bornPlace->text();
}

const QDate BaptismNewPersonWidg::baptismDate() const
{
    return ui->baptismDate->date();
}

const QString BaptismNewPersonWidg::godMother() const
{
    return ui->godmother->text();
}

const QString BaptismNewPersonWidg::godFather() const
{
    return ui->godfather->text();
}

const QString BaptismNewPersonWidg::getMinister() const
{
    return ui->minister->text();
}

const QString BaptismNewPersonWidg::father() const
{
    return ui->father->text();
}

const QString BaptismNewPersonWidg::fatherPlace() const
{
    return ui->fatherPlace->text();
}

const QString BaptismNewPersonWidg::mother() const
{
    return ui->mother->text();
}

const QString BaptismNewPersonWidg::motherPlace() const
{
    return ui->motherPlace->text();
}

const QString BaptismNewPersonWidg::paternalGrandPa() const
{
    return ui->paternalGrandpa->text();
}

const QString BaptismNewPersonWidg::paternalGrandPaPlace() const
{
    return ui->patGrandpaPlace->text();
}

const QString BaptismNewPersonWidg::paternalGrandMa() const
{
    return ui->paternalGrandma->text();
}

const QString BaptismNewPersonWidg::paternalGrandMaPlace() const
{
    return ui->paternalGrandmaPlace->text();
}

const QString BaptismNewPersonWidg::maternalGrandPa() const
{
    return ui->maternalGrandpa->text();
}

const QString BaptismNewPersonWidg::maternalGrandPaPlace() const
{
    return ui->maternalgrandpaPlace->text();
}

const QString BaptismNewPersonWidg::maternalGrandMa() const
{
    return ui->maternalGrandma->text();
}

const QString BaptismNewPersonWidg::maternalGrandMaPlace() const
{
    return ui->maternalGrandmaPlace->text();
}

void BaptismNewPersonWidg::setBornDate(const QDate &date)
{
    ui->bornDate->setDate(date);
}

void BaptismNewPersonWidg::setBornPlace(const QString &str)
{
    ui->bornPlace->setText(str);
}

void BaptismNewPersonWidg::setBaptismDate(const QDate &date)
{
    ui->baptismDate->setDate(date);
}

void BaptismNewPersonWidg::setGodMother(const QString &str)
{
    ui->godmother->setText(str);
}

void BaptismNewPersonWidg::setGodFather(const QString &str)
{
    ui->godfather->setText(str);
}

void BaptismNewPersonWidg::setMinister(const QString &str)
{
    ui->minister->setText(str);
}

void BaptismNewPersonWidg::setFather(const QString &str)
{
    ui->father->setText(str);
}

void BaptismNewPersonWidg::setFatherPlace(const QString &str)
{
    ui->fatherPlace->setText(str);
}

void BaptismNewPersonWidg::setMother(const QString &str)
{
    ui->mother->setText(str);
}

void BaptismNewPersonWidg::setMotherPlace(const QString &str)
{
    ui->motherPlace->setText(str);
}

void BaptismNewPersonWidg::setPaternalGrandPa(const QString &str)
{
    ui->paternalGrandpa->setText(str);
}

void BaptismNewPersonWidg::setPaternalGrandPaPlace(const QString &str)
{
    ui->patGrandpaPlace->setText(str);
}

void BaptismNewPersonWidg::setPaternalGrandMa(const QString &str)
{
    ui->paternalGrandma->setText(str);
}

void BaptismNewPersonWidg::setPaternalGrandMaPlace(const QString &str)
{
    ui->paternalGrandmaPlace->setText(str);
}

void BaptismNewPersonWidg::setMaternalGrandPa(const QString &str)
{
    ui->maternalGrandpa->setText(str);
}

void BaptismNewPersonWidg::setMaternalGrandPaPlace(const QString &str)
{
    ui->maternalgrandpaPlace->setText(str);
}

void BaptismNewPersonWidg::setMaternalGrandMa(const QString &str)
{
    ui->maternalGrandma->setText(str);
}

void BaptismNewPersonWidg::setMaternalGrandMaPlace(const QString &str)
{
    ui->maternalGrandmaPlace->setText(str);
}

void BaptismNewPersonWidg::on_saveBtn_clicked()
{
    saveData(CreateBookWidget::GB);
    if (!setSaved()) {
        return;
    }
    // Validar que las fechas sean válidas
    if (!ui->baptismDate->date().isValid()) {
        QMessageBox::warning(this, "Error", "La fecha de bautismo no es válida");
        return;
    }
    if (!ui->bornDate->date().isValid()) {
        QMessageBox::warning(this, "Error", "La fecha de nacimiento no es válida");
        return;
    }
    if (!datesCoherency(ui->bornDate->date() <= ui->baptismDate->date(),
                       tr("La fecha de baustismo es anterior a la "
                          "de nacimiento de la persona.")))
        return;
    emit widgetClosed(true);
    close();
}


void BaptismNewPersonWidg::on_cancelBtn_clicked()
{
    emit widgetClosed(false);
    close();
}

COMMON_IMPLEMENTATIONS(BaptismNewPersonWidg)
