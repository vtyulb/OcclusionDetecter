#include <QDebug>

#include "opticalflowdetecter.h"

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

OpticalFlow OpticalFlowDetecter::detect(const MyImage &i1, const MyImage &i2) {
    static OpticalFlow flow;
    if (flow.flow.size() != i1.height || flow.flow[0].size() != i1.width) {
        qDebug() << "optical flow initialization";
        flow.flow.resize(i1.height);
        for (int i = 0; i < i1.height; i++) {
            flow[i].resize(i1.width);
            flow[i].fill(Point());
        }
    }

    for (int i = 0; i < i1.height; i += 8)
        for (int j = 0; j < i2.width; j += 8) {
            bool cont = true;
            while (cont) {
                cont = false;
                int cx = flow[i][j].dx;
                int cy = flow[i][j].dy;
                int res = cmp(i1, i2, j, i, j + cx, i + cy);
                for (int k = 0; k < 4; k++) {
                    int nx = cx + dx[k];
                    int ny = cy + dy[k];

                    int nres = cmp(i1, i2, j, i, j + nx, i + ny);
                    if (nres < res) {
                        cont = true;
                        res = nres;
                        flow[i][j].dx = nx;
                        flow[i][j].dy = ny;
                    }
                }
            }
        }

    //-----------------------------
    for (int i = 0; i < i1.height; i += 8)
        for (int j = 0; j < i1.width; j += 8)
            for (int k = 0; k < 8; k++)
                for (int l = 0; l < 8; l++)
                    flow[i + k][j + k] = flow[i][j];
    //-----------------------------

    return flow;
}

int OpticalFlowDetecter::cmp(const MyImage &a, const MyImage &b, int x1, int y1, int x2, int y2) {
    if (x1 + 8 > a.width || y1 + 8 > a.height || x2 + 8 > b.width || y2 + 8 > b.height ||
            x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
        return 100500;

    int res = 0;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            res += abs(a[i + y1][j + x1] - b[i + y2][j + x2]);

    return res;
}
