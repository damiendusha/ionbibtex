/*
* Copyright (C) 2013, 2014, 2020 Damien Dusha
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

#include "CMetadataPages.h"
#include "Utilities/StringUtilities/StringUtilities.h"

#include <stdio.h>

CMetadataPages::CMetadataPages() :
    CMetadataElement("pages"),
    m_startPage(0),
    m_endPage(0)
{
}

CMetadataPages::~CMetadataPages()
{
}

bool CMetadataPages::ParseData(const CCitationMetadata &metadata)
{
    if (!metadata.HasElement(ECitationElement::kFirstPage) ||
        !metadata.HasElement(ECitationElement::kLastPage))
    {
        return false;
    }

    std::string firstpage_string = metadata.GetValue(ECitationElement::kFirstPage);
    std::string lastpage_string = metadata.GetValue(ECitationElement::kLastPage);

    bool ok = true;
    ok = ok && Utilities::ParseValue<int>(firstpage_string, m_startPage);
    ok = ok && Utilities::ParseValue<int>(lastpage_string, m_endPage);

    return ok;
}

std::string CMetadataPages::GetBibtexLine() const
{
    char buffer[1024];
    sprintf(buffer, "pages = {%d - %d}", m_startPage, m_endPage);

    return std::string(buffer);
}


