#ifndef CNETWORKFORCLIENT_H
#define CNETWORKFORCLIENT_H

#include <QObject>
#include "CConnectionForClient.h"
#include <QThread>
#include <QMap>
class CNetworkForClients : public QObject
{
    Q_OBJECT
public:
    explicit CNetworkForClients(bool bIsWinNetwork = true,QObject *parent = 0);
    ~CNetworkForClients();
    void createConnection(QString strIp,int nPort,INetworkInterface* pNotifier);
    void send(QString strIp,int nPort,QString strMsg);
    void sendAll(QString strMsg);
    void sendByQByteArray(QString strIp,int nPort,QByteArray arrMsg);
    void sendAllByQByteArray(QByteArray arrMsg);
    void resetConnection(QString strIp,int nPort);
    void resetAll();
signals:
    void sigSendMsg(QString strIpPort,QString strMsg);
    void sigSendByQByteArray(QString strIpPort,QByteArray arrMsg);
    void sigResetConnection(QString strIpPort);
private:
    bool m_bIsWinNetwork;
    QString genIpPort(QString strIp,int nPort);
    QMap<QString,CConnectionForClient*> m_mapConnections;//保存资源以便最终释放
};

#endif // CNETWORKFORCLIENT_H
