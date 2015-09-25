#include "occfinder.h"

#define max(a, b) ((a) < (b) ? b : a)

MyImage OCCfinder::find(const OpticalFlow &flow1, const OpticalFlow &flow2) {
    MyImage res(flow1.width(), flow1.height());

    for (int i = 1; i < flow1.height(); i++)
        for (int j = 1; j < flow1.width(); j++) {
            int verr = fabs(flow1[i][j].dx - flow1[i - 1][j].dx) + 0.5;
            int herr = fabs(flow1[i][j].dx - flow1[i][j - 1].dx) + 0.5;
            for (int k = 0; k < verr; k++)
                for (int l = 0; l < herr; l++)
                    res[max(i - k, 0)][max(j - l, 0)] = 250;
        }

    return res;
}
