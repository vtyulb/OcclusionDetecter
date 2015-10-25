#include "ordfinder.h"
#include <algorithm>

using std::min;
using std::max;

MyImage ORDfinder::find(const OpticalFlow &flow1, const OpticalFlow &flow2) {
    MyImage res(flow1.width(), flow1.height());

    for (int i = 0; i < flow1.height(); i++)
        for (int j = 0; j < flow1.width(); j++)
                for (int k = 1; k < min(20, flow1.width() - j - 1); k++)
                    if (flow1[i][j].dx - k > flow1[i][j + k].dx) {
                        res[i][j] = 255;
                        res[i][j + k] = 255;
                    }

    return res;
}

