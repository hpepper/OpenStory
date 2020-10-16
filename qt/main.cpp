#include "mainwindow.h"
#include <QApplication>


#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // https://doc.qt.io/qt-5/qsettings.html#details
    // These must be here otherwise the setting will be saved under: 'Unknown Organization'
    // https://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
    QCoreApplication::setOrganizationName("RpgTools");
    QCoreApplication::setOrganizationDomain("open.tools.rpg");
    QCoreApplication::setApplicationName("Story teller");


    MainWindow *w = new MainWindow();
    w->show();


    return a.exec();
}
