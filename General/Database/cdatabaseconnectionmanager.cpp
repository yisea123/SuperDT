#include "cdatabaseconnectionmanager.h"
#include "clog.h"
#include <QMutex>
#include <QFile>
#include <QFileInfo>
#include "CXmlTool.h"

CDatabaseConnectionManager::CDatabaseConnectionManager()
{
}

CDatabaseConnectionManager *CDatabaseConnectionManager::getInstance()
{
    static CDatabaseConnectionManager* m_pInstance = nullptr;
    if(m_pInstance == nullptr){
        if(m_pInstance == nullptr){
            m_pInstance = new CDatabaseConnectionManager();
        }
    }
    return m_pInstance;
}

bool CDatabaseConnectionManager::init()
{
    CXmlTool::loadConfig(this);
#ifdef Q_OS_ANDROID
    QString strSrc = "assets:/" + m_strDBPath;
    QFileInfo fiDestDB(m_strDBPath);
    QFileInfo fiSrcDB(strSrc);
    if(!fiDestDB.exists() && fiSrcDB.exists())
    {
        QByteArray data;
        QFile fileSrc(strSrc);
        if (fileSrc.open(QFile::ReadOnly)) {
            data = fileSrc.readAll();
            fileSrc.close();
        } else {
            qDebug() << "src file open failed " << fileSrc.fileName() << fileSrc.errorString();
        }

        QFile fileDest(m_strDBPath);
        if (fileDest.open(QFile::WriteOnly)) {
            fileDest.write(data);
            fileDest.close();
        } else {
            qDebug() << "dest file open failed" << fileDest.fileName() << fileDest.errorString();
        }
    }
#endif
    m_cDatabase = QSqlDatabase::addDatabase("QSQLITE");
    m_cDatabase.setDatabaseName(m_strDBPath);

    if(this->openConnection()){
        logImpInfoWin()<<"CDatabaseConnectionManager::init 本地数据库连接成功，地址为"<<m_strDBPath<<flushWin;
        this->closeConnection();
        return true;
    }else{
        logErrorWin()<<"CDatabaseConnectionManager::init 本地数据库初始连接失败，"
                       "试图打开的地址为"<<m_strDBPath<<flushWin;
        return false;
    }
}

void CDatabaseConnectionManager::loadConfig(QDomElement root)
{
    while (!root.isNull())
    {
        QDomElement element = root.toElement();
        if (!element.isNull())
        {
            if(element.tagName().compare("DatabaseType") == 0){
                m_strDBType = CXmlTool::getString(element);
            }else if(element.tagName().compare("DatabasePath") == 0){
                m_strDBPath = CXmlTool::getString(element);
            }else if(element.tagName().compare("DatabaseUserName") == 0){
                m_strDBUser = CXmlTool::getString(element);
            }else if(element.tagName().compare("DatabasePwd") == 0){
                m_strDBPwd = CXmlTool::getString(element);
            }
            root = root.nextSiblingElement();
        }
    }
}

bool CDatabaseConnectionManager::openConnection()
{
    m_qMutex.lock();
    if(m_cDatabase.open())
    {
        return true;
    }
    else{
        logErrorWin()<<"CDatabaseConnectionManager::openConnection 数据库连接失败"<<flushWin;
        m_qMutex.unlock();//@TODO 是否需要在此unLock
        return false;
    }
}

void CDatabaseConnectionManager::closeConnection()
{
    m_cDatabase.close();
    m_qMutex.unlock();
}
