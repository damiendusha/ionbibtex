/*
* Copyright (C) 2013, 2014 Damien Dusha
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


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

    std::string prefix("<meta xmlns=\"http://www.w3.org/1999/xhtml\" name=\"citation_author\" content=\"");
    std::string suffix("\" />");

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



