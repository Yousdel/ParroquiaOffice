#ifndef FILES_H
#define FILES_H

#include <QString>
#include <QVector>
#include "Books/createbookwidget.h"


#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMessageBox>




class Files
{
public:
    // Constructor: si filePath está vacío usa la ruta por defecto en AppConfigLocation
    explicit Files(const QString &filePath = QString());

    // Escribe el booleano 'true' indicando que la base de datos fue creada.
    // Devuelve true si la escritura tuvo éxito.
    bool writeDatabaseIsCreated();

    // Lee el booleano del archivo. Si la lectura es correcta devuelve true y
    // coloca el valor en 'created'. Si no existe/ocurre error devuelve false.
    bool readCreatedDBFile(bool &created);

    bool writeCurrentTable(const QString &currTable);

    bool readCurrentTable(QString &currTable);

    bool readBooksList(QVector<QString> &list);
    bool writeBooksList(const QVector<QString> &list);
    bool readBooksEntireNamesList(QVector<QString> &list);
    bool writeBooksEntireNamesList(const QVector<QString> &list);
    bool readBooksTypes(QVector<CreateBookWidget::BookType> &types);
    bool writeBooksTypes(const QVector<CreateBookWidget::BookType> &types);

    bool readParroquia(QString &parroquia);
    bool writeParroquia(const QString &parroquia);

    static bool copyDirectory(const QString &sourcePath, const QString &destPath) {
        QDir sourceDir(sourcePath);
        QDir destDir(destPath);

        // Crear el directorio de destino si no existe
        if (!destDir.exists()) {
            destDir.mkpath(destPath);
        }

        // Obtener una lista de archivos y directorios en el directorio de origen
        foreach (QString file, sourceDir.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
            QFile::copy(sourceDir.filePath(file), destDir.filePath(file));
        }

        foreach (QString dir, sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
            copyDirectory(sourceDir.filePath(dir), destDir.filePath(dir));
        }
        return true;
    }
private:
    QString m_filePath;
};

#endif // FILES_H
