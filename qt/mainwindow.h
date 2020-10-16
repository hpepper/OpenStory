#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QGroupBox>

#include <QLabel>
#include <QLineEdit>

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>

#include <QSettings>

#include <QTextEdit>

#include "helpinformationdisplay.h"

#include "storagesave.h"

// This is to allow focus change to be acted on in the application.
#if defined(thisApplication)
#undef thisApplication
#endif
#define thisApplication (static_cast<QApplication *>(QCoreApplication::instance()))



class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

    // https://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void projectnameUpdateSlot();
    void projectdescriptionUpdateSlot();
    void projectdescriptionUpdateSlotTimeOutSave();
    void premiseUpdateSlot();
    void ideaUpdateSlot();
    void openRecentFile();
    void focusChanged(QWidget *previousWidget, QWidget *currentWidget);

signals:
    // Used for sending to StorageSave

    void projectnameUpdate(QString);
    void projectdescriptionUpdate(QString);
    void premiseUpdate(QString);

    // These are local signals for transferring text to the storage class.
    void signalProjectNameUpdated(QString);
    void signalProjectDescriptionUpdated(QString);
    void signalPremiseUpdated(QString);
    void signalIdeaUpdated(QString);

private:
    void createMenu();
    void createGridGroupBox();
    void createStatusBar();

    void quitApp();
    bool newFile();
    bool openFile();
    bool loadFile(QString);
    bool fileSaveAs();
    bool fileSave();
    void writeSettings();
    void readSettings();
    bool maybeSave();
    bool userReallyWantsToQuit();
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    void setCurrentFile(const QString &fileName);

    QAction *separatorAct;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

    QSettings m_settings;


    QGridLayout *gridLayoutArea;

    StorageSave *m_pStorageSave;

    QLineEdit *m_lineProjectName;
    QTextEdit *m_textProjectDescription;

    QLineEdit *m_linePremise;
    QLineEdit *m_lineIdea;

    QLabel *m_labelInformationText;

    HelpInformationDisplay *m_txtbrowserInformationText;

    enum { NumGridRows = 3, NumButtons = 4 };

    QMenuBar *menuBar;
    QGroupBox *gridGroupBox;

    QMenu *fileMenu;
    QAction *exitAction;

    QLabel *labels[NumGridRows];


    QWidget *mainWindowArea;

    QGridLayout *gridLayout;

    QHelpEngineCore *m_helpCoreEngine;

    qint64 m_nLastEpochSaveProjectDescription = 0;
    QString m_collectionsFileFullPath;

    // How many seconds to wait between commits of QtEdit fields.
    const qint64 m_nSecondsBetweenQtEditSaves = 5;

    bool m_bSaveTriggerSetForProjectDescription = false;

    QString m_currentDirectory = "";

     QMap<QWidget*, QString> m_mapWidgetToHelpKeyWord;
};

#endif // MAINWINDOW_H
