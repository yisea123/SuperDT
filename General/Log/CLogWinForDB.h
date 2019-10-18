#ifndef CLOGWINFORDB_H
#define CLOGWINFORDB_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QDomElement>
#include <QVector>
#include <QFileInfo>
#include <QStringList>

#include "CLogWin.h"

class CLogWinForDB:public QObject
{
    Q_OBJECT
public:
    explicit CLogWinForDB();
    static CLogWinForDB *getInstance();

public:
    void init();
    void insertRow(QString strTableName,QVector<QString> vecRowValue);
    void loadLogWinConfig(QDomElement root);
public slots:
    void slotRedirect(QString strDate);
    void slotCheckCache();
private:
    quint64 getFileSize(const QString strFileName);
    int getDBTableCount();
    int getDBArgForStragety();
    int byteToMB(quint64 byte){return (byte<(1024*1024)) ? 0 : byte >> 20;}
    void clearLogToSafe();
    /*数据库*/
    bool initDB();
    bool openConnection();
    void closeConnection();
    void creatTable(QString strTableName,QVector<QString> vecColumnNames);
    bool isHasTable(QString strTableName);
    void removeTable(QString strTableName);
private:
    QVector<QString> m_vecColumnName = {"Id","Level","Date","File","Func","Line","Msg"};
    QSqlDatabase m_dbDatabase;
    QSqlQuery m_dbQuery;
    QString m_strDBPath;
    QString m_strDBUserName;
    QString m_strDBPwd;

    QString SQL_CREATE_TABLE;
    QString m_strTableName;
    QStringList m_listTableName;

    EnmClearLogStragety m_enmClearLogStragety = ENM_COUNT;
    int m_nLogMaxSize =  10;
    int m_nLogSafetySize = 10;
};

#endif // CLOGWINFORDB_H
