#include "displayer.h"
#include "ui_displayer.h"

#include <QPainter>
#include <QRect>
#include <QMessageBox>

#include <basicocclusiondetecter.h>

const QString videoPath = "susi/image";

Displayer::Displayer() :
    QMainWindow(0),
    ui(new Ui::Displayer)
{
    ui->setupUi(this);

    timer.setInterval(1000/24);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
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
    p.drawImage(QRect(0, 30, width(), height() - 55), image);
    p.end();
}

void Displayer::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        exit(0);
    else if (event->key() == Qt::Key_Space) {
        if (timer.isActive()) {
            timer.stop();
            status->setText("paused");
            qApp->processEvents();
        } else
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
    status->setText("generating next frame...");
    currentFrame++;

    QImage i1;
    QImage i2;

    if (!i1.load((videoPath + QString::number(currentFrame) + ".jpg")) || !i2.load((videoPath + QString::number(currentFrame + 1) + ".jpg"))) {
        currentFrame = 0;
        nextFrame();
        return;
    }

    setImage(detecter.getOcclusions(i1, i2).getRes());

    status->setText("waiting for event...");
}

void Displayer::showAboutQt() {
    QMessageBox::aboutQt(this, "About Qt");
}

void Displayer::showAbout() {
    QMessageBox::about(this, "About", "VirtualDub 2.0 - unusefull non-working clone of virtualdub.\nWritten by Vladislav Tyulbashev <vtyulb@vtyulb.ru>");
}
