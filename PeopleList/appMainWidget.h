#ifndef APPMAINWIDGET_H
#define APPMAINWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

#include "Tools/files.h"


class ShowOrHideBtns;
class DatabaseTableView;
class SelectBookWidget;
class CreateBookWidget;
class FindTextWidget;
class DropTableWidget;

/**
 * @brief Widget con y para manipular el listado de personas de un libro
 */
class AppMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AppMainWidget(QWidget *parent = nullptr);
    ~AppMainWidget();

private:
    DatabaseTableView *view=nullptr;
    QPushButton *createDbBtn;
    QPushButton *openDbBtn;
    QPushButton *removeDBBtn, *createBook;
    QLabel *parroq;
    SelectBookWidget *selectBookWidget=nullptr;
    DropTableWidget *dropBook=nullptr;
    ShowOrHideBtns *sh;
    QString textForSearch;
    QString filePath;
    CreateBookWidget *createBookWidget;
    FindTextWidget *findText;

    void takeDecissionForShowOrHideSuggestWidget();

    void hideOpenBtnAndTitle();
    
    void setBooksInView();
    
    void showParrName(const QString parr);



private slots:
    void showOrdered(const QString &book);


    int makeAnEntireDBCopy() {
        if (filePath.isEmpty()) {
            qWarning() << "filePath vacío";
            return 0;
        }

        QFileInfo fi(filePath);
        QString sourceDirPath;

        // Si filePath ya es una carpeta, tomamos esa carpeta;
        // si es un archivo, tomamos su directorio padre.
        if (fi.exists() && fi.isDir()) {
            sourceDirPath = fi.absoluteFilePath(); // la carpeta misma
        } else {
            sourceDirPath = fi.absolutePath(); // el directorio que contiene el archivo
        }

        if (sourceDirPath.isEmpty()) {
            qWarning() << "No se pudo determinar el directorio de origen a partir de:" << filePath;
            return 0;
        }

        QDir sourceDir(sourceDirPath);
        if (!sourceDir.exists()) {
            qWarning() << "Directorio de origen no existe:" << sourceDirPath;
            return 0;
        }

        // Selección de carpeta de destino
        QString destDirPath = QFileDialog::getExistingDirectory(nullptr, "Selecciona la carpeta de destino");
        if (destDirPath.isEmpty()) {
            return 0; // Salir si no se seleccionó ninguna carpeta
        }

        // Copiar la carpeta
        bool ok = Files::copyDirectory(sourceDirPath, destDirPath);
        if (ok) {
            qDebug() << "Copia completada de:" << sourceDirPath << "a:" << destDirPath;
            QMessageBox::information(this,
                                     tr("Éxito"),
                                     tr("Los archivos se han copiado exitosamente en %1")
                                         .arg(destDirPath));
        } else {
            qWarning() << "Error copiando de" << sourceDirPath << "a" << destDirPath;
            QMessageBox::critical(this,
                                     tr("Error"),
                                     tr("Los archivos no se han copiado correctamente en %1")
                                         .arg(destDirPath));
        }

        return ok ? 1 : 0;
    }



signals:
};

#endif // APPMAINWIDGET_H
