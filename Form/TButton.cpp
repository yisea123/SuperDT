#include "TButton.h"

TButton::TButton(QWidget *parent, bool status) : QPushButton(parent),m_bStatus(status)
{
    this->initUI();
}

void TButton::initUI()
{
    this->updateUI();
    this->setMinimumSize(32,32);
    connect(this,SIGNAL(clicked()),this,SLOT(slotClicked()));
}

void TButton::slotClicked()
{
    m_bStatus = !m_bStatus;
    this->updateUI();
    emit signalChanged(m_bStatus); //按钮状态改变信号
}

void TButton::updateUI()
{
    if(m_bStatus)
        this->setStyleSheet(getImageStytle("btn_c.png"));
    else
        this->setStyleSheet(getImageStytle("btn_n.png"));
}

QString TButton::getImageStytle(QString strImage)
{
    return "TButton {border-image:url(:/image/icon/" + strImage + ")}";
}
