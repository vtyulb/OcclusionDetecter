#include <occlusions.h>
#include <displayer.h>

Occlusions::Occlusions()
{
    res = QImage(100, 100, QImage::Format_ARGB32);
}


void Occlusions::display() {
    Displayer *d = new Displayer();
    d->setImage(res);
    d->show();
    d->repaint();
}

void Occlusions::setRes(const QImage &im) {
    res = im;
}
