#include "lineeditWregexpval.h"
#include "ui_lineeditWregexpval.h"


#include <QRegularExpression>
#include <QRegularExpressionValidator>



LineEditWReExpVal::LineEditWReExpVal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QRegularExpression rx("^[A-Z][A-Z0-9]*$");
    auto *validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit->setValidator(validator);

    // Forzar mayúsculas al editar (maneja teclas y pegado)
    connect(ui->lineEdit, &QLineEdit::textEdited,
            this, [this](const QString &text){
        QString up = text.toUpper();
        if (up != text) {
            int pos = ui->lineEdit->cursorPosition();
            ui->lineEdit->setText(up);
            ui->lineEdit->setCursorPosition(qMin(pos, up.size()));
        }
    });

}


const QString LineEditWReExpVal::text() const
{
    return ui->lineEdit->text();
}

LineEditWReExpVal::~LineEditWReExpVal()
{
    delete ui;
}
