#include "dbwidget.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

void DBWidget::showParrName(const QString parr)
{
    parroq->setText(tr("Parroquia: <h3><br/><b>%1</b></h3>").arg(parr));
    parroq->show();
}


QString DBWidget::askParroq()
{
    QString parr;
    do {
        parr=
            QInputDialog::getText(this, tr("Parroquia"),
                                  tr("Introduce el nombre completo de la parroquia\n\n"
                                     "(No puedes cancelar esto porque es necesario\n"
                                     "para el resto del trabajo)"));
    } while (parr.isEmpty());
    showParrName(parr);
    emit setParrName(parr);

    return parr;
}

DBWidget::DBWidget(QWidget *parent)
    : QWidget{parent}
{
    createDbBtn=new QPushButton(tr("Crear la Base\n"
                                     "de Datos"), this);
    createDbBtn->setIcon(QIcon(":/Icons/create_db.svg"));
    createDbBtn->setIconSize(QSize(24,24));

    openDbBtn=new QPushButton(tr("Abrir\n"
                                   "Base de Datos"),this);
    openDbBtn->setIcon(QIcon(":/Icons/folder.svg"));
    openDbBtn->setIconSize(QSize(24,24));
    removeDBBtn=new QPushButton(tr("Borrar la\n"
                                     "Base de Datos."), this);
    removeDBBtn->setEnabled(false);

    makeDBCopy=new QPushButton(tr("Hacer Salva de\n"
                                    "la Base de Datos"),this);
    makeDBCopy->setIcon(QIcon(":/Icons/makeCopy.svg"));
    makeDBCopy->hide();

    parroq = new QLabel("",this);
    parroq->hide();

    QHBoxLayout *dbBtns1=new QHBoxLayout;
    dbBtns1->addWidget(createDbBtn);
    dbBtns1->addWidget(openDbBtn);
    dbBtns1->addWidget(removeDBBtn);
    dbBtns1->addWidget(makeDBCopy);
    QVBoxLayout *dbBtns=new QVBoxLayout;
    dbBtns->addWidget(parroq);
    dbBtns->addLayout(dbBtns1);

    sh=new ShowOrHideBtns(createDbBtn, openDbBtn, removeDBBtn);
    sh->readCreatedFile();

    connect(makeDBCopy, &QPushButton::clicked, this, &DBWidget::makeAnEntireDBCopy);
    connect(createDbBtn, &QPushButton::clicked, this, [this](){
        // Usar un diálogo de "guardar" para elegir carpeta y nombre
        filePath = QFileDialog::getSaveFileName(
            this,
            tr("Crea un Directorio y la Nueva Base de Datos"),
            QDir::homePath() + QDir::separator() + "nueva_base.db",
            tr("Bases SQLite (*.db);;Todos los archivos (*)"));

        if (filePath.isEmpty())
            return; // el usuario canceló

        // Asegurar extensión .db si falta
        QFileInfo fi(filePath);
        if (fi.suffix().isEmpty())
            filePath += ".db";

        qDebug() << "Crear DB en:" << filePath;

        emit openDBbyCreateDB(filePath);

        if (sh) sh->createTheCreatedFile();
    });

    connect(openDbBtn, &QPushButton::clicked,
            this, [this](){
                filePath = QFileDialog::getOpenFileName(
                    this,
                    tr("Abrir Base de Datos"),
                    QDir::homePath(),
                    tr("Bases SQLite (*.db);;Todos los archivos (*)"));

                if (filePath.isEmpty())
                    return; // el usuario canceló

                emit openDBbyOpenDBButton(filePath);
            });

    setLayout(dbBtns);
}
