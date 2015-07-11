#include <QRgb>
#include <QColor>

#include "imageconverter.h"

MyImage ImageConverter::convert(const QImage im) {
    MyImage image;
    image.height = im.height();
    image.width = im.width();
    image.bright = new byte*[im.height() + 2] + 1;

    image.bright[-1] = new byte[im.width()];
    image.bright[im.height()] = new byte[im.width()];

    for (int i = 0; i < im.height(); i++) {
        image.bright[i] = new byte[im.width()];

        for (int j = 0; j < im.width(); j++) {
            QColor color = QColor::fromRgb(im.pixel(j, i));
            image[i][j] = 0.299 * color.red()  + 0.587 * color.green() + 0.114 * color.blue();
        }
    }

    return image;
}
