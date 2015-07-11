#ifndef OPTICALFLOWDETECTER_H
#define OPTICALFLOWDETECTER_H

#include <QImage>

#include <opticalflow.h>
#include <myimage.h>

#define step 4

class OpticalFlowDetecter {
    public:
        OpticalFlowDetecter() = delete;

        static OpticalFlow detect(const MyImage&, const MyImage&);
        static inline int cmp(const MyImage&, const MyImage&, int x1, int y1, int x2, int y2);
};

#endif // OPTICALFLOWDETECTER_H
