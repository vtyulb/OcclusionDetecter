#ifndef DMCFINDER_H
#define DMCFINDER_H

// disparity map check

#include <myimage.h>

class DMCfinder
{
public:
    DMCfinder() = delete;

    static MyImage find(const MyImage &dm);
signals:

public slots:
};

#endif // DMCFINDER_H
