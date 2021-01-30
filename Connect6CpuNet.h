#ifndef CONNECT6CPUNET_H
#define CONNECT6CPUNET_H

#include <QTcpSocket>

#include "Connect6.h"
#include "connect6_protocol.h"

class Connect6CpuNet : public Connect6
{
public:
    Connect6CpuNet(QString name, QString ip, QString port);

    void putPiece(int x, int y) override;

private:
    QTcpSocket socket;
};

#endif // CONNECT6CPUNET_H