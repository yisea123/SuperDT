#ifndef CEXCELTOOL_H
#define CEXCELTOOL_H
#include "IExcelLoader.h"
class CExcelTool
{
public:
    static void loadExcel(QString strFolderName,IExcelLoader* pLoader);
private:
    static QString convertFromNumber(int number);
};

#endif // CEXCELTOOL_H
