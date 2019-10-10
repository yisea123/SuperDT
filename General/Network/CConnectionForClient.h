#ifndef CCONNECTIONFORCLIENT_H
#define CCONNECTIONFORCLIENT_H

/*
 * 客户端网络连接涉及到定时器、重连，需单独启用线程。服务器网络连接不需要。
*/

#include "AbsConnection.h"
#include <QTimer>
#include <QHostAddress>
#include <QThread>

#define RECONNECTTIMES -1//无限重连
#define RECONNET_SPAN_TIME 3000//重连间隔

class CConnectionForClient : public AbsConnection
{
    Q_OBJECT
public:
    explicit CConnectionForClient(QString strIp, int nPort);
    void init(bool bIsWinProtocal,INetworkInterface *pNotifier);
    void unInit();
    ~CConnectionForClient();
private:
    QThread *m_pThread = nullptr;
    bool m_bIsFirstConnect = true;
    QTimer *m_pTimer;
    QHostAddress *m_pRemoteIP;
signals:
    void sigInitForClild();
public slots:
    void slotResetConnection(QString strIpPort);
private slots:
    void slotInitForClild();
    void slotCreateConnection();
    void slotConnected();
    void slotDisconnected();
    void slotThreadFinished();
};

#endif // CCONNECTIONFORCLIENT_H
