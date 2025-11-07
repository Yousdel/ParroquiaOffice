#include "button.h"

Button::Button(const QString &text, QWidget *parent) :
    QPushButton(text,parent)
{
    background_color="purple";
    text_color="white";
    hvTxtColor="yellow";
    hvBgColor="black";
}

void Button::setAppareance()
{
    setFont(QFont("Eras",0xf));
    setStyleSheet(
                QString (
                "QPushButton {"
                "background-color: %1;"
                "color: %2;"
                "}"
                "QPushButton:hover {"
                "background-color: %3;"
                "color: %4;"
                "}").
                arg(background_color,
                    text_color,
                    hvBgColor,
                    hvTxtColor
                    ));
}
