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
        MyImage previousDepth;
        MyImage prediction;
        bool hasPrevious = false;

        Occlusions averageIt(Occlusions);
        MyImage apply(const MyImage&, const OpticalFlow&);

        MyImage getMEFaith(QImage);
        MyImage getMEtimeFaith(const OpticalFlow&);

        MyImage stabilize(MyImage prev, MyImage cur, OpticalFlow flow, MyImage faithMap);

        void basicTimeFiltration(MyImage &image);
};

#endif // BASICOCCLUSIONDETECTER_H
