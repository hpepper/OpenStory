#include "storagesave.h"

#include <QDebug>


/* TODO When I start loading the data to load an existing char
 *   Disable the SaveXml() until the load is done, that way I can just fake the interfacething,
 *   that it seems Qt support.
 */

// TODO Later handle that it might be a newer version of XML being read in.
/** Currently The whole structure is created here.
 *
 * Adding a new Group:
 *  Add it in New
 * Add it in loadXml
 *
 * Adding a new field:
 *  Add it to new
 *  Add a load function.
 */
// TODO later on read of the XML, fill out the missing part of the structure.
StorageSave::StorageSave(QObject *parent) : QObject(parent)
{
    // TOOD How will all those elements be deleted?
    tinyxml2::XMLElement *pElement;

    // https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
    // TODO Add the <!DOCTYPE ADVENTURE SYSTEM "story.dtd">
    m_pXmlDoc = new tinyxml2::XMLDocument;
    // TODO move all of this into a 'New()' function.
    tinyxml2::XMLElement *pRoot = m_pXmlDoc->NewElement("STORY");
    pRoot->SetAttribute("Version", "0.1.0");

    m_pXmlDoc->InsertFirstChild(pRoot);

    // Section for entries like project name etc.
    m_pGenerel = m_pXmlDoc->NewElement("Genrel");
    pRoot->InsertEndChild(m_pGenerel);

    // Section for entries like premise etc.
    m_pStoryDesign = m_pXmlDoc->NewElement("StoryDesign");
    pRoot->InsertEndChild(m_pStoryDesign);


    // -- GENEREL
    pElement = m_pXmlDoc->NewElement("ProjectName");
    m_pGenerel->InsertEndChild(pElement);
    pElement = m_pXmlDoc->NewElement("ProjectDescription");
    m_pGenerel->InsertEndChild(pElement);

    // -- STORYDESIGN
    pElement = m_pXmlDoc->NewElement("Premise");
    m_pStoryDesign->InsertEndChild(pElement);
} // end StorageSave::StorageSave


void StorageSave::setCurrentFileName(QString fileName) {
    // TODO any pre investigation?
    m_sXmlFilename = fileName;
}

/**
 * @brief StorageSave::getCurrentFileName
 * @return "" if not set(default filename) otherwise the
 */
QString StorageSave::getCurrentFileName() {
    QString sCurrentFileName = "";

    // if the default name is still in use, then just return ""
    if ( m_sXmlFilename != defaultFileName) {
        sCurrentFileName = m_sXmlFilename;
    }
    return(sCurrentFileName);
}


bool StorageSave::loadXml() {
    bool loadWorked = false;

    // XMLError is an enum
    tinyxml2::XMLError enumValue = m_pXmlDoc->LoadFile( m_sXmlFilename.toStdString().c_str() );
    if ( enumValue == tinyxml2::XML_SUCCESS ) {
        // TODO populate all the reference stuff
        tinyxml2::XMLElement *pRoot = m_pXmlDoc->RootElement();
        if ( pRoot != nullptr ) {
            qDebug() << "loadXml(): root element found";
            m_pGenerel = pRoot->FirstChildElement("Genrel");
            if ( m_pGenerel != nullptr ) {
                qDebug() << "loadXml(): Set m_pGenerel";
            }
            m_pStoryDesign = pRoot->FirstChildElement("StoryDesign");
            if ( m_pStoryDesign != nullptr ) {
                qDebug() << "loadXml(): Set m_pStoryDesign";
            }
        }
        loadWorked = true;
    }
    // TODO Possibly populate the missing entries in the XML?
    return(loadWorked);
}


bool StorageSave::saveXml() {
    bool saveWorked = false;

    // XMLError is an enum
    tinyxml2::XMLError enumValue = m_pXmlDoc->SaveFile( m_sXmlFilename.toStdString().c_str() );
    if ( enumValue == tinyxml2::XML_SUCCESS ) {
        saveWorked = true;
    }
    return(saveWorked);
}

QString StorageSave::getProjectName()
{
    QString textContent = "";
    tinyxml2::XMLElement * pElement = m_pGenerel->FirstChildElement("ProjectName");
    if (pElement != nullptr) {
        textContent = pElement->GetText();
    } else {
        qDebug() << "getProjectName(): TODO init the entry and save the XML?";
    }
    return(textContent);
}


QString StorageSave::getProjectDescription()
{
    QString textContent = "";
    tinyxml2::XMLElement * pElement = m_pGenerel->FirstChildElement("ProjectDescription");
    if (pElement != nullptr) {
        textContent = pElement->GetText();
    } else {
        qDebug() << "getProjectDescription(): TODO init the entry and save the XML?";
    }
    return(textContent);
}

QString StorageSave::getPremise()
{
    QString textContent = "";
    tinyxml2::XMLElement * pElement = m_pStoryDesign->FirstChildElement("Premise");
    if (pElement != nullptr) {
        textContent = pElement->GetText();
    } else {
        qDebug() << "getPremise(): TODO init the entry and save the XML?";
    }
    return(textContent);
}


void StorageSave::projectnameUpdate(QString sText) {
    qDebug() << "Called update for project name: " << sText;
    tinyxml2::XMLElement * pElement = m_pGenerel->FirstChildElement("ProjectName");
    if (pElement != nullptr) {
        pElement->SetText(sText.toStdString().c_str());
        saveXml();
    }
}

void StorageSave::projectdescriptionUpdate(QString sText) {
    tinyxml2::XMLElement * pElement = m_pGenerel->FirstChildElement("ProjectDescription");
    if (pElement != nullptr) {
        qDebug() << "projectdescriptionUpdate() Saving project description: " << sText;
        pElement->SetText(sText.toStdString().c_str());
        saveXml();
    }
}

void StorageSave::premiseUpdate(QString sText) {
    tinyxml2::XMLElement * pElement = m_pStoryDesign->FirstChildElement("Premise");
    if (pElement != nullptr) {
        qDebug() << "Saving Premise: " << sText;
        pElement->SetText(sText.toStdString().c_str());
        saveXml();
    }
}
