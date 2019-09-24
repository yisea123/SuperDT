#ifndef TTEXTEDIT_H
#define TTEXTEDIT_H


#include <QPlainTextEdit>
#include <QObject>
#include <QSplitter>
#include <QStack>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;
class TTextEditor: public QPlainTextEdit
{
    Q_OBJECT
public:
   TTextEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
private slots:
    void slotVSplitScreen(); //垂直分屏
    void slotHSplitScreen(); //水平分屏
    void slotMergeScreen();  //并且
private:
    QWidget *lineNumberArea;

    QStack<QSplitter *> m_stackSplitter;
    QStack<TTextEditor *> m_stackTextEditor;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TTextEditor *editor) : QWidget(editor) {
        TTextEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(TTextEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        TTextEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TTextEditor *TTextEditor;
};

#endif // TTEXTEDIT_H
