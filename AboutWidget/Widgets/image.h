#ifndef IMAGE_H
#define IMAGE_H

//qt
#include <QWidget>
#include <QLabel>
//app


/**
 * @brief Widget con una imagen
 */
class Image : public QLabel
{
    Q_OBJECT
public:
    //ctor
    Image(QWidget *parent, int w, int h);

    //metodos
    void
    assignPixmap(const QString &filename,
                int width, int height);

    void
    moveToPoint(int x, int y)
    {
        move(QPoint(x,y));
        _x=x; _y=y;
    }

    void
    point(int &x, int &y)
    {
        x=_x; y=_y;
    }

    //getters
     int myWidth() const { return _width; }
     int myHeight() const { return _height; }
     const QString  &filename() const { return _filename; }

public slots:


private:    
    int
    _x,_y;

    bool
    firstAssignment=true;

    const int
    _width, _height;

    QString
    _filename;
    //metodos



signals:

};

#endif // POSITION_H
