#ifndef HARMANKARDONAVR645RECEIVER_H
#define HARMANKARDONAVR645RECEIVER_H

#include "receiver.h"

#include <qextserialport.h>
#include <QQueue>

class HarmanKardonAVR645Receiver : public Receiver {
	Q_OBJECT
	public:
		explicit HarmanKardonAVR645Receiver(QObject* parent = 0);

	signals:

	public slots:

	private slots:
		void serialRead();

	private:
		QextSerialPort* port;
        QQueue<quint8> inputQueue;

};

#endif // HARMANKARDONAVR645RECEIVER_H
