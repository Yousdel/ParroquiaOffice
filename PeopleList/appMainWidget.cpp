#include "appMainWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QFileDialog>
#include <QInputDialog>
#include <QFileInfo>

#include "Tools/AppTitle.h"
#include "databasetableview.h"
#include "AboutWidget/aboutwidget.h"
#include "Books/createbookwidget.h"
#include "DropTableWidget/droptablewidget.h"
#include "Books/selectbookwidget.h"
#include "PeopleList/findtextwidget.h"
#include "bookslist.h"
#include "DarkLightMode/darklightmode.h"
#include "DBWidget/dbwidget.h"


void AppMainWidget::takeDecissionForShowOrHideSuggestWidget()
{
    qDebug()<< "takeDecissionForShowOrHideSuggestWidget("<<filePath<<")";

    selectBookWidget->setPathAndRefreshSuggestList(filePath);
    if (selectBookWidget->list().size() > 0x0) {
        selectBookWidget->show();
    }
    qDebug() << "selectBookWidget list size "<<selectBookWidget->list().size();

}

void AppMainWidget::hideOpenBtnAndTitle()
{
    dbwidget->hideOpenBtn();
    QFileInfo fi(filePath);
    QString s = fi.fileName();
    setWindowTitle(QString("%2 - %1").arg(APPTITLE,s));
}

void AppMainWidget::setBooksInView()
{
    BooksList bl(filePath); bl.readFile();
    view->setBooks(bl.getList());
}


bool AppMainWidget::openDB(const QString &dbfilePath)
{
    filePath = dbfilePath;
    // Abrir DB y comprobar éxito
    if (!view->openDatabase(filePath)) {
        QMessageBox::critical(this, tr("Error"),
                              tr("No se pudo abrir o "
                                 "crear la base de datos:\n%1").arg(filePath));
        return false;
    }
    return true;
}



void AppMainWidget::showOrdered(const QString &book)
{
    if (book.isEmpty()) return;
    CreateBookWidget::BookType type= selectBookWidget->getType(book);
    view->setTable(book, type);
    findText->show();
    //mantener la busqueda en caso deseado
    if (findText->buttonText() == tr("Quitar búsqueda")){
        view->findText(textForSearch);
    }
    view->orderByCorrespondingDate();
}

AppMainWidget::AppMainWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle(APPTITLE);

    if (dropBook == nullptr)
    {
        dropBook = new DropTableWidget(filePath);
        connect(dropBook, &DropTableWidget::widgetClosed,
                this, [this](bool remove){
                    if (remove && dropBook->bookToDrop().isEmpty()==false) {
                        view->dropTable(dropBook->bookToDrop());
                        BooksList bl(filePath);
                        bl.removeBook(dropBook->bookToDrop());
                        selectBookWidget->refreshList();
                    }
                });
    }

    QVBoxLayout *main_lay=new QVBoxLayout(this);

    QHBoxLayout *lay_btns=new QHBoxLayout;

    dbwidget = new DBWidget(this);

    createBook= new QPushButton(tr("Crear un\n"
                                    "libro"),this);
    createBook->setIcon(QIcon(":/Icons/create_book.svg"));
    createBook->setIconSize(QSize(24,24));
    createBook->hide();

    selectBookWidget = new SelectBookWidget("",this);
    selectBookWidget->hide();

    removeBook = new QPushButton("Eliminar\n"
                                              "un libro",this);
    removeBook->setIcon(QIcon(":/Icons/delete_book.svg"));
    removeBook->setIconSize(QSize(24,24));
    removeBook->hide();


    QHBoxLayout *book_lay=new QHBoxLayout;
    book_lay->addWidget(createBook);
    book_lay->addWidget(selectBookWidget);
    book_lay->addWidget(removeBook);


    findText= new FindTextWidget(this);
    findText->hide();
    QPushButton *about=new QPushButton(tr("Acerca de..."),this);
    about->setIcon(QIcon(":/Icons/about.svg"));
    about->setIconSize(QSize(24,24));

    DarkLightMode *toggleDarkWidget = new DarkLightMode(QDir::homePath()+
                                                            "/parroquia_office/"
                                                            "darkmode.txt",this);

    QVBoxLayout *finalBtnslay=new QVBoxLayout;
    finalBtnslay->addWidget(about);
    finalBtnslay->addWidget(toggleDarkWidget);

    view= new DatabaseTableView(this);

    lay_btns->addWidget(dbwidget);
    lay_btns->addStretch(0x1);
    lay_btns->addLayout(book_lay);
    lay_btns->addStretch(0x1);    
    lay_btns->addWidget(findText);
    lay_btns->addLayout(finalBtnslay);

    main_lay->addLayout(lay_btns);
    main_lay->addWidget(view);

    connect(about, &QPushButton::clicked, this, [this](){
        AboutWidget *w=new AboutWidget(this);
        w->setAppNameString(APPTITLE);
        w->setIconFilename(":/Icons/icono.svg");
        w->setButtonColors("lightgray","black");
        w->setButtonHoverColors("white","blue");
        w->show();
    });

    connect(createBook, &QPushButton::clicked,this,[this](){
        createBookWidget= new CreateBookWidget();
        createBookWidget->show();
        connect(createBookWidget, &CreateBookWidget::createBook,
                this,
                [this](const CreateBookWidget::BookType &type,
                                const QString &sigla,
                                    const QString &entireName)
                {
                    view->createTable(sigla, type, entireName);
                    takeDecissionForShowOrHideSuggestWidget();
                    removeBook->show();
                    selectBookWidget->setText(sigla);
                    view->setTable(sigla,type); //abrirlo
                    showOrdered(sigla);
                    dropBook->updateBooks();
                });
        connect(createBookWidget, &CreateBookWidget::widgetClosed,
                createBookWidget, &CreateBookWidget::deleteLater);
    });

    connect(selectBookWidget, &SelectBookWidget::bookSelected,
            this, &AppMainWidget::showOrdered);

    connect(removeBook, &QPushButton::clicked,
            this, [this](){
        if (view->books().size()==0x0){
            QMessageBox::information(this,tr("Sin libros"),
                                     tr("No hay libros en esta base de datos. "
                                        "Por eso no puedes eliminar"));
            return;
        }        
        dropBook->setPath(filePath);
        dropBook->updateBooks();
        dropBook->show();
        dropBook->raise();
    });

    connect(findText, &FindTextWidget::searchDesired,
            this, [this](const QString &text,bool alltables, bool allWords){
        view->findText(text, alltables, allWords);
        textForSearch = text;        
    });
    connect(findText, &FindTextWidget::returnedToNormalView,
            this, [this](){
        view->findText("");
        showOrdered(view->currentBook());
        view->refresh();
    });
    connect(view, &DatabaseTableView::returnToNormalView,
            findText, &FindTextWidget::returnToNormalView);


    connect(dbwidget, &DBWidget::openDBbyCreateDB,
            this, &AppMainWidget::openDBbyCreateDB);
    connect(dbwidget, &DBWidget::openDBbyOpenDBButton,
        this, &AppMainWidget::openDBbyOpenDBBtn);

    connect(dbwidget, &DBWidget::setParrName, this, &AppMainWidget::setParr);

    resize(1000,700);
}

void AppMainWidget::openDBbyOpenDBBtn(const QString &dbFilePath)
{
    filePath = dbFilePath;
    if (!openDB(filePath)) return;
    createBook->show();
    dropBook->setPath(filePath);
    takeDecissionForShowOrHideSuggestWidget();
    hideOpenBtnAndTitle();
    view->readParroquiaFromFile();
    setBooksInView();
    if (view->books().size() > 0x0){
        dropBook->updateBooks();
        dropBook->hide();
        removeBook->show();
        findText->show();
    }
    dbwidget->showParrName(view->parroq());
    dbwidget->showMakeDBCopy();
}


void AppMainWidget::openDBbyCreateDB(const QString &dbfilePath)
{
    if (!openDB(dbfilePath)) return;
    createBook->show();
    takeDecissionForShowOrHideSuggestWidget();
    hideOpenBtnAndTitle();
    dbwidget->askParroq();
}

void AppMainWidget::setParr(const QString &parrName){
    view->setParroquia(parrName);
    setBooksInView();
}

AppMainWidget::~AppMainWidget(){
    delete dropBook;
    delete view;

}
