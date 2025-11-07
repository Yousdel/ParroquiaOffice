#include "droptablewidget.h"
#include "ui_droptablewidget.h"

#include <QTableWidgetItem>
#include <QDebug>

#include "PeopleList/bookslist.h"

void DropTableWidget::updateBooks()
{
    qDebug() << "updateBooks path"<< _path;
    ui->tableWidget->setColumnCount(0x1);
    BooksList l(_path);
        //leer los libros
    l.readFile();
    ui->tableWidget->setRowCount(l.getList().size());
    ui->tableWidget->setHorizontalHeaderLabels(
        QStringList("Libros\n"
                    "creados"));
    int row=0x0;
    // ordenar los libros
    QVector<QString> list = l.getList();
    SortTableList::sort(list);
    //agregar al widget
    for (const QString &item : list) {
        ui->tableWidget->setItem(row, 0x0, new QTableWidgetItem(item));
        ++row;
    }
}

DropTableWidget::DropTableWidget(const QString &path, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DropTableWidget), _path(path)
{
    ui->setupUi(this);

    updateBooks();
}

DropTableWidget::~DropTableWidget()
{
    delete ui;
}

const QString &DropTableWidget::bookToDrop()
{
    return m_selected_book;
}

void DropTableWidget::on_tableWidget_cellClicked(int row, int column)
{
    m_selected_book=ui->tableWidget->item(row, column)->text();
    ui->currentSelectedBookLabel->setText(
            m_selected_book);
}


void DropTableWidget::on_removeBook_clicked()
{
    emit widgetClosed(true);
    close();
}


void DropTableWidget::on_CancelBtn_clicked()
{
    emit widgetClosed(false);
    close();
}

