#include "displayer.h"
#include "ui_displayer.h"

#include <QPainter>
#include <QRect>

#include <basicocclusiondetecter.h>

Displayer::Displayer() :
    QWidget(0),
    ui(new Ui::Displayer)
{
    ui->setupUi(this);

    timer.setInterval(1000/24);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer.start();
    nextFrame();
    show();
}

Displayer::~Displayer()
{
    delete ui;
}

void Displayer::setImage(const QImage &im) {
    image = im;
    repaint();
}

void Displayer::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(QRect(0, 0, width(), height()), image);
    p.end();
}

void Displayer::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        exit(0);
    else if (event->key() == Qt::Key_Space) {
        if (timer.isActive())
            timer.stop();
        else
            timer.start();
    } else if (event->key() == Qt::Key_Right)
        nextFrame();
    else
        prevFrame();
}

void Displayer::prevFrame() {
    currentFrame -= 2;
    nextFrame();
}

void Displayer::nextFrame() {
    currentFrame++;

    QImage i1;
    QImage i2;

    if (!i1.load(("image" + QString::number(currentFrame) + ".jpg")) || !i2.load(("image" + QString::number(currentFrame + 1) + ".jpg"))) {
        currentFrame = 0;
        nextFrame();
        return;
    }

    BasicOcclusionDetecter detecter;
    setImage(detecter.getOcclusions(i1, i2).getRes());
}
