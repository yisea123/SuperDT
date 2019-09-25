#include <QDebug>

#include "TSettingArea.h"

TSettingArea::TSettingArea(QWidget *parent) : QWidget(parent)
{
    initVal();
    initUI();
}

void TSettingArea::initVal()
{
    m_sIconSize = QSize(32,32);
    m_nWidgetMainWidth = 300;
    m_nButtonMainWidth = m_sIconSize.width() + 10;
}

void TSettingArea::initUI()
{
    /*初始化背景*/
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

    /*初始化所有的设置按钮*/
    initMainButton();

    m_pHLayout = new QHBoxLayout;
    m_pHLayout->addWidget(m_pWidgetSettingButton);
    m_pHLayout->addWidget(m_pWidgetSetting);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(m_pHLayout);
}

void TSettingArea::initMainButton()
{

    m_pButtonMain = new QPushButton(m_pWidgetSettingButton);
    m_pButtonMain->setFixedSize(m_sIconSize);
    m_pButtonMain->setCheckable(true); // 设置允许选中
    m_pButtonMain->setStyleSheet(getImageStytle("you.png"));
    connect(m_pButtonMain,SIGNAL(clicked()),this,SLOT(slotButtonMain()));

    m_pButtonUser = new QPushButton(m_pWidgetSettingButton);
    m_pButtonUser->setFixedSize(m_sIconSize);
    m_pButtonUser->setStyleSheet(getImageStytle("icon-user.png"));

    m_pButtonMenu = new QPushButton(m_pWidgetSettingButton);
    m_pButtonMenu->setFixedSize(m_sIconSize);
    m_pButtonMenu->setStyleSheet(getImageStytle("caidan.png"));

//    m_pButtonUser = new QPushButton(m_pWidgetSettingButton);
//    m_pButtonMain->setFixedSize(m_sIconSize);
//    m_pButtonMain->setStyleSheet(getImageStytle("you.png"));

    m_pButtonRecvSetting = new QPushButton(m_pWidgetSettingButton);
    m_pButtonRecvSetting->setFixedSize(m_sIconSize);
    m_pButtonRecvSetting->setStyleSheet(getImageStytle("download.png"));

    m_pButtonCodec = new QPushButton(m_pWidgetSettingButton);
    m_pButtonCodec->setFixedSize(m_sIconSize);
    m_pButtonCodec->setStyleSheet(getImageStytle("hex.png"));

    m_pButtonSend = new QPushButton(m_pWidgetSettingButton);
    m_pButtonSend->setFixedSize(m_sIconSize);
    m_pButtonSend->setStyleSheet(getImageStytle("fasong.png"));

    m_pButtonConnect = new QPushButton(m_pWidgetSettingButton);
    m_pButtonConnect->setFixedSize(m_sIconSize);
    m_pButtonConnect->setStyleSheet(getImageStytle("lianjie.png"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(5);
    layout->addWidget(m_pButtonMain);
    layout->addStretch(1);
    layout->addWidget(m_pButtonUser);
    layout->addWidget(m_pButtonMenu);
    layout->addWidget(m_pButtonRecvSetting);
    layout->addWidget(m_pButtonCodec);
    layout->addWidget(m_pButtonSend);
    layout->addWidget(m_pButtonConnect);
    layout->addStretch(1);
    layout->setContentsMargins((m_nButtonMainWidth-m_sIconSize.width())/2, 0, (m_nButtonMainWidth-m_sIconSize.width())/2, 0);

    m_pWidgetSettingButton->setLayout(layout);
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

    static bool bIsOpen = true;
    bIsOpen = !bIsOpen;

    /*设置按钮的图标*/
    if(bIsOpen){
        m_pButtonMain->setStyleSheet(getImageStytle("you.png"));
    }else{
        m_pButtonMain->setStyleSheet(getImageStytle("zuo.png"));
    }

}

QString TSettingArea::getImageStytle(QString strImage)
{
    return "QPushButton {border-image:url(:/image/icon/" + strImage + ")}";
}
