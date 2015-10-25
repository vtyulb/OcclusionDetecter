#ifndef DEPTHLOADER_H
#define DEPTHLOADER_H

#include <myimage.h>
#include <QString>

class DepthLoader
{
public:
    DepthLoader() = delete;

    static MyImage load(QString, int width, int height);

signals:

public slots:
};

#endif // DEPTHLOADER_H
