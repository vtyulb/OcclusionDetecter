#include "lrcfinder.h"

#define min(a,b) ((a) < (b) ? (a) : (b))

MyImage LRCfinder::find(const OpticalFlow &flow1, const OpticalFlow &flow2) {
    MyImage res(flow1.width(), flow1.height());

    for (int i = 0; i < flow1.height(); i++)
        for (int j = 0; j < flow1.width(); j++) {
            int in = flow1[i][j].dy + i;
            int jn = flow1[i][j].dx + j;

            res[i][j] = fabs(flow2[in][jn].dy + in - i) +
                        fabs(flow2[in][jn].dx + jn - j);

            res[i][j] = min(res[i][j] * 30, 250);
        }

    return res;
}
