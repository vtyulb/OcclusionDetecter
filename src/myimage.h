#ifndef MYIMAGE
#define MYIMAGE

#include <QDebug>

typedef unsigned char byte;

struct MyImage {
    int width;
    int height;

    byte **bright;

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
};

#endif // MYIMAGE

