#include "displayer.h"
#include "ui_displayer.h"

#include <QPainter>
#include <QRect>

Displayer::Displayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Displayer)
{
    ui->setupUi(this);
}

Displayer::~Displayer()
{
    delete ui;
}

void Displayer::setImage(const QImage &im) {
    image = im;
}

void Displayer::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(QRect(0, 0, width(), height()), image);
    p.end();
}
