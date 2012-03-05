#ifndef HARMANKARDONAVR645RECEIVER_H
#define HARMANKARDONAVR645RECEIVER_H

#include "receiver.h"

#include <qextserialport.h>

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

};

#endif // HARMANKARDONAVR645RECEIVER_H
