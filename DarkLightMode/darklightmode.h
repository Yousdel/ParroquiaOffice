#ifndef DARKLIGHTMODE_H
#define DARKLIGHTMODE_H

#include <QWidget>
#include <QApplication>
#include <QPalette>
#include <QStyleFactory>
#include <QPushButton>
#include <QCloseEvent>
//app
#include "DarkLightMode/dark_files.h"
/**
 * @brief widget con un boton que cambia la interfaz de usuario
 * de claro a oscuro y viceversa
 */
class DarkLightMode : public QWidget
{
    Q_OBJECT

private:
    QPalette originalPalette = qApp->palette();
    bool dark = false;
    QPushButton *toggleDarkBtn=nullptr;

    void setDarkPalette(QApplication &app)
    {
        // Usar Fusion para que la paleta tenga efecto consistente
        app.setStyle(QStyleFactory::create("Fusion"));

        QPalette dark;
        dark.setColor(QPalette::Window, QColor(37,37,38));
        dark.setColor(QPalette::WindowText, Qt::white);
        dark.setColor(QPalette::Base, QColor(30,30,30));          // fondos de QLineEdit, QTextEdit
        dark.setColor(QPalette::AlternateBase, QColor(45,45,45));
        dark.setColor(QPalette::ToolTipBase, Qt::white);
        dark.setColor(QPalette::ToolTipText, Qt::white);
        dark.setColor(QPalette::Text, Qt::white);
        dark.setColor(QPalette::Button, QColor(53,53,53));
        dark.setColor(QPalette::ButtonText, Qt::white);
        dark.setColor(QPalette::BrightText, Qt::red);
        dark.setColor(QPalette::Link, QColor(42,130,218));
        dark.setColor(QPalette::Highlight, QColor(42,130,218));
        dark.setColor(QPalette::HighlightedText, Qt::black);

        // Colores para widgets deshabilitados
        dark.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127,127,127));
        dark.setColor(QPalette::Disabled, QPalette::Text, QColor(127,127,127));
        dark.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127,127,127));

        app.setPalette(dark);
    }
private slots:
    void toggleDark()
    {
        if (!dark) {
            setDarkPalette(*qApp);
            QString myGlobalStyleSheet=
                    "QWidget {"
                    "background-color: #252526;"
                    "color: #e6e6e6;"
                    "}"

                    "QPushButton {"
                    "background-color: #3c3f41;"
                    "color: #e6e6e6;"
                    "border: 1px solid #555;"
                    "padding: 4px;"
                    "border-radius: 4px;"
                    "}"
                    "QPushButton:hover { background-color: #505354; }"
                    "QPushButton:pressed { background-color: #2d2f30; }"

                    "QLabel { color: #e6e6e6; }"

                    "QLineEdit, QTextEdit, QPlainTextEdit {"
                    "background-color: #1e1e1e;"
                    "color: #e6e6e6;"
                    "border: 1px solid #444;"
                    "}"

                    "QTableView {"
                    "background-color: #232324;"
                    "gridline-color: #3a3a3a;"
                    "color: #e6e6e6;"
                    "}"
                    "QHeaderView::section {"
                    "background-color: #2b2b2b;"
                    "color: #e6e6e6;"
                    "padding: 4px;"
                    "}"

                    "QScrollBar:vertical {"
                    "background: #2b2b2b;"
                    "width: 12px;"
                    "}"
                    "QScrollBar::handle:vertical {"
                    "background: #505354;"
                    "border-radius: 6px;"
                    "}";

            qApp->setStyleSheet(myGlobalStyleSheet); // opcional
            toggleDarkBtn->setIcon(QIcon(":/dark_Icons/sun.svg"));
            toggleDarkBtn->setText(tr("Modo día"));
        } else {
            qApp->setPalette(originalPalette);
            qApp->setStyleSheet(""); // o stylesheet para claro
            toggleDarkBtn->setIcon(QIcon(":/dark_Icons/moon.svg"));
            toggleDarkBtn->setText(tr("Modo noche"));
        }
        dark = !dark;
        DarkFiles::writeToFile(m_path, dark);
    }


public:
    DarkLightMode(QString pathWhereSaveStatus, QWidget *parent = nullptr);


private:
    QString m_path;
signals:

};

#endif // DARKLIGHTMODE_H
