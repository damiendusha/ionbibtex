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

#include "CPublication.h"

#include "MetadataElement/CMetadataYear.h"
#include "MetadataElement/CMetadataAuthor.h"

#include <iostream>


CPublication::CPublication(const std::string& bibType)
    : m_bibType(bibType)
{
}

CPublication::~CPublication()
{
    for (std::vector<CMetadataElement*>::iterator it = m_metadata.begin() ; it != m_metadata.end() ; ++it)
    {
        delete(*it);
    }

    m_metadata.clear();
}

bool CPublication::ParseData(const CCitationMetadata& data)
{
    for (std::vector<CMetadataElement*>::iterator it = m_metadata.begin() ; it != m_metadata.end() ; ++it)
    {
        if (!(*it)->ParseData(data))
        {
            return false;
        }
    }

    return true;
}


std::string CPublication::WriteBibTeX()
{
    std::string record;
    record += WriteBibTeXRecordOpening();
    record += WriteBibTeXRecordData();
    record += WriteBibTeXRecordClosing();

    return record;
}

std::string CPublication::WriteBibTeXRecordOpening()
{
    return "@" + m_bibType + "{" + WriteBibTeXRecordKey() + ",\n";
}

std::string CPublication::WriteBibTeXRecordKey()
{
    CMetadataYear* year = NULL;
    CMetadataAuthor* author = NULL;

    // Find the author and year
    for (std::vector<CMetadataElement*>::iterator it = m_metadata.begin() ; it != m_metadata.end() ; ++it)
    {
        if (!year)
            year = dynamic_cast<CMetadataYear*>(*it);

        if (!author)
            author = dynamic_cast<CMetadataAuthor*>(*it);
    }

    std::string key;
    if (author)
        key += author->GetFirstAuthorSurname();

    if (year)
        key += year->GetYear();

    return key;
}

std::string CPublication::WriteBibTeXRecordData()
{
    std::string out;
    for (std::vector<CMetadataElement*>::iterator it = m_metadata.begin() ; it != m_metadata.end() ; ++it)
    {
        std::string line = (*it)->GetBibtexLine();
        out += line;

        // Do not print the comma on the final record
        if (it + 1 != m_metadata.end())
            out += ",";

        out += "\n";
    }

    return out;
}

std::string CPublication::WriteBibTeXRecordClosing()
{
    return "}\n";
}

