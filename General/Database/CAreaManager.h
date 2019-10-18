#ifndef CAREAMANAGER_H
#define CAREAMANAGER_H

#include <QObject>
#include <QMap>

class CAreaManager : public QObject
{
    Q_OBJECT
public:
    explicit CAreaManager(QObject *parent = 0);

    static QString getName(QString strArea, int nLeve=0);
    static QString getSimpleName(QString strArea, int nLeve=0);
    static QMap<QString, QString> getChildArea(QString strArea);

signals:

public slots:
};

#endif // CAREAMANAGER_H
