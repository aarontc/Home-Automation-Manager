#include "TCPServerThread.h"

#include <QDebug>
#include <QHostAddress>

TCPServerThread::TCPServerThread(int socketDescriptor, QObject* parent)
	: QThread(parent)
	, socketDescriptor(socketDescriptor)
{ }



void TCPServerThread::run() {
	QTcpSocket tcpSocket;
	//tcpSocket = new QTcpSocket();
	if (tcpSocket.setSocketDescriptor(socketDescriptor)) {
		qDebug() << "Connection accepted" << socketDescriptor << "from" << tcpSocket.peerName() << tcpSocket.peerAddress() << tcpSocket.peerPort();
	} else {
		emit error(tcpSocket.error());
		return;
	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	out << "Hello, world!";

	tcpSocket.write(block);
	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnected();
	qDebug() << "Connection lost" << socketDescriptor;
}

