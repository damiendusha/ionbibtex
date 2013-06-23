
#include "CMetadataAuthor.h"


CMetadataAuthor::CMetadataAuthor() :
    CMetadataElement("author")
{
}

CMetadataAuthor::~CMetadataAuthor()
{
}

bool CMetadataAuthor::ParseData(const std::vector< std::string >& data)
{
    m_authorList.clear();

    std::string prefix("<meta name=\"citation_author\" content=\"");
    std::string suffix("\">");

    std::vector<size_t> lines = LinesThatContainsString(data, prefix);

    for (std::vector<size_t>::const_iterator it = lines.begin() ; it != lines.end() ; ++it)
    {
        std::string author;
        if (!ParseSingleLine(data[*it], prefix, suffix, author))
            return false;

        m_authorList.push_back(author);
    }

    return !m_authorList.empty();
}

std::string CMetadataAuthor::GetBibtexLine() const
{
    std::string output("author = {");
    for (unsigned int i = 0 ; i < m_authorList.size() - 1; ++i)
    {
        output += m_authorList[i] + std::string(" and ");
    }

    output += m_authorList[m_authorList.size() - 1] + std::string("}");
    return output;
}

std::string CMetadataAuthor::GetFirstAuthorSurname()
{
    if (m_authorList.size() == 0)
    {
        return "";
    }

    std::string surname;
    StripSuffix(m_authorList[0], ",", surname);

    return surname;
}



