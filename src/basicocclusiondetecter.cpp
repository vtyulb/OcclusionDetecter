#include <QColor>
#include <QPainter>
#include <QDebug>

#include <basicocclusiondetecter.h>
#include <opticalflow.h>
#include <opticalflowdetecter.h>
#include <bilinearfilter.h>
#include <superfilter.h>
#include <lrcfinder.h>
#include <occfinder.h>
#include <ordfinder.h>

const bool drawOpticalFlow = false;

using std::swap;
using std::min;

BasicOcclusionDetecter::BasicOcclusionDetecter():
    previousOcclusion(MyImage(5, 5))
{

}


Occlusions BasicOcclusionDetecter::getOcclusions(QImage i1, QImage i2) {
//    OpticalFlow flow = OpticalFlowDetecter::detect(MyImage(i1), MyImage(i2));
//    OpticalFlow backFlow = OpticalFlowDetecter::detect(MyImage(i2), MyImage(i1));
    OpticalFlow flow1 = OpticalFlowDetecter::useMediaLabAlgo(i1.text("path") + ".motion");
    OpticalFlow flow2 = OpticalFlowDetecter::useMediaLabAlgo(i2.text("path") + ".motion");

    Occlusions res;
    res.i1 = BilinearFilter::apply(MyImage(flow1), MyImage(i1)).toImage();

    MyImage lrc = LRCfinder::find(flow1, flow2);
    MyImage ord = ORDfinder::find(flow1, flow2);
    MyImage occ = OCCfinder::find(flow1, flow2);

    QImage occl(lrc.width, lrc.height, QImage::Format_ARGB32);
    for (int i = 0; i < lrc.height; i++)
        for (int j = 0; j < lrc.width; j++) {
            occl.setPixel(j, i, QColor(lrc[i][j], ord[i][j], occ[i][j]).rgb());
        }

    res.i2 = occl;
    res.i3 = getMEFaith(i1).toImage();

    return res;
}

MyImage BasicOcclusionDetecter::getMEFaith(QImage a) {
    MyImage res(a.width(), a.height());
    for (int i = 5; i < a.height() - 5; i++)
        for (int j = 5; j < a.width() - 5; j++) {
            QRgb v = a.pixel(j, i);
            int rd = 0;
            for (int k = -3; k < 3; k++)
                for (int l = -3; l < 3; l++) {
                    QRgb b = a.pixel(j + k, i + l);
                    rd += (abs(qRed(v) - qRed(b)) + abs(qBlue(v) - qBlue(b)) + abs(qGreen(v) - qGreen(b)));
                }

            res[i][j] = min(rd / 20, 255);
        }

    return res;
}
