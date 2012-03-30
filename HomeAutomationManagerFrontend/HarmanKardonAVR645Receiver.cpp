#include "HarmanKardonAVR645Receiver.h"

#include <QDebug>

const char HarmanKardonAVR645Receiver::COMMAND_POWER_ON[] = { 0x80, 0x70, 0xC0, 0x3F };
const char HarmanKardonAVR645Receiver::COMMAND_POWER_OFF[] = { 0x80, 0x70, 0x9F, 0x60 };
const char HarmanKardonAVR645Receiver::COMMAND_VOLUME_UP[] = { 0x80, 0x70, 0xC7, 0x38 };
const char HarmanKardonAVR645Receiver::COMMAND_VOLUME_DOWN[] = { 0x80, 0x70, 0xC8, 0x37 };

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
	static QByteArray data;

	QByteArray bytes;
	int a = port->bytesAvailable();
	bytes.resize(a);
	port->read(bytes.data(), bytes.size());

	data.append(bytes);

	while(data.length() >= 60) {
		if(data[0] == 'M' &&
		   data[1] == 'P' &&
		   data[2] == 'S' &&
		   data[3] == 'E' &&
		   data[4] == 'N' &&
		   data[5] == 'D' &&
		   data[8] == static_cast<char>(0xf0) &&
		   data[23] == static_cast<char>(0x00) &&
		   data[24] == static_cast<char>(0xf1) &&
		   data[39] == static_cast<char>(0x00) &&
		   data[40] == static_cast<char>(0xf2) &&
		   data[55] == static_cast<char>(0x00)) {

			quint8 checkOdd(0), checkEven(0);
			for(int i(8); i<58; i+=2) {
				checkEven ^= data[i];
				checkOdd ^= data[i+1];
			}

			if(checkEven == static_cast<quint8>(data[58])) {
				if(checkOdd == static_cast<quint8>(data[59])) {
					QByteArray line1 = data.mid(9, 14);
					QByteArray line2 = data.mid(25, 14);
					QByteArray icons = data.mid(41, 14);
					emit UpdateReceived(line1, line2, icons);
				} else {
					qDebug() << "odd checksum failed";
				}
			} else {
				qDebug() << "even checksum failed";
			}
			data.remove(0, 60);
		} else {
			data.remove(0, 1);
		}
	}
}

void HarmanKardonAVR645Receiver::SendCommand(QByteArray command) {
	QByteArray data;
	data.append("PCSEND");
	data.append(2);
	data.append(4);
	data.append(command.data(), 4);
	data.append(command[0]^command[2]);
	data.append(command[1]^command[3]);
	port->write(data);
}
