#include <QVBoxLayout>

#include "NetworkApp.h"
#include "TCardItem.h"
#include "TCard.h"

NetworkApp::NetworkApp(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void NetworkApp::initUI()
{
    TCardItem *cardItem1 = new TCardItem("接收显示",ENM_TBUTTON);
    TCardItem *cardItem2 = new TCardItem("十六进制显示",ENM_TBUTTON);
    TCardItem *cardItem3 = new TCardItem("保存到文件",ENM_TCOMBOX);
    cardItem3->addComBoxItem("192.168.1.1");
    cardItem3->addComBoxItem("192.168.1.2");
    cardItem3->addComBoxItem("192.168.1.3");

    TCard *card1 = new TCard(this);
    card1->addWidget(cardItem1);
    card1->addWidget(cardItem2);
    card1->addWidget(cardItem3);
    card1->processStyle();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addSpacing(1);
    layout->addWidget(card1);
    layout->addStretch(1);
    layout->setContentsMargins(2,0,2,0);
    this->setLayout(layout);
}
