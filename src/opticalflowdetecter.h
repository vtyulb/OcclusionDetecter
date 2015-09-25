#ifndef OPTICALFLOWDETECTER_H
#define OPTICALFLOWDETECTER_H

#include <QImage>

#include <opticalflow.h>
#include <myimage.h>

class OpticalFlowDetecter {
    public:
        OpticalFlowDetecter() = delete;

        static OpticalFlow detect(const MyImage&, const MyImage&);
        static OpticalFlow useMediaLabAlgo(const QString);
        static inline int cmp(const MyImage&, const MyImage&, int x1, int y1, int x2, int y2);
        static inline int cmp_binary(const MyImage&, const MyImage&, int x1, int y1, double x2, int y2);
        static inline int cmp_det(const byte*, double);
};

#endif // OPTICALFLOWDETECTER_H
