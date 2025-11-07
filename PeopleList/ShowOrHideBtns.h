#ifndef SHOWORHIDEBTNS_H
#define SHOWORHIDEBTNS_H

#include <QPushButton>
#include <QDir>
#include "Tools/files.h"

/**
 * @brief mostrar u ocultar los tres botones en dependencia
 * del estado de la base de datos
 */
class ShowOrHideBtns
{
public:
    ShowOrHideBtns(QPushButton *create,
                         QPushButton *open,
                         QPushButton *remove) :
        _create(create),
        _open(open),
        _remove(remove)    { }
    void readCreatedFile(){
        bool cr;
        Files f(path);
        if (f.readCreatedDBFile(cr)){
            _create->setVisible(!cr);
            _open->setVisible(cr);
            _remove->setVisible(cr);
        } else {
            //si no existe
            _create->show();
            _open->hide();
            _remove->hide();
        }
    }

    void createTheCreatedFile(){
        Files f(path);
        if (f.writeDatabaseIsCreated())
            readCreatedFile();
    }

private:
    QPushButton *_create;
    QPushButton *_open;
    QPushButton *_remove;

    QString path=QDir::homePath()+"/parroquia_office/dbcreated.txt";
};

#endif // SHOWORHIDEBTNS_H
