#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>

#include "TWindowLayoutDefine.h"

class TitleBar : public QWidget,public TWindowLayoutDefine
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

public:
    void setWindowTitle(QString strTitle);
private:
    void initVal();
    void initUI();

    QString getImageStytle(QString strImage);
    QWidget *m_pParentWindow;
    QPushButton *m_pExitButton;
    QPushButton *m_pMaxButton;
    QPushButton *m_pMinButton;
    QLabel *m_pLabelTitle;
    QLabel *m_pLabelIcon;
    QString m_strIconPath;

    QPoint m_pointWindowPos;
    QPoint m_pointMousePos;
    QPoint m_pointDPos;
    bool m_bLeftButtonPressed;
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private slots:
    void slotExit();
    void slotMax();
    void slotMin();
};

#endif // TITLEBAR_H
