#ifndef CTABLE_H
#define CTABLE_H

#include <QObject>
#include <QString>
#include <QVector>
#include "clog.h"
#include "cdatabaseconnectionmanager.h"
#include "csqltool.h"
#include "IExcelLoader.h"
#include "CEnmTool.h"

#include <QSqlQuery>
#include "qsqlerror.h"

struct StData
{
    virtual QString getId() = 0;
    virtual void loadData(QVector<QString> vec) = 0;
    virtual QString getValue(int nIndex) = 0;
    virtual QVector<QString> toQVector() = 0;
};

class CTable : public QObject,public IExcelLoader
{
    Q_OBJECT
protected:
    CTable(QString strTableName,QVector<QString> vecColumnNames);
public:
    virtual void loadExcel(QVector<QVector<QString>> vecData){
        Q_UNUSED(vecData);
    }
public:
    QString m_strTableName;
    QString getTableName(){return m_strTableName;}
    QString getSqlSynTable();
    void init();//普通初始化，多用于从服务器接受并同步数据
    void initByLoadData();//从Excel加载数据并初始化
    void deleteRow(QString strId);
    void updateColumn(int nColumn,QString strColumnVal,QString strId);
signals:
    void sigUpdate(QString strId);
private slots:
    void slotRecreateTable(QString strTableName);
    void slotSynData(QString strSql, QString strTableName, QString strId);
protected:
    QStringList getLabels(QString strLabels);// 分割标签组的文字，得到各个标签，带#号
    void sendInfoDatabaseChange(QString strTableName, QString strSql = "", QString strId = "");
    QVector<QString> m_vecColumnNames;
    QString SQL_CREATE_TABLE;
    QString m_strExcelName;//该表默认的Excel文件名，默认从该文件读取数据

public://以下为模板方法，声明和定义不可分开。
    template<class TemplateForStruct>
    void addRow(TemplateForStruct st)
    {
        CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
        pDatabase->openConnection();
        QString strSql = CSqlTool::getSqlBindedValue(CSqlTool::getSqlInsert(m_strTableName,m_vecColumnNames.size()),st.toQVector());
        QSqlQuery cSqlQuery;
        cSqlQuery.prepare(strSql);
        if(!cSqlQuery.exec()){
            logWin()<<"CTable::addRow 表："<<m_strTableName<<" Sql错误:"<<cSqlQuery.lastError().text()<<flushWin;
            pDatabase->closeConnection();
        }else{
            pDatabase->closeConnection();
            sendInfoDatabaseChange(m_strTableName,strSql,st.getId());
        }
    }

    template<class TemplateForStruct>
    void updateRow(TemplateForStruct st)
    {
        CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
        pDatabase->openConnection();
        QVector<QString> vec = st.toQVector();
        vec.pop_front();
        vec.append(st.getId());
        QString strSql =CSqlTool::getSqlBindedValue(CSqlTool::getSqlUpdateRow(m_strTableName, m_vecColumnNames),vec);
        QSqlQuery cSqlQuery;cSqlQuery.prepare(strSql);
        if(!cSqlQuery.exec()){
            logWin()<<"CTable::updateRow  表："<<m_strTableName<<" Sql错误:"<<cSqlQuery.lastError().text()<<flushWin;
            pDatabase->closeConnection();
        }else{
            pDatabase->closeConnection();
            emit sigUpdate(st.getId());
            sendInfoDatabaseChange(m_strTableName,strSql,st.getId());
        }
    }

    template<class TemplateForStruct>
    TemplateForStruct queryRow(QString strId)
    {
        CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
        pDatabase->openConnection();
        QString strSql = CSqlTool::getSqlQuery(m_strTableName, m_vecColumnNames[0]);
        QSqlQuery cSqlQuery;
        cSqlQuery.prepare(strSql);
        cSqlQuery.addBindValue(strId);
        cSqlQuery.exec();
        if (cSqlQuery.next())
        {
            QVector<QString> vec;
            for(int i=0;i<m_vecColumnNames.size();i++){
                vec.append(cSqlQuery.value(i).toString());
            }
            TemplateForStruct stResult;
            stResult.loadData(vec);
            pDatabase->closeConnection();
            return stResult;
        }else{
            TemplateForStruct stResult;
            //logWarnningWin()<<"CTable::queryRow 查询不到信息,表为"<<m_strTableName<<"要查主键为"<<strId<<flushWin;
            pDatabase->closeConnection();
            return stResult;
        }
    }

    template<class TemplateForStruct>
    QVector<TemplateForStruct> queryAll()
    {
        CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
        pDatabase->openConnection();
        QString strSql = CSqlTool::getSqlQueryAll(m_strTableName);
        QSqlQuery cSqlQuery;
        cSqlQuery.exec(strSql);
        QVector<TemplateForStruct> vecStructs;
        while (cSqlQuery.next())
        {
            QVector<QString> vec;
            for(int i=0;i<m_vecColumnNames.size();i++){
                vec.append(cSqlQuery.value(i).toString());
            }
            TemplateForStruct stResult;
            stResult.loadData(vec);
            vecStructs.push_back(stResult);
        }
        pDatabase->closeConnection();
        return vecStructs;
    }
};

#endif // CTABLE_H
