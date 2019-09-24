#include <QDebug>

#include "TSettingArea.h"

TSettingArea::TSettingArea(QWidget *parent) : QWidget(parent)
{
    initVal();
    initUI();
}



void TSettingArea::initVal()
{
    m_sIconSize = QSize(36,36);
    m_nWidgetMainWidth = 300;
    m_nButtonMainWidth = m_sIconSize.width() + 4;
}

void TSettingArea::initUI()
{
/*    m_pWidgetMain = new QWidget(this)*/;

    this->setMaximumWidth(m_nWidgetMainWidth + m_sIconSize.width());
    this->setMinimumWidth(m_nButtonMainWidth);
    this->setFixedWidth(m_nWidgetMainWidth + m_sIconSize.width());

    m_pWidgetSettingButton = new QWidget(this);
    m_pWidgetSettingButton->setFixedWidth(m_nButtonMainWidth);
    m_pWidgetSettingButton->setMinimumWidth(m_nButtonMainWidth);
    m_pWidgetSettingButton->setStyleSheet("QWidget{background-color:#bebebe;}");

    m_pWidgetSetting = new QWidget(this);
    m_pWidgetSetting->setFixedWidth(m_nWidgetMainWidth);
    m_pWidgetSetting->setMinimumWidth(m_nWidgetMainWidth);
    m_pWidgetSetting->setStyleSheet("QWidget{background-color:#cccccc;}");

    m_pButtonMain = new QPushButton(m_pWidgetSettingButton);
    m_pButtonMain->setFixedWidth(m_nButtonMainWidth);
    connect(m_pButtonMain,SIGNAL(clicked()),this,SLOT(slotButtonMain()));



    m_pHLayout = new QHBoxLayout;
    m_pHLayout->addWidget(m_pWidgetSettingButton);
    m_pHLayout->addWidget(m_pWidgetSetting);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(m_pHLayout);

//    QHBoxLayout *layout = new QHBoxLayout;
//    layout->addWidget(m_pWidgetMain);
//    this->setLayout(layout);
}

void TSettingArea::slotButtonMain()
{
    qDebug()<<"设置按键";

    if(m_pWidgetSetting->isVisible()){
        m_pWidgetSetting->setVisible(false);
        this->setFixedWidth(m_nButtonMainWidth);
    }else{
        m_pWidgetSetting->setVisible(true);
        this->setFixedWidth(m_nWidgetMainWidth + m_sIconSize.width());
    }
}
