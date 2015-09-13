#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QLabel>
#include <QImage>

#include <ui_displayer.h>
#include <basicocclusiondetecter.h>
#include <occlusions.h>

class Displayer : public QMainWindow
{
    Q_OBJECT

public:
    Displayer();
    ~Displayer();

    void setImage(const QImage &image);

private:
    Ui::Displayer *ui;
    QLabel *status;
    QImage *face = NULL;
    QString pathl, pathr, patht1, patht2;
    QTimer timer;
    Occlusions occlusions;
    AbstractOcclusionDetecter *detecter;

    int currentFrame = 0;

    void nativePaint();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent*);

    void dump();

private slots:
    void nextFrame();
    void prevFrame();

    void showAbout();
    void showAboutQt();
};

#endif // DISPLAYER_H
