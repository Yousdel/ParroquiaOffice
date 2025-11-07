#ifndef SQLENGINE_H
#define SQLENGINE_H

#include "createbookwidget.h"
#include <QSqlQuery>
#include <QVector>

class BaseNewPersonWidg;
/**
 * @brief Tiene la cadena QString para crear el libro*(tabla)
 */
class SQLEngine
{
private:
    enum InsertType{
        Columns, Placeholders
    };

    QString s;
    QSqlQuery *insert;
    QVector<QString> allFieldsForBind, m_fields;

    void commonInsert(QString &sql, InsertType values);

    void singlePersonCommonInsert(QString &sql, InsertType values,
                                  const CreateBookWidget::BookType &book_type);

    void finalAppends(QString &sql, InsertType values);

    void baptismInsert(QString &sql, InsertType values,
                       const CreateBookWidget::BookType &book_type);

    void marriageInsert(QString &sql, InsertType values,
                        const CreateBookWidget::BookType &book_type);

    void defunctionInsert(QString &sql, InsertType values,
                          const CreateBookWidget::BookType &book_type);

    void confirmationInsert(QString &sql, InsertType values,
                            const CreateBookWidget::BookType &book_type);

    void completeInsert(QString &sql, CreateBookWidget::BookType book_type, InsertType values);

    void putColonOfEachItemOf(QVector<QString> &v);

    void appendFields(QString &sql, const QStringList &fields, InsertType values,
                      bool ending=false);
public:
    const QString &createBookSQLString(const CreateBookWidget::BookType &type,
                                const QString &ident);
    void setSqlQuery(QSqlQuery *query)
    {
        insert=query;
    }

    bool insertPerson(BaseNewPersonWidg *w, const QString &ident,
                      CreateBookWidget::BookType book_type);

    const QVector<QString> &getFields(
                   CreateBookWidget::BookType book_type );
    const QVector<QString> &getAllFields();
    const QString &getDateFieldName(CreateBookWidget::BookType book_type);
    const QString &updatePersonSQL(const QString &tableName,
                                   CreateBookWidget::BookType type,
                                   int id);
};

#endif // SQLENGINE_H
