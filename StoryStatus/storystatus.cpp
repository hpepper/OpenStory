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

/**
 * List all the attributes that the given element has.
 */
void listAllAttributes(tinyxml2::XMLElement *xmlElement)
{
    const tinyxml2::XMLAttribute *pAttrib = xmlElement->FirstAttribute();

    while (pAttrib)
    {
        std::cout << "DDD attibute: " << pAttrib->Name() << "  value: " << pAttrib->Value() << std::endl;
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
            std::cout << "Done compare" << std::endl;
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
                std::cout << "Missing" << std::endl;
            }
            // if contain TODO
            else if (elementContent.find("TODO") > 0)
            {
                std::cout << "Done find" << std::endl;
            }
            else
            {
                std::cout << "Done (default)" << std::endl;
            }
            
        }
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
                // Pantheon
                // SeasonPlan
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
            showSeriesStatus(xmlRoot, directoryPathToSeriesFile);
        }
        else
        {
            std::cerr << "!!! root XML element not found" << std::endl;
        }
    }
}