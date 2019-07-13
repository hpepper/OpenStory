#include "mainwindow.h"

#include <QVBoxLayout>

#include <QGridLayout>
#include <QPushButton>

#include <QStatusBar>
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
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    //connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
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
