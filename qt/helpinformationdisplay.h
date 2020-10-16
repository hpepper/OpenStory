#ifndef HELPINFORMATIONDISPLAY_H
#define HELPINFORMATIONDISPLAY_H


#include <QtHelp/QHelpEngineCore>

#include <QtWidgets/QTextBrowser>


QT_BEGIN_NAMESPACE
class QHelpEngineCore;
QT_END_NAMESPACE;


class HelpInformationDisplay : public QTextBrowser
{
    Q_OBJECT
public:
    explicit HelpInformationDisplay(QWidget *parent = nullptr, QString sQtHelpCollectionFile = "");
    void showHelpTextForKeyword(QString helpKeyword);

signals:

public slots:

private:
    // Thiss seems to be called during init of the help engine.
    QVariant loadResource(int type, const QUrl &name) override;

    QHelpEngineCore *m_helpCoreEngine;
};

#endif // HELPINFORMATIONDISPLAY_H
