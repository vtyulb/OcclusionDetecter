#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include <math.h>

#include <QVector>

struct Point {
    int dx;
    int dy;

    Point(int x = 0, int y = 0) { dx = x; dy = y; }
    int dist() const { return sqrt(dx * dx + dy * dy) * 30 + 50; }
};

class OpticalFlow
{
    public:
        OpticalFlow() {};

        QVector<QVector<Point> > flow;

        QVector<Point>& operator[](int i) { return flow[i]; }
        const QVector<Point> operator[](int i) const { return flow[i]; }
};

#endif // OPTICALFLOW_H
