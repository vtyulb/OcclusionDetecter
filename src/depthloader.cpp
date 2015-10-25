#include "depthloader.h"

#include <QFile>

MyImage DepthLoader::load(QString name, int width, int height) {
    QFile f(name);
    f.open(QIODevice::ReadOnly);

    MyImage res(width, height);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            char c;
            f.read(&c, 1);
            res[i][j] = (unsigned char)c;
        }

    return res;
}
