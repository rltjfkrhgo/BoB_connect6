#ifndef NETADAPTER_H
#define NETADAPTER_H

#include <QObject>
#include <QTcpSocket>

#include "Connect6Type.h"

class NetAdapter : public QObject
{
    Q_OBJECT

public:
    explicit NetAdapter(QObject* parent = nullptr);
    ~NetAdapter();

    void sendGameStart(const QString& myname, const QString& ip, const QString& port);

signals:
    void postGameStart(const Piece myColor, const QString& othername);

private slots:
    void onRecv();

private:
    void gameStart(const struct Connect6ProtocolHdr& hdr);
    void put(const struct Connect6ProtocolHdr& hdr);
    void turn(const struct Connect6ProtocolHdr& hdr);

    QTcpSocket* socket;

    constexpr static int BUFFSIZE = 256;
    char recvBuff[BUFFSIZE];
    char sendBuff[BUFFSIZE];

    uint8_t mynumber;
    QString othername;
};

#endif // NETADAPTER_H
