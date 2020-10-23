/* 
 * Provided an indented status of how thing are going, what the status is.
 * 
 * Series - wip
 *   - SeriesBible - Missing.
 *   - Series 1 - wip
 *     - X missing (At the series level)
 *     - Season 1 - wip
 *       - Y missing(at the season level)
 *       - Episode 1 - wip
 *         - Z missing (at the episode level)
 *         - all the episode stuff
 */

#include <tinyxml2.h> // XML operations.
#include <string>

#include <getopt.h> // cli parms

#include <iostream> // std::cout

#include <filesystem> // path

std::string f_fileBasePath = "";

std::string getStringAttributeOfElement(tinyxml2::XMLElement *xmlElement, std::string attributeName, std::string defaultValue = "")
{
    std::string returnString = defaultValue;

    //std::cout << "DDD getStringAttributeOfElement(): " << attributeName << std::endl;

    if (xmlElement != nullptr)
    {
        const char *readAttributeValue = xmlElement->Attribute(attributeName.c_str());
        if (readAttributeValue != nullptr)
        {
            //std::cout << "DDD Attribute Value: " << readAttributeValue << std::endl;
            returnString = readAttributeValue;
        }
    }

    return (returnString);
}

/**
 * List all the attributes that the given element has.
 */
void listAllAttributes(tinyxml2::XMLElement *xmlElement)
{
    const tinyxml2::XMLAttribute *pAttrib = xmlElement->FirstAttribute();

    while (pAttrib)
    {
        std::cout << "DDD attibute: " << pAttrib->Name() << "  value: " << pAttrib->Value() << std::endl;
        std::string attributeName = pAttrib->Name();
        std::cout << "DDD get it: " << getStringAttributeOfElement(xmlElement, attributeName) << std::endl;
        pAttrib = pAttrib->Next();
    }
}

int showSeriesBibleStatus(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;

    if (xmlElement == nullptr)
    {
        std::cout << "    SeriesBible: No entry" << std::endl;
    }
    else
    {
        std::string seriesBibleFilename = "";

        const char *attribubteContent = xmlElement->Attribute("Filename");
        if (attribubteContent != nullptr)
        {
            seriesBibleFilename = attribubteContent;
        }
        else
        {
            std::cerr << "EEE atribute not found" << std::endl;
        }

        if (seriesBibleFilename == "")
        {
            std::cout << "    SeriesBible: No entry" << std::endl;
        }
        else
        {
            std::cout << " TODO Implement handling series bible; filename:" << seriesBibleFilename << std::endl;
        }
    }

    return (nStatus);
}

int showStatusGenericElement(tinyxml2::XMLElement *xmlElement, std::string subElementName, std::string textIndent)
{
    int nStatus = 0;

    //std::cout << "DDD showStatusGenericElement(" << subElementName << ")" << std::endl;
    tinyxml2::XMLElement *xmlGenericElement = xmlElement->FirstChildElement(subElementName.c_str());
    if (xmlGenericElement == nullptr)
    {
        std::cout << textIndent << subElementName << ": - not defined" << std::endl;
    }
    else
    {
        std::cout << textIndent << subElementName << ": ";
        std::string statusAttribute = "";

        // if 'Status' attribute is 'Done'
        const char *attributeContent = xmlGenericElement->Attribute("Status");
        if (attributeContent != nullptr)
        {
            statusAttribute = attributeContent;
        }

        if ((statusAttribute.compare("Done") == 0) || (statusAttribute.compare("done") == 0))
        {
            std::cout << "Done compare";
        }
        else
        {
            // if empty
            std::string elementContent = "";
            const char *charContent = xmlGenericElement->GetText();
            if (charContent != nullptr)
            {
                elementContent = charContent;
            }

            if (elementContent.compare("") == 0)
            {
                std::cout << "Missing";
            }
            // if contain TODO
            else if (elementContent.find("TODO") != std::string::npos)
            {
                std::cout << "Done (with find)";
            }
            else
            {
                std::cout << "Done (default)";
            }
        }
        std::cout << std::endl;
    }
    return (nStatus);
}

int showStoryDesignStatus(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;

    tinyxml2::XMLElement *xmlStoryDesign = xmlElement->FirstChildElement("StoryDesign");
    if (xmlStoryDesign == nullptr)
    {
        std::cout << "StoryDesign: - none defined" << std::endl;
    }
    else
    {
        std::cout << "    StoryDesign" << std::endl;
        nStatus = showStatusGenericElement(xmlStoryDesign, "Motif", "      ");
        // TODO Possibly these are in the Pantheon?
        nStatus = showStatusGenericElement(xmlStoryDesign, "Characters", "      ");
        nStatus = showStatusGenericElement(xmlStoryDesign, "Antagonists", "      ");

        tinyxml2::XMLElement *xmlPremise = xmlStoryDesign->FirstChildElement("Premise");
        if (xmlPremise == nullptr)
        {
            std::cout << "Premise: - none defined" << std::endl;
        }
        else
        {
            std::cout << "      Premise" << std::endl;
            nStatus = showStatusGenericElement(xmlStoryDesign, "Premise", "        ");
            nStatus = showStatusGenericElement(xmlPremise, "EndResult", "        ");
        }

        tinyxml2::XMLElement *xmlCentralIssue = xmlStoryDesign->FirstChildElement("CentralIssue");
        if (xmlCentralIssue == nullptr)
        {
            std::cout << "CentralIssue: - none defined" << std::endl;
        }
        else
        {
            std::cout << "      CentralIssue" << std::endl;
            nStatus = showStatusGenericElement(xmlStoryDesign, "CentralIssue", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatIsTheCentralQuestionIWantToExplore", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "HowDoIWantTheAudienceToRespondToTheStory", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatDoesTheHeroineWant", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatDoesTheHeroineExpectToAchieve", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheHeroineFails", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheHeroineSucceed", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatIsTheHeroineQuestingAfter", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatDoesTheHeroineNeed", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatDoesTheAntagonistWant", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatDoesTheAntagonistExpectToAchieve", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheAntagonistFails", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheAntagonistSucceed", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatDoesTheAntagonistNeed", "        ");
            nStatus = showStatusGenericElement(xmlCentralIssue, "WhatIsTheConflict", "        ");
        }
        tinyxml2::XMLElement *xmlStoryProfile = xmlStoryDesign->FirstChildElement("StoryProfile");
        if (xmlStoryProfile == nullptr)
        {
            std::cout << "StoryProfile: - none defined" << std::endl;
        }
        else
        {
            std::cout << "      StoryProfile" << std::endl;
            nStatus = showStatusGenericElement(xmlStoryDesign, "StoryProfile", "        ");
            nStatus = showStatusGenericElement(xmlStoryProfile, "Mood", "        ");
            nStatus = showStatusGenericElement(xmlStoryProfile, "Tone", "        ");
            nStatus = showStatusGenericElement(xmlStoryProfile, "Theme", "        ");
            nStatus = showStatusGenericElement(xmlStoryProfile, "LogLine", "        ");
        }
    }

    return (nStatus);
}

std::string getStringContentOfNamedSubElement(tinyxml2::XMLElement *xmlElement, std::string subElementName, std::string defaultValue = "")
{
    std::string returnString = defaultValue;

    if (xmlElement != nullptr)
    {
        tinyxml2::XMLElement *xmlSubElement = xmlElement->FirstChildElement(subElementName.c_str());
        if (xmlSubElement != nullptr)
        {
            const char *readElementContent = xmlSubElement->GetText();
            if (readElementContent != nullptr)
            {
                returnString = readElementContent;
            }
        }
    }

    return (returnString);
}

tinyxml2::XMLElement *getRootElementOfXmlFile(std::string filename)
{
    tinyxml2::XMLElement *xmlReturnElementPointer = nullptr;

    tinyxml2::XMLDocument *xmlSeasonDoc = new tinyxml2::XMLDocument();
    tinyxml2::XMLError enumValue = xmlSeasonDoc->LoadFile(filename.c_str());
    if (enumValue == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLElement *xmlRoot = xmlSeasonDoc->RootElement();
        if (xmlRoot != nullptr)
        {
            xmlReturnElementPointer = xmlRoot;
        }
        else
        {
            std::cerr << "!!! root XML element not found: " << filename << std::endl;
        }
    }
    else
    {
        std::cout << "!!! failing loading: " << filename << std::endl;
        xmlSeasonDoc->PrintError();
    }
    return (xmlReturnElementPointer);
}

int showSceneListStatus(tinyxml2::XMLElement *xmlEncounter)
{
    int nStatus = 0;

    std::string textIndent = "            ";

    // itterate through the scenes
    tinyxml2::XMLElement *xmlScene = xmlEncounter->FirstChildElement("Scene");
    while (xmlScene != nullptr)
    {
        std::cout << "          Scene: ";
        // get id attr
        std::string identifier = getStringAttributeOfElement(xmlScene, "Id");
        // get filename attr
        std::string encounterName = getStringAttributeOfElement(xmlScene, "Name");
        std::cout << identifier << " - " << encounterName << std::endl;

        nStatus = showStatusGenericElement(xmlScene, "BehindTheScene", textIndent);
        std::cout << textIndent << "Site: ";
        tinyxml2::XMLElement *xmlSite = xmlScene->FirstChildElement("Site");
        if (xmlSite != nullptr)
        {
            std::string siteName = getStringAttributeOfElement(xmlScene, "Name");
            if (siteName.length() > 0)
            {
                std::cout << "Done";
            }
            else
            {
                std::cout << "Missing";
            }
        }
        else
        {
            std::cout << "Missing";
        }
        std::cout << std::endl;

        int nNumberOfActors = 0;
        // itterate through the scenes
        tinyxml2::XMLElement *xmlActor = xmlScene->FirstChildElement("Actor");
        while (xmlActor != nullptr)
        {
            nNumberOfActors++;
            std::string actorName = getStringAttributeOfElement(xmlActor, "Name");
            std::string actorFilename = getStringAttributeOfElement(xmlActor, "File");
            std::string actorNumberOfUnits = getStringAttributeOfElement(xmlActor, "Units");
            std::cout << "            Actor: " << actorName << " (" << actorNumberOfUnits << ")";
            if ((actorName.length() == 0) || (actorFilename.length() == 0) || (actorNumberOfUnits.length() == 0))
            {
                std::cout << " Missing";
            }
            std::cout << std::endl;
            xmlActor = xmlActor->NextSiblingElement("Actor");
        }
        if (nNumberOfActors == 0)
        {
            std::cout << "            Actor: Missing" << std::endl;
        }

        nStatus = showStatusGenericElement(xmlScene, "TellItToThemStraight", textIndent);
        nStatus = showStatusGenericElement(xmlScene, "Debugging", textIndent);
        nStatus = showStatusGenericElement(xmlScene, "Temperature", textIndent);
        nStatus = showStatusGenericElement(xmlScene, "TimeOfDay", textIndent);
        nStatus = showStatusGenericElement(xmlScene, "SoundTrack", textIndent);
        nStatus = showStatusGenericElement(xmlScene, "SnatchOfDialog", textIndent);
        xmlScene = xmlScene->NextSiblingElement();
    }

    return (nStatus);
}
int showSessionStatus(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;

    nStatus = showStatusGenericElement(xmlElement, "Prologue", "        ");
    nStatus = showStatusGenericElement(xmlElement, "CrawlText", "        ");

    // itterate through the encounters
    tinyxml2::XMLElement *xmlEncounter = xmlElement->FirstChildElement("Encounter");
    while (xmlEncounter != nullptr)
    {
        //listAllAttributes(xmlSession);
        std::cout << "        Encounter: ";
        // get id attr
        std::string identifier = getStringAttributeOfElement(xmlEncounter, "Id");
        // get filename attr
        std::string encounterName = getStringAttributeOfElement(xmlEncounter, "Name");
        std::cout << identifier << " - " << encounterName << std::endl;
        showSceneListStatus(xmlEncounter);
        xmlEncounter = xmlEncounter->NextSiblingElement();
    }

    return (nStatus);
}

int showSeasonPlanStatus(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;

    tinyxml2::XMLElement *xmlSeasonPlan = xmlElement->FirstChildElement("SeasonPlan");
    if (xmlSeasonPlan == nullptr)
    {
        std::cout << "SeasonPlan: - none defined" << std::endl;
    }
    else
    {
        std::cout << "    SeasonPlan: " << std::endl;
        // itterate through the sessions
        tinyxml2::XMLElement *xmlSession = xmlSeasonPlan->FirstChildElement("Session");
        while (xmlSession != nullptr)
        {
            //listAllAttributes(xmlSession);
            std::cout << "      Session: ";
            // get id attr
            std::string identifier = getStringAttributeOfElement(xmlSession, "Id");
            // get filename attr
            std::string filename = getStringAttributeOfElement(xmlSession, "Filename");
            // get note
            std::string sessionNote = getStringContentOfNamedSubElement(xmlSession, "Note");
            std::cout << identifier << " - " << sessionNote << std::endl;
            xmlSession = xmlSession->NextSiblingElement();

            if (filename.length() > 0)
            {
                std::cout << "      DDD Filename: " << filename << "  base path: " << f_fileBasePath << std::endl;
                tinyxml2::XMLElement *xmlSessionXmlFileElement = getRootElementOfXmlFile(f_fileBasePath + "/" + filename);
                if (xmlSessionXmlFileElement != nullptr)
                {
                    showSessionStatus(xmlSessionXmlFileElement);
                }
            }
        }
    }
    return (nStatus);
}

int showSeasonStatus(tinyxml2::XMLElement *xmlElement, std::string basePath)
{
    int nStatus = 0;

    std::string filename = "";

    const char *attribubteContent = xmlElement->Attribute("Filename");
    if (attribubteContent != nullptr)
    {
        filename = attribubteContent;
    }
    else
    {
        std::cerr << "EEE 'Filename' atribute not found" << std::endl;
    }

    if (filename == "")
    {
        std::cout << "    Season filename: No entry" << std::endl;
    }
    else
    {
        std::cout << " TODO Implement handling season; filename:" << filename << std::endl;
        tinyxml2::XMLDocument *xmlSeasonDoc = new tinyxml2::XMLDocument();
        std::string seasonFullpathFilename = basePath + "/" + filename;
        tinyxml2::XMLError enumValue = xmlSeasonDoc->LoadFile(seasonFullpathFilename.c_str());
        if (enumValue == tinyxml2::XML_SUCCESS)
        {
            tinyxml2::XMLElement *xmlRoot = xmlSeasonDoc->RootElement();
            if (xmlRoot != nullptr)
            {
                // StoryDesign
                showStoryDesignStatus(xmlRoot);
                // TODO Pantheon (should this go into the bible? or is this the pantheon, for only this season. and if a character will be used in later season, only then will it go into the bible?)
                // SeasonPlan
                showSeasonPlanStatus(xmlRoot);
            }
            else
            {
                std::cerr << "!!! root XML element not found: " << seasonFullpathFilename << std::endl;
            }
        }
        else
        {
            std::cout << "!!! failing loading: " << seasonFullpathFilename << std::endl;
            xmlSeasonDoc->PrintError();
        }
    }

    return (nStatus);
}

int showSeriesStatus(tinyxml2::XMLElement *xmlRoot, std::string basePath)
{
    int nStatus = 0;

    // TODO get bible
    tinyxml2::XMLElement *xmlSeriesBibleElement = xmlRoot->FirstChildElement("SeriesBible");
    nStatus = showSeriesBibleStatus(xmlSeriesBibleElement);

    // TODO go through seasons
    tinyxml2::XMLElement *xmlSeasonElement = xmlRoot->FirstChildElement("Season");
    if (xmlSeasonElement == nullptr)
    {
        std::cout << "Season: - none defined" << std::endl;
    }
    while (xmlSeasonElement)
    {
        nStatus = showSeasonStatus(xmlSeasonElement, basePath);
        // TODO find next
        xmlSeasonElement = xmlSeasonElement->NextSiblingElement();
    }

    return (nStatus);
}

int main(int argc, char *argv[])
{

    std::string fileNameXml = "series.xml";

    const char *const short_opts = "hi:";
    const option long_opts[] = {
        {"seriesfile", required_argument, nullptr, 'i'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}};

    int index;
    int opt = 0;
    while (opt != -1)
    {
        // TODO FAIL if unexpected parms are provided

        opt = getopt_long(argc, argv, short_opts, long_opts, &index);

        switch (opt)
        {
        case 'i':
            fileNameXml = optarg;
            break;
        }
    }

    std::cout << "DDD filename: " << fileNameXml << std::endl;

    std::filesystem::path pathForSeriesFile{fileNameXml};

    std::string directoryPathToSeriesFile = "./";

    if (pathForSeriesFile.has_parent_path())
    {
        directoryPathToSeriesFile = pathForSeriesFile.parent_path().string();
    }

    std::cout << "DDD path: " << directoryPathToSeriesFile << std::endl;

    tinyxml2::XMLDocument *xmlDoc = new tinyxml2::XMLDocument();
    tinyxml2::XMLError enumValue = xmlDoc->LoadFile(fileNameXml.c_str());
    if (enumValue == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLElement *xmlRoot = xmlDoc->RootElement();
        if (xmlRoot != nullptr)
        {
            f_fileBasePath = directoryPathToSeriesFile; // todo make the 'directoryPathToSeriesFile' var the gloabl one
            showSeriesStatus(xmlRoot, directoryPathToSeriesFile);
        }
        else
        {
            std::cerr << "!!! root XML element not found" << std::endl;
        }
    }
}