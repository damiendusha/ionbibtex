
#include "CDataSourceFile.h"
#include "Utilities/IO/CTextFile.h"

#include <iostream>

CDataSourceFile::CDataSourceFile(const std::string& filename)
    : CDataSource(filename)
{
}


CDataSourceFile::~CDataSourceFile()
{
}


bool CDataSourceFile::ParseDataSource(std::vector< std::string >& data)
{
    Utilities::IO::CTextFileReader reader;
    if (!reader.LoadFile(m_resourceName))
    {
        std::cerr << "Cannot read file \"" << m_resourceName << "\"" << std::endl;
        return false;
    }

    // Get everything from the file
    reader.GetEntireData(data);

    return true;
}


