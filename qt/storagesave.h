#ifndef STORAGESAVE_H
#define STORAGESAVE_H

#include <QObject>

#include <tinyxml2.h>

// TODO start doing the xx documentation



class StorageSave : public QObject
{
    Q_OBJECT
public:
    explicit StorageSave(QObject *parent = nullptr);
    void setCurrentFileName(QString);
    QString getCurrentFileName();
    bool loadXml();
    bool saveXml();

    QString getIdea();
    QString getProjectName();
    QString getProjectDescription();
    QString getPremise();

public slots:
    void ideaUpdate(QString);
    void projectnameUpdate(QString);
    void projectdescriptionUpdate(QString);
    void premiseUpdate(QString);

private:

    tinyxml2::XMLElement *CreateElementInGivenSection(tinyxml2::XMLElement *xmlSection, QString sElementName);
    const QString defaultFileName = "storytellerdefault.xml";
    QString m_sXmlFilename = defaultFileName;

    // http://leethomason.github.io/tinyxml2/
    tinyxml2::XMLDocument *m_pXmlDoc;
    tinyxml2::XMLElement *m_pGenerel;
    tinyxml2::XMLElement *m_pStoryDesign;


};

#endif // STORAGESAVE_H
