#ifndef MYIMAGE
#define MYIMAGE

#include <assert.h>

#include <QImage>
#include <QFile>
#include <QColor>
#include <QTextStream>

#include <opticalflow.h>

typedef unsigned char byte;

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct MyImage {
    int width;
    int height;

    byte *bright;

    MyImage(const MyImage &src) {
        height = src.height;
        width = src.width;

        init();
        memcpy(bright - width, src.bright - width, (height + 2) * width);
    }

    MyImage& operator =(const MyImage &src) {
        height = src.height;
        width = src.width;

        init();
        memcpy(bright - width, src.bright - width, (height + 2) * width);

        return *this;
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
                (*this)[i][j] = flow[i][j].dist();

    }

    const byte* operator[](int y) const {
        if (y >= 0 && y < height)
            return bright + width * y;
        else
            return bright;
    }

    byte* operator[](int y)  {
        if (y >= 0 && y < height)
            return bright + width * y;
        else
            return bright;
    }

    void init() {
        bright = new byte[(height + 2) * width] + width;
        memset(bright - width, 0, (height + 2) * width);
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
        delete[] (bright - width);
    }

    MyImage(MyImage&& tmp) {
        height = tmp.height;
        width = tmp.width;

        init();
        memcpy(bright - width, tmp.bright - width, (height + 2) * width);
    }

    OpticalFlow toOF() {
        OpticalFlow res(width, height);

        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                res[i][j] = Point(-((*this)[i][j] - 128.0) / 4.0);

       /* QFile f("/home/vlad/tst.txt");
        f.open(QIODevice::WriteOnly);
        QTextStream s(&f);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                s << (*this)[i][j] << " ";
            s << "\n";
        }*/

        return res;
    }

    MyImage& operator =(MyImage &&tmp) {
        height = tmp.height;
        width = tmp.width;

        init();
        memcpy(bright - width, tmp.bright - width, (height + 2) * width);

        return *this;
    }

    MyImage() = delete;
};

#endif // MYIMAGE

