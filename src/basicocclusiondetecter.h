#ifndef BASICOCCLUSIONDETECTER_H
#define BASICOCCLUSIONDETECTER_H

#include <abstractocclusiondetecter.h>

class BasicOcclusionDetecter : public AbstractOcclusionDetecter
{
    public:
        BasicOcclusionDetecter();

        Occlusions getOcclusions(QImage, QImage);

    private:
        QImage prev;
};

#endif // BASICOCCLUSIONDETECTER_H
