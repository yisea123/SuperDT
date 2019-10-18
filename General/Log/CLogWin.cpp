#include "CLogWin.h"
#include "CLogWinForDB.h"
#include "CLogWinForWindow.h"
#include "CLogWinForTxt.h"

CLogWin::CLogWin()
{
    this->init();
}

CLogWin::~CLogWin()
{
    m_pTimerHous->stop();
    m_pTimerDays->stop();
}

CLogWin *CLogWin::getInstance()
{
    static CLogWin* m_pInstance = nullptr;
    if(m_pInstance == nullptr){
        if(m_pInstance == nullptr){
            m_pInstance = new CLogWin();
        }
    }
    return m_pInstance;
}
void CLogWin::init()
{
    this->loadConfig();//获取配置文件

    this->setTimeStyle(TIME_STYLE_2);

    m_pTimerDays = new QTimer(this);
    connect(m_pTimerDays,SIGNAL(timeout()),this,SLOT(slotTimeOutDays()));
    m_pTimerDays->start(1*1000); //24*60*60*1000 (天)

    m_pTimerHous = new QTimer(this);
    connect(m_pTimerHous,SIGNAL(timeout()),this,SLOT(slotTimeOutHours()));
    m_pTimerHous->start(1*1000);          //60*60*1000 (小时)

    /*绑定文件输出重定向槽函数*/
    if(m_bAbleOutDB){
        CLogWinForDB::getInstance()->init();
        connect(this,SIGNAL(signalRedirect(QString)),CLogWinForDB::getInstance(),SLOT(slotRedirect(QString)));
        connect(this,SIGNAL(signalCheckCache()),CLogWinForDB::getInstance(),SLOT(slotCheckCache()));
    }

    if(m_bAbleOutTxt){
        CLogWinForTxt::getInstance()->init();
        connect(this,SIGNAL(signalRedirect(QString)),CLogWinForTxt::getInstance(),SLOT(slotRedirect(QString)));
        connect(this,SIGNAL(signalCheckCache()),CLogWinForTxt::getInstance(),SLOT(slotCheckCache()));
    }
}

CLogWin &CLogWin::log()
{
    return *this;
}

CLogWin &CLogWin::logFatal(const char *file, const char *func, int line)
{  
    m_currentLogLevel = LEVEL_FATAL;
    m_strLevel = "FATAL";
    processLogHead(file,func,line);

    return *this;
}

CLogWin &CLogWin::logError(const char *file, const char *func, int line)
{
    m_currentLogLevel = LEVEL_ERROR;
    m_strLevel = "ERROR";
    processLogHead(file,func,line);

    return *this;
}

CLogWin &CLogWin::logWarning(const char *file, const char *func, int line)
{
    m_currentLogLevel = LEVEL_WARNING;
    m_strLevel = "WARNING";
    processLogHead(file,func,line);

    return *this;
}

CLogWin &CLogWin::logInfo(const char *file, const char *func, int line)
{
    m_currentLogLevel = LEVEL_INFO;
    m_strLevel = "INFO";
    processLogHead(file,func,line);

    return *this;
}

CLogWin &CLogWin::logDebug(const char *file, const char *func, int line)
{
    m_currentLogLevel = LEVEL_DEBUG;
    m_strLevel = "DEBUG";
    processLogHead(file,func,line);

    return *this;
}

void CLogWin::slotFinshed()
{
    qDebug()<<"LogWin线程结束!";
}


void CLogWin::loadConfig()
{
    QString strXmlPath = QApplication::applicationDirPath()+"/LogWinConfig.xml";
    QFile file(strXmlPath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"CConfig::ReadConfig 打开配置文件失败！"<< strXmlPath <<flushWin;
        return;
    }

    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
        return ;
    QDomElement root = doc.documentElement();
    if(root.tagName() != "LogWinConfig")
        return;
    file.close();

    /*加载配置文件*/
    this->loadLogWinConfig(root);
    CLogWinForDB::getInstance()->loadLogWinConfig(root);
    CLogWinForTxt::getInstance()->loadLogWinConfig(root);
}

void CLogWin::loadLogWinConfig(QDomElement root)
{
    QDomElement node = root.firstChildElement();
    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        if (!element.isNull())
        {
            if(element.tagName() == "AbleOutDB"){
               m_bAbleOutDB = textToBool(element.text());
            }else if(element.tagName() == "AbleOutWindow"){
               m_bAbleOutWindow = textToBool(element.text());
            }else if(element.tagName() == "AbleOutConsole"){
               m_bAbleOutConsole = textToBool(element.text());
            }else if(element.tagName() == "AbleOutTxt"){
               m_bAbleOutTxt = textToBool(element.text());
            }else if(element.tagName() == "OutPriority"){
               m_nPriority = textToInt(element.text());
            }else if(element.tagName() == "CreateNewLog"){
                m_nCreateNewLog = textToInt(element.text());
            }else if(element.tagName() == "CheckCacheHours"){
                m_nCheckCacheHours = textToInt(element.text());
            }

            node = node.nextSiblingElement();
        }
    }

    qDebug()<<"LogWin加载配置文件完毕!"<< m_bAbleOutDB << m_bAbleOutWindow << m_bAbleOutConsole<< m_bAbleOutTxt \
           << m_nPriority <<m_nCreateNewLog <<m_nCheckCacheHours;
}


void CLogWin::slotTimeOutHours()
{
    static int nSgHours = 0;

    nSgHours++;
    if(m_nCheckCacheHours == nSgHours){
        nSgHours = 0;
        emit signalCheckCache(); //m_nCheckCacheHours 小时发出一次信号
        qDebug()<<"发出检测缓存日志文件信号!";
    }
}

void CLogWin::slotTimeOutDays()
{
    static int nSgDays = 0;

    nSgDays++;
    if(m_nCreateNewLog == nSgDays){
        nSgDays = 0;
        /*获取系统日期*/
        QDateTime dateTime = getDateTime();
        QString strDate = dateTimeToStr(dateTime,TIME_STYLE_4);
        emit signalRedirect(strDate); //m_nCreateNewLog 天发出一次该信号
        qDebug()<<"发出文件重定向信号！";
    }
}

const char *CLogWin::getLevelStyle(EnmLogLevel level)
{
    switch(level){
    case LEVEL_FATAL:
        return LOG_FONT_FATAL;
    case LEVEL_ERROR:
        return LOG_FONT_ERROR;
    case LEVEL_WARNING:
        return LOG_FONT_WARNING;
    case LEVEL_INFO:
        return LOG_FONT_INFO;
    case LEVEL_DEBUG:
        return LOG_FONT_DEBUG;
    default:
        return " ";
    }
}

QVector<QString> CLogWin::getVecMsg()
{
    QVector<QString> vecMsg;
    vecMsg.append(m_strDBId);
    vecMsg.append(m_strLevel);
    vecMsg.append(m_strDate);
    vecMsg.append(m_strFileName);
    vecMsg.append(m_strFuncName);
    vecMsg.append(m_strLineNum);
    vecMsg.append(m_strMsg);

    return vecMsg;
}

CLogWin &CLogWin::operator<<(const char *s)
{
    /*遇到输出标记  开始输出日志*/
    if((QString)s == (QString)flushWin){
        if(m_currentLogLevel > m_nPriority) //当前输出等级大于设定优先级  不输出
            return *this;

        /*输出日志信息*/
        jointMsg();//拼接信息     
        m_qMutex.lock();
        outLog();
        m_qMutex.unlock();
    }else{
        m_strMsg += s;
    }

    return *this;
}

void CLogWin::outLog()
{
    /*输出到数据库*/
    if(m_bAbleOutDB)
    {
        CLogWinForDB::getInstance()->insertRow(nullptr,getVecMsg());
    }

    /*输出到控制台*/
    if(m_bAbleOutConsole)
    {
        const char *levelStyle = getLevelStyle(m_currentLogLevel); //这个属性不能使用QString类型  会导致设置失效
        qDebug()<<levelStyle<<m_strAllMsg<<LOG_ATTR_REC; //恢复控制台默认属性;
    }

    /*输出到窗口*/
    if(m_bAbleOutWindow)
    {
        CLogWinForWindow::getInstance()->appendLog(m_strAllMsg);
    }

    /*输出到文本文件*/
    if(m_bAbleOutTxt)
    {
        CLogWinForTxt::getInstance()->appendLog(m_strAllMsg);
    }

    m_strMsg = "";
}

void CLogWin::processLogHead(const char *file, const char *func, int line)
{
    QDateTime dateTime = getDateTime();
    m_strDBId = dateTimeToStr(dateTime,m_enmTimeDBIdStyle);
    m_strDate = dateTimeToStr(dateTime,m_enmTimeStyle);
    m_strFileName = QString(file);
    m_strFuncName = QString(func);
    m_strLineNum = QString::number(line);
    processFileName();
}

void CLogWin::processFileName()
{
    int pos = m_strFileName.lastIndexOf("\\");
    if(-1 == pos) //未查找到  返回
        return ;

    int size = m_strFileName.size();

    m_strFileName = m_strFileName.mid(pos + 1,size - pos + 2);
}

void CLogWin::jointMsg()
{
    /*拼接所有的Log信息*/
    m_strAllMsg = "[" + m_strLevel.leftJustified(7,' ') + "] "
                + "[" + m_strDate + "] "
                + "[File:" + m_strFileName + "] "
                + "[Func:" + m_strFuncName + "(){}] "
                + "[Line:" + m_strLineNum + "] "
            + m_strMsg;
}

QString CLogWin::dateTimeToStr(QDateTime &dateTime, EnmDisplayTimeStyle timeStyle)
{
    QString strTime;

    switch (timeStyle){
    case TIME_STYLE_1:
        strTime =  dateTime.toString("hh:mm:ss");
        break;
    case TIME_STYLE_2:
        strTime =  dateTime.toString("yyyy-MMM-ddd hh:mm:ss A");
        break;
    case TIME_STYLE_3:
        strTime =  dateTime.toString("yyyyMMddhhmmss");
        break;
    case TIME_STYLE_4:
        strTime =  dateTime.toString("hhmmss");
        break;
    default:
        break;
    }

    return strTime;
}
