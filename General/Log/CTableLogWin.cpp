#include "CTableLogWin.h"
#include "clog.h"
CTableLogWin::CTableLogWin()
{

}

CTableLogWin *CTableLogWin::getInstance()
{
    static CTableLogWin* m_pInstance = nullptr;
    if(m_pInstance == nullptr){
        if(m_pInstance == nullptr){
            m_pInstance = new CTableLogWin();
        }
    }
    return m_pInstance;
}

void CTableLogWin::init()
{
    m_strDBPath = "C:/DB/LogWin.db";
    m_strTableName = "LOG_WIN_20191014";

    if(this->initDB()){
        qDebug()<<"日志专用数据库: "<<m_strDBPath<<" 已存在";
    }

    m_dbQuery = QSqlQuery(m_dbDatabase);

    this->creatTable(m_strTableName,m_vecColumnName);
}

void CTableLogWin::loadConfig(QDomElement root)
{

}

bool CTableLogWin::initDB()
{
    m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_dbDatabase.setDatabaseName(m_strDBPath);

    return this->openConnection();
}

bool CTableLogWin::openConnection()
{
    m_qMutex.lock();
    if(m_dbDatabase.open())
    {
        qDebug()<<"CDatabaseConnectionManager::init 本地数据库连接成功，地址为"<<m_strDBPath;
        return true;
    }
    else{
        qDebug()<<"CDatabaseConnectionManager::init 本地数据库初始连接失败，"
                       "试图打开的地址为"<<m_strDBPath;
        m_qMutex.unlock(); //@TODO 是否需要在此unLock
        return false;
    }
}

void CTableLogWin::closeConnection()
{
    m_dbDatabase.close();
    m_qMutex.unlock();
}


void CTableLogWin::creatTable(QString strTableName, QVector<QString> vecColumnNames)
{
     if(isHasTable(m_strTableName))
         return ; //表存在  直接返回

     qDebug()<<"创建表:"<<strTableName;

    m_strTableName = strTableName;

    QVector<QString> m_vecColumnNames;
    m_vecColumnNames = vecColumnNames;

    //获取SQL_CREATE_TABLE语句
    SQL_CREATE_TABLE = "";
    if(m_vecColumnNames.size()<=1){
        qDebug()<<"CTable::CTable 非法的参数,表为"<<m_strTableName<<"大小为"<<m_vecColumnNames.size()<<flushWin;
        return;
    }

    SQL_CREATE_TABLE = "CREATE TABLE " + m_strTableName +
            "("+m_vecColumnNames[0]+" TEXT  NULL," ;

    for(int i=1;i<m_vecColumnNames.size()-1;i++){
        SQL_CREATE_TABLE += m_vecColumnNames[i]+" TEXT   NULL," ;
    }
    SQL_CREATE_TABLE += m_vecColumnNames[m_vecColumnNames.size()-1]+" TEXT   NULL)" ;


    m_dbQuery.prepare(SQL_CREATE_TABLE);
    if(!m_dbQuery.exec())
        qDebug()<<"创建表:" <<m_strTableName <<"失败！"<<SQL_CREATE_TABLE;

}

bool CTableLogWin::isHasTable(QString strTableName)
{
    QString strSql = "select count(*)  from sqlite_master where type='table' and name='" + strTableName + "';";
    m_dbQuery.prepare(strSql);
    if(m_dbQuery.exec()){
        if(m_dbQuery.next()){
            if(m_dbQuery.value(0).toBool()){
                qDebug()<<"表:"<< strTableName << "已存在！";
                return true;
            }else{
                qDebug()<<"表:"<< strTableName << "不存在！";
                return false;
            }
        }
    }else{
        qDebug()<<"不在存在表"<< strSql;
    }

    return false;
}

void CTableLogWin::insertRow(QString strTableName, QVector<QString> vecRowValue)
{
    if(vecRowValue.size() != m_vecColumnName.size()){
        qDebug()<<"表插入行出错，传递数据和规定表头不符！请检查传入参数！" << vecRowValue.size()<<m_vecColumnName.size();
        return ;
    }

    if(!strTableName.isEmpty())
        m_strTableName = strTableName;

    QString strSqlInsert = "INSERT INTO "+m_strTableName + " (";
    for(int i = 0; i < m_vecColumnName.size(); i++){
        strSqlInsert += m_vecColumnName.at(i);
        if(i != (m_vecColumnName.size()-1))
            strSqlInsert += ",";
        else
            strSqlInsert += ") ";
    }

    strSqlInsert += " VALUES(";
    for(int i=0;i<m_vecColumnName.size();i++){
        strSqlInsert += ":" + m_vecColumnName.at(i);
        if(i < m_vecColumnName.size()-1)
            strSqlInsert += ",";
    }
    strSqlInsert += ")";

    m_dbQuery.prepare(strSqlInsert);
    for(int i = 0; i < vecRowValue.size();i++){
        m_dbQuery.bindValue(":" + m_vecColumnName.at(i),vecRowValue.at(i));
    }
    if(!m_dbQuery.exec())
        qDebug()<<"表插入行出错，语句为:"<<strSqlInsert<<",请检查语句!";
}
