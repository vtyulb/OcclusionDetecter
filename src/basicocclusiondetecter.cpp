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
#include <dmcfinder.h>
#include <ordfinder.h>
#include <depthloader.h>

const bool drawOpticalFlow = false;

using std::swap;
using std::min;

namespace {
    QString hackName(QString name) {
        int a = name.indexOf('0');
        QString number;
        for (int i = 0; i < 4; i++)
            number += name[a + i];

        number = QString::number(number.toInt() - 1);
        while (number.size() != 4)
            number = '0' + number;

        for (int i = 0; i < 4; i++)
            name[a + i] = number[i];

        return name;
    }
}

BasicOcclusionDetecter::BasicOcclusionDetecter():
    previousDepth(MyImage(5, 5)),
    prediction(MyImage(5, 5))
{

}


Occlusions BasicOcclusionDetecter::getOcclusions(QImage i1, QImage i2) {
//    OpticalFlow flow = OpticalFlowDetecter::detect(MyImage(i1), MyImage(i2));
//    OpticalFlow backFlow = OpticalFlowDetecter::detect(MyImage(i2), MyImage(i1));
//    OpticalFlow flow1 = OpticalFlowDetecter::useMediaLabAlgo(i1.text("path") + ".motion");
//    OpticalFlow flow2 = OpticalFlowDetecter::useMediaLabAlgo(i2.text("path") + ".motion");


    Occlusions res;

//    MyImage ord = ORDfinder::find(flow1, flow2);
//    MyImage occ = OCCfinder::find(flow1, flow2);
    MyImage depth1 = DepthLoader::load(i1.text("path") + ".depth", i1.width(), i1.height());
    MyImage depth2 = DepthLoader::load(i2.text("path") + ".depth", i2.width(), i2.height());

    OpticalFlow leftTimeBackFlow = OpticalFlowDetecter::useMediaLabAlgo(hackName(i1.text("path")) + ".time.back.motion");
    OpticalFlow leftTimeFlow = OpticalFlowDetecter::useMediaLabAlgo(i1.text("path") + ".time.motion");

    OpticalFlow flow1 = depth1.toOF();
    OpticalFlow flow2 = depth2.toOF();
    MyImage lrc = LRCfinder::find(flow1, flow2);
    previousDepth = depth1;

    if (hasPrevious) {
        MyImage timeLRC = LRCfinder::find(leftTimeFlow, leftTimeBackFlow);
        MyImage stabilized = stabilize(hasPrevious ? previousDepth : depth1, depth1, leftTimeBackFlow, timeLRC);
        previousDepth = stabilized;

        res.i2 = stabilized.toImage();
        res.i3 = timeLRC.toImage();

        basicTimeFiltration(lrc);
    }

    prediction = lrc;

    res.i1 = lrc.toImage();

    hasPrevious = true;
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

MyImage BasicOcclusionDetecter::getMEtimeFaith(const OpticalFlow &flow) {

}

MyImage BasicOcclusionDetecter::stabilize(MyImage prev, MyImage cur, OpticalFlow flow, MyImage faithMap) {
    MyImage res(cur.width, cur.height);

    for (int i = 0; i < cur.height; i++)
        for (int j = 0; j < cur.width; j++) {
            const int dx = flow[i][j].dx;
            const int dy = flow[i][j].dy;

            const double prevCost = 0.4 + min(abs(prev[i + dy][j + dx] - cur[i][j]) / 255.0, 0.4);

            if (faithMap[i][j] < 200)
                res[i][j] = min(prev[i + dy][j + dx] * prevCost + cur[i][j] * (1 - prevCost), 255.0);
            else
                res[i][j] = cur[i][j];
        }

    return res;
}

void BasicOcclusionDetecter::basicTimeFiltration(MyImage &image) {
    for (int i = 5; i < image.height - 5; i++)
        for (int j = 5; j < image.width - 5; j++) {
            if (image[i][j] > 128) {
                int num = 0;
                int nn = 0;
                for (int k = -5; k < 5; k++)
                    for (int z = -5; z < 5; z++) {
                        num += prediction[i + k][j + z] > 128;
                        nn += image[i + k][j + z] > 128;
                    }

                if (num > 5 || nn > 23)
                    image[i][j] = 255;
                else
                    image[i][j] = 0;

            } else {
                image[i][j] = 0;
            }
        }
}
