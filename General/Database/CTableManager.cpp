#include "CTableManager.h"
#include "cdatabaseconnectionmanager.h"
#include "clog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>
CTableManager::CTableManager(QObject *parent) : QObject(parent)
{
}

CTableManager *CTableManager::getInstance()
{
    static CTableManager* pInstance = nullptr;
    static QMutex mutex;
    if(nullptr == pInstance){
        mutex.lock();
        if(nullptr == pInstance){
            CTableManager *pTemp = new CTableManager();//局部变量防止构造函数未完成时返回指针，另一线程引用产生问题
            pInstance = pTemp;
        }
        mutex.unlock();
    }
    return pInstance;
}

void CTableManager::execSqlForSynTable(QString strSql, QString strTableName)
{
    //都必须用信号槽机制，否则会因为多线程导致执行顺序错误
    emit sigRecreateTable(strTableName);//先重建空表
    emit sigSynData(strSql,strTableName,ID_ALL_FOR_TABLE);//接收整表信息。
}

void CTableManager::execSqlForSynRow(QString strSql, QString strTableName, QString strId)
{
    emit sigSynData(strSql,strTableName,strId);//接收信息。
}
