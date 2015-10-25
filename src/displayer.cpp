#include "displayer.h"

#include <QPainter>
#include <QRect>
#include <QMessageBox>
#include <QDebug>

#include <basicocclusiondetecter.h>
#include <opencvbasedocclusiondetecter.h>

//const QString SCENE = "alley_1/";
const QString SCENE = "";

//const QString videoPath = "/home/vlad/work/sintel/training/";
const QString videoPath = "/home/vlad/work/pirates/";

Displayer::Displayer()
{
    detecter = new BasicOcclusionDetecter;
    while (nextFrame());
}

Displayer::~Displayer()
{
}

void Displayer::nativePaint() {
    delete face;
//    int w = width();
//    int h = height() - 30;
    int w = 1920;
    int h = 1080;
    face = new QImage(w, h, QImage::Format_ARGB32);

    //pathl, patht1, patht2
    QPainter p(face);
    p.drawImage(QRect(0, 0, w / 2, h / 2), QImage(pathl));
    p.drawImage(QRect(0, h / 2, w / 2, h / 2), occlusions.i3);
    p.drawImage(QRect(w / 2, 0, w / 2, h / 2), occlusions.i2);
    p.drawImage(QRect(w / 2, h / 2, w / 2, h / 2), occlusions.i1);


    p.setBrush(QBrush(QColor("white")));
    p.drawRect(1, 0, 165, 40);
    p.drawRect(w / 2, 0, 165, 40);
    p.drawRect(1, h / 2, 165, 40);
    p.drawRect(w / 2, h / 2, 165, 40);

    p.setPen(QColor("black"));
    p.setFont(QFont("Times", 18, QFont::Bold));
    p.drawText(5, 30, "Trailer");
    p.drawText(w / 2 + 5, 30, "Depth map");
    p.drawText(5, h / 2 + 30, "Time faith");
    p.drawText(w / 2 + 5, h / 2 + 30, "Occlusions");

    p.end();

//    *face = occlusions.i1;
}

void Displayer::prevFrame() {
    currentFrame -= 2;
    nextFrame();
}

bool Displayer::nextFrame() {
    currentFrame++;

    qDebug() << "--------------- processing frame " << currentFrame << "-------------------";

    QImage i1;
    QImage i2;

    pathl = videoPath + "final_left/" + SCENE + "frame_0" + QString::number(currentFrame / 100) + QString::number(currentFrame % 100 / 10) + QString::number(currentFrame % 10) + ".png";
    pathr = videoPath + "final_right/" + SCENE +  "frame_0" + QString::number(currentFrame / 100) + QString::number(currentFrame % 100 / 10) + QString::number(currentFrame % 10) + ".png";
    patht1 = videoPath + "occlusions/" + SCENE + "frame_0" + QString::number(currentFrame / 100) + QString::number(currentFrame % 100 / 10) + QString::number(currentFrame % 10) + ".png";
    patht2 = videoPath + "disparities_viz/" + SCENE + "frame_0" + QString::number(currentFrame / 100) + QString::number(currentFrame % 100 / 10) + QString::number(currentFrame % 10) + ".png";


    if (!i1.load(pathl) || !i2.load(pathr)) {
        qDebug() << "--------------again--------------";
        currentFrame = 0;
        return false;
    }

    i1.setText("path", pathl);
    i2.setText("path", pathr);


    occlusions = detecter->getOcclusions(i1, i2);


    nativePaint();
    dump();

    return true;
}

void Displayer::dump() {
    static int number = 0;
    face->save("output" + QString::number(number / 100) + QString::number(number % 100 / 10) + QString::number(number % 10) + ".png");
    number++;
}
