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

public slots:
    void onBoardChanged(const Piece color, const int y, const int x);

signals:
    void postGameStart(const Piece myColor, const QString& othername);
    void setPieceNet(const int y, const int x);

private slots:
    void onRecv();

private:
    void gameStart(const struct Connect6ProtocolHdr& hdr);
    void turn(const struct Connect6ProtocolHdr& hdr);
    void sendPut(int y1, int x1, int y2, int x2);

    QTcpSocket* socket;

    constexpr static int BUFFSIZE = 256;
    char recvBuff[BUFFSIZE];
    char sendBuff[BUFFSIZE];

    uint8_t mynumber;
    QString othername;

    Piece myColor;
};

#endif // NET_H
