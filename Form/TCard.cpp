#include "TCard.h"

TCard::TCard(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void TCard::addWidget(QWidget *widget)
{
    /*添加空白分隔*/
    if(m_listWidget.count() > 1)
        m_pVLayout->addSpacing(2);

    m_pVLayout->addWidget(widget);
    m_listWidget.append(widget);
}

/******
 * Note:从 QWidget子类化  需要提供paintEvent
 * 详见 Qt Style Sheets Reference
 ******/
void TCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TCard::initUI()
{
    this->setStyleSheet("TCard {background-color:rgbs(204,204,204,100);border-radius:10;}");
    m_pVLayout = new QVBoxLayout(this);
    m_pVLayout->setContentsMargins(0,0,0,0);
}
