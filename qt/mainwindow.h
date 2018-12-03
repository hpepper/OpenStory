#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenuBar>
#include <QMenu>

#include <QLabel>

#include <QLineEdit>
#include <QTextEdit>


#include <QGroupBox>

#include <QGridLayout>

#include "storagesave.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    void createMenu();
    void createGridGroupBox();
    void createStatusBar();

    QGridLayout *gridLayoutArea;

    StorageSave *m_pStorageSave;

    QLineEdit *m_lineSceneName;

    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar *menuBar;
    QGroupBox *gridGroupBox;

    QMenu *fileMenu;
    QAction *exitAction;

    QLabel *labels[NumGridRows];
    QLineEdit *lineEdits[NumGridRows];
    QTextEdit *smallEditor;

    QWidget *mainWindowArea;

    QGridLayout *gridLayout;
};

#endif // MAINWINDOW_H
