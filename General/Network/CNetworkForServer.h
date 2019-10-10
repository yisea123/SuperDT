#ifndef CNETWORKFORSERVER_H
#define CNETWORKFORSERVER_H

#include <QObject>
#include "INetworkInterface.h"
#include <QTcpServer>
#include <QMap>
#include "CConnectionForServer.h"
#include <QThread>

class CNetworkForServer : public QObject
{
    Q_OBJECT
public:
    explicit CNetworkForServer(int nPort,INetworkInterface *pNotifier,QObject *parent = 0);
    void init();
    void send(QString strIp,int nPort,QString strMsg);
    void sendByQByteArray(QString strIp,int nPort,QByteArray arrMsg);
    void sendAll(QString strMsg);
    void sendAllByQByteArray(QByteArray arrMsg);
    void sendExcept(QByteArray arrMsg,QString strIp,int nPort);
    bool hasConnection(QString strIp,int nPort);
private:
    int m_nPort;
    INetworkInterface* m_pNotifier;
    QTcpServer *m_pTcpServer;
    QMap<QString,CConnectionForServer*> m_mapConnections;
    QString genIpPort(QString strIp,int nPort);
private slots:
    void slotConnected();
    void slotDisConnected(QString strIpPort);
signals:
    void sigSend(QString strIpPort,QString strMsg);
    void sigSendByQByteArray(QString strIpPort,QByteArray arrMsg);
};

#endif // CNETWORKFORSERVER_H
