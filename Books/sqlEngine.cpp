#include "sqlEngine.h"
#include "PeopleList/PersonWidgets/basenewpersonwidg.h"
//qt
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>


const QString &SQLEngine::createBookSQLString(const CreateBookWidget::BookType &type,
                                              const QString &ident)
{
    static
        QString s;
    s.clear();
    s.append(
    QString(
        "CREATE TABLE IF NOT EXISTS %1 ("
        "Id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Libro TEXT NOT NULL, "
        "Folio TEXT NOT NULL, "
        "Numero_de_inscripcion TEXT NOT NULL, "
            ).arg(ident));

    //para libros de una sola persona(bautismo, defuncion y confirmacion)
    if (CreateBookWidget::isSinglePersonType(type)) {
        s.append(
            "Primer_Apellido TEXT NOT NULL, "
            "Segundo_Apellido TEXT NOT NULL, "
            "Nombres TEXT NOT NULL, ");
    }

    //para libro de bautismo
    if (CreateBookWidget::isBaptismType(type)) {
        s.append("Fecha_de_nacimiento DATE NOT NULL, ");
        s.append("Lugar_de_nacimiento TEXT NOT NULL, ");
        s.append("Fecha_de_bautismo DATE NOT NULL, ");

        s.append("Hijo_de_Padre TEXT NOT NULL, ");
        s.append("Naturalidad_del_padre TEXT NOT NULL, ");
        s.append("Hijo_de_madre TEXT NOT NULL, ");
        s.append("Naturalidad_de_madre TEXT NOT NULL, ");

        s.append("Abuelo_paterno TEXT NOT NULL, ");
        s.append("Naturalidad_abuelo_paterno TEXT NOT NULL, ");
        s.append("Abuela_paterna TEXT NOT NULL, ");
        s.append("Naturalidad_abuela_paterna TEXT NOT NULL, ");

        s.append("Abuelo_materno TEXT NOT NULL, ");
        s.append("Naturalidad_abuelo_materno TEXT NOT NULL, ");
        s.append("Abuela_materna TEXT NOT NULL, ");
        s.append("Naturalidad_abuela_materna TEXT NOT NULL, ");

        s.append("Padrino TEXT NOT NULL, ");
        s.append("Madrina TEXT NOT NULL, ");
        s.append("Ministro TEXT NOT NULL, ");
    } else
        //Libro de matrimonios
    if (CreateBookWidget::isMarriageType(type)) {
        s.append("Contrayente_El TEXT NOT NULL, ");
        s.append("Contrayente_Ella TEXT NOT NULL, ");
        s.append("Lugar_de_nacimiento_El TEXT NOT NULL, ");
        s.append("Lugar_de_nacimiento_Ella TEXT NOT NULL, ");
        s.append("Fecha_del_Matrimonio DATE NOT NULL, ");

        s.append("Nombre_Padre_El TEXT NOT NULL, ");
        s.append("Nombre_Madre_El TEXT NOT NULL, ");

        s.append("Nombre_Padre_Ella TEXT NOT NULL, ");
        s.append("Nombre_Madre_Ella TEXT NOT NULL, ");

        s.append("Testigo_1 TEXT NOT NULL, ");
        s.append("Testigo_2 TEXT NOT NULL, ");

        s.append("Padrino_1 TEXT NOT NULL, ");
        s.append("Padrino_2 TEXT NOT NULL, ");
        s.append("Presbitero TEXT NOT NULL, ");
    } else
        //Libro de Defunciones
    if (CreateBookWidget::isDefunctionType(type)) {
        s.append("Fecha_de_Excequias DATE NOT NULL, ");
        s.append("Fecha_de_muerte DATE NOT NULL, ");

        s.append("Causa_de_la_muerte TEXT NOT NULL, ");
        s.append("Edad TEXT NOT NULL, ");

        s.append("Padre TEXT NOT NULL, ");
        s.append("Madre TEXT NOT NULL, ");
        s.append("Ministro TEXT NOT NULL, ");
    } else
        //Libro de Confirmaciones
    if (CreateBookWidget::isConfirmationType(type)) {
        s.append("Fecha_de_Confirmacion DATE NOT NULL, ");
        s.append("Padrino_o_Madrina TEXT NOT NULL, ");
        s.append("Ministro TEXT NOT NULL, ");
    }

    s.append("Notas_Marginales TEXT NOT NULL, "
             "Otros_datos TEXT NOT NULL)");
    return s;
}

// helper en SQLEngine
void SQLEngine::appendFields(QString &sql, const QStringList &fields, InsertType values
                              , bool ending)
{
    if (fields.isEmpty()) return;

    if (values == Columns) {
        // columnas: "Primer_Apellido, Segundo_Apellido, Nombres..."
        sql.append(fields.join(", "));
        if (!ending)
            sql.append(", ");
        for (const QString &f : fields) {
            m_fields << f;
        }
    } else {
        // placeholders: ":Primer_Apellido, :Segundo_Apellido, :Nombres..."
        QStringList placeholders;
        placeholders.reserve(fields.size());
        for (const QString &f : fields) {
            m_fields << f;
            QString ph = ":" + f;
            placeholders << ph;
            allFieldsForBind << ph; // almacenar para bind posterior
        }
        sql.append(placeholders.join(", "));
        if (!ending)
            sql.append(", ");
    }
}


void SQLEngine::commonInsert(QString &sql, InsertType values)
{
    static const QStringList fields = {
        "Libro", "Folio", "Numero_de_inscripcion"
    };
    appendFields(sql, fields, values);

}

void SQLEngine::singlePersonCommonInsert(QString &sql, InsertType values,
                                          const CreateBookWidget::BookType &book_type)
{
    if (!CreateBookWidget::isSinglePersonType(book_type))
        return;

    static const QStringList fields = {
        "Primer_Apellido", "Segundo_Apellido", "Nombres"
    };

    appendFields(sql, fields, values);

}


void SQLEngine::finalAppends(QString &sql, InsertType values)
{    
    static const QStringList fields = {
        "Notas_Marginales", "Otros_datos"
    };

    appendFields(sql, fields, values, true);

}


void SQLEngine::baptismInsert(QString &sql,InsertType values,
                               const CreateBookWidget::BookType &book_type)
{
    if (!CreateBookWidget::isBaptismType(book_type)) return;
    static const QStringList fields = {
                                       "Fecha_de_nacimiento",
                                       "Lugar_de_nacimiento",
                                       "Fecha_de_bautismo",

                                       "Hijo_de_Padre",
                                       "Naturalidad_del_padre",
                                       "Hijo_de_madre",
                                       "Naturalidad_de_madre",

                                       "Abuelo_paterno",
                                       "Naturalidad_abuelo_paterno",
                                       "Abuela_paterna",
                                       "Naturalidad_abuela_paterna",

                                       "Abuelo_materno",
                                       "Naturalidad_abuelo_materno",
                                       "Abuela_materna",
                                       "Naturalidad_abuela_materna",

                                       "Padrino",
                                       "Madrina",
                                       "Ministro"
    };

    appendFields(sql, fields, values);

}

void SQLEngine::marriageInsert(QString &sql, InsertType values,
                                const CreateBookWidget::BookType &book_type)
{
    if (!CreateBookWidget::isMarriageType(book_type)){
        return;
    }
    static const QStringList fields = {
                                       "Contrayente_El",
                                       "Contrayente_Ella",
                                       "Lugar_de_nacimiento_El",
                                       "Lugar_de_nacimiento_Ella",
                                       "Fecha_del_Matrimonio",

                                       "Nombre_Padre_El",
                                       "Nombre_Madre_El",

                                       "Nombre_Padre_Ella",
                                       "Nombre_Madre_Ella",

                                       "Testigo_1",
                                       "Testigo_2",

                                       "Padrino_1",
                                       "Padrino_2",
                                       "Presbitero"};
    appendFields(sql,fields,values);


}

void SQLEngine::defunctionInsert(QString &sql, InsertType values,
                                  const CreateBookWidget::BookType &book_type)
{
    if (!CreateBookWidget::isDefunctionType(book_type)){
        return;
    }
    static const QStringList fields = {
        "Fecha_de_Excequias",
        "Fecha_de_muerte",

        "Causa_de_la_muerte",
        "Edad",

        "Padre",
        "Madre",
        "Ministro"
    };

    appendFields(sql, fields, values);


}

void SQLEngine::confirmationInsert(QString &sql, InsertType values,
                                    const CreateBookWidget::BookType &book_type)
{
    if (!CreateBookWidget::isConfirmationType(book_type)){
        return;
    }
    static const QStringList fields = {
        "Fecha_de_Confirmacion",
        "Padrino_o_Madrina",
        "Ministro",
    };

    appendFields(sql, fields, values);


}

void SQLEngine::completeInsert(QString &sql, CreateBookWidget::BookType book_type,
                                InsertType values)
{
    allFieldsForBind.clear();
    m_fields.clear();

    commonInsert(sql, values);
    singlePersonCommonInsert(sql, values, book_type);
    baptismInsert(sql, values, book_type);
    marriageInsert(sql, values, book_type);
    defunctionInsert(sql, values, book_type);
    confirmationInsert(sql, values, book_type);
    finalAppends(sql, values);
}

bool SQLEngine::insertPerson(BaseNewPersonWidg *w, const QString &ident,
                              CreateBookWidget::BookType book_type)
{
    // Preparar la cadena sql
    QString sql = QString("INSERT INTO %1 (").arg(ident);
    completeInsert(sql, book_type, Columns);
    sql.append(") VALUES (");  //**************************************************
    completeInsert(sql, book_type, Placeholders);
    sql.append(")");

    qDebug() << "SQL a ejecutar:" << sql;

    if (!insert->prepare(sql)) {
        qWarning() << "prepare error:" << insert->lastError().text();
        return false;
    }
    const QVector<QVariant> allValues (w->allValues());
    qDebug() <<"campos son:"<< allFieldsForBind.size();
    qDebug() << "los valores son:"<<allValues.size();
    qDebug() <<"allValues"<<allValues;
    if (allFieldsForBind.size() != allValues.size()) {
        qDebug()<< "****************** ERROR EN DISEÑO *************************";
        return false;
    }
    for (int i = 0x0; i < allFieldsForBind.size(); ++i) {
        insert->bindValue(allFieldsForBind.at(i), allValues.at(i));
    }

    if (!insert->exec()) {
        qWarning() << "exec error:" << insert->lastError().text();
        qWarning() << "lastQuery:" << insert->lastQuery();
        return false;
    }
    return true;
}

const QVector<QString> &SQLEngine::getFields(CreateBookWidget::BookType book_type)
{
    QString sql;  //solo uso sql para poder llamar a completeInsert y tomar los mfields
    completeInsert(sql, book_type, Columns);
    return m_fields;
}

const QString &SQLEngine::getDateFieldName(CreateBookWidget::BookType book_type)
{
    static QString s;
    s.clear();
    if (CreateBookWidget::isBaptismType(book_type)){
        s.append("Fecha_de_bautismo");
    }
    if (CreateBookWidget::isMarriageType(book_type)){
        s.append("Fecha_del_Matrimonio");
    }
    if (CreateBookWidget::isDefunctionType(book_type)){
        s.append("Fecha_de_Excequias");
    }
    if (CreateBookWidget::isConfirmationType(book_type)){
        s.append("Fecha_de_Confirmacion");
    }
    return s;
}

const QVector<QString> &SQLEngine::getAllFields()
{
    static QVector<QString> v;
    v.clear();
    v.append(getFields(CreateBookWidget::GB));
    v.append(getFields(CreateBookWidget::GM));
    v.append(getFields(CreateBookWidget::GD));
    v.append(getFields(CreateBookWidget::GC));
    return v;
}


const QString &SQLEngine::updatePersonSQL(const QString& tableName,
                             CreateBookWidget::BookType type, int id) {
    static QString sql;
    sql.clear();
    // 1. Obtener los nuevos valores del widget.
    //    Deberás tener un método en el widget que te devuelva los datos,
    //    similar a como tienes setValues() para establecerlos.

    QVector<QString> columns = getFields(type);

    // 2. Construir la consulta UPDATE.
    //    Es MUY recomendable usar consultas preparadas para evitar inyección SQL.
    sql = QString("UPDATE %1 SET").arg(tableName);
    for (int i = 0x0; i < columns.size(); ++i) {
        sql.append(QString(" %1 = ?").arg(columns.at(i)));
        if (i < columns.size() - 0x1)
            sql.append(",");
        //    Debes reemplazar "columna1, columna2, ..." con los nombres reales de tus columnas.
    }
    sql.append(QString(" WHERE id = %1").arg(id));

    return sql;

}

