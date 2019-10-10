#include "CConnectionForUdp.h"
#include "clog.h"
CConnectionForUdp::CConnectionForUdp(QString strIp, int nPort)
{
    m_strIp = strIp;
    m_nPort = nPort;
    m_strIpPort = m_strIp + ":" + QString::number(nPort);
}

void CConnectionForUdp::init(int nNotifyPort, INetworkInterface *pNotifier)
{
    m_nNotifyPort = nNotifyPort;
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

void CConnectionForUdp::unInit()
{
    m_pThread->quit();
}

CConnectionForUdp::~CConnectionForUdp()
{
}

void CConnectionForUdp::slotSend(QString strIpPort, QString strMessage)
{
    if(m_strIpPort.compare(strIpPort) != 0){
        return;
    }

    m_pSendSocket->writeDatagram(strMessage.toUtf8(), QHostAddress(m_strIp), m_nPort);
}

void CConnectionForUdp::slotSendByQByteArray(QString strIpPort, QByteArray arrMsg)
{
    if(m_strIpPort.compare(strIpPort) != 0){
        return;
    }

    m_pSendSocket->writeDatagram(arrMsg, QHostAddress(m_strIp), m_nPort);
}

void CConnectionForUdp::slotDataReceived()
{
    if(nullptr == m_pReceSocket){
        logErrorWin()<<"CConnectionForUdp::slotDataReceived 逻辑错误，m_pReceSocket为空"<<flushWin;
        return;
    }
    while (1)//将数据读入缓存
    {
        int readCount = m_pReceSocket->readLine(m_szBuffer,BUFFER_SIZE_CLIENTS);
        if (readCount <= 0){
            break;
        }
        QByteArray arrByte;
        arrByte.append(m_szBuffer,readCount);
        m_pNotifier->dataArrivedForInterface(arrByte,m_strIp, m_nPort);
        memset( m_szBuffer, 0, BUFFER_SIZE_CLIENTS );
    }
}

int CConnectionForUdp::send(QString strMessage)
{
    if(nullptr == m_pSendSocket){
        logErrorWin()<<"AbsConnection::send 逻辑错误，m_pTcpSocket为空"<<flushWin;
        return -1;
    }
    return m_pSendSocket->writeDatagram(strMessage.toUtf8(), QHostAddress(m_strIp), m_nPort);
}


void CConnectionForUdp::slotInitForClild()
{
    m_pSendSocket = new QUdpSocket(this);       // 发送

    if(m_nNotifyPort >= 0){
        m_pReceSocket = new QUdpSocket(this);       // 接收
        bool bRes = m_pReceSocket->bind(QHostAddress::AnyIPv4,m_nNotifyPort,QAbstractSocket::ShareAddress);
        if(!bRes)
        {
             logErrorWin()<<"CConnectionForUdp::slotInitForClild bind failed"<<flushWin;
        }
        connect(m_pReceSocket, SIGNAL(readyRead()), this, SLOT(slotDataReceived()));
    }

    m_pNotifier->connectStateChangedForInterface(m_bConnected,m_strIp,m_nPort);
}


void CConnectionForUdp::slotThreadFinished()
{
    m_pThread->deleteLater();
    this->deleteLater();
}


