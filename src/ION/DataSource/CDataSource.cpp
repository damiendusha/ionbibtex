
#include "CDataSource.h"
#include "CDataSourceFile.h"
#include "CDataSourceURL.h"


CDataSource::CDataSource(const std::string& resourceName)
    : m_resourceName(resourceName)
{
}

CDataSource::~CDataSource()
{

}

CDataSource* CDataSource::GetDataSource(const std::string& location)
{
    if (location.empty())
        return NULL;

    std::string file = location;

    // Assume a paper number if a digit is given
    if ( isdigit(file[0]) )
    {
        return new CDataSourceURL(std::string("http://www.ion.org/search/view_abstract.cfm?jp=p&idno=") + location);
    }

    // Check for a URL
    if (file.find("http://") != std::string::npos || file.find("https://") != std::string::npos)
    {
        return new CDataSourceURL(file);
    }

    return new CDataSourceFile(file);
}


