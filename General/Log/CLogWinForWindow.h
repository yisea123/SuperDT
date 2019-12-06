#ifndef CLOGWINFORWINDOW_H
#define CLOGWINFORWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>

class CLogWinForWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CLogWinForWindow();

    static CLogWinForWindow *getInstance();
    void appendLog(QString strLog);
private:
    void initUI();
private:
    QTextEdit *m_pTextEdit;
    QGridLayout *m_pGLayout;
};

#endif // CLOGWINFORWINDOW_H
