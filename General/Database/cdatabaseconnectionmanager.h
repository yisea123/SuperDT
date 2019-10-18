#ifndef CDATABASECONNECTIONMANAGER_H
#define CDATABASECONNECTIONMANAGER_H

#include <QSqlDatabase>
#include <QMutex>
#include "IConfigLoader.h"

class CDatabaseConnectionManager : public IConfigLoader
{
private:
    explicit CDatabaseConnectionManager();
    void loadConfig(QDomElement root);
private:
    QString m_strDBType = "";
    QString m_strDBPath = "";
    QString m_strDBUser = "";
    QString m_strDBPwd = "";

public:
    static CDatabaseConnectionManager* getInstance();
    bool init();

    bool openConnection();
    void closeConnection();
private:
    void setDataBaseName( QString strDatabaseName );
    QSqlDatabase m_cDatabase;
    QMutex m_qMutex;
};

#endif // CDATABASECONNECTIONMANAGER_H
