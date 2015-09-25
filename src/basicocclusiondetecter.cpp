#include <QColor>
#include <QPainter>

#include <basicocclusiondetecter.h>
#include <opticalflow.h>
#include <opticalflowdetecter.h>
#include <bilinearfilter.h>
#include <superfilter.h>
#include <lrcfinder.h>
#include <occfinder.h>

const bool drawOpticalFlow = false;

using std::swap;

BasicOcclusionDetecter::BasicOcclusionDetecter():
    previousOcclusion(MyImage(5, 5))
{

}


Occlusions BasicOcclusionDetecter::getOcclusions(QImage i1, QImage i2) {
    OpticalFlow flow = OpticalFlowDetecter::detect(MyImage(i1), MyImage(i2));
    OpticalFlow backFlow = OpticalFlowDetecter::detect(MyImage(i2), MyImage(i1));
    OpticalFlow flow1 = OpticalFlowDetecter::useMediaLabAlgo(i1.text("path") + ".motion");

    MyImage a(flow);
    MyImage disparityMap = BilinearFilter::apply(a, MyImage(i1));

    Occlusions res;
    res.i1 = BilinearFilter::apply(MyImage(flow1), MyImage(i1)).toImage();
    res.i2 = LRCfinder::find(flow, backFlow).toImage();
//    res.i3 = OCCfinder::find(flow, backFlow).toImage();
    res.i3 = disparityMap.toImage();

//    res.i1 = MyImage(flow1).toImage();
    return res;
}
