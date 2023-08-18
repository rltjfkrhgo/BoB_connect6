#include "Net.h"

#include "Controller.h"

Net::Net(const QString& myname,
         const QString& ip,
         const QString& port,
         QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QIODevice::readyRead, this, &Net::recv);
    socket->connectToHost(ip, port.toInt());
}

void Net::recv()
{

}

void Net::send()
{

}
