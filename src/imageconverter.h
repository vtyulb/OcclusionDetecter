#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QImage>

#include <myimage.h>

class ImageConverter
{
    public:
        ImageConverter() = delete;

        static MyImage convert(const QImage);
};

#endif // IMAGECONVERTER_H
