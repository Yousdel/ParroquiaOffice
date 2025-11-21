QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AboutWidget/Widgets/button.cpp \
    AboutWidget/Widgets/image.cpp \
    AboutWidget/Widgets/label.cpp \
    AboutWidget/aboutwidget.cpp \
    AboutWidget/littlefontlabel.cpp \
    Books/LineEditForTypeBooksName/lineeditWregexpval.cpp \
    Books/createbookwidget.cpp \
    Books/selectbookwidget.cpp \
    Books/sqlEngine.cpp \
    Books/suggestwidget.cpp \
    DBWidget/dbwidget.cpp \
    DarkLightMode/darklightmode.cpp \
    Field/fieldwidget.cpp \
    Field/stringforfield.cpp \
    Field/stringforfieldwidget.cpp \
    PeopleList/DropTableWidget/droptablewidget.cpp \
    PeopleList/PersonWidgets/CommonWidget/commonwidget.cpp \
    PeopleList/PersonWidgets/CommonWidget/singlepersoncommonwidget.cpp \
    PeopleList/PersonWidgets/baptismnewpersonwidg.cpp \
    PeopleList/PersonWidgets/basenewpersonwidg.cpp \
    PeopleList/PersonWidgets/confirmationnewpersonwidg.cpp \
    PeopleList/PersonWidgets/defunctionsnewpersonwidg.cpp \
    PeopleList/PersonWidgets/newmarriagewidg.cpp \
    PeopleList/PersonWidgets/newpersonwidgetfactory.cpp \
    PeopleList/ShowOrHideBtns.cpp \
    PeopleList/Tools/files.cpp \
    PeopleList/Tools/sorttablelist.cpp \
    PeopleList/appMainWidget.cpp \
    PeopleList/bookslist.cpp \
    PeopleList/databasetableview.cpp \
    PeopleList/findtextwidget.cpp \
    PeopleList/searchallwidget.cpp \
    PeopleList/splash.cpp \
    main.cpp 

HEADERS += \
    AboutWidget/Widgets/button.h \
    AboutWidget/Widgets/image.h \
    AboutWidget/Widgets/label.h \
    AboutWidget/aboutwidget.h \
    AboutWidget/littlefontlabel.h \
    Books/LineEditForTypeBooksName/lineeditWregexpval.h \
    Books/createbookwidget.h \
    Books/selectbookwidget.h \
    Books/sqlEngine.h \
    Books/suggestwidget.h \
    DBWidget/dbwidget.h \
    DarkLightMode/dark_files.h \
    DarkLightMode/darklightmode.h \
    Field/fieldwidget.h \
    Field/stringforfield.h \
    Field/stringforfieldwidget.h \
    PeopleList/DropTableWidget/droptablewidget.h \
    PeopleList/PersonWidgets/CommonWidget/commonwidget.h \
    PeopleList/PersonWidgets/CommonWidget/singlepersoncommonwidget.h \
    PeopleList/PersonWidgets/baptismnewpersonwidg.h \
    PeopleList/PersonWidgets/basenewpersonwidg.h \
    PeopleList/PersonWidgets/confirmationnewpersonwidg.h \
    PeopleList/PersonWidgets/defunctionsnewpersonwidg.h \
    PeopleList/PersonWidgets/newmarriagewidg.h \
    PeopleList/PersonWidgets/newpersonwidgetfactory.h \
    PeopleList/ShowOrHideBtns.h \
    PeopleList/Tools/AppTitle.h \
    PeopleList/Tools/files.h \
    PeopleList/Tools/sorttablelist.h \
    PeopleList/appMainWidget.h \
    PeopleList/bookslist.h \
    PeopleList/databasetableview.h \
    PeopleList/findtextwidget.h \
    PeopleList/searchallwidget.h \
    PeopleList/splash.h 

TRANSLATIONS += \
    ParroquiaOffice_es_CU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    DarkLightMode/dark_light_icons.qrc \
    images.qrc

FORMS += \
    Books/LineEditForTypeBooksName/lineeditWregexpval.ui \
    Books/createbookwidget.ui \
    PeopleList/DropTableWidget/droptablewidget.ui \
    PeopleList/PersonWidgets/CommonWidget/commonwidget.ui \
    PeopleList/PersonWidgets/CommonWidget/singlepersoncommonwidget.ui \
    PeopleList/PersonWidgets/baptismnewpersonwidg.ui \
    PeopleList/PersonWidgets/confirmationnewpersonwidg.ui \
    PeopleList/PersonWidgets/defunctionsnewpersonwidg.ui \
    PeopleList/PersonWidgets/newmarriagewidg.ui \
    PeopleList/findtextwidget.ui

RC_ICONS += icono.ico
