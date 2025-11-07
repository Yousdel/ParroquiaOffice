#pragma once

#include <QWidget>
#include "PeopleList/bookslist.h"


class QLineEdit;
class QStringListModel;
class QCompleter;

class SuggestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SuggestWidget(const QString &db_filepath, QWidget *parent = nullptr);

    // Si quieres establecer la lista completa de sugerencias:
    void setAllSuggestions(const QStringList &all);

    const QStringList &list() const{
        return m_allSuggestions;
    }


    //especificar donde buscar el archivo de lista de tablas
    void setPath(const QString &db_filepath){
        path = db_filepath;
        if (bookList) delete bookList;
        bookList=new BooksList(path);
    }
    const CreateBookWidget::BookType &getType(const QString &book) const{
        return bookList->getType(book);
    }

    void setText(const QString &book);
public slots:
    void refreshList();

private slots:
    // slot opcional para actualizar sugerencias desde una fuente externa
    void onTextEdited(const QString &text);
    void emitBookSelected();

private:
    QLineEdit *m_lineEdit;
    QStringListModel *m_model;
    QCompleter *m_completer;
    QString path;

    BooksList *bookList=nullptr;

    QStringList m_allSuggestions; // lista completa (puede venir de fichero/BD)

signals:
    void bookSelected(QString book);
};
