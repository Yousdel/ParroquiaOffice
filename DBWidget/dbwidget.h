#ifndef DBWIDGET_H
#define DBWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

#include "PeopleList/ShowOrHideBtns.h"
#include "PeopleList/Tools/files.h"



class QLabel;
/**
 * @brief The DBWidget class
 */
class DBWidget : public QWidget
{
    Q_OBJECT

private:
    QPushButton *createDbBtn;
    QPushButton *openDbBtn;
    QPushButton *removeDBBtn;
    QPushButton *makeDBCopy;
    QLabel *parroq;
    ShowOrHideBtns *sh;
    QString filePath;


public:
    explicit DBWidget(QWidget *parent = nullptr);
    ~DBWidget(){
        delete createDbBtn;
        delete openDbBtn;
        delete removeDBBtn;
        delete sh;
    }
    void hideOpenBtn() { openDbBtn->hide(); }
    void showParrName(const QString parr);

    void showMakeDBCopy(){
        makeDBCopy->show();
    }

public slots:
    QString askParroq();

private slots:
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
    void openDB(QString filePath);
    void openDBbyCreateDB(QString filePath);
    void openDBbyOpenDBButton(QString filePath);
    void setParrName(QString parr);
};

#endif // DBWIDGET_H
