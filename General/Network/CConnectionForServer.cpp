#include "CConnectionForServer.h"
#include <QHostAddress>
#include "clog.h"
CConnectionForServer::CConnectionForServer(QTcpSocket *pTcpSocket)
{
    m_pTcpSocket = pTcpSocket;
    QHostAddress addressIp = m_pTcpSocket->peerAddress();
    bool bOk = false;
    QHostAddress addressIpV4(addressIp.toIPv4Address(&bOk));
    if(bOk){
        m_strIp = addressIpV4.toString();
    }else{
        logErrorWin()<<"CConnectionForServer::CConnectionForServer 无法获取Ipv4地址，原始地址为"<<addressIp.toString()<<flushWin;
        m_strIp = "errorIp";
    }

    m_nPort = m_pTcpSocket->peerPort();
    logWin()<<"CConnectionForServer::CConnectionForServer 连接接入，Ip为"<<m_strIp<<"端口为"<<m_nPort<<flushWin;
    //connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(m_pTcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(slotDataReceived()));
}

void CConnectionForServer::init(INetworkInterface *pNotifier)
{
    m_bIsWinProtocal = true;//当前版本，所有服务器都是Win协议
    if(nullptr == pNotifier){
        m_pNotifier = new CDefaultNotifier();
    }else{
        m_pNotifier = pNotifier;
    }

    //对于服务端连接，初始化意味着已经连接成功
    m_bConnected = true;
    m_pNotifier->connectStateChangedForInterface(true,m_strIp,m_nPort);
}

void CConnectionForServer::slotDisconnected()
{
    logWin()<<"CConnectionForServer::CConnectionForServer 连接断开，Ip为"<<m_strIp<<"端口为"<<m_nPort<<flushWin;
    m_pNotifier->connectStateChangedForInterface(false,m_strIp,m_nPort);
    emit sigDisConnected(getIpPort());
}
