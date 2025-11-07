#include "littlefontlabel.h"

LittleFontLabel::LittleFontLabel(QWidget *parent):
    QLabel(parent)
{
    setLittleFont();
}

LittleFontLabel::LittleFontLabel(const QString &text, QWidget *parent):
    QLabel(text, parent)
{
    setLittleFont();
}

void
LittleFontLabel::setLittleFont()
{
    setFont(QFont("DejaVu sans mono",0x9));

}
