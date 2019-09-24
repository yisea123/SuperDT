#ifndef TSETTINGAREA_H
#define TSETTINGAREA_H

#include <QWidget>
#include <QPushbutton>
#include <QHBoxLayout>

class TSettingArea : public QWidget
{
    Q_OBJECT
public:
    explicit TSettingArea(QWidget *parent = 0);


signals:

public slots:
    void slotButtonMain();
private:
    void initVal();
    void initUI();

private:
    QPushButton *m_pButtonMain;
    QWidget *m_pWidgetSettingButton;
    QWidget *m_pWidgetSetting;
    QWidget *m_pWidgetMain;
    QSize m_sIconSize;
    int m_nWidgetMainWidth;
    int m_nButtonMainWidth;
    QHBoxLayout *m_pHLayout;
};

#endif // TSETTINGAREA_H
