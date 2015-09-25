#include <iostream>

#include <QFile>
#include <QImage>
#include <QApplication>
#include <QTimer>
#include <QEventLoop>

#include <basicocclusiondetecter.h>
#include <displayer.h>

// Start program with "-platform offscreen"
// if no X-Server available. No signatures
//                     would be available!

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Displayer d;

    return 0;
}
