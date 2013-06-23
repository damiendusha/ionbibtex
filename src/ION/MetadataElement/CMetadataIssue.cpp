/*
* Copyright (C) 2013 Damien Dusha
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

#include "CMetadataIssue.h"
#include <stdio.h>


CMetadataIssue::CMetadataIssue() :
    CMetadataElement("journal")
{
}


CMetadataIssue::~CMetadataIssue()
{
}


std::string CMetadataIssue::GetBibtexLine() const
{
    char buffer[m_issue.size() + 1024];
    sprintf(buffer, "title = {%s}", m_issue.c_str());

    return std::string(buffer);
}


bool CMetadataIssue::ParseData(const std::vector< std::string> &data)
{
    const std::string prefix("<meta name=\"citation_issue\" content=\"");
    const std::string suffix("\">");
    
    return ParseSingleLine(data, prefix, suffix, m_issue);
}



