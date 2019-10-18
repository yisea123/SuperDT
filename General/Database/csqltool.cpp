#include "csqltool.h"
#include "clog.h"
#include "cjson.h"
#include "QVariantList"
#include <QList>

QString CSqlTool::parseVectorToString(QVector<QString> vec)
{
    QVariantList qvList;
    for(int i=0;i<vec.size();i++){
        qvList.append(vec[i]);
    }
    QJsonObject jObj;
    jObj.insert("arrData",QJsonArray::fromVariantList(qvList));
    return CJson::parseToQString(jObj);
}

QString CSqlTool::parseVectorToString(QStringList vec)
{
    QVariantList qvList;
    for(int i=0;i<vec.length();i++){
        qvList.append(vec.at(i));
    }
    QJsonObject jObj;
    jObj.insert("arrData",QJsonArray::fromVariantList(qvList));
    return CJson::parseToQString(jObj);
}

QVector<QString> CSqlTool::parseStringToVector(QString str)
{
    QVector<QString> vecResult;
    QJsonArray jArr = CJson::parseToQJsonArray(str.toUtf8());
    for(int i = 0;i<jArr.size();i++)
    {
        QString strTemp = jArr.at(i).toString();
        vecResult.append(strTemp);
    }
    return vecResult;
}

QString CSqlTool::getSqlInsert(QString strTableName, int nColNum){
    //"insert into "+strTableName+" values(?,?)";
    QString strSqlInsert = "insert into "+strTableName+" values(";
    for(int i=0;i<nColNum-1;i++){
        strSqlInsert += "?,";
    }
    strSqlInsert += "?)";
    return strSqlInsert;
}

QString CSqlTool::getSqlDelete(QString strTableName, QString strKeyName)
{
    //"delete from " +strTableName + " where username = ?";
    QString strSqlDelete = "delete from " +strTableName + " where ";
    strSqlDelete += strKeyName + " = ?";
    return strSqlDelete;
}

QString CSqlTool::getSqlUpdateRow(QString strTableName, QVector<QString> arrColmnNames)
{//更新一行数据
    //"update "+strTableName+" set password =?,authority =? where username =?";
    QString strSqlUpdateRow = "update "+strTableName+" set ";
    for(int i=1;i<arrColmnNames.length()-1;i++){
        strSqlUpdateRow += arrColmnNames[i]+ " =?,";
    }
    strSqlUpdateRow += arrColmnNames[arrColmnNames.length()-1]+ " =? ";
    strSqlUpdateRow += "where "+arrColmnNames[0] + " =?";
    return 	strSqlUpdateRow;
}

QString CSqlTool::getSqlUpdateOneColm(QString strTableName,QString strUpdateColmnName,
                                      QString strColumnVal,QString strKeyName,QString strKeyVal)
{
    //"update "+strTableName+" set password = 'val' where username = 'val'";
    QString strSqlUpdate = "update "+strTableName+" set ";
    strSqlUpdate += strUpdateColmnName + " = '";
    strSqlUpdate += strColumnVal +"' where ";
    strSqlUpdate += strKeyName + " = '"+strKeyVal+"'";
    return strSqlUpdate;
}

QString CSqlTool::getSqlQuery(QString strTableName, QString strColmName)
{
    //"select * from "+strTableName+ " where username = ";
    QString strSqlQuery = "select * from " +strTableName + " where ";
    strSqlQuery += strColmName + " = ?";
    return strSqlQuery;
}

QString CSqlTool::getSqlQueryAll(QString strTableName){
    return "select * from " +strTableName;
}

QString CSqlTool::getSqlBindedValue(QString strSqlOrigin, QVector<QString> vecStruct)
{
    QString strSqlReturned = "";
    QList<QString> list = strSqlOrigin.split('?');
    if( (list.size()-1) != vecStruct.size()){
        logErrorWin()<<"CSqlTool::getSqlBindedValue sql语句和参数不符合"<< list.size()-1 << " " << vecStruct.size() << flushWin;
        return nullptr;
    }
    for(int i=0;i<list.size()-1;i++){
        strSqlReturned += list.at(i);
        if(vecStruct.at(i) == nullptr){
            strSqlReturned += "''";
        }else{
            strSqlReturned += "'"+vecStruct.at(i)+"'";
        }
    }
    strSqlReturned += list.at(list.size()-1);
    return strSqlReturned;
}
