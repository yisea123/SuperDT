#include "StatusBar.h"

#include <QHBoxLayout>

StatusBar::StatusBar(QWidget *parent) : QWidget(parent)
{
    initVal();
    initUI();
}

void StatusBar::initVal()
{
    m_sIconSize = QSize(20,20);
}

void StatusBar::initUI()
{
    this->setFixedHeight(22);

    m_pWidget = new QWidget(this);
    m_pWidget->setStyleSheet("QWidget{background-color:#bebebe;}");

    /*水平分屏*/
    m_pHSplitScreenButton = new QPushButton(m_pWidget);
    m_pHSplitScreenButton->setFixedSize(m_sIconSize);
    m_pHSplitScreenButton->setStyleSheet(getImageStytle("hfenping.png"));
    connect(m_pHSplitScreenButton,SIGNAL(clicked()),this,SIGNAL(signalHSplitScreen()));

    /*垂直分屏*/
    m_pVSplitScreenButton = new QPushButton(m_pWidget);
    m_pVSplitScreenButton->setFixedSize(m_sIconSize);
    m_pVSplitScreenButton->setStyleSheet(getImageStytle("vfenping.png"));
    connect(m_pVSplitScreenButton,SIGNAL(clicked()),this,SIGNAL(signalVSplitScreen()));

    /*合并屏幕*/
    m_pMergeScreen = new QPushButton(m_pWidget);
    m_pMergeScreen->setFixedSize(m_sIconSize);
    m_pMergeScreen->setStyleSheet(getImageStytle("hebing.png"));
    connect(m_pMergeScreen,SIGNAL(clicked()),this,SIGNAL(signalMergeScreen()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addStretch(1);
    layout->addWidget(m_pHSplitScreenButton);
    layout->addWidget(m_pVSplitScreenButton);
    layout->addWidget(m_pMergeScreen);
    layout->setContentsMargins(0, 0, 5, 0);

    m_pWidget->setLayout(layout);

    QHBoxLayout *bgLayout = new QHBoxLayout(this);
    bgLayout->addWidget(m_pWidget);
    bgLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(bgLayout);
}

QString StatusBar::getImageStytle(QString strImage)
{
    return "QPushButton {border-image:url(:/image/icon/" + strImage + ")}";
}
