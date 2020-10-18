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