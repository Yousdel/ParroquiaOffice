// splash.h
#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QScreen>
#include <QGuiApplication>

/**
 * @brief Splash es para mostrar una imagen sola en la pantalla
 */
class Splash : public QWidget
{
    Q_OBJECT
public:
    explicit Splash(const QPixmap &pix, int millis = 4000, QWidget *parent = nullptr)
        : QWidget(parent), m_pix(pix)
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        // Si tu PNG tiene transparencia y quieres que se respete:
        setAttribute(Qt::WA_TranslucentBackground);
        setFixedSize(m_pix.size());

        // Centrar en la pantalla principal:
        QScreen *screen = QGuiApplication::primaryScreen();
        if (screen) {
            QRect sg = screen->geometry();
            move(sg.center() - rect().center());
        }

        // Cerrar automáticamente tras 'millis' milisegundos
        QTimer::singleShot(millis, this, &QWidget::close);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.drawPixmap(0, 0, m_pix);
    }

private:
    QPixmap m_pix;
};
