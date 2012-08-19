#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>

class TCPServerThread : public QThread {
		Q_OBJECT
	public:
		explicit TCPServerThread(int socketDescriptor, QObject* parent = 0);
	void run();


	signals:
		void error(QTcpSocket::SocketError socketError);

	private:
		int socketDescriptor;
		QTcpSocket* tcpSocket;
};

#endif // TCPSERVERTHREAD_H
