#ifndef TCARDITEM_H
#define TCARDITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>

#include "TButton.h"

class TCardItem : public QWidget
{
    Q_OBJECT
public:
    explicit TCardItem(QString text,QWidget *parent = 0);

    void setText(QString text){m_pLabelText->setText(text);}
signals:

public slots:

private:
    void paintEvent(QPaintEvent *event);
    void initUI();
    QHBoxLayout *m_pHLayout;
    QLabel *m_pLabelText;
    TButton *m_pButton;
};

#endif // TCARDITEM_H
