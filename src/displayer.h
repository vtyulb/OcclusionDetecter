#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QObject>
#include <QPaintEvent>
#include <QLabel>
#include <QImage>

#include <basicocclusiondetecter.h>
#include <occlusions.h>

class Displayer : public QObject
{
    Q_OBJECT

public:
    Displayer();
    ~Displayer();

    void setImage(const QImage &image);

private:
    QImage *face = NULL;
    QString pathl, pathr, patht1, patht2;
    Occlusions occlusions;
    AbstractOcclusionDetecter *detecter;

    int currentFrame = 0;

    void nativePaint();

    void dump();

private slots:
    bool nextFrame();
    void prevFrame();
};

#endif // DISPLAYER_H
