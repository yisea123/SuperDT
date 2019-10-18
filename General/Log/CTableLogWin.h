#ifndef CTABLELOGWIN_H
#define CTABLELOGWIN_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QDomElement>
#include <QVector>


class CTableLogWin:public QObject
{
    Q_OBJECT
public:
    explicit CTableLogWin();

    static CTableLogWin *getInstance();
    void init();
public:
    void loadConfig(QDomElement root);
    /*数据库连接*/
    bool initDB();
    bool openConnection();
    void closeConnection();
    void creatTable(QString strTableName,QVector<QString> vecColumnNames);
    bool isHasTable(QString strTableName);
    /*数据库操作*/
    void insertRow(QString strTableName,QVector<QString> vecRowValue);
    void queryRow();
    void queryTable();
private:
    QVector<QString> m_vecColumnName = {"Level","Date","File","Func","Line","Msg"};
    QSqlDatabase m_dbDatabase;
    QSqlQuery m_dbQuery;
    QMutex m_qMutex;
    QString m_strDBPath;
    QString m_strDBUserName;
    QString m_strDBPwd;

    QString SQL_CREATE_TABLE;
    QString m_strTableName;
};

#endif // CTABLELOGWIN_H
