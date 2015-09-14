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

    Occlusions res;
    res.i1 = BilinearFilter::apply(a, MyImage(i1)).toImage();
    return res;
}
