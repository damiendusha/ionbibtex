
#include "CDataSourceURL.h"
#include "Utilities/IO/CTextFile.h"

#include <iostream>
#include <stdlib.h>

CDataSourceURL::CDataSourceURL(const std::string& filename)
    : CDataSource(filename)
{
}

CDataSourceURL::~CDataSourceURL()
{
}

bool CDataSourceURL::ParseDataSource(std::vector< std::string >& data)
{
    const std::string site = "site.txt";
    const std::string command("wget -O " + site + " '" + m_resourceName + "' > /dev/null");

    int ok = system(command.c_str());
    if (ok != 0)
    {
        std::cerr << "Error getting URL " << m_resourceName << std::endl;
        return false;
    }

    Utilities::IO::CTextFileReader reader;
    if (!reader.LoadFile(site))
    {
        std::cerr << "Cannot read file \"" << site << "\"" << std::endl;
        return false;
    }

    // Get everything from the file
    reader.GetEntireData(data);

    return true;
}
