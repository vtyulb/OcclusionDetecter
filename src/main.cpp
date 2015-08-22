#include <iostream>

#include <QFile>
#include <QImage>
#include <QApplication>
#include <QTimer>
#include <QEventLoop>

#include <basicocclusiondetecter.h>
#include <displayer.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Displayer d;

    return a.exec();
}
