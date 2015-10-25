#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include <math.h>

#include <QImage>
#include <QVector>

struct Point {
    double dx;
    double dy;

    Point(double x = 0, double y = 0) { dx = x; dy = y; }
    int dist() const { return std::min(-dx * 4 + 128, 255.0); }
};

struct MyImage;

class OpticalFlow
{
    public:
        OpticalFlow(int width = 0, int height = 0);

        QVector<QVector<Point> > flow;

        QVector<Point>& operator[](int i) { return flow[i]; }
        const QVector<Point> operator[](int i) const { return flow[i]; }

        inline int width() const { return flow[0].size(); }
        inline int height() const { return flow.size(); }

        void convertFromME(QImage i1, QImage i2, MyImage *regions);
};

#endif // OPTICALFLOW_H
