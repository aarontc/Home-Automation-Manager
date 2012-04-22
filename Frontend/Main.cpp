#include <QtGui/QApplication>
#include "MainWindow.h"

#include <HomeAutomation/HarmanKardonAVR645Receiver.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	HarmanKardonAVR645Receiver r(&w);
	QObject::connect(&r, SIGNAL(UpdateReceived(QByteArray,QByteArray,QByteArray)), &w, SLOT(ReceiverStatus(QByteArray,QByteArray,QByteArray)));
	QObject::connect(&w, SIGNAL(ReceiverCommand(QByteArray)), &r, SLOT(SendCommand(QByteArray)));

	return a.exec();
}
