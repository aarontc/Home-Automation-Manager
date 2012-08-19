#include "TCPServer.h"
#include "TCPServerThread.h"

TCPServer::TCPServer(QObject *parent)
	: QTcpServer(parent)
{ }


void TCPServer::incomingConnection(int socketDescriptor) {
	TCPServerThread* thread = new TCPServerThread(socketDescriptor, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}
