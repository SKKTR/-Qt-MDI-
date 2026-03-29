#ifndef MYCHILD_H
#define MYCHILD_H

#include<QTextEdit>
#include<QPrinter>

class MyChild : public QTextEdit
{
    Q_OBJECT
public:
    MyChild();


    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(QString fileName);
    QString userFriendlyCurrentFile();
    QString currentFile();
    void mergeFormationOnWordOrSelection(const QTextCharFormat &format);
    void setAlign(int align);
    void setStyle(int style);

    bool isUntitled;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void documentWasModified();

private:
    QString curFile;
//    bool isUntitled;

    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
};

#endif // MYCHILD_H
