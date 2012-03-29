#include "HarmanKardonAVR645Receiver.h"

#include <QDebug>

HarmanKardonAVR645Receiver::HarmanKardonAVR645Receiver(QObject* parent)
    : Receiver(parent)
{

	this->port = new QextSerialPort("/dev/ttyUSB0", QextSerialPort::EventDriven);
	port->setBaudRate(BAUD38400);
	port->setFlowControl(FLOW_OFF);
	port->setParity(PAR_NONE);
	port->setDataBits(DATA_8);
	port->setStopBits(STOP_1);

	if(port->open(QIODevice::ReadWrite) == true) {
		connect(port, SIGNAL(readyRead()), this, SLOT(serialRead()));
	} else {
		throw 42;
	}
}

void HarmanKardonAVR645Receiver::serialRead() {
	QByteArray bytes;
	int a = port->bytesAvailable();
	bytes.resize(a);
    d(bytes.data(), bytes.size());

	qDebug() << "Got" << bytes;
}
