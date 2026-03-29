#include "mychild.h"

#include<QtWidgets>

MyChild::MyChild()
{
    setAttribute(Qt::WA_DeleteOnClose);//窗口关闭就清理内存
    isUntitled=true;
}

void MyChild::newFile()//文本修改使标题修改
{
    static int sequenceNumber=1;
    isUntitled=true;
    curFile=tr("Word文档-%1").arg(sequenceNumber++);
    setWindowTitle(curFile+"[*]");
    connect(document(), &QTextDocument::contentsChanged, this, &MyChild::documentWasModified);
    //    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));
}

bool MyChild::loadFile(const QString &fileName)//将要打开的文件内容，标题写入窗口，在窗口修改内容会使标题+*
{
    if(!fileName.isEmpty())
    {
        if(!QFile::exists(fileName))
            return false;

        QFile file(fileName);

        if (!file.open(QFile::ReadOnly))
            return false;

        QByteArray data=file.readAll();

        QTextCodec* codec=Qt::codecForHtml(data);
        QString str=codec->toUnicode(data);

        if(Qt::mightBeRichText(str))
        {
            this->setHtml(str);
        }
        else
        {
            str=QString::fromLocal8Bit(data);
            this->setPlainText(str);
        }

        setCurrentFile(fileName);
        //        disconnect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
        connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));
        return true;
    }
    return false;
}

bool MyChild::save()//是新建的文件则另存为，打开的文件则保存文件
{
    if(isUntitled)
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MyChild::saveAs()//打开另存为窗口，实现另存为
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("另存为"),curFile,tr("HTML 文档(*.html);;所有文件(*.*)"));

    if(fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool MyChild::saveFile(QString fileName)//给没.htm和.html结尾的打开的文件加.html的结尾，将打开的文件写入要保存的内容
{
    if(!(fileName.endsWith(".htm",Qt::CaseInsensitive) || fileName.endsWith(".html",Qt::CaseInsensitive)))
    {
        fileName+=".html";
    }

    QTextDocumentWriter writer(fileName);
    bool success=writer.write(this->document());
    //    if(success)
    //        setCurrentFile(fileName);

    return success;
}

QString MyChild::userFriendlyCurrentFile()//返回strippedName函数
{
    return strippedName(curFile);
}

QString MyChild::currentFile()//返回激活窗口的文件名或文件路径
{
    return curFile;
}

void MyChild::mergeFormationOnWordOrSelection(const QTextCharFormat &format)//应用样式
{
    QTextCursor cursor=this->textCursor();

    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void MyChild::setAlign(int align)//应用不同的对齐方式
{
    if(align==1)
        this->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if(align==2)
        this->setAlignment(Qt::AlignCenter);
    else if(align==3)
        this->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if(align==4)
        this->setAlignment(Qt::AlignJustify);
}

void MyChild::setStyle(int style)//将文本转成列表，以及将列表转成文本
{
    QTextCursor cursor=this->textCursor();

    if(style!=0)
    {
        QTextListFormat::Style stylename=QTextListFormat::ListDisc;

        switch(style)
        {
        default:
            break;
        case 1:
            stylename=QTextListFormat::ListDisc;
            break;
        case 2:
            stylename=QTextListFormat::ListCircle;
            break;
        case 3:
            stylename=QTextListFormat::ListSquare;
            break;
        case 4:
            stylename=QTextListFormat::ListDecimal;
            break;
        case 5:
            stylename=QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            stylename=QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            stylename=QTextListFormat::ListLowerRoman;
            break;
        case 8:
            stylename=QTextListFormat::ListUpperRoman;
            break;
        }

        cursor.beginEditBlock();
        QTextBlockFormat blockFmt=cursor.blockFormat();
        QTextListFormat listFmt;

        if(!(cursor.currentList()))
        {
            listFmt.setIndent(blockFmt.indent()+1);
        }

        listFmt.setStyle(stylename);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else
    {
        if (cursor.currentList()) {
            QTextBlockFormat bfmt;
            bfmt.setIndent(0);
            cursor.setBlockFormat(bfmt);
        }
    }
}

void MyChild::closeEvent(QCloseEvent *event)//子窗口或主窗口关闭，若文本有修改则呼出QMessageBox窗口
{
    if(maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MyChild::documentWasModified()//修改文本和[*]相联系
{
    setWindowModified(document()->isModified());
}

bool MyChild::maybeSave()//打开要不要保存的QMessageBox的窗口
{
    if(!document()->isModified())
        return true;

    QMessageBox::StandardButton ret;
    ret=QMessageBox::warning(this,tr("Qt Word"),tr("文件'%1'已经被修改，是否保存吗？").arg(userFriendlyCurrentFile()),QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);

    if(ret==QMessageBox::Save)
        return save();
    else if(ret==QMessageBox::Cancel)
        return false;

    return true;
}

void MyChild::setCurrentFile(const QString &fileName)//设置要打开的文件名
{
    curFile=QFileInfo(fileName).canonicalFilePath();
    isUntitled=false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile()+"[*]");
}

QString MyChild::strippedName(const QString &fullFileName)//返回要打开的文件名
{
    return QFileInfo(fullFileName).fileName();
}
