#include <QDebug>

#include "TSettingArea.h"
#include "TButton.h"
#include "TCard.h"
#include "NetworkApp.h"

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

    /*设置条*/
    m_pWidgetButtonArea = new QWidget(this);
    m_pWidgetButtonArea->setFixedWidth(m_nButtonMainWidth);
    m_pWidgetButtonArea->setMinimumWidth(m_nButtonMainWidth);
    m_pWidgetButtonArea->setStyleSheet("QWidget{background-color:#bebebe;}");

    /*用户信息显示区*/
    m_pWidgetUserArea = new QWidget(this);
    m_pWidgetUserArea->setFixedSize(m_nWidgetMainWidth,210);
    m_pWidgetUserArea->setMinimumWidth(m_nWidgetMainWidth);
    m_pWidgetUserArea->setStyleSheet("QWidget{background-color:#cccccc;}");

    /*参数设置区*/
    m_pWidgetSettingArea = new QWidget(this);
    m_pWidgetSettingArea->setFixedWidth(m_nWidgetMainWidth);
    m_pWidgetSettingArea->setMinimumWidth(m_nWidgetMainWidth);
    m_pWidgetSettingArea->setStyleSheet("QWidget{background-color:#cccccc;}");


    /*初始化按钮条、用户区、参数设置区*/
    TSettingBtnBar *bar = new TSettingBtnBar(m_pWidgetButtonArea);
//    initButtonArea();
    initUserArea();
    initSettingArea();

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_pWidgetUserArea);
    vLayout->addWidget(m_pWidgetSettingArea);


    m_pHLayout = new QHBoxLayout;
    m_pHLayout->addWidget(m_pWidgetButtonArea);
    m_pHLayout->addLayout(vLayout);
    m_pHLayout->setSpacing(0);
    m_pHLayout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(m_pHLayout);
}

void TSettingArea::initButtonArea()
{

    m_pButtonMain = new QPushButton(m_pWidgetButtonArea);
    m_pButtonMain->setFixedSize(m_sIconSize);
    m_pButtonMain->setCheckable(true); // 设置允许选中
    m_pButtonMain->setStyleSheet(getImageStytle("you.png"));
    connect(m_pButtonMain,SIGNAL(clicked()),this,SLOT(slotButtonMain()));

    m_pButtonUser = new QPushButton(m_pWidgetButtonArea);
    m_pButtonUser->setFixedSize(m_sIconSize);
    m_pButtonUser->setStyleSheet(getImageStytle("icon-user.png"));

    m_pButtonMenu = new QPushButton(m_pWidgetButtonArea);
    m_pButtonMenu->setFixedSize(m_sIconSize);
    m_pButtonMenu->setStyleSheet(getImageStytle("caidan.png"));

//    m_pButtonUser = new QPushButton(m_pWidgetButtonArea);
//    m_pButtonMain->setFixedSize(m_sIconSize);
//    m_pButtonMain->setStyleSheet(getImageStytle("you.png"));

    m_pButtonRecvSetting = new QPushButton(m_pWidgetButtonArea);
    m_pButtonRecvSetting->setFixedSize(m_sIconSize);
    m_pButtonRecvSetting->setStyleSheet(getImageStytle("download.png"));

    m_pButtonCodec = new QPushButton(m_pWidgetButtonArea);
    m_pButtonCodec->setFixedSize(m_sIconSize);
    m_pButtonCodec->setStyleSheet(getImageStytle("hex.png"));

    m_pButtonSend = new QPushButton(m_pWidgetButtonArea);
    m_pButtonSend->setFixedSize(m_sIconSize);
    m_pButtonSend->setStyleSheet(getImageStytle("fasong.png"));

    m_pButtonConnect = new QPushButton(m_pWidgetButtonArea);
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

    m_pWidgetButtonArea->setLayout(layout);
}

void TSettingArea::initUserArea()
{

}

void TSettingArea::initSettingArea()
{

    NetworkApp *networkApp = new NetworkApp(m_pWidgetSettingArea);
    //networkApp->setFixedWidth(m_nWidgetMainWidth - 10);
}

void TSettingArea::slotButtonMain()
{
    qDebug()<<"设置按键";

    if(m_pWidgetSettingArea->isVisible()){
        m_pWidgetSettingArea->setVisible(false);
        this->setFixedWidth(m_nButtonMainWidth);
    }else{
        m_pWidgetSettingArea->setVisible(true);
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
