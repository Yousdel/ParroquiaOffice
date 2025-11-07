#ifndef LITTLEFONTLABEL_H
#define LITTLEFONTLABEL_H

#include <QLabel>



/**
 * @brief Label de pequeño tamaño de fuente
 */
class LittleFontLabel : public QLabel
{
public:
    LittleFontLabel(QWidget *parent = nullptr);
    LittleFontLabel(
            const QString &text,
            QWidget *parent = nullptr);

private:
    void setLittleFont();
};

#endif // LITTLEFONTLABEL_H
