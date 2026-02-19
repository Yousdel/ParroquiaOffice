#include "confirmationnewpersonwidg.h"
#include "ui_confirmationnewpersonwidg.h"

ConfirmationNewPersonWidg::ConfirmationNewPersonWidg(QWidget *parent)
    : BaseNewPersonWidg(parent)
    , ui(new Ui::ConfirmationNewPersonWidg)
{
    ui->setupUi(this);
    setWindowTitle("Agregar Nueva Persona a Libro de Confirmaciones");
}

ConfirmationNewPersonWidg::~ConfirmationNewPersonWidg()
{
    delete ui;
}


const QDate ConfirmationNewPersonWidg::confirmationDate() const
{
    return ui->confirmationDate->date();
}

const QString ConfirmationNewPersonWidg::godFatherOrMother() const
{
    return ui->godFaOrMother->text();
}

const QString ConfirmationNewPersonWidg::minister() const
{
    return ui->minister->text();
}

void ConfirmationNewPersonWidg::setConfirmationDate(const QDate &date)
{
    ui->confirmationDate->setDate(date);
}

void ConfirmationNewPersonWidg::setGodFatherOrMother(const QString &str)
{
    ui->godFaOrMother->setText(str);
}

void ConfirmationNewPersonWidg::setMinister(const QString &str)
{
    ui->minister->setText(str);
}

void ConfirmationNewPersonWidg::on_pushButton_clicked()
{
    if (!ui->confirmationDate->date().isValid()) {
        QMessageBox::warning(this, "Error", "La fecha de confirmación no es válida");
        return;
    }
    // --guardar
    saveData(CreateBookWidget::GC);
    if (!setSaved()) {
        return;
    }
    emit widgetClosed(true);
    close();

}


void ConfirmationNewPersonWidg::on_cancelBtn_clicked()
{
    emit widgetClosed(false);
    close();
}

COMMON_IMPLEMENTATIONS(ConfirmationNewPersonWidg)
