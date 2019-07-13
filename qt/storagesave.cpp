#include "storagesave.h"

#include <QDebug>


/* TODO When I start loading the data to load an existing char
 *   Disable the SaveXml() until the load is done, that way I can just fake the interfacething,
 *   that it seems Qt support.
 */

// TODO Later handle that it might be a newer version of XML being read in.
/** Currently The whole structure is created here.
 */
// TODO later on read of the XML, fill out the missing part of the structure.
StorageSave::StorageSave(QObject *parent) : QObject(parent)
{
    // TOOD How will all those elements be deleted?
    tinyxml2::XMLElement *pElement;

    // https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
    // TODO Add the <!DOCTYPE ADVENTURE SYSTEM "story.dtd">
    m_pXmlDoc = new tinyxml2::XMLDocument;
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


void StorageSave::saveXml() {
    m_pXmlDoc->SaveFile( m_sXmlFilename.toStdString().c_str() );
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
        qDebug() << "Saving project description: " << sText;
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
