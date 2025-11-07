#include "appMainWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPushButton>
#include <QFileDialog>
#include <QInputDialog>
#include <QFileInfo>

#include "Tools/AppTitle.h"
#include "ShowOrHideBtns.h"
#include "databasetableview.h"
#include "AboutWidget/aboutwidget.h"
#include "Books/createbookwidget.h"
#include "DropTableWidget/droptablewidget.h"
#include "Books/selectbookwidget.h"
#include "PeopleList/findtextwidget.h"
#include "bookslist.h"
#include "DarkLightMode/darklightmode.h"

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
    openDbBtn->hide();
    QFileInfo fi(filePath);
    QString s = fi.fileName();
    setWindowTitle(QString("%2 - %1").arg(APPTITLE,s));
}

void AppMainWidget::setBooksInView()
{
    BooksList bl(filePath); bl.readFile();
    view->setBooks(bl.getList());
}

void AppMainWidget::showParrName(const QString parr)
{
    parroq->setText(tr("Parroquia: <h3><br/><b>%1</b></h3>").arg(parr));
    parroq->show();
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
    createDbBtn=new QPushButton(tr("Crear la Base\n"
                                "de Datos"), this);
    createDbBtn->setIcon(QIcon(":/Icons/create_db.svg"));
    createDbBtn->setIconSize(QSize(24,24));
    openDbBtn=new QPushButton(tr("Abrir\n"
                              "Base de Datos"),this);
    openDbBtn->setIcon(QIcon(":/Icons/folder.svg"));
    openDbBtn->setIconSize(QSize(24,24));
    removeDBBtn=new QPushButton(tr("Borrar la\n"
                                  "Base de Datos."), this);
    removeDBBtn->setEnabled(false);

    QPushButton *makeDBCopy=new QPushButton(tr("Hacer Salva de\n"
                                                 "la Base de Datos"),this);
    makeDBCopy->setIcon(QIcon(":/Icons/makeCopy.svg"));
    makeDBCopy->hide();

    parroq = new QLabel("",this);
    parroq->hide();
    QHBoxLayout *dbBtns1=new QHBoxLayout;
    dbBtns1->addWidget(createDbBtn);
    dbBtns1->addWidget(openDbBtn);
    dbBtns1->addWidget(removeDBBtn);
    dbBtns1->addWidget(makeDBCopy);

    QVBoxLayout *dbBtns=new QVBoxLayout;
    dbBtns->addWidget(parroq);
    // dbBtns->addStretch(0x1);
    dbBtns->addLayout(dbBtns1);

    createBook= new QPushButton(tr("Crear un\n"
                                    "libro"),this);
    createBook->setIcon(QIcon(":/Icons/create_book.svg"));
    createBook->setIconSize(QSize(24,24));
    createBook->hide();

    selectBookWidget = new SelectBookWidget("",this);
    selectBookWidget->hide();

    QPushButton *removeBook = new QPushButton("Eliminar\n"
                                              "un libro",this);
    removeBook->setIcon(QIcon(":/Icons/delete_book.svg"));
    removeBook->setIconSize(QSize(24,24));
    removeBook->hide();


    QHBoxLayout *book_lay=new QHBoxLayout;
    book_lay->addWidget(createBook);
    book_lay->addWidget(selectBookWidget);
    book_lay->addWidget(removeBook);

    sh=new ShowOrHideBtns(createDbBtn, openDbBtn, removeDBBtn);
    sh->readCreatedFile();

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

    lay_btns->addLayout(dbBtns);
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

    connect(createDbBtn, &QPushButton::clicked, this, [this](){
        // Usar un diálogo de "guardar" para elegir carpeta y nombre
        filePath = QFileDialog::getSaveFileName(
            this,
            tr("Crea un Directorio y la Nueva Base de Datos"),
            QDir::homePath() + QDir::separator() + "nueva_base.db",
            tr("Bases SQLite (*.db);;Todos los archivos (*)"));

        if (filePath.isEmpty())
            return; // el usuario canceló

        // Asegurar extensión .db si falta
        QFileInfo fi(filePath);
        if (fi.suffix().isEmpty())
            filePath += ".db";

        qDebug() << "Crear DB en:" << filePath;

        // Abrir DB y comprobar éxito (asumo que openDatabase devuelve bool)
        if (!view->openDatabase(filePath)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("No se pudo abrir o "
                                     "crear la base de datos:\n%1").arg(filePath));
            return;
        }
        if (sh) sh->createTheCreatedFile();        
        createBook->show();
        takeDecissionForShowOrHideSuggestWidget();
        hideOpenBtnAndTitle();
        QString parr;
        do {
            parr=
                QInputDialog::getText(this, tr("Parroquia"),
                                         tr("Introduce el nombre completo de la parroquia\n\n"
                                         "(No puedes cancelar esto porque es necesario\n"
                                         "para el resto del trabajo)"));
        } while (parr.isEmpty());
        showParrName(parr);
        view->setParroquia(parr);
        setBooksInView();
    });

    connect(openDbBtn, &QPushButton::clicked,
            this, [this, removeBook, makeDBCopy](){
        filePath = QFileDialog::getOpenFileName(
            this,
            tr("Abrir Base de Datos"),
            QDir::homePath(),
            tr("Bases SQLite (*.db);;Todos los archivos (*)"));

        if (filePath.isEmpty())
            return; // el usuario canceló

        if (!view->openDatabase(filePath)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("No se pudo abrir la base de datos:\n%1").arg(filePath));
            return;
        }
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
        showParrName(view->parroq());
        makeDBCopy->show();
    });

    connect(createBook, &QPushButton::clicked,this,[this,removeBook](){
        createBookWidget= new CreateBookWidget();
        createBookWidget->show();
        connect(createBookWidget, &CreateBookWidget::createBook,
                this,
                [this,removeBook](const CreateBookWidget::BookType &type,
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
    connect(makeDBCopy, &QPushButton::clicked, this, &AppMainWidget::makeAnEntireDBCopy);

    resize(1000,700);
}

AppMainWidget::~AppMainWidget(){
    delete dropBook;
    delete view;
    delete createDbBtn;
    delete openDbBtn;
    delete removeDBBtn;
    delete sh;
}
