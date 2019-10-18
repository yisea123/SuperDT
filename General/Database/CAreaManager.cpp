#include "CAreaManager.h"
#include "AdapterArea.h"

CAreaManager::CAreaManager(QObject *parent) : QObject(parent)
{

}

QString CAreaManager::getName(QString strArea, int nLeve)
{
    QString strName;
    QString strAreaTemp = strArea;
    StArea stTemp;

    stTemp = AdapterArea::getInstance()->queryRow(strAreaTemp);
    if("" == stTemp.strId){
        return "";
    }
    strName = stTemp.strName;
    strAreaTemp = stTemp.strParent;

    for(int i=0; i<nLeve; i++)
    {
        stTemp = AdapterArea::getInstance()->queryRow(strAreaTemp);
        if("" == stTemp.strId || "" == stTemp.strName){
            break;
        }
        strName = stTemp.strName + "-" + strName;
        strAreaTemp = stTemp.strParent;
    }
    return strName;
}

QString CAreaManager::getSimpleName(QString strArea, int nLeve)
{
    QString strName;
    QString strAreaTemp = strArea;
    StArea stTemp;

    stTemp = AdapterArea::getInstance()->queryRow(strAreaTemp);
    if("" == stTemp.strId){
        return "";
    }
    strName = stTemp.strSimpleName;
    strAreaTemp = stTemp.strParent;

    for(int i=0; i<nLeve; i++)
    {
        stTemp = AdapterArea::getInstance()->queryRow(strAreaTemp);
        if("" == stTemp.strId || "" == stTemp.strSimpleName){
            break;
        }
        strName = stTemp.strSimpleName + "-" + strName;
        strAreaTemp = stTemp.strParent;
    }
    return strName;
}

QMap<QString, QString> CAreaManager::getChildArea(QString strArea)
{
    QMap<QString, QString> mapAreaName;

    QVector<StArea> vecStrArea = AdapterArea::getInstance()->queryAll();
    foreach (StArea st, vecStrArea) {
        if(st.strParent == strArea){
            mapAreaName.insert(st.strId, st.strName);
        }
    }

    return mapAreaName;
}
