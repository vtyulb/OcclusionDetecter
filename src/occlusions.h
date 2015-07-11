#ifndef OCCLUSIONS_H
#define OCCLUSIONS_H

#include <QImage>

class Occlusions
{
    public:
        Occlusions();

        void display();
        void setRes(const QImage&);
        QImage getRes();

    private:
        QImage res;
};

#endif // OCCLUSIONS_H
