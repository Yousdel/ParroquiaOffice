#pragma once

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QVector>
//app
#include "Books/createbookwidget.h"
#include "Tools/files.h"

class QHBoxLayout;

class DatabaseTableView : public QWidget
{
    Q_OBJECT
public:
    explicit DatabaseTableView(QWidget *parent=nullptr);
    ~DatabaseTableView();

    // Abrir (o reabrir) la base SQLite. Devuelve true si OK.
    bool openDatabase(const QString &filePath);

    /** crea tabla segun tipo de tabla*/
    bool createTable(const QString &tableName,
                     const CreateBookWidget::BookType &type, const QString &entireName);
    // Seleccionar la tabla a mostrar. Devuelve true si la selección fue exitosa.
    bool setTable(const QString &tableName,
                  const CreateBookWidget::BookType &type);

    void setBooks(const QVector<QString> &v){
        tables=v;
    }
    const QVector<QString> &books() const {
        return tables;
    }

    // Forzar recarga de la tabla
    void refresh();

    QAbstractItemModel *model() const { return m_model; }

    void addPersonToTable();

    bool findText(const QString &text, bool searchAllTables = false,
                   bool matchAllWords = false);
    void setParroquia(const QString &parroquia) {
        _parroquia = parroquia;
        //salvar en archivo
        Files f(_dbFilePath);
        if (!f.writeParroquia(parroquia)){
            QMessageBox::warning(this,
                                 tr("Error"),
                                 tr("No se pudo guardar el nombre de la parroquia\n"
                                    "en un archivo"));
        }
    }

    void readParroquiaFromFile()
    {
        Files f(_dbFilePath);
        f.readParroquia(_parroquia);
    }

    const QString &parroq() const { return _parroquia; }

    const QString &currentBook() const { return _tableName; }
    //borrar  tabla de la base de datos
    bool dropTable(const QString &tableName);

    void orderByCorrespondingDate();

public slots:
    bool searchRow(const QString &book, const QString &folio, const QString &incNumber);
    void viewEditRow();
private slots:
    void takeIndexClicked(const QModelIndex &mindex);
    void prepareTxtFile();
private:
    QSqlDatabase m_db;
    QTableView *m_view;
    QAbstractItemModel *m_model = nullptr;


    QHBoxLayout *mainl;
    QString m_connectionName,
        _tableName, _entireName,
        _dbFilePath,
        _parroquia;
    QModelIndex m_current_index;
    QPushButton *removeCurrentPerson,
        *prepareFileBtn, *appendRowBtn, *viewEditRowBtn;
    QLabel *noItemsFounded;
    QVector<QString> tables;
    QSqlError m_lastError;

    CreateBookWidget::BookType currentType;

    QSqlError modelLastError() const {
        if (auto table = qobject_cast<QSqlTableModel*>(m_model)) return table->lastError();
        if (auto query = qobject_cast<QSqlQueryModel*>(m_model)) return query->lastError();
        return QSqlError();
    }

    bool findTextInCurrentTable(const QString &text, bool matchAllWords);
    bool updateWith(const QString &sql, const QVector<QVariant> v);
    
    
    void updateBtnsTextsByType();
    
signals:
    void returnToNormalView();
};
