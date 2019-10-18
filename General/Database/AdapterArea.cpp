#include "AdapterArea.h"
#include "CEnmTool.h"
AdapterArea::AdapterArea():CTable("TABLE_Area",StArea().m_vecColumnNames)
{
    m_strExcelName = "TableArea.xls";
}


//AdapterArea* AdapterArea::m_pInstance = new AdapterArea();
AdapterArea *AdapterArea::getInstance()
{
    static AdapterArea* pInstance = nullptr;
    if(pInstance == nullptr){
        pInstance = new AdapterArea();
    }
    return pInstance;
//    return m_pInstance;
}


void AdapterArea::addRow(StArea st)
{
    CTable::addRow<StArea>(st);
}

void AdapterArea::updateRow(StArea st)
{
    CTable::updateRow<StArea>(st);
}

StArea AdapterArea::queryRow(QString strId)
{
    return CTable::queryRow<StArea>(strId);
}

QVector<StArea> AdapterArea::queryAll()
{
    return CTable::queryAll<StArea>();
}

QString AdapterArea::getPrefix(QString strArea,int nLeve)
{
    QString strPreFix;
    QString strAreaTemp = strArea;
    StArea stTemp;

    if(nLeve <= 1){
        return strPreFix;
    }

    QVector<StArea> vecArea = queryAll();
    foreach (StArea st, vecArea) {
        m_mapAreadIdSt.insert(st.getId(),st);
    }

    for(int i=1; i<nLeve; i++){
        stTemp = m_mapAreadIdSt.value(strAreaTemp);
        if("" == stTemp.strId || "" == stTemp.strName){
            break;
        }
        strPreFix = stTemp.strName + "-" + strPreFix;
        strAreaTemp = stTemp.strParent;
    }
    return strPreFix;
}

QString AdapterArea::getSimplePrefix(QString strArea,int nLeve)
{
    QString strPreFix;
    QString strAreaTemp = strArea;
    StArea stTemp;

    if(nLeve <= 1){
        return strPreFix;
    }

    QVector<StArea> vecArea = queryAll();
    foreach (StArea st, vecArea) {
        m_mapAreadIdSt.insert(st.getId(),st);
    }

    for(int i=1; i<nLeve; i++){
        stTemp = m_mapAreadIdSt.value(strAreaTemp);
        if("" == stTemp.strId || "" == stTemp.strName){
            break;
        }
        strPreFix = stTemp.strSimpleName + "-" + strPreFix;
        strAreaTemp = stTemp.strParent;
    }
    return strPreFix;
}

QVector<StArea> AdapterArea::getChild(QString strArea)
{
    QVector<StArea> vecStArea;

    QVector<StArea> vecStTemp = queryAll();
    foreach (StArea stTemp, vecStTemp) {
        if(stTemp.strParent == strArea){
            vecStArea.push_back(stTemp);
        }
    }

    return vecStArea;
}



void AdapterArea::loadExcel(QVector<QVector<QString> > vecData)
{
    /*表头
     * 0:标签、1:Id、2:名称、3:父区域、
    */
    foreach(QVector<QString> vecDataRow , vecData){
        //一 将Excel表里数据初步转换为数据库结构体所需数据
        //1 检查
        if(StArea().m_vecColumnNames.size() != vecDataRow.size()){
            logErrorWin()<<"AdapterArea::loadExcell excel数据不符"<<flushWin;
            return;
        }

        StArea st;
        st.loadData(vecDataRow);
        if("" == st.getId() || "" == st.strId){//Excel录入容易将空行录进来
            continue;
        }else{
            this->addRow(st);
        }
    }
}

