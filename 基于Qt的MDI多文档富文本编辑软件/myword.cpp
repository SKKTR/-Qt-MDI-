#include "myword.h"

const QString srcpaths=":/new/prefix1/images";
MyWord::MyWord(QWidget *parent)
    : QMainWindow(parent)
{

    mdiArea=new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setCentralWidget(mdiArea);//将mdiArea加到中心控件
    connect(mdiArea,&QMdiArea::subWindowActivated,this,&MyWord::updateMenus);
    //    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(updateMenus()));

    createAction();
    createMenus();
    createToolBars();
    createStatusBar();
    updateMenus();

    resize(900,600);

    setWindowTitle("Office办公自动化文字编辑软件 V2.1");
    //setUnifiedTitleAndToolBarOnMac(true);
}

MyWord::~MyWord()
{
}

void MyWord::closeEvent(QCloseEvent* event)//关闭所有窗口
{
    mdiArea->closeAllSubWindows();
    if(mdiArea->currentSubWindow())
        event->ignore();
    else
        event->accept();
}

void MyWord::updateMenus()//有激活的窗口就使xxact点亮
{
    bool hasMyChild=(activeMyChild()!=0);

    saveAct->setEnabled(hasMyChild);
    saveAsAct->setEnabled(hasMyChild);
    printAct->setEnabled(hasMyChild);
    printPreviewAct->setEnabled(hasMyChild);

    pasteAct->setEnabled(hasMyChild);

    closeAct->setEnabled(hasMyChild);
    closeAllAct->setEnabled(hasMyChild);
    tileAct->setEnabled(hasMyChild);
    cascadeAct->setEnabled(hasMyChild);
    nextAct->setEnabled(hasMyChild);
    previousAct->setEnabled(hasMyChild);
    separatorAct->setEnabled(hasMyChild);

    bool hasSelection=(activeMyChild());

    cutAct->setEnabled(hasSelection);
    copyAct->setEnabled(hasSelection);

    boldAct->setEnabled(hasSelection);
    italicAct->setEnabled(hasSelection);
    underlineAct->setEnabled(hasSelection);
    leftAlignAct->setEnabled(hasSelection);
    centerAct->setEnabled(hasSelection);
    rightAlignAct->setEnabled(hasSelection);
    justifyAct->setEnabled(hasSelection);
    colorAct->setEnabled(hasSelection);
}

MyChild* MyWord::createMyChild()//返回child和将child加入mdiAea
{
    MyChild* child=new MyChild;

    mdiArea->addSubWindow(child);

    //    connect(child,SIGNAL(copyAvailable(bool)),cutAct,SLOT(setEnabled(bool)));
    //    connect(child,SIGNAL(copyAvailable(bool)),copyAct,SLOT(setEnabled(bool)));

    //    connect(child->document(), &QTextDocument::cursorPositionChanged, this, [=]() {
    //        if (child->textCursor().hasSelection()) {
    //            QTextCharFormat fmt = child->textCursor().charFormat();
    //            fontChanged(fmt.font());
    //            colorChanged(fmt.foreground().color());
    //            alignmentChanged(child->alignment());
    //        }
    //    });

    return child;
}

void MyWord::createAction()//实现各个Action，和各个实现功能的函数想连接
{
    newAct=new QAction(QIcon(srcpaths+"/filenew.png"),tr("新建(&N)"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setToolTip("新建");
    newAct->setStatusTip(tr("创建一个新的word文件."));
    connect(newAct, &QAction::triggered, this, &MyWord::fileNew);
    //    connect(newAct,SIGNAL(triggered()),this,SLOT(fileNew()));

    openAct=new QAction(QIcon(srcpaths+"/fileopen.png"),tr("打开(&O)"),this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setToolTip("打开");
    openAct->setStatusTip(tr("打开已经存在的word文档."));
    connect(openAct, &QAction::triggered, this, &MyWord::fileOpen);
    //    connect(openAct,SIGNAL(triggered()),this,SLOT(fileOpen()));

    saveAct=new QAction(QIcon(srcpaths+"/filesave.png"),tr("保存(&S)"),this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setToolTip("保存");
    saveAct->setStatusTip(tr("将当前word文档存盘."));
    connect(saveAct, &QAction::triggered, this, &MyWord::fileSave);
    //    connect(saveAct,SIGNAL(triggered()),this,SLOT(fileSave()));

    saveAsAct=new QAction(tr("另存为(&A)..."),this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setToolTip("另存为");
    saveAsAct->setStatusTip(tr("用另一个新的文件名称,保存当前word文档"));
    connect(saveAsAct, &QAction::triggered, this, &MyWord::fileSaveAs);
    //    connect(saveAsAct,SIGNAL(triggered()),this,SLOT(fileSaveAs()));

    printAct=new QAction(QIcon(srcpaths+"/fileprint.png"),tr("打印(&P)"),this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印当前word文档."));
    connect(printAct, &QAction::triggered, this, &MyWord::filePrint);
    //    connect(printAct,SIGNAL(triggered()),this,SLOT(filePrint()));

    printPreviewAct=new QAction(tr("打印预览..."),this);
    printPreviewAct->setStatusTip(tr("打印预览当前word文档效果."));
    connect(printPreviewAct, &QAction::triggered, this, &MyWord::filePrintPreview);
    //    connect(printPreviewAct,SIGNAL(triggered()),this,SLOT(filePrintPreview()));

    exitAct=new QAction(tr("退出(&X)"),this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip("退出word文件应用程序");
    connect(exitAct, &QAction::triggered, qApp, &QApplication::closeAllWindows);
    //    connect(exitAct,SIGNAL(triggered()),qApp,SLOT(closeAllWindows()));

    undoAct=new QAction(QIcon(srcpaths+"/editundo.png"),tr("撤销(&U)"),this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setToolTip("销毁");
    undoAct->setStatusTip(tr("销毁当前word文档操作."));
    connect(undoAct, &QAction::triggered, this, &MyWord::undo);
    //    connect(undoAct,SIGNAL(triggered()),this,SLOT(undo()));

    redoAct=new QAction(QIcon(srcpaths+"/editredo.png"),tr("重做(&R)"),this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setToolTip("重做");
    redoAct->setStatusTip(tr("恢复之前的word文档操作."));
    connect(redoAct, &QAction::triggered, this, &MyWord::redo);
    //    connect(redoAct,SIGNAL(triggered()),this,SLOT(redo()));

    cutAct=new QAction(QIcon(srcpaths+"/editcut.png"),tr("剪切(&T)"),this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("从word文档中裁剪所选择的内容,将它存放到剪贴板."));
    connect(cutAct, &QAction::triggered, this, &MyWord::cut);
    //    connect(cutAct,SIGNAL(triggered()),this,SLOT(cut()));

    copyAct=new QAction(QIcon(srcpaths+"/editcopy.png"),tr("复制(&C)"),this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("复制当前所选中的内容,将它存放到剪贴板."));
    connect(copyAct, &QAction::triggered, this, &MyWord::copy);
    //    connect(copyAct,SIGNAL(triggered()),this,SLOT(copy()));

    pasteAct=new QAction(QIcon(srcpaths+"/editpaste.png"),tr("粘贴(&P)"),this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("将剪贴板里面的内容粘贴到当前word文档."));
    connect(pasteAct, &QAction::triggered, this, &MyWord::paste);
    //    connect(pasteAct,SIGNAL(triggered()),this,SLOT(paste()));

    boldAct=new QAction(QIcon(srcpaths+"/textbold.png"),tr("加粗(&B)"),this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(Qt::CTRL+Qt::Key_B);
    boldAct->setToolTip("加粗");
    boldAct->setStatusTip(tr("将你所选择的文字进行加粗处理"));
    QFont bold;
    bold.setBold(true);
    boldAct->setFont(bold);
    connect(boldAct, &QAction::triggered, this, &MyWord::textBold);
    //    connect(boldAct,SIGNAL(triggered()),this,SLOT(textBold()));

    italicAct=new QAction(QIcon(srcpaths+"/textitalic.png"),tr("倾斜(&I)"),this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(Qt::CTRL+Qt::Key_I);
    italicAct->setToolTip("倾斜");
    italicAct->setStatusTip(tr("将你所选择的文字进行倾斜处理"));
    QFont italic;
    italic.setItalic(true);
    italicAct->setFont(italic);
    connect(italicAct, &QAction::triggered, this, &MyWord::textItalic);
    //    connect(italicAct,SIGNAL(triggered()),this,SLOT(textItalic()));

    underlineAct=new QAction(QIcon(srcpaths+"/textunder.png"),tr("下划线(&U)"),this);
    underlineAct->setCheckable(true);
    underlineAct->setShortcut(Qt::CTRL+Qt::Key_U);
    underlineAct->setToolTip("下划线");
    underlineAct->setStatusTip(tr("将你所选择的文字添加下划线"));
    QFont underline;
    underline.setUnderline(true);
    underlineAct->setFont(underline);
    connect(underlineAct, &QAction::triggered, this, &MyWord::textUnderline);
    //    connect(underlineAct,SIGNAL(triggered()),this,SLOT(textUnderline()));

    QActionGroup* grp=new QActionGroup(this);
    connect(grp, &QActionGroup::triggered, this, &MyWord::textAlign);
    //    connect(grp,SIGNAL(triggered(QAction* )),this,SLOT(textAlign(QAction* )));

    leftAlignAct=new QAction(QIcon(srcpaths+"/textleft.png"),tr("左对齐(&L)"),grp);
    centerAct=new QAction(QIcon(srcpaths+"/textcenter.png"),tr("居中对齐(&E)"),grp);
    rightAlignAct=new QAction(QIcon(srcpaths+"/textright.png"),tr("右对齐(&R)"),grp);
    justifyAct=new QAction(QIcon(srcpaths+"/textjustify.png"),tr("两端对齐(&J)"),grp);

    leftAlignAct->setShortcut(Qt::CTRL+Qt::Key_L);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setToolTip("左对齐");
    leftAlignAct->setStatusTip(tr("将选择文字进行左对齐."));

    centerAct->setShortcut(Qt::CTRL+Qt::Key_E);
    centerAct->setCheckable(true);
    centerAct->setToolTip("居中对齐");
    centerAct->setStatusTip(tr("将选择文字进行居中对齐."));

    rightAlignAct->setShortcut(Qt::CTRL+Qt::Key_R);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setToolTip("右对齐");
    rightAlignAct->setStatusTip(tr("将选择文字进行右对齐."));

    justifyAct->setShortcut(Qt::CTRL+Qt::Key_J);
    justifyAct->setCheckable(true);
    justifyAct->setToolTip("两端对齐");
    justifyAct->setStatusTip(tr("将选择文字进行两端对齐."));

    QPixmap pix(16,16);
    pix.fill(Qt::red);
    colorAct=new QAction(pix,tr("颜色(&C)..."),this);
    colorAct->setToolTip("颜色");
    colorAct->setStatusTip(tr("将你选择的文字,设置对应的颜色"));
    connect(colorAct, &QAction::triggered, this, &MyWord::textColor);
    //    connect(colorAct,SIGNAL(triggered()),this,SLOT(textColor()));

    closeAct=new QAction(tr("关闭(&O)"),this);
    closeAct->setStatusTip("关闭活动word文档子窗口.");
    connect(closeAct,&QAction::triggered,mdiArea,&QMdiArea::closeActiveSubWindow);
    //    connect(closeAct,SIGNAL(triggered()),mdiArea,SLOT(closeActiveSubWindow()));

    closeAllAct=new QAction(tr("关闭所有(&A)"),this);
    closeAllAct->setStatusTip("关闭活动word文档所有子窗口.");
    connect(closeAllAct,&QAction::triggered,mdiArea,&QMdiArea::closeAllSubWindows);
    //    connect(closeAllAct,SIGNAL(triggered()),mdiArea,SLOT(closeAllSubWindows()));

    tileAct=new QAction(tr("平铺(&A)"),this);
    tileAct->setStatusTip("平铺子窗口.");
    connect(tileAct,SIGNAL(triggered()),mdiArea,SLOT(tileSubWindows()));

    cascadeAct=new QAction(tr("层叠(&C)"),this);
    cascadeAct->setStatusTip("层叠子窗口.");
    connect(cascadeAct,&QAction::triggered,mdiArea,&QMdiArea::cascadeSubWindows);
    //    connect(cascadeAct,SIGNAL(triggered()),mdiArea,SLOT(cascadeSubWindows()));

    nextAct=new QAction(tr("下一个(&T)"),this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip("移动焦点到下一个子窗口.");
    connect(nextAct,&QAction::triggered,mdiArea,&QMdiArea::activateNextSubWindow);
    //    connect(nextAct,SIGNAL(triggered()),mdiArea,SLOT(activateNextSubWindow()));

    previousAct=new QAction(tr("前一个(&A)"),this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip("移动焦点到前一个子窗口.");
    connect(previousAct,&QAction::triggered,mdiArea,&QMdiArea::activatePreviousSubWindow);
    //    connect(previousAct,SIGNAL(triggered()),mdiArea,SLOT(activatePreviousSubWindow()));

    separatorAct=new QAction(this);
    separatorAct->setSeparator(true);

    aboutAct=new QAction(tr("关于(&A)"),this);
    aboutAct->setStatusTip("关于Office Word相关信息");
    connect(aboutAct, &QAction::triggered, this, &MyWord::about);
    //    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

    aboutQtAct=new QAction(tr("关于Qt(&Qt)"),this);
    aboutQtAct->setStatusTip("关于Qt库相关信息");
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    //    connect(aboutQtAct,SIGNAL(triggered()),this,SLOT(aboutQt()));

}

void MyWord::createMenus()  //将各个action加入menu栏
{
    fileMenu=menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addAction(printPreviewAct);
    fileMenu->addAction(exitAct);

    editMenu=menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    formatMenu=menuBar()->addMenu(tr("格式(&O)"));
    fontMenu=formatMenu->addMenu(tr("字体(&D)"));
    fontMenu->addAction(boldAct);
    fontMenu->addAction(italicAct);
    fontMenu->addAction(underlineAct);

    alignMenu=formatMenu->addMenu(tr("段落"));
    alignMenu->addAction(leftAlignAct);
    alignMenu->addAction(centerAct);
    alignMenu->addAction(rightAlignAct);
    alignMenu->addAction(justifyAct);

    formatMenu->addAction(colorAct);

    windowMenu=menuBar()->addMenu(tr("窗口(&W)"));
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);

    helpMenu=menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutQtAct);
}

void MyWord::createToolBars() //将各个action加入工具栏
{
    fileToolBar=addToolBar(tr("文件"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);

    editToolBar=addToolBar(tr("编辑"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    formatToolBar=addToolBar(tr("格式"));
    formatToolBar->addAction(boldAct);
    formatToolBar->addAction(italicAct);
    formatToolBar->addAction(underlineAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(leftAlignAct);
    formatToolBar->addAction(centerAct);
    formatToolBar->addAction(rightAlignAct);
    formatToolBar->addAction(justifyAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(colorAct);

    addToolBarBreak(Qt::TopToolBarArea);
    comboToolBar=addToolBar(tr("组合选择"));
    comboStyle=new QComboBox();
    comboToolBar->addWidget(comboStyle);
    comboStyle->addItem("标准");
    comboStyle->addItem("项目符号 (●)");
    comboStyle->addItem("项目符号 (○)");
    comboStyle->addItem("项目符号 (■)");
    comboStyle->addItem("编号 (⒈⒉⒊)");
    comboStyle->addItem("编号 ( a.b.c.)");
    comboStyle->addItem("编号 ( A.B.C.)");
    comboStyle->addItem("编号 (ⅰ.ⅱ.ⅲ.)");
    comboStyle->addItem("编号 (Ⅰ.Ⅱ.Ⅲ.)");
    comboStyle->setStatusTip("段落加上标号或编号");
    connect(comboStyle,QOverload<int>::of(&QComboBox::activated),this,&MyWord::textStyle);
//    connect(comboStyle,SIGNAL(activated(int)),this,SLOT(textStyle(int)));

    comboFont=new QFontComboBox();
    comboToolBar->addWidget(comboFont);
    comboFont->setStatusTip("更改字体");
    connect(comboFont,QOverload<const QString &>::of(&QComboBox::activated),this,&MyWord::textFamily);
//    connect(comboFont,SIGNAL(activated(QString)),this,SLOT(textFamily(QString)));

    comboSize=new QComboBox();
    comboToolBar->addWidget(comboSize);
    comboSize->setEditable(true);
    comboSize->setStatusTip("更改字号");
    QFontDatabase db;
    foreach(int size,db.standardSizes())
        comboSize->addItem(QString::number(size));
    connect(comboSize,QOverload<const QString &>::of(&QComboBox::activated),this,&MyWord::textSize);
//    connect(comboSize,SIGNAL(activated(QString)),this,SLOT(textSize(QString)));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font().pointSize())));
}

void MyWord::createStatusBar()//在状态栏显示就绪状态
{
    statusBar()->showMessage(tr("就绪状态"));
}

MyChild* MyWord::activeMyChild()//获取当前激活的窗口，返回强制转类型的子窗口
{
    if(QMdiSubWindow* activeSubWindow=mdiArea->activeSubWindow())
        return qobject_cast<MyChild*>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow* MyWord::findMyChild(const QString &filename)//存在与打开的窗口有相同的路径则返回那个相同路径的子窗口
{
    QString canonicalFilePath=QFileInfo(filename).canonicalFilePath();

    foreach(QMdiSubWindow* window,mdiArea->subWindowList())
    {
        MyChild* myChild=qobject_cast<MyChild*>(window->widget());

        if(myChild->currentFile()==canonicalFilePath)
            return window;
    }

    return 0;
}

void MyWord::setActiveSubWindow(QWidget* window)//将某窗口设为激活窗口
{
    if(!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));
}

void MyWord::fileNew()//和newFile相关联以及和新建窗口
{
    MyChild* child=createMyChild();
    child->newFile();
    child->show();
    enabledText();
}

void MyWord::fileOpen()//将要打开的文件写入，若存在与要打开的文件相同路径则激活该相同路径的窗口
{
    QString filename=QFileDialog::getOpenFileName(this,tr("打开"),QString(),tr("HTML 文档(*.htm *.html);;所有文件(*.*)"));

    if(!filename.isEmpty())
    {
        QMdiSubWindow* existing=findMyChild(filename);
        if(existing)
        {
            mdiArea->setActiveSubWindow(existing);
            return;
        }

        MyChild* child=createMyChild();
        if(child->loadFile(filename))
        {
            statusBar()->showMessage(tr("文件已经加载"),2000);
            child->show();
            enabledText();
        }
        else
        {
            child->close();
        }
    }
}

void MyWord::fileSave()//和save()函数相联系
{
    if(activeMyChild() && activeMyChild()->save())
        statusBar()->showMessage(tr("word文档保存成功."));
}

void MyWord::fileSaveAs()//和saveAs()函数相联系
{
    if(activeMyChild() && activeMyChild()->saveAs())
        statusBar()->showMessage(tr("word文档另存为成功."));
}

void MyWord::undo()//撤销
{
    if(activeMyChild())
        activeMyChild()->undo();
}

void MyWord::redo()//复原上一次的操作
{
    if(activeMyChild())
        activeMyChild()->redo();
}

void MyWord::cut()//剪贴
{
    if(activeMyChild())
        activeMyChild()->cut();
}

void MyWord::copy()//复制
{
    if(activeMyChild())
        activeMyChild()->copy();
}

void MyWord::paste()//粘贴
{
    if(activeMyChild())
        activeMyChild()->paste();
}

void MyWord::enabledText()//将函数内的action功能显示出
{
    boldAct->setEnabled(true);
    italicAct->setEnabled(true);
    underlineAct->setEnabled(true);
    leftAlignAct->setEnabled(true);
    centerAct->setEnabled(true);
    rightAlignAct->setEnabled(true);
    justifyAct->setEnabled(true);
    colorAct->setEnabled(true);
}

void MyWord::textBold()//和mergeFormationOnWordOrSelection相联系，进行加粗操作
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldAct->isChecked()?QFont::Bold:QFont::Normal);
    if(activeMyChild())
        activeMyChild()->mergeFormationOnWordOrSelection(fmt);
}

void MyWord::textItalic()//和mergeFormationOnWordOrSelection相联系，进行倾斜操作
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicAct->isChecked());
    if(activeMyChild())
        activeMyChild()->mergeFormationOnWordOrSelection(fmt);
}

void MyWord::textUnderline()//和mergeFormationOnWordOrSelection相联系，进行画下划线操作
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineAct->isChecked());
    if(activeMyChild())
        activeMyChild()->mergeFormationOnWordOrSelection(fmt);
}

void MyWord::textAlign(QAction* a)//和setAlign相联系
{
    if(activeMyChild())
    {
        if(a==leftAlignAct)
            activeMyChild()->setAlign(1);
        else if(a==centerAct)
            activeMyChild()->setAlign(2);
        else if(a==rightAlignAct)
            activeMyChild()->setAlign(3);
        else if(a==justifyAct)
            activeMyChild()->setAlign(4);
    }
}

void MyWord::textStyle(int styleIndex)//和setStyle相联系
{
    if(activeMyChild())
        activeMyChild()->setStyle(styleIndex);
}

void MyWord::textFamily(const QString &f)//和mergeFormationOnWordOrSelection相联系，进行改字体的操作
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    if(activeMyChild())
        activeMyChild()->mergeFormationOnWordOrSelection(fmt);
}

void MyWord::textSize(const QString &p)//和mergeFormationOnWordOrSelection相联系，进行改字号的操作
{
    qreal pointsize=p.toFloat();
    if(p.toFloat()>0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointsize);
        if(activeMyChild())
            activeMyChild()->mergeFormationOnWordOrSelection(fmt);
    }
}

void MyWord::textColor()//打开颜色系统窗口，获取颜色，改变文本颜色
{
    if(activeMyChild())
    {
        QColor color=QColorDialog::getColor(activeMyChild()->textColor(),this);
        if(!color.isValid())
            return;
        QTextCharFormat fmt;
        fmt.setForeground(color);
        activeMyChild()->mergeFormationOnWordOrSelection(fmt);
        colorChanged(color);
    }
}

//void MyWord::fontChanged(const QFont &f)
//{
//    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
//    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));

//    boldAct->setChecked(f.bold());
//    italicAct->setChecked(f.italic());
//    underlineAct->setChecked(f.underline());
//}

void MyWord::colorChanged(const QColor &c)//修改颜色action的图标
{
    QPixmap pix(16,16);
    pix.fill(c);
    colorAct->setIcon(pix);
}

//void MyWord::alignmentChanged(Qt::Alignment a)
//{
//    if(a & Qt::AlignLeft)
//        leftAlignAct->setChecked(true);
//    else if(a & Qt::AlignCenter)
//        centerAct->setChecked(true);
//    else if(a & Qt::AlignRight)
//        rightAlignAct->setChecked(true);
//    else if(a & Qt::AlignJustify)
//        justifyAct->setChecked(true);
//}

void MyWord::filePrint()//打开打印窗口，实现打印功能
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog* pdlg=new QPrintDialog(&printer,this);
    if(activeMyChild()->textCursor().hasSelection())
        pdlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    pdlg->setWhatsThis(tr("打印文档"));
    if(pdlg->exec()==QDialog::Accepted)
        activeMyChild()->print(&printer);

    delete pdlg;
}

void MyWord::filePrintPreview()//打开打印预览窗口
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer,this);
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),SLOT(printPreview(QPrinter*)));
    preview.exec();
}

void MyWord::printPreview(QPrinter* printer)//实现打印功能
{
    activeMyChild()->print(printer);
}

void MyWord::about()//实现关于action的功能
{
    QMessageBox::about(this,tr("关于"),tr("此软件是基于Qt5实现的文字处理软件! ! !"));
}
