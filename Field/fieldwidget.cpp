#include "fieldwidget.h"

#include <QVBoxLayout>

//app
#include "stringforfieldwidget.h"
#include "Field/stringforfield.h"


FieldWidget::FieldWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout=new QVBoxLayout(this);

    QString s="Texto sin especificar";
    StringForField *model=new StringForField(s);
    StringForField *model2=new StringForField(s);

    StringForFieldWidget *title = new StringForFieldWidget(model);
    StringForFieldWidget *content = new StringForFieldWidget(model2);

    title->setIsTitle(true);

    mainLayout->addWidget(title);
    mainLayout->addWidget(content);

    setLayout(mainLayout);
}
