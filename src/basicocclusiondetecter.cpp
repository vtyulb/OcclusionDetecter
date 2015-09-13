#include <QColor>
#include <QPainter>

#include <basicocclusiondetecter.h>
#include <opticalflow.h>
#include <opticalflowdetecter.h>
#include <bilinearfilter.h>
#include <superfilter.h>

const bool drawOpticalFlow = false;

using std::swap;

BasicOcclusionDetecter::BasicOcclusionDetecter():
    previousOcclusion(MyImage(5, 5))
{

}


Occlusions BasicOcclusionDetecter::getOcclusions(QImage i1, QImage i2) {
    OpticalFlow flow = OpticalFlowDetecter::detect(MyImage(i1), MyImage(i2));

    MyImage a(flow);

    if (hasPrevious) {
        for (int i = 0; i < a.height; i++)
            for (int j = 0; j < a.width; j++) {
                int x = previousFlow[i][j].dx + j;
                int y = previousFlow[i][j].dy + i;

                a[y][x] = a[y][x] * 0.65 + 0.35 * previousFlow[i][j].dist();
            }
    }

    SuperFilter filter(i1.width(), i1.height());
    MyImage result = filter.apply(a, i1);

    QImage imageRes = result.toImage();
    for (int i = 0; i < result.height; i++)
        for (int j = 0; j < result.width; j++)
            for (int k = 0; k < 4; k++)
                if (result[i + dy[k]][j + dx[k]] != result[i][j]) {
                    int vx = 0;
                    int vy = 0;
                    int total = 0;
                    for (int i1 = -2; i1 < 3; i1++)
                        for (int j1 = -2; j1 < 3; j1++)
                            if (i + i1 >= 0 && i + i1 < result.height && j + j1 >= 0 && j + j1 < result.width) {
                                total++;

                                if (result[i + i1][j + j1] != result[i][j]) {
                                    vx += flow[i + i1][j + j1].dx;
                                    vy += flow[i + i1][j + j1].dy;
                                } else {
                                    vx -= flow[i + i1][j + j1].dx;
                                    vy -= flow[i + i1][j + j1].dy;
                                }
                            }

                    vx /= total;
                    vy /= total;

                    int i1min = 0;
                    int j1min = 0;

                    if (vx < 0)
                        swap(vx, i1min);

                    if (vy < 0)
                        swap(vy, j1min);

                    for (int i1 = i1min; i1 <= vx; i1++)
                        for (int j1 = j1min; j1 <= vy; j1++)
                            if (i + i1 >= 0 && i + i1 < result.height && j + j1 >= 0 && j + j1 < result.width)
                                if (result[i + i1][j + j1] != result[i][j])
                                    imageRes.setPixel(j + j1, i + i1, QColor("red").rgb());
                }


    /*if (drawOpticalFlow) {
        QPainter p(&a);
        p.setPen(QColor("red"));
        for (int i = 0; i < a.height(); i += step)
            for (int j = 0; j < a.width(); j += step)
                p.drawLine(j, i, j + flow[i][j].dx, i + flow[i][j].dy);

        p.end();
    }*/

    previousFlow = flow;
    previousOcclusion = result;
    hasPrevious = true;

    Occlusions res;
    res.i1 = imageRes;
    return res;
}
