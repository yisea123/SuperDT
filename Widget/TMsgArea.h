#ifndef TMSGAREA_H
#define TMSGAREA_H

#include <QWidget>
#include <QList>
#include <QSplitter>
#include <QHBoxLayout>

#include "TTextEditor.h"

class TMsgArea : public QWidget
{
    Q_OBJECT
public:
    explicit TMsgArea(QWidget *parent = 0);

private:
    void initVal();
    void initUI();
    QSplitter *creatSplitter(Qt::Orientation orientation,QWidget *parent);
    void creatTextEditor(QWidget *parent);
    void removeTextEditor(TTextEditor *rmTextEditor);
    void removeSplitter(QSplitter *rmSplitter);
    void removeLastTextEditor();
    void removeLastSplitter();
signals:

public slots:
    void slotVSplitScreen(); //垂直分屏
    void slotHSplitScreen(); //水平分屏
    void slotMergeScreen();  //并且
    void slotFocusChange(QWidget *old, QWidget *now);

private:
    QList<TTextEditor *> m_listTextEditor;
    QList<QSplitter *> m_plistSplitter;
    TTextEditor *m_pOldFocusTextEditor;
    TTextEditor *m_pNowFocusTextEditor;

    QWidget *m_pGrandgrandfather;
    QSplitter *m_pParentSplitter;
    QSplitter *m_pGrandpaSplitter;
    TTextEditor *m_pBrotherTextEditor;
    QSplitter *m_pUncleSplitter;
    QSplitter *m_pSplitterMain;
    TTextEditor *m_pTextEditorMain;
    QHBoxLayout *m_pHLayout;

};

#endif // TMSGAREA_H
