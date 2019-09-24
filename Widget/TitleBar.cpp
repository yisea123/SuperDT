/************************************
            开发日志
2019/09/17
    实现功能：最小化、最大化、关闭窗口、左键点击移动窗口位置、双击最大化或默认大小

************************************/

#include "TitleBar.h"
#include <QDebug>
#include <QHBoxLayout>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    initVal();
    initUI();
}

void TitleBar::setWindowTitle(QString strTitle)
{
    m_pLabelTitle->setAlignment(Qt::AlignCenter);
    m_pLabelTitle->setText(strTitle);
}

void TitleBar::initVal()
{
    m_strIconPath = "/image/icon/";
    m_pParentWindow = this->window(); //获取本部件所处的窗口
}

void TitleBar::initUI()
{
    this->setFixedHeight(32);

    m_pLabelIcon = new QLabel(this);
    m_pLabelIcon->setFixedSize(24,24);  //设置最大宽高和最小宽高固定  不再拉伸
    m_pLabelIcon->setScaledContents(true); //允许图片按比例缩小填充Label

    m_pLabelTitle = new QLabel(this);
    m_pLabelTitle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinButton = new QPushButton(this);
    m_pMinButton->setFixedSize(24,24);
    m_pMinButton->setStyleSheet(getImageStytle("min-gray.png"));
    connect(m_pMinButton,SIGNAL(clicked()),this,SLOT(slotMin()));

    m_pMaxButton = new QPushButton(this);
    m_pMaxButton->setFixedSize(24,24);
    m_pMaxButton->setStyleSheet(getImageStytle("max-gray.png"));
    connect(m_pMaxButton,SIGNAL(clicked()),this,SLOT(slotMax()));

    m_pExitButton = new QPushButton(this);
    m_pExitButton->setFixedSize(24,24);
    m_pExitButton->setStyleSheet(getImageStytle("exit-gray.png"));
    connect(m_pExitButton,SIGNAL(clicked()),this,SLOT(slotExit()));


    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_pLabelIcon);
    layout->addStretch(1);  //中间添加一个拉伸量 空白区
    layout->addWidget(m_pLabelTitle);
    layout->addStretch(1);
    layout->addWidget(m_pMinButton);
    layout->addWidget(m_pMaxButton);
    layout->addWidget(m_pExitButton);
    layout->setContentsMargins(0, 0, 5, 0);//设置左、上、右、下 M argins

    setLayout(layout);
}

QString TitleBar::getImageStytle(QString strImage)
{
    return "QPushButton {border-image:url(:/image/icon/" + strImage + ")}";
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLeftButtonPressed)
    {
        m_pParentWindow->move(event->globalPos() - m_pointDPos);//鼠标松开的全局位置 - 鼠标位置与窗口位置差
    }
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = true;//记录按键按下

        m_pointWindowPos = m_pParentWindow->pos();
        m_pointMousePos = event->globalPos();                   // 获得鼠标在屏幕中的全局位置
        m_pointDPos = m_pointMousePos - m_pointWindowPos;       // 鼠标位置与窗口位置差
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)  // 鼠标左键释放
    {
        m_bLeftButtonPressed = false;       // 记录鼠标状态
    }
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    slotMax();
}
void TitleBar::slotExit()
{
    m_pParentWindow->close();
}

void TitleBar::slotMax()
{
    if(m_pParentWindow->isMaximized())
        m_pParentWindow->showNormal();
    else
        m_pParentWindow->showMaximized();
}

void TitleBar::slotMin()
{
    m_pParentWindow->showMinimized();
}


