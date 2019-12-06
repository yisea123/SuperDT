#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSizeGrip>

#include "TitleBar.h"
#include "StatusBar.h"
#include "TMsgArea.h"
#include "TSettingArea.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void initUI();

private:
    TitleBar *m_pTitleBar;
    StatusBar *m_pStatusBar;
    TMsgArea *m_pMsgArea;
    TSettingArea *m_pSettingArea;
private slots:
    void slotLog();
};

#endif // MAINWIDGET_H
