#ifndef IEXCELLOADER_H
#define IEXCELLOADER_H

#include <QVector>
#include <QString>
class IExcelLoader
{
public:
    virtual void loadExcel(QVector<QVector<QString>> vecData) = 0;
};

#endif // IEXCELLOADER_H
