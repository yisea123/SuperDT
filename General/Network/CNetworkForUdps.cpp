#include "CNetworkForUdps.h"
#include "CLogWin.h"

CNetworkForUdps::CNetworkForUdps(QObject *parent) : QObject(parent)
{

}

CNetworkForUdps::~CNetworkForUdps()
{
    foreach (CConnectionForUdp *pConn, m_mapConnections.values()) {
        pConn->unInit();
        pConn = nullptr;
    }
    m_mapConnections.clear();
}

void CNetworkForUdps::createConnection(QString strIp, int nPort, int nNotifyPort, INetworkInterface *pNotifier)
{
    QString strIpPort = strIp+":"+QString::number(nPort);
    if(m_mapConnections.contains(strIpPort)){
        logWarnningWin()<<"CNetworkForUdps::createConnection 重复Ip和端口的连接："<<strIpPort<<flushWin;
        return;
    }
    CConnectionForUdp *pConnection = new CConnectionForUdp(strIp,nPort);
    pConnection->init(nNotifyPort,pNotifier);
    connect(this,SIGNAL(sigSendMsg(QString,QString)),pConnection,SLOT(slotSend(QString,QString)));
    connect(this,SIGNAL(sigSendByQByteArray(QString,QByteArray)),pConnection,SLOT(slotSendByQByteArray(QString,QByteArray)));
//    connect(this,SIGNAL(sigResetConnection(QString)),pConnection,SLOT(slotResetConnection(QString)));
    m_mapConnections.insert(strIpPort,pConnection);
}

void CNetworkForUdps::send(QString strIp, int nPort, QString strMsg)
{
    emit sigSendMsg(genIpPort(strIp,nPort),strMsg);
}

void CNetworkForUdps::sendAll(QString strMsg)
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigSendMsg(strIpPort,strMsg);
    }
}

void CNetworkForUdps::sendByQByteArray(QString strIp, int nPort, QByteArray arrMsg)
{
    emit sigSendByQByteArray(genIpPort(strIp,nPort),arrMsg);
}

void CNetworkForUdps::sendAllByQByteArray(QByteArray arrMsg)
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigSendByQByteArray(strIpPort,arrMsg);
    }
}

QString CNetworkForUdps::genIpPort(QString strIp, int nPort)
{
    return strIp + ":" + QString::number(nPort);
}
