#ifndef LRCFINDER_H
#define LRCFINDER_H

#include <myimage.h>
#include <opticalflow.h>

class LRCfinder
{
public:
    LRCfinder() = delete;

    static MyImage find(const OpticalFlow &flow1, const OpticalFlow &flow2);

signals:

public slots:
};

#endif // LRCFINDER_H
