#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TCPServer : public QTcpServer
{
		Q_OBJECT
	public:
		explicit TCPServer(QObject *parent = 0);
		void incomingConnection(int socketDescriptor);

	signals:

	public slots:

};

#endif // TCPSERVER_H
