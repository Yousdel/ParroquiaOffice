#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>



/**
 * @brief Widget Acerca de...
 */
class AboutWidget : public QWidget
{
public:
    explicit AboutWidget(QWidget *parent = nullptr);

    const QString &
    aboutString() const
    {
        return m_string;
    }

    /**
     * @brief setAppNameString() es
     * para especificar el nombre del producto y
     * debe ser llamado antes de show()
     */
    void
    setAppNameString(const QString &s);

    /**
     * @brief el icono puede ser una ruta del archivo
     * o puede ser un recurso de Qt. Llamar antes de show()
     */
    void
    setIconFilename(const QString &filename)
    {
        iconFileName=filename;
    }

    /**
     * @brief el archivo de la imagen de background,
     * si se desea respetar la transparencia , preferiblemente
     * un .xpm, puede ser una ruta del archivo,
     * o puede ser un recurso de Qt. Llamar antes de show()
     */
    void
    setBackgroundPixmapFilename
        (const QString &filename)
    {
        backgroundPixmapFilename = filename;
    }

    /**
     * @brief especificar cada color en ingles.
     * Llamar antes de show()
     */
    void setButtonColors(
            const QString &background,
            const QString &text)
    {
        btnTextColor = text;
        btnBackgColor = background;
    }

    /**
     * @brief especificar cada color en ingles,
     * los colores son los que reflejara el boton
     * al pasar por encima del mismo el mouse.
     * Llamar antes de show()
     */
    void
    setButtonHoverColors(
            const QString &textColor,
            const QString &backgroundColor)
    {
        hvTxtColor=textColor;
        hvBgColor=backgroundColor;
    }

protected:
    void showEvent(QShowEvent *event) override
    {
        addWidgets();
        (void) event;
    }

private:
    QString m_string,
    iconFileName,
    backgroundPixmapFilename,
    btnBackgColor,
    btnTextColor,
    hvBgColor,
    hvTxtColor;

    void addWidgets();
};

#endif // ABOUTWIDGET_H
