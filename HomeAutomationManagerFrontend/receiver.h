#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = 0);

signals:

public slots:

};

#endif // RECEIVER_H
