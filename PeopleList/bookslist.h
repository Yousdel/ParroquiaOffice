#ifndef BOOKSLIST_H
#define BOOKSLIST_H

#include <QObject>

#include <QVector>
#include <Books/createbookwidget.h>
#include "PeopleList/Tools/sorttablelist.h"


class BooksList : public QObject
{
    Q_OBJECT
public:
    BooksList(const QString &dbFilePath, QObject *parent = nullptr);

    void appendToFile(const QString &tableName,
                      const CreateBookWidget::BookType &type,
                      const QString &entireName);
    void removeBook(const QString &tableName);
    void readFile();

    const QVector<QString> &getList() const {
        return namesList;
    }
    const QVector<QString> &getEntireNamesList() const {
        return entireNamesList;
    }
    const QString &getEntireNameForBook(const QString &book) {
        readFile();
        static QString s; s.clear();
        s.append(entireNamesList.at(namesList.indexOf(book)));
        return s;
    }
    const QVector<CreateBookWidget::BookType> &getTypes() const {
        return types;
    }

    const CreateBookWidget::BookType &getType(const QString &book) const{
        const int idx= namesList.indexOf(book);
        static CreateBookWidget::BookType nonetype=CreateBookWidget::None;
        if (idx == -0x1) return nonetype;
        return types.at(idx);
    }

private:
    QString path;
    QVector<QString> namesList, entireNamesList;
    QVector<CreateBookWidget::BookType> types;

signals:
};

#endif // BOOKSLIST_H
