#ifndef TSETTINGBTNBAR_H
#define TSETTINGBTNBAR_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QStringList>

class TSettingBtnBar:public QWidget
{
    Q_OBJECT
public:
    explicit TSettingBtnBar(QWidget *parent = 0);
private:
    void init();
    void createView();
private slots:
    void slotBtnClicked(QString strId);
private:
    QVector<QPushButton *> m_vecBtn;
    QSize m_sIconSize;
    QString m_strImgUrl;
};

#endif // TSETTINGBTNBAR_H
