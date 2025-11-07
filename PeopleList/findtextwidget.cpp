#include "findtextwidget.h"
#include "ui_findtextwidget.h"
#include <QDebug>


FindTextWidget::FindTextWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::findTextWidget)
{
    ui->setupUi(this);
    ui->lineEdit->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->find->hide();
    ui->lineEdit->setToolTip(tr("Haz clic 3 veces para escribir\n"
                                "Se distinguen Las tildes mayúsculas de las minúsculas.\n"
                                "Presiona Enter para ejecutar la búsqueda"));
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->allWords->hide();
    ui->allWords->setToolTip(tr("Si desactivas esta opción mostrará resultados de\n"
                                "al menos una de las palabras que introduzcas"));
    connect(ui->findBtn,&QPushButton::clicked,this, &FindTextWidget::on_findBtn_clicked);
}

FindTextWidget::~FindTextWidget()
{
    delete ui;
}

const QString FindTextWidget::buttonText() const {
    return ui->findBtn->text();
}



void FindTextWidget::on_lineEdit_returnPressed()
{
    ui->lineEdit->hide();
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->allWords->hide();
    ui->find->hide();
    ui->label->setText(QString("Se muestran resultados en el libro "
                               "actual para\n\"%1\"").
                       arg(ui->lineEdit->text()));
    ui->label->show();
    emit searchDesired(ui->lineEdit->text().toUtf8(), ui->radioButton->isChecked(),
                        ui->allWords->isChecked());
}


void FindTextWidget::on_findBtn_clicked()
{
    checked = !checked;
    if (checked)
    {
        ui->findBtn->setText(tr("Quitar búsqueda"));
        ui->findBtn->setIcon(QIcon());
        ui->lineEdit->show();
        ui->radioButton->show();
        ui->radioButton_2->show();
        ui->allWords->show();
        ui->label_2->show();
        ui->find->show();
    }
    else {
        ui->findBtn->setText(tr("Buscar"));
        ui->findBtn->setIcon(QIcon(":/Icons/find.svg"));
        ui->lineEdit->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
        ui->allWords->hide();
        ui->find->hide();
        emit returnedToNormalView();
    }
}


void FindTextWidget::on_find_clicked()
{
    on_lineEdit_returnPressed();
}

