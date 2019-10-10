#ifndef CConnectionForUdp_H
#define CConnectionForUdp_H

/*
 * 客户端网络连接涉及到定时器、重连，需单独启用线程。服务器网络连接不需要。
*/

#include "AbsConnection.h"
#include <QTimer>
#include <QUdpSocket>
#include <QHostAddress>
#include <QThread>

#define RECONNECTTIMES -1//无限重连
#define RECONNET_SPAN_TIME 3000//重连间隔

class CConnectionForUdp  : public QObject
{
    Q_OBJECT
public:
    explicit CConnectionForUdp(QString strIp, int nPort);
    void init(int nNotifyPort,INetworkInterface *pNotifier);
    void unInit();
    ~CConnectionForUdp();
private:
    QThread *m_pThread = nullptr;
    const bool m_bConnected = true;  // 事实上 UDP 是不存在是否连接上的概念的， 但是为了与 INetworkInterface 接口保持一致，这里认为连接状态总是 true

    QString m_strIp = "";
    int m_nPort = -1;
    int m_nNotifyPort = -1;
    QString m_strIpPort;

    INetworkInterface *m_pNotifier = nullptr;
    QUdpSocket* m_pSendSocket;
    QUdpSocket* m_pReceSocket;


    char m_szBuffer[BUFFER_SIZE_CLIENTS];

public slots:
    void slotSend(QString strIpPort,QString strMessage);
    void slotSendByQByteArray(QString strIpPort,QByteArray arrMsg);
    void slotDataReceived();

private:
    int send(QString strMessage);

signals:
    void sigInitForClild();

private slots:
    void slotInitForClild();
    void slotThreadFinished();
};

#endif // CConnectionForUdp_H
