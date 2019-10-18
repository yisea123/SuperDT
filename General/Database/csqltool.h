#ifndef CSQLTOOL_H
#define CSQLTOOL_H

#include <QString>
#include <QVector>

class CSqlTool
{
public:
    static QString parseVectorToString(QVector<QString> vec);
    static QString parseVectorToString(QStringList vec);
    static QVector<QString> parseStringToVector(QString str);

    static QString getSqlInsert(QString strTableName, int nColNum);
    static QString getSqlDelete(QString strTableName,QString strKeyName);
    static QString getSqlUpdateRow(QString strTableName,QVector<QString> arrColmnNames);
    static QString getSqlUpdateOneColm(QString strTableName,QString strUpdateColmnName,
                                       QString strColumnVal,QString strKeyName,QString strKeyVal);

    static QString getSqlQuery(QString strTableName,QString strColmName);
    static QString getSqlQueryAll(QString strTableName);

    static QString getSqlBindedValue(QString strSqlOrigin,QVector<QString> vecStruct);
};

#endif // CSQLTOOL_H
