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

public slots:
    void projectnameUpdate(QString);
    void projectdescriptionUpdate(QString);
    void premiseUpdate(QString);

private:
    void saveXml();

    // TODO V Add function to set the filename.
    QString m_sXmlFilename = "storytellerdefault.xml";

    tinyxml2::XMLDocument *m_pXmlDoc;
    tinyxml2::XMLElement *m_pGenerel;
    tinyxml2::XMLElement *m_pStoryDesign;

};

#endif // STORAGESAVE_H
