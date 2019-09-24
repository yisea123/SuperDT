#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QPushButton>

#include "TWindowLayoutDefine.h"

class StatusBar : public QWidget,public TWindowLayoutDefine
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);

    void initUI();
    void initVal();
signals:
    void signalVSplitScreen();
    void signalHSplitScreen();
    void signalMergeScreen();
private:
    QString getImageStytle(QString strImage);

    QWidget *m_pWidget;
    QPushButton *m_pHSplitScreenButton;//水平分屏
    QPushButton *m_pVSplitScreenButton;//垂直分屏
    QPushButton *m_pMergeScreen;//合并屏幕
    QSize m_sIconSize;
public slots:
};

#endif // STATUSBAR_H
