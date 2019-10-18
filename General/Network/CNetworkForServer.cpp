#include "CNetworkForServer.h"
#include "CLogWin.h"


CNetworkForServer::CNetworkForServer(int nPort, INetworkInterface *pNotifier, QObject *parent) : QObject(parent)
{
    m_nPort = nPort;
    m_pNotifier = pNotifier;
}

void CNetworkForServer::init()
{
    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->listen(QHostAddress::Any,m_nPort);
    logImpInfoWin()<<"CNetworkForServer::init 监听端口"<<m_nPort<<flushWin;
    connect(m_pTcpServer,SIGNAL(newConnection()),this,SLOT(slotConnected()));
}

void CNetworkForServer::send(QString strIp, int nPort, QString strMsg)
{
    emit sigSend(genIpPort(strIp,nPort),strMsg);
}

void CNetworkForServer::sendByQByteArray(QString strIp, int nPort, QByteArray arrMsg)
{
    emit sigSendByQByteArray(genIpPort(strIp,nPort),arrMsg);
}

void CNetworkForServer::sendAll(QString strMsg)
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigSend(strIpPort,strMsg);
    }
}

void CNetworkForServer::sendAllByQByteArray(QByteArray arrMsg)
{
    foreach(QString strIpPort,m_mapConnections.keys()){
        emit sigSendByQByteArray(strIpPort,arrMsg);
    }
}

void CNetworkForServer::sendExcept(QByteArray arrMsg, QString strIp, int nPort)
{
    const QString strIpPortExcept = this->genIpPort(strIp,nPort);
    foreach(QString strIpPort,m_mapConnections.keys()){
        if(strIpPortExcept != strIpPort){
            emit sigSendByQByteArray(strIpPort,arrMsg);
        }
    }
}

bool CNetworkForServer::hasConnection(QString strIp, int nPort)
{
    QString strIpPort = this->genIpPort(strIp,nPort);
    return m_mapConnections.contains(strIpPort);
}

QString CNetworkForServer::genIpPort(QString strIp, int nPort)
{
    return strIp + ":" + QString::number(nPort);
}

void CNetworkForServer::slotConnected()
{
    QTcpSocket *pTcpSocket = m_pTcpServer->nextPendingConnection();
    CConnectionForServer *pConn = new CConnectionForServer(pTcpSocket);
    pConn->init(m_pNotifier);
    connect(pConn,SIGNAL(sigDisConnected(QString)),this,SLOT(slotDisConnected(QString)));
    connect(this,SIGNAL(sigSend(QString,QString)),pConn,SLOT(slotSend(QString,QString)));
    connect(this,SIGNAL(sigSendByQByteArray(QString,QByteArray)),pConn,SLOT(slotSendByQByteArray(QString,QByteArray)));
    m_mapConnections.insert(pConn->getIpPort(),pConn);
}

void CNetworkForServer::slotDisConnected(QString strIpPort)
{
    if(!m_mapConnections.contains(strIpPort)){
        logWarnningWin()<<"CNetworkForServer::slotDisConnected 查询不到IpPort"<<flushWin;
    }else{
        CConnectionForServer *pConn = m_mapConnections.value(strIpPort);
        pConn->deleteLater();
        pConn = nullptr;
        m_mapConnections.remove(strIpPort);
    }
}
