#ifndef OCCLUSIONS_H
#define OCCLUSIONS_H

#include <QImage>

class Occlusions
{
    public:
        Occlusions();

        void display();
        void setRes(const QImage&);

    private:
        QImage res;
};

#endif // OCCLUSIONS_H
