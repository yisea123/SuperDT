#ifndef CXMLTOOL_H
#define CXMLTOOL_H

#include <QString>
#include <QDomElement>
#include "IConfigLoader.h"

class CXmlTool
{
public:
    static QString loadConfig(IConfigLoader *pLoader,QString strFolderName = "");
    static QString loadUIConfig(QString strFolderName,IConfigLoader *pLoader);
    static QString getString(QDomElement element);
    static int getInt(QDomElement element);
    static bool getBool(QDomElement element);
};

#endif // CXMLTOOL_H
