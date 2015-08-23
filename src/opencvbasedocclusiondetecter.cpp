#include "opencvbasedocclusiondetecter.h"

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QDebug>
#include <QColor>

OpenCVBasedOcclusionDetecter::OpenCVBasedOcclusionDetecter()
{

}

Occlusions OpenCVBasedOcclusionDetecter::getOcclusions(QImage left, QImage right) {

    qDebug() << "passing file" << left.text("path") << "to opencv";
    qDebug() << "passing file" << right.text("path") << "to opencv";
    qDebug() << "---";
    cv::Mat matLeft = cv::imread(cv::String(left.text("path").toStdString().data()), cv::IMREAD_GRAYSCALE);
    cv::Mat matRight = cv::imread(cv::String(right.text("path").toStdString().data()), cv::IMREAD_GRAYSCALE);
    cv::Mat disparity(matLeft.rows, matLeft.cols, CV_16S);
    cv::Mat disparity_8bit(matLeft.rows, matLeft.cols, CV_8UC1);

    cv::Ptr<cv::StereoBM> sbm = cv::StereoBM::create(16 * 5, 21);
    sbm->compute(matLeft, matRight, disparity);

    /*double min, max;
    cv::minMaxLoc(disparity, &min, &max);
    disparity.convertTo(disparity_8bit, CV_8UC1, 255/(max - min));


    QImage result(left.width(), left.height(), QImage::Format_RGB32);
    for (int i = 0; i < result.width(); i++)
        for (int j = 0; j < result.height(); j++) {
            int color = disparity.at<uchar>(i, j);
            result.setPixel(i, j, QColor(color, color, color).rgb());
        }*/

    cv::imwrite("SBM_sample.png", disparity);
    QImage result("SBM_sample.png");

    Occlusions occ;
    occ.setRes(result);
    return occ;
}

