#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include <math.h>

#include <QVector>

struct Point {
    double dx;
    double dy;

    Point(double x = 0, double y = 0) { dx = x; dy = y; }
    int dist() const { return std::min(sqrt((dx * dx + dy * dy) * 100.0), 255.0); }
};

class OpticalFlow
{
    public:
        OpticalFlow() {};

        QVector<QVector<Point> > flow;

        QVector<Point>& operator[](int i) { return flow[i]; }
        const QVector<Point> operator[](int i) const { return flow[i]; }

        inline int width() const { return flow[0].size(); }
        inline int height() const { return flow.size(); }
};

#endif // OPTICALFLOW_H
