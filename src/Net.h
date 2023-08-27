#ifndef NET_H
#define NET_H

#include <QObject>
#include <QTcpSocket>

#include "Connect6Type.h"

class Net : public QObject
{
    Q_OBJECT

public:
    explicit Net(QObject* parent = nullptr);
    ~Net();

    void sendGameStart(const QString& myname, const QString& ip, const QString& port);

private slots:
    void recv();
    void send();

private:
    void recvGameStart(const struct Connect6ProtocolHdr& hdr);

    QTcpSocket* socket;

    constexpr static int BUFFSIZE = 256;
    char recvBuff[BUFFSIZE];
    char sendBuff[BUFFSIZE];

    uint8_t mynumber;
    QString othername;
};

#endif // NET_H
