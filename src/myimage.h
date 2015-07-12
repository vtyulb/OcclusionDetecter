#ifndef MYIMAGE
#define MYIMAGE

#include <assert.h>

#include <QImage>
#include <QColor>

#include <opticalflow.h>

typedef unsigned char byte;

struct MyImage {
    int width;
    int height;

    byte **bright;
    int *counter;



    MyImage(const MyImage &src) {
        counter = src.counter;
        bright = src.bright;
        height = src.height;
        width = src.width;

        (*counter) += 1;
    }

    MyImage(int width, int height) {
        this->height = height;
        this->width = width;
        init();
    }

    MyImage(const QImage &im) {
        height = im.height();
        width = im.width();
        init();

        for (int i = 0; i < im.height(); i++) {
            for (int j = 0; j < im.width(); j++) {
                QColor color = QColor::fromRgb(im.pixel(j, i));
                (*this)[i][j] = 0.299 * color.red()  + 0.587 * color.green() + 0.114 * color.blue();
            }
        }

    }

    MyImage(const OpticalFlow &flow) {
        height = flow.flow.size();
        width = flow.flow[0].size();
        init();

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                bright[i][j] = flow[i][j].dist() * 10;

    }

    const byte* operator[](int y) const {
        if (y >= 0 && y < height)
            return bright[y];
        else
            return bright[0];
    }

    byte* operator[](int y)  {
        if (y >= 0 && y < height)
            return bright[y];
        else
            return bright[0];
    }

    void init() {
        bright = new byte*[height + 2] + 1;
        for (int i = -1; i <= height; i++)
            bright[i] = new byte[width];

        counter = new int;
        (*counter) = 1;
    }

    void release() {
        for (int i = -1; i <= height; i++)
            delete[] bright[i];

        delete[] (bright - 1);
        delete counter;
    }

    QImage toImage() {
        QImage res(width, height, QImage::Format_RGB32);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++) {
                int a = (*this)[i][j];
                res.setPixel(j, i, QColor(a, a, a).rgb());
            }

        return res;
    }



    ~MyImage() {
        assert(*counter < 10);
        assert(*counter > 0);
        if (*counter == 1)
            release();
        else
            *counter -= 1;
    }

    MyImage(MyImage&& tmp) {
        bright = tmp.bright;
        height = tmp.height;
        width = tmp.width;
        counter = tmp.counter;
    }

    MyImage& operator =(MyImage &&a) = delete;
    MyImage& operator =(const MyImage &a) = delete;
    MyImage() = delete;
};

#endif // MYIMAGE

