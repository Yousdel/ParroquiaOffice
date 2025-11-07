#include "databasetableview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QDebug>
#include <QUuid>
#include <QHeaderView>
#include <QPushButton>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QPushButton>
//app
#include "Books/createbookwidget.h"
#include "Books/sqlEngine.h"
#include "PeopleList/PersonWidgets/newpersonwidgetfactory.h"
#include "PeopleList/Tools/files.h"
#include "PeopleList/bookslist.h"
#include "PeopleList/searchallwidget.h"
#include "Books/selectbookwidget.h"



DatabaseTableView::DatabaseTableView(QWidget *parent)
    : QWidget(parent),
    m_view(new QTableView(this)),
    m_model(nullptr)
{
    m_view->setToolTip(tr("Al hacer clic aqui se muestran opciones\n"
                       "respecto a la persona.\n\n"
                          "Puedes modificar los campos de una persona\n"
                          "y al cambiar de fila quedan modificados y\n"
                          "guardados en la Base de Datos."));
    auto *btns_lay=new QHBoxLayout;

    appendRowBtn=new QPushButton(tr("Agregar\n"
                                   "Nueva fila"), this);
    appendRowBtn->setIcon(QIcon(":/Icons/plus.svg"));
    appendRowBtn->setIconSize(QSize(24,24));
    appendRowBtn->hide();

    removeCurrentPerson=new QPushButton(tr("Eliminar\n"
                                        "esta persona"),this);
    removeCurrentPerson->setIcon(QIcon(":/Icons/minus-red.svg"));
    removeCurrentPerson->setIconSize(QSize(24,24));
    removeCurrentPerson->hide();

    prepareFileBtn=new QPushButton(tr("Preparar archivo\n"
                                        "de esta fila"), this);
    prepareFileBtn->setIcon(QIcon(":/Icons/create_text.svg"));
    prepareFileBtn->setIconSize(QSize(24,24));
    prepareFileBtn->hide();
    noItemsFounded=new QLabel(QString("<html><head/><body><p>"
                                        "<span style=\" font-weight:700;"
                                        " color:#ff0000;\">%1</span>"
                                        "</p></body></html>"
                                        "").arg(tr("No hay elementos\n"
                                   "a mostrar")), this);
    noItemsFounded->hide();
    viewEditRowBtn = new QPushButton(tr("Ver/editar\n"
                                     "ficha"), this);
    viewEditRowBtn->setIcon(QIcon(":/Icons/view_edit_record.svg"));
    prepareFileBtn->setIconSize(QSize(24,24));
    viewEditRowBtn->hide();

    btns_lay->addWidget(appendRowBtn);
    btns_lay->addWidget(removeCurrentPerson);
    btns_lay->addWidget(viewEditRowBtn);
    btns_lay->addStretch(0x1);
    btns_lay->addWidget(noItemsFounded);
    btns_lay->addStretch(0x1);
    btns_lay->addWidget(prepareFileBtn);

    // Crear layout
    auto *lay = new QVBoxLayout;
    lay->addWidget(m_view);
    lay->addLayout(btns_lay);
    mainl= new QHBoxLayout(this);
    mainl->addLayout(lay);

    setLayout(mainl);

    // Crear una conexión con nombre único
    m_connectionName = QUuid::createUuid().toString();
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);

    // model se crea después de abrir la DB (para pasarle el QSqlDatabase)

    connect(m_view, &QTableView::clicked,
            this, &DatabaseTableView::takeIndexClicked);
    connect(removeCurrentPerson, &QPushButton::clicked,
            this,[this]()
    {
        m_model->removeRow(m_current_index.row());
        QTimer::singleShot(1500, this,[this](){
            refresh();
        });
    });
    connect(prepareFileBtn, &QPushButton::clicked,
            this, &DatabaseTableView::prepareTxtFile);
    connect(appendRowBtn, &QPushButton::clicked, this,[this](){
        addPersonToTable();
        refresh();
    });
    connect(viewEditRowBtn, &QPushButton::clicked,
            this, &DatabaseTableView::viewEditRow);
}

void DatabaseTableView::prepareTxtFile()
{
    prepareFileBtn->hide();
    removeCurrentPerson->hide();

    // implementación del slot
    QModelIndex index=m_current_index;

    if (!index.isValid())
        return;

    // Comprobar conexión a BD (opcional)
    if (!m_db.isValid() || !m_db.isOpen()) {
        QMessageBox::warning(this, tr("Base de datos"),
                             tr("La conexión a la base de datos no está abierta."));
        return;
    }

    // Obtener el índice correspondiente en el modelo fuente si hay un proxy
    QModelIndex sourceIndex = index;
    QAbstractItemModel *viewModel = m_view->model();
    QSqlTableModel *sourceModel = qobject_cast<QSqlTableModel*>(viewModel);

    if (!sourceModel) {
        // comprobar si es un proxy (p. ej. QSortFilterProxyModel)
        QSortFilterProxyModel *proxy = qobject_cast<QSortFilterProxyModel*>(viewModel);
        if (proxy) {
            sourceIndex = proxy->mapToSource(index);
            sourceModel = qobject_cast<QSqlTableModel*>(proxy->sourceModel());
        }
    }

    if (!sourceModel) {
        QMessageBox::warning(this, tr("Modelo"),
                             tr("No se pudo obtener el modelo "
                                "de datos (no es QSqlTableModel)."));
        return;
    }

    int row = sourceIndex.row();
    if (row < 0x0 || row >= sourceModel->rowCount()) {
        QMessageBox::warning(this, tr("Fila"),
                             tr("Fila seleccionada no válida."));
        return;
    }

    // Obtener el registro de la fila
    QSqlRecord rec = sourceModel->record(row);
    if (rec.isEmpty()) {
        QMessageBox::warning(this, tr("Registro"),
                             tr("No se pudo obtener los datos de la fila seleccionada."));
        return;
    }

    // Pedir nombre/ubicación del archivo
    QString defaultName = QString("%1_fila_%2.txt").arg(_tableName).arg(row + 0x1);
    QString fileName =
        QFileDialog::getSaveFileName(this,
                                     tr("Guardar fila como"),
                                     defaultName,
                                     tr("Archivos de texto (*.txt);;Todos los archivos (*)"));
    if (fileName.isEmpty())
        return; // el usuario canceló

    // Preparar el contenido: cada valor en una línea nueva
    QStringList lines;
    lines << tr("Parroquia");
    lines << _parroquia;
    lines << tr("Nombre completo del libro");
    lines << _entireName;
    for (int i = 0; i < rec.count(); ++i) {
        QVariant v = rec.value(i);
        // incluir nombre de campo:
        lines << QString("%1:\n%2").arg(rec.fieldName(i), v.toString());

    }
    QString content = lines.join(QLatin1Char('\n'));

    // Guardar en UTF-8
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"),
                              tr("No se puede abrir el"
                                 " archivo para escribir:\n%1").arg(file.errorString()));
        return;
    }
    QByteArray bytes = content.toUtf8();
    qint64 written = file.write(bytes);
    file.close();

    if (written <= 0x0) {
        QMessageBox::critical(this, tr("Error"),
                              tr("No se pudo escribir en el archivo."));
        return;
    }
    QMessageBox::information(this, tr("Éxito"),
                             tr("Fila guardada en:\n%1").arg(fileName));
}

void DatabaseTableView::takeIndexClicked(const QModelIndex &mindex)
{
    m_current_index = mindex;
    removeCurrentPerson->show();
    prepareFileBtn->show();
    viewEditRowBtn->show();
}

DatabaseTableView::~DatabaseTableView()
{
    // Borrar los objetos que usan la conexión antes de removerla
    delete m_view;
    delete m_model;

    // Cerrar y remover la conexión (remover sólo después de destruir modelos/vistas)
    if (m_db.isOpen()) m_db.close();
    QSqlDatabase::removeDatabase(m_connectionName);
}

bool DatabaseTableView::openDatabase(const QString &filePath)
{
    // Si hay una conexión previa con nombre, cerrar y removerla con cuidado
    // (solo si no hay QSqlDatabase instancias que la estén usando).
    if (m_db.isValid() && m_db.isOpen()) {
        m_db.close();
    }

    // Si m_db no es válido, creamos una conexión nueva.
    if (!m_db.isValid()) {
        // usar un nombre de conexión único (por ejemplo, basado en puntero o uuid)
        const QString connName = QStringLiteral("conn_%1").arg(reinterpret_cast<quintptr>(this));
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), connName);
        if (!m_db.isValid()) {
            qWarning() << "No se pudo crear QSqlDatabase válida";
            QMessageBox::critical(nullptr, tr("Error"),
                                  tr("No se pudo crear la conexión de base de datos."));
            return false;
        }
    }

    m_db.setDatabaseName(filePath);

    if (!m_db.open()) {
        QString s =
            QStringLiteral("No se pudo abrir la base de datos: %1").arg(m_db.lastError().text());
        qWarning() << s;
        QMessageBox::critical(nullptr, tr("Error"), s);
        return false;
    }

    // Si ya existe un modelo, elimínalo y créalo de nuevo con la nueva conexión
    if (m_model) {
        delete m_model;
        m_model = nullptr;
    }

    m_model = new QSqlTableModel(this, m_db);
    if (auto table = qobject_cast<QSqlTableModel*>(m_model)){
        table->setEditStrategy(QSqlTableModel::OnRowChange);
    }
    m_view->setModel(m_model);
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setAlternatingRowColors(true);
    m_view->horizontalHeader()->setStretchLastSection(true);
    qDebug()<<"openDatabase() finalizada correctamente";
    _dbFilePath = filePath;
    return true;
}


bool DatabaseTableView::createTable(const QString &tableName,
                                    const CreateBookWidget::BookType &type,
                                    const QString &entireName)
{
    if (!m_db.isOpen()) {
        qWarning() << "La base de datos no está abierta. Llama a openDatabase() primero.";
        return false;
    }
    if (tableName.isEmpty()) {
        qWarning() << "Nombre de tabla vacío";
        return false;
    }

    _tableName = tableName;
    _entireName = entireName;
    QSqlQuery q(m_db); // <--- usar la conexión correcta

    // Escapar el nombre de tabla (usa el escape del driver)
    QString ident =
        m_db.driver()->escapeIdentifier(tableName,
                                    QSqlDriver::TableName);
    SQLEngine s;
    const QString createStmt = s.createBookSQLString(type, ident);

    if (!q.exec(createStmt)) {
        qCritical() << "Error al crear la tabla:" << q.lastError().text();
        QMessageBox::critical(this, "Error",
                              "Error al crear la tabla: " + q.lastError().text());
        return false;
    }
    BooksList *book_list=new BooksList(_dbFilePath);
    book_list->appendToFile(tableName, type, entireName);
    book_list->deleteLater();
    if (!tables.contains(tableName))
        tables.append(tableName);
    return true;
}


bool DatabaseTableView::setTable(const QString &tableName,
                                 const CreateBookWidget::BookType &type)
{
    if (!m_db.isOpen()) {
        qWarning() << "La base de datos no está abierta. Llama a openDatabase() primero.";
        return false;
    }
    if (!m_model) {
        // debería crearse en openDatabase
        m_model = new QSqlTableModel(this, m_db);
        m_view->setModel(m_model);
    }

    if (auto table= qobject_cast<QSqlTableModel*>(m_model)){
        table->setTable(tableName);
    }
    _tableName = tableName;
    BooksList books(_dbFilePath);
    _entireName = books.getEntireNameForBook(_tableName);
    currentType = type;
    bool ok=false;
    if (auto table= qobject_cast<QSqlTableModel*>(m_model)){
        ok = table->select();
    }
    if (!ok) {
        QString s=tr("Error al seleccionar la tabla:") +
                    modelLastError().text();
        qWarning() << s;
        QMessageBox::critical(this,"Error",s);
    } else {

        for (int c = 0x0; c < m_model->columnCount(); ++c) {
            QString header = m_model->headerData(c, Qt::Horizontal).toString();
            m_view->horizontalHeader()->setSectionResizeMode(c,
                                                             QHeaderView::ResizeToContents);
            m_model->setHeaderData(c, Qt::Horizontal, header);
        }
    }
    appendRowBtn->show();
    updateBtnsTextsByType();

    return ok;
}

void DatabaseTableView::updateBtnsTextsByType()
{
    appendRowBtn->setText(tr("Agregar\n%1").
                          arg(CreateBookWidget::shortString(currentType)));
    removeCurrentPerson->setText(tr("Eliminar\n%1").
                                 arg(CreateBookWidget::shortString(currentType)));
    prepareFileBtn->setText(tr("Copiar este\n%1\nen archivo de texto").
                            arg(CreateBookWidget::shortString(currentType)));
    viewEditRowBtn->setText(tr("Ver/editar\n%1").
                            arg(CreateBookWidget::shortString(currentType)));
}

void DatabaseTableView::refresh()
{
    if (!m_model) return;

    setUpdatesEnabled(false);

    if (auto table = qobject_cast<QSqlTableModel*>(m_model)) {
        if (!table->select()) {
            qWarning() << "Failed to refresh table model:" << table->lastError().text();
        }
    } else if (auto query = qobject_cast<QSqlQueryModel*>(m_model)) {
        // Re-ejecutar la query ya almacenada por QSqlQueryModel
        QSqlQuery q = query->query();
        query->setQuery(q); // volver a ejecutar
        if (q.lastError().isValid()) {
            qWarning() << "Failed to refresh query model:" << q.lastError().text();
        }
    } else {
        qWarning() << "Modelo no soportado en refresh()";
    }

    if (m_model->rowCount() == 0) {
        noItemsFounded->show();
    } else {
        noItemsFounded->hide();
    }

    setUpdatesEnabled(true);
    removeCurrentPerson->hide();
    prepareFileBtn->hide();
    viewEditRowBtn->hide();
    updateBtnsTextsByType();
}


void DatabaseTableView::addPersonToTable()
{
    if (!m_db.isOpen()) {
        qWarning() << "La base de datos no está abierta. Llama a openDatabase() primero.";
        return;
    }
    qDebug()<<"addPersonToTable() -> currentType == Marriage =>"<<
        CreateBookWidget::isMarriageType(currentType);

    // Fabrica de widget
    BaseNewPersonWidg *w =
        NewPersonWidgetFactory::createForType(currentType,_parroquia,_tableName);
    if (w==nullptr) {
        qDebug() << "widget factory => widget nullptr";
        return;
    }
    w->setCurrentIdToShow(m_model->rowCount() + 0x1);
    w->show();

    // Conectar y usar deleteLater() para evitar eliminar objetos inmediatamente dentro de callbacks
    connect(w, &BaseNewPersonWidg::widgetClosed, this, [this, w](bool save) {
        if (!save) {
            w->deleteLater(); return;}
        qDebug() << "widget widgetClosed";
            // Solo insertar si hay nombre (puedes cambiar la lógica según tu widget)

            // Escapar el identificador solo para la SQL manual
            QString ident = m_db.driver()->escapeIdentifier(_tableName, QSqlDriver::TableName);

        // Usar transacción para atomicidad
        if (!m_db.transaction()) {
            qWarning() << "No se pudo iniciar la transacción:" << m_db.lastError().text();
        }

        QSqlQuery *insert=new QSqlQuery(m_db);
        SQLEngine s;
        s.setSqlQuery(insert);
        if (!s.insertPerson(w, ident, currentType)){
            qCritical() << "Error al insertar:" << insert->lastError().text();
            QMessageBox::critical(this, tr("Error"),
                                  tr("Error al insertar:\n%1").
                                  arg(insert->lastError().text()));
            if (m_db.isOpen()) m_db.rollback();
        } else {
            // Commit y actualizar la vista
            if (!m_db.commit())
                qWarning() << "No se pudo hacer commit:" << m_db.lastError().text();

            if (m_model) {
                // setTable con el nombre sin escapar
                /*
                if (auto table = qobject_cast<QSqlTableModel *>(m_model)){
                    table->setTable(_tableName);*/
                setTable(_tableName, currentType);
                //}
                orderByCorrespondingDate();
            }
        }

        w->deleteLater();
    });
}

bool DatabaseTableView::findTextInCurrentTable(const QString &text,bool matchAllWords)
{
    if (!m_db.isOpen()) {
        qWarning() << "La base de datos no está abierta.";
        return false;
    }
    if (_tableName.isEmpty() || !m_model) {
        qWarning() << "No hay tabla seleccionada en el modelo.";
        return false;
    }

    QString search = text.trimmed();
    // Si la búsqueda está vacía, quitar filtro y refrescar todo
    auto table= qobject_cast<QSqlTableModel *>(m_model);
    if (search.isEmpty()) {
        if (table){
            table->setFilter(QString());
            table->select();
        }
        return true;
    }

    // Obtener columnas y tipos desde PRAGMA table_info
    QStringList textColumns;
    QSqlQuery q(m_db);
    const QString pragma = QString("PRAGMA table_info(%1)")
                               .arg(m_db.driver()->escapeIdentifier(_tableName,
                                                                    QSqlDriver::TableName));
    if (!q.exec(pragma)) {
        qWarning() << "No se pudo consultar la estructura de la tabla:" <<
            q.lastError().text();
        return false;
    }

    while (q.next()) {
        // PRAGMA table_info devuelve: cid, name, type, notnull, dflt_value, pk
        QString colName = q.value(0x1).toString();
        QString colType = q.value(0x2).toString().toUpper();

        // considerar tipos de texto comunes
        if (colType.contains("CHAR") || colType.contains("CLOB") ||
            colType.contains("TEXT") || colType.contains("VARCHAR")) {
            textColumns << m_db.driver()->escapeIdentifier(colName, QSqlDriver::FieldName);
        }
    }

    if (textColumns.isEmpty()) {
        qWarning() << "No se encontraron columnas de texto en la tabla" << _tableName;
        return false;
    }
    // Construir cláusula LIKE para cada columna
    static QRegularExpression regexpression("\\s+");
    QStringList clauses, words = search.split(regexpression), tableConds;
    // Para cada palabra, crear una subcondición con OR entre columnas
    for (int j = 0x0; j < words.size(); ++j) {
        QStringList perWord;
        for (const QString &col : std::as_const(textColumns)){
            // Escapar comillas simples en el término de búsqueda para SQL
            QString esc = words.at(j);
            esc.replace("'", "''"); // escape para literales SQL
            // arg 1 = columna, arg 2 = '%texto%'
            perWord << QString("%1 LIKE '%2'").arg(col, "%" + esc + "%");
        }
        tableConds << QString("(%1)").arg(perWord.join(" OR "));
    }

    QString filter;
    if (!matchAllWords)
        filter = tableConds.join(" OR ");
    else
        filter = tableConds.join(" AND ");
    table->setFilter(filter);
    return table->select();
}

bool DatabaseTableView::updateWith(const QString &sql, const QVector<QVariant> v)
{
    // 3. Preparar la consulta.
    QSqlQuery query(m_db);
    if (!query.prepare(sql)) {
        m_lastError = query.lastError();
        return false;
    }

    // 4. Vincular los valores.
    //    El orden debe coincidir con los '?' en la consulta.
    //    query.addBindValue(newValues.value(0)); // Valor para columna1
    //    query.addBindValue(newValues.value(1)); // Valor para columna2
    //    ...
    for(const QVariant &item: v){
        query.addBindValue(item.toString());
    }

    // 5. Ejecutar la consulta.
    if (!query.exec()) {
        m_lastError = query.lastError();
        return false;
    }
    return true;
}


bool DatabaseTableView::findText(const QString &text, bool searchAllTables,
                                 bool matchAllWords)
{
    if (!searchAllTables)
        return findTextInCurrentTable(text, matchAllWords);
    if (text.trimmed().isEmpty())
        return false;

    static const QStringList fieldsForAllTablesSearch = { "Libro",
                                                         "Folio", "Numero_de_inscripcion" };
    QStringList tableList; // Preparar lista de tablas a buscar
    for (const QString &t : std::as_const(tables))
        if (!t.isEmpty())
            tableList << t;
    if (tableList.isEmpty())
        return false;
    QStringList selects;
    QSqlDriver *driver = m_db.driver();
    if (!driver) return false;

    static QRegularExpression regexpress("\\s+");
    QStringList words = text.split(regexpress, Qt::SkipEmptyParts);
    if (words.isEmpty())
        return false;

    for (const QString &table : std::as_const(tableList)) {
        QSqlRecord rec = m_db.record(table);
        bool ok = true; // Verificar que la tabla tenga todos los campos requeridos
        for (const QString &f : fieldsForAllTablesSearch) {
            if (rec.indexOf(f) < 0x0) { ok = false; break; }
        }
        if (!ok) continue;

        // Preparar lista de columnas escapadas (todas las columnas de la tabla)
        QStringList escapedCols;
        for (int i = 0; i < rec.count(); ++i) {
            QString col = rec.fieldName(i);
            QString escCol = QString::fromUtf8(
                driver->escapeIdentifier(col, QSqlDriver::FieldName)
                .toStdString().c_str());
            escapedCols << escCol;
        }

        if (escapedCols.isEmpty()) continue;

        // Construir condiciones:
        // - Si matchAllWords == false -> OR entre todas las combinaciones (comportamiento actual)
        // - Si matchAllWords == true  -> para cada palabra crear (col1 LIKE :p OR col2 LIKE :p ...)
        //   y luego unir esas agrupaciones por AND
        QStringList tableConds;
        if (!matchAllWords) {
            // OR entre todas las combinaciones (palabra en cualquier columna)
            for (int i = 0; i < escapedCols.size(); ++i) {
                for (int j = 0; j < words.size(); ++j) {
                    tableConds << QString("COALESCE(CAST(%1 AS TEXT), '') LIKE :pattern%2")
                                  .arg(escapedCols.at(i)).arg(j);
                }
            }
        } else {
            // Para cada palabra, crear una subcondición con OR entre columnas
            for (int j = 0; j < words.size(); ++j) {
                QStringList perWord;
                for (int i = 0; i < escapedCols.size(); ++i) {
                    perWord << QString("COALESCE(CAST(%1 AS TEXT), '') LIKE :pattern%2")
                                .arg(escapedCols.at(i)).arg(j);
                }
                if (!perWord.isEmpty())
                    tableConds << QString("(%1)").arg(perWord.join(" OR "));
            }
        }

        if (tableConds.isEmpty()) continue;

        QString whereClause;
        if (!matchAllWords)
            whereClause = tableConds.join(" OR ");
        else
            whereClause = tableConds.join(" AND ");

        QString escTable = QString::fromUtf8(
            driver->escapeIdentifier(table, QSqlDriver::TableName)
                .toStdString().c_str());
        QString escLibro = QString::fromUtf8(
            driver->escapeIdentifier(fieldsForAllTablesSearch[0x0], QSqlDriver::FieldName)
                .toStdString().c_str());
        QString escFolio = QString::fromUtf8(
            driver->escapeIdentifier(fieldsForAllTablesSearch[0x1], QSqlDriver::FieldName)
                .toStdString().c_str());
        QString escNumero = QString::fromUtf8(
            driver->escapeIdentifier(fieldsForAllTablesSearch[0x2], QSqlDriver::FieldName)
                .toStdString().c_str());

        QString sel = QString("SELECT %1, %2, %3 FROM %4 WHERE (%5)")
                          .arg(escLibro, escFolio, escNumero, escTable, whereClause);
        selects << sel;
    }

    if (selects.isEmpty())
        return false;
    QString sql = selects.join(" UNION ALL ");
    qDebug() << "SQL:" << sql;
    QSqlQuery q(m_db);
    if (!q.prepare(sql)) {
        return false;
    }

    // Bindear cada palabra una vez: :pattern0, :pattern1, ...
    for (int i = 0; i < words.size(); ++i) {
        q.bindValue(QString(":pattern%1").arg(i), QString("%%1%").arg(words.at(i)));
    }
    if (!q.exec()) {
        QMessageBox::critical(this, tr("Error"),
                              tr("He encontrado un error en la consulta: %1")
                                  .arg(q.lastError().text()));
        return false;
    }
    QSqlQueryModel *resultModel = new QSqlQueryModel(this);
    resultModel->setQuery(q);
    // ventana independiente
    SearchAllWidget *resultWidget = new SearchAllWidget(text, nullptr);

    connect(resultWidget, &SearchAllWidget::rowSelected,
            this, &DatabaseTableView::searchRow);
    connect(resultWidget , &SearchAllWidget::widgetClosed,
            this, &DatabaseTableView::returnToNormalView);

    resultWidget->setModel(resultModel);
    resultWidget->show();
    return (resultModel->rowCount() > 0x0);
}



bool DatabaseTableView::searchRow(const QString &book,
                                  const QString &folio,
                                  const QString &incNumber)
{
    SelectBookWidget sel(_dbFilePath);
    CreateBookWidget::BookType type =sel.getType(book);
    setTable(book, type);

    if (!m_db.isOpen()) {
        qWarning() << "La base de datos no está abierta.";
        return false;
    }
    if (_tableName.isEmpty() || !m_model) {
        qWarning() << "No hay tabla seleccionada en el modelo.";
        return false;
    }

    QString searchFolio = folio.trimmed();
    // Si la búsqueda está vacía, quitar filtro y refrescar todo
    auto table= qobject_cast<QSqlTableModel *>(m_model);
    if (searchFolio.isEmpty()) {
        if (table){
            table->setFilter(QString());
            table->select();
        }
        return true;
    }
    QString searchInsc = incNumber.trimmed();
    // Si la búsqueda está vacía, quitar filtro y refrescar todo
    if (searchInsc.isEmpty()) {
        if (table){
            table->setFilter(QString());
            table->select();
        }
        return true;
    }
    // Obtener columnas y tipos desde PRAGMA table_info
    QStringList textColumns;
    QSqlQuery q(m_db);
    const QString pragma = QString("PRAGMA table_info(%1)")
                               .arg(m_db.driver()->escapeIdentifier(_tableName, QSqlDriver::TableName));
    if (!q.exec(pragma)) {
        qWarning() << "No se pudo consultar la estructura de la tabla:" << q.lastError().text();
        return false;
    }

    while (q.next()) {
        // PRAGMA table_info devuelve: cid, name, type, notnull, dflt_value, pk
        QString colName = q.value(0x1).toString();
        QString colType = q.value(0x2).toString().toUpper();

        // considerar tipos de texto comunes
        if ((colType.contains("CHAR") || colType.contains("CLOB") ||
             colType.contains("TEXT") || colType.contains("VARCHAR")) &&
            (colName.contains("Folio") || colName.contains("Numero_de_inscripcion"))) {
            textColumns << m_db.driver()->escapeIdentifier(colName, QSqlDriver::FieldName);
        }
    }

    if (textColumns.isEmpty()) {
        qWarning() << "No se encontraron columnas de texto en la tabla" << _tableName;
        return false;
    }

    QString escFolio= searchFolio;
    escFolio.replace("'", "''");
    QString escInsc = searchInsc;
    escInsc.replace("'", "''");

    QString folioCol, inscCol;
    for (const QString &col : std::as_const(textColumns)) {
        if (col.contains("Folio", Qt::CaseInsensitive)) folioCol = col;
        if (col.contains("Numero_de_inscripcion", Qt::CaseInsensitive)) inscCol = col;
    }

    QString filter;
    if (!folioCol.isEmpty() && !inscCol.isEmpty()) {
        filter = QString("%1 LIKE '%%2%' AND %3 LIKE '%%4%'")
        .arg(folioCol, escFolio, inscCol, escInsc);
        table->setFilter(filter);
        table->setEditStrategy(QSqlTableModel::OnRowChange);
        return table->select();
    }
    return false;
}

void DatabaseTableView::viewEditRow()
{
    if (!m_db.isOpen()) {
        qWarning() << "La base de datos no está abierta. Llama a openDatabase() primero.";
        return;
    }
    qDebug()<<"viewEditRow() -> currentType == Marriage =>"<<
        CreateBookWidget::isMarriageType(currentType);

    // Fabrica de widget
    BaseNewPersonWidg *w =
        NewPersonWidgetFactory::createForType(currentType,_parroquia,_tableName);
    if (w==nullptr) {
        qDebug() << "widget factory => widget nullptr";
        return;
    }
    w->setWindowTitle(tr("Ver o editar %1").
                      arg(CreateBookWidget::shortString(currentType)));
    QVector<QVariant> rowValues;
    QModelIndex idx = m_current_index;
    QAbstractItemModel *model = m_model ? m_model : m_view->model();
    if (model) {
        if (auto proxy = qobject_cast<QSortFilterProxyModel*>(model)) {
            idx = proxy->mapToSource(idx);
            model = proxy->sourceModel();
        }
        if (auto table = qobject_cast<QSqlTableModel*>(model)) {
            QSqlRecord rec = table->record(idx.row());
            for (int i = 0x0; i < rec.count(); ++i) rowValues.append(rec.value(i));
        } else {
            int cols = model->columnCount();
            for (int c = 0x0; c < cols; ++c) {
                rowValues.append(model->data(model->index(idx.row(), c), Qt::EditRole));
            }
        }
    } else {
        qWarning() << "No hay modelo disponible para leer la fila seleccionada";
    }

    // Pasar los valores al widget (implementar setValues en tu widget)
    w->setValues(rowValues, currentType);
    const int id=rowValues.at(0x0).toInt();
    w->setCurrentIdToShow(id);

    w->show();

    // Conectar y usar deleteLater() para evitar eliminar objetos inmediatamente dentro de callbacks
    connect(w, &BaseNewPersonWidg::widgetClosed, this, [this, w, id](bool save) {
        if (!save) {
            w->deleteLater();
            return;}
        qDebug() << "widget widgetClosed";

        // Escapar el identificador solo para la SQL manual
        QString ident = m_db.driver()->escapeIdentifier(_tableName, QSqlDriver::TableName);

        // Usar transacción para atomicidad
        if (!m_db.transaction()) {
            qWarning() << "No se pudo iniciar la transacción:" << m_db.lastError().text();
        }

        QSqlQuery *updateQuery = new QSqlQuery(m_db); // Cambiado el nombre de la variable para mayor claridad
        SQLEngine s;
        s.setSqlQuery(updateQuery);

        // *** CAMBIO CLAVE #1 ***
        // Obtenemos el ID del registro que estamos editando. Ya lo guardamos en el widget.
        const int recordId = id;

        // En lugar de s.insertPerson, llamamos a un nuevo método s.updatePerson.
        // Este método debe ser implementado en tu clase SQLEngine.
        QString sql=s.updatePersonSQL(ident, currentType, recordId);
        QVector<QVariant> newValues = w->allValues();

        if (!updateWith(sql, newValues)){
            qCritical() << "Error al actualizar:" << updateQuery->lastError().text();
            QMessageBox::critical(this, tr("Error"),
                                  tr("Error al actualizar:\n%1").
                                  arg(m_lastError.text()));
            if (m_db.isOpen()) m_db.rollback();
        } else {
            // Commit y actualizar la vista
            if (!m_db.commit())
                qWarning() << "No se pudo hacer commit:" << m_db.lastError().text();

            if (m_model) {
                auto table = qobject_cast<QSqlTableModel *>(m_model);
                if (table){
                    // *** CAMBIO CLAVE #2 ***
                    // No eliminamos la fila ni volvemos a setear la tabla.
                    // Simplemente volvemos a seleccionar los datos del modelo.
                    // Esto refrescará la vista con los valores actualizados de la base de datos.
                    table->select();
                }                
                orderByCorrespondingDate();
            }
        }
        w->deleteLater();
    });
}



bool DatabaseTableView::dropTable(const QString &tableName)
{
    if (!m_db.isOpen()) {
        qWarning() << "Database is not open";
        return false;
    }

    //llamar un dialog "¿está seguro de eliminar la tabla?"

    QSqlDriver *driver = m_db.driver();
    if (!driver) {
        qWarning() << "No SQL driver available";
        return false;
    }

    // Validar el nombre de la tabla (permitir solo identificadores simples)
    QRegularExpression re(QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));
    if (!re.match(tableName).hasMatch()) {
        qWarning() << "Invalid table name:" << tableName;
        return false;
    }

    // Escapar el identificador según el driver
    QString escaped = driver->escapeIdentifier(tableName, QSqlDriver::TableName);
    QString sql = QStringLiteral("DROP TABLE IF EXISTS %1").arg(escaped);

    QSqlQuery q(m_db);
    if (!q.exec(sql)) {
        qWarning() << "Failed to drop table" << tableName << ":" << q.lastError().text();
        return false;
    }
    tables.removeAll(tableName);
    return true;
}

void DatabaseTableView::orderByCorrespondingDate()
{
    if (!m_model) return;

    // correspondingDateField debe ser el nombre de columna tal cual como está en la tabla,
    // sin comillas ni escape. fieldIndex busca por el nombre "simple".
    QString correspondingDateField = SQLEngine().getDateFieldName(currentType);
    int col=-0x1;
    if (auto table = qobject_cast<QSqlTableModel*>(m_model)){
        col= table->fieldIndex(correspondingDateField);
    }
    if (col == -0x1) {
        qWarning() << "Campo de fecha no encontrado en el modelo:" << correspondingDateField;
        return;
    }

    //  ascendente
    if (auto table=qobject_cast<QSqlTableModel*>(m_model))
        table->setSort(col, Qt::AscendingOrder);
    // Aplicar el orden
    if (auto table = qobject_cast<QSqlTableModel*>(m_model)){
        if (!table->select()) {
            qWarning() << "Error al ordenar/seleccionar modelo:" << modelLastError().text();
        }
    }
    // Se actualiza la vista
    refresh();
}


