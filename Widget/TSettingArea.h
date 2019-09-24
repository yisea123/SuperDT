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
    void initMainButton();
private:
    QString getImageStytle(QString strImage);
    QWidget *m_pWidgetSettingButton;
    QWidget *m_pWidgetSetting;
    QWidget *m_pWidgetMain;
    QSize m_sIconSize;
    int m_nWidgetMainWidth;
    int m_nButtonMainWidth;
    QHBoxLayout *m_pHLayout;
    QPushButton *m_pButtonMain;
    QPushButton *m_pButtonUser;
    QPushButton *m_pButtonMenu;
    QPushButton *m_pButtonRecvSetting;
    QPushButton *m_pButtonCodec;
    QPushButton *m_pButtonSend;
    QPushButton *m_pButtonConnect;
};

#endif // TSETTINGAREA_H
