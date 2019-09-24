/*
 * 功能说明
 * 1.初始化好的主界面里有一个分割器和一个编辑器垫底
 * 2.提供三个槽函数,分别是对选中编辑器进行水平分割、垂直分割、删除分割。
 *
 * 实现思路
 * 水平分割
 * 1.获取当前选中的编辑器
 * 2.设置选中编辑器所在的分割器为水平分割器(原本就是水平分割器不用操作)
 * 3.new两个分割器放在 编辑器所在的分割器
 * 4.将编辑器放入其中的一个分割器  再new出一个编辑器放入另一个分割器
 * 垂直分割如上
 *
 * 删除选中的编辑器
 *
 * 大于两个编辑器（以下称呼均是相对选中编辑器而言）
 * 1.找到叔叔分割器 移到祖父上
 * 2.删除 所选中的编辑器自己、父亲分割器、爷爷分割器。
 *
 * 剩余两个编辑器
 * 1.找到兄弟编辑器  移到爷爷分割器上
 * 2.删除自己、父亲分割器、叔叔分割器
 */

#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QThread>

#include "TMsgArea.h"

TMsgArea::TMsgArea(QWidget *parent)
    : QWidget(parent)
{
    initVal();
    initUI();
}

void TMsgArea::initVal()
{
    m_pOldFocusTextEditor = nullptr;
    m_pNowFocusTextEditor = nullptr;
    m_pParentSplitter = nullptr;
    m_pGrandpaSplitter = nullptr;
    m_pBrotherTextEditor = nullptr;
    m_pUncleSplitter = nullptr;
    m_pGrandgrandfather = nullptr;
}

void TMsgArea::initUI()
{
    this->setObjectName("WidgetMain");

    /*初始化一个主分割器 和 一个主文本编辑器*/
    m_pSplitterMain = new QSplitter(Qt::Vertical,this);
    m_pSplitterMain->setObjectName("m_pSplitterMain");
    m_plistSplitter.append(m_pSplitterMain);

    m_pTextEditorMain = new TTextEditor(m_pSplitterMain);
    m_pTextEditorMain->setObjectName("m_pTextEditorMain");
    m_listTextEditor.append(m_pTextEditorMain);

    m_pNowFocusTextEditor = m_pTextEditorMain; //初始化选中的编辑器为主编辑器

    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->addWidget(m_pSplitterMain);
    this->setLayout(m_pHLayout);

    /*绑定 焦点部件改变 的信号  获取当前鼠标所在的Widget 保存鼠标最后选中的编辑器用于分屏等操作*/
    connect(qApp,SIGNAL(focusChanged(QWidget *, QWidget *)),this,SLOT(slotFocusChange(QWidget *, QWidget *)));
}

QSplitter *TMsgArea::creatSplitter(Qt::Orientation orientation, QWidget *parent)
{
    QSplitter *splitter = new QSplitter(orientation,parent);
    splitter->setObjectName("splitter" + QString::number(m_plistSplitter.size()));
    m_plistSplitter.append(splitter);

    return splitter;
}

void TMsgArea::creatTextEditor(QWidget *parent)
{
    TTextEditor *textEditor = new TTextEditor(parent);
    textEditor->setObjectName("textEditor" + QString::number(m_listTextEditor.size()));
    m_listTextEditor.append(textEditor);
}

void TMsgArea::removeTextEditor(TTextEditor *rmTextEditor)
{
    if((nullptr == rmTextEditor) || (0 == m_listTextEditor.count()))
        return ;

    /*遍历链表  删除项*/
    TTextEditor *tmpTextEditor;
    foreach(tmpTextEditor,m_listTextEditor){
        if(tmpTextEditor == rmTextEditor)
        {
            m_listTextEditor.removeOne(rmTextEditor);
            delete rmTextEditor;
            qDebug()<<"从链表里删除一个Editor!";
            qDebug()<<"还有：" <<m_listTextEditor.count()<<" 个textEditor";

            foreach(tmpTextEditor,m_listTextEditor){
                qDebug()<<"还存在的textEditor: "<< tmpTextEditor->objectName();
            }

            return;
        }
    }


}

void TMsgArea::removeSplitter(QSplitter *rmSplitter)
{
    if((nullptr == rmSplitter) || (0 == m_plistSplitter.count()))
        return ;

    /*遍历链表  删除项*/
    QSplitter *tmpSplitter;
    foreach(tmpSplitter,m_plistSplitter){
        if(tmpSplitter == rmSplitter)
        {
            m_plistSplitter.removeOne(rmSplitter);
            delete rmSplitter;
            qDebug()<<"从链表里删除一个Splitter!";
            qDebug()<<"还有：" << m_plistSplitter.count() <<" 个Splitter";

            /*调试*/
            foreach(tmpSplitter,m_plistSplitter){
                qDebug()<<"还存在的Splitter: "<< tmpSplitter->objectName();
            }

            return;
        }
    }

}

void TMsgArea::removeLastTextEditor()
{
    TTextEditor *tmpTextEditor;
    tmpTextEditor = m_listTextEditor.last();
    m_listTextEditor.removeLast(); //删除指针
    delete tmpTextEditor;          //释放资源
    tmpTextEditor = nullptr;
}

void TMsgArea::removeLastSplitter()
{
    QSplitter *tmpSplitter;
    tmpSplitter = m_plistSplitter.last();
    m_plistSplitter.removeLast();
    delete tmpSplitter;
    tmpSplitter = nullptr;
}

void TMsgArea::slotVSplitScreen()
{
    // Qt::Vertical   垂直
    // Qt::Horizontal 水平
    qDebug("垂直分屏");
    if(nullptr == m_pNowFocusTextEditor)
        return ;

    m_pParentSplitter = qobject_cast<QSplitter *>(m_pNowFocusTextEditor->parentWidget());
    if(nullptr == m_pParentSplitter)
        return ;

    /*m_pParentSplitter
      * 1.如果是水平分割器 设置为垂直分割器  是垂直分割器不用管
      * 2.new 两个垂直分割器(水平分割器也可以 因为无法预料下次分割是水平还是垂直)
      * 3.将 m_pNowFocusTextEditor(当前选中的编辑器) 移到其中一个分割器
      * 4.new 一个编辑器 到另一个分割器
      * 5.添加这两个分割器到 m_pParentSplitter(选中编辑器所在的分割器中) */

    if(Qt::Vertical != m_pParentSplitter->orientation()){
        qDebug("所在Splitter是水平分割器!");
        m_pParentSplitter->setOrientation(Qt::Vertical); //设置为垂直分割器
    }

    QSplitter *splitterFirst = creatSplitter(Qt::Vertical,m_pParentSplitter);
    QSplitter *splitterSecond = creatSplitter(Qt::Vertical,m_pParentSplitter);

    m_pNowFocusTextEditor->setParent(splitterFirst);

    creatTextEditor(splitterSecond);

    m_pParentSplitter->addWidget(splitterFirst);
    m_pParentSplitter->addWidget(splitterSecond);

    /*设置分割比例  目前无效  @bug*/
    m_pParentSplitter->setStretchFactor(0,1);
    m_pParentSplitter->setStretchFactor(1,1);
}

void TMsgArea::slotHSplitScreen()
{
    qDebug("水平分屏");
    if(nullptr == m_pNowFocusTextEditor)
        return ;

    m_pParentSplitter = qobject_cast<QSplitter *>(m_pNowFocusTextEditor->parentWidget());
    if(nullptr == m_pParentSplitter)
        return ;

    /*m_pParentSplitter
     * 1.如果垂直分割器 设置为水平分割器 水平则不设置
     * 2.new 两个水平分割器(垂直分割器也可以 因为无法预料下次分割是水平还是垂直)
     * 3.将 m_pNowFocusTextEditor(当前选中的编辑器) 移到其中一个分割器
     * 4.new 一个编辑器 到另一个分割器
     * 5.添加这两个分割器到 m_pParentSplitter(选中编辑器所在的分割器中) */
    if(Qt::Horizontal != m_pParentSplitter->orientation()){
        qDebug("所在Splitter是垂直分割器!");
        m_pParentSplitter->setOrientation(Qt::Horizontal); //设置为 水平 分割器
    }

    QSplitter *splitterFirst = creatSplitter(Qt::Horizontal,m_pParentSplitter);
    QSplitter *splitterSecond = creatSplitter(Qt::Horizontal,m_pParentSplitter);

    m_pNowFocusTextEditor->setParent(splitterFirst);

    creatTextEditor(splitterSecond);

    m_pParentSplitter->addWidget(splitterFirst);
    m_pParentSplitter->addWidget(splitterSecond);

    /*设置分割比例  目前无效  @bug*/
    m_pParentSplitter->setStretchFactor(0,1);
    m_pParentSplitter->setStretchFactor(1,1);
}

void TMsgArea::slotMergeScreen()
{
    /* 大于两个编辑器的分屏策略
     * QSplitter Grandgrandfather,*Grandpa,*uncle,*parent;
     * TTextEditor *brother *Me *uncleEditor;
     *    -----------------------------------------------------
     *  |                  Grandgrandfather                    |
     *  |  -----------------------------   -----------------   |
     *  | |          Grandpa            | |    Grandpa      |  |
     *  | |  -----------   -----------  | |    ---------    |  |
     *  | | |  uncle    | |   parent  | | |   |         |   |  |
     *  | | |  -------  | |  -------  | | |   | uncle   |   |  |
     *  | | | |brother| | | |   Me  | | | |   | Editor  |   |  |
     *  | | |  -------  | |  -------  | | |   |         |   |  |
     *  | | |           | |           | | |    ---------    |  |
     *  | |  -----------   -----------  | |                 |  |
     *  |  -----------------------------   -----------------   |
     *   ------------------------------------------------------
     * 大于两个编辑器删除分屏策略
     * 1.找到 叔叔对象
     * 2.把 叔叔对象 放入祖父里
     * 3.删除选中编辑器、父亲、爷爷
     */


    /* 剩余两个编辑器的分屏状态
     * QWidget *Grandgrandfather;
     * QSplitter *Grandpa,*uncle,*parent;
     * TTextEditor *brother *Me *uncleEditor;
     *    -----------------------------------------------------
     *  |                  Grandgrandfather                    |
     *  |  -----------------------------   -----------------   |
     *  | |          Grandpa            | |    Grandpa      |  |
     *  | |  -----------   -----------  | |    ---------    |  |
     *  | | |  uncle    | |   parent  | | |   |         |   |  |
     *  | | |  -------  | |  -------  | | |   | uncle   |   |  |
     *  | | | |brother| | | |   Me  | | | |   | Editor  |   |  |
     *  | | |  -------  | |  -------  | | |   |         |   |  |
     *  | | |           | |           | | |    ---------    |  |
     *  | |  -----------   -----------  | |                 |  |
     *  |  -----------------------------   -----------------   |
     *   ------------------------------------------------------
     * 剩余两个编辑器删除分屏策略
     * 1.找到 叔叔对象、兄弟编辑器
     * 2.把 兄弟编辑器放入爷爷里
     * 3.删除选中编辑器、父亲、爷爷
     */

    /*当前未选中窗口  或者只有一个Editor 不操作  退出*/
    if((nullptr == m_pNowFocusTextEditor) || (1 == m_listTextEditor.count()))
        return ;


    m_pParentSplitter = qobject_cast<QSplitter *>(m_pNowFocusTextEditor->parentWidget());   //获取父对象
    m_pGrandpaSplitter = qobject_cast<QSplitter *>(m_pParentSplitter->parentWidget());      //获取爷爷对象
    m_pGrandgrandfather = m_pGrandpaSplitter->parentWidget();                               //获取曾祖父

    if((nullptr == m_pParentSplitter) || (nullptr == m_pGrandpaSplitter) || (nullptr == m_pGrandgrandfather))
        return ;

    /*遍历爷爷对象  找到叔叔对象*/
    for(int i = 0; i < m_pGrandpaSplitter->count(); i++)
    {
        /*每个 爷爷Splitter 里只有两个子对象 */
        if(m_pParentSplitter->objectName() != m_pGrandpaSplitter->widget(i)->objectName()){
            m_pUncleSplitter = qobject_cast<QSplitter *>(m_pGrandpaSplitter->widget(i));
        }
    }

//    /*剩下两个编辑器 的删除方法*/
//    if(3 > m_listTextEditor.count())
//    {
//        m_pBrotherTextEditor = qobject_cast<TTextEditor *>(m_pUncleSplitter->widget(0));//叔叔分割器仅有一个兄弟编辑器
//        m_pBrotherTextEditor->setParent(m_pGrandpaSplitter);//将兄弟编辑器放入爷爷里

//        removeTextEditor(m_pNowFocusTextEditor);
//        removeSplitter(m_pParentSplitter);
//        removeSplitter(m_pUncleSplitter);

//        m_pNowFocusTextEditor = m_listTextEditor.last();

//        return ;
//    }
    /*选中编辑器祖父不是Splitter 是主背景Widget 的删除方法*/
    /* 1.删除自己和父亲
     */
    if(m_pSplitterMain ==  m_pGrandpaSplitter)
    {
        removeTextEditor(m_pNowFocusTextEditor);
        removeSplitter(m_pParentSplitter);

        m_pNowFocusTextEditor = m_listTextEditor.last();
        qDebug()<<"执行删除策略1";
        return ;
    }
    /*大于两个编辑器的删除方法*/
    else
    {
        QSplitter * splitterGrandFather = qobject_cast<QSplitter *>(m_pGrandgrandfather);
        if(nullptr != splitterGrandFather){
            //爷爷index是0 就把叔叔放到0 防止直接放入祖父之后引起布局变化
            if(0 == splitterGrandFather->indexOf(m_pGrandpaSplitter))
                splitterGrandFather->insertWidget(0,m_pUncleSplitter);
            else
                splitterGrandFather->insertWidget(1,m_pUncleSplitter);
        }

        removeTextEditor(m_pNowFocusTextEditor);
        removeSplitter(m_pParentSplitter);
        removeSplitter(m_pGrandpaSplitter);

        m_pNowFocusTextEditor = m_listTextEditor.last();
        m_pParentSplitter = nullptr;
        m_pGrandpaSplitter = nullptr;
        qDebug()<<"执行删除策略2";
        return ;
    }

}

void TMsgArea::slotFocusChange(QWidget *old, QWidget *now)
{
    TTextEditor *oldTextEditor = qobject_cast<TTextEditor *>(old);
    TTextEditor *nowTextEditor = qobject_cast<TTextEditor *>(now);

    /*过滤事件  获取当前光标所在TTextEditor*/
    if((nullptr == oldTextEditor) && (nullptr == nowTextEditor))
    {
        qDebug("新旧部件不在 Editor！");
        return;
    }

    if(nullptr != nowTextEditor){
        m_pOldFocusTextEditor = m_pNowFocusTextEditor;
        m_pNowFocusTextEditor = nowTextEditor;

        if(nullptr != m_pOldFocusTextEditor){
            //m_pOldFocusTextEditor->appendPlainText("上次光标在这");
        }
        if(nullptr != m_pNowFocusTextEditor){
            m_pNowFocusTextEditor->appendPlainText("现在光标在这");

        }
    }
}

