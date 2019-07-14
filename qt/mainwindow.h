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

private slots:
    void projectnameUpdateSlot();
    void projectdescriptionUpdateSlot();
    void premiseUpdateSlot();

signals:
    // Used for sending to StorageSave

    void projectnameUpdate(QString);
    void projectdescriptionUpdate(QString);
    void premiseUpdate(QString);

    // These are local sigals for transferring text to the storage class.
    void signalProjectNameUpdated(QString);
    void signalProjectDescriptionUpdated(QString);
    void signalPremiseUpdated(QString);

private:
    void createMenu();
    void createGridGroupBox();
    void createStatusBar();

    QGridLayout *gridLayoutArea;

    StorageSave *m_pStorageSave;

    QLineEdit *m_lineProjectName;
    QTextEdit *m_textProjectDescription;

    QLineEdit *m_linePremise;

    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar *menuBar;
    QGroupBox *gridGroupBox;

    QMenu *fileMenu;
    QAction *exitAction;

    QLabel *labels[NumGridRows];


    QWidget *mainWindowArea;

    QGridLayout *gridLayout;
};

#endif // MAINWINDOW_H
