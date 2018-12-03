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

    // addWidget(*Widget, row, column, rowspan, colspan)
    // 0th row
    QLabel *labelSceneNameLabel = new QLabel(this);
    labelSceneNameLabel->setText("Scene name:");
    gridLayoutArea->addWidget(labelSceneNameLabel,0,0,1,1);

    m_lineSceneName = new QLineEdit(this);
    m_lineSceneName->setText("");
    // TODO Add some sort of 'on exit' to go and save the sheet.
    gridLayoutArea->addWidget(m_lineSceneName,0,1,1,1);


    /*

    createGridGroupBox();

     QVBoxLayout *mainLayout = new QVBoxLayout;

     mainLayout->setMenuBar(menuBar);

     mainLayout->addWidget(gridGroupBox);

     parent->setLayout(mainLayout);

     parent->setWindowTitle(tr("Basic Layouts"));
     */
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
        lineEdits[i] = new QLineEdit;
        layout->addWidget(labels[i], i + 1, 0);
        layout->addWidget(lineEdits[i], i + 1, 1);
    }
    smallEditor = new QTextEdit;
    smallEditor->setPlainText(tr("This widget takes up about two thirds of the "
                                 "grid layout."));
    layout->addWidget(smallEditor, 0, 2, 4, 1);
    layout->setColumnStretch(1, 10);
    layout->setColumnStretch(2, 20);
    gridGroupBox->setLayout(layout);
}

void MainWindow::createStatusBar()
{

    statusBar()->showMessage(tr("Ready"));
}
