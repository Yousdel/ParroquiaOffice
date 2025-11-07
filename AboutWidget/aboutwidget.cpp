#include "aboutwidget.h"

//qt
#include <QVBoxLayout>
#include <QHBoxLayout>
//app
#include "littlefontlabel.h"
#include "AboutWidget/Widgets/label.h"
#include "AboutWidget/Widgets/button.h"
#include "AboutWidget/Widgets/image.h"


AboutWidget::AboutWidget(QWidget *parent):
    QWidget(parent, Qt::Window)
{
    setWindowTitle("Acerca de...");
}

void AboutWidget::setAppNameString(const QString &s)
{
    QString s_;
    if (s.length() >
            QString("e-mail (correo electrónico): ").
            length())
        s_= s + "\n";
    else
        s_= s;
    m_string=
            QString("%1 "
                    "es desarrollado por:\n\n\n"
                    "Ing. Yousdel Corvo Llanes\n\n"
                    "e-mail (correo electrónico): \n"
                    "yousdelc@gmail.com")
            .arg(s_);
}

void
AboutWidget::addWidgets()
{
    //fondo de pantalla
    Image *background=new Image(this,
                                0x404,0x250);
    if (!backgroundPixmapFilename.isEmpty())
        background->assignPixmap(
                backgroundPixmapFilename,
                0x404,0x250);

    QVBoxLayout *mainlayout=
            new QVBoxLayout(this);

    QHBoxLayout *layoutWithInfo=
            new QHBoxLayout();
    QLabel *icon=
            new QLabel("",this);
    if (!iconFileName.isEmpty())
        icon->setPixmap(QPixmap(iconFileName).
                    scaled(90,90,Qt::KeepAspectRatio));
    LittleFontLabel *info=
            new LittleFontLabel(m_string,this);
    info->setFont(
                QFont("DejaVu sans mono",0xc));

    QHBoxLayout *oklayout =
            new QHBoxLayout();
    Button *okbtn=
            new Button("OK", this);
    if (!btnBackgColor.isEmpty())
        okbtn->setBackgroundColor(btnBackgColor);
    if (!btnTextColor.isEmpty())
        okbtn->setTextColor(btnTextColor);
    if (!hvBgColor.isEmpty() && !hvBgColor.isEmpty())
        okbtn->setHoverColors(hvTxtColor,
                              hvBgColor);
    okbtn->show();

    oklayout->addStretch(0x1);
    oklayout->addWidget(okbtn);

    connect(okbtn, &Button::clicked,
            this, &AboutWidget::close);

    layoutWithInfo->addWidget(icon);
    layoutWithInfo->addWidget(info);
    mainlayout->addLayout(layoutWithInfo);
    mainlayout->addLayout(oklayout);
}
