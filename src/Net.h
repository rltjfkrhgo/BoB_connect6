#ifndef NET_H
#define NET_H

#include <QObject>
#include <QTcpSocket>

#include "Connect6Type.h"

class Net : public QObject
{
    Q_OBJECT

public:
    explicit Net(const QString& myname, const QString& ip, const QString& port, QObject* parent = nullptr);

private slots:
    void recv();
    void send();

private:
    QTcpSocket* socket;
};

#endif // NET_H
