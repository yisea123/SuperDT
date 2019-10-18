#include "CLogWinForWindow.h"
#include <QDebug>
#include <QPalette>

CLogWinForWindow::CLogWinForWindow()
{
    this->initUI();
}

CLogWinForWindow *CLogWinForWindow::getInstance()
{
    static CLogWinForWindow* m_pInstance = nullptr;
    if(m_pInstance == nullptr){
        if(m_pInstance == nullptr){
            m_pInstance = new CLogWinForWindow();
        }
    }
    return m_pInstance;
}

void CLogWinForWindow::appendLog(QString strLog)
{
    m_pTextEdit->append(strLog);
}

void CLogWinForWindow::initUI()
{
    this->resize(1200,200);
    this->setWindowTitle("LogWin");
    //this->setWindowOpacity(0.3);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);//窗口保持最前

    m_pTextEdit = new QTextEdit(this);
    m_pTextEdit->setStyleSheet("QTextEdit{color:rgba(54,179,226,1);}");

    m_pGLayout = new QGridLayout;
    m_pGLayout->addWidget(m_pTextEdit);

    this->setLayout(m_pGLayout);
    this->show();
}

void CLogWinForWindow::exit()
{

}
