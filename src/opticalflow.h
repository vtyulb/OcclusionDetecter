#ifndef OPTICALFLOW_H
#define OPTICALFLOW_H

#include <QVector>

struct Point {
    int dx;
    int dy;

    Point(int x = 0, int y = 0) { dx = x; dy = y; }
    int dist() { return dx * dx + dy * dy; }
};

class OpticalFlow
{
    public:
        OpticalFlow() {};

        QVector<QVector<Point> > flow;

        QVector<Point>& operator[](int i) { return flow[i]; }
};

#endif // OPTICALFLOW_H
