#ifndef AdapterArea_H
#define AdapterArea_H

#include <CTable.h>
#include "AdapterArea.h"

struct StArea : public StData//,public StArea
{
    QString strId;
    QString strName;
    QString strSimpleName;
    QString strParent;
    int nLevel;

    // 注意逗号分隔， 每增加一行都要有逗号
    QVector<QString> m_vecColumnNames = {
        "id",                       // 0
        "Name",                     // 1
        "SimpleName",               // 2
        "ParentArea",               // 3
        "Level"                     // 4
    };

public:
    StArea(){}
    StArea(QVector<QString> vec){
        if(vec.size()!=m_vecColumnNames.size()){
            logErrorWin()<<"StArea构造函数 错误的vec大小"<<flushWin;
            return;
        }
        strId = vec.at(0);
        strName = vec.at(1);
        strSimpleName = vec.at(2);
        strParent = vec.at(3);
        nLevel = vec.at(4).toInt();
    }


    QString getId(){return strId;}
public:
    void loadData(QVector<QString> vec)
    {
        if(vec.size()!=m_vecColumnNames.size()){
            logErrorWin()<<"StArea loadData 错误的vec大小"<< vec.size() << m_vecColumnNames.size() << flushWin;
            return;
        }

        strId = vec.at(0);
        strName = vec.at(1);
        strSimpleName = vec.at(2);
        strParent = vec.at(3);
        nLevel = vec.at(4).toInt();
    }

    QString getValue(int nIndex){
        switch(nIndex) {
        case 0:
            return strId;
        case 1:
            return strName;
        case 2:
            return strSimpleName;
        case 3:
            return strParent;
        case 4:
            return QString::number(nLevel);
        default:
            logErrorWin()<<"StArea::getValue 非法参数"<<nIndex<<flushWin;
            return "";
        }
    }

    QVector<QString> toQVector(){
        QVector<QString> vec;
        vec.push_back(strId);               // 0
        vec.push_back(strName);             // 1
        vec.push_back(strSimpleName);       // 2
        vec.push_back(strParent);           // 3
        vec.push_back(QString::number(nLevel));           // 4
        return vec;
    }
};


class AdapterArea : public CTable
{
    Q_OBJECT
protected:
    AdapterArea();
public:
    static AdapterArea* getInstance();
private:
//    static AdapterArea *m_pInstance;
public:
    void addRow(StArea st);
    void updateRow(StArea st);
    StArea queryRow(QString strId);
    QVector<StArea> queryAll();

    QString getPrefix(QString strArea,int nLeve);
    QString getSimplePrefix(QString strArea,int nLeve);
    QVector<StArea> getChild(QString strArea);

private:
    QMap<QString, StArea> m_mapAreadIdSt;   //

public:
    void loadExcel(QVector<QVector<QString>> vecData);
protected:
};

#endif // AdapterArea_H
