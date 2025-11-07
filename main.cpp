
#include <QApplication>
#include <QWidget>
#include <QTranslator>
#include <QSqlDatabase>
#include <QDebug>
#include <QObject>
#include "PeopleList/Tools/AppTitle.h"
#include "PeopleList/appMainWidget.h"
#include "PeopleList/splash.h"



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ParroquiaOffice_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        QMessageBox::critical(nullptr,
                              QObject::tr("%1").arg(APPTITLE),
                              QObject::tr("No te preocupes, el  programa"
                                          " funciona bien, el sistema operativo "
                                          "no contiene SQLite,"
                                          " necesario para poder crear o abrir"
                                          " la base de Datos "
                                          "de %1. Trata de conseguir que ese módulo esté"
                                          " instalado en tu sistema operativo y vuelve a "
                                          "ejecutar el programa").arg(APPTITLE));
        return 0x0;
    }

    //presentacion
    Splash splash(QPixmap(":/Icons/splash.svg"));
    splash.show();

    //ventana principal de la app
    AppMainWidget win;
    QTimer::singleShot(3000, &win, [&win](){ win.show(); });


    return app.exec();
}
