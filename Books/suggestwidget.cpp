#include "suggestwidget.h"
#include <QLineEdit>
#include <QStringListModel>
#include <QCompleter>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>




void SuggestWidget::refreshList()
{
    if (bookList == nullptr)   return;

    bookList->readFile();
    QVector<QString> list=bookList->getList();
    SortTableList::sort(list);  //ordenar
    m_allSuggestions = list.toList();
}

void SuggestWidget::setText(const QString &book)
{
    refreshList();
    m_lineEdit->setText(book);
    emitBookSelected();
}

SuggestWidget::SuggestWidget(const QString &db_filepath, QWidget *parent)
    : QWidget(parent),
      m_lineEdit(new QLineEdit(this)),
      m_model(new QStringListModel(this)),
      m_completer(new QCompleter(m_model, this)),
    path(db_filepath)
{
    bookList=new BooksList(path);
    auto *layout = new QHBoxLayout(this);

    QPushButton *find=new QPushButton(this);
    find->setIcon(QIcon(":/Icons/find.svg"));

    layout->addWidget(m_lineEdit);
    layout->addWidget(find);
    setLayout(layout);

    // Configurar el completador
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    m_completer->setFilterMode(Qt::MatchContains);       // coincide si contiene la subcadena
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->setModel(m_model);

    m_lineEdit->setCompleter(m_completer);
    m_lineEdit->setToolTip(tr("Cuando presiones Enter\n"
                           "tendrás acceso al libro"));

    // Si quieres controlar cuándo actualizar (por ejemplo, filtrar un array grande),
    // conectar textEdited y actualizar model manualmente:
    connect(m_lineEdit, &QLineEdit::textEdited, this, &SuggestWidget::onTextEdited);
    connect(m_lineEdit, &QLineEdit::returnPressed,this,&SuggestWidget::emitBookSelected);
    connect(m_lineEdit, &QLineEdit::selectionChanged,this,&SuggestWidget::emitBookSelected);
    connect(find, &QPushButton::clicked, this, &SuggestWidget::emitBookSelected);

    // Ejemplo: lista por defecto (puedes cargar desde fichero/BD)
    refreshList();
    m_model->setStringList(m_allSuggestions);
}

void SuggestWidget::setAllSuggestions(const QStringList &all)
{
    m_allSuggestions = all;
    m_model->setStringList(m_allSuggestions); // actualizar modelo completo
}

void SuggestWidget::onTextEdited(const QString &text)
{
    if (text.isEmpty()) {
        m_model->setStringList(m_allSuggestions);
        return;
    }

    QStringList filtered;
    const Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    for (const QString &s : std::as_const(m_allSuggestions)) {
        if (s.contains(text, cs))
            filtered << s;
    }

    m_model->setStringList(filtered);

    // Forzar que se muestre el popup aunque el QLineEdit tenga el foco
    // (no siempre necesario; QCompleter suele abrirlo automáticamente).
    if (!filtered.isEmpty()) {
        m_completer->complete();
    } else {
        m_completer->popup()->hide();
    }
}

void SuggestWidget::emitBookSelected()
{
    emit bookSelected(m_lineEdit->text());
}
