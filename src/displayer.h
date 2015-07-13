#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QWidget>
#include <QMainWindow>
#include <QPaintEvent>
#include <QTimer>
#include <QLabel>

#include <ui_displayer.h>
#include <basicocclusiondetecter.h>

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
    QImage image;
    QTimer timer;
    BasicOcclusionDetecter detecter;

    int currentFrame = 20;

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent*);

private slots:
    void nextFrame();
    void prevFrame();

    void showAbout();
    void showAboutQt();
};

#endif // DISPLAYER_H
