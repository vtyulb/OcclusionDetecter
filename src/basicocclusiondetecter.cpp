#include <QColor>
#include <QPainter>

#include <basicocclusiondetecter.h>
#include <opticalflow.h>
#include <opticalflowdetecter.h>
#include <bilinearfilter.h>

BasicOcclusionDetecter::BasicOcclusionDetecter()
{

}


Occlusions BasicOcclusionDetecter::getOcclusions(QImage i1, QImage i2) {
    Occlusions res;

    OpticalFlow flow = OpticalFlowDetecter::detect(MyImage(i1), MyImage(i2));

    QImage a = BilinearFilter::apply(flow, i1).toImage();


    /*QPainter p(&a);
    p.setPen(QColor("red"));
    for (int i = 0; i < a.height(); i += step)
        for (int j = 0; j < a.width(); j += step)
            p.drawLine(j, i, j + flow[i][j].dx, i + flow[i][j].dy);

    p.end();*/

    res.setRes(a);
    return res;
}
