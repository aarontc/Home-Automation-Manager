#ifndef HARMANKARDONAVR645RECEIVER_H
#define HARMANKARDONAVR645RECEIVER_H

#include "receiver.h"

#include <qextserialport.h>
#include <QQueue>

class HarmanKardonAVR645Receiver : public Receiver {
	Q_OBJECT
	public:
		static const char COMMAND_POWER_ON[];
		static const char COMMAND_POWER_OFF[];
		static const char COMMAND_VOLUME_UP[];
		static const char COMMAND_VOLUME_DOWN[];

		explicit HarmanKardonAVR645Receiver(QObject* parent = 0);

	signals:
		void UpdateReceived(QByteArray line1, QByteArray line2, QByteArray icons);

	public slots:
		void SendCommand(QByteArray command);

	private slots:
		void serialRead();

	private:
		QextSerialPort* port;
};

#endif // HARMANKARDONAVR645RECEIVER_H
