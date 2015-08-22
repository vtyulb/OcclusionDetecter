#ifndef CVOPTICALFLOWDETECTER_H
#define CVOPTICALFLOWDETECTER_H

#include <opticalflowdetecter.h>

class CVOpticalFlowDetecter
{
    public:
        CVOpticalFlowDetecter() = delete;

        static OpticalFlow detect(const MyImage&, const MyImage&);
};

#endif // CVOPTICALFLOWDETECTER_H
