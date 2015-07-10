#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class Displayer;
}

class Displayer : public QWidget
{
    Q_OBJECT

public:
    explicit Displayer(QWidget *parent = 0);
    ~Displayer();

    void setImage(const QImage &image);

private:
    Ui::Displayer *ui;
    QImage image;

    void paintEvent(QPaintEvent *);
};

#endif // DISPLAYER_H
