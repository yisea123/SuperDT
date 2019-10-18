#include "TCardItem.h"

TCardItem::TCardItem(QString text, EnmType type, QWidget *parent) : QWidget(parent)
{
    initUI(type);
    this->setText(text);
}

void TCardItem::addComBoxItem(QString strText)
{
    m_pComBox->addItem(strText);
}


void TCardItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TCardItem::initUI(EnmType type)
{
    this->setFixedHeight(40);

    switch (type) {
    case ENM_TBUTTON:
        creatTButtonItem();
        break;
    case ENM_TCOMBOX:
        creatTComBoxItem();
        break;
    default:
        break;
    }

}

void TCardItem::creatTButtonItem()
{
    m_pLabelText = new QLabel(this);
    m_pLabelText->setText("无标题");

    m_pButton = new TButton(this);

    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->addWidget(m_pLabelText);
    m_pHLayout->addStretch(1);
    m_pHLayout->addWidget(m_pButton);
    m_pHLayout->setContentsMargins(5,0,5,0);

    this->setLayout(m_pHLayout);
}

void TCardItem::creatTComBoxItem()
{
    m_pLabelText = new QLabel(this);
    m_pLabelText->setText("无标题");

    m_pComBox = new TComBox(this);
    //m_pComBox->setEditable(true);

    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->addWidget(m_pLabelText);
    m_pHLayout->addStretch(1);
    m_pHLayout->addWidget(m_pComBox);
    m_pHLayout->setContentsMargins(5,0,5,0);

    this->setLayout(m_pHLayout);
}
