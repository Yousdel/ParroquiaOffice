#include "selectbookwidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
//app
#include "suggestwidget.h"
#include "PeopleList/bookslist.h"


SelectBookWidget::SelectBookWidget(const QString &dbfilepath,
                                   QWidget *parent) :
    QWidget(parent)
{
    setPalette(QPalette(QColor("white"),QColor(0,200,255)));

    m_path = dbfilepath;
    QLabel *selectBook= new QLabel(tr("Seleccionar libro a visualizar:"), this);
    typeLabel = new QLabel(this);

    suggestWidg=new SuggestWidget(dbfilepath, this);
    connect(suggestWidg, &SuggestWidget::bookSelected,
            this, &SelectBookWidget::bookSelected);
    connect(suggestWidg, &SuggestWidget::bookSelected,
            this, &SelectBookWidget::showDetails);
    QHBoxLayout *btns_lay=new QHBoxLayout;
    btns_lay->addStretch(0x1);
    btns_lay->addWidget(selectBook);
    btns_lay->addStretch(0x1);

    QVBoxLayout *lay=new QVBoxLayout(this);
    lay->addLayout(btns_lay);
    lay->addWidget(suggestWidg);
    lay->addWidget(new QLabel(tr("Escribe aquí las siglas que identifican al libro,\n"
                                 "elige alguna de las sugerencias, y presiona Enter"),this));
    lay->addWidget(typeLabel);

    setLayout(lay);

    setPathAndRefreshSuggestList(dbfilepath);

}

const QStringList &SelectBookWidget::list() const
{
    return suggestWidg->list();
}

void SelectBookWidget::setPathAndRefreshSuggestList(const QString &path){
    m_path = path;
    suggestWidg->setPath(path);
    suggestWidg->refreshList();
}

const CreateBookWidget::BookType &SelectBookWidget::getType(const QString &book) const
{
    return suggestWidg->getType(book);
}

void SelectBookWidget::setText(const QString &text)
{
    suggestWidg->setText(text);
}

void SelectBookWidget::refreshList(){
    suggestWidg->refreshList();
}


void SelectBookWidget::showDetails(const QString &book)
{
    BooksList l(m_path);
    l.readFile();
    const int idx= l.getList().indexOf(book);
    CreateBookWidget::BookType booktype = l.getTypes().at(idx);
    CreateBookWidget w(this);
    w.hide();
    type= w.stringForType(booktype);
    w.deleteLater();
    typeLabel->setText(QString(tr("Tipo de Libro:<br/><b>%1</b>")).arg(type));
}
