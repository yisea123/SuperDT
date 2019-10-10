#ifndef CConnectionForServer_H
#define CConnectionForServer_H

#include "AbsConnection.h"

class CConnectionForServer : public AbsConnection
{
    Q_OBJECT
public:
    explicit CConnectionForServer(QTcpSocket *pTcpSocket);
    void init(INetworkInterface *pNotifier);
private slots:
    void slotDisconnected();
signals:
    void sigDisConnected(QString strIpPort);
};

#endif // CConnectionForServer_H
