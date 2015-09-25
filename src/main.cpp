#include <iostream>

#include <QFile>
#include <QImage>
#include <QCoreApplication>
#include <QTimer>
#include <QEventLoop>

#include <basicocclusiondetecter.h>
#include <displayer.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Displayer d;

    return a.exec();
}
