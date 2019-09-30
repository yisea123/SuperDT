#ifndef TCARDITEM_H
#define TCARDITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

#include "TButton.h"
#include "TComBox.h"

enum EnmType{
    ENM_TBUTTON = 0,
    ENM_TCOMBOX,
};


class TCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TCardItem(QString text,EnmType type,QWidget *parent = 0);

    void setText(QString text){m_pLabelText->setText(text);}
    void addComBoxItem(QString strText);
signals:

public slots:

private:
    void paintEvent(QPaintEvent *event);
    void initUI(EnmType type);
    void creatTButtonItem();
    void creatTComBoxItem();

    QHBoxLayout *m_pHLayout;
    QLabel *m_pLabelText;
    TButton *m_pButton;
    TComBox *m_pComBox;
};

#endif // TCARDITEM_H
