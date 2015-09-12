#include "displayer.h"
#include "ui_displayer.h"

#include <QPainter>
#include <QRect>
#include <QMessageBox>
#include <QDebug>

#include <basicocclusiondetecter.h>
#include <opencvbasedocclusiondetecter.h>

const QString videoPath = "/home/vlad/work/sintel/training/";

Displayer::Displayer() :
    QMainWindow(0),
    ui(new Ui::Displayer)
{
    ui->setupUi(this);

    timer.setInterval(1000/24);
//    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer.start();

    QTimer *focus = new QTimer(this);
    focus->setInterval(0.1);
    QObject::connect(focus, SIGNAL(timeout()), this, SLOT(setFocus()));
    focus->start();

    status = new QLabel;
    ui->statusbar->addWidget(status);

    QObject::connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered(bool)), this, SLOT(showAboutQt()));


    detecter = new OpenCVBasedOcclusionDetecter();


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

void Displayer::nativePaint() {
    delete face;
    int w = width();
    int h = height() - 30;
    face = new QImage(w, h, QImage::Format_ARGB32);

    QPainter p(face);
    p.drawImage(QRect(0, 0, w / 2, h / 2), QImage(pathl));
    p.drawImage(QRect(0, h / 2, w / 2, h / 2), QImage(patht1));
    p.drawImage(QRect(w / 2, 0, w / 2, h / 2), QImage(patht2));
    p.drawImage(QRect(w / 2, h / 2, w / 2, h / 2), image);


    p.setBrush(QBrush(QColor("white")));
    p.drawRect(1, 0, 145, 40);
    p.drawRect(w / 2, 0, 145, 40);
    p.drawRect(1, h / 2, 145, 40);
    p.drawRect(w / 2, h / 2, 145, 40);

    p.setPen(QColor("black"));
    p.drawText(5, 30, "Left channel");
    p.drawText(w / 2 + 5, 30, "Ground Truth: depth");
    p.drawText(5, h / 2 + 30, "Ground Truth: occlusions");
    p.drawText(w / 2 + 5, h / 2 + 30, "My occlusions on depth");

    p.end();
}

void Displayer::paintEvent(QPaintEvent *) {
    QPainter p1(this);
    p1.drawImage(QRect(0, 30, width(), height() - 30), *face);
    p1.end();
}

void Displayer::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        exit(0);
    else if (event->key() == Qt::Key_Space) {
        if (timer.isActive()) {
            timer.stop();
            status->setText("paused");
            qApp->processEvents();
        } else {
            timer.start();
            nextFrame();
        }
    } else if (event->key() == Qt::Key_Right)
        nextFrame();
    else if (event->key() == Qt::Key_Left)
        prevFrame();
}

void Displayer::prevFrame() {
    currentFrame -= 2;
    nextFrame();
}

void Displayer::nextFrame() {
    status->setText("generating next frame...");
    qApp->processEvents();
    currentFrame++;

    QImage i1;
    QImage i2;

    pathl = videoPath + "final_left/alley_2/frame_00" + QString::number(currentFrame / 10) + QString::number(currentFrame % 10) + ".png";
    pathr = videoPath + "final_right/alley_2/frame_00" + QString::number(currentFrame / 10) + QString::number(currentFrame % 10) + ".png";
    patht1 = videoPath + "occlusions/alley_2/frame_00" + QString::number(currentFrame / 10) + QString::number(currentFrame % 10) + ".png";
    patht2 = videoPath + "disparities_viz/alley_2/frame_00" + QString::number(currentFrame / 10) + QString::number(currentFrame % 10) + ".png";


    if (!i1.load(pathl) || !i2.load(pathr)) {
        qDebug() << "--------------again--------------";
        currentFrame = 0;
        nextFrame();
        return;
    }

    i1.setText("path", pathl);
    i2.setText("path", pathr);

    setImage(detecter->getOcclusions(i1, i2).getRes());
    nativePaint();
    repaint();
    dump();

    status->setText("waiting for event...");

    if (timer.isActive())
        QTimer::singleShot(17, this, SLOT(nextFrame()));
}

void Displayer::showAboutQt() {
    QMessageBox::aboutQt(this, "About Qt");
}

void Displayer::showAbout() {
    QMessageBox::about(this, "About", "VirtualDub 2.0 - unusefull non-working clone of virtualdub.\nWritten by Vladislav Tyulbashev <vtyulb@vtyulb.ru>");
}

void Displayer::dump() {
    static int number = 1;
    face->save("output" + QString::number(number / 100) + QString::number(number % 100 / 10) + QString::number(number % 10) + ".jpg");
    number++;
}
