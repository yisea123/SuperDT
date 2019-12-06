#include "MainWidget.h"
#include "TWindowLayoutDefine.h"
#include "clog.h"

#include <QVBoxLayout>
#include <QTimer>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

MainWidget::~MainWidget()
{

}

void MainWidget::initUI()
{
//    QTimer *timerLog = new QTimer(this);
//    connect(timerLog,SIGNAL(timeout()),this,SLOT(slotLog()));
//    timerLog->start(2000);

//    this->setWindowTitle("QQ ");
//    this->setWindowIcon(QIcon(":/images/po.jpg"));
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);    // 设置尺寸属性
    this->setMinimumSize(1024,720);
    this->setMouseTracking(true); //设置鼠标追踪  只要鼠标在本窗体内  就会触发MouseMoveEvent()


    m_pTitleBar = new TitleBar(this);
    m_pTitleBar->setWindowTitle("SuperDT");

    m_pStatusBar = new StatusBar(this);

    m_pMsgArea = new TMsgArea(this);
    connect(m_pStatusBar,SIGNAL(signalVSplitScreen()),m_pMsgArea,SLOT(slotVSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalHSplitScreen()),m_pMsgArea,SLOT(slotHSplitScreen()));
    connect(m_pStatusBar,SIGNAL(signalMergeScreen()),m_pMsgArea,SLOT(slotMergeScreen()));

    m_pSettingArea = new TSettingArea(this);

    QSizeGrip *sizeGrip = new QSizeGrip(this);//拖拽

    /*Msg和Setting*/
    QHBoxLayout *layoutMsgAndSetting = new QHBoxLayout;
    layoutMsgAndSetting->addWidget(m_pMsgArea);
    layoutMsgAndSetting->addWidget(m_pSettingArea);
    layoutMsgAndSetting->setSpacing(0); //设置间距
    layoutMsgAndSetting->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_pTitleBar);
    layout->addWidget(m_pStatusBar);
    layout->addLayout(layoutMsgAndSetting);
    layout->addWidget(sizeGrip);
    layout->setSpacing(0); //设置间距
    layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(layout);
}

void MainWidget::slotLog()
{
    logFatalWin()<< "ssssssssssssssss" <<flushWin;
    logErrorWin()<< "ssssssssssssssss" <<flushWin;
    logWarnningWin()<< "ssssssssssssssss" << flushWin;
    logImpInfoWin()<< "ssssssssssssssss" << flushWin;
    logDebugWin()<< "ssssssssssssssss" << flushWin;
}

