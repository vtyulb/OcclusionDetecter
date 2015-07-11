#include <occlusions.h>
#include <displayer.h>

Occlusions::Occlusions()
{
    res = QImage(100, 100, QImage::Format_ARGB32);
}

void Occlusions::display() {
//    Displayer *d = Displayer::getDisplayer();
//    d->setImage(res);
}

void Occlusions::setRes(const QImage &im) {
    res = im;
}

QImage Occlusions::getRes() {
    return res;
}
