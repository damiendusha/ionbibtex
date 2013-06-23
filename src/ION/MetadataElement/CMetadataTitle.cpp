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

#include "CMetadataTitle.h"
#include <stdio.h>


CMetadataTitle::CMetadataTitle() :
    CMetadataElement("title")
{
}


CMetadataTitle::~CMetadataTitle()
{
}


std::string CMetadataTitle::GetBibtexLine() const
{
    char buffer[m_title.size() + 1024];
    sprintf(buffer, "title = {%s}", m_title.c_str());
    
    return std::string(buffer);
}


bool CMetadataTitle::ParseData(const std::vector< std::string> &data)
{
    const std::string prefix("<meta name=\"citation_title\" content=\"");
    const std::string suffix("\">");
    
    return ParseSingleLine(data, prefix, suffix, m_title);
}



