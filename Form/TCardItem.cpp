#include "TCardItem.h"

TCardItem::TCardItem(QString text, QWidget *parent) : QWidget(parent)
{
    initUI();
    this->setText(text);
}


void TCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TCardItem::initUI()
{
    this->setStyleSheet("TCardItem {background-color:rgb(168,168,168);}");
    m_pLabelText = new QLabel;
    m_pLabelText->setText("无标题");
    m_pLabelText->setStyleSheet("{font-size:12;font-color:#FFFFFF;}");

    m_pButton = new TButton;

    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->addWidget(m_pLabelText);
    m_pHLayout->addStretch(1);
    m_pHLayout->addWidget(m_pButton);
    m_pHLayout->setContentsMargins(5,0,5,0);

    this->setLayout(m_pHLayout);
}
