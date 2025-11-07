#include "searchallwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QDebug>

SearchAllWidget::SearchAllWidget(const QString &text, QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowTitle(text);
    noitems = new QLabel(tr("No hay elementos de esta búsqueda"));
    noitems->hide();
    QVBoxLayout *lay = new QVBoxLayout(this);
    tv = new QTableView(this);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(tv, &QTableView::clicked,
            this, &SearchAllWidget::rowClicked);

    lay->addWidget(new QLabel(tr("Búsqueda de \"%1\" (todos los libros):\n\n"
                                 "Ayuda: Al hacer click en una fila se muestra la\n"
                                 "misma en la tabla. \n\n"
                                 "Al cerrar esta ventana se cierra la búsqueda en la\n"
                                 "la tabla. No la cierre hasta que no haya tomado o\n"
                                 "cambiado todos los datos que necesita de esta búsqueda").arg(text)));
    lay->addWidget(tv);
    lay->addWidget(noitems);
    setLayout(lay);
}

void SearchAllWidget::setModel(QSqlQueryModel *resultModel)
{
    tv->setModel(resultModel);
    tv->setColumnWidth(0, 30);
    tv->setColumnWidth(1, 30);
    tv->setColumnWidth(2, 130);
    if (resultModel->rowCount()==0x0)
        noitems->show();
    else
        noitems->hide();
    resize(220,600);
}

void SearchAllWidget::rowClicked(const QModelIndex &index)
{
    if (!index.isValid()) return; // Asegúrate de que el índice es válido.

    int row = index.row();

    // Asumiendo que 'book', 'folio' e 'insc_number' son las columnas 0, 1 y 2, respectivamente.
    QString book = index.sibling(row, 0x0).data().toString(); // Primera columna
    QString folio = index.sibling(row, 0x1).data().toString(); // Segunda columna
    QString incNumb = index.sibling(row, 0x2).data().toString(); // Tercera columna

    qDebug() << book << folio << incNumb;

    emit rowSelected(book, folio, incNumb); // Emitir la señal con los valores seleccionados
}

void SearchAllWidget::closeEvent(QCloseEvent *event)
{
    emit widgetClosed();
    QWidget::closeEvent(event);
}
