#include "opencvbasedocclusiondetecter.h"

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/core.hpp>

#include <QDebug>
#include <QColor>
#include <QPainter>
#include <QFile>

#include <string>

const double THRESHHOLD = 0.6;

#define min(a, b) (a < b ? a : b)

OpenCVBasedOcclusionDetecter::OpenCVBasedOcclusionDetecter()
{

}

Occlusions OpenCVBasedOcclusionDetecter::getOcclusions(QImage left, QImage right) {

    qDebug() << "passing file" << left.text("path") << "to opencv";
    qDebug() << "passing file" << right.text("path") << "to opencv";
    qDebug() << "---";
    cv::Mat matLeft = cv::imread(cv::String(left.text("path").toStdString().data()), cv::IMREAD_GRAYSCALE);
    cv::Mat matRight = cv::imread(cv::String(right.text("path").toStdString().data()), cv::IMREAD_GRAYSCALE);
    cv::Mat flow(matLeft.rows, matLeft.cols, CV_32FC2);

    cv::Ptr<cv::DenseOpticalFlow> flowCalc = cv::createOptFlow_DualTVL1();

    QString cache = left.text("path") + "_cached.yml";
    qDebug() << "cache at " << cache;
    if (!QFile(cache).exists()) {
        qDebug() << " ... not found";
        flowCalc->calc(matLeft, matRight, flow);

        cv::FileStorage file(cache.toStdString(), cv::FileStorage::WRITE);
        file << "flow" << flow;
        file.release();

        qDebug() << "...dumped";
    } else {
        qDebug() << " ... found";

        cv::FileStorage file(cache.toStdString(), cv::FileStorage::READ);
        file["flow"] >> flow;
        file.release();
    }


    QImage result(left.width(), left.height(), QImage::Format_RGB32);
    QImage verticalFaith(left.width(), left.height(), QImage::Format_RGB32);

    for (int i = 0; i < left.width(); i++)
        for (int j = 0; j < left.height(); j++) {
            double dx = flow.ptr<float>(j)[2 * i];
            double dy = flow.ptr<float>(j)[2 * i + 1];

            int color = sqrt(dx * dx + dy * dy) * 10;
            if (color > 255)
                color = 255;

            result.setPixel(i, j, QColor(color, color, color).rgb());
            int c2 = min(fabs(dy), 6.0) * 40;
            verticalFaith.setPixel(i, j, QColor(c2, c2, c2).rgb());
        }

    QPainter p(&result);
    p.setBrush(QBrush(QColor("red")));
    p.setPen(QColor("red"));

    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, -1, 1};
    for (int i = 1; i < left.width() - 1; i++)
        for (int j = 1; j < left.height() - 1; j++) {
            double x = flow.ptr<float>(j)[2 * i];
            double y = flow.ptr<float>(j)[2 * i + 1];

            for (int k = 0; k < 4; k++) {
                double x1 = flow.ptr<float>(j + dy[k])[2 * (i + dx[k])];
                double y1 = flow.ptr<float>(j + dy[k])[2 * (i + dx[k]) + 1];

                double diff = fabs(x1 - x) + fabs(y1 - y);
                if (diff >= THRESHHOLD)
                    p.drawEllipse(i, j, diff * 2, diff * 2);
            }


        }

    p.end();

    Occlusions occ;
    occ.i1 = result;
    occ.i2 = verticalFaith;
    return occ;
}

