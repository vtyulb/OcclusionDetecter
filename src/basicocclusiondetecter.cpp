#include <QColor>
#include <QPainter>

#include <basicocclusiondetecter.h>
#include <opticalflow.h>
#include <opticalflowdetecter.h>
#include <bilinearfilter.h>
#include <superfilter.h>

const bool drawOpticalFlow = false;

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
    res.setRes(result.toImage());
    return res;
}
