#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimer>

namespace Ui {
    class Displayer;
}

class Displayer : public QWidget
{
    Q_OBJECT

public:
    Displayer();
    ~Displayer();

    void setImage(const QImage &image);

private:
    Ui::Displayer *ui;
    QImage image;
    QTimer timer;

    int currentFrame = 1;

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent*);

private slots:
    void nextFrame();
    void prevFrame();
};

#endif // DISPLAYER_H
