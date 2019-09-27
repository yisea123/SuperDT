#ifndef TCARD_H
#define TCARD_H

#include <QWidget>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QList>

class TCard : public QWidget
{
    Q_OBJECT
public:
    explicit TCard(QWidget *parent = 0);

    void addWidget(QWidget *widget);
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    QVBoxLayout *m_pVLayout;
    QList<QWidget *> m_listWidget;
    void initUI();
};

#endif // TCARD_H
