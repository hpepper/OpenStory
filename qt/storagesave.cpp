#include "storagesave.h"

#include <QDebug>


/* TODO When I start loading the data to load an existing char
 *   Disable the SaveXml() until the load is done, that way I can just fake the interfacething,
 *   that it seems Qt support.
 */

StorageSave::StorageSave(QObject *parent) : QObject(parent)
{
    //tinyxml2::XMLElement *pElement;

    // TODO Add the <!DOCTYPE ADVENTURE SYSTEM "story.dtd">
    m_pXmlDoc = new tinyxml2::XMLDocument;
    tinyxml2::XMLElement *pRoot = m_pXmlDoc->NewElement("ADVENTURE");
    pRoot->SetAttribute("Version", "0.1.0");

    m_pXmlDoc->InsertFirstChild(pRoot);

    /*
     * TODO
     * Add information about rule set, game world Creater, version
     *   Type of game etc.
     */
    // https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
    tinyxml2::XMLElement *pPrologue = m_pXmlDoc->NewElement("Prologue");
    pRoot->InsertFirstChild(pPrologue);


    tinyxml2::XMLElement *pCrawlText = m_pXmlDoc->NewElement("CrawlText");
    pRoot->InsertEndChild(pCrawlText);

} // end StorageSave::StorageSave


