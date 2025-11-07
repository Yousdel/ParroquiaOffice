#ifndef BUTTON_H
#define BUTTON_H


#include <QPushButton>



class Button : public QPushButton
{
public:
    Button(const QString &text,
           QWidget *parent=nullptr);

    /**
     * llamar antes de show()
     */
    void
    setBackgroundColor(const QString &color)
    {
        background_color = color;
    }

    /**
     * llamar antes de show()
     */
    void
    setTextColor(const QString &color)
    {
        text_color = color;
    }

    /**
     * @brief Colores al pasar el mouse por encima.
     *  Llamar antes de show()
     */
    void
    setHoverColors(
            const QString &textColor,
            const QString &backgroundColor)
    {
        hvTxtColor=textColor;
        hvBgColor=backgroundColor;
    }

protected:
    void showEvent(QShowEvent *) override
    {
        setAppareance();
    }

private:
    void
    setAppareance();

    QString background_color,
        text_color,
    hvBgColor,
    hvTxtColor;
};

#endif // BUTTON_H
