#include "CLogWinForDB.h"
#include "clog.h"

CLogWinForDB::CLogWinForDB()
{

}

CLogWinForDB *CLogWinForDB::getInstance()
{
    static CLogWinForDB* m_pInstance = nullptr;
    if(m_pInstance == nullptr){
        if(m_pInstance == nullptr){
            m_pInstance = new CLogWinForDB();
        }
    }
    return m_pInstance;
}

void CLogWinForDB::init()
{
    m_strTableName = "LOG_WIN_FIRST";

    if(this->initDB()){
        qDebug()<<"日志专用数据库: "<<m_strDBPath<<" 已存在";
    }

    m_dbQuery = QSqlQuery(m_dbDatabase);

    this->creatTable(m_strTableName,m_vecColumnName);
}

void CLogWinForDB::loadLogWinConfig(QDomElement root)
{
    QDomElement node = root.firstChildElement();
    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        if (!element.isNull())
        {
            if(element.tagName() == "DatabasePath"){
               m_strDBPath = element.text();
            }else if(element.tagName() == "EnmClearLogStragety"){
               m_enmClearLogStragety = CLogWinEnm::getClearLogStragetyFromString(element.text());
            }else if(element.tagName() == "LogMaxSize"){
               m_nLogMaxSize = CLogWin::textToInt(element.text());
            }else if(element.tagName() == "LogSafetySize"){
                m_nLogSafetySize = CLogWin::textToInt(element.text());
            }

            node = node.nextSiblingElement();
        }
    }

    qDebug()<<"DB加载配置文件完毕!" <<m_strDBPath<<m_enmClearLogStragety<<m_nLogMaxSize<<m_nLogSafetySize;
}

bool CLogWinForDB::initDB()
{
    m_dbDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_dbDatabase.setDatabaseName(m_strDBPath);

    return this->openConnection();
}

bool CLogWinForDB::openConnection()
{
    if(m_dbDatabase.open())
    {
        qDebug()<<"CLogWinForDB::openConnection 本地数据库连接成功，地址为"<<m_strDBPath;
        return true;
    }
    else{
        qDebug()<<"CLogWinForDB::openConnection 本地数据库初始连接失败，"
                       "试图打开的地址为"<<m_strDBPath;
        return false;
    }
}

void CLogWinForDB::closeConnection()
{
    m_dbDatabase.close();
}


void CLogWinForDB::creatTable(QString strTableName, QVector<QString> vecColumnNames)
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

bool CLogWinForDB::isHasTable(QString strTableName)
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

void CLogWinForDB::removeTable(QString strTableName)
{
    if(!isHasTable(m_strTableName))
        return ;                //表不存在  直接返回

    QString strSql = "drop table " + strTableName + ";";
    m_dbQuery.prepare(strSql);
    m_dbQuery.exec();
}

void CLogWinForDB::insertRow(QString strTableName, QVector<QString> vecRowValue)
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

quint64 CLogWinForDB::getFileSize(const QString strFileName)
{
    QFileInfo tmpFileInfo(strFileName);

    return tmpFileInfo.size();
}

int CLogWinForDB::getDBTableCount()
{
    m_listTableName = m_dbDatabase.tables();
    return m_listTableName.count();
}

int CLogWinForDB::getDBArgForStragety()
{
    /*根据策略获取文件参数*/
    switch(m_enmClearLogStragety){
    case ENM_COUNT:
        return getDBTableCount();  //获取数据库中表的个数
    case ENM_SIZE:
        return byteToMB(getFileSize(m_strDBPath)); //获取数据库文件的大小
    default:
        return 0;
    };
}

void CLogWinForDB::clearLogToSafe()
{
    m_listTableName = m_dbDatabase.tables(); //最先创建的在前边
    if(m_listTableName.isEmpty())            //数据库中没有表  无法删除
        return ;

    this->removeTable(m_listTableName.takeFirst());  //删除所有表中最前边的一张表

    int nDBSize = getDBArgForStragety(); //根据策略获取日志的个数 或 大小（MB）
    qDebug()<<"日志数:"<<nDBSize;
    if(nDBSize > m_nLogSafetySize)
        clearLogToSafe();
}

void CLogWinForDB::slotRedirect(QString strDate)
{
    m_strTableName = "LOG_WIN_" + strDate;
    if(isHasTable(m_strTableName))
        return ;

    this->creatTable(m_strTableName,m_vecColumnName);
}

void CLogWinForDB::slotCheckCache()
{
    int nDBSize = getDBArgForStragety();

    /*超出限定最大值 清理日志*/
    if(nDBSize > m_nLogMaxSize)
        clearLogToSafe();
}
