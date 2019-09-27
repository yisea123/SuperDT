#ifndef TBUTTON_H
#define TBUTTON_H

#include <QPushButton>

class TButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TButton(QWidget *parent = 0,bool status = true);

    bool getStatus(){return m_bStatus;}
signals:
    void signalChanged(bool status);
public slots:
    void slotClicked();
private:
    void updateUI();
    void initUI();
    QString getImageStytle(QString strImage);
private:
    bool m_bStatus;

};

#endif // TBUTTON_H
