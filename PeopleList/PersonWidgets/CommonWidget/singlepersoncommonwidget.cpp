#include "singlepersoncommonwidget.h"
#include "ui_singlepersoncommonwidget.h"

SinglePersonCommonWidget::SinglePersonCommonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SinglePersonCommonWidget)
{
    ui->setupUi(this);
}

SinglePersonCommonWidget::~SinglePersonCommonWidget()
{
    delete ui;
}

const QString SinglePersonCommonWidget::getName() const
{
    return ui->name->text();
}

const QString SinglePersonCommonWidget::getFirstName() const
{
    return ui->firstName->text();
}

const QString SinglePersonCommonWidget::getLastName() const
{
    return ui->lastName->text();
}

void SinglePersonCommonWidget::setName(const QString &str)
{
    ui->name->setText(str);
}

void SinglePersonCommonWidget::setFirstName(const QString &str)
{
    ui->firstName->setText(str);
}

void SinglePersonCommonWidget::setLastName(const QString &str)
{
    ui->lastName->setText(str);
}


