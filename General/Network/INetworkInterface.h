#ifndef INETWORKINTERFACE_H
#define INETWORKINTERFACE_H

#include <QString>
#include <QObject>

class CSignalLaucher : public QObject{
    Q_OBJECT
public:
    void dataArrived(QByteArray arrMessage,QString strIp, int nPort){
        emit sigDataArrived(arrMessage,strIp,nPort);
    }
    void connectStateChanged(bool bState,QString strIp,int nPort){
        emit sigConnectStateChanged(bState,strIp,nPort);
    }
signals:
    void sigDataArrived(QByteArray arrMessage,QString strIp, int nPort);
    void sigConnectStateChanged(bool bState,QString strIp,int nPort);
};

class INetworkInterface
{
protected:
    INetworkInterface(){
        m_pLaucher = new CSignalLaucher();
    }
    virtual ~INetworkInterface(){
        m_pLaucher->deleteLater();
        m_pLaucher = nullptr;
    }
    CSignalLaucher *m_pLaucher = nullptr;
public:
    void dataArrivedForInterface(QByteArray arrMessage,QString strIp, int nPort){
        m_pLaucher->dataArrived(arrMessage,strIp,nPort);
        dataArrived(arrMessage,strIp,nPort);
    }
    void connectStateChangedForInterface(bool bState,QString strIp,int nPort){
        m_pLaucher->connectStateChanged(bState,strIp,nPort);
        connectStateChanged(bState,strIp,nPort);
    }
protected:
    virtual void dataArrived(QByteArray arrMessage,QString strIp, int nPort){
        Q_UNUSED(arrMessage);
        Q_UNUSED(strIp);
        Q_UNUSED(nPort);
    }
    virtual void connectStateChanged(bool bState,QString strIp,int nPort){
        Q_UNUSED(bState);
        Q_UNUSED(strIp);
        Q_UNUSED(nPort);
    }
};

#endif // INETWORKINTERFACE_H
