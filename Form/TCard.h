#ifndef TCARD_H
#define TCARD_H

#include <QWidget>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QList>

enum EnmStyle{
    ENM_FIRST = 0,
    ENM_NORMAL,
    ENM_END,
    ENM_ONLY_ONE,
};

class TCard : public QWidget
{
    Q_OBJECT
public:
    explicit TCard(QWidget *parent = 0);

    void addWidget(QWidget *widget);
    void processStyle();
protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
private:
    void initUI();
    QString getStyle(EnmStyle num);
    QVBoxLayout *m_pVLayout;
    QList<QWidget *> m_listWidget;

};

#endif // TCARD_H
