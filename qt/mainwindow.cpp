#include "mainwindow.h"

#include <QVBoxLayout>

#include <QApplication>

#include <QCloseEvent>

#include <QDateTime>
#include <QDebug>

#include <QFileDialog>

#include <QGridLayout>

#include <QPushButton>

#include <QStatusBar>

#include <QTimer>

#include <QWidget>

// See: http://doc.qt.io/qt-5/qmainwindow.html#details
// See: http://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
MainWindow::MainWindow() : mainWindowArea(new QWidget)
{

    m_pStorageSave = new StorageSave;

    gridLayoutArea = new QGridLayout;
    mainWindowArea->setLayout(gridLayoutArea);

    // See: https://forum.qt.io/topic/53814/qlayout-attempting-to-add-qlayout-to-mainwindow-which-already-has-a-layout-solved/4
    // Set the grid layout as a main layout
    setCentralWidget(mainWindowArea);


    // Window title
    setWindowTitle("Story teller");

    createStatusBar();

    createMenu();
    setMenuBar(menuBar);

    // TODO Have a tree list to the left, where I can create encounters and scenes
    // Clicking on an existing scene will load that data into the scene view
    // In the encounter view have list of scenes at the buttom
    // use signals to load these things and send data around.

    // Scene (add it under the Encounter)

    // TODO add WhatsThis: https://doc.qt.io/qt-5/qwhatsthis.html

    // addWidget(*Widget, row, column, rowspan, colspan)
    // 0th row
    int rowNumber = 0;
    QLabel *labelProjectName = new QLabel(this);
    labelProjectName->setText("Project name:");
    labelProjectName->setToolTip("Just a name that allows you to recognize the project.");
    gridLayoutArea->addWidget(labelProjectName,rowNumber,0,1,1);

    m_lineProjectName = new QLineEdit(this);
    m_lineProjectName->setText("");
    // TODO Add some sort of 'on exit' to go and save the sheet.
    gridLayoutArea->addWidget(m_lineProjectName,rowNumber,1,1,1);


    // 1st row
    rowNumber++;
    QLabel *labelBehindTheSceneLabel = new QLabel(this);
    labelBehindTheSceneLabel->setText("Project desctiption:");
    labelBehindTheSceneLabel->setToolTip("You quick note, to help you remember what you want with this project.");
    gridLayoutArea->addWidget(labelBehindTheSceneLabel,rowNumber,0,1,1);

    m_textProjectDescription = new QTextEdit(this);
    m_textProjectDescription->setText("");
    // TODO Add some sort of 'on exit' to go and save the sheet.
    gridLayoutArea->addWidget(m_textProjectDescription,rowNumber,1,2,1);


    // TODO StoryDesign, move into a class, and then put it in a tab

    // TODO Have a dropdown list of all the projects.
    // TODO

    // 2nd row
    rowNumber++;
    QLabel *labelNamePremise = new QLabel(this);
    labelNamePremise->setText("Premise:");
    //labelNamePremise->setWhatsThis("WhatsThis");
    labelNamePremise->setToolTip("ToolTip");
    gridLayoutArea->addWidget(labelNamePremise,rowNumber,0,1,1);

    m_linePremise = new QLineEdit(this);
    m_linePremise->setText("");
    //m_lineNamePremise->setStatusTip("StatusTip");
    // TODO Add some sort of 'on exit' to go and save the sheet.
    gridLayoutArea->addWidget(m_linePremise,rowNumber,1,1,1);


     // TODO have a draft 'Premise' section that can be 'hidden' collapesed
    /*

    createGridGroupBox();

     QVBoxLayout *mainLayout = new QVBoxLayout;

     mainLayout->setMenuBar(menuBar);

     mainLayout->addWidget(gridGroupBox);

     parent->setLayout(mainLayout);

     parent->setWindowTitle(tr("Basic Layouts"));
     */
    /*
     connect(sender, &Sender::signalName, receiver, &Receiver::slotName);
     From Mastering QT 5, p17.
     sender : This is the object that will send the signal. In our example, it is
              the QPushButton named addTaskButton added from the UI designer.
     &Sender::signalName : This is the pointer to the member signal function. Here,
                           we want do something when the clicked signal is triggered.
     receiver : This is the object that will receive and handle the signal. In our case, it
                is the QApplication object created in main.cpp .
     &Receiver::slotName : This is a pointer to one of the receiver's member slot
                           functions. In this example, we use the built-in quit() slot from Qapplication ,
                           which will exit the application.
   */



    // http://doc.qt.io/qt-5/qcombobox.html
   // http://doc.qt.io/qt-5/qcombobox.html#currentIndexChanged
   // https://stackoverflow.com/questions/28071461/qcombobox-connect

   // TODO isModified() for qlineedit
   // Described under 'Signals' in https://doc.qt.io/qt-5/qlineedit.html
   // This is for handling the drop down box(s)
   /* Send a signal when the lineEdit is done, the targeted slot will then get the text and signal it to the storage slot */
   QObject::connect(m_lineProjectName, SIGNAL(editingFinished()), this, SLOT(projectnameUpdateSlot()));
   QObject::connect(this, SIGNAL(signalProjectNameUpdated(QString)), m_pStorageSave, SLOT(projectnameUpdate(QString)));

   QObject::connect(m_textProjectDescription, SIGNAL(textChanged()), this, SLOT(projectdescriptionUpdateSlot()));


   QObject::connect(m_textProjectDescription, SIGNAL(textChanged()), this, SLOT(projectdescriptionUpdateSlot()));
   QObject::connect(this, SIGNAL(signalProjectDescriptionUpdated(QString)), m_pStorageSave, SLOT(projectdescriptionUpdate(QString)));

   QObject::connect(m_linePremise, SIGNAL(editingFinished()), this, SLOT(premiseUpdateSlot()));
   QObject::connect(this, SIGNAL(signalPremiseUpdated(QString)), m_pStorageSave, SLOT(premiseUpdate(QString)));

   // This must be last.
   readSettings();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);

    menuBar->addMenu(fileMenu);

    // QKeySequence::Save
    //Shift+Ctrl+S : Save As.
    fileMenu->addAction(tr("&Save"), this, &MainWindow::fileSave, QKeySequence::Save);

    //Shift+Ctrl+S : Save As.
    fileMenu->addAction(tr("&Save As..."), this, &MainWindow::fileSaveAs, QKeySequence::SaveAs);

    // https://doc.qt.io/qt-5/qkeysequence.html#details
    //fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),  QKeySequence(tr("Ctrl+O", "File|Open")));
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile,  QKeySequence(tr("Ctrl+O", "File|Open")));
    // Note the "File|Open" translator comment. It is by no means necessary, but it provides some context for the human translator.
    //connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
    // QKeySequence::Close
    // QKeySequence::New
    qDebug() << "Call to createMenu() - ";
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        recentFileActs[i]->setToolTip("TODO Full lenght file path");
        // TODO set up the trigger correctly, to load the file.
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }
    separatorAct = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i) {
        fileMenu->addAction(recentFileActs[i]);
    }
    fileMenu->addSeparator();
    // QKeySequence::Quit
    // Ctrl+Q
    // https://doc.qt.io/qt-5/qapplication.html
    // It seems that closeAllWindows() eventually emits the closeEvent().
    fileMenu->addAction(tr("E&xit"), this,  &QApplication::closeAllWindows,  QKeySequence::Quit);
    // QKeySequence::WhatsThis
    updateRecentFileActions();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (userReallyWantsToQuit()) {
        // TODO if maybeSave()
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

// https://doc.qt.io/qt-5/qsettings.html#details
void MainWindow::writeSettings()
{
    m_settings.beginGroup("MainWindow");
    m_settings.setValue("size", size());
    m_settings.setValue("pos", pos());
    m_settings.endGroup();
    if ( m_currentDirectory != "") {
        m_settings.setValue("currentDirectory", m_currentDirectory);

    }
}

void MainWindow::readSettings()
{
    m_settings.beginGroup("MainWindow");
    resize(m_settings.value("size", QSize(400, 400)).toSize());
    move(m_settings.value("pos", QPoint(200, 200)).toPoint());
    m_settings.endGroup();

    m_currentDirectory = m_settings.value("currentDirectory").toString();
    qDebug() << "Call to readSettings() - Dir: " << m_currentDirectory;
}

// From: https://doc.qt.io/archives/qt-4.8/qt-mainwindows-recentfiles-mainwindow-cpp.html
void MainWindow::setCurrentFile(const QString &fileName)
{
    qDebug() << "Call to setCurrentFile()";

    QString curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}
// From: https://doc.qt.io/archives/qt-4.8/qt-mainwindows-recentfiles-mainwindow-cpp.html
void MainWindow::updateRecentFileActions()
{
    qDebug() << "Call to updateRecentFileActions()";
    QStringList files = m_settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}
// From: https://doc.qt.io/archives/qt-4.8/qt-mainwindows-recentfiles-mainwindow-cpp.html
QString MainWindow::strippedName(const QString &fullFileName)
{
    qDebug() << "Call to strippedName()";
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        loadFile(action->data().toString());
}

// from: https://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
bool MainWindow::maybeSave()
{
    /* TODO implement this later.
    if (!textEdit->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    */
    return true;
}

bool MainWindow::userReallyWantsToQuit() {
    return true;
}

bool MainWindow::openFile()
{
    qDebug() << "Call to openFile()";
    // 'Save as...' is the title in the modal window.
    QFileDialog fileDialog(this, tr("Open file"));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);

    // https://en.wikipedia.org/wiki/XML_and_MIME
    // http://www.iana.org/assignments/media-types/media-types.xhtml
    // https://tools.ietf.org/html/rfc7303#page-21

    // This belows here, tells it what suffix filters to use, based on the mimetype (here it will be .xml)
    QStringList mimeTypes;
    mimeTypes << "text/xml";
    fileDialog.setMimeTypeFilters(mimeTypes);
    // I think this is when you have a list of multiple mimetypes, like different image types, then this sets the default one to use.
    fileDialog.setDefaultSuffix("xml");

    // TODO save the last default directory, e.g. in the .ini file.

    // Execute the dialog.
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString selectedFilename = fileDialog.selectedFiles().first();
    bool success = loadFile(selectedFilename);
    return success;
}

// This acutally loads the file and loads the data from the file to the view.
bool MainWindow::loadFile(QString selectedFilename) {
    m_pStorageSave->setCurrentFileName(selectedFilename);
    setCurrentFile(selectedFilename);
    qDebug() << "Call to Open()" << selectedFilename;
    bool success = m_pStorageSave->loadXml();
    // TODO clear out all views, when loading a new file, or when doing a 'New'
    // TODO Populate current display (tab) (move this code to a separate function
    QString text;
    text = m_pStorageSave->getProjectName();
    m_lineProjectName->setText(text);
    text = m_pStorageSave->getProjectDescription();
    m_textProjectDescription->setText(text);
    text = m_pStorageSave->getPremise();
    m_linePremise->setText(text);
    return success;
}

void MainWindow::quitApp()
{
    qDebug() << "Call to quitApp()";
}

// From: ./widgets/richtext/textedit/textedit.cpp
bool MainWindow::fileSave()
{
    // If the current file name hasn't been set, then call fileSaveAs() first
    if (m_pStorageSave->getCurrentFileName() == "")
        return fileSaveAs();
    /* TODO: what is this=
    if (fileName.startsWith(QStringLiteral(":/")))
        return fileSaveAs();
     */

    bool success = m_pStorageSave->saveXml();
    if (success) {
        qDebug() << "fileSave(): success";
        // textEdit->document()->setModified(false);
        // statusBar()->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
        setCurrentFile(m_pStorageSave->getCurrentFileName());
    } else {
        qDebug() << "fileSave(): failed";
        //statusBar()->showMessage(tr("Could not write to file \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

bool MainWindow::fileSaveAs()
{
    // fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
    // "Open Image" titel of the modal window.

    // 'Save as...' is the title in the modal window.
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if ( m_currentDirectory != " ") {
        fileDialog.setDirectory(m_currentDirectory);
    }

    // https://en.wikipedia.org/wiki/XML_and_MIME
    // http://www.iana.org/assignments/media-types/media-types.xhtml
    // https://tools.ietf.org/html/rfc7303#page-21

    // This belows here, tells it what suffix filters to use, based on the mimetype (here it will be .xml)
    QStringList mimeTypes;
    mimeTypes << "text/xml";
    fileDialog.setMimeTypeFilters(mimeTypes);
    // I think this is when you have a list of multiple mimetypes, like different image types, then this sets the default one to use.
    fileDialog.setDefaultSuffix("xml");

    // TODO save the last default directory, e.g. in the .ini file.

    // Execute the dialog.
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString selectedFilename = fileDialog.selectedFiles().first();
    m_pStorageSave->setCurrentFileName(selectedFilename);
    m_currentDirectory = fileDialog.directory().path();
    qDebug() << "Call to fileSaveAs()" << selectedFilename;
    qDebug() << "Call to fileSaveAs() - Dir: " << m_currentDirectory;
    return fileSave();
}


// From: http://doc.qt.io/qt-5/qtwidgets-layouts-basiclayouts-example.html
void MainWindow::createGridGroupBox()
{
    gridGroupBox = new QGroupBox(tr("Grid layout"));
    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < NumGridRows; ++i) {
        labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
        layout->addWidget(labels[i], i + 1, 0);
    }
    //smallEditor = new QTextEdit;
    /*
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
                                 */
    //layout->addWidget(smallEditor, 0, 2, 4, 1);
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}



void MainWindow::projectnameUpdateSlot() {
    // TODO check if text has changed?
    emit(signalProjectNameUpdated(m_lineProjectName->text()));
}
void MainWindow::projectdescriptionUpdateSlot() {
    qDebug() << "projectdescriptionUpdateSlot() ENTRY";
    // This function can be triggered by both; changes in the description text area and a time set by this function.
    /*
     * Have a timestamp if it has been more than 5s then save otherwise set a timer for 5s
     * If setting a timer I also need to monitor exit() so that everything is saved before exit.
     */
    qint64 nCurrentEpoch = QDateTime::currentSecsSinceEpoch();
    qDebug() << "projectdescriptionUpdateSlot() last epoch...: " << m_nLastEpochSaveProjectDescription;
    qDebug() << "projectdescriptionUpdateSlot() current epoch: " << nCurrentEpoch;
    if (( nCurrentEpoch - m_nLastEpochSaveProjectDescription) >= m_nSecondsBetweenQtEditSaves ) {
        m_nLastEpochSaveProjectDescription = nCurrentEpoch;
        projectdescriptionUpdateSlotTimeOutSave();
    } else {
        // if it is less than 5s since last, save, then set a oneshot for the delta to 5s
        qDebug() << "projectdescriptionUpdateSlot() wait for next save?" ;
        if (!m_bSaveTriggerSetForProjectDescription) {
            // if the timer hasn't been set, then set it.
            int deltaMiliseconds = int (1000 * m_nSecondsBetweenQtEditSaves);
            qDebug() << "projectdescriptionUpdateSlot() setting wait timer to " << deltaMiliseconds;
            m_bSaveTriggerSetForProjectDescription = true;

            QTimer::singleShot(deltaMiliseconds, this, SLOT(projectdescriptionUpdateSlotTimeOutSave()));
        }
        // See https://doc.qt.io/qt-5/qtimer.html
    }
    // TODO V Have a way to handle if we exit without having saved known changes.
    //  e.g. having a dictionary of unsaved fields, that could then be done emit on? at save??
}

void MainWindow::projectdescriptionUpdateSlotTimeOutSave() {
    qDebug() << "projectdescriptionUpdateSlotTimeOutSave()";
    m_bSaveTriggerSetForProjectDescription = false;
    emit(signalProjectDescriptionUpdated(m_textProjectDescription->toPlainText()));
}

void MainWindow::premiseUpdateSlot() {
    // TODO check if text has changed?
    emit(signalPremiseUpdated(m_linePremise->text()));
}
