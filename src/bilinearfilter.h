#ifndef BILINEARFILTER_H
#define BILINEARFILTER_H

#include <myimage.h>

class BilinearFilter
{
    public:
        BilinearFilter() = delete;

        static MyImage apply(const MyImage &target, const MyImage &colors);
};

#endif // BILINEARFILTER_H
