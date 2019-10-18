#include "CTable.h"
#include <QJsonObject>
#include "CExcelTool.h"
#include "cjson.h"
#include "CTableManager.h"
#include "ProtocalCommon.h"
#include "CAccessProxy.h"

CTable::CTable(QString strTableName, QVector<QString> vecColumnNames)
{
    m_strTableName = strTableName;
    m_strExcelName = "";
    m_vecColumnNames = vecColumnNames;
    //获取SQL_CREATE_TABLE语句
    SQL_CREATE_TABLE = "";
    if(m_vecColumnNames.size()<=1){
        logErrorWin()<<"CTable::CTable 非法的参数,表为"<<m_strTableName<<"大小为"<<m_vecColumnNames.size()<<flushWin;
        return;
    }
    SQL_CREATE_TABLE = "CREATE TABLE " + m_strTableName +
            "("+m_vecColumnNames[0]+" varchar(50)    PRIMARY KEY    NOT NULL," ;
    for(int i=1;i<m_vecColumnNames.size()-1;i++){
        SQL_CREATE_TABLE += m_vecColumnNames[i]+" TEXT   NULL," ;
    }
    SQL_CREATE_TABLE += m_vecColumnNames[m_vecColumnNames.size()-1]+" TEXT   NULL)" ;

    connect(CTableManager::getInstance(),SIGNAL(sigSynData(QString,QString,QString)),this,SLOT(slotSynData(QString,QString,QString)),Qt::DirectConnection);
    connect(CTableManager::getInstance(),SIGNAL(sigRecreateTable(QString)),this,SLOT(slotRecreateTable(QString)),Qt::DirectConnection);
}

QString CTable::getSqlSynTable()
{
    /*所需字符串如下：
     * insert into "+strTableName+" values "
     * (value11,value12),(value21,value22)
     */
    //第一步：生成字符串头
    QString strSql =  "insert into "+m_strTableName+" values ";
    //第二步：获取表里所有行的结果集
    CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
    pDatabase->openConnection();
    QSqlQuery cSqlQuery;
    cSqlQuery.exec(CSqlTool::getSqlQueryAll(m_strTableName));
    bool bIsEmpty = true;//判断表里内容是否为空
    while (cSqlQuery.next())//第三步：对每一行添加“(value11,value12),”字符串
    {
        bIsEmpty = false;
        strSql += "(";
        for(int i=0;i<m_vecColumnNames.size();i++){
            strSql += "'";
            strSql += cSqlQuery.value(i).toString();
            strSql += "'";
            if(i != m_vecColumnNames.size()-1){
                strSql += ",";
            }
        }
        strSql += ")";
        strSql += ",";
    }
    pDatabase->closeConnection();
    if(bIsEmpty){//表里内容为空则返回空字符串
        logWarnningWin()<<"CTable::getSqlSynTable 内容为空："<<m_strTableName<<flushWin;
        return "";//返回语句必须在pDatabase->closeConnection()之后，不然会锁死
    }
    //第四步：去掉最后多余的一个“,”
    strSql = strSql.mid(0,strSql.length()-1);
    return strSql;
}

void CTable::init()
{
    slotRecreateTable(m_strTableName);
}

void CTable::initByLoadData()
{
    this->init();
    CExcelTool::loadExcel(m_strExcelName,this);
}

void CTable::deleteRow(QString strId)
{
    CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
    pDatabase->openConnection();
    QVector<QString> vecValues;
    vecValues.push_back(strId);
    QString strSql = CSqlTool::getSqlBindedValue(CSqlTool::getSqlDelete(m_strTableName, m_vecColumnNames[0]),vecValues);

    QSqlQuery cSqlQuery;
    cSqlQuery.prepare(strSql);
    if(!cSqlQuery.exec())
    {
        logWin()<<"CTable::deleteRow 表："<<m_strTableName<<" Sql错误:"<<cSqlQuery.lastError().text()<<flushWin;
        pDatabase->closeConnection();
    }else{
        pDatabase->closeConnection();
        sendInfoDatabaseChange(m_strTableName,strSql,strId);
    }
}

void CTable::updateColumn(int nColumn, QString strColumnVal, QString strId)
{
    CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
    pDatabase->openConnection();
    QString strSql = CSqlTool::getSqlUpdateOneColm(m_strTableName,m_vecColumnNames.at(nColumn),
                                                   strColumnVal,m_vecColumnNames.at(0),strId);
    QSqlQuery cSqlQuery;cSqlQuery.prepare(strSql);
    if(!cSqlQuery.exec()){
        logWin()<<"CTable::updateColumn  表："<<m_strTableName<<" Sql错误:"<<cSqlQuery.lastError().text()<<flushWin;
        pDatabase->closeConnection();
    }else{
        pDatabase->closeConnection();
        emit sigUpdate(strId);
        sendInfoDatabaseChange(m_strTableName,strSql,strId);
    }
}

void CTable::slotRecreateTable(QString strTableName)
{
    if(m_strTableName != strTableName){
        return;
    }
    //1、打开连接
    CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
    pDatabase->openConnection();
    //2、尝试删除表
    QSqlQuery cSqlQueryDelete;
    cSqlQueryDelete.prepare("DROP TABLE "+m_strTableName);
    if(! cSqlQueryDelete.exec()){
        logWin()<<"CTable::init 删除表时，表不存在"<<m_strTableName<<flushWin;
    }
    //3、尝试建立表
    QSqlQuery cSqlQueryCreateTable;
    cSqlQueryCreateTable.prepare(SQL_CREATE_TABLE);
    if(! cSqlQueryCreateTable.exec()){
        logErrorWin()<<"CTable::init 逻辑错误。表创建语句不生效，或创建表时表已存在，表为："<<m_strTableName<<flushWin;
        logImpInfoWin()<<SQL_CREATE_TABLE<<flushWin;
    }else{
        logWin()<<"CTable::init 创建表"<<m_strTableName<<flushWin;
    }
    pDatabase->closeConnection();
}

void CTable::slotSynData(QString strSql, QString strTableName, QString strId)
{
    if(m_strTableName != strTableName){
        return;
    }
    CDatabaseConnectionManager* pDatabase = CDatabaseConnectionManager::getInstance();
    pDatabase->openConnection();

    QSqlQuery cSqlQuery;cSqlQuery.prepare(strSql);
    if(!cSqlQuery.exec()){
        logErrorWin()<<"CTable::slotSynTable 表："<<strTableName<<" Sql:"<<strSql<<" 错误为:"<<cSqlQuery.lastError().text()<<flushWin;
        pDatabase->closeConnection();
        return;
    }
    pDatabase->closeConnection();
    emit sigUpdate(strId);
}

QStringList CTable::getLabels(QString strLabels)
{
    QStringList vec;
    if("" == strLabels){
        return vec;
    }
    if('#' != strLabels.at(0)){
        logErrorWin()<<"CTable::getLabels 错误的首字符："<<strLabels<<flushWin;
        return vec;
    }
    return strLabels.split('#',QString::SkipEmptyParts);//按规则第一个值为""，然后才是"#xx",需忽略空
}

void CTable::sendInfoDatabaseChange(QString strTableName, QString strSql, QString strId)
{
    QByteArray arrCore = ProtocalCommon::synDataForOneRow(strSql,strTableName,strId);
    QByteArray arrMsg = ProtocalCommon::synDataOneRowToAllClientsAndServer(arrCore);
    CAccessProxy::getInstance()->order(arrMsg);
}
