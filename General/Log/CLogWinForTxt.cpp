#include "CLogWinForTxt.h"
#include <QDebug>

CLogWinForTxt::CLogWinForTxt()
{

}

CLogWinForTxt *CLogWinForTxt::getInstance()
{
    static CLogWinForTxt* m_pInstance = nullptr;
    if(m_pInstance == nullptr){
        if(m_pInstance == nullptr){
            m_pInstance = new CLogWinForTxt();
        }
    }
    return m_pInstance;
}

void CLogWinForTxt::init()
{
    QDir tempDir;
    m_strDirPath = getDirPath(m_strFilePath);
    if(!tempDir.exists(m_strDirPath))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(m_strDirPath);
    }

    m_pFileLog = new QFile(m_strFilePath);
}

void CLogWinForTxt::loadLogWinConfig(QDomElement root)
{
    QDomElement node = root.firstChildElement();
    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        if (!element.isNull())
        {
            if(element.tagName() == "TxtPath"){
               m_strFilePath = element.text();
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
    qDebug()<<"Txt加载配置文件完毕!" <<m_strFilePath<<m_enmClearLogStragety<<m_nLogMaxSize<<m_nLogSafetySize;
}


QString CLogWinForTxt::getDirPath(QString strPath)
{
    int pos = strPath.lastIndexOf("/");
    if(-1 == pos) //未查找到  返回
        return "";

    return strPath.mid(0,pos + 1);
}

void CLogWinForTxt::appendLog(QString strLog)
{
    if(!m_pFileLog->open(QIODevice::ReadWrite|QIODevice::Append)){
        qDebug()<<m_strFilePath <<":文件打开失败!";
    }

    QTextStream textStream(m_pFileLog);
    textStream<<strLog<<endl;
    m_pFileLog->flush();
    m_pFileLog->close();
}

void CLogWinForTxt::slotRedirect(QString strDate)
{
    delete m_pFileLog;
    m_strFilePath = getDirPath(m_strFilePath) + "LogWin" + strDate + ".txt";

    m_pFileLog = new QFile(m_strFilePath);
    if(m_pFileLog->open(QIODevice::ReadWrite)){
        qDebug()<<"新的日志文件创建成功!";
        m_pFileLog->close();
    }else{
        qDebug()<<"新的日志文件创建失败!";
    }
}

void CLogWinForTxt::slotCheckCache()
{
    qDebug()<<"检查日志缓存!";
    int dirSize = getDirArgForStragety();

    if(dirSize > m_nLogMaxSize)
        clearLogToSafe();
}

void CLogWinForTxt::clearLogToSafe()
{
    /*获取文件列表  日期排序*/
    QDir tmpDir(m_strDirPath);
    QStringList fileNameList = tmpDir.entryList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Time);

    /*按旧日期在前  删除一个最旧的日志文件*/
    QString strFileName;
    strFileName = fileNameList.at(fileNameList.count()-1); //获取最旧的日志文件
    QFile::remove(m_strDirPath+strFileName);
    qDebug()<<"删除日志文件"<<(m_strDirPath+strFileName);

    int dirSize = getDirArgForStragety();
    /*递归删除  直至文件夹大小达到m_nLogSafetySize以内*/
    if(dirSize > m_nLogSafetySize)
        clearLogToSafe();
    else
        return ;
}

/******
* Note:传入的文件路径格式如: "D:/SoftPage/SVN"
* "D:\SoftPage\SVN" 无效  需转义为"D:\\SoftPage\\SVN"可正常使用
****/
quint64 CLogWinForTxt::getDirSize(const QString filePath)
{
    QDir tmpDir(filePath);
    quint64 size = 0;

    /*获取文件列表  统计文件大小*/
    foreach(QFileInfo fileInfo, tmpDir.entryInfoList(QDir::Files)){
        size += fileInfo.size();
    }

    /*获取文件夹  并且过滤掉.和..文件夹 统计各个文件夹的文件大小 */
    foreach(QString subDir, tmpDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
        size += getDirSize(filePath + QDir::separator() + subDir); //递归进行  统计所有子目录
    }

    return size;
}

int CLogWinForTxt::getDirFileCount(const QString filePath)
{
    QDir tmpDir(filePath);
    return tmpDir.entryInfoList(QDir::Files).count();
}

int CLogWinForTxt::getDirArgForStragety()
{
    /*根据策略删除文件*/
    switch(m_enmClearLogStragety){
    case ENM_COUNT:
        return  getDirFileCount(m_strDirPath);  //获取文件个数
    case ENM_SIZE:
        return byteToMB(getDirSize(m_strDirPath)); //获取文件大小
    default:
        return 0;
    };
}
