#ifndef OPENCVBASEDOCCLUSIONDETECTER_H
#define OPENCVBASEDOCCLUSIONDETECTER_H

#include <abstractocclusiondetecter.h>

class OpenCVBasedOcclusionDetecter: public AbstractOcclusionDetecter {
    public:
        OpenCVBasedOcclusionDetecter();

        Occlusions getOcclusions(QImage, QImage);
};

#endif // OPENCVBASEDOCCLUSIONDETECTER_H
