#include "CExcelTool.h"
#include "clog.h"
#include "CConfiger.h"
#include <QFile>
#include <QDir>

#ifdef Q_OS_WIN
#include <QAxObject>
void CExcelTool::loadExcel(QString strFolderName, IExcelLoader *pLoader)
{
    logWin()<<"CExcelTool::loadExcel 开始处理文件"<<strFolderName<<flushWin;
    QString strPath = CConfiger::getApplicationUrl() + "ExcelData/" + strFolderName;
    QFile file(strPath);
    if(!file.exists()){
        logErrorWin() << "CExcelTool::loadExcel 路径错误，或文件不存在,路径为"<<strPath<<flushWin;
        return;
    }else if(!strPath.right(4).contains("xls"))
    {
        logErrorWin() << "CExcelTool::loadExcel 文件类型错误，只接受xls文件或xlsx文件"<<flushWin;
        return;
    }

    QAxObject *excel = new QAxObject("Excel.Application");//excel应用程序
    excel->dynamicCall("SetVisible(bool)", false); //true 表示操作文件时可见，false表示为不可见
    QAxObject *workbooks = excel->querySubObject("WorkBooks");//所有excel文件
    QAxObject *workbook = workbooks->querySubObject("Open(QString&)", strPath);//按照路径获取文件
    QAxObject * worksheets = workbook->querySubObject("WorkSheets");//获取文件的所有sheet页
    QAxObject * worksheet = worksheets->querySubObject("Item(int)", 1);//获取文件的第一个sheet页
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");//有数据的矩形区域

    QAxObject * rows = usedrange->querySubObject("Rows");//获取行数
    int nRows = rows->property("Count").toInt();
    logWin()<<"CExcelTool::loadExcel 文件数据行数为"<<nRows-1<<"，不含表头"<<flushWin;
    if(nRows <= 1){
        logWarnningWin()<<"CExcelTool::loadExcel 无数据，跳过该文件"<<flushWin;
        return;
    }
    QAxObject * columns = usedrange->querySubObject("Columns");//获取列数
    int nColumns = columns->property("Count").toInt();
    logWin()<<"CExcelTool::loadExcel 文件数据列数为"<<nColumns<<flushWin;

    QVector<QVector<QString>> vecDatas;//获取所有数据
    for(int i = 2;i <= nRows;i++){//第一行默认为表头，从第二行读起
        QVector<QString> vecDataRow;
        for(int j = 1;j <= nColumns;j++){
            //QString strGirdName = convertFromNumber(j)+QString::number(i);//如A2,F6
            QAxObject *cell = worksheet->querySubObject("Cells(int,int)",i,j);
            QString strValue = cell->property("Value2").toString();
            vecDataRow.push_back(strValue);
        }
        vecDatas.push_back(vecDataRow);
    }
    //关闭文件
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
    if (excel)
    {
        delete excel;
        excel = NULL;
    }

    pLoader->loadExcel(vecDatas);//输送数据
    logImpInfoWin()<<"CExcelTool::loadExcel 文件处理结束，"<<strFolderName<<flushWin;
}
#else
void CExcelTool::loadExcel(QString strFolderName, IExcelLoader *pLoader)
{
    Q_UNUSED(strFolderName);
    Q_UNUSED(pLoader);
    logErrorWin()<<"CExcelTool::loadExcel 非Win平台不处理Excel数据加载逻辑"<<flushWin;
}
#endif

QString CExcelTool::convertFromNumber(int number)
{
    QString resultStr = "";
    while(number > 0)
    {
        int k = number % 26;
        if(k == 0)
            k = 26;
        resultStr.push_front(QChar(k + 64));
        number = (number - k) / 26;
    }
    return resultStr;
}
