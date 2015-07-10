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
    QImage a(flow.flow[0].size(), flow.flow.size(), QImage::Format_RGB32);
    for (int i = 0; i < a.height(); i++)
        for (int j = 0; j < a.width(); j++)
            a.setPixel(j, i, QColor(flow[i][j].dist(), flow[i][j].dist(), flow[i][j].dist()).rgb());

    QPainter p(&a);
    p.setPen(QColor("red"));
    for (int i = 0; i < a.height(); i += 8)
        for (int j = 0; j < a.width(); j += 8)
            p.drawLine(j, i, j + flow[i][j].dx, i + flow[i][j].dy);

    p.end();

    res.setRes(a);
    return res;
}
