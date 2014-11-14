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

bool CMetadataPages::ParseData(const std::vector< std::string >& data)
{
    const std::string firstpage_prefix("<meta xmlns=\"http://www.w3.org/1999/xhtml\" name=\"citation_firstpage\" content=\"");
    const std::string lastpage_prefix ("<meta xmlns=\"http://www.w3.org/1999/xhtml\" name=\"citation_lastpage\" content=\"");
    const std::string suffix("\" />");

    std::string firstpage_string;
    std::string lastpage_string;

    bool ok = true;
    ok = ok && ParseSingleLine(data, firstpage_prefix, suffix, firstpage_string);
    ok = ok && ParseSingleLine(data, lastpage_prefix,  suffix, lastpage_string);

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


