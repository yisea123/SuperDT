#ifndef ABSCONNECTION_H
#define ABSCONNECTION_H

#include <QTcpSocket>
#include "INetworkInterface.h"

#define BUFFER_SIZE_CLIENTS 1024*1024

class CDefaultNotifier : public INetworkInterface{
    void slotDataArrived(QByteArray arrMessage,QString strIp, int nPort){
        Q_UNUSED(arrMessage);
        Q_UNUSED(strIp);
        Q_UNUSED(nPort);
    }
    void slotConnectStateChanged(bool bState,QString strIp,int nPort){
        Q_UNUSED(bState);
        Q_UNUSED(strIp);
        Q_UNUSED(nPort);
    }
};

class AbsConnection : public QObject
{
    Q_OBJECT
public:
    QString getIpPort();
    virtual ~AbsConnection();
protected:
    QTcpSocket *m_pTcpSocket = nullptr;
    QString m_strIp = "";
    int m_nPort = -1;
    INetworkInterface *m_pNotifier = nullptr;

    bool m_bConnected = false;
    char m_szBuffer[BUFFER_SIZE_CLIENTS];
    QByteArray m_totalByteArr;

    bool m_bIsWinProtocal = false;//标识是否是Win协议
public slots:
    void slotSend(QString strIpPort,QString strMessage);
    void slotSendByQByteArray(QString strIpPort,QByteArray arrMsg);
    void slotDataReceived();
private:
    int send(QString strMessage);
    int sendByWin(QString strMessage);
    void dataRecevied();
    void dataReceviedByWin();
private:
    QByteArray splitPacket(QByteArray &oldPacket, char* newPacket, int nLength);
    int calculateLen( char* dataBuf );
};

#endif // ABSCONNECTION_H
