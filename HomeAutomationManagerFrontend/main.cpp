#include <QtGui/QApplication>
#include "mainwindow.h"

#include "HarmanKardonAVR645Receiver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	HarmanKardonAVR645Receiver r(&w);

    return a.exec();
}
