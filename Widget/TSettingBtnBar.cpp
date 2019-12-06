#include "TSettingBtnBar.h"
#include "TLockButton.h"
#include <QVBoxLayout>
#include <QDebug>

TSettingBtnBar::TSettingBtnBar(QWidget *parent)
    :QWidget(parent)
{
    m_sIconSize = QSize(24,24);
    m_strImgUrl = "image/setting";
    init();
}

void TSettingBtnBar::init()
{

    createView();
}

void TSettingBtnBar::createView()
{
    this->setFixedWidth(60);

    QStringList listUrl;
    listUrl <<"you"<<"icon-user"<<"caidan"<<"download"<<"hex"<<"fasong"<<"lianjie";

    foreach(QString strUrl,listUrl){
        TLockButton *pSettingBtn = new TLockButton(strUrl,m_strImgUrl + strUrl + "_c.png",m_strImgUrl + strUrl + "_n.png",this);
        pSettingBtn->setFixedSize(m_sIconSize);
        connect(pSettingBtn,SIGNAL(sigClicked(QString)),this,SLOT(slotBtnClicked(QString)));
        m_vecBtn.push_back(pSettingBtn);
    }


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(5);
    layout->addWidget(m_vecBtn.at(0));
    layout->addStretch(1);
    for(int i = 1; i < m_vecBtn.count(); i++){
        layout->addWidget(m_vecBtn.at(i));
    }
    layout->addStretch(1);
    //layout->setContentsMargins((m_nButtonMainWidth-m_sIconSize.width())/2, 0, (m_nButtonMainWidth-m_sIconSize.width())/2, 0);

    this->setLayout(layout);
}

void TSettingBtnBar::slotBtnClicked(QString strId)
{
    qDebug()<<"btn Id:"<<strId;
}
