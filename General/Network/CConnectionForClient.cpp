#include "CConnectionForClient.h"
#include "clog.h"
CConnectionForClient::CConnectionForClient(QString strIp, int nPort)
{
    m_strIp = strIp;
    m_nPort = nPort;
}

void CConnectionForClient::init(bool bIsWinProtocal, INetworkInterface *pNotifier)
{
    m_bIsWinProtocal = bIsWinProtocal;
    if(nullptr == pNotifier){
        m_pNotifier = new CDefaultNotifier();
    }else{
        m_pNotifier = pNotifier;
    }

    m_pThread = new QThread();
    connect(m_pThread,SIGNAL(finished()),this,SLOT(slotThreadFinished()));
    this->moveToThread(m_pThread);
    m_pThread->start();

    //之后的逻辑都得通过信号和槽接通
    connect(this,SIGNAL(sigInitForClild()),this,SLOT(slotInitForClild()));
    emit sigInitForClild();
}

void CConnectionForClient::unInit()
{
    m_pThread->quit();
}

CConnectionForClient::~CConnectionForClient()
{
    if(nullptr != m_pRemoteIP){
        delete m_pRemoteIP;
        m_pRemoteIP = nullptr;
    }
}

void CConnectionForClient::slotResetConnection(QString strIpPort)
{
    if(this->getIpPort() == strIpPort){
        this->slotDisconnected();
    }
}

void CConnectionForClient::slotInitForClild()
{
    m_pTcpSocket = new QTcpSocket(this);
    //connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
    connect(m_pTcpSocket, SIGNAL(connected()), this, SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(slotDataReceived()));
    m_pTcpSocket->abort();
    m_pRemoteIP = new QHostAddress();
    m_pRemoteIP->setAddress(m_strIp);

    slotCreateConnection();//立刻进入一次slotCreateConnection
    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(RECONNET_SPAN_TIME);
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(slotCreateConnection()));
    m_pTimer->start();//启动定时器，每隔一段时间进入slotCreateConnection判断是否需要重连
}

void CConnectionForClient::slotCreateConnection()
{
    if(m_bConnected == true){
        return;
    }
    m_pTcpSocket->abort();
    m_pTcpSocket->connectToHost(*m_pRemoteIP, m_nPort);
    if(!m_pTcpSocket->waitForConnected(1500))//等待连接结果再返回，以免刚连接时发送消息，消息发送会失败
    {
        if(m_bIsFirstConnect){
            logWin()<<"CConnectionForClient::slotCreateConnection 首次连接不上:"<<getIpPort()<<flushWin;
            m_pNotifier->connectStateChangedForInterface(false,m_strIp,m_nPort);
        }else{
            //logWin()<<"CConnectionForClient::slotCreateConnection 尝试重连:"<<getIpPort()<<flushWin;
        }
    }
    m_bIsFirstConnect = false;
}

void CConnectionForClient::slotConnected()
{
    logWin()<<"CConnectionForClient::slotConnected 已连接到:"<<getIpPort()<<flushWin;
    m_bConnected = true;
    m_pNotifier->connectStateChangedForInterface(true,m_strIp,m_nPort);
}

void CConnectionForClient::slotDisconnected()
{
    if(m_bConnected == false){
        return;
    }
    m_bConnected = false;
    m_pNotifier->connectStateChangedForInterface(false,m_strIp,m_nPort);
    logWin()<<"CConnectionForClient::slotDisconnected 连接已断开:"<<getIpPort()<<flushWin;
}

void CConnectionForClient::slotThreadFinished()
{
    m_pThread->deleteLater();
    this->deleteLater();
}
