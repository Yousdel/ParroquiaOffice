#include "createbookwidget.h"
#include "ui_createbookwidget.h"

#include <QMessageBox>

CreateBookWidget::CreateBookWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateBookWidget)
{
    ui->setupUi(this);
    setWindowTitle("Creando Libro");
    on_comboBox_currentTextChanged(ui->comboBox->currentText());
}

CreateBookWidget::~CreateBookWidget()
{
    delete ui;
}

const QString CreateBookWidget::entireName() const
{
    return ui->entireName->text();
}

const QString CreateBookWidget::desiredSigla() const
{
    return ui->sigla->text();
}

CreateBookWidget::BookType CreateBookWidget::desiredType() const
{
    return static_cast<BookType>(ui->comboBox->currentIndex());
}

void CreateBookWidget::on_createBtn_clicked()
{
    if (ui->entireName->text().isEmpty() ||
        ui->sigla->text().isEmpty()) {
        QMessageBox::warning(this, tr("Campos Vacíos"),
                             tr("No puedes crear un libro si "
                                "has dejado campos vacíos en este formulario. "
                                "Todos son necesarios para el resto del trabajo."));
        return;
    }
    emit createBook(static_cast<BookType>(ui->comboBox->currentIndex()),                
                ui->sigla->text(), ui->entireName->text());
    emit widgetClosed();
    close();
}


void CreateBookWidget::on_cancelBtn_clicked()
{
    emit widgetClosed();
    close();
}


void CreateBookWidget::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->entireName->setToolTip(tr("Complete el nombre completo del libro"));
    if (!arg1.contains(tr("Personalizado")))
    {
        ui->entireName->setText(arg1);
    }
    else {
        ui->entireName->setText(QString());
    }
}


const QString CreateBookWidget::stringForType(CreateBookWidget::BookType type)
{
    QStringList l;
    l << "Libro General de Bautismos";
    l << "Libro Suplementario de Bautismos";
    l << "Libro General de Matrimonios";
    l << "Libro Suplementario de Matrimonios";
    l << "Libro General de Defunciones";
    l << "Libro Suplementario de Defunciones";
    l << "Libro General de Confirmaciones";
    l << "Libro Suplementario de Confirmaciones";

    l << "Libro de Bautismos Personalizado";
    l << "Libro de Matrimonios Personalizado";
    l << "Libro de Defunciones Personalizado";
    l << "Libro de Confirmaciones Personalizado";
    return l.at(static_cast<int>(type));
}
