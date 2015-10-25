#include <opticalflow.h>
#include <myimage.h>

#include <QDebug>

namespace {
    double cmp_det(const byte *r, double x) {
        int floor = x;
        double a = x - floor;
        return r[floor] * (1 - a) + r[floor + 1] * a;
    }
}

void OpticalFlow::convertFromME(QImage i1, QImage i2, MyImage *faith) {
    MyImage a1(i1);
    MyImage a2(i2);

    const int W = 30;

    for (int i = 0; i < a1.height; i++)
        for (int j = 1; j < a1.width - 1; j++)
            if ((*faith)[i][j] > 50)
        {
            double dx = flow[i][j].dx - 2;
            double resDX = dx;
            double res = 1000;
//            double proposed = (flow[i][j - 1].dx + flow[i][j + 1].dx) / 2;
            double proposed = flow[i][j].dx;
            for (int k = 0; k < 16; k++, dx += 0.25) {
                double cur = fabs(cmp_det(a1[i], j) - cmp_det(a2[i], j + dx));
                if (cur + fabs(proposed - dx) * W < res + fabs(resDX - proposed) * W) {
                    res = cur;
                    resDX = dx;
//                    static int corr = 0;
//                    qDebug() << corr++;
                }
            }

            flow[i][j].dx = resDX;
            flow[i][j].dy = 0;
        }
}

OpticalFlow::OpticalFlow(int width, int height) {
    flow.resize(height);
    for (int i = 0; i < height; i++)
        flow[i].resize(width);
}
