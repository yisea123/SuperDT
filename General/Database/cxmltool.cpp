#include "CXmlTool.h"
#include "CConfiger.h"
#include <Qfile>
#include "clog.h"

QString CXmlTool::loadConfig(IConfigLoader *pLoader, QString strFolderName)
{
    QString strRealFolder = CConfiger::getApplicationUrl();
    if("" != strFolderName){//strFolderName不为空代表是UI配置文件
        strRealFolder += "UI/Controllers/" + strFolderName + "/";
    }
    QString strXmlPath = strRealFolder + "config.xml";

    QFile file(strXmlPath);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        logErrorWin()<<"找不到配置文件!指定的路径为："<<strXmlPath<<flushWin;
        return strRealFolder;
    }

    QString strError;int nErrorLine;int nErrorColumn;QDomDocument doc;
    if (!doc.setContent(&file, false, &strError, &nErrorLine, &nErrorColumn))
    {
        logErrorWin()<<"配置文件格式错误!指定的路径为："+strXmlPath<<flushWin;
        return strRealFolder;
    }

    QDomElement root = doc.documentElement();
    if(root.tagName() != "Config")
    {
        logErrorWin()<<"没找到Config根节点!指定的路径为："+strXmlPath<<flushWin;
        return strRealFolder;
    }

    QDomElement node = root.firstChildElement();
    pLoader->loadConfig(node);
    file.close();
    return strRealFolder;
}

QString CXmlTool::loadUIConfig(QString strFolderName, IConfigLoader *pLoader)
{
    return loadConfig(pLoader,strFolderName);
}

QString CXmlTool::getString(QDomElement element)
{
    return element.text();
}

int CXmlTool::getInt(QDomElement element)
{
    QString str= element.text();
    bool ok;
    int tmpPort = str.toInt(&ok,10);
    if(ok)
    {
        return tmpPort;
    }
    else
    {
        return -1;
    }
}

bool CXmlTool::getBool(QDomElement element)
{
    QString str= element.text();
    if(str.compare("true")==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
