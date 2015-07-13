#include <QDebug>

#include "opticalflowdetecter.h"

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

const int mass = 64;

namespace {
    inline int sqr(int a) { return a * a; }
}

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

    long long totalError = 0, res = 100500;

    for (int i = 0; i < i1.height; i += step)
        for (int j = 0; j < i2.width; j += step) {

            res = cmp(i1, i2, j, i, j + flow[i][j].dx, i + flow[i][j].dy);
            if (i > 0) {
                int nres = cmp(i1, i2, j, i, flow[i - step][j].dx, flow[i - step][j].dy);
                if (nres < res - mass) {
                    flow[i][j] = flow[i - step][j];
                    res = nres;
                }
            }

            if  (j > 0) {
                int nres = cmp(i1, i2, j, i, flow[i][j - step].dx, flow[i][j - step].dy);
                if (nres < res - mass) {
                    flow[i][j] = flow[i][j - step];
                    res = nres;
                }
            }

            if (1) {
                int nres = cmp(i1, i2, j, i, j, i);
                if (nres < res + mass) {
                    flow[i][j] = Point(0, 0);
                    res = nres;
                }
            }

/*            if (res > 2500) {
                int sd = 16;
                while (sd > 1) {
                    int cx = flow[i][j].dx;
                    int cy = flow[i][j].dy;
                    int res = cmp(i1, i2, j, i, j + cx, i + cy);
                    for (int k = 0; k < 4; k++) {
                        int nx = cx + dx[k] * sd;
                        int ny = cy + dy[k] * sd;

                        int nres = cmp(i1, i2, j, i, j + nx, i + ny);
                        if (nres < res - mass) {
                            res = nres;
                            flow[i][j].dx = nx;
                            flow[i][j].dy = ny;
                        }
                    }

                    sd /= 2;
                }
            }*/

            bool cont = true;
            while (cont) {
                cont = false;
                int cx = flow[i][j].dx;
                int cy = flow[i][j].dy;
                res = cmp(i1, i2, j, i, j + cx, i + cy);
                for (int k = 0; k < 4; k++) {
                    int nx = cx + dx[k];
                    int ny = cy + dy[k];

                    int nres = cmp(i1, i2, j, i, j + nx, i + ny);
                    if (nres < res - mass) {
                        cont = true;
                        res = nres;
                        flow[i][j].dx = nx;
                        flow[i][j].dy = ny;
                    }
                }
            }

            totalError += res;
        }

    qDebug() << "average error" << totalError / i1.height / i1.width;

    //-----------------------------
    for (int i = 0; i < i1.height; i += step)
        for (int j = 0; j < i1.width; j += step)
            for (int k = 0; k < step; k++)
                for (int l = 0; l < step; l++)
                    flow[i + k][j + l] = flow[i][j];
    //-----------------------------

    return flow;
}

int OpticalFlowDetecter::cmp(const MyImage &a, const MyImage &b, int x1, int y1, int x2, int y2) {
//    if (x1 + step > a.width || y1 + step > a.height || x2 + step > b.width || y2 + step > b.height ||
//            x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
//        return 100500;

    int res = 0;

    for (int i = -step / 2; i < step + step / 2; i++)
        for (int j = -step / 2; j < step + step / 2; j++)
            res += abs(a[i + y1][j + x1] - b[i + y2][j + x2]);

    return res;
}
