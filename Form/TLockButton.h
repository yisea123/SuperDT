#ifndef TLOCKBUTTON_H
#define TLOCKBUTTON_H

#include <QPushButton>

class TLockButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TLockButton(QString strId,QString strImgUrlN,QString strImgUrlC,QWidget *parent = nullptr);
    void setText(QString strTextN,QString strTextC = "");
    void setTextColor(QString strColor){m_strTextColor = strColor;}
    void setTextSize(int nSize){m_nTextSize = nSize;}
    void setChecked(bool bState);
    QString getId(){return m_strId;}
signals:
    void sigClicked(QString strId);
private:
    void refreshButton();
private slots:
    void slotClicked(bool bState);
private:
    QString m_strId;
    QString m_strImgUrlN; //默认图片
    QString m_strImgUrlC; //Checked图片
    QString m_strTextN;
    QString m_strTextC;
    QString m_strTextColor;
    int m_nTextSize;

};

#endif // TLOCKBUTTON_H
