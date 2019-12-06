#include "TLockButton.h"
#include <QDebug>

TLockButton::TLockButton(QString strId,QString strImgUrlN,QString strImgUrlC,QWidget *parent )
    :QPushButton(parent)
{
    m_strId = strId;
    m_strImgUrlN = strImgUrlN;
    m_strImgUrlC = strImgUrlC;
    m_strTextN = "#ffffff";
    m_strTextC = "#ffffff";
    m_strTextColor = "#ffffff";
    connect(this,SIGNAL(clicked(bool)),this,SLOT(slotClicked(bool)));
    refreshButton();
}

void TLockButton::setText(QString strTextN, QString strTextC)
{
    m_strTextN = strTextN;
    m_strTextC = (strTextC == "") ? strTextN : strTextC;
    refreshButton();
}

void TLockButton::setChecked(bool bState)
{
    if(bState)
        this->setText(m_strTextC);
    else
        this->setText(m_strTextN);
}

void TLockButton::refreshButton()
{
    this->setStyleSheet("QPushButton{border-image:url("+ m_strImgUrlN +");color:"+ m_strTextColor +";}"
                        "QPushButton:checked{border-image:url("+ m_strImgUrlC +");color:"+ m_strTextColor +";}"
                        "QPushButton:hover{border-image:url("+ m_strImgUrlC +");color:"+ m_strTextColor +";}"
                        );
    qDebug()<<"QPushButton:checked{border-image:url("+ m_strImgUrlC +");color:"+ m_strTextColor +";}";
}

void TLockButton::slotClicked(bool bState)
{
    Q_UNUSED(bState)

    emit sigClicked(m_strId);
}
