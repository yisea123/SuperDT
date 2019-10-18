#ifndef CLOGWINFORTXT_H
#define CLOGWINFORTXT_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QDomElement>

#include "CLogWin.h"

class CLogWinForTxt : public QObject
{
    Q_OBJECT
public:
    CLogWinForTxt();
    static CLogWinForTxt *getInstance();

    void init();
    void appendLog(QString strLog);
    void loadLogWinConfig(QDomElement root);
public slots:
    void slotRedirect(QString strDate);
    void slotCheckCache();
private:
    void clearLogToSafe();
    quint64 getDirSize(const QString filePath);
    QString getDirPath(QString strPath);
    int getDirFileCount(const QString filePath);
    int getDirArgForStragety();
    int byteToMB(quint64 byte){return (byte<(1024*1024)) ? 0 : byte >> 20;}
private:
    QFile *m_pFileLog;
    QString m_strFilePath = "C:/LogWin/LogWin.txt";
    QString m_strDirPath;  //日志的文件夹位置

    EnmClearLogStragety m_enmClearLogStragety = ENM_COUNT;
    int m_nLogMaxSize =  20;
    int m_nLogSafetySize = 20;
};

#endif // CLOGWINFORTXT_H
