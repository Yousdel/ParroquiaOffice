#ifndef APPMAINWIDGET_H
#define APPMAINWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>




class DatabaseTableView;
class SelectBookWidget;
class CreateBookWidget;
class FindTextWidget;
class DropTableWidget;
class DBWidget;

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
    DBWidget *dbwidget;
    QPushButton *createBook;
    QPushButton *removeBook;
    SelectBookWidget *selectBookWidget=nullptr;
    DropTableWidget *dropBook=nullptr;

    QString textForSearch;
    QString filePath;
    CreateBookWidget *createBookWidget;
    FindTextWidget *findText;

    void takeDecissionForShowOrHideSuggestWidget();

    void hideOpenBtnAndTitle();
    
    void setBooksInView();
    
private slots:
    bool openDB(const QString &dbfilePath);

    void showOrdered(const QString &book);

    void setParr(const QString &parrName);
    void openDBbyCreateDB(const QString &dbfilePath);
    void openDBbyOpenDBBtn(const QString &dbFilePath);
signals:
    void askParr();
};

#endif // APPMAINWIDGET_H
