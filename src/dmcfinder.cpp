#include "dmcfinder.h"

// occ as I think now

MyImage DMCfinder::find(const MyImage &dm) {
    MyImage res(dm.width, dm.height);

    for (int i = 0; i < dm.height; i++)
        for (int j = 1; j < dm.width; j++)
            if (dm[i][j]-dm[i][j - 1] > 3) {
                for (int k = 0; k < (dm[i][j]-dm[i][j - 1]) / 1.3; k++)
                    res[i][j - k] = 255;
            }

    return res;
}
