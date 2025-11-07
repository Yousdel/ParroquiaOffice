#include "files.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDebug>

Files::Files(const QString &filePath)
{
    if (!filePath.isEmpty()) {
        m_filePath = filePath;
        QFileInfo fi(filePath);        
        QDir().mkpath(fi.path());
        qDebug() << "creado directorio "<<fi.path();
    } else {
        // Ubicación por defecto: AppConfigLocation (ej: ~/.config/YourApp/ o similar)
        QString configDir =
                QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
        if (configDir.isEmpty()) {
            // fallback al directorio actual si no se puede obtener AppConfigLocation
            configDir = QDir::currentPath();
        }
        QDir().mkpath(configDir);
        m_filePath = QDir(configDir).filePath(QStringLiteral("db_created.flag"));
    }
}

bool Files::writeDatabaseIsCreated()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"no se pudo abrir "<<m_filePath;
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);
    bool created = true;
    out << created;

    file.close();

    qDebug()<< "writeDatabaseIsCreated() ejecutado exitosamente y archivo creado";
    return true;
}

bool Files::readCreatedDBFile(bool &created)
{
    QFile file(m_filePath);
    if (!file.exists()) {
        created = false;
        return false; // no existe el archivo
    }
    if (!file.open(QIODevice::ReadOnly)) {
        created = false;
        return false; // error al abrir
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    bool ok = true;
    in >> created;
    if (in.status() != QDataStream::Ok) {
        created = false;
        ok = false;
    }

    file.close();
    qDebug()<< "readFile() ejecutado exitosamente y archivo leido.";
    return ok;
}

bool Files::writeCurrentTable(const QString &currTable)
{
    QFile file(m_filePath+"curr_t.txt");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"writeCurrentTable() no se pudo abrir "<<m_filePath;
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_0);
    out << currTable;

    file.close();

    qDebug()<< "writeCurrentTable() ejecutado exitosamente y archivo creado";
    return true;
}

bool Files::readCurrentTable(QString &currTable)
{
    QFile file(m_filePath+"curr_t.txt");
    if (!file.exists()) {
        return false; // no existe el archivo
    }
    if (!file.open(QIODevice::ReadOnly)) {
        return false; // error al abrir
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0);
    bool ok = true;
    in >> currTable;
    if (in.status() != QDataStream::Ok) {
        ok = false;
    }

    file.close();
    qDebug()<< "readCurrentTable() ejecutado exitosamente y archivo leido.";
    return ok;
}

bool Files::writeBooksList(const QVector<QString> &list)
{
    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    // Asegurarnos de que el directorio exista
    if (!dir.exists()) {
        if (!dir.mkpath(dir.absolutePath()))
            return false;
    }

    const QString fileName = dir.filePath("books.txt");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&file);
    out.setCodec("UTF-8"); // Qt5. En Qt6 se usa otra API si hace falta.

    for (const QString &item : list) {
        out << item << '\n';
        if (out.status() != QTextStream::Ok) {
            file.close();
            return false;
        }
    }

    file.close();
    qDebug()<<"writeBooksList finaliza con true ->list"<<list;
    return true;
}

bool Files::readBooksEntireNamesList(QVector<QString> &list)
{
    list.clear();

    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    const QString fileName = dir.filePath("entirenamebooks.txt");
    QFile file(fileName);
    if (!file.exists())
        return false;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    in.setCodec("UTF-8"); // Qt5

    while (!in.atEnd()) {
        QString line = in.readLine();
        // Opcional: si no quieres eliminar espacios en los extremos, quita trimmed()
        line = line.trimmed();
        if (!line.isEmpty())
            list.append(line);
    }

    file.close();
    return true;
}

bool Files::writeBooksEntireNamesList(const QVector<QString> &list)
{
    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    // Asegurarnos de que el directorio exista
    if (!dir.exists()) {
        if (!dir.mkpath(dir.absolutePath()))
            return false;
    }

    const QString fileName = dir.filePath("entirenamebooks.txt");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out(&file);
    out.setCodec("UTF-8"); // Qt5. En Qt6 se usa otra API si hace falta.

    for (const QString &item : list) {
        out << item << '\n';
        if (out.status() != QTextStream::Ok) {
            file.close();
            return false;
        }
    }

    file.close();
    qDebug()<<"write entire names BooksList finaliza con true ->list"<<list;
    return true;
}

bool Files::writeBooksTypes(
    const QVector<CreateBookWidget::BookType> &types)
{
    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    // Asegurarnos de que el directorio exista
    if (!dir.exists()) {
        if (!dir.mkpath(dir.absolutePath()))
            return false;
    }

    //************************************ Tipos ******************************
    const QString fileName2 = dir.filePath("types.txt");
    QFile filetypes(fileName2);
    if (!filetypes.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    QTextStream out2(&filetypes);
    out2.setCodec("UTF-8"); // Qt5. En Qt6 se usa otra API si hace falta.

    for (const CreateBookWidget::BookType &item : types) {
        out2 << static_cast<int>(item) << '\n';
        if (out2.status() != QTextStream::Ok) {
            filetypes.close();
            return false;
        }
    }
    filetypes.close();
    qDebug()<<"writeBooksTypes finaliza con true ->types"<<types;
    return true;
}
bool Files::readParroquia(QString &parroquia)
{
    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    qDebug() << "readParroquia( m_filePath =" << m_filePath;

    if (!dir.exists()) {
        qWarning() << "No existe la ruta:" << dir;
        return false;
    }

    QString fileName = dir.filePath("parrq.txt");
    qDebug() << "Escribiendo en:" << fileName;

    QFile file(fileName);
    if (!file.exists()) {
        return false;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");                 // Qt5

    QString line = in.readLine();        // lee toda la línea (incluye espacios)
    if (in.status() != QTextStream::Ok && !file.atEnd()) {
        file.close();
        return false;
    }

    parroquia = line;
    file.close();
    qDebug() << "readParroquia(): leido =" << parroquia;
    return true;
}

bool Files::writeParroquia(const QString &parroquia)
{
    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    qDebug() << "writeParroquia( m_filePath =" << m_filePath;



    // Crear la carpeta si hace falta
    if (!dir.exists()) {
        qWarning() << "No existe la ruta:" << dir;
        return false;
    }

    QString fileName = dir.filePath("parrq.txt");
    qDebug() << "Escribiendo en:" << fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "No se pudo abrir archivo:" << fileName << "-" << file.errorString();
        return false;
    }

    // Escritor: puedes usar QTextStream o escribir bytes directamente
    QTextStream out(&file);
    out.setCodec("UTF-8"); // Qt5
    out << parroquia << '\n';
    out.flush();

    if (out.status() != QTextStream::Ok) {
        qWarning() << "Error al escribir en el stream:" << out.status();
        file.close();
        return false;
    }

    file.close();
    qDebug() << "Escrito correctamente:" << parroquia;
    return true;
}



bool Files::readBooksList(QVector<QString> &list)
{
    list.clear();

    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();
    const QString fileName = dir.filePath("books.txt");
    QFile file(fileName);
    if (!file.exists())
        return false;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    in.setCodec("UTF-8"); // Qt5

    while (!in.atEnd()) {
        QString line = in.readLine();
        // Opcional: si no quieres eliminar espacios en los extremos, quita trimmed()
        line = line.trimmed();
        if (!line.isEmpty())
            list.append(line);
    }

    file.close();
    return true;
}

bool Files::readBooksTypes(
    QVector<CreateBookWidget::BookType> &types)
{
    //*********************************** tipos *******************************
    types.clear();
    QFileInfo fi(m_filePath);
    QDir dir = fi.absoluteDir();

    const QString fileName2 = dir.filePath("types.txt");
    QFile file_types(fileName2);
    if (!file_types.exists())
        return false;

    if (!file_types.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in2(&file_types);
    in2.setCodec("UTF-8"); // Qt5

    while (!in2.atEnd()) {
        QString line = in2.readLine();
        // Opcional: si no quieres eliminar espacios en los extremos, quita trimmed()
        line = line.trimmed();
        if (!line.isEmpty()){
            CreateBookWidget::BookType type=
                static_cast<CreateBookWidget::BookType>(
                    line.toInt());
            types.append(type);
        }
    }

    file_types.close();

    return true;
}
