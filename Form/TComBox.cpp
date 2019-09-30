#include "TComBox.h"

TComBox::TComBox(QWidget *parent)
    : QComboBox(parent)
{
    initUI();
}

void TComBox::initUI()
{
    this->setFixedSize(150,30);
    this->setStyleSheet("TComBox{background:#FFFFFF;border-radius:5px;}"
                        "QComboBox::drop-down{"
                            "background-color:transparent;"
                            "width:20px;"
                            "top:4px;"
                            "height:20px;"
                            "right:4px;"
                        "}"
                        "QComboBox::down-arrow {"
                            "image:url(:/image/icon/combox-drop.png);"
                        "}");
}
