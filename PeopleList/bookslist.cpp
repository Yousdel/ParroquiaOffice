#include "bookslist.h"
#include "Tools/files.h"

BooksList::BooksList(const QString &dbFilePath,QObject *parent)
    : QObject{parent},
    path(dbFilePath)
{}

void BooksList::appendToFile(
    const QString &tableName,
    const CreateBookWidget::BookType &type,
    const QString &entireName)
{
    //agregar a archivo de listado el nombre y tipo de esta tabla
    Files f(path);

    f.readBooksList(namesList);
    f.readBooksTypes(types);
    f.readBooksEntireNamesList(entireNamesList);
    //agregar a esta tabla
    namesList << tableName;
    types << type;
    entireNamesList << entireName;
    f.writeBooksList(namesList); // y a archivos
    f.writeBooksTypes(types);
    f.writeBooksEntireNamesList(entireNamesList);
}

void BooksList::removeBook(const QString &tableName)
{
    readFile();
    const int idx = namesList.indexOf(tableName);
    if (idx ==-0x1) return;
    namesList.removeAt(idx);
    types.removeAt(idx);
    entireNamesList.removeAt(idx);
    Files f(path);
    f.writeBooksList(namesList);
    f.writeBooksTypes(types);
    f.writeBooksEntireNamesList(entireNamesList);
}

void BooksList::readFile()
{
    Files f(path);
    f.readBooksList(namesList);
    f.readBooksTypes(types);
    f.readBooksEntireNamesList(entireNamesList);
}
