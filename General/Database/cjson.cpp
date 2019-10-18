#include "cjson.h"
#include <QJsonDocument>
#include <clog.h>

QByteArray CJson::toQByteArray(QJsonObject jJsonObj)
{
    //1、生成Json节点 示例
    //    QJsonObject jJsonObj;
    //    jJsonObj.insert("name", QString("Qt"));
    //    jJsonObj.insert("version", 5);
    //    jJsonObj.insert("windows", true);

    //2、将Json节点转成Json文件
    QJsonDocument jDocument;
    jDocument.setObject(jJsonObj);

    //3、将Json文件转出QString
    QByteArray arrJson = jDocument.toJson(QJsonDocument::Compact);
    return arrJson;
}

QString CJson::parseToQString(QJsonObject jJsonObj)
{
    QString strJson(toQByteArray(jJsonObj));
    return strJson;
}

QJsonObject CJson::parseToQJson(QByteArray dataJson)
{
    //1、Json转换成QJsonDocument
    QJsonParseError jError;
    QJsonDocument jDocument = QJsonDocument::fromJson(dataJson,&jError);

    //2、错误检验
    if(jError.error != QJsonParseError::NoError || !jDocument.isObject())
    {
        logErrorWin()<<"CJson parseToQJson 错误的Json格式："<<dataJson<<flushWin;
        QJsonObject jEmpty;
        return jEmpty;
    }

    return jDocument.object();

    //    //3、从QJsonObject获取节点数据 示例
    //    QJsonObject jJsonObj = CJson::parseToQJson(strJson);
    //    if(!jJsonObj.contains("name") || !jJsonObj.value("name").isString()
    //            || !jJsonObj.contains("version") || !jJsonObj.value("version").isDouble()
    //            || !jJsonObj.contains("windows") || !jJsonObj.value("windows").isBool())
    //    {
    //        CLogHelper::write("类名:方法名 数据与协议不符"+strJson,LOG_ERROR);
    //        //return;
    //    }

    //    QString strName = jJsonObj.value("name").toString();
    //    int nVersion = jJsonObj.value("version").toInt();
    //    bool bFlag = jJsonObj.value("windows").toBool();
}

QJsonArray CJson::parseToQJsonArray(QByteArray dataJson)
{
    QJsonObject jObj = CJson::parseToQJson(dataJson);
    if(!jObj.contains("arrData") || !jObj.value("arrData").isArray()){
        //logErrorWin<<"CJson parseToQJsonArray 不符合arrData节点数组方式："<<dataJson<<flushWin;
        QJsonArray jArrEmpty;
        return jArrEmpty;
    }
    QJsonArray jArr = jObj.value("arrData").toArray();

    return jArr;

    //    //处理Json数组的示例代码
    //    QJsonArray jArr = CJson::parseToQJsonArray(strData);
    //    bool bIsFirstCheck = true;//用于后续值检查，由于是Json数组，考虑效率，只检查一次。
    //    for(int i = 0;i<jArr.size();i++)
    //    {
    //        QJsonObject jJsonObj = jArr.at(i).toObject();
    //        if(bIsFirstCheck){
    //            bIsFirstCheck = false;
    //            if(!jJsonObj.contains("strId") || !jJsonObj.value("strId").isString()
    //                    || !jJsonObj.contains("strEchoUrl") || !jJsonObj.value("strEchoUrl").isString()
    //                    || !jJsonObj.contains("strName") || !jJsonObj.value("strName").isString()
    //                    || !jJsonObj.contains("strRoomId") || !jJsonObj.value("strRoomId").isString() )
    //            {
    //                CLogHelper::write("类名:方法名 数据与协议不符"+strData,LOG_ERROR);
    //                return;
    //            }
    //        }
    //        QString strId = jJsonObj.value("strId").toString();
    //        QString strEchoUrl = jJsonObj.value("strEchoUrl").toString();
    //        QString strName = jJsonObj.value("strName").toString();
    //        QString strRoomId = jJsonObj.value("strRoomId").toString();
    //        //@TODO 处理数据的逻辑代码
    //    }
}

QVector<QByteArray> CJson::splitJsonToVec(QByteArray dataJson)
{
    QVector<QByteArray> vecdata;
    int nLeftNum = 0;
    int nRightNum = 0;
    int nStart = 0;
    for(int i = 0 ;i < dataJson.length() ;i++)
    {
        if(dataJson.at(i) == '{') nLeftNum++;
        if(dataJson.at(i) == '}') nRightNum++;
        if(nLeftNum == nRightNum && nLeftNum != 0)
        {
            nLeftNum = 0;
            nRightNum = 0;
            vecdata.push_back(dataJson.mid(nStart,i-nStart+1));
            nStart = i+1;
        }
    }
    return vecdata;
}
QVector<QJsonObject> CJson::jsonArrToVectorJObject(QJsonArray jJsonArr)
{
    QVector<QJsonObject> vecJObject;
    for(int i = 0 ; i < jJsonArr.size(); i++){
        QJsonObject jObject = jJsonArr.at(i).toObject();
        vecJObject.append(jObject);
    }
    return vecJObject;
}

