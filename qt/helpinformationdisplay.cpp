
#include <QDebug>

#include "helpinformationdisplay.h"

HelpInformationDisplay::HelpInformationDisplay(QWidget *parent, QString sQtHelpCollectionFile) : QTextBrowser(parent)
{
    // the .qhc file
    QString helpFile = QLatin1String(sQtHelpCollectionFile.toLatin1());

    qDebug() << "HelpBrowser(): collectionFile:"  << helpFile;

    m_helpCoreEngine = new QHelpEngineCore(helpFile, this);
    if (!m_helpCoreEngine->setupData()) {
        qDebug() << "EEE - showHelpForKeyword() - Engine deleted";
        delete m_helpCoreEngine;
        m_helpCoreEngine = nullptr;
    }
}

void HelpInformationDisplay::showHelpTextForKeyword(QString helpKeyword) {
    qDebug() << "showHelpTextForKeyword(): "  << helpKeyword;
    if (m_helpCoreEngine) {
        qDebug() << "showHelpTextForKeyword(): - core engine defined.";
        qDebug() << "   collection file:" << m_helpCoreEngine->collectionFile();
        qDebug() << "   current filter:" << m_helpCoreEngine->currentFilter();
        QMap<QString, QUrl> links = m_helpCoreEngine->linksForKeyword(helpKeyword);
        qDebug() << "   error: " << m_helpCoreEngine->error();
        if (links.count()) {
            qDebug() << "showHelpTextForKeyword(): - links count - "  << links.constBegin().value();
            QUrl resultUrl = m_helpCoreEngine->findFile(links.constBegin().value());
            qDebug() << "showHelpTextForKeyword(): - findFile result: "  << resultUrl.fileName();
            qDebug() << "showHelpTextForKeyword(): - Scheme: "  << resultUrl.scheme();

            setSource(links.constBegin().value());
        }
    }
}

QVariant HelpInformationDisplay::loadResource(int type, const QUrl &name)
{
    QByteArray ba;
    qDebug() << "loadResource()";
    if (type < 4 && m_helpCoreEngine) {
        QUrl url(name);
        if (name.isRelative())
            url = source().resolved(url);
        ba = m_helpCoreEngine->fileData(url);
    }
    return ba;
}
