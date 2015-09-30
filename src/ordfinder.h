#ifndef ORDFINDER_H
#define ORDFINDER_H

#include <myimage.h>
#include <opticalflow.h>

class ORDfinder
{
public:
    ORDfinder() = delete;

    static MyImage find(const OpticalFlow &flow1, const OpticalFlow &flow2);

signals:

public slots:
};

#endif // ORDFINDER_H
