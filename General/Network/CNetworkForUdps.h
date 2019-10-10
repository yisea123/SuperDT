#ifndef CNetworkForUdps_H
#define CNetworkForUdps_H

#include <QMap>
#include "INetworkInterface.h"
#include "CConnectionForUdp.h"


class CNetworkForUdps : public QObject
{
    Q_OBJECT
public:
    explicit CNetworkForUdps(QObject *parent = 0);
    ~CNetworkForUdps();
    void createConnection(QString strIp, int nPort, int nNotifyPort, INetworkInterface* pNotifier);
    void send(QString strIp,int nPort,QString strMsg);
    void sendAll(QString strMsg);
    void sendByQByteArray(QString strIp,int nPort,QByteArray arrMsg);
    void sendAllByQByteArray(QByteArray arrMsg);

signals:
    void sigSendMsg(QString strIpPort,QString strMsg);
    void sigSendByQByteArray(QString strIpPort,QByteArray arrMsg);
    void sigResetConnection(QString strIpPort);
private:
    bool m_bIsWinNetwork;
    QString genIpPort(QString strIp,int nPort);
    QMap<QString,CConnectionForUdp*> m_mapConnections;//保存资源以便最终释放
};

#endif // CNetworkForUdps_H
