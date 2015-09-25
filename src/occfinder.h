#ifndef OCCFINDER_H
#define OCCFINDER_H

#include <myimage.h>
#include <opticalflow.h>

class OCCfinder
{
public:
    OCCfinder() = delete;

    static MyImage find(const OpticalFlow &flow1, const OpticalFlow &flow2);

signals:

public slots:
};

#endif // OCCFINDER_H
