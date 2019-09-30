#include "TCard.h"

TCard::TCard(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void TCard::addWidget(QWidget *widget)
{
    /*添加空白分隔*/
    if(m_listWidget.count() > 0)
        m_pVLayout->addSpacing(1);

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
    m_pVLayout = new QVBoxLayout(this);
    //m_pVLayout->setContentsMargins(5,0,5,0);
}

/******
 * Note:卡片添加完  要手动调用  设置每条Item的样式
 ******/
void TCard::processStyle()
{
    int itemCount = m_listWidget.size();

    if(0 == itemCount)
        return ;

    /*只有一个  设置四角圆角*/
    if(1 == itemCount)
    {
        m_listWidget.at(0)->setStyleSheet(getStyle(ENM_ONLY_ONE));
    }

    /*超过一个  设置第一个  和 最后一个圆角*/
    if(2 <= itemCount)
    {
        for(int i = 0; i < itemCount; i++){
            if(0 == i)
                m_listWidget.at(i)->setStyleSheet(getStyle(ENM_FIRST));
            else if(i == (itemCount - 1))
                m_listWidget.at(i)->setStyleSheet(getStyle(ENM_END));
            else
                m_listWidget.at(i)->setStyleSheet(getStyle(ENM_NORMAL));
        }
    }

}

QString TCard::getStyle(EnmStyle num)
{
    QString strStyle;

    switch (num) {
    case ENM_FIRST:
        strStyle = "background-color:rgb(185,185,185);border-top-left-radius:10px;"\
                    "border-top-right-radius:10px;color:#FFFFFF;";
        break;
    case ENM_NORMAL:
        strStyle = "background-color:rgb(185,185,185);border-radius:0px;color:#FFFFFF;";
        break;
    case ENM_END:
        strStyle = "background-color:rgb(185,185,185);border-bottom-left-radius:10px;"\
                    "border-bottom-right-radius:10px;color:#FFFFFF;";
        break;
    case ENM_ONLY_ONE:

    default:
        break;
    }

    return strStyle;
}
