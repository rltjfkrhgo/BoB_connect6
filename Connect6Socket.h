#ifndef CONNECT6SOCKET_H
#define CONNECT6SOCKET_H

#include <QTcpSocket>

#include "connect6_protocol.h"
#include "Connect6.h"
#include "Connect6AI.h"

class Connect6Socket : public QObject
{
    Q_OBJECT

public:
    const static int BUFFSIZE = 256;
    Connect6Socket(QString myname, QString ip, QString port, Connect6* connect6);
    ~Connect6Socket();

private:
    QTcpSocket*  socket;
    uchar  recvBuff[BUFFSIZE];
    uchar  sendBuff[BUFFSIZE];
    size_t  recvLen;
    size_t  sendLen;

    QString  myname;
    QString  ip;
    QString  port;
    QString  othername;  // 상대방 이름

    uint8_t  mynumber;

    Connect6*   connect6;
    Connect6AI* ai;

    bool isRunning;


signals:
    void sendMsg(QString msg);

private slots:
    void recv();
};

#endif // CONNECT6SOCKET_H
