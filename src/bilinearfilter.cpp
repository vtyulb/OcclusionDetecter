#include "bilinearfilter.h"

namespace {
    inline int sqr(int a) { return a * a; }
    inline double gauss(int dist, double sigma) {
        return 1 / sqrt(3.141592 * sigma * sigma) * exp(-dist / sigma / sigma);
    }

    const int window = 8;
    const int sigma_spatial = 10;
    const int sigma_color = 3;
    const int mxn = 256*256;
}

MyImage BilinearFilter::apply(const MyImage &target, const MyImage &colors) {
    QVector<double> gauss_spatial;
    QVector<double> gauss_color;

    for (int i = 0; i < mxn; i++) {
        gauss_color.push_back(gauss(i, sigma_color));
        gauss_spatial.push_back(gauss(i, sigma_spatial));
    }


    MyImage res(target.width, target.height);
    for (int i = 0; i < target.height; i++)
        for (int j = 0; j < target.width; j++) {
            double sum = 0;
            double k = 0;
            for (int dx = -window + 1; dx < window; dx++)
                for (int dy = -window + 1; dy < window; dy++)
                    if (i + dy >= target.height || i + dy < 0 || j + dx >= target.width || j + dx < 0)
                        continue;
                    else {
                        double cur_k = gauss_spatial[sqr(dx) + sqr(dy)] *
                            gauss_color[sqr(colors[i][j] - colors[i + dy][j + dx])];

                        sum += target[i + dy][j + dx] * cur_k;
                        k += cur_k;
                    }

            res[i][j] = sum / k;
        }

    return res;
}
