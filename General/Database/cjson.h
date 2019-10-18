#ifndef CJOSN_H
#define CJOSN_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
class CJson
{
public:
    static QByteArray toQByteArray(QJsonObject jJsonObj);
    static QString parseToQString(QJsonObject jJsonObj);
    static QJsonObject parseToQJson(QByteArray dataJson);
    static QJsonArray parseToQJsonArray(QByteArray dataJson);
    static QVector<QByteArray> splitJsonToVec(QByteArray dataJson);
    static QVector<QJsonObject> jsonArrToVectorJObject(QJsonArray jJsonArr);
};

#endif // CJOSN_H
