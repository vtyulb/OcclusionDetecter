#include <QColor>
#include <QPainter>

#include <basicocclusiondetecter.h>
#include <opticalflow.h>
#include <opticalflowdetecter.h>
#include <imageconverter.h>

BasicOcclusionDetecter::BasicOcclusionDetecter()
{

}


Occlusions BasicOcclusionDetecter::getOcclusions(QImage i1, QImage i2) {
    Occlusions res;

    OpticalFlow flow = OpticalFlowDetecter::detect(ImageConverter::convert(i1), ImageConverter::convert(i2));

    MyImage im = ImageConverter::convert(i1);
    QImage a = i1;
    for (int i = 0; i < a.height(); i++)
        for (int j = 0; j < a.width(); j++) {
            int base = flow[i][j].dist() * 10;
            if (base > 255)
                base = 255;
//            a.setPixel(j, i, QColor(base, base, base).rgb());
        }

    /*QPainter p(&a);
    p.setPen(QColor("red"));
    for (int i = 0; i < a.height(); i += step)
        for (int j = 0; j < a.width(); j += step)
            p.drawLine(j, i, j + flow[i][j].dx, i + flow[i][j].dy);

    p.end();*/

    res.setRes(a);
    return res;
}
