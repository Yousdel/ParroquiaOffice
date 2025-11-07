#ifndef DARK_FILES_H
#define DARK_FILES_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

class DarkFiles : public QObject{

public:
    static
    bool writeToFile(const QString &m_filePath, bool dark=false )
    {
        QFile file(m_filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug()<<"no se pudo abrir " << m_filePath;
            QMessageBox::critical(nullptr,
                                  tr("Error de archivo"),
                                  tr("No se pudo salvar el modo día / "
                                     "noche en archivo."));
            return false;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_0);        
        out << dark;

        file.close();

        qDebug()<< "darkfiles::writeToFile() ejecutado exitosamente y archivo creado";
        return true;
    }

    static
    bool readFile(const QString &m_filePath, bool &dark)
    {
        QFile file(m_filePath);
        if (!file.exists()) {
            dark = false;
            return false; // no existe el archivo
        }
        if (!file.open(QIODevice::ReadOnly)) {
            dark = false;
            QMessageBox::critical(nullptr,
                                  tr("Error de archivo"),
                                  tr("No se pudo leer el modo día / "
                                     "noche del archivo."));
            return false; // error al abrir
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_0);
        bool ok = true;
        in >> dark;
        if (in.status() != QDataStream::Ok) {
            dark = false;
            ok = false;
        }

        file.close();
        qDebug()<< "readFile() ejecutado exitosamente y archivo leido.";
        return ok;
    }
};


#endif // DARK_FILES_H
