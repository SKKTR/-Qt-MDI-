#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>
#include<mychild.h>
#include<QtWidgets>
#include<QPrintDialog>
#include<QPrinter>
#include<QPrintPreviewDialog>

class MyChild;
class QAction;
class QMenu;
class QComboBox;
class QFontComboBox;
class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;

class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = nullptr);
    ~MyWord();
protected:
    void closeEvent(QCloseEvent* event);
private:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void printPreview(QPrinter* printer);

    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void about();

    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign(QAction* a);
    void textStyle(int styleIndex);
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textColor();

    void updateMenus();
    void updateWindowMenu();
    void setActiveSubWindow(QWidget* window);
    MyChild* createMyChild();

    void createAction();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void enabledText();
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);
    MyChild* activeMyChild();
    QMdiSubWindow* findMyChild(const QString &filename);

    QMdiArea* mdiArea;
    QSignalMapper* windowMapper;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* formatMenu;
    QMenu* fontMenu;
    QMenu* alignMenu;
    QMenu* windowMenu;
    QMenu* helpMenu;

    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QToolBar* formatToolBar;
    QToolBar* comboToolBar;
    QComboBox* comboStyle;
    QFontComboBox* comboFont;
    QComboBox* comboSize;

    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* printAct;
    QAction* printPreviewAct;
    QAction* exitAct;

    QAction* undoAct;
    QAction* redoAct;
    QAction* cutAct;
    QAction* copyAct;
    QAction* pasteAct;

    QAction* boldAct;
    QAction* italicAct;
    QAction* underlineAct;
    QAction* leftAlignAct;
    QAction* centerAct;
    QAction* rightAlignAct;
    QAction* justifyAct;
    QAction* colorAct;

    QAction* closeAct;
    QAction* closeAllAct;
    QAction* tileAct;
    QAction* cascadeAct;
    QAction* nextAct;
    QAction* previousAct;
    QAction* separatorAct;

    QAction* aboutAct;
    QAction* aboutQtAct;

};
#endif // MYWORD_H
