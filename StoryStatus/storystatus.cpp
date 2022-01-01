/* 
 * Provided an indented status of how thing are going, what the status is.
 * 
 * Series - wip
 *   - SeriesHandbook - Missing.
 *   - Series 1 - wip
 *     - X missing (At the series level)
 *     - Season 1 - wip
 *       - Y missing(at the season level)
 *       - Episode 1 - wip
 *         - Z missing (at the episode level)
 *         - all the episode stuff
 */

#include <assert.h>
#include <tinyxml2.h> // XML operations.
#include <string>
#include <vector>

#include <getopt.h> // cli parms

#include <iostream> // std::cout

#include <filesystem> // path

#include <map> // list

#include <math.h> // ceil

#include <utility> // std::pair

std::string f_fileBasePath = "";

std::string versionText = "0.1.3";

tinyxml2::XMLDocument *f_xmlDoc = nullptr;

std::map<std::string, bool> f_mapCharacterDefinitions;

std::vector<std::string> listOfPlayers = {"Player1", "Player2"};

int f_numberOfPlayers = listOfPlayers.size();
int f_totalNumberOfScenes = 40;
int f_scenesPerSession = 3;

// Ceil; always round up
int f_numberOfSessions = ceil((1.0 * f_totalNumberOfScenes) / f_scenesPerSession);

// From Day 11 - Plot diagram
std::map<int, std::string> f_mapScenePurpose = {
    {1, "Expostion/Teaser - Hook the reader, show the environment"},
    {2, "Opening - Leads the main character to a conflict. Central question that you'll be exploring throughout the movie."},
    {3, "Meet the main antagonist or someone/something symbolicing the main antagonist"},
    {4, "The deflector character slows the main character down. Pulls the main character off path."},
    {5, "Inciting event - Begins the plot"},
    {6, "The main characters challenge is made clear to the audience."},
    {7, "Ally aids main character proppel main character out of status quo."},
    {8, "The main character is offered to move forwards, but the main character sees themselves as held back, in the current context(perspective)."},
    {9, "The antagonist or deflector conflict stops the main character or threatens emotional stakes."},
    {10, "Show severerity of threat"},
    {11, "Rising - This is the event that pushes the Lead from the comfortable daily life, into a new territory. ∗ Deflector or antagonist threats to take the stakes character."},
    {12, "The main character decides that they must act to save the Stakes Character"},
    {13, "Complication - Opponent's plan and main counterattack"},
    {14, "yes - The main character begins the learning process, actively pursuing what they thinks is needed to resolve the Central Question while getting an insight into what will really be needed to resolve the Central Question"},
    {15, "no - The main character will meet with low-level opposition which they will struggle to barely overcome. These can be considered 'training exercises' or 'dry runs' for the skills and/or insights that the hero will really need."},
    {16, "TODO there is an off on the yes/no series"},
    {17, "yes3"},
    {18, "no3 - the opposition to the heroʼs goal will be shown to be a very strong opposition."},
    {19, "yes5 - The main character continues to wander, learning with greater clarity what he or she needs to do to resolve the Central Question while testing the waters with their nascent abilities."},
    {20, "no5 - The opposition to the main character becomes aware of the main characters existence"},
    {21, "yes6"},
    {22, "no6 - The opposite value of the theme is clearly stated"},
    {23, "yes7 - The third act solution is shown, though the significance of it is likely lost on the hero at this time."},
    {24, "no7 - Moral argument:(13)Attack by ally"},
    {25, "yes8 - The main character will meet with some initial success."},
    {26, "no8 - The villain/opposing force will tighten the screws on the heroʼs goal"},
    {27, "yes9"},
    {28, "no9"},
    {29, "yes10"},
    {30, "no10"},
    {31, "yes12 - Intense, direct conflict between the main character and the opposing force/villain"},
    {32, "Trouble - no12- Plot:(14)Apparent defeat"},
    {33, "yes13 - The main character emerges from the death-moment (resurrection) a new being, more fully actualized, with a new understanding, but not quite ready for the final challenge yet"},
    {34, "Falling - No13 - The main character believes they have lost the goal and their opponent has won"},
    {35, "Prepare - Yes14 - So at this point the main charcter gets a new piece of information that shows them that victory is possible"},
    {36, "No14 - Whatever answers the question “Whatʼs the worst that can happen?”, happens. The villain gains the ultimate upper hand."},
    {37, "BigYes - (17)Third revelation and decision. The main character, having embraced the positive thematic argument, makes a commitment to change. This sets up the resolution to the Private Conflict."},
    {38, "No - The main character meets with failure, but instead of licking their wounds, the main character presses on"},
    {39, "BigNo - (18)Gate, Gauntlet, visit to death - Finally the main character must; either; pass through a narrow gate or; travel down a long gauntlet"},
    {40, "FinalYes"}};

/// This lists the key scene names and maps the scene numbers to the KeyScene names.
std::map<int, std::string> f_mapKeySceneNumberssToSceneName = {
    {1, "Exposition"},
    {2, "Opening"},
    {5, "Incident"},
    {11, "TurningPoint"},
    {13, "Complication"},
    {32, "Trouble"},
    {34, "AllSeemsLost"},
    {35, "Prepare"},
    {40, "ResolutionEducation"}};

/// This map is used for loading the key scene definitions, read from the 'TenMinutteMovie' section
std::map<std::string, std::string> f_mapKeySceneNameToDescription = {
    {"Exposition", ""},
    {"Opening", ""},
    {"Incident", ""},
    {"TurningPoint", ""},
    {"Complication", ""},
    {"Trouble", ""},
    {"AllSeemsLost", ""},
    {"Prepare", ""},
    {"ResolutionEducation", ""}};

int f_currentActNumber = 0;

bool f_numberOfSessionsHasBeenModified = false;

void adjustTheNumberOfSessions()
{
    if (!f_numberOfSessionsHasBeenModified)
    {
        if (f_numberOfSessions > int(f_totalNumberOfScenes / f_scenesPerSession))
        {
            f_numberOfSessions = int(f_totalNumberOfScenes / f_scenesPerSession) + 1;
        }
        f_numberOfSessionsHasBeenModified = true;
    }
}

void deleteelementIfExists(tinyxml2::XMLElement *xmlElement, std::string elementName)
{
    tinyxml2::XMLElement *xmlResultElement = xmlElement->FirstChildElement(elementName.c_str());
    if (xmlResultElement != nullptr)
    {
        xmlElement->DeleteChild(xmlResultElement);
    }
}

// These are used to when creating a new PlotPlan, by enabling reading the
//  old plot plan and enabling add the old info to the new structure.
std::map<int, tinyxml2::XMLElement *> f_mapSceneIdToXmlElement;
std::map<int, tinyxml2::XMLElement *> f_mapSequenceIdToXmlElement;

std::map<int, std::string> f_mapPlayerCharacters;

std::string getStringAttributeOfElement(tinyxml2::XMLElement *xmlElement, std::string attributeName, std::string defaultValue = "")
{
    std::string returnString = defaultValue;

    if (xmlElement != nullptr)
    {
        const char *readAttributeValue = xmlElement->Attribute(attributeName.c_str());
        if (readAttributeValue != nullptr)
        {
            returnString = readAttributeValue;
        }
    }

    return (returnString);
}

int loadPlayerList(tinyxml2::XMLElement *xmlRoot)
{
    int nStatus = 0;
    tinyxml2::XMLElement *xmlHeadingElement = xmlRoot->FirstChildElement("PlayerCharacters");
    if (xmlHeadingElement != nullptr)
    {
        int nIndex = 1;
        tinyxml2::XMLElement *xmlPlayer = xmlHeadingElement->FirstChildElement("Character");
        while (xmlPlayer != nullptr)
        {
            std::string actorName = getStringAttributeOfElement(xmlPlayer, "Name");
            f_mapPlayerCharacters[nIndex] = actorName;
            nIndex++;
            xmlPlayer = xmlPlayer->NextSiblingElement("Character");
        }
    }
    return (nStatus);
}

int getActNumberForSceneNumber(int sceneNumber)
{
    int returnActNumber = 0;
    if ((sceneNumber >= 1) && (sceneNumber <= 12))
    {
        returnActNumber = 1;
    }
    else if ((sceneNumber >= 13) && (sceneNumber <= 36))
    {
        returnActNumber = 2;
    }
    else if (sceneNumber >= 37)
    {
        returnActNumber = 3;
    }

    return (returnActNumber);
}

std::string getSceneSeed(int sceneNumber)
{
    std::string sceneSeed = "";
    std::string keySceneName = "";

    std::map<int, std::string>::iterator it = f_mapKeySceneNumberssToSceneName.find(sceneNumber);
    if (it != f_mapKeySceneNumberssToSceneName.end())
    {
        keySceneName = it->second;
        std::cout << " keySceneName: '" << keySceneName << "' ";
    }
    if (keySceneName != "")
    {
        std::map<std::string, std::string>::iterator it = f_mapKeySceneNameToDescription.find(keySceneName);
        if (it != f_mapKeySceneNameToDescription.end())
        {
            sceneSeed = it->second;
            std::cout << " sceneSeed: '" << sceneSeed << "'";
        }
    }
    std::cout << std::endl;
    return (sceneSeed);
}

tinyxml2::XMLElement *generateScene(tinyxml2::XMLElement *xmlSession, int sessionNumber, int sceneNumber, tinyxml2::XMLElement *parentElement)
{
    // TODO parent must fill out the session structure.
    //tinyxml2::XMLElement *xmlScene = new tinyxml2::XMLElement();
    //new off of the parent

    int currentActNumber = getActNumberForSceneNumber(sceneNumber);
    tinyxml2::XMLElement *xmlScene = xmlSession->InsertNewChildElement("Scene");
    xmlSession->SetAttribute("Id", sceneNumber);
    xmlSession->SetAttribute("Name", "");
    xmlSession->SetAttribute("Act", currentActNumber);
    xmlSession->SetAttribute("Session", sessionNumber);
    // Add entry for the scene purpose
    // Add entry for optional design note for scene if it is the Ricing, Prepare etc.
    std::string sceneSeedDescription = getSceneSeed(sceneNumber);
    tinyxml2::XMLElement *xmlElement = nullptr;
    if (sceneSeedDescription != "")
    {
        xmlElement = xmlScene->InsertNewChildElement("Seed");
        xmlElement->InsertNewText(sceneSeedDescription.c_str());
    }
    std::map<int, std::string>::iterator it = f_mapScenePurpose.find(sceneNumber);
    if (it != f_mapScenePurpose.end())
    {
        xmlElement = xmlScene->InsertNewChildElement("Purpose");
        xmlElement->InsertNewText((it->second).c_str());
    }
    xmlElement = xmlScene->InsertNewChildElement("Time");
    xmlElement = xmlScene->InsertNewChildElement("Intensity");
    xmlElement = xmlScene->InsertNewChildElement("Location");
    xmlElement = xmlScene->InsertNewChildElement("Storyline");
    xmlElement = xmlScene->InsertNewChildElement("CentralIssue");
    xmlElement = xmlScene->InsertNewChildElement("ScenePurpose");
    // Always include 'PCs'
    xmlElement = xmlScene->InsertNewChildElement("Character");
    xmlElement->SetAttribute("Name", "");
    xmlElement->SetAttribute("Units", 0);
    for (int playerIndex = 0; playerIndex < listOfPlayers.size(); playerIndex++)
    {
        xmlElement = xmlScene->InsertNewChildElement("Character");
        xmlElement->SetAttribute("Name", listOfPlayers[playerIndex].c_str());
        xmlElement->SetAttribute("Units", 1);
    }
    xmlElement = xmlScene->InsertNewChildElement("Synopsis");
    xmlElement = xmlScene->InsertNewChildElement("SnatchOfDialog");
    xmlElement = xmlScene->InsertNewChildElement("SceneConnections");
    xmlElement = xmlScene->InsertNewChildElement("TellItStraight");
    xmlElement = xmlScene->InsertNewChildElement("Hooks");
    xmlElement = xmlScene->InsertNewChildElement("Behind");
    xmlElement = xmlScene->InsertNewChildElement("Debugging");
    return (NULL);
}

// maybe the return should be the XML thingy
int generateSession(tinyxml2::XMLElement *xmlPlotDiagram, int nSessionId, std::string primary, std::string secondary)
{
    tinyxml2::XMLElement *xmlSession = xmlPlotDiagram->InsertNewChildElement("Session");
    xmlSession->SetAttribute("Id", nSessionId);
    xmlSession->SetAttribute("Primary", primary.c_str());
    xmlSession->SetAttribute("Secondary", secondary.c_str());
    // DELETE std::cout << "  <Session Id=\"" << nSessionId << "\" Primary=\"" << primary << "\" Secondary=\"" << secondary << "\" Filename=\"\">" << std::endl;
    // TODO add sequence
    // itterate through scenes (and sequences)
    int startSceneNumber = (nSessionId - 1) * f_scenesPerSession;
    for (int sceneOffset = 1; sceneOffset <= f_scenesPerSession; sceneOffset++)
    {
        generateScene(xmlSession, nSessionId, startSceneNumber + sceneOffset, NULL);
    }
    std::cout << "  </Session>" << std::endl;
    return (0);
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

int showSeriesHandbookStatus(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;

    if (xmlElement == nullptr)
    {
        std::cout << "    SeriesHandbook: No entry" << std::endl;
    }
    else
    {
        std::string seriesHandbookFilename = "";

        const char *attribubteContent = xmlElement->Attribute("Filename");
        if (attribubteContent != nullptr)
        {
            seriesHandbookFilename = attribubteContent;
        }
        else
        {
            std::cerr << "EEE " << __FILE__ << "(" << __LINE__ << ")"
                      << "atribute not found" << std::endl;
        }

        if (seriesHandbookFilename == "")
        {
            std::cout << "    SeriesHandbook: No entry" << std::endl;
        }
        else
        {
            std::cout << " TODO Implement handling series Handbook; filename:" << seriesHandbookFilename << std::endl;
        }
    }

    return (nStatus);
}

std::string showStatusGenericElement(tinyxml2::XMLElement *xmlElement, std::string subElementName, std::string textIndent)
{
    std::string elementContent = "";

    tinyxml2::XMLElement *xmlGenericElement = xmlElement->FirstChildElement(subElementName.c_str());
    if (xmlGenericElement == nullptr)
    {
        std::cout << textIndent << subElementName << ": - not defined" << std::endl;
    }
    else
    {
        const char *charContent = xmlGenericElement->GetText();
        if (charContent != nullptr)
        {
            elementContent = charContent;
        }

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
            if (elementContent.length() == 0)
            {
                std::cout << "Missing";
            }
            // if contain TODO
            else if ((elementContent.find("TODO") != std::string::npos) || (elementContent.find("XXX") != std::string::npos))
            {
                std::cout << "There are TODOs";
            }
            else
            {
                std::cout << "Done";
            }
        }
        std::cout << std::endl;
    }
    return (elementContent);
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
        showStatusGenericElement(xmlStoryDesign, "Motif", "      ");
        // TODO Possibly these are in the Pantheon?
        showStatusGenericElement(xmlStoryDesign, "Characters", "      ");
        showStatusGenericElement(xmlStoryDesign, "Antagonists", "      ");

        // TODO expand Premise
        tinyxml2::XMLElement *xmlPremise = xmlStoryDesign->FirstChildElement("Premise");
        if (xmlPremise == nullptr)
        {
            std::cout << "Premise: - none defined" << std::endl;
        }
        else
        {
            std::cout << "      Premise" << std::endl;
            showStatusGenericElement(xmlStoryDesign, "Premise", "        ");
            showStatusGenericElement(xmlPremise, "EndResult", "        ");
        }

        tinyxml2::XMLElement *xmlCentralIssue = xmlStoryDesign->FirstChildElement("CentralIssue");
        if (xmlCentralIssue == nullptr)
        {
            std::cout << "CentralIssue: - none defined" << std::endl;
        }
        else
        {
            std::cout << "      CentralIssue" << std::endl;
            showStatusGenericElement(xmlStoryDesign, "CentralIssue", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatIsTheCentralQuestionIWantToExplore", "        ");
            showStatusGenericElement(xmlCentralIssue, "HowDoIWantTheAudienceToRespondToTheStory", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatDoesTheHeroineWant", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatDoesTheHeroineExpectToAchieve", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheHeroineFails", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheHeroineSucceed", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatIsTheHeroineQuestingAfter", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatDoesTheHeroineNeed", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatDoesTheAntagonistWant", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatDoesTheAntagonistExpectToAchieve", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheAntagonistFails", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatHappensIfTheAntagonistSucceed", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatDoesTheAntagonistNeed", "        ");
            showStatusGenericElement(xmlCentralIssue, "WhatIsTheConflict", "        ");
        }
        tinyxml2::XMLElement *xmlStoryProfile = xmlStoryDesign->FirstChildElement("StoryProfile");
        if (xmlStoryProfile == nullptr)
        {
            std::cout << "StoryProfile: - none defined" << std::endl;
        }
        else
        {
            std::cout << "      StoryProfile" << std::endl;
            showStatusGenericElement(xmlStoryDesign, "StoryProfile", "        ");
            showStatusGenericElement(xmlStoryProfile, "Mood", "        ");
            showStatusGenericElement(xmlStoryProfile, "Tone", "        ");
            showStatusGenericElement(xmlStoryProfile, "Theme", "        ");
            showStatusGenericElement(xmlStoryProfile, "LogLine", "        ");
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

int showSceneListStatus(tinyxml2::XMLElement *xmlEncounter, bool forPlotDiagram = false)
{
    int nStatus = 0;

    std::string textIndent = "                ";

    // itterate through the scenes
    tinyxml2::XMLElement *xmlScene = xmlEncounter->FirstChildElement("Scene");
    while (xmlScene != nullptr)
    {
        std::cout << "            Scene: ";
        // get id attr
        std::string identifier = getStringAttributeOfElement(xmlScene, "Id");
        // get filename attr
        std::string encounterName = getStringAttributeOfElement(xmlScene, "Name");

        if (encounterName.compare("") == 0)
        {
            encounterName = "Missing scene name";
        }

        std::cout << identifier << " - " << encounterName << std::endl;
        // TODO do Intensity if plot diagram

        if (!forPlotDiagram)
        {
            // TODO should 'behind the scene' be part of the plot diagram
            showStatusGenericElement(xmlScene, "BehindTheScene", textIndent);

            // TODO Do a dive into the planet xml file and investigate it.
            std::cout << textIndent << "Planet: ";
            tinyxml2::XMLElement *xmlPlanet = xmlScene->FirstChildElement("Planet");
            if (xmlPlanet != nullptr)
            {
                std::string planetName = getStringAttributeOfElement(xmlPlanet, "File");
                if (planetName.length() > 0)
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

            std::cout << textIndent << "Site: ";
            tinyxml2::XMLElement *xmlSite = xmlScene->FirstChildElement("Site");
            if (xmlSite != nullptr)
            {
                std::string siteName = getStringAttributeOfElement(xmlSite, "Name");
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
        }
        int nNumberOfActors = 0;
        // itterate through the scenes
        tinyxml2::XMLElement *xmlActor = xmlScene->FirstChildElement("Character");
        while (xmlActor != nullptr)
        {
            nNumberOfActors++;
            std::string actorName = getStringAttributeOfElement(xmlActor, "Name");

            std::string actorFilename = "DoesNotExists";
            if (!forPlotDiagram)
            {
                actorFilename = getStringAttributeOfElement(xmlActor, "File");
                std::cout << "DDD actor defined in file: " << actorName << " - '" << actorFilename << "'" << std::endl;
            }
            else if (f_mapCharacterDefinitions.count(actorName) == 0)
            {
                actorFilename = "";
            }
            std::string actorNumberOfUnits = getStringAttributeOfElement(xmlActor, "Units");
            std::cout << textIndent << "Character: " << actorName << " (" << actorNumberOfUnits << ")";
            // TODO only test for actorname when plotdiagram or maybe check the character exists in the characterweb?
            if ((actorName.length() == 0) || (actorFilename.length() == 0) || (actorNumberOfUnits.length() == 0))
            {
                std::cout << " Missing";
            }
            else
            {
                std::cout << " Done";
            }
            std::cout << std::endl;
            xmlActor = xmlActor->NextSiblingElement("Character");
        }
        if (nNumberOfActors == 0)
        {
            std::cout << textIndent << "Character: Missing" << std::endl;
        }

        if (forPlotDiagram)
        {
            showStatusGenericElement(xmlScene, "Synopsis", textIndent);
        }
        else
        {
            showStatusGenericElement(xmlScene, "TellItToThemStraight", textIndent);
            showStatusGenericElement(xmlScene, "Debugging", textIndent);
            showStatusGenericElement(xmlScene, "Smell", textIndent);
            showStatusGenericElement(xmlScene, "Temperature", textIndent);
            showStatusGenericElement(xmlScene, "TimeOfDay", textIndent);
            showStatusGenericElement(xmlScene, "SoundTrack", textIndent);
            showStatusGenericElement(xmlScene, "SnatchOfDialog", textIndent);
        }

        xmlScene = xmlScene->NextSiblingElement();
    }

    return (nStatus);
}

int showEpisodeStatus(std::string filename, std::string storyPrimary = "", std::string storySecondary = "")
{
    int nStatus = 0;

    std::string textIndent = "        ";
    tinyxml2::XMLElement *xmlElement = getRootElementOfXmlFile(f_fileBasePath + "/" + filename);
    if (xmlElement != nullptr)
    {

        // TODO Support TodoList (Maybe I can put this into the 'SessionStatus' as TODO lines, which can the be listed? (maybe I can keep the TODO list in a comment until the session is ready for the Roll20 upload?))
        std::string sessionStatus = getStringContentOfNamedSubElement(xmlElement, "sessionStatus");

        if ((sessionStatus.compare("Done") == 0) || (sessionStatus.compare("done") == 0))
        {
            std::cout << " - Done" << std::endl;
        }
        else
        {
            std::cout << std::endl;
            std::cout << textIndent << " " << storyPrimary << " / " << storySecondary << std::endl;
            showStatusGenericElement(xmlElement, "Prologue", textIndent);
            showStatusGenericElement(xmlElement, "CrawlText", textIndent);

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
                xmlEncounter = xmlEncounter->NextSiblingElement("Encounter");
            }
        }
    }
    else
    {
        std::cout << " - Missing file" << std::endl;
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
            std::string oneLineSummary = getStringContentOfNamedSubElement(xmlSession, "OneLineSummary");
            std::cout << identifier << " - " << filename << " - " << oneLineSummary;
            std::string storyPrimary = getStringContentOfNamedSubElement(xmlSession, "Primary");
            std::string storySecondary = getStringContentOfNamedSubElement(xmlSession, "Secondary");

            if (filename.length() > 0)
            {
                showEpisodeStatus(filename, storyPrimary, storySecondary);
            }
            else
            {
                std::cout << "Missing" << std::endl;
            }
            xmlSession = xmlSession->NextSiblingElement("Session");
        }
    }
    return (nStatus);
}

int showTenMinutteMovie(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;
    std::string textIndent = "      ";

    tinyxml2::XMLElement *xmlTenMinuteMovie = xmlElement->FirstChildElement("TenMinutteMovie");
    if (xmlTenMinuteMovie == nullptr)
    {
        std::cout << "TenMinutteMovie: - none defined" << std::endl;
    }
    else
    {
        // The f_mapKeySceneNameToDescription is used in generateScene
        f_mapKeySceneNameToDescription["Exposition"] = showStatusGenericElement(xmlTenMinuteMovie, "Exposition", textIndent);
        f_mapKeySceneNameToDescription["Opening"] = showStatusGenericElement(xmlTenMinuteMovie, "Opening", textIndent);
        f_mapKeySceneNameToDescription["Incident"] = showStatusGenericElement(xmlTenMinuteMovie, "Incident", textIndent);
        f_mapKeySceneNameToDescription["TurningPoint"] = showStatusGenericElement(xmlTenMinuteMovie, "TurningPoint", textIndent);
        f_mapKeySceneNameToDescription["Complication"] = showStatusGenericElement(xmlTenMinuteMovie, "Complication", textIndent);
        f_mapKeySceneNameToDescription["Trouble"] = showStatusGenericElement(xmlTenMinuteMovie, "Trouble", textIndent);
        f_mapKeySceneNameToDescription["AllSeemsLost"] = showStatusGenericElement(xmlTenMinuteMovie, "AllSeemsLost", textIndent);
        f_mapKeySceneNameToDescription["Prepare"] = showStatusGenericElement(xmlTenMinuteMovie, "Prepare", textIndent);
        f_mapKeySceneNameToDescription["ResolutionEducation"] = showStatusGenericElement(xmlTenMinuteMovie, "ResolutionEducation", textIndent);
    }
    return (nStatus);
}

int showCharacterWeb(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;
    std::string textIndent = "      ";

    std::map<std::string, bool> expectedType = {
        {"Main Character", false},
        {"Antagonist", false},
        {"FakeAntagonist-ActualProtagonist", false},
        {"Protagonist", false},
        {"FakeProtagonist-ActualAntagonist", false}};

    tinyxml2::XMLElement *xmlCharacterWeb = xmlElement->FirstChildElement("CharacterWeb");
    if (xmlCharacterWeb == nullptr)
    {
        std::cout << "CharacterWeb: - none defined" << std::endl;
    }
    else
    {
        std::cout << "    CharacterWeb: " << std::endl;
        // itterate through the sessions
        tinyxml2::XMLElement *xmlSession = xmlCharacterWeb->FirstChildElement("Character");
        while (xmlSession != nullptr)
        {
            //listAllAttributes(xmlSession);
            std::cout << "      Character: ";
            // get id attr
            std::string plotSubject = getStringAttributeOfElement(xmlSession, "PlotSubject");
            // get filename attr
            std::string characterType = getStringAttributeOfElement(xmlSession, "Type");
            std::string characterName = getStringAttributeOfElement(xmlSession, "Name");
            // get note
            std::string oneLineSummary = getStringContentOfNamedSubElement(xmlSession, "OneLineSummary");
            std::cout << characterName << " - " << characterType << " - " << plotSubject << std::endl;
            std::string storyPrimary = getStringContentOfNamedSubElement(xmlSession, "Primary");
            std::string storySecondary = getStringContentOfNamedSubElement(xmlSession, "Secondary");

            expectedType[characterType] = true;

            xmlSession = xmlSession->NextSiblingElement("Character");
        }

        std::map<std::string, bool>::iterator it = expectedType.begin();
        while (it != expectedType.end())
        {
            if (it->second == false)
            {
                std::cout << textIndent << " character type " << it->first << " : Missing" << std::endl;
            }
            it++;
        }
    }
    return (nStatus);
}

int showPlotDiagram(tinyxml2::XMLElement *xmlElement)
{
    int nStatus = 0;
    std::string textIndent = "            ";

    tinyxml2::XMLElement *xmlPlotDiagram = xmlElement->FirstChildElement("PlotDiagram");
    if (xmlPlotDiagram == nullptr)
    {
        std::cout << "PlotDiagram: - none defined" << std::endl;
    }
    else
    {
        std::cout << "    PlotDiagram: " << std::endl;
        // itterate through the sessions
        tinyxml2::XMLElement *xmlAct = xmlPlotDiagram->FirstChildElement("Act");
        while (xmlAct != nullptr)
        {
            // get id attr
            std::string actNumber = getStringAttributeOfElement(xmlAct, "Number");
            std::cout << "      Act: " << actNumber << std::endl;

            tinyxml2::XMLElement *xmlSequence = xmlAct->FirstChildElement("Sequence");
            while (xmlSequence != nullptr)
            {
                // get id attr
                std::string sequenceNumber = getStringAttributeOfElement(xmlSequence, "Number");
                std::string sequenceName = getStringAttributeOfElement(xmlSequence, "Name");
                std::cout << "         Sequence: " << sequenceNumber << " - " << sequenceName << std::endl;

                /* TODO move to episode 
                showStatusGenericElement(xmlSequence, "Weakness", textIndent);
                showStatusGenericElement(xmlSequence, "Need", textIndent);
                showStatusGenericElement(xmlSequence, "Desire", textIndent);
                showStatusGenericElement(xmlSequence, "Opponent", textIndent);
                showStatusGenericElement(xmlSequence, "Plan", textIndent);
                showStatusGenericElement(xmlSequence, "Battle", textIndent);
                showStatusGenericElement(xmlSequence, "SelfRevelation", textIndent);
                showStatusGenericElement(xmlSequence, "NewEquilibrium", textIndent);
                */

                showSceneListStatus(xmlSequence, true);

                xmlSequence = xmlSequence->NextSiblingElement("Sequence");
            }

            xmlAct = xmlAct->NextSiblingElement("Act");
        }
    }
    return (nStatus);
}

tinyxml2::XMLNode *createStoryBootstrapIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createStoryBootstrapIfMissing()" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("StoryBootstrap");
    if (xmlResultElement == nullptr)
    {
        // https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial/
        // TODO change to add this directly to the xmlRoot.
        tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("StoryBootstrap");
        xmlResultElement = xmlRoot->InsertFirstChild(xmlNewElement);
    }
    return (xmlResultElement);
}

tinyxml2::XMLNode *createPlayerCharactersIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createPlayerCharactersIfMissing()" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("PlayerCharacters");
    if (xmlResultElement == nullptr)
    {
        tinyxml2::XMLNode *xmlParentNode = createStoryBootstrapIfMissing(xmlRoot, updateStructure);
        if (xmlParentNode == nullptr)
        {
            std::cout << "!!! createStoryBootstrapIfMissing() returned a nullptr" << std::endl;
            exit(99);
        }
        // TODO Add directly to xmlRoot, instead
        tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("PlayerCharacters");
        xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewElement);
    }

    return (xmlResultElement);
}

tinyxml2::XMLNode *createStoryDesignIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createStoryDesignIfMissing()" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("StoryDesign");
    if (xmlResultElement == nullptr)
    {
        tinyxml2::XMLNode *xmlParentNode = createPlayerCharactersIfMissing(xmlRoot, updateStructure);
        if (xmlParentNode == nullptr)
        {
            std::cout << "!!! createStoryBootstrapIfMissing() returned a nullptr" << std::endl;
            exit(99);
        }
        tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("StoryDesign");
        xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewElement);
    }

    return (xmlResultElement);
}

tinyxml2::XMLNode *createTenMinutteMovieIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createTenMinutteMovieIfMissing()" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("TenMinutteMovie");
    if (xmlResultElement == nullptr)
    {
        tinyxml2::XMLNode *xmlParentNode = createStoryDesignIfMissing(xmlRoot, updateStructure);
        if (xmlParentNode == nullptr)
        {
            std::cout << "!!! createTenMinutteMovieIfMissing() returned a nullptr" << std::endl;
            exit(99);
        }
        tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("TenMinutteMovie");
        xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewElement);
    }

    return (xmlResultElement);
}

tinyxml2::XMLNode *createPlotPlanIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createPlotPlanIfMissing()" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("PlotPlan");
    if (xmlResultElement != nullptr)
    {
        // TODO delete the existing plotplan
    }

    tinyxml2::XMLNode *xmlParentNode = createTenMinutteMovieIfMissing(xmlRoot, updateStructure);
    if (xmlParentNode == nullptr)
    {
        std::cout << "!!! createPlotPlanIfMissing() returned a nullptr" << std::endl;
        exit(99);
    }
    tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("PlotPlan");
    xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewElement);

    loadPlayerList(xmlRoot);

    return (xmlResultElement);
}

tinyxml2::XMLNode *createCharacterWebIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createCharacterWebIfMissing() - 1" << std::endl;
    if (xmlRoot == nullptr)
    {
        std::cout << "!!! createCharacterWebIfMissing() xmlRoot is a nullptr" << std::endl;
        exit(99);
    }
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("CharacterWeb");
    std::cout << "DDD createCharacterWebIfMissing() - 2" << std::endl;
    if (xmlResultElement == nullptr)
    {
        tinyxml2::XMLNode *xmlParentNode = createPlotPlanIfMissing(xmlRoot, updateStructure);
        std::cout << "DDD createCharacterWebIfMissing() - 3" << std::endl;
        if (xmlParentNode == nullptr)
        {
            std::cout << "!!! createCharacterWebIfMissing() returned a nullptr" << std::endl;
            exit(99);
        }
        tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("CharacterWeb");
        std::cout << "DDD createCharacterWebIfMissing() - 4" << std::endl;
        // TODO V populate this
        xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewElement);
        std::cout << "DDD createCharacterWebIfMissing() - 5" << std::endl;
    }
    std::cout << "DDD createCharacterWebIfMissing() - 6" << std::endl;

    return (xmlResultElement);
}

tinyxml2::XMLNode *createPanthonIfMissing(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createPanthonIfMissing()" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("Panthon");
    if (xmlResultElement == nullptr)
    {
        tinyxml2::XMLNode *xmlParentNode = createCharacterWebIfMissing(xmlRoot, updateStructure);
        if (xmlParentNode == nullptr)
        {
            std::cout << "!!! createPanthonIfMissing() - createCharacterWebIfMissing() returned a nullptr" << std::endl;
            exit(99);
        }
        if (f_xmlDoc == nullptr)
        {
            std::cout << "!!! createPanthonIfMissing() f_xmlDoc is a nullptr" << std::endl;
            exit(99);
        }
        tinyxml2::XMLElement *xmlNewElement = f_xmlDoc->NewElement("Panthon");
        // TODO V populate this
        xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewElement);
    }

    return (xmlResultElement);
}

void createSessionPlanEntry(tinyxml2::XMLElement *xmlSession, int sessionId, std::string primaryText, std::string secondaryText)
{
    xmlSession->SetAttribute("Id", std::to_string(sessionId).c_str());
    xmlSession->SetAttribute("Filename", "");
    int playerIndex = ((sessionId - 2) % f_numberOfPlayers);
    tinyxml2::XMLElement *xmlReuse = xmlSession->InsertNewChildElement("Primary");
    xmlReuse->SetText(primaryText.c_str());
    xmlReuse = xmlSession->InsertNewChildElement("Secondary");
    xmlReuse->SetText(secondaryText.c_str());
    xmlReuse = xmlSession->InsertNewChildElement("Note");
}

tinyxml2::XMLNode *createNewSeasonPlanElementAndRequiredStructures(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createNewSeasonPlanElementAndRequiredStructures() - 1" << std::endl;
    adjustTheNumberOfSessions();

    tinyxml2::XMLNode *xmlResultNode = nullptr;
    tinyxml2::XMLNode *xmlParentNode = createPanthonIfMissing(xmlRoot, updateStructure);
    // TODO move some of this out of the if statement
    if (xmlParentNode == nullptr)
    {
        std::cout << "!!! createNewSesonPlanElementAndRequiredStructures() returned a nullptr" << std::endl;
        exit(99);
    }
    tinyxml2::XMLElement *xmlSeasonPlan = f_xmlDoc->NewElement("NewSeasonPlan");
    // TODO V populate this
    xmlResultNode = xmlRoot->InsertAfterChild(xmlParentNode, xmlSeasonPlan);

    tinyxml2::XMLElement *xmlResultElement = xmlResultNode->ToElement();

    bool removeLastPlayerFromList = false;
    // TODO how should this look?
    // If there are 4 or more players and it is an even number of players, then add an extra 'player' and call it 'story'
    if (f_numberOfPlayers % 2 == 0)
    {
        listOfPlayers.push_back("story");
        f_numberOfPlayers = listOfPlayers.size();
        removeLastPlayerFromList = true;
    }

    // First session
    tinyxml2::XMLElement *xmlSession = xmlResultElement->InsertNewChildElement("Session");
    xmlSession->SetAttribute("Id", "1");
    xmlSession->SetAttribute("Filename", "");
    tinyxml2::XMLElement *xmlReuse = xmlSession->InsertNewChildElement("Primary");
    xmlReuse->SetText("Story arc");
    xmlReuse = xmlSession->InsertNewChildElement("Secondary");
    xmlReuse->SetText("Resolve Previous Arch");
    xmlReuse = xmlSession->InsertNewChildElement("Note");

    std::string storyArc = "Story Arc";

    for (int sessionId = 2; sessionId < f_numberOfSessions; sessionId++)
    {
        int playerIndex = ((sessionId - 2) % f_numberOfPlayers);
        std::string playerName = listOfPlayers[playerIndex];
        xmlSession = xmlResultElement->InsertNewChildElement("Session");
        if ((sessionId % 2) == 0)
        {
            createSessionPlanEntry(xmlSession, sessionId, playerName, storyArc);
        }
        else
        {
            createSessionPlanEntry(xmlSession, sessionId, storyArc, playerName);
        }
    }

    // Last session
    xmlSession = xmlResultElement->InsertNewChildElement("Session");
    xmlSession->SetAttribute("Id", std::to_string(f_numberOfSessions).c_str());
    xmlSession->SetAttribute("Filename", "");
    xmlReuse = xmlSession->InsertNewChildElement("Primary");
    xmlReuse->SetText("Conclusion");
    xmlReuse = xmlSession->InsertNewChildElement("Secondary");
    xmlReuse->SetText("Hint to next Arc");
    xmlReuse = xmlSession->InsertNewChildElement("Note");

    if (removeLastPlayerFromList)
    {
        listOfPlayers.pop_back();
        f_numberOfPlayers = listOfPlayers.size();
    }
    deleteelementIfExists(xmlRoot, "SeasonPlan");
    xmlSeasonPlan->SetName("SeasonPlan");
    return (xmlResultNode);
}

std::pair<std::string, std::string> getPrimaryAndSecondaryForSessionId(tinyxml2::XMLElement *xmlElement, int sessionId)
{
    std::pair<std::string, std::string> returnPair("pair", "odd");
    return (returnPair);
}

/**
 * 
 * Expected order:
 *  StoryBootstrap
 *  StoryDesign
 *  TenMinutteMovie
 *  PlotPlan
 *  CharacterWeb
 *  Pantheon
 *  SeasonPlan
 *  Plotdiagram
 */
tinyxml2::XMLNode *createNewPlotDiagramElementAndRequiredStructures(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    std::cout << "DDD createNewPlotDiagramElementAndRequiredStructures()" << std::endl;
    std::cout << "DDD B" << std::endl;
    tinyxml2::XMLNode *xmlResultElement = xmlRoot->FirstChildElement("NewPlotDiagram");
    if (xmlResultElement == nullptr)
    {
        tinyxml2::XMLNode *xmlParentNode = createNewSeasonPlanElementAndRequiredStructures(xmlRoot, updateStructure);
        // TODO move some of this out of the if statement
        if (xmlParentNode == nullptr)
        {
            std::cout << "!!! createNewPlotDiagramElementAndRequiredStructures() returned a nullptr" << std::endl;
            exit(99);
        }
        std::cout << "DDD createNewPlotDiagramElementAndRequiredStructures() creating NewPlotDiagram" << std::endl;
        tinyxml2::XMLElement *xmlNewPlotDiagram = f_xmlDoc->NewElement("NewPlotDiagram");
        // TODO V populate this
        xmlResultElement = xmlRoot->InsertAfterChild(xmlParentNode, xmlNewPlotDiagram);

        adjustTheNumberOfSessions();
        generateSession(xmlNewPlotDiagram, 1, "Story arc", "Resolve Previous Arch");
        int playerIndexCounter = 0;
        for (int sessionNumber = 2; sessionNumber < f_numberOfSessions; sessionNumber++)
        {
            int playerIndex = (playerIndexCounter % f_numberOfPlayers);
            // std::cout << "DDD playerIndex: " << playerIndex << " sessionNumber: " << sessionNumber << std::endl;
            std::string focusPlayerName = listOfPlayers.at(playerIndex);
            if ((sessionNumber % 2) == 0)
            {
                generateSession(xmlNewPlotDiagram, sessionNumber, focusPlayerName, "Story arc");
            }
            else
            {
                generateSession(xmlNewPlotDiagram, sessionNumber, "Story arc", focusPlayerName);
            }
            playerIndexCounter++;
        }
        // last scene(40) is missing
        generateSession(xmlNewPlotDiagram, f_numberOfSessions, "Conclusion", "Hint to next Arc");
        // TODO replace old structure
    }
    //f_xmlDoc->Print();

    return (xmlResultElement);
}

/** Load the given season file and go through Design status and itterate the season plan.
 * @param std::string Name of season xml file
 * 
 * @see showStoryDesignStatus
 * @see showSeasonPlanStatus
 * 
 */
int showSeasonStatus(tinyxml2::XMLElement *xmlRoot, bool updateStructure = false)
{
    int nStatus = 0;

    if (xmlRoot != nullptr)
    {
        if (updateStructure)
        {
            createNewPlotDiagramElementAndRequiredStructures(xmlRoot);
        }

        // StoryDesign
        showStoryDesignStatus(xmlRoot);

        // TenMinutteMove
        showTenMinutteMovie(xmlRoot);

        // TODO PlotPlan

        // CharacterWeb
        showCharacterWeb(xmlRoot);

        // PlotDiagram
        showPlotDiagram(xmlRoot);

        // TODO Pantheon (should this go into the Handbook? or is this the pantheon, for only this season. and if a character will be used in later season, only then will it go into the Handbook?)

        // SeasonPlan
        showSeasonPlanStatus(xmlRoot);
    }
    else
    {
        std::cerr << "!!! root XML element is null" << std::endl;
        exit(99);
    }

    return (nStatus);
}

// TODO Document all the functions with doxy or whatever should be the documentation tool

/** Show the SeriesHandbookStatus and itterate through the Seasons
 * @param tinyxml2::XMLElement* root xml element of the Series xml file.
 * 
 * @see showSeriesHandbookStatus
 * @see showSeasonStatus
 */
int showSeriesStatus(tinyxml2::XMLElement *xmlRoot)
{
    int nStatus = 0;

    // TODO get Handbook
    tinyxml2::XMLElement *xmlSeriesHandbookElement = xmlRoot->FirstChildElement("SeriesHandbook");
    nStatus = showSeriesHandbookStatus(xmlSeriesHandbookElement);

    // TODO go through seasons
    tinyxml2::XMLElement *xmlSeasonElement = xmlRoot->FirstChildElement("Season");
    if (xmlSeasonElement == nullptr)
    {
        std::cout << "Season: - none defined" << std::endl;
    }
    while (xmlSeasonElement)
    {
        std::string filename = "";

        const char *attribubteContent = xmlSeasonElement->Attribute("Filename");
        if (attribubteContent != nullptr)
        {
            filename = attribubteContent;
        }
        else
        {
            std::cerr << "EEE " << __FILE__ << "(" << __LINE__ << ")"
                      << "'Filename' atribute not found in XML file." << std::endl;
        }

        if (filename == "")
        {
            std::cout << "    Season filename: No entry" << std::endl;
        }
        else
        {
            std::cout << "XXX implement this: 'nStatus = showSeasonStatus(filename);'" << std::endl;
        }
        xmlSeasonElement = xmlSeasonElement->NextSiblingElement("Season");
    }

    return (nStatus);
}

/**
 * Loads the charcter definitons into the master map: f_mapCharacterDefinitions.
 * 
 */
void LoadCharacterDefinitions(tinyxml2::XMLElement *xmlNode)
{
    tinyxml2::XMLElement *xmlHeadingElement = xmlNode->FirstChildElement("Pantheon");
    if (xmlHeadingElement != nullptr)
    {
        tinyxml2::XMLElement *xmlActor = xmlHeadingElement->FirstChildElement("Character");
        while (xmlActor != nullptr)
        {
            std::string actorName = getStringAttributeOfElement(xmlActor, "Name");
            f_mapCharacterDefinitions[actorName] = true;
            std::cout << "ACTOR NAME: " << actorName << std::endl;
            xmlActor = xmlActor->NextSiblingElement("Character");
        }
    }
    xmlHeadingElement = xmlNode->FirstChildElement("CharacterWeb");
    if (xmlHeadingElement != nullptr)
    {
        tinyxml2::XMLElement *xmlActor = xmlHeadingElement->FirstChildElement("Character");
        while (xmlActor != nullptr)
        {
            std::string actorName = getStringAttributeOfElement(xmlActor, "Name");
            if (actorName.length() > 0)
            {
                f_mapCharacterDefinitions[actorName] = true;
                std::cout << "ACTOR NAME: " << actorName << std::endl;
            }
            xmlActor = xmlActor->NextSiblingElement("Character");
        }
    }
}

/**
 * Load f_mapSequenceIdToXmlElement and f_mapSceneIdToXmlElement
 */
void LoadPlotPlan(tinyxml2::XMLElement *xmlRoot)
{
    tinyxml2::XMLElement *xmlPlotDiagramElement = xmlRoot->FirstChildElement("PlotDiagram");
    if (xmlPlotDiagramElement != nullptr)
    {
        tinyxml2::XMLElement *xmlSequence = xmlPlotDiagramElement->FirstChildElement("Sequence");
        while (xmlSequence != nullptr)
        {
            std::string sequenceNumber = getStringAttributeOfElement(xmlSequence, "Number");
            if (sequenceNumber.length() > 0)
            {
                f_mapSequenceIdToXmlElement[std::stoi(sequenceNumber)] = xmlSequence;
            }
            tinyxml2::XMLElement *xmlScene = xmlPlotDiagramElement->FirstChildElement("Scene");
            while (xmlScene != nullptr)
            {
                std::string sceneId = getStringAttributeOfElement(xmlScene, "Id");
                if (sceneId.length() > 0)
                {
                    f_mapSequenceIdToXmlElement[std::stoi(sceneId)] = xmlScene;
                }
                xmlScene = xmlScene->NextSiblingElement("Scene");
            }
            xmlSequence = xmlSequence->NextSiblingElement("Sequence");
        }
    }
}

int main(int argc, char *argv[])
{
    // TODO support both series and session files

    std::string pathAndFilenameXml = "series.xml";
    std::string fileType = "series";

    bool updateStructure = false;

    // TODO V add --update-PlotDiagram

    const char *const short_opts = "a:e:hs:u";
    const option long_opts[] = {
        {"autoupdate", no_argument, nullptr, 'u'},
        {"episodefile", required_argument, nullptr, 'e'},
        {"help", no_argument, nullptr, 'h'},
        {"seasonfile", required_argument, nullptr, 'a'},
        {"seriesfile", required_argument, nullptr, 's'},
        {nullptr, no_argument, nullptr, 0}};
    // TODO support --status (current op method)
    // TODO support --update will save an updated version of the xml file being read

    int index;
    int opt = 0;
    while (opt != -1)
    {
        // TODO FAIL if unexpected parms are provided

        opt = getopt_long(argc, argv, short_opts, long_opts, &index);

        switch (opt)
        {
        case 'a':
            pathAndFilenameXml = optarg;
            fileType = "season";
            break;
        case 'e':
            pathAndFilenameXml = optarg;
            fileType = "episode";
            break;
        case 's':
            pathAndFilenameXml = optarg;
            fileType = "series";
            break;
        case 'u':
            updateStructure = true;
            break;
        }
    }

    std::string fileNameXml = "";

    std::filesystem::path fullPathForFile{pathAndFilenameXml};
    f_fileBasePath = "./";
    if (fullPathForFile.has_parent_path())
    {
        f_fileBasePath = fullPathForFile.parent_path().string();
        fileNameXml = fullPathForFile.filename().string();
    }

    std::cout << "Version: " << versionText << std::endl;

    std::cout << "DDD full: " << pathAndFilenameXml << std::endl;
    std::cout << "DDD path: " << f_fileBasePath << std::endl;
    std::cout << "DDD file: " << fileNameXml << std::endl;

    f_xmlDoc = new tinyxml2::XMLDocument();
    tinyxml2::XMLError enumValue = f_xmlDoc->LoadFile(pathAndFilenameXml.c_str());
    if (enumValue == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLElement *xmlRoot = f_xmlDoc->RootElement();
        if (xmlRoot != nullptr)
        {
            LoadCharacterDefinitions(xmlRoot);
            // TODO isn't is only the season file that has the plot plan
            LoadPlotPlan(xmlRoot);

            if (fileType.compare("series") == 0)
            {
                // TODO maybe also replace xmlRoot with fileNameXml for consistency.
                showSeriesStatus(xmlRoot);
            }
            else if (fileType.compare("season") == 0)
            {
                std::cout << "DDD main() - about to call showSeasonStatus()" << std::endl;
                showSeasonStatus(xmlRoot, updateStructure);
            }
            else if (fileType.compare("episode") == 0)
            {
                showEpisodeStatus(fileNameXml);
            }
            // XMLError is an enum
            tinyxml2::XMLError enumValue = f_xmlDoc->SaveFile("XXX_file.xml");
        }
        else
        {
            std::cerr << "!!! root XML element not found" << std::endl;
        }
    }
    else
    {
        std::string xmlErrorString = f_xmlDoc->ErrorStr();
        std::cerr << "!!! XML error in file?: " << xmlErrorString << std::endl;
        //tinyxml2::XMLDocument::PrintError()
    }
}