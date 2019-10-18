#ifndef NETWORKAPP_H
#define NETWORKAPP_H

#include <QWidget>

class NetworkApp : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkApp(QWidget *parent = 0);

    void initUI();
signals:

public slots:
};

#endif // NETWORKAPP_H
