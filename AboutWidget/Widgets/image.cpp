#include "image.h"




Image::Image(QWidget *parent, int w, int h) :
    QLabel(parent), _width(w), _height(h)
{
    setMinimumSize(w, h);
    setMaximumSize(w, h);
}

void Image::assignPixmap(const QString &filename, int width, int height)
{
    setPixmap(QPixmap(filename).
              scaled(width, height,
                     Qt::KeepAspectRatio));
    if (firstAssignment){
        _filename=filename;
        firstAssignment=false;
    }
    setMinimumSize(width,height);
    setMaximumSize(width,height);
}



