#include "CNetworkForClients.h"
#include "clog.h"

CNetworkForClients::CNetworkForClients(bool bIsWinNetwork, QObject *parent) : QObject(parent)
{
    m_bIsWinNetwork = bIsWinNetwork;
}

CNetworkForClients::~CNetworkForClients()
{
    foreach (CConnectionForClient *pConn, m_mapConnections.values()) {
        pConn->unInit();
        pConn = nullptr;
    }
    m_mapConnections.clear();
}

void CNetworkForClients::createConnection(QString strIp, int nPort, INetworkInterface *pNotifier)//@TODO 无限重连
{
    QString strIpPort = strIp+":"+QString::number(nPort);
    if(m_mapConnections.contains(strIpPort)){
        logWarnningWin()<<"CNetworkForClients::createConnection 重复Ip和端口的连接："<<strIpPort<<flushWin;
        return;
    }
    CConnectionForClient *pConnection = new CConnectionForClient(strIp,nPort);
    pConnection->init(m_bIsWinNetwork,pNotifier);
    connect(this,SIGNAL(sigSendMsg(QString,QString)),pConnection,SLOT(slotSend(QString,QString)));
    connect(this,SIGNAL(sigSendByQByteArray(QString,QByteArray)),pConnection,SLOT(slotSendByQByteArray(QString,QByteArray)));
    connect(this,SIGNAL(sigResetConnection(QString)),pConnection,SLOT(slotResetConnection(QString)));
    m_mapConnections.insert(pConnection->getIpPort(),pConnection);
}

void CNetworkForClients::send(QString strIp, int nPort, QString strMsg)
{
    emit sigSendMsg(genIpPort(strIp,nPort),strMsg);
}

void CNetworkForClients::sendAll(QString strMsg)
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigSendMsg(strIpPort,strMsg);
    }
}

void CNetworkForClients::sendByQByteArray(QString strIp, int nPort, QByteArray arrMsg)
{
    emit sigSendByQByteArray(genIpPort(strIp,nPort),arrMsg);
}

void CNetworkForClients::sendAllByQByteArray(QByteArray arrMsg)
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigSendByQByteArray(strIpPort,arrMsg);
    }
}

void CNetworkForClients::resetConnection(QString strIp, int nPort)
{
    emit sigResetConnection(this->genIpPort(strIp,nPort));
}

void CNetworkForClients::resetAll()
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigResetConnection(strIpPort);
    }
}

QString CNetworkForClients::genIpPort(QString strIp, int nPort)
{
    return strIp + ":" + QString::number(nPort);
}
