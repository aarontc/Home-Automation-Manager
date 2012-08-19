#include <QtCore/QCoreApplication>

#include <iostream>

#include <QTime>
#include "TCPServer.h"

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);

	// Seed random number generator
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	TCPServer server;


	if (server.listen(QHostAddress::Any, 42424)) {
		std::cout << "Home Automation Manager Backend Server - Listening...\n\n";
	} else {
		std::cerr << QString("Unable to start server: %1").arg(server.errorString()).data();
		return(-1);
	}

	return a.exec();
}
