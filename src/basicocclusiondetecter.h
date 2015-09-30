#ifndef BASICOCCLUSIONDETECTER_H
#define BASICOCCLUSIONDETECTER_H

#include <abstractocclusiondetecter.h>
#include <opticalflow.h>
#include <myimage.h>

class BasicOcclusionDetecter : public AbstractOcclusionDetecter
{
    public:
        BasicOcclusionDetecter();

        Occlusions getOcclusions(QImage, QImage);

    private:
        MyImage previousOcclusion;
        OpticalFlow previousFlow;
        bool hasPrevious = false;

        Occlusions averageIt(Occlusions);
        MyImage apply(const MyImage&, const OpticalFlow&);

        MyImage getMEFaith(QImage);
};

#endif // BASICOCCLUSIONDETECTER_H
