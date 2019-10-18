#ifndef CLOGWIN_H
#define CLOGWIN_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QVector>
#include <QMutex>
#include <QTimer>
#include <QDomElement>
#include <QApplication>

#include "CLogWinEnm.h"

#define flushWin "FLUSH_LOG_WINCOMN_20191011"
#define ONE_HOUR_FOR_MSEC (60*60*1000)
#define ONE_DAY_FOR_MSEC (24*60*60*1000)

/*控制台输出字体颜色 40+背景色   30+字体色 0黑 1红 2绿 3黄 4蓝 5紫 6青 7白*/
#define LOG_FONT_FATAL      "\033[41;37m" //红底白字
#define LOG_FONT_ERROR      "\033[31m" //红色
#define LOG_FONT_WARNING    "\033[33m" //黄色
#define LOG_FONT_INFO       "\033[32m" //绿色
#define LOG_FONT_DEBUG      "\033[37m" //白色

/*控制台输出属性设置*/
#define LOG_ATTR_REC   "\033[0m"  //重新设置属性到缺省设置
#define LOG_ATTR_BOL   "\033[1m"  //设置粗体


class CLogWin : public QObject
{
    Q_OBJECT
public:
    CLogWin();
    ~CLogWin();
    static CLogWin *getInstance();

    CLogWin& log(); //用来实现格式化输出
    CLogWin& logFatal(const char *file,const char *func,int line);     //严重错误 造成程序终止
    CLogWin& logError(const char *file,const char *func,int line);     //一般错误 参数或操作错误，影响系统正常运行
    CLogWin& logWarning(const char *file,const char *func,int line);   //警告 可能造成错误
    CLogWin& logInfo(const char *file,const char *func,int line);      //状态信息或运行节点
    CLogWin& logDebug(const char *file,const char *func,int line);     //调试信息

    /*重载操作符*/
    CLogWin& operator <<(QChar t){m_strMsg += t; return *this;}
    CLogWin& operator <<(bool t){m_strMsg += (t ? "true" : "false"); return *this;}
    CLogWin& operator <<(char t){m_strMsg += QString(t); return *this;}
    CLogWin& operator <<(signed short i){m_strMsg += (QString::number(i));return *this;}
    CLogWin& operator <<(unsigned short i){m_strMsg += (QString::number(i));return *this;}
    CLogWin& operator <<(signed int i){m_strMsg += (QString::number(i));return *this;}
    CLogWin& operator <<(unsigned int i){m_strMsg += (QString::number(i));return *this;}
    CLogWin& operator <<(signed long l){m_strMsg += (QString::number(l));return *this;}
    CLogWin& operator <<(unsigned long l){m_strMsg += (QString::number(l));return *this;}
    CLogWin& operator <<(qint64 i){m_strMsg += (QString::number(i));return *this;}
    CLogWin& operator <<(quint64 i){m_strMsg += (QString::number(i));return *this;}
    CLogWin& operator <<(float f){m_strMsg += (QString::number(f));return *this;}
    CLogWin& operator <<(double f){m_strMsg += (QString::number(f));return *this;}
    CLogWin& operator <<(const char *s);
    CLogWin& operator <<(const QString &s){m_strMsg += s;return *this;}
    CLogWin& operator <<(const QStringRef &s){m_strMsg += s;return *this;}
    CLogWin& operator <<(QLatin1String s){m_strMsg += QString(s);return *this;}
    CLogWin& operator <<(const QByteArray &b){m_strMsg += QString(b);return *this;}
public:
    void setTimeStyle(EnmDisplayTimeStyle timeStyle){m_enmTimeStyle = timeStyle;}
    void setDBIdTimeStyle(EnmDisplayTimeStyle timeStyle){m_enmTimeDBIdStyle = timeStyle;}
    static bool textToBool(QString str){ return (str == "true") ? true : false;}
    static int textToInt(QString str){return str.toInt();}
signals:
    void signalRedirect(QString strDate);
    void signalCheckCache();
private slots:
    void slotFinshed();
    void slotTimeOutHours();
    void slotTimeOutDays();
private:
    void init();
    void loadConfig();
    void loadLogWinConfig(QDomElement root);
    void outLog();
    void processLogHead(const char *file,const char *func,int line); //处理日志头信息
    void processFileName();     //处理掉过长的文件名
    void jointMsg();            //拼接所有的信息为一个字符串
    QDateTime getDateTime(){return QDateTime::currentDateTime();}
    QString dateTimeToStr(QDateTime &dateTime,EnmDisplayTimeStyle timeStyle);
    const char *getLevelStyle(EnmLogLevel level);
    QVector<QString> getVecMsg();
private:
    EnmDisplayTimeStyle m_enmTimeStyle = TIME_STYLE_2;
    EnmDisplayTimeStyle m_enmTimeDBIdStyle = TIME_STYLE_3;
    EnmLogLevel m_currentLogLevel = LEVEL_DEBUG;
    QMutex m_qMutex;
    /*打印信息构成*/
    QString m_strDBId;
    QString m_strLevel;
    QString m_strDate;
    QString m_strFileName;
    QString m_strFuncName;
    QString m_strLineNum;
    QString m_strMsg;
    QString m_strAllMsg;

    /*输出方式*/
    bool m_bAbleOutDB = false;
    bool m_bAbleOutWindow = false;
    bool m_bAbleOutConsole = true;
    bool m_bAbleOutTxt = false;

    /*路径 和 名称*/
    QString m_strPathDB;
    QString m_strNameDB;
    QString m_strPathTxt;
    QString m_strNameTxt;

    /*输出优先级控制*/
    int m_nPriority = 5;            //目前有0~5  个优先级  0关闭所有输出

    /*产生新日志的周期*/
    QTimer *m_pTimerDays;
    int m_nCreateNewLog = 1;        //单位天  默认1天
    /*检查缓存周期*/
    QTimer *m_pTimerHous;              //周期小时
    int m_nCheckCacheHours = 12;    //检查缓存的周期   单位小时 默认12小时
};

#endif // CLOGWIN_H
