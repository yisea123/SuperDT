#ifndef CTABLEMANAGER_H
#define CTABLEMANAGER_H

#include <QObject>

#define ID_ALL_FOR_TABLE "id_all_for_table_from_CTableManager_of_VariwinPlatform_V1"

class CTableManager : public QObject
{
    Q_OBJECT
private:
    explicit CTableManager(QObject *parent = 0);
public:
    static CTableManager* getInstance();
    void execSqlForSynTable(QString strSql,QString strTableName);
    void execSqlForSynRow(QString strSql,QString strTableName,QString strId);
signals:
    void sigSynData(QString strSql,QString strTableName,QString strId);
    void sigRecreateTable(QString strTableName);
};

#endif // CTABLEMANAGER_H
