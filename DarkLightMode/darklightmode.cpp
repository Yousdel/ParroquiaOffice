#include "darklightmode.h"
#include <QPushButton>
#include <QVBoxLayout>




DarkLightMode::DarkLightMode(QString pathWhereSaveStatus, QWidget *parent) :
    QWidget(parent), m_path(pathWhereSaveStatus)
{
    QVBoxLayout *layout= new QVBoxLayout(this);
    toggleDarkBtn = new QPushButton(tr("Modo noche"),this);
    toggleDarkBtn->setIcon(QIcon(":/dark_Icons/moon.svg"));

    connect(toggleDarkBtn, &QPushButton::clicked,
            this, &DarkLightMode::toggleDark);

    bool c=false;
    DarkFiles::readFile(pathWhereSaveStatus ,c);
    if (c) {  //si se guardo que estaba en modo oscuro
        toggleDark();
    }

    layout->addWidget(toggleDarkBtn);

    setLayout(layout);
}
