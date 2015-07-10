#ifndef ABSTRACTOCCLUSIONDETECTER_H
#define ABSTRACTOCCLUSIONDETECTER_H

#include <QImage>

#include <occlusions.h>

class AbstractOcclusionDetecter {
    public:
        AbstractOcclusionDetecter() {};
        virtual Occlusions getOcclusions(QImage, QImage) {};
};

#endif // ABSTRACTOCCLUSIONDETECTER_H
